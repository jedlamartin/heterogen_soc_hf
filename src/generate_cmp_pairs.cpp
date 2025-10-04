#include <cstddef>
#include <iostream>

constexpr size_t num_of_elements = 32;

int main() {
    for(size_t k = 2; k <= num_of_elements; k *= 2) {
        for(size_t j = k / 2; j > 0; j /= 2) {
            for(size_t i = 0; i < num_of_elements; i++) {
                size_t ixj = i ^ j;
                if(ixj > i) {
                    std::cout << '(' << i << ',' << ixj << ')' << std::endl;
                }
            }
        }
    }
    return 0;
}