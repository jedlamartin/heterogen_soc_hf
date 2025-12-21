STRINGIFY(

	inline void compare_swap_uchar(unsigned char* window, unsigned int i, unsigned int j) {
		unsigned char w_min = min(window[i], window[j]);
		unsigned char w_max = max(window[i], window[j]);

		window[i] = w_min;
		window[j] = w_max;
	}

	inline void batcher5x5_uchar(unsigned char* w){
		// p = 1
		// k = 1
		compare_swap_uchar(w, 0, 1);
		compare_swap_uchar(w, 2, 3);
		compare_swap_uchar(w, 4, 5);
		compare_swap_uchar(w, 6, 7);
		compare_swap_uchar(w, 8, 9);
		compare_swap_uchar(w, 10, 11);
		compare_swap_uchar(w, 12, 13);
		compare_swap_uchar(w, 14, 15);
		compare_swap_uchar(w, 16, 17);
		compare_swap_uchar(w, 18, 19);
		compare_swap_uchar(w, 20, 21);
		compare_swap_uchar(w, 22, 23);

		// p = 2
		// k = 2
		compare_swap_uchar(w, 0, 2);
		compare_swap_uchar(w, 1, 3);
		compare_swap_uchar(w, 4, 6);
		compare_swap_uchar(w, 5, 7);
		compare_swap_uchar(w, 8, 10);
		compare_swap_uchar(w, 9, 11);
		compare_swap_uchar(w, 12, 14);
		compare_swap_uchar(w, 13, 15);
		compare_swap_uchar(w, 16, 18);
		compare_swap_uchar(w, 17, 19);
		compare_swap_uchar(w, 20, 22);
		compare_swap_uchar(w, 21, 23);
		// k = 1
		compare_swap_uchar(w, 1, 2);
		compare_swap_uchar(w, 5, 6);
		compare_swap_uchar(w, 9, 10);
		compare_swap_uchar(w, 13, 14);
		compare_swap_uchar(w, 17, 18);
		compare_swap_uchar(w, 21, 22);

		// p = 4
		// k = 4
		compare_swap_uchar(w, 0, 4);
		compare_swap_uchar(w, 1, 5);
		compare_swap_uchar(w, 2, 6);
		compare_swap_uchar(w, 3, 7);
		compare_swap_uchar(w, 8, 12);
		compare_swap_uchar(w, 9, 13);
		compare_swap_uchar(w, 10, 14);
		compare_swap_uchar(w, 11, 15);
		compare_swap_uchar(w, 16, 20);
		compare_swap_uchar(w, 17, 21);
		compare_swap_uchar(w, 18, 22);
		compare_swap_uchar(w, 19, 23);
		// k = 2
		compare_swap_uchar(w, 2, 4);
		compare_swap_uchar(w, 3, 5);
		compare_swap_uchar(w, 10, 12);
		compare_swap_uchar(w, 11, 13);
		compare_swap_uchar(w, 18, 20);
		compare_swap_uchar(w, 19, 21);
		// k = 1
		compare_swap_uchar(w, 1, 2);
		compare_swap_uchar(w, 3, 4);
		compare_swap_uchar(w, 5, 6);
		compare_swap_uchar(w, 9, 10);
		compare_swap_uchar(w, 11, 12);
		compare_swap_uchar(w, 13, 14);
		compare_swap_uchar(w, 17, 18);
		compare_swap_uchar(w, 19, 20);
		compare_swap_uchar(w, 21, 22);

		// p = 8
		// k = 8
		compare_swap_uchar(w, 0, 8);
		compare_swap_uchar(w, 1, 9);
		compare_swap_uchar(w, 2, 10);
		compare_swap_uchar(w, 3, 11);
		compare_swap_uchar(w, 4, 12);
		compare_swap_uchar(w, 5, 13);
		compare_swap_uchar(w, 6, 14);
		compare_swap_uchar(w, 7, 15);
		compare_swap_uchar(w, 16, 24);
		// k = 4
		compare_swap_uchar(w, 4, 8);
		compare_swap_uchar(w, 5, 9);
		compare_swap_uchar(w, 6, 10);
		compare_swap_uchar(w, 7, 11);
		compare_swap_uchar(w, 20, 24);
		// k = 2
		compare_swap_uchar(w, 2, 4);
		compare_swap_uchar(w, 3, 5);
		compare_swap_uchar(w, 6, 8);
		compare_swap_uchar(w, 7, 9);
		compare_swap_uchar(w, 10, 12);
		compare_swap_uchar(w, 11, 13);
		compare_swap_uchar(w, 18, 20);
		compare_swap_uchar(w, 19, 21);
		compare_swap_uchar(w, 22, 24);
		// k = 1
		compare_swap_uchar(w, 1, 2);
		compare_swap_uchar(w, 3, 4);
		compare_swap_uchar(w, 5, 6);
		compare_swap_uchar(w, 7, 8);
		compare_swap_uchar(w, 9, 10);
		compare_swap_uchar(w, 11, 12);
		compare_swap_uchar(w, 13, 14);
		compare_swap_uchar(w, 17, 18);
		compare_swap_uchar(w, 19, 20);
		compare_swap_uchar(w, 21, 22);
		compare_swap_uchar(w, 23, 24);

		// p = 16
		// k = 16
		compare_swap_uchar(w, 0, 16);
		compare_swap_uchar(w, 1, 17);
		compare_swap_uchar(w, 2, 18);
		compare_swap_uchar(w, 3, 19);
		compare_swap_uchar(w, 4, 20);
		compare_swap_uchar(w, 5, 21);
		compare_swap_uchar(w, 6, 22);
		compare_swap_uchar(w, 7, 23);
		compare_swap_uchar(w, 8, 24);
		// k = 8
		compare_swap_uchar(w, 8, 16);
		compare_swap_uchar(w, 9, 17);
		compare_swap_uchar(w, 10, 18);
		compare_swap_uchar(w, 11, 19);
		compare_swap_uchar(w, 12, 20);
		compare_swap_uchar(w, 13, 21);
		compare_swap_uchar(w, 14, 22);
		compare_swap_uchar(w, 15, 23);
		// k = 4
		compare_swap_uchar(w, 4, 8);
		compare_swap_uchar(w, 5, 9);
		compare_swap_uchar(w, 6, 10);
		compare_swap_uchar(w, 7, 11);
		compare_swap_uchar(w, 12, 16);
		compare_swap_uchar(w, 13, 17);
		compare_swap_uchar(w, 14, 18);
		compare_swap_uchar(w, 15, 19);
		compare_swap_uchar(w, 20, 24);
		// k = 2
		compare_swap_uchar(w, 2, 4);
		compare_swap_uchar(w, 3, 5);
		compare_swap_uchar(w, 6, 8);
		compare_swap_uchar(w, 7, 9);
		compare_swap_uchar(w, 10, 12);
		compare_swap_uchar(w, 11, 13);
		compare_swap_uchar(w, 14, 16);
		compare_swap_uchar(w, 15, 17);
		compare_swap_uchar(w, 18, 20);
		compare_swap_uchar(w, 19, 21);
		compare_swap_uchar(w, 22, 24);
		// k = 1
		compare_swap_uchar(w, 1, 2);
		compare_swap_uchar(w, 3, 4);
		compare_swap_uchar(w, 5, 6);
		compare_swap_uchar(w, 7, 8);
		compare_swap_uchar(w, 9, 10);
		compare_swap_uchar(w, 11, 12);
		compare_swap_uchar(w, 13, 14);
		compare_swap_uchar(w, 15, 16);
		compare_swap_uchar(w, 17, 18);
		compare_swap_uchar(w, 19, 20);
		compare_swap_uchar(w, 21, 22);
		compare_swap_uchar(w, 23, 24);

		// Sorting is complete. The median vector is at window[12].
	}
		
__kernel void median2d_kernel_gl(
		int imgWidth,
        int imgWidthF,
		__global unsigned char* gInput,
		__global unsigned char* gOutput)
{
	// 1 thread calculates 1 component

	int row = get_global_id(1);
	int col = get_global_id(0);
	
	//if (col >= imgWidth * 3 || row >= get_global_size(1)) return;

	unsigned char window[25] = {0};

	int src_offset = (row * imgWidthF * 3) + col;

	for(int i = 0; i < 5; ++i){
		for(int j = 0; j < 5; ++j){
			int rd_offset = src_offset + (i * imgWidthF * 3) + (j * 3);
			window[i * 5 + j] = gInput[rd_offset];
		}
	}

	batcher5x5_uchar(window);

	int wr_offset = (row * imgWidth * 3) + col;
	gOutput[wr_offset] = window[12];
}

	inline void compare_swap_uchar16(uchar16* window, unsigned int i, unsigned int j) {
		uchar16 w_min = min(window[i], window[j]);
		uchar16 w_max = max(window[i], window[j]);

		window[i] = w_min;
		window[j] = w_max;
	}

	inline void batcher5x5_uchar16(unsigned char* w){
		// p = 1
		// k = 1
		compare_swap_uchar16(w, 0, 1);
		compare_swap_uchar16(w, 2, 3);
		compare_swap_uchar16(w, 4, 5);
		compare_swap_uchar16(w, 6, 7);
		compare_swap_uchar16(w, 8, 9);
		compare_swap_uchar16(w, 10, 11);
		compare_swap_uchar16(w, 12, 13);
		compare_swap_uchar16(w, 14, 15);
		compare_swap_uchar16(w, 16, 17);
		compare_swap_uchar16(w, 18, 19);
		compare_swap_uchar16(w, 20, 21);
		compare_swap_uchar16(w, 22, 23);

		// p = 2
		// k = 2
		compare_swap_uchar16(w, 0, 2);
		compare_swap_uchar16(w, 1, 3);
		compare_swap_uchar16(w, 4, 6);
		compare_swap_uchar16(w, 5, 7);
		compare_swap_uchar16(w, 8, 10);
		compare_swap_uchar16(w, 9, 11);
		compare_swap_uchar16(w, 12, 14);
		compare_swap_uchar16(w, 13, 15);
		compare_swap_uchar16(w, 16, 18);
		compare_swap_uchar16(w, 17, 19);
		compare_swap_uchar16(w, 20, 22);
		compare_swap_uchar16(w, 21, 23);
		// k = 1
		compare_swap_uchar16(w, 1, 2);
		compare_swap_uchar16(w, 5, 6);
		compare_swap_uchar16(w, 9, 10);
		compare_swap_uchar16(w, 13, 14);
		compare_swap_uchar16(w, 17, 18);
		compare_swap_uchar16(w, 21, 22);

		// p = 4
		// k = 4
		compare_swap_uchar16(w, 0, 4);
		compare_swap_uchar16(w, 1, 5);
		compare_swap_uchar16(w, 2, 6);
		compare_swap_uchar16(w, 3, 7);
		compare_swap_uchar16(w, 8, 12);
		compare_swap_uchar16(w, 9, 13);
		compare_swap_uchar16(w, 10, 14);
		compare_swap_uchar16(w, 11, 15);
		compare_swap_uchar16(w, 16, 20);
		compare_swap_uchar16(w, 17, 21);
		compare_swap_uchar16(w, 18, 22);
		compare_swap_uchar16(w, 19, 23);
		// k = 2
		compare_swap_uchar16(w, 2, 4);
		compare_swap_uchar16(w, 3, 5);
		compare_swap_uchar16(w, 10, 12);
		compare_swap_uchar16(w, 11, 13);
		compare_swap_uchar16(w, 18, 20);
		compare_swap_uchar16(w, 19, 21);
		// k = 1
		compare_swap_uchar16(w, 1, 2);
		compare_swap_uchar16(w, 3, 4);
		compare_swap_uchar16(w, 5, 6);
		compare_swap_uchar16(w, 9, 10);
		compare_swap_uchar16(w, 11, 12);
		compare_swap_uchar16(w, 13, 14);
		compare_swap_uchar16(w, 17, 18);
		compare_swap_uchar16(w, 19, 20);
		compare_swap_uchar16(w, 21, 22);

		// p = 8
		// k = 8
		compare_swap_uchar16(w, 0, 8);
		compare_swap_uchar16(w, 1, 9);
		compare_swap_uchar16(w, 2, 10);
		compare_swap_uchar16(w, 3, 11);
		compare_swap_uchar16(w, 4, 12);
		compare_swap_uchar16(w, 5, 13);
		compare_swap_uchar16(w, 6, 14);
		compare_swap_uchar16(w, 7, 15);
		compare_swap_uchar16(w, 16, 24);
		// k = 4
		compare_swap_uchar16(w, 4, 8);
		compare_swap_uchar16(w, 5, 9);
		compare_swap_uchar16(w, 6, 10);
		compare_swap_uchar16(w, 7, 11);
		compare_swap_uchar16(w, 20, 24);
		// k = 2
		compare_swap_uchar16(w, 2, 4);
		compare_swap_uchar16(w, 3, 5);
		compare_swap_uchar16(w, 6, 8);
		compare_swap_uchar16(w, 7, 9);
		compare_swap_uchar16(w, 10, 12);
		compare_swap_uchar16(w, 11, 13);
		compare_swap_uchar16(w, 18, 20);
		compare_swap_uchar16(w, 19, 21);
		compare_swap_uchar16(w, 22, 24);
		// k = 1
		compare_swap_uchar16(w, 1, 2);
		compare_swap_uchar16(w, 3, 4);
		compare_swap_uchar16(w, 5, 6);
		compare_swap_uchar16(w, 7, 8);
		compare_swap_uchar16(w, 9, 10);
		compare_swap_uchar16(w, 11, 12);
		compare_swap_uchar16(w, 13, 14);
		compare_swap_uchar16(w, 17, 18);
		compare_swap_uchar16(w, 19, 20);
		compare_swap_uchar16(w, 21, 22);
		compare_swap_uchar16(w, 23, 24);

		// p = 16
		// k = 16
		compare_swap_uchar16(w, 0, 16);
		compare_swap_uchar16(w, 1, 17);
		compare_swap_uchar16(w, 2, 18);
		compare_swap_uchar16(w, 3, 19);
		compare_swap_uchar16(w, 4, 20);
		compare_swap_uchar16(w, 5, 21);
		compare_swap_uchar16(w, 6, 22);
		compare_swap_uchar16(w, 7, 23);
		compare_swap_uchar16(w, 8, 24);
		// k = 8
		compare_swap_uchar16(w, 8, 16);
		compare_swap_uchar16(w, 9, 17);
		compare_swap_uchar16(w, 10, 18);
		compare_swap_uchar16(w, 11, 19);
		compare_swap_uchar16(w, 12, 20);
		compare_swap_uchar16(w, 13, 21);
		compare_swap_uchar16(w, 14, 22);
		compare_swap_uchar16(w, 15, 23);
		// k = 4
		compare_swap_uchar16(w, 4, 8);
		compare_swap_uchar16(w, 5, 9);
		compare_swap_uchar16(w, 6, 10);
		compare_swap_uchar16(w, 7, 11);
		compare_swap_uchar16(w, 12, 16);
		compare_swap_uchar16(w, 13, 17);
		compare_swap_uchar16(w, 14, 18);
		compare_swap_uchar16(w, 15, 19);
		compare_swap_uchar16(w, 20, 24);
		// k = 2
		compare_swap_uchar16(w, 2, 4);
		compare_swap_uchar16(w, 3, 5);
		compare_swap_uchar16(w, 6, 8);
		compare_swap_uchar16(w, 7, 9);
		compare_swap_uchar16(w, 10, 12);
		compare_swap_uchar16(w, 11, 13);
		compare_swap_uchar16(w, 14, 16);
		compare_swap_uchar16(w, 15, 17);
		compare_swap_uchar16(w, 18, 20);
		compare_swap_uchar16(w, 19, 21);
		compare_swap_uchar16(w, 22, 24);
		// k = 1
		compare_swap_uchar16(w, 1, 2);
		compare_swap_uchar16(w, 3, 4);
		compare_swap_uchar16(w, 5, 6);
		compare_swap_uchar16(w, 7, 8);
		compare_swap_uchar16(w, 9, 10);
		compare_swap_uchar16(w, 11, 12);
		compare_swap_uchar16(w, 13, 14);
		compare_swap_uchar16(w, 15, 16);
		compare_swap_uchar16(w, 17, 18);
		compare_swap_uchar16(w, 19, 20);
		compare_swap_uchar16(w, 21, 22);
		compare_swap_uchar16(w, 23, 24);

		// Sorting is complete. The median vector is at window[12].
	}

__kernel void median2d_kernel_gl_16x(
		int imgWidth,
        int imgWidthF,
		__global uchar* gInput,
		__global uchar* gOutput
)
{
	// 1 thread calculates 16 components

	int row = get_global_id(1);
	int col = get_global_id(0);

	uchar16 window[25] = {0};

	int src_offset = (row * imgWidthF * 3) + (col * 16);

	for(int i = 0; i < 5; ++i){
		for(int j = 0; j < 5; ++j){
			int rd_offset = src_offset + (i * imgWidthF * 3) + (j * 3);
			window[i * 5 + j] = vload16(0, gInput + rd_offset);
		}
	}

	batcher5x5_uchar16(window);

	int wr_offset = (row * imgWidth * 3) + (col * 16);
	vstore16(window[12], 0, gOutput + wr_offset);

}



)