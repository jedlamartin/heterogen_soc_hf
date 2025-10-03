#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <omp.h>

constexpr size_t M_WIDTH = 5;
constexpr size_t M_HEIGHT = 5;

void batcher_merge_rgb(uint8_t* elements, size_t first, size_t last){
    size_t n = last - first + 1;

    if(n <= 1) return;

    size_t m = 1;
    while (m < n) m <<= 1;
    m >>= 1;

    for(size_t i=first; i + m <= last; ++i){
        // r
        if(elements[i * 3] < elements[(i + m) * 3]){
            uint8_t tmp = elements[i * 3];
            elements[i * 3] = elements[(i + m) * 3];
            elements[(i + m) * 3] = tmp;
        }
        // g
        if(elements[i * 3 + 1] < elements[(i + m) * 3  + 1]){
            uint8_t tmp = elements[i * 3 + 1];
            elements[i * 3 + 1] = elements[(i + m) * 3 + 1];
            elements[(i + m) * 3 + 1] = tmp;
        }
        // b
        if(elements[i * 3 + 2] < elements[(i + m) * 3 + 2]){
            uint8_t tmp = elements[i * 3 + 2];
            elements[i * 3 + 2] = elements[(i + m) * 3 + 2];
            elements[(i + m) * 3 + 2] = tmp;
        }
    }
    batcher_merge_rgb(elements, first, first + m - 1);
    batcher_merge_rgb(elements, first + m, last);

}

void bacher_sort_rgb(uint8_t* elements, size_t first, size_t last){
    size_t n = last - first + 1;

    if(n <= 1) return;
    
    size_t mid = first + n / 2;
    bacher_sort_rgb(elements, first, mid - 1);
    bacher_sort_rgb(elements, mid, last);

    batcher_merge_rgb(elements, first, last);
}

void median2d_c(int imgHeight, int imgWidth, int imgWidthF, uint8_t *imgSrcExt, uint8_t *imgDst) {
    #pragma omp parallel for
    for(int row = 0; row < imgHeight; ++row){
        for(int col = 0; col < imgWidth; ++col){
            uint8_t buffer [M_HEIGHT * M_WIDTH * 3] = {0};
            for(size_t frow = 0; frow < M_HEIGHT; ++frow){
                for(size_t fcol = 0; fcol < M_WIDTH; ++fcol){
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
            bacher_sort_rgb(buffer, 0, M_HEIGHT * M_WIDTH - 1);
            imgDst[(row * imgWidth + col) * 3] = buffer[(M_HEIGHT * M_WIDTH) / 2 * 3];
            imgDst[(row * imgWidth + col) * 3 + 1] = buffer[(M_HEIGHT * M_WIDTH) / 2 * 3 + 1];
            imgDst[(row * imgWidth + col) * 3 + 2] = buffer[(M_HEIGHT * M_WIDTH) / 2 * 3 + 2];
        }
    }
}

