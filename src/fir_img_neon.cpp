#ifdef __aarch64__

#include <arm_neon.h>
#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <array>

constexpr uint32_t WIN_HEIGHT = 5;
constexpr uint32_t WIN_LENGTH = 5;

void batcher_sort_5x5(std::array<uint8x16_t, WIN_LENGTH * WIN_HEIGHT> &window) {
  // --- Sorting Network: Batcher odd-even merge sort for 32 elements ---
  uint8x16_t w_min, w_max;

  // Stage 1: 0<->1  2<->3  4<->5  ...
  for (uint32_t i = 0; i + 1 < WIN_HEIGHT * WIN_LENGTH; i += 2) {
    w_min = vminq_u8(window[i], window[i + 1]);
    w_max = vmaxq_u8(window[i], window[i + 1]);

    window[i] = w_min;
    window[i + 1] = w_max;
  }

  // Stage 2: 0<->2 1<->3  4<->6 5<->7 ...
  for (uint32_t i = 0; i < WIN_HEIGHT * WIN_LENGTH; i += 4) {
#pragma unroll
    for (uint32_t j = i; j < i + 2 && j + 2 < WIN_HEIGHT * WIN_LENGTH; ++j) {
      w_min = vminq_u8(window[j], window[j + 2]);
      w_max = vmaxq_u8(window[j], window[j + 2]);

      window[j] = w_min;
      window[j + 2] = w_max;
    }
  }

  // Stage 3: 1<->2  5<->6  9<->10 ...
  for (uint32_t i = 1; i + 1 < WIN_HEIGHT * WIN_LENGTH; i += 4) {
    w_min = vminq_u8(window[i], window[i + 1]);
    w_max = vmaxq_u8(window[i], window[i + 1]);

    window[i] = w_min;
    window[i + 1] = w_max;
  }

  // Stage 4: 0<->4 1<->5 2<->6 3<->7  8<->12 9<->13 ...
  for (uint32_t i = 0; i < WIN_HEIGHT * WIN_LENGTH; i += 8) {
#pragma unroll
    for (uint32_t j = i; j < i + 4 && j + 4 < WIN_HEIGHT * WIN_LENGTH; ++j) {
      w_min = vminq_u8(window[j], window[j + 4]);
      w_max = vmaxq_u8(window[j], window[j + 4]);

      window[j] = w_min;
      window[j + 4] = w_max;
    }
  }

  // Stage 5: 2<->4 3<->5 10<->12 11<->13 ...
  for (uint32_t i = 2; i < WIN_HEIGHT * WIN_LENGTH; i += 8) {
#pragma unroll
    for (uint32_t j = i; j < i + 2 && j + 2 < WIN_HEIGHT * WIN_LENGTH; ++j) {
      w_min = vminq_u8(window[j], window[j + 2]);
      w_max = vmaxq_u8(window[j], window[j + 2]);

      window[j] = w_min;
      window[j + 2] = w_max;
    }
  }

  // Stage 6: 1<->2 3<->4 5<->6 7<->8 9<->10 11<->12 13<->14 ...
  for (uint32_t i = 1; i < WIN_HEIGHT * WIN_LENGTH; i += 8) {
#pragma unroll
    for (uint32_t j = i; j < i + 6 && j + 1 < WIN_HEIGHT * WIN_LENGTH; j += 2) {
      w_min = vminq_u8(window[j], window[j + 1]);
      w_max = vmaxq_u8(window[j], window[j + 1]);

      window[j] = w_min;
      window[j + 1] = w_max;
    }
  }

  // Stage 7: 0<->8 1<->9 2<->10 3<->11 ...
  for (uint32_t i = 0; i < WIN_HEIGHT * WIN_LENGTH; i += 16) {
#pragma unroll
    for (uint32_t j = i; j < i + 8 && j + 8 < WIN_HEIGHT * WIN_LENGTH; ++j) {
      w_min = vminq_u8(window[j], window[j + 8]);
      w_max = vmaxq_u8(window[j], window[j + 8]);

      window[j] = w_min;
      window[j + 8] = w_max;
    }
  }

  // Stage 8: 4<->8 5<->9 6<->10 7<->11  20<->24 21<->25 ...
  for (uint32_t i = 4; i < WIN_HEIGHT * WIN_LENGTH; i += 16) {
#pragma unroll
    for (uint32_t j = i; j < i + 4 && j + 4 < WIN_HEIGHT * WIN_LENGTH; ++j) {
      w_min = vminq_u8(window[j], window[j + 4]);
      w_max = vmaxq_u8(window[j], window[j + 4]);

      window[j] = w_min;
      window[j + 4] = w_max;
    }
  }

  // Stage 9: 2<->4 3<->5 6<->8 7<->9 ...
  for (uint32_t i = 2; i < WIN_HEIGHT * WIN_LENGTH; i += 8) {
#pragma unroll
    for (uint32_t j = i; j < i + 2 && j + 2 < WIN_HEIGHT * WIN_LENGTH; ++j) {
      w_min = vminq_u8(window[j], window[j + 2]);
      w_max = vmaxq_u8(window[j], window[j + 2]);

      window[j] = w_min;
      window[j + 2] = w_max;
    }
  }

  // Stage 10: 0<->16 1<->17 2<->18 ...
  for (uint32_t i = 0; i + 16 < WIN_HEIGHT * WIN_LENGTH; ++i) {
    w_min = vminq_u8(window[i], window[i + 16]);
    w_max = vmaxq_u8(window[i], window[i + 16]);

    window[i] = w_min;
    window[i + 16] = w_max;
  }

  // Stage 11: 8<->16 9<->17 10<->18 ...
  for (uint32_t i = 8; i + 8 < WIN_HEIGHT * WIN_LENGTH; ++i) {
    w_min = vminq_u8(window[i], window[i + 8]);
    w_max = vmaxq_u8(window[i], window[i + 8]);

    window[i] = w_min;
    window[i + 8] = w_max;
  }

  // Stage 12: 4<->8 5<->9 6<->10 7<->11  12<->16 13<->17 ...
  for (uint32_t i = 4; i < WIN_HEIGHT * WIN_LENGTH; i += 8) {
#pragma unroll
    for (uint32_t j = i; j < i + 4 && j + 4 < WIN_HEIGHT * WIN_LENGTH; ++j) {
      w_min = vminq_u8(window[j], window[j + 4]);
      w_max = vmaxq_u8(window[j], window[j + 4]);

      window[j] = w_min;
      window[j + 4] = w_max;
    }
  }

  // Stage 13: 2<->4 3<->5 6<->8 7<->9 ...
  for (uint32_t i = 2; i < WIN_HEIGHT * WIN_LENGTH; i += 4) {
#pragma unroll
    for (uint32_t j = i; j < i + 2 && j + 2 < WIN_HEIGHT * WIN_LENGTH; ++j) {
      w_min = vminq_u8(window[j], window[j + 2]);
      w_max = vmaxq_u8(window[j], window[j + 2]);

      window[j] = w_min;
      window[j + 2] = w_max;
    }
  }

  // Stage 14: 1<->2 3<->4 5<->6 ...
  for (uint32_t i = 1; i + 1 < WIN_HEIGHT * WIN_LENGTH; i += 2) {
    w_min = vminq_u8(window[i], window[i + 1]);
    w_max = vmaxq_u8(window[i], window[i + 1]);

    window[i] = w_min;
    window[i + 1] = w_max;
  }

  // ---------------------------------------------------------------
  // End of 32-element Batcher odd-even mergesort network
  // ---------------------------------------------------------------
}

void median2d_neon_uload(int32_t imgHeight, int32_t imgWidth, int32_t imgWidthF,
                         uint8_t *imgSrcExt, uint8_t *imgDst) {
#pragma omp parallel for
  for (uint32_t row = 0; row < imgHeight; ++row) {
    for (uint32_t col = 0; col < (imgWidth * 3); col += 16) {
      std::array<uint8x16_t, WIN_LENGTH * WIN_HEIGHT> window;

      // Load window
      for (uint32_t i = 0; i < WIN_HEIGHT; ++i) {
        for (uint32_t j = 0; j < WIN_LENGTH; ++j) {
          window[i * WIN_LENGTH + j] =
              vld1q_u8(imgSrcExt + (row + i) * imgWidthF * 3 + col + j * 3);
        }
      }

      batcher_sort_5x5(window);

      // Store median value (13th element in sorted 25 elements)
      vst1q_u8(imgDst + row * imgWidth * 3 + col, window[13]);
    }
  }
}

void median2d_neon_sh(int32_t imgHeight, int32_t imgWidth, int32_t imgWidthF,
                      uint8_t *imgSrcExt, uint8_t *imgDst) {
  for (size_t row = 0; row < imgHeight; ++row) {
    for (size_t col = 0; col < imgWidth; ++col) {
    }
  }
}

#endif
