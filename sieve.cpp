#include <cmath>
#include <vector>
#include <bit>
#include <algorithm>

constexpr uint8_t D[8] = {1, 7, 11, 13, 17, 19, 23, 29};


// next of D
// constexpr uint8_t n_D[8] = {7, 11, 13, 17, 19, 23, 29, 31};


// difference of D
constexpr uint8_t d_D[8] = {6, 4, 2, 4, 2, 4, 6, 2};


// inverse_function of D
// const map<int int> i_D = {1:0, 7:1, 11:2, 13:3, 17:4, 19:5, 23:6, 29:7};


/* Dp_q = [[i*j/30 for i in D] for j in D] */
/* Dp_q[i][j] = (D[i] * D[j]) / 30 */
/*
constexpr uint8_t Dp_q[8][8] = {
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  1,  2,  3,  3,  4,  5,  6},
    { 0,  2,  4,  4,  6,  6,  8, 10},
    { 0,  3,  4,  5,  7,  8,  9, 12},
    { 0,  3,  6,  7,  9, 10, 13, 16},
    { 0,  4,  6,  8, 10, 12, 14, 18},
    { 0,  5,  8,  9, 13, 14, 17, 22},
    { 0,  6, 10, 12, 16, 18, 22, 28}
};
*/


/* D_q = [Dp_q[i][i] for i in range(8)] */
/* D_q[i] = Dp_q[i][i] = (D[i] * D[i]) / 30 */
constexpr uint8_t D_q[8] = {0, 1, 4, 5, 9, 12, 17, 28};


/* d_Dp_q = [[i*n_D[j]/30 - i*D[j]/30 for j in range(8)] for i in D] */
constexpr uint8_t d_Dp_q[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 1},
    {2, 2, 0, 2, 0, 2, 2, 1},
    {3, 1, 1, 2, 1, 1, 3, 1},
    {3, 3, 1, 2, 1, 3, 3, 1},
    {4, 2, 2, 2, 2, 2, 4, 1},
    {5, 3, 1, 4, 1, 3, 5, 1},
    {6, 4, 2, 4, 2, 4, 6, 1}
};


/* Dp_r = [[i*j%30 for i in D] for j in D] */
/* Dp_r[i][j] = (D[i] * D[j]) % 30 */
constexpr uint8_t Dp_r[8][8] = {
    {1,  7,  11, 13, 17, 19, 23, 29},
    {7,  19, 17, 1,  29, 13, 11, 23},
    {11, 17, 1,  23, 7,  29, 13, 19},
    {13, 1,  23, 19, 11, 7,  29, 17},
    {17, 29, 7,  11, 19, 23, 1,  13},
    {19, 13, 29, 7,  23, 1,  17, 11},
    {23, 11, 13, 29, 1,  17, 19, 7 },
    {29, 23, 19, 17, 13, 11, 7,  1 }
};


/* i_Dp_r = i_D[Dp_r] */
/*
const vector<vector<uint8_t>> i_Dp_r = {
    {0, 1, 2, 3, 4, 5, 6, 7},
    {1, 5, 4, 0, 7, 3, 2, 6},
    {2, 4, 0, 6, 1, 7, 3, 5},
    {3, 0, 6, 5, 2, 1, 7, 4},
    {4, 7, 1, 2, 5, 6, 0, 3},
    {5, 3, 7, 1, 6, 0, 4, 2},
    {6, 2, 3, 7, 0, 4, 5, 1},
    {7, 6, 5, 4, 3, 2, 1, 0}
};
*/


// bitmasks = 0xff - (1 << i_Dp_r)
constexpr uint8_t bitmasks[8][8] = {
    {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f},
    {0xfd, 0xdf, 0xef, 0xfe, 0x7f, 0xf7, 0xfb, 0xbf},
    {0xfb, 0xef, 0xfe, 0xbf, 0xfd, 0x7f, 0xf7, 0xdf},
    {0xf7, 0xfe, 0xbf, 0xdf, 0xfb, 0xfd, 0x7f, 0xef},
    {0xef, 0x7f, 0xfd, 0xfb, 0xdf, 0xbf, 0xfe, 0xf7},
    {0xdf, 0xf7, 0x7f, 0xfd, 0xbf, 0xfe, 0xef, 0xfb},
    {0xbf, 0xfb, 0xf7, 0x7f, 0xfe, 0xef, 0xdf, 0xfd},
    {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe}
};


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

            /* flagの最も右側に立っているビットの位置 */
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

std::vector<int64_t> to_primes(const std::vector<uint8_t> flags) {

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