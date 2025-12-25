STRINGIFY(

inline void compare_swap_float(float* window, unsigned int i, unsigned int j) {
		float w_min = min(window[i], window[j]);
		float w_max = max(window[i], window[j]);

		window[i] = w_min;
		window[j] = w_max;
	}

inline void batcher5x5_float(float* w){
		// p = 1
		// k = 1
		compare_swap_float(w, 0, 1);
		compare_swap_float(w, 2, 3);
		compare_swap_float(w, 4, 5);
		compare_swap_float(w, 6, 7);
		compare_swap_float(w, 8, 9);
		compare_swap_float(w, 10, 11);
		compare_swap_float(w, 12, 13);
		compare_swap_float(w, 14, 15);
		compare_swap_float(w, 16, 17);
		compare_swap_float(w, 18, 19);
		compare_swap_float(w, 20, 21);
		compare_swap_float(w, 22, 23);

		// p = 2
		// k = 2
		compare_swap_float(w, 0, 2);
		compare_swap_float(w, 1, 3);
		compare_swap_float(w, 4, 6);
		compare_swap_float(w, 5, 7);
		compare_swap_float(w, 8, 10);
		compare_swap_float(w, 9, 11);
		compare_swap_float(w, 12, 14);
		compare_swap_float(w, 13, 15);
		compare_swap_float(w, 16, 18);
		compare_swap_float(w, 17, 19);
		compare_swap_float(w, 20, 22);
		compare_swap_float(w, 21, 23);
		// k = 1
		compare_swap_float(w, 1, 2);
		compare_swap_float(w, 5, 6);
		compare_swap_float(w, 9, 10);
		compare_swap_float(w, 13, 14);
		compare_swap_float(w, 17, 18);
		compare_swap_float(w, 21, 22);

		// p = 4
		// k = 4
		compare_swap_float(w, 0, 4);
		compare_swap_float(w, 1, 5);
		compare_swap_float(w, 2, 6);
		compare_swap_float(w, 3, 7);
		compare_swap_float(w, 8, 12);
		compare_swap_float(w, 9, 13);
		compare_swap_float(w, 10, 14);
		compare_swap_float(w, 11, 15);
		compare_swap_float(w, 16, 20);
		compare_swap_float(w, 17, 21);
		compare_swap_float(w, 18, 22);
		compare_swap_float(w, 19, 23);
		// k = 2
		compare_swap_float(w, 2, 4);
		compare_swap_float(w, 3, 5);
		compare_swap_float(w, 10, 12);
		compare_swap_float(w, 11, 13);
		compare_swap_float(w, 18, 20);
		compare_swap_float(w, 19, 21);
		// k = 1
		compare_swap_float(w, 1, 2);
		compare_swap_float(w, 3, 4);
		compare_swap_float(w, 5, 6);
		compare_swap_float(w, 9, 10);
		compare_swap_float(w, 11, 12);
		compare_swap_float(w, 13, 14);
		compare_swap_float(w, 17, 18);
		compare_swap_float(w, 19, 20);
		compare_swap_float(w, 21, 22);

		// p = 8
		// k = 8
		compare_swap_float(w, 0, 8);
		compare_swap_float(w, 1, 9);
		compare_swap_float(w, 2, 10);
		compare_swap_float(w, 3, 11);
		compare_swap_float(w, 4, 12);
		compare_swap_float(w, 5, 13);
		compare_swap_float(w, 6, 14);
		compare_swap_float(w, 7, 15);
		compare_swap_float(w, 16, 24);
		// k = 4
		compare_swap_float(w, 4, 8);
		compare_swap_float(w, 5, 9);
		compare_swap_float(w, 6, 10);
		compare_swap_float(w, 7, 11);
		compare_swap_float(w, 20, 24);
		// k = 2
		compare_swap_float(w, 2, 4);
		compare_swap_float(w, 3, 5);
		compare_swap_float(w, 6, 8);
		compare_swap_float(w, 7, 9);
		compare_swap_float(w, 10, 12);
		compare_swap_float(w, 11, 13);
		compare_swap_float(w, 18, 20);
		compare_swap_float(w, 19, 21);
		compare_swap_float(w, 22, 24);
		// k = 1
		compare_swap_float(w, 1, 2);
		compare_swap_float(w, 3, 4);
		compare_swap_float(w, 5, 6);
		compare_swap_float(w, 7, 8);
		compare_swap_float(w, 9, 10);
		compare_swap_float(w, 11, 12);
		compare_swap_float(w, 13, 14);
		compare_swap_float(w, 17, 18);
		compare_swap_float(w, 19, 20);
		compare_swap_float(w, 21, 22);
		compare_swap_float(w, 23, 24);

		// p = 16
		// k = 16
		compare_swap_float(w, 0, 16);
		compare_swap_float(w, 1, 17);
		compare_swap_float(w, 2, 18);
		compare_swap_float(w, 3, 19);
		compare_swap_float(w, 4, 20);
		compare_swap_float(w, 5, 21);
		compare_swap_float(w, 6, 22);
		compare_swap_float(w, 7, 23);
		compare_swap_float(w, 8, 24);
		// k = 8
		compare_swap_float(w, 8, 16);
		compare_swap_float(w, 9, 17);
		compare_swap_float(w, 10, 18);
		compare_swap_float(w, 11, 19);
		compare_swap_float(w, 12, 20);
		compare_swap_float(w, 13, 21);
		compare_swap_float(w, 14, 22);
		compare_swap_float(w, 15, 23);
		// k = 4
		compare_swap_float(w, 4, 8);
		compare_swap_float(w, 5, 9);
		compare_swap_float(w, 6, 10);
		compare_swap_float(w, 7, 11);
		compare_swap_float(w, 12, 16);
		compare_swap_float(w, 13, 17);
		compare_swap_float(w, 14, 18);
		compare_swap_float(w, 15, 19);
		compare_swap_float(w, 20, 24);
		// k = 2
		compare_swap_float(w, 2, 4);
		compare_swap_float(w, 3, 5);
		compare_swap_float(w, 6, 8);
		compare_swap_float(w, 7, 9);
		compare_swap_float(w, 10, 12);
		compare_swap_float(w, 11, 13);
		compare_swap_float(w, 14, 16);
		compare_swap_float(w, 15, 17);
		compare_swap_float(w, 18, 20);
		compare_swap_float(w, 19, 21);
		compare_swap_float(w, 22, 24);
		// k = 1
		compare_swap_float(w, 1, 2);
		compare_swap_float(w, 3, 4);
		compare_swap_float(w, 5, 6);
		compare_swap_float(w, 7, 8);
		compare_swap_float(w, 9, 10);
		compare_swap_float(w, 11, 12);
		compare_swap_float(w, 13, 14);
		compare_swap_float(w, 15, 16);
		compare_swap_float(w, 17, 18);
		compare_swap_float(w, 19, 20);
		compare_swap_float(w, 21, 22);
		compare_swap_float(w, 23, 24);

		// Sorting is complete. The median vector is at window[12].
	}



__kernel void median2d_kernel_sh_uchar_float(
		int imgWidth,
        int imgWidthF,
		__global unsigned char* gInput,
		__global unsigned char* gOutput)
{
	// 1 thread calculates 1 component

	int row = get_global_id(1);
	int col = get_global_id(0);

	// 20x20x1 window
	__local float data[20][20];

	int rgb_offset = (get_group_id(1) * get_num_groups(0) + get_group_id(0)) % 3;
	int wg_offset =  (get_group_id(1) * get_local_size(1) * imgWidthF * 3) + (get_group_id(0) / 3 * get_local_size(0) * 3 + rgb_offset);
	int loc_row = get_local_id(1);
	int loc_col = get_local_id(0);


	// 1 thread loads 2 bytes
	#pragma unroll
	for(int i = 0; i < 2; ++i){
		int win_idx = (loc_row * get_local_size(0)) + (loc_col) + i * get_local_size(1) * get_local_size(0);
		int win_row = win_idx / 20;
		int win_col = win_idx % 20;

		int rd_offset = wg_offset + (win_row * imgWidthF * 3) + (win_col * 3);

		if(win_row < 20 && win_col < 20){
			data[win_row][win_col] = (float)gInput[rd_offset];
		}
	}
	
	barrier(CLK_LOCAL_MEM_FENCE);

	float window[25] = {0};
	#pragma unroll
	for(int i = 0; i < 5; ++i){
		#pragma unroll
		for(int j = 0; j < 5; ++j){
			window[i * 5 + j] = data[loc_row + i][loc_col + j];
		}
	}

	batcher5x5_float(window);

	
	int wr_offset = (row * imgWidth * 3) + (get_group_id(0) / 3 * get_local_size(0) * 3 + loc_col * 3 + rgb_offset);
	gOutput[wr_offset] = (unsigned char) window[12];


}


)