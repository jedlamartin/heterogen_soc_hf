#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <deque> // Added for delay simulation
#include "types.h"

#define TEST_WIDTH  64
#define TEST_HEIGHT 32

// Hardware Latency parameters for 5x5 window
// The explicit delay you added in HW for signals
constexpr int SIGNAL_DELAY = 15; 
// Number of lines to skip at the start (Line buffer fill time for 5x5)
constexpr int SKIP_LINES = 2;

// Function Declaration
void median2d_hw(uint8_ct* r_in, uint8_ct* g_in, uint8_ct* b_in, 
                 uint1_ct* hs_in, uint1_ct* vs_in, uint1_ct* de_in, 
                 uint8_ct* r_out, uint8_ct* g_out, uint8_ct* b_out, 
                 uint1_ct* hs_out, uint1_ct* vs_out, uint1_ct* de_out);

// Software Reference
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

    // 1. Generate Input Image
    std::cout << "[TestBench] Generating Input Image..." << std::endl;
    srand(123); // Fixed seed for reproducibility
    for (int i = 0; i < num_pixels; ++i) {
        uint8_t val = (i * 4) % 256; 
        if ((rand() % 20) == 0) val = (rand() % 2) ? 0 : 255; // Add salt & pepper noise
        src_img[i] = val;
    }

    // 2. Hardware Simulation
    std::cout << "[TestBench] Running Hardware Simulation..." << std::endl;
    uint8_ct r_in = 0, g_in = 0, b_in = 0;
    uint1_ct hs_in = 0, vs_in = 0, de_in = 0;
    uint8_ct r_out, g_out, b_out;
    uint1_ct hs_out, vs_out, de_out;

    // Queue to delay the C-simulation data to match the Control Signal Delay
    std::deque<uint8_t> r_delay_q;

    // Run enough cycles to flush the pipeline
    int total_cycles = (TEST_WIDTH + 10) * (TEST_HEIGHT + 5); 
    int out_idx = 0; 

    for (int i = 0; i < total_cycles; ++i) {
        // --- Input Generation ---
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

        // --- IP Call ---
        median2d_hw(&r_in, &g_in, &b_in, &hs_in, &vs_in, &de_in,
                    &r_out, &g_out, &b_out, &hs_out, &vs_out, &de_out);

        // --- C-Sim Compensation Logic ---
        
        // 1. Push current "instant" result into the delay line
        r_delay_q.push_back((uint8_t)r_out);

        // 2. Pop the "aligned" result (from SIGNAL_DELAY cycles ago)
        uint8_t r_aligned = 0;
        if (r_delay_q.size() > SIGNAL_DELAY) {
            r_aligned = r_delay_q.front();
            r_delay_q.pop_front();
        }

        // 3. Capture result based on VALID signal
        // Since de_out is delayed by the IP, and r_aligned is delayed by the queue,
        // they are now perfectly synchronized.
        if (de_out == 1 && out_idx < num_pixels) {
            hw_result[out_idx++] = r_aligned;
        }
    }

    // 3. Software Reference Calculation
    std::cout << "[TestBench] Running Software Reference..." << std::endl;
    for (int y = 0; y < TEST_HEIGHT; ++y) {
        for (int x = 0; x < TEST_WIDTH; ++x) {
            sw_result[y * TEST_WIDTH + x] = median_ref(src_img, x, y, TEST_WIDTH, TEST_HEIGHT);
        }
    }

    // 4. Verify Results
    std::cout << "[TestBench] Verifying Results..." << std::endl;
    int errors = 0;
    
    // Group delay for 5x5 window (Center is at index 2)
    const int GROUP_DELAY_X = 2;
    const int GROUP_DELAY_Y = 2;

    // We verify the "valid" center part of the image
    // START: y = 2 because rows 0,1 outputs correspond to negative window coordinates (padding)
    // STOP:  y < H-2 because the HW stream ends before flushing the very last pixels of the image
    for (int y = GROUP_DELAY_Y; y < TEST_HEIGHT - GROUP_DELAY_Y; ++y) {
        for (int x = GROUP_DELAY_X; x < TEST_WIDTH - GROUP_DELAY_X; ++x) { 
            
            // 1. Software Index (The pixel we want to verify)
            int sw_idx = y * TEST_WIDTH + x;

            // 2. Hardware Index (Where this pixel is located in the output stream)
            // The HW output for Center(x,y) appears when Input is at (y+2, x+2)
            // Linear Index = (Row + DelayY) * Width + (Col + DelayX)
            int hw_idx = (y + GROUP_DELAY_Y) * TEST_WIDTH + (x + GROUP_DELAY_X);

            // Boundary check: ensure we don't read past the captured HW buffer
            if (hw_idx >= num_pixels) continue;

            uint8_t hw_val = hw_result[hw_idx];
            uint8_t sw_val = sw_result[sw_idx];

            if (hw_val != sw_val) {
                std::cout << "Error at (x=" << x << ", y=" << y << ") "
                          << "SW Idx: " << sw_idx << " HW Idx: " << hw_idx
                          << " Exp: " << (int)sw_val 
                          << " Got: " << (int)hw_val << std::endl;
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