#include <iostream>
#include <cmath>
#include <vector>
#include <ranges>
#include <algorithm>
#include <chrono>

#include "sieve.h"

std::vector<int64_t> almprm2_2(const int8_t k, const int64_t n) {

    std::chrono::high_resolution_clock::time_point begin, end;
    std::chrono::milliseconds ms = std::chrono::milliseconds(0);

    begin = std::chrono::high_resolution_clock::now();
    const auto P = sieve(-(-n >> (k-1)));
    end = std::chrono::high_resolution_clock::now();

    ms = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);

    std::cout << "in sieve: " << ms.count() << " ms" << std::endl;

    const int64_t kp = 1 << k;
    std::vector<int8_t> PF(n-kp);

    for (auto p : P) {
        for (int64_t j = 1, r = p; r < n && j <= k+1; ++j, r *= p) {
            for (int64_t l = r - (kp-1)%r - 1; l < n-kp; l += r) {
                ++PF[l];
            }
        }
    }

    std::vector<int64_t> Pk(std::ranges::count(PF, k));
    auto Pk_iter = std::begin(Pk);
    for (int64_t j = 0; j < n-kp; ++j) {
        if (PF[j] == k) {
            *(Pk_iter++) = j + kp;
        }
    }

    return Pk;
}