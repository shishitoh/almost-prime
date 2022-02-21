#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <cmath>
#include <chrono>

#include "sieve.hpp"
#include "merge.hpp"

std::vector<int64_t> almprm3_2(const int8_t k, const int64_t n) {

    const auto P = sieve(-(-n >> (k-1)));
    std::vector<size_t> PIs(k-1);
    size_t PIi;
    std::vector<int64_t>::iterator Pk_iter;

    if (k == 1) [[unlikely]] return P;

    int64_t Pmul = 1 << (k-1);

    std::vector<std::vector<int64_t>> Pks;
    std::vector<size_t> separr(0);

    const int64_t max = std::ceil(std::pow((long double)n, (long double)1/k));

    while (true) {
        size_t last = *std::ranges::partition_point(std::ranges::iota_view(PIs.back(), P.size()),
                                                    [&](const size_t x) -> const bool {
                                                        return P[x] * Pmul < n;
                                                    });
        if (PIs.back() < last) {
            Pks.emplace_back(last - PIs.back());
            Pk_iter = Pks.back().begin();
            for (size_t i = PIs.back(); i < last; ++i) {
                *(Pk_iter++) = Pmul * P[i];
            }
            PIs.back() += 1;
        } else {
            for (int i = k-3; i >= 0; --i) {
                if (PIs[i] == PIs.back()) {
                    continue;
                } else {
                    PIi = PIs[i]+1;
                    for (int j = i; j < k-1; ++j) {
                        PIs[j] = PIi;
                    }
                    break;
                }
            }
            if (max <= P[PIs[0]]) break;
        }

        Pmul = 1;
        for (int i = 0; i < k-1; ++i) {
            Pmul *= P[PIs[i]];
        }
    }

    return heap_merge(Pks);
}