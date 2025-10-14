#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>

constexpr size_t M_WIDTH = 5;
constexpr size_t M_HEIGHT = 5;

#ifdef RECURSIVE
void batcher_merge_rgb(uint8_t *elements, size_t first, size_t last) {
  size_t n = last - first + 1;

  if (n <= 1)
    return;

  size_t m = 1;
  while (m < n)
    m <<= 1;
  m >>= 1;

  for (size_t i = first; i + m <= last; ++i) {
    // r
    if (elements[i * 3] < elements[(i + m) * 3]) {
      uint8_t tmp = elements[i * 3];
      elements[i * 3] = elements[(i + m) * 3];
      elements[(i + m) * 3] = tmp;
    }
    // g
    if (elements[i * 3 + 1] < elements[(i + m) * 3 + 1]) {
      uint8_t tmp = elements[i * 3 + 1];
      elements[i * 3 + 1] = elements[(i + m) * 3 + 1];
      elements[(i + m) * 3 + 1] = tmp;
    }
    // b
    if (elements[i * 3 + 2] < elements[(i + m) * 3 + 2]) {
      uint8_t tmp = elements[i * 3 + 2];
      elements[i * 3 + 2] = elements[(i + m) * 3 + 2];
      elements[(i + m) * 3 + 2] = tmp;
    }
  }
  batcher_merge_rgb(elements, first, first + m - 1);
  batcher_merge_rgb(elements, first + m, last);
}

void batcher_sort_5x5(uint8_t *elements, size_t first = 0,
                      size_t last = M_HEIGHT * M_WIDTH - 1) {
  size_t n = last - first + 1;

  if (n <= 1)
    return;

  size_t mid = first + n / 2;
  bacher_sort_rgb(elements, first, mid - 1);
  bacher_sort_rgb(elements, mid, last);

  batcher_merge_rgb(elements, first, last);
}
#else
inline void compare_swap(uint8_t *window, uint32_t i, uint32_t j) {
  uint8_t w_min = std::min(window[i], window[j]);
  uint8_t w_max = std::max(window[i], window[j]);

  window[i] = w_min;
  window[j] = w_max;
}

void batcher_sort_5x5(uint8_t *w) {
  // Get the underlying pointer to the start of the __m256i array

  // The 25-element Batcher network (105 comparisons) is unrolled.

  // ---------------------------------------------------------------
  // 5-Way Merge: Stage 1 (Total: 12 comparisons)
  // ---------------------------------------------------------------
  for (int i = 0; i < 3; i++) {

    compare_swap(w, 0 * 3 + i, 1 * 3 + i);
    compare_swap(w, 3 * 3 + i, 4 * 3 + i);
    compare_swap(w, 6 * 3 + i, 7 * 3 + i);
    compare_swap(w, 9 * 3 + i, 10 * 3 + i);
    compare_swap(w, 12 * 3 + i, 13 * 3 + i);
    compare_swap(w, 15 * 3 + i, 16 * 3 + i);
    compare_swap(w, 18 * 3 + i, 19 * 3 + i);
    compare_swap(w, 21 * 3 + i, 22 * 3 + i);

    compare_swap(w, 1 * 3 + i, 2 * 3 + i);
    compare_swap(w, 4 * 3 + i, 5 * 3 + i);
    compare_swap(w, 7 * 3 + i, 8 * 3 + i);
    compare_swap(w, 10 * 3 + i, 11 * 3 + i);
    compare_swap(w, 13 * 3 + i, 14 * 3 + i);
    compare_swap(w, 16 * 3 + i, 17 * 3 + i);
    compare_swap(w, 19 * 3 + i, 20 * 3 + i);
    compare_swap(w, 22 * 3 + i, 23 * 3 + i);
    compare_swap(w, 2 * 3 + i, 3 * 3 + i);

    // ---------------------------------------------------------------
    // 5-Way Merge: Stage 2 (Total: 25 comparisons)
    // ---------------------------------------------------------------
    compare_swap(w, 0 * 3 + i, 3 * 3 + i);
    compare_swap(w, 1 * 3 + i, 4 * 3 + i);
    compare_swap(w, 2 * 3 + i, 5 * 3 + i);
    compare_swap(w, 6 * 3 + i, 9 * 3 + i);
    compare_swap(w, 7 * 3 + i, 10 * 3 + i);
    compare_swap(w, 8 * 3 + i, 11 * 3 + i);
    compare_swap(w, 12 * 3 + i, 15 * 3 + i);
    compare_swap(w, 13 * 3 + i, 16 * 3 + i);
    compare_swap(w, 14 * 3 + i, 17 * 3 + i);
    compare_swap(w, 18 * 3 + i, 21 * 3 + i);
    compare_swap(w, 19 * 3 + i, 22 * 3 + i);
    compare_swap(w, 20 * 3 + i, 23 * 3 + i);

    compare_swap(w, 3 * 3 + i, 6 * 3 + i);
    compare_swap(w, 4 * 3 + i, 7 * 3 + i);
    compare_swap(w, 5 * 3 + i, 8 * 3 + i);
    compare_swap(w, 9 * 3 + i, 12 * 3 + i);
    compare_swap(w, 10 * 3 + i, 13 * 3 + i);
    compare_swap(w, 11 * 3 + i, 14 * 3 + i);
    compare_swap(w, 15 * 3 + i, 18 * 3 + i);
    compare_swap(w, 16 * 3 + i, 19 * 3 + i);
    compare_swap(w, 17 * 3 + i, 20 * 3 + i);
    compare_swap(w, 21 * 3 + i, 24 * 3 + i);

    compare_swap(w, 6 * 3 + i, 12 * 3 + i);
    compare_swap(w, 7 * 3 + i, 13 * 3 + i);
    compare_swap(w, 8 * 3 + i, 14 * 3 + i);
    compare_swap(w, 10 * 3 + i, 15 * 3 + i);
    compare_swap(w, 11 * 3 + i, 16 * 3 + i);
    compare_swap(w, 12 * 3 + i, 18 * 3 + i);
    compare_swap(w, 13 * 3 + i, 19 * 3 + i);
    compare_swap(w, 14 * 3 + i, 20 * 3 + i);

    // ---------------------------------------------------------------
    // 5-Way Merge: Stage 3 (Total: 28 comparisons)
    // ---------------------------------------------------------------
    compare_swap(w, 0 * 3 + i, 12 * 3 + i);
    compare_swap(w, 1 * 3 + i, 13 * 3 + i);
    compare_swap(w, 2 * 3 + i, 14 * 3 + i);
    compare_swap(w, 3 * 3 + i, 15 * 3 + i);
    compare_swap(w, 4 * 3 + i, 16 * 3 + i);
    compare_swap(w, 5 * 3 + i, 17 * 3 + i);
    compare_swap(w, 6 * 3 + i, 18 * 3 + i);
    compare_swap(w, 7 * 3 + i, 19 * 3 + i);
    compare_swap(w, 8 * 3 + i, 20 * 3 + i);
    compare_swap(w, 9 * 3 + i, 21 * 3 + i);
    compare_swap(w, 10 * 3 + i, 22 * 3 + i);
    compare_swap(w, 11 * 3 + i, 23 * 3 + i);
    compare_swap(w, 12 * 3 + i, 24 * 3 + i);

    compare_swap(w, 1 * 3 + i, 6 * 3 + i);
    compare_swap(w, 2 * 3 + i, 7 * 3 + i);
    compare_swap(w, 3 * 3 + i, 8 * 3 + i);
    compare_swap(w, 4 * 3 + i, 9 * 3 + i);
    compare_swap(w, 5 * 3 + i, 10 * 3 + i);
    compare_swap(w, 11 * 3 + i, 18 * 3 + i);
    compare_swap(w, 12 * 3 + i, 19 * 3 + i);
    compare_swap(w, 13 * 3 + i, 20 * 3 + i);
    compare_swap(w, 14 * 3 + i, 21 * 3 + i);
    compare_swap(w, 15 * 3 + i, 22 * 3 + i);
    compare_swap(w, 16 * 3 + i, 23 * 3 + i);

    compare_swap(w, 6 * 3 + i, 11 * 3 + i);
    compare_swap(w, 7 * 3 + i, 12 * 3 + i);
    compare_swap(w, 8 * 3 + i, 13 * 3 + i);
    compare_swap(w, 9 * 3 + i, 14 * 3 + i);
    compare_swap(w, 10 * 3 + i, 15 * 3 + i);

    // ---------------------------------------------------------------
    // Final Merge: Stage 4 (Total: 40 comparisons)
    // ---------------------------------------------------------------
    compare_swap(w, 0 * 3 + i, 6 * 3 + i);
    compare_swap(w, 1 * 3 + i, 7 * 3 + i);
    compare_swap(w, 2 * 3 + i, 8 * 3 + i);
    compare_swap(w, 3 * 3 + i, 9 * 3 + i);
    compare_swap(w, 4 * 3 + i, 10 * 3 + i);
    compare_swap(w, 5 * 3 + i, 11 * 3 + i);
    compare_swap(w, 12 * 3 + i, 18 * 3 + i);
    compare_swap(w, 13 * 3 + i, 19 * 3 + i);
    compare_swap(w, 14 * 3 + i, 20 * 3 + i);
    compare_swap(w, 15 * 3 + i, 21 * 3 + i);
    compare_swap(w, 16 * 3 + i, 22 * 3 + i);
    compare_swap(w, 17 * 3 + i, 23 * 3 + i);

    compare_swap(w, 1 * 3 + i, 3 * 3 + i);
    compare_swap(w, 2 * 3 + i, 4 * 3 + i);
    compare_swap(w, 5 * 3 + i, 7 * 3 + i);
    compare_swap(w, 6 * 3 + i, 8 * 3 + i);
    compare_swap(w, 9 * 3 + i, 11 * 3 + i);
    compare_swap(w, 10 * 3 + i, 12 * 3 + i);
    compare_swap(w, 13 * 3 + i, 15 * 3 + i);
    compare_swap(w, 14 * 3 + i, 16 * 3 + i);
    compare_swap(w, 17 * 3 + i, 19 * 3 + i);
    compare_swap(w, 18 * 3 + i, 20 * 3 + i);
    compare_swap(w, 21 * 3 + i, 23 * 3 + i);

    compare_swap(w, 0 * 3 + i, 2 * 3 + i);
    compare_swap(w, 3 * 3 + i, 5 * 3 + i);
    compare_swap(w, 4 * 3 + i, 6 * 3 + i);
    compare_swap(w, 7 * 3 + i, 9 * 3 + i);
    compare_swap(w, 8 * 3 + i, 10 * 3 + i);
    compare_swap(w, 11 * 3 + i, 13 * 3 + i);
    compare_swap(w, 14 * 3 + i, 16 * 3 + i);
    compare_swap(w, 15 * 3 + i, 17 * 3 + i);
    compare_swap(w, 18 * 3 + i, 20 * 3 + i);
    compare_swap(w, 19 * 3 + i, 21 * 3 + i);
    compare_swap(w, 22 * 3 + i, 24 * 3 + i);

    compare_swap(w, 1 * 3 + i, 2 * 3 + i);
    compare_swap(w, 3 * 3 + i, 4 * 3 + i);
    compare_swap(w, 5 * 3 + i, 6 * 3 + i);
    compare_swap(w, 7 * 3 + i, 8 * 3 + i);
    compare_swap(w, 9 * 3 + i, 10 * 3 + i);
    compare_swap(w, 11 * 3 + i, 12 * 3 + i);
    compare_swap(w, 13 * 3 + i, 14 * 3 + i);
    compare_swap(w, 15 * 3 + i, 16 * 3 + i);
    compare_swap(w, 17 * 3 + i, 18 * 3 + i);
    compare_swap(w, 19 * 3 + i, 20 * 3 + i);
    compare_swap(w, 21 * 3 + i, 22 * 3 + i);
    compare_swap(w, 23 * 3 + i, 24 * 3 + i);

    // Sorting is complete. The median vector is at window[12].
  }
}
#endif

void median2d_c(int32_t imgHeight, int32_t imgWidth, int32_t imgWidthF,
                uint8_t *imgSrcExt, uint8_t *imgDst) {
#pragma omp parallel for
  for (int row = 0; row < imgHeight; ++row) {
    for (int col = 0; col < imgWidth; ++col) {
      uint8_t buffer[M_HEIGHT * M_WIDTH * 3] = {0};
      for (size_t frow = 0; frow < M_HEIGHT; ++frow) {
        for (size_t fcol = 0; fcol < M_WIDTH; ++fcol) {
          // r
          buffer[(frow * M_WIDTH + fcol) * 3] =
              imgSrcExt[((row + frow) * imgWidthF + col + fcol) * 3];

          // g
          buffer[(frow * M_WIDTH + fcol) * 3 + 1] =
              imgSrcExt[((row + frow) * imgWidthF + col + fcol) * 3 + 1];

          // b
          buffer[(frow * M_WIDTH + fcol) * 3 + 2] =
              imgSrcExt[((row + frow) * imgWidthF + col + fcol) * 3 + 2];
        }
      }
      batcher_sort_5x5(buffer);
      imgDst[(row * imgWidth + col) * 3] = buffer[(M_HEIGHT * M_WIDTH) / 2 * 3];
      imgDst[(row * imgWidth + col) * 3 + 1] =
          buffer[(M_HEIGHT * M_WIDTH) / 2 * 3 + 1];
      imgDst[(row * imgWidth + col) * 3 + 2] =
          buffer[(M_HEIGHT * M_WIDTH) / 2 * 3 + 2];
    }
  }
}
