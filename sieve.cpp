#include <cmath>
#include <vector>
#include <bit>
#include <algorithm>

#include "sieve.h"

std::vector<uint8_t> flag_sieve(const int64_t n) {

    const int64_t size = (n-1)/30+1;
    std::vector<uint8_t> flags(size, 0xff);

    uint8_t idx_i1, idx_i2;
    const uint8_t *bitmask;
    int64_t G[8], G2[7], m;

    if (const uint8_t r = (n-1)%30 + 1; r <= 1)  flags[size-1] = 0b00000000;
    else if 					       (r <= 7)  flags[size-1] = 0b00000001;
    else if 					       (r <= 11) flags[size-1] = 0b00000011;
    else if 					       (r <= 13) flags[size-1] = 0b00000111;
    else if 					       (r <= 17) flags[size-1] = 0b00001111;
    else if 					       (r <= 19) flags[size-1] = 0b00011111;
    else if 					       (r <= 23) flags[size-1] = 0b00111111;
    else if 					       (r <= 29) flags[size-1] = 0b01111111;

    flags[0] -= 1;

    for (int64_t m1 = 0; m1 < std::floor((std::sqrt(n-1)/30)) + 1; ++m1) {

        /* flag &= flag-1 は立っている最下位ビットを0に変える */
        for(uint8_t flag = flags[m1]; flag; flag &= flag-1) {

            /* flagの最下位ビットの位置 */
            idx_i1 = idx_i2 = std::countr_zero(flag);
            m = 30*m1*m1 + 2*m1*D[idx_i1] + D_q[idx_i1];

            bitmask = bitmasks[idx_i1];

            /* 前計算 */
            G[0] = m1*d_D[0] + d_Dp_q[idx_i1][0];
            G[1] = m1*d_D[1] + d_Dp_q[idx_i1][1];
            G[2] = m1*d_D[2] + d_Dp_q[idx_i1][2];
            G[3] = m1*d_D[3] + d_Dp_q[idx_i1][3];
            G[4] = m1*d_D[4] + d_Dp_q[idx_i1][4];
            G[5] = m1*d_D[5] + d_Dp_q[idx_i1][5];
            G[6] = m1*d_D[6] + d_Dp_q[idx_i1][6];
            G[7] = m1*d_D[7] + d_Dp_q[idx_i1][7];
            G2[0] = G[0];
            G2[1] = G2[0] + G[1];
            G2[2] = G2[1] + G[2];
            G2[3] = G2[2] + G[3];
            G2[4] = G2[3] + G[4];
            G2[5] = G2[4] + G[5];
            G2[6] = G2[5] + G[6];

            /* ループアンローリング */
            while ( m < size && !(idx_i2 == 0)) { 
                flags[m] &= bitmask[idx_i2];
                m += G[idx_i2];
                idx_i2 = (idx_i2 + 1) & 7;
            }
            while (m + 28 * m1 + D[idx_i1] - 1 < size) {
                flags[m        ] &= bitmask[0];
                flags[m + G2[0]] &= bitmask[1];
                flags[m + G2[1]] &= bitmask[2];
                flags[m + G2[2]] &= bitmask[3];
                flags[m + G2[3]] &= bitmask[4];
                flags[m + G2[4]] &= bitmask[5];
                flags[m + G2[5]] &= bitmask[6];
                flags[m + G2[6]] &= bitmask[7];
                m += 30*m1 + D[idx_i1];
            }
            while (m < size) {
                flags[m] &= bitmask[idx_i2];
                m += G[idx_i2];
                idx_i2 = (idx_i2 + 1) & 7;
            }
        }
    }

    return flags;
}

std::vector<int64_t> to_primes(const std::vector<uint8_t> &flags) {

    int64_t count = 3;

    for (uint8_t flag : flags) {
        count += std::popcount(flag);
    }
    std::vector<int64_t> P(count);

    auto P_iter = std::begin(P);

    *(P_iter++) = 2;
    *(P_iter++) = 3;
    *(P_iter++) = 5;
    for (int64_t m = 0; uint8_t flag : flags) {
        while (flag) {
            *(P_iter++) = m + D[std::countr_zero(flag)];
            flag &= flag-1;
        }
        m += 30;
    }

    return P;
}

std::vector<int64_t> sieve(const int64_t n) {

    if 		(n < 2) [[unlikely]] return {};
    else if (n < 3) [[unlikely]] return {2};
    else if (n < 5) [[unlikely]] return {2, 3};
    else if (n < 7) [[unlikely]] return {2, 3, 5};

    const auto flags = flag_sieve(n);
    return to_primes(flags);
}