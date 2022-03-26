#include <vector>
#include <algorithm>

std::vector<int64_t> almprm1(const int8_t k, const int64_t n) {

    std::vector<std::vector<int64_t>> P(k+1);
    std::vector<int64_t> Pk;

    for (int64_t i = 1; i < n; ++i) {
        for (int64_t j = 0; j <= k; ++j) {
            if (std::ranges::any_of(P[j], [i](const int64_t x) noexcept {return i%x == 0;})) {
                continue;
            }
            P[j].push_back(i);
            break;
        }
    }

    Pk = std::move(P[k]);

    return Pk;
}