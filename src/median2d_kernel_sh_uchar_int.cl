STRINGIFY(

__kernel void median2d_kernel_sh_uchar_int(
		int imgWidth,
        int imgWidthF,
		__global unsigned char* gInput,
		__global unsigned char* gOutput)
{

	// 1 thread calculates 1 component

	int row = get_global_id(1);
	int col = get_global_id(0);

	// 20x20x1 window
	__local unsigned char window[20][20];

	int rgb_offset = (get_group_id(1) * get_num_groups(0) + get_group_id(0)) % 3;
	int wg_offset =  (get_group_id(1) * get_local_size(0) * imgWidthF * 3) + (get_group_id(0) % 3 * get_local_size(0) + rgb_offset);
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
			window[win_row][win_col] = gInput[rd_offset];
		}
	}
	
	barrier(CLK_LOCAL_MEM_FENCE);

	// Need to check the WG size etc


}


)