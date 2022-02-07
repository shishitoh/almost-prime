#include <vector>
#include <algorithm>
#include "almprm.hpp"

std::vector<int64_t> almprm2(const int k, const int64_t n) {

    std::vector<unsigned char> PF(n, 0);
    std::vector<int64_t> Pk;

    for (int64_t i = 2; i < n; ++i) {
        if (PF[i] == 0) {
            int64_t r = 1;
            for (int64_t j = 1; j <= k+1; ++j) {
                r *= i;
                if (r >= n) break;
                for (int64_t l = r; l < n; l += r) {
                    ++PF[l];
                }
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