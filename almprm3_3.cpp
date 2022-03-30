#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <cmath>

#include "sieve.h"
#include "merge.h"

void almprm_impl(const int8_t k, const int64_t n, const size_t minidx, const int64_t mulP,
                 const std::vector<int64_t> &P, std::vector<int64_t> &Pk, std::vector<size_t> &separr) {

    // std::cout <<"k: " << (int)k << ", minidx: " << minidx << ", mulP: " << mulP << std::endl;

    const size_t maxidx = *std::ranges::partition_point(std::ranges::iota_view(minidx, P.size()),
                                                        [&](const size_t x) -> bool {
                                                            return P[x] < std::ceil(std::pow((n+mulP-1)/mulP, 1.0/k));
                                                        });

    if (k == 1) {
        const size_t tmp = Pk.size();
        Pk.resize(tmp + maxidx - minidx);
        separr.push_back(Pk.size());
        auto Pk_iter = Pk.begin() + tmp;
        for (size_t i = minidx; i < maxidx; ++i) {
            // std::cout << mulP*P[i] << std::endl;
            *(Pk_iter++) = mulP * P[i];
        }
    } else {
        for (size_t i = minidx; i < maxidx; ++i) {
            almprm_impl(k-1, n, i, mulP*P[i], P, Pk, separr);
        }
    }
}

std::vector<int64_t> almprm3_3(const int8_t k, const int64_t n) {

    const auto P = sieve(-(-n >> (k-1)));

    std::vector<int64_t> Pk;
    std::vector<size_t> separr;

    almprm_impl(k, n, 0, 1, P, Pk, separr);

    recursive_inplace_merge(Pk, separr, 0, separr.size()-1);

    return Pk;
}