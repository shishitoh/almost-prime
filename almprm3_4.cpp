#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <cmath>

#include "sieve.h"
#include "merge.h"

/* iterator的な */
struct PP {
    int64_t cur;
    int64_t mul;
    std::vector<int64_t>::const_iterator P_iter;

    constexpr void next() noexcept {
        cur = *(++P_iter) * mul;
    }
};

constexpr bool operator<(const PP &Pa, const PP &Pb) noexcept {
    return Pa.cur < Pb.cur;
}
constexpr bool operator>(const PP &Pa, const PP &Pb) noexcept {
    return Pa.cur > Pb.cur;
}

template<typename T, std::size_t Root = 0>
void heapify(std::vector<T> &V, std::size_t n) {
    T tmp = std::move(V[n]);
    std::size_t k;
    constexpr int nRoot = 1 - Root;
    while ((k=(n<<1)+nRoot) < V.size()) {
        if (k+1 < V.size() && V[k] > V[k+1]) ++k;
        if (tmp < V[k]) break;
        V[n] = std::move(V[k]);
        n = k;
    }
    V[n] = std::move(tmp);
}

template<typename T, std::size_t Root = 0>
void make_heap(std::vector<T> &V) {
    for (int64_t n = ((V.size() + Root) >> 1) - 1; n >= (int64_t)Root; --n) {
        heapify<T, Root>(V, n);
    }
}

void almprm_impl(const int8_t k, const int64_t n, const std::size_t minidx, const int64_t mulP,
                 const std::vector<int64_t> &P, std::vector<PP> *PPvector, std::size_t *ptotal_size) {

    /* mul * pow(P[x], k) < n を満たす最大のxをmaxidxと定義する */
    const size_t maxidx = *std::ranges::partition_point(
        std::ranges::iota_view(minidx, P.size()),
        [&](const size_t x) -> bool {
            return P[x] < std::ceil(std::pow((n+mulP-1)/mulP, 1.0/k));
        }
    );

    if (k == 1) {
        PPvector->push_back(PP{mulP*P[minidx], mulP, P.begin()+minidx});
        *ptotal_size += maxidx-minidx;
    } else {
        for (size_t i = minidx; i < maxidx; ++i) {
            almprm_impl(k-1, n, i, mulP*P[i], P, PPvector, ptotal_size);
        }
    }
}

std::vector<int64_t> almprm3_4(const int8_t k, const int64_t n) {

    if (k == 0) [[unlikely]] return {1};

    auto P = sieve(-(-n >> (k-1)));
    P.push_back(-(-n >> (k-1))); // P.end()の中身を参照してしまうバグの応急処置

    std::size_t total_size = 0;
    std::vector<PP> PPvector(0);

    almprm_impl(k, n, 0, 1, P, &PPvector, &total_size);

    make_heap(PPvector);
    std::vector<int64_t> Pk(total_size);

    for (auto &pk : Pk) {
        pk = PPvector[0].cur;
        PPvector[0].next();
        heapify(PPvector, 0);
    }

    return Pk;
}
