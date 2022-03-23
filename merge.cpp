#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

std::vector<int64_t> heap_merge(std::vector<std::vector<int64_t>> &VV) {

    size_t pa, is, k, VVsizes, VVsize;
    std::vector<int64_t> tmpV, MV;
    VVsizes = VVsize = VV.size();

    /* VVを1番目(0番目でなく)を根としてvectorのsizeでmin heapifyする */
    for (size_t i = VVsize>>1; i >= 1; --i) {
        pa = i;
        is = VV[pa].size();
        tmpV = std::move(VV[pa]);
        /* 左の子が存在 */
        while ((k=(pa<<1)) < VVsize) {
            if (k+1 < VVsizes && VV[k].size() > VV[k+1].size()) ++k;
            if (is <= VV[k].size()) break;
            VV[pa] = std::move(VV[k]);
            pa = k;
        }
        VV[pa] = std::move(tmpV);
    }
    /* 0番目のheapify(的なこと)をする */
    if (VV[0].size() > VV[1].size()) {
        tmpV = std::move(VV[0]);
        VV[0] = std::move(VV[1]);
        pa = 1;
        is = tmpV.size();
        /* 左の子が存在 */
        while ((k=(pa<<1)) < VVsize) {
            if (k+1 < VVsizes && VV[k].size() > VV[k+1].size()) ++k;
            if (is <= VV[k].size()) break;
            VV[pa] = std::move(VV[k]);
            pa = k;
        }
        VV[pa] = std::move(tmpV);
    }
    /* heapified. */


    /* heapから2つpop、それをmergeしてまたheapにinsert
    VV.size()が2になるまで続ける */
    for (int i = 2; i < VVsize; ++i) {

        MV.resize(VV[0].size()+VV[1].size());

        std::merge(VV[0].begin(), VV[0].end(),
                   VV[1].begin(), VV[1].end(), MV.begin());

        pa = 1;
        is = VV[VVsizes-1].size();
        tmpV = std::move(VV[VVsizes-1]);
        --VVsizes;
        VV.pop_back();
        /* 左の子が存在 */
        while ((k=(pa<<1)) < VVsizes) {
            if (k+1 < VVsizes && VV[k].size() > VV[k+1].size()) ++k;
            if (is <= VV[k].size()) break;
            VV[pa] = std::move(VV[k]);
            pa = k;
        }
        VV[pa] = std::move(tmpV);

        if (MV.size() > VV[1].size()) {
            VV[0] = std::move(VV[1]);
            pa = 1;
            is = MV.size();
            /* 左の子が存在 */
            while ((k=(pa<<1)) < VVsizes) {
                if (k+1 < VVsizes && VV[k].size() > VV[k+1].size()) ++k;
                if (is <= VV[k].size()) break;
                VV[pa] = std::move(VV[k]);
                pa = k;
            }
            VV[pa] = std::move(MV);
        } else {
            VV[0] = std::move(MV);
        }
    }

    MV.resize(VV[0].size()+VV[1].size());
    std::merge(VV[0].begin(), VV[0].end(),
               VV[1].begin(), VV[1].end(), MV.begin());

    return MV;
}

void recursive_inplace_merge(std::vector<int64_t> &V,
                     const std::vector<size_t> &separr,
                     const size_t start, const size_t last) {

    const size_t m = (separr[start] + separr[last]) >> 1;
    size_t k = *std::ranges::partition_point(std::ranges::iota_view(start, last),
                                             [&m, &separr](const int a) -> const bool {
                                                 return separr[a] < m;
                                             });
    k = (m-separr[k-1] < separr[k]-m) ? k-1 : k;

    if (k-start > 1) {
        recursive_inplace_merge(V, separr, start, k);
    }
    if (last-k > 1) {
        recursive_inplace_merge(V, separr, k, last);
    }
    std::inplace_merge(V.begin()+separr[start], V.begin()+separr[k], V.begin()+separr[last]);
}