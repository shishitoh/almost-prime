#include <iostream>
#include <vector>
#include <algorithm>
#include <bit>
#include <chrono>

#include "sieve.hpp"

std::vector<int64_t> almprm2_3(const int8_t k, const int64_t n) {

    std::chrono::high_resolution_clock::time_point begin, end;
    std::chrono::milliseconds ms = std::chrono::milliseconds(0);

    int64_t p;
    const int64_t maxp = -(-n >> (k-1));
    bool  pcontinue = 1;

    begin = std::chrono::high_resolution_clock::now();
    std::vector<uint8_t> fP = flag_sieve(maxp);
    end = std::chrono::high_resolution_clock::now();

    ms = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);

    std::cout << "in sieve: " << ms.count() << " ms" << std::endl;

    if (k == 1) [[unlikely]] return to_primes(fP);

    const int64_t kp = 1 << k;
    std::vector<int8_t> PF(n-kp);

    for (auto p : {2, 3, 5}) {
        if (p >= maxp) [[unlikely]] {
            pcontinue = 0;
            break;
        }
        for (int64_t j = 1, r = p; r < n && j <= k+1; ++j, r *= p) {
            for (int64_t l = r - (kp-1)%r - 1; l < n-kp; l += r) {
                ++PF[l];
            }
        }
    }
    if (pcontinue) [[likely]] {
        for (int64_t i = 0; i < fP.size(); ++i) {
            for (uint8_t flag = fP[i]; flag; flag &= flag-1) {
                p = 30*i + D[std::countr_zero(flag)];
                for (int64_t j = 1, r = p; r < n && j <= k+1; ++j, r *= p) {
                    for (int64_t l = r - (kp-1)%r - 1; l < n-kp; l += r) {
                        ++PF[l];
                    }
                }
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