#include <vector>
#include <algorithm>

std::vector<int64_t> almprm2_1(const int8_t k, const int64_t n) {

    std::vector<int8_t> PF(n);

    for (int64_t i = 2; i < n; ++i) {
        if (PF[i] == 0) {
            for (int64_t j = 1, r = i; r < n && j <= k+1; ++j, r *= i) {
                for (int64_t l = r; l < n; l += r) {
                    ++PF[l];
                }
            }
        }
    }

    std::vector<int64_t> Pk(std::ranges::count(PF, k));
    auto Pk_iter = std::begin(Pk);
    for (int64_t j = 1; j < n; ++j) {
        if (PF[j] == k) {
            *(Pk_iter++) = j;
        }
    }

    return Pk;
}