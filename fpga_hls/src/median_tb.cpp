#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "types.h"

#define TEST_WIDTH  64
#define TEST_HEIGHT 32

// Hardware Latency parameters for 5x5 window
// The center of a 5x5 window ending at current pixel is shifted by 2
#define GROUP_DELAY_Y 2 
#define GROUP_DELAY_X 2
// The explicit delay you added in HW for signals
#define SIGNAL_DELAY  4 

void median2d_hw(uint8_ct* r_in, uint8_ct* g_in, uint8_ct* b_in, 
                 uint1_ct* hs_in, uint1_ct* vs_in, uint1_ct* de_in, 
                 uint8_ct* r_out, uint8_ct* g_out, uint8_ct* b_out, 
                 uint1_ct* hs_out, uint1_ct* vs_out, uint1_ct* de_out);

uint8_t median_ref(const std::vector<uint8_t>& img, int x, int y, int w, int h) {
    std::vector<uint8_t> window;
    for (int wy = -2; wy <= 2; ++wy) {
        for (int wx = -2; wx <= 2; ++wx) {
            int cx = x + wx; int cy = y + wy;
            // Mirroring/Clamping boundary handling
            if (cx < 0) cx = 0; if (cx >= w) cx = w - 1;
            if (cy < 0) cy = 0; if (cy >= h) cy = h - 1;
            window.push_back(img[cy * w + cx]);
        }
    }
    std::sort(window.begin(), window.end());
    return window[12];
}

int main() {
    const int num_pixels = TEST_WIDTH * TEST_HEIGHT;
    std::vector<uint8_t> src_img(num_pixels);
    std::vector<uint8_t> hw_result(num_pixels);
    std::vector<uint8_t> sw_result(num_pixels);

    std::cout << "[TestBench] Generating Input Image..." << std::endl;
    for (int y = 0; y < TEST_HEIGHT; ++y) {
        for (int x = 0; x < TEST_WIDTH; ++x) {
            uint8_t val = (x * 4) % 256; 
            if ((rand() % 20) == 0) val = (rand() % 2) ? 0 : 255; 
            src_img[y * TEST_WIDTH + x] = val;
        }
    }

    std::cout << "[TestBench] Running Hardware Simulation..." << std::endl;
    uint8_ct r_in, g_in, b_in;
    uint1_ct hs_in, vs_in, de_in;
    uint8_ct r_out, g_out, b_out;
    uint1_ct hs_out, vs_out, de_out;

    // Run enough cycles to flush the pipeline
    int total_cycles = (TEST_WIDTH + 10) * (TEST_HEIGHT + 5); 
    int out_idx = 0; 

    for (int i = 0; i < total_cycles; ++i) {
        int frame_x = i % (TEST_WIDTH + 10); 
        int frame_y = i / (TEST_WIDTH + 10);
        bool active_video = (frame_x < TEST_WIDTH) && (frame_y < TEST_HEIGHT);

        if (active_video) {
            r_in = src_img[frame_y * TEST_WIDTH + frame_x];
            de_in = 1; hs_in = 1;
        } else {
            r_in = 0; de_in = 0; hs_in = 0;
        }
        vs_in = (frame_y < TEST_HEIGHT) ? 1 : 0;

        median2d_hw(&r_in, &g_in, &b_in, &hs_in, &vs_in, &de_in,
                    &r_out, &g_out, &b_out, &hs_out, &vs_out, &de_out);

        // Store result linearly based on valid output flag
        if (de_out == 1 && out_idx < num_pixels) {
            hw_result[out_idx++] = (uint8_t)r_out;
        }
    }

    std::cout << "[TestBench] Running Software Reference..." << std::endl;
    for (int y = 0; y < TEST_HEIGHT; ++y) {
        for (int x = 0; x < TEST_WIDTH; ++x) {
            sw_result[y * TEST_WIDTH + x] = median_ref(src_img, x, y, TEST_WIDTH, TEST_HEIGHT);
        }
    }

    std::cout << "[TestBench] Verifying Results..." << std::endl;
    int errors = 0;
    
    // START verification at y=2 because the first 2 lines of HW output 
    // are garbage (median of empty buffer + first lines).
    // STOP verification at H-2 because we run out of valid HW output data in this buffer capture.
    for (int y = 2; y < TEST_HEIGHT - 2; ++y) {
        for (int x = 2; x < TEST_WIDTH - 2; ++x) { 
            
            // Software Index: The pixel we want to verify
            int sw_idx = y * TEST_WIDTH + x;

            // Hardware Index calculation:
            // 1. To get the result for pixel (y,x), the HW needs input up to (y+2, x+2).
            // 2. The HW output stream `hw_result` is captured starting from `de_out` high.
            // 3. `de_out` is delayed by SIGNAL_DELAY (4) relative to input `de_in`.
            // 4. Therefore, hw_result[0] corresponds to input pixel index `SIGNAL_DELAY`.
            // Formula: HW_Index = (Input_Index_Needed) - SIGNAL_DELAY
            
            int input_row_needed = y + GROUP_DELAY_Y;
            int input_col_needed = x + GROUP_DELAY_X;
            int input_linear_idx = input_row_needed * TEST_WIDTH + input_col_needed;
            
            int hw_idx = input_linear_idx - SIGNAL_DELAY;

            // Safety check
            if (hw_idx < 0 || hw_idx >= num_pixels) continue;

            if (hw_result[hw_idx] != sw_result[sw_idx]) {
                std::cout << "Error at SW(x=" << x << ", y=" << y << ") "
                          << "vs HW(idx=" << hw_idx << ") -> "
                          << "Exp: " << (int)sw_result[sw_idx] 
                          << " Got: " << (int)hw_result[hw_idx] << std::endl;
                errors++;
                if(errors > 20) break;
            }
        }
        if(errors > 20) break;
    }
    
    if (errors == 0) {
        std::cout << "\n*** TEST PASSED! ***" << std::endl;
        return 0;
    } else {
        std::cout << "\n*** TEST FAILED with " << errors << " errors. ***" << std::endl;
        return 1;
    }
}