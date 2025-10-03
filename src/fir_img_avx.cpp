#ifdef __amd64__

#include <stdint.h>

#include <omp.h>

#include <emmintrin.h>
#include <nmmintrin.h>
#include <immintrin.h>




void median2d_avx_uload(int32_t imgHeight, int32_t imgWidth, int32_t imgWidthF, uint8_t *imgSrcExt, uint8_t *imgDst)
{
	// Generate the vector-coefficients
	__m256i filter_laplace[25];
	for (int32_t i = 0; i < 25; i++)
	{
		//filter_laplace[i] = _mm256_set1_epi16((int16_t)(filter[i]));
	}

	#pragma omp parallel for
	for (int32_t row=0; row<imgHeight; row++)
	{
		int32_t wr_base = row*imgWidth*3;
		int32_t rd_base = row*imgWidthF*3;

		// step through all components in a line
		for (int32_t col=0; col<(imgWidth*3); col=col+16)
		{




		}
	}
}

#endif
