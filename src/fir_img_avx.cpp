#ifdef __amd64__

#include <array>

#include <stdint.h>

#include <omp.h>

#include <emmintrin.h>
#include <nmmintrin.h>
#include <immintrin.h>

constexpr uint32_t WIN_HEIGHT = 5;
constexpr uint32_t WIN_LENGTH = 5;

inline void compare_swap(__m256i* window, uint32_t i, uint32_t j) {
    __m256i w_min = _mm256_min_epu8(window[i], window[j]);
    __m256i w_max = _mm256_max_epu8(window[i], window[j]);
    
    window[i] = w_min;
    window[j] = w_max;
}

 void batcher_sort_5x5(__m256i* w) {
    // Get the underlying pointer to the start of the __m256i array

    // The 25-element Batcher network (105 comparisons) is unrolled.
    
    // ---------------------------------------------------------------
    // 5-Way Merge: Stage 1 (Total: 12 comparisons)
    // ---------------------------------------------------------------
    compare_swap(w, 0, 1);  compare_swap(w, 3, 4);  compare_swap(w, 6, 7);
    compare_swap(w, 9, 10); compare_swap(w, 12, 13); compare_swap(w, 15, 16);
    compare_swap(w, 18, 19); compare_swap(w, 21, 22);
    
    compare_swap(w, 1, 2);  compare_swap(w, 4, 5);  compare_swap(w, 7, 8);
    compare_swap(w, 10, 11); compare_swap(w, 13, 14); compare_swap(w, 16, 17);
    compare_swap(w, 19, 20); compare_swap(w, 22, 23); compare_swap(w, 2, 3);
    
    // ---------------------------------------------------------------
    // 5-Way Merge: Stage 2 (Total: 25 comparisons)
    // ---------------------------------------------------------------
    compare_swap(w, 0, 3);  compare_swap(w, 1, 4);  compare_swap(w, 2, 5);
    compare_swap(w, 6, 9);  compare_swap(w, 7, 10); compare_swap(w, 8, 11);
    compare_swap(w, 12, 15); compare_swap(w, 13, 16); compare_swap(w, 14, 17);
    compare_swap(w, 18, 21); compare_swap(w, 19, 22); compare_swap(w, 20, 23);
    
    compare_swap(w, 3, 6);  compare_swap(w, 4, 7);  compare_swap(w, 5, 8);
    compare_swap(w, 9, 12); compare_swap(w, 10, 13); compare_swap(w, 11, 14);
    compare_swap(w, 15, 18); compare_swap(w, 16, 19); compare_swap(w, 17, 20);
    compare_swap(w, 21, 24);

    compare_swap(w, 6, 12); compare_swap(w, 7, 13); compare_swap(w, 8, 14);
    compare_swap(w, 10, 15); compare_swap(w, 11, 16);
    compare_swap(w, 12, 18); compare_swap(w, 13, 19); compare_swap(w, 14, 20);

    // ---------------------------------------------------------------
    // 5-Way Merge: Stage 3 (Total: 28 comparisons)
    // ---------------------------------------------------------------
    compare_swap(w, 0, 12); compare_swap(w, 1, 13); compare_swap(w, 2, 14);
    compare_swap(w, 3, 15); compare_swap(w, 4, 16); compare_swap(w, 5, 17);
    compare_swap(w, 6, 18); compare_swap(w, 7, 19); compare_swap(w, 8, 20);
    compare_swap(w, 9, 21); compare_swap(w, 10, 22); compare_swap(w, 11, 23);
    compare_swap(w, 12, 24);

    compare_swap(w, 1, 6);  compare_swap(w, 2, 7);  compare_swap(w, 3, 8);
    compare_swap(w, 4, 9);  compare_swap(w, 5, 10); compare_swap(w, 11, 18);
    compare_swap(w, 12, 19); compare_swap(w, 13, 20); compare_swap(w, 14, 21);
    compare_swap(w, 15, 22); compare_swap(w, 16, 23);

    compare_swap(w, 6, 11); compare_swap(w, 7, 12); compare_swap(w, 8, 13);
    compare_swap(w, 9, 14); compare_swap(w, 10, 15);

    // ---------------------------------------------------------------
    // Final Merge: Stage 4 (Total: 40 comparisons)
    // ---------------------------------------------------------------
    compare_swap(w, 0, 6);  compare_swap(w, 1, 7);  compare_swap(w, 2, 8);
    compare_swap(w, 3, 9);  compare_swap(w, 4, 10); compare_swap(w, 5, 11);
    compare_swap(w, 12, 18); compare_swap(w, 13, 19); compare_swap(w, 14, 20);
    compare_swap(w, 15, 21); compare_swap(w, 16, 22); compare_swap(w, 17, 23);

    compare_swap(w, 1, 3);  compare_swap(w, 2, 4);  compare_swap(w, 5, 7);
    compare_swap(w, 6, 8);  compare_swap(w, 9, 11); compare_swap(w, 10, 12);
    compare_swap(w, 13, 15); compare_swap(w, 14, 16); compare_swap(w, 17, 19);
    compare_swap(w, 18, 20); compare_swap(w, 21, 23);

    compare_swap(w, 0, 2);  compare_swap(w, 3, 5);  compare_swap(w, 4, 6);
    compare_swap(w, 7, 9);  compare_swap(w, 8, 10); compare_swap(w, 11, 13);
    compare_swap(w, 14, 16); compare_swap(w, 15, 17); compare_swap(w, 18, 20);
    compare_swap(w, 19, 21); compare_swap(w, 22, 24);

    compare_swap(w, 1, 2);  compare_swap(w, 3, 4);  compare_swap(w, 5, 6);
    compare_swap(w, 7, 8);  compare_swap(w, 9, 10); compare_swap(w, 11, 12);
    compare_swap(w, 13, 14); compare_swap(w, 15, 16); compare_swap(w, 17, 18);
    compare_swap(w, 19, 20); compare_swap(w, 21, 22); compare_swap(w, 23, 24);

    // Sorting is complete. The median vector is at window[12].
} 



 /* void batcher_sort_5x5(__m256i* window) {
  // ---------------------------------------------------------------
  // Sorting Network: Batcher odd-even merge sort for 25 elements  |
  // ---------------------------------------------------------------

  __m256i w_min, w_max;

  // Stage 1: 0<->1  2<->3  4<->5  ...
  for (uint32_t i = 0; i + 1 < WIN_HEIGHT * WIN_LENGTH; i += 2) {
    w_min = _mm256_min_epu8(window[i], window[i + 1]);
    w_max = _mm256_max_epu8(window[i], window[i + 1]);

    window[i] = w_min;
    window[i + 1] = w_max;
  }

  // Stage 2: 0<->2 1<->3  4<->6 5<->7 ...
  for (uint32_t i = 0; i < WIN_HEIGHT * WIN_LENGTH; i += 4) {
#pragma unroll
    for (uint32_t j = i; j < i + 2 && j + 2 < WIN_HEIGHT * WIN_LENGTH; ++j) {
      w_min = _mm256_min_epu8(window[j], window[j + 2]);
      w_max = _mm256_max_epu8(window[j], window[j + 2]);

      window[j] = w_min;
      window[j + 2] = w_max;
    }
  }

  // Stage 3: 1<->2  5<->6  9<->10 ...
  for (uint32_t i = 1; i + 1 < WIN_HEIGHT * WIN_LENGTH; i += 4) {
    w_min = _mm256_min_epu8(window[i], window[i + 1]);
    w_max = _mm256_max_epu8(window[i], window[i + 1]);

    window[i] = w_min;
    window[i + 1] = w_max;
  }

  // Stage 4: 0<->4 1<->5 2<->6 3<->7  8<->12 9<->13 ...
  for (uint32_t i = 0; i < WIN_HEIGHT * WIN_LENGTH; i += 8) {
#pragma unroll
    for (uint32_t j = i; j < i + 4 && j + 4 < WIN_HEIGHT * WIN_LENGTH; ++j) {
      w_min = _mm256_min_epu8(window[j], window[j + 4]);
      w_max = _mm256_max_epu8(window[j], window[j + 4]);

      window[j] = w_min;
      window[j + 4] = w_max;
    }
  }

  // Stage 5: 2<->4 3<->5 10<->12 11<->13 ...
  for (uint32_t i = 2; i < WIN_HEIGHT * WIN_LENGTH; i += 8) {
#pragma unroll
    for (uint32_t j = i; j < i + 2 && j + 2 < WIN_HEIGHT * WIN_LENGTH; ++j) {
      w_min = _mm256_min_epu8(window[j], window[j + 2]);
      w_max = _mm256_max_epu8(window[j], window[j + 2]);

      window[j] = w_min;
      window[j + 2] = w_max;
    }
  }

  // Stage 6: 1<->2 3<->4 5<->6 7<->8 9<->10 11<->12 13<->14 ...
  for (uint32_t i = 1; i < WIN_HEIGHT * WIN_LENGTH; i += 8) {
#pragma unroll
    for (uint32_t j = i; j < i + 6 && j + 1 < WIN_HEIGHT * WIN_LENGTH; j += 2) {
      w_min = _mm256_min_epu8(window[j], window[j + 1]);
      w_max = _mm256_max_epu8(window[j], window[j + 1]);

      window[j] = w_min;
      window[j + 1] = w_max;
    }
  }

  // Stage 7: 0<->8 1<->9 2<->10 3<->11 ...
  for (uint32_t i = 0; i < WIN_HEIGHT * WIN_LENGTH; i += 16) {
#pragma unroll
    for (uint32_t j = i; j < i + 8 && j + 8 < WIN_HEIGHT * WIN_LENGTH; ++j) {
      w_min = _mm256_min_epu8(window[j], window[j + 8]);
      w_max = _mm256_max_epu8(window[j], window[j + 8]);

      window[j] = w_min;
      window[j + 8] = w_max;
    }
  }

  // Stage 8: 4<->8 5<->9 6<->10 7<->11  20<->24 21<->25 ...
  for (uint32_t i = 4; i < WIN_HEIGHT * WIN_LENGTH; i += 16) {
#pragma unroll
    for (uint32_t j = i; j < i + 4 && j + 4 < WIN_HEIGHT * WIN_LENGTH; ++j) {
      w_min = _mm256_min_epu8(window[j], window[j + 4]);
      w_max = _mm256_max_epu8(window[j], window[j + 4]);

      window[j] = w_min;
      window[j + 4] = w_max;
    }
  }

  // Stage 9: 2<->4 3<->5 6<->8 7<->9 ...
  for (uint32_t i = 2; i < WIN_HEIGHT * WIN_LENGTH; i += 8) {
#pragma unroll
    for (uint32_t j = i; j < i + 2 && j + 2 < WIN_HEIGHT * WIN_LENGTH; ++j) {
      w_min = _mm256_min_epu8(window[j], window[j + 2]);
      w_max = _mm256_max_epu8(window[j], window[j + 2]);

      window[j] = w_min;
      window[j + 2] = w_max;
    }
  }

  // Stage 10: 0<->16 1<->17 2<->18 ...
  for (uint32_t i = 0; i + 16 < WIN_HEIGHT * WIN_LENGTH; ++i) {
    w_min = _mm256_min_epu8(window[i], window[i + 16]);
    w_max = _mm256_max_epu8(window[i], window[i + 16]);

    window[i] = w_min;
    window[i + 16] = w_max;
  }

  // Stage 11: 8<->16 9<->17 10<->18 ...
  for (uint32_t i = 8; i + 8 < WIN_HEIGHT * WIN_LENGTH; ++i) {
    w_min = _mm256_min_epu8(window[i], window[i + 8]);
    w_max = _mm256_max_epu8(window[i], window[i + 8]);

    window[i] = w_min;
    window[i + 8] = w_max;
  }

  // Stage 12: 4<->8 5<->9 6<->10 7<->11  12<->16 13<->17 ...
  for (uint32_t i = 4; i < WIN_HEIGHT * WIN_LENGTH; i += 8) {
#pragma unroll
    for (uint32_t j = i; j < i + 4 && j + 4 < WIN_HEIGHT * WIN_LENGTH; ++j) {
      w_min = _mm256_min_epu8(window[j], window[j + 4]);
      w_max = _mm256_max_epu8(window[j], window[j + 4]);

      window[j] = w_min;
      window[j + 4] = w_max;
    }
  }

  // Stage 13: 2<->4 3<->5 6<->8 7<->9 ...
  for (uint32_t i = 2; i < WIN_HEIGHT * WIN_LENGTH; i += 4) {
#pragma unroll
    for (uint32_t j = i; j < i + 2 && j + 2 < WIN_HEIGHT * WIN_LENGTH; ++j) {
      w_min = _mm256_min_epu8(window[j], window[j + 2]);
      w_max = _mm256_max_epu8(window[j], window[j + 2]);

      window[j] = w_min;
      window[j + 2] = w_max;
    }
  }

  // Stage 14: 1<->2 3<->4 5<->6 ...
  for (uint32_t i = 1; i + 1 < WIN_HEIGHT * WIN_LENGTH; i += 2) {
    w_min = _mm256_min_epu8(window[i], window[i + 1]);
    w_max = _mm256_max_epu8(window[i], window[i + 1]);

    window[i] = w_min;
    window[i + 1] = w_max;
  }

  // ---------------------------------------------------------------
  // End of 32-element Batcher odd-even mergesort network          |
  // ---------------------------------------------------------------
} */
void median2d_avx_uload(int32_t imgHeight, int32_t imgWidth, int32_t imgWidthF, uint8_t *imgSrcExt, uint8_t *imgDst){

	#pragma omp parallel for
	for(int32_t row = 0; row < imgHeight; ++row){
		for(int32_t col = 0; col < imgWidth * 3; col += 32){
			__m256i window[WIN_LENGTH * WIN_HEIGHT] = {};
			
			// Load the window: 256 bit => 32 * uint8_t => 10 * rgb r g
			for (uint32_t i = 0; i < WIN_HEIGHT; ++i) {
				for (uint32_t j = 0; j < WIN_LENGTH; ++j) {
				window[i * WIN_LENGTH + j] =
					_mm256_loadu_si256(reinterpret_cast<const __m256i*>(imgSrcExt + (row + i) * imgWidthF * 3 + col + j * 3));
				}
			}

			batcher_sort_5x5(window);

			_mm256_storeu_si256(reinterpret_cast<__m256i*> (imgDst + row * imgWidth * 3 + col), window[12]);
		}
	}


}

#endif
