#include <vector>
#include <algorithm>

#include "almprm.hpp"
#include "../product-of-primes/sieve2.h"

std::vector<int64_t> almprm2_2(const int k, const int64_t n) {

    auto P = sieve2<int64_t>((n >> (k-1)) + 1);

    std::vector<unsigned char> PF(n);
    std::vector<int64_t> Pk;

    for (auto p : P) {
        int64_t r = 1;
        for (int i = 1; i <= k+1; ++i) {
            r *= p;
            if (r >= n) break;
            for (int64_t j = r; j < n; j += r) {
                ++PF[j];
            }
        }
    }

    Pk.reserve(std::ranges::count(PF, k));
    for (int64_t i = 0; i < n; ++i) {
        if (PF[i] == k) {
            Pk.push_back(i);
        }
    }

    return Pk;
}