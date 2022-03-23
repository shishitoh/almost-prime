#include <cstdint>
#include <cmath>
#include <vector>
#include <bit>

#include "sieve.hpp"

class Eratosthenes {

    std::vector<uint8_t> i_flags; // init
    std::vector<uint8_t> s_flags; // segmented
    std::vector<uint64_t> p_idxs;
    static constexpr uint64_t SEGMENT_SIZE = 2 * 1024 * 1024; // 2MB

    void init_flags(const int64_t);
    void init_pidxs();
    void segmented_sieve(const int64_t n);

public:
    Eratosthenes(const int64_t n)
    {
        init_flags(n);
        init_pidxs();
    }

    ~Eratosthenes() = default;


};

void Eratosthenes::init_flags(const int64_t n) {
    i_flags = flag_sieve(std::ceil(std::sqrt(n)));
}

void Eratosthenes::init_pidxs() {

    uint64_t size = 0;
    uint8_t flag;

    for (auto flag : i_flags) {
        size += std::popcount(flag);
    }

    p_idxs.resize(size);

    auto p_iter = p_idxs.begin();
    for (int64_t i = 0; i < i_flags.size(); ++i) {
        for (uint8_t flag = i_flags[i]; flag; flag &= flag-1) {
            *(p_iter++) = (i << 3) | std::countr_zero(flag);
        }
    }
}


