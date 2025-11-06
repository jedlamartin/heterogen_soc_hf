#ifdef __amd64__

    #include <emmintrin.h>
    #include <immintrin.h>
    #include <nmmintrin.h>
    #include <omp.h>
    #include <stdint.h>

    #include <array>

constexpr uint32_t WIN_HEIGHT = 5;
constexpr uint32_t WIN_LENGTH = 5;

inline void compare_swap(__m256i* window, uint32_t i, uint32_t j) {
    __m256i w_min = _mm256_min_epu8(window[i], window[j]);
    __m256i w_max = _mm256_max_epu8(window[i], window[j]);

    window[i] = w_min;
    window[j] = w_max;
}

void batcher_sort_5x5(__m256i* w) {
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

void median2d_avx_uload(int32_t imgHeight,
                        int32_t imgWidth,
                        int32_t imgWidthF,
                        uint8_t* imgSrcExt,
                        uint8_t* imgDst) {
    #pragma omp parallel for
    for(int32_t row = 0; row < imgHeight; ++row) {
      __m256i window[WIN_LENGTH * WIN_HEIGHT];
        for(int32_t col = 0; col < imgWidth * 3; col += 32) {
            // Load the window: 256 bit => 32 * uint8_t => 10 * rgb r g
            for(uint32_t i = 0; i < WIN_HEIGHT; ++i) {
                for(uint32_t j = 0; j < WIN_LENGTH; ++j) {
                    window[i * WIN_LENGTH + j] =
                        _mm256_loadu_si256(reinterpret_cast<const __m256i*>(
                            imgSrcExt + (row + i) * imgWidthF * 3 + col +
                            j * 3));
                }
            }

            batcher_sort_5x5(window);

            _mm256_storeu_si256(
                reinterpret_cast<__m256i*>(imgDst + row * imgWidth * 3 + col),
                window[12]);
        }
    }
}

#endif
