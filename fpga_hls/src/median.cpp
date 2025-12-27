#include <algorithm>
#include "types.h"

constexpr int BUF_L = 8192;

constexpr int WIN_H = 5;
constexpr int WIN_L = 5;

// From report 75ns/5ns
constexpr int PIXEL_DELAY = 15; 


inline void batcher5x5(uint8_ct* w);

void median2d_hw(uint8_ct* r_in, uint8_ct* g_in, uint8_ct* b_in, uint1_ct* hs_in, uint1_ct* vs_in, uint1_ct* de_in, uint8_ct* r_out, uint8_ct* g_out, uint8_ct* b_out, uint1_ct* hs_out, uint1_ct* vs_out, uint1_ct* de_out){
#pragma HLS INTERFACE mode=ap_none port=return

#pragma HLS INTERFACE mode=ap_none port=r_in
#pragma HLS INTERFACE mode=ap_none port=g_in
#pragma HLS INTERFACE mode=ap_none port=b_in
#pragma HLS INTERFACE mode=ap_none port=hs_in
#pragma HLS INTERFACE mode=ap_none port=vs_in
#pragma HLS INTERFACE mode=ap_none port=de_in

#pragma HLS INTERFACE mode=ap_none port=r_out
#pragma HLS INTERFACE mode=ap_none port=g_out
#pragma HLS INTERFACE mode=ap_none port=b_out
#pragma HLS INTERFACE mode=ap_none port=hs_out
#pragma HLS INTERFACE mode=ap_none port=vs_out
#pragma HLS INTERFACE mode=ap_none port=de_out

#pragma HLS PIPELINE II=1
    
    static uint8_ct line_buf[3][WIN_H - 1][BUF_L];
    #pragma HLS BIND_STORAGE variable=line_buf type=ram_2p
    #pragma HLS ARRAY_PARTITION variable=line_buf dim=1 type=complete
    #pragma HLS ARRAY_PARTITION variable=line_buf dim=2 type=complete
    
    uint8_ct cur_pixel[3];
    cur_pixel[0] = *r_in;
    cur_pixel[1] = *g_in;
    cur_pixel[2] = *b_in;

    // Variable to check edge of hs
    static uint1_ct hs_edge[2];
    hs_edge[0] = hs_edge[1];
    hs_edge[1] = *hs_in;
    
    // Current column of the frame - latest index of circular buffer
    static uint14_ct curr_col;
    if(hs_edge[0] == 0 && hs_edge[1] == 1){
        curr_col = 0;
    } else{
        curr_col++;
    }


    // Window to calculate the median value of
    static uint8_ct window[3][WIN_H][WIN_L];
    #pragma HLS ARRAY_PARTITION variable=window type=complete

    // Shifting the window left by 1 column every iteration. Delay: 1
    for(int rgb = 2; rgb >= 0; --rgb){
    #pragma HLS UNROLL
        for(int x = WIN_H - 1; x >= 0; --x){
            for(int y = 0; y < WIN_L - 1; ++y){
                window[rgb][x][y] = window[rgb][x][y + 1];
            }
        }
    }
    // Putting the new column in
    for(int rgb = 2; rgb >= 0; --rgb){
    #pragma HLS UNROLL
        // The new pixel
        window[rgb][WIN_H - 1][WIN_L - 1] = cur_pixel[rgb];
        for(int x = WIN_H - 1 - 1; x >= 0; --x){
            window[rgb][x][WIN_L - 1] = line_buf[rgb][x][curr_col];
        }
    }
        
    // Putting the new data in the buffer
    for(int rgb = 2; rgb >= 0; --rgb){
    #pragma HLS UNROLL
        for(int x = 0; x < WIN_H - 1 - 1; ++x){
            line_buf[rgb][x][curr_col] = line_buf[rgb][x + 1][curr_col];
        }
        line_buf[rgb][WIN_H - 1 - 1][curr_col] = cur_pixel[rgb];
    }
    
    // Copying the window to a temp vairable to be able to sort it
    uint8_ct window_cpy[3][WIN_H * WIN_L];
    #pragma HLS ARRAY_PARTITION variable=window_cpy dim=0 type=complete
    for(int rgb = 2; rgb >=0; --rgb){
    #pragma HLS UNROLL
        for(int x = WIN_H - 1; x >= 0; --x){
            for(int y = WIN_L - 1; y>=0; --y){
                window_cpy[rgb][x * WIN_H + y] = window[rgb][x][y];
            }
        }
    }
    batcher5x5(window_cpy[0]);
    batcher5x5(window_cpy[1]);
    batcher5x5(window_cpy[2]);
    
    *r_out = window_cpy[0][WIN_H * WIN_L / 2];
    *g_out = window_cpy[1][WIN_H * WIN_L / 2];
    *b_out = window_cpy[2][WIN_H * WIN_L / 2];


    // Delaying the control signals
    static uint1_ct de_dl[PIXEL_DELAY];
    static uint1_ct hs_dl[PIXEL_DELAY];
    static uint1_ct vs_dl[PIXEL_DELAY];

    *de_out = de_dl[0];
    *hs_out = hs_dl[0];
    *vs_out = vs_dl[0];

    for(int i = 0; i < PIXEL_DELAY; ++i){
    #pragma HLS UNROLL
        de_dl[i] = (i == PIXEL_DELAY - 1) ? *de_in : de_dl[i + 1];
        hs_dl[i] = (i == PIXEL_DELAY - 1) ? *hs_in : hs_dl[i + 1];
        vs_dl[i] = (i == PIXEL_DELAY - 1) ? *vs_in : vs_dl[i + 1];
    }
}

inline void compare_swap(uint8_ct* window, int i, int j) {
#pragma HLS INLINE
    uint8_ct w_min = std::min(window[i], window[j]);
    uint8_ct w_max = std::max(window[i], window[j]);

    window[i] = w_min;
    window[j] = w_max;
}

inline void batcher5x5(uint8_ct* w){
#pragma HLS INLINE
     // p = 1
    // k = 1
    compare_swap(w, 0, 1);
    compare_swap(w, 2, 3);
    compare_swap(w, 4, 5);
    compare_swap(w, 6, 7);
    compare_swap(w, 8, 9);
    compare_swap(w, 10, 11);
    compare_swap(w, 12, 13);
    compare_swap(w, 14, 15);
    compare_swap(w, 16, 17);
    compare_swap(w, 18, 19);
    compare_swap(w, 20, 21);
    compare_swap(w, 22, 23);

    // p = 2
    // k = 2
    compare_swap(w, 0, 2);
    compare_swap(w, 1, 3);
    compare_swap(w, 4, 6);
    compare_swap(w, 5, 7);
    compare_swap(w, 8, 10);
    compare_swap(w, 9, 11);
    compare_swap(w, 12, 14);
    compare_swap(w, 13, 15);
    compare_swap(w, 16, 18);
    compare_swap(w, 17, 19);
    compare_swap(w, 20, 22);
    compare_swap(w, 21, 23);
    // k = 1
    compare_swap(w, 1, 2);
    compare_swap(w, 5, 6);
    compare_swap(w, 9, 10);
    compare_swap(w, 13, 14);
    compare_swap(w, 17, 18);
    compare_swap(w, 21, 22);

    // p = 4
    // k = 4
    compare_swap(w, 0, 4);
    compare_swap(w, 1, 5);
    compare_swap(w, 2, 6);
    compare_swap(w, 3, 7);
    compare_swap(w, 8, 12);
    compare_swap(w, 9, 13);
    compare_swap(w, 10, 14);
    compare_swap(w, 11, 15);
    compare_swap(w, 16, 20);
    compare_swap(w, 17, 21);
    compare_swap(w, 18, 22);
    compare_swap(w, 19, 23);
    // k = 2
    compare_swap(w, 2, 4);
    compare_swap(w, 3, 5);
    compare_swap(w, 10, 12);
    compare_swap(w, 11, 13);
    compare_swap(w, 18, 20);
    compare_swap(w, 19, 21);
    // k = 1
    compare_swap(w, 1, 2);
    compare_swap(w, 3, 4);
    compare_swap(w, 5, 6);
    compare_swap(w, 9, 10);
    compare_swap(w, 11, 12);
    compare_swap(w, 13, 14);
    compare_swap(w, 17, 18);
    compare_swap(w, 19, 20);
    compare_swap(w, 21, 22);

    // p = 8
    // k = 8
    compare_swap(w, 0, 8);
    compare_swap(w, 1, 9);
    compare_swap(w, 2, 10);
    compare_swap(w, 3, 11);
    compare_swap(w, 4, 12);
    compare_swap(w, 5, 13);
    compare_swap(w, 6, 14);
    compare_swap(w, 7, 15);
    compare_swap(w, 16, 24);
    // k = 4
    compare_swap(w, 4, 8);
    compare_swap(w, 5, 9);
    compare_swap(w, 6, 10);
    compare_swap(w, 7, 11);
    compare_swap(w, 20, 24);
    // k = 2
    compare_swap(w, 2, 4);
    compare_swap(w, 3, 5);
    compare_swap(w, 6, 8);
    compare_swap(w, 7, 9);
    compare_swap(w, 10, 12);
    compare_swap(w, 11, 13);
    compare_swap(w, 18, 20);
    compare_swap(w, 19, 21);
    compare_swap(w, 22, 24);
    // k = 1
    compare_swap(w, 1, 2);
    compare_swap(w, 3, 4);
    compare_swap(w, 5, 6);
    compare_swap(w, 7, 8);
    compare_swap(w, 9, 10);
    compare_swap(w, 11, 12);
    compare_swap(w, 13, 14);
    compare_swap(w, 17, 18);
    compare_swap(w, 19, 20);
    compare_swap(w, 21, 22);
    compare_swap(w, 23, 24);

    // p = 16
    // k = 16
    compare_swap(w, 0, 16);
    compare_swap(w, 1, 17);
    compare_swap(w, 2, 18);
    compare_swap(w, 3, 19);
    compare_swap(w, 4, 20);
    compare_swap(w, 5, 21);
    compare_swap(w, 6, 22);
    compare_swap(w, 7, 23);
    compare_swap(w, 8, 24);
    // k = 8
    compare_swap(w, 8, 16);
    compare_swap(w, 9, 17);
    compare_swap(w, 10, 18);
    compare_swap(w, 11, 19);
    compare_swap(w, 12, 20);
    compare_swap(w, 13, 21);
    compare_swap(w, 14, 22);
    compare_swap(w, 15, 23);
    // k = 4
    compare_swap(w, 4, 8);
    compare_swap(w, 5, 9);
    compare_swap(w, 6, 10);
    compare_swap(w, 7, 11);
    compare_swap(w, 12, 16);
    compare_swap(w, 13, 17);
    compare_swap(w, 14, 18);
    compare_swap(w, 15, 19);
    compare_swap(w, 20, 24);
    // k = 2
    compare_swap(w, 2, 4);
    compare_swap(w, 3, 5);
    compare_swap(w, 6, 8);
    compare_swap(w, 7, 9);
    compare_swap(w, 10, 12);
    compare_swap(w, 11, 13);
    compare_swap(w, 14, 16);
    compare_swap(w, 15, 17);
    compare_swap(w, 18, 20);
    compare_swap(w, 19, 21);
    compare_swap(w, 22, 24);
    // k = 1
    compare_swap(w, 1, 2);
    compare_swap(w, 3, 4);
    compare_swap(w, 5, 6);
    compare_swap(w, 7, 8);
    compare_swap(w, 9, 10);
    compare_swap(w, 11, 12);
    compare_swap(w, 13, 14);
    compare_swap(w, 15, 16);
    compare_swap(w, 17, 18);
    compare_swap(w, 19, 20);
    compare_swap(w, 21, 22);
    compare_swap(w, 23, 24);

    // Sorting is complete. The median vector is at window[12].
}
