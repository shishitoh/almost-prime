#include <vector>
#include <algorithm>

#include "sieve.hpp"

std::vector<int64_t> almprm2_2(const int8_t k, const int64_t n) {

    if (k == 0) [[unlikely]] return {1};

    const auto P = sieve(-(-n >> (k-1)));

    if (k == 1) [[unlikely]] return P;

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