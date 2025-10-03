#ifdef __aarch64__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <omp.h>

#include <arm_neon.h>


void median2d_neon_uload(int32_t imgHeight, int32_t imgWidth, int32_t imgWidthF, uint8_t *imgSrcExt, uint8_t *imgDst)
{

	// Generate the vector-coefficients
	int16x8_t filter_laplace[25];
	for (int32_t i = 0; i < 25; i++)
	{
		filter_laplace[i] = vdupq_n_s16(int16_t(filter[i]));
	}


	for (int32_t row=0; row<imgHeight; row++)
	{
		for (int32_t col=0; col<(imgWidth*3); col=col+8)
		{
			int32_t rd_offset;
			uint8x8_t load_data;
			int16x8_t ext_data;
			int16x8_t coeff;
			int16x8_t accu;


		}
	}
}


void median2d_neon_sh(int32_t imgHeight, int32_t imgWidth, int32_t imgWidthF, uint8_t *imgSrcExt, uint8_t *imgDst)
{


	for (size_t row = 0; row < imgHeight; ++row) {
		for (size_t col = 0; col < imgWidth; ++col) {


		}
	}
}

#endif
