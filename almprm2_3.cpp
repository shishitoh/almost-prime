#include <iostream>
#include <vector>
#include <algorithm>
#include <bit>

#include "sieve.h"

std::vector<int64_t> almprm2_3(const int8_t k, const int64_t n) {

    if (k == 0) [[unlikely]] return {1};

    const int64_t kp = 1 << k;
    if (n <= kp) [[unlikely]] return {};

    int64_t p;
    const int64_t maxp = -(-n >> (k-1));

    std::vector<uint8_t> fP = flag_sieve(maxp);

    std::vector<int8_t> PF(n-kp);

    for (auto p : {2, 3, 5}) {
        if (p >= maxp) [[unlikely]] {
            break;
        }
        for (int64_t j = 1, r = p; r < n && j <= k+1; ++j, r *= p) {
            for (int64_t l = r - (kp-1)%r - 1; l < n-kp; l += r) {
                ++PF[l];
            }
        }
    }
    for (std::size_t i = 0; i < fP.size(); ++i) {
        for (uint8_t flag = fP[i]; flag; flag &= flag-1) {
            p = 30*i + D[std::countr_zero(flag)];
            for (int64_t j = 1, r = p; r < n && j <= k+1; ++j, r *= p) {
                for (int64_t l = r - (kp-1)%r - 1; l < n-kp; l += r) {
                    ++PF[l];
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