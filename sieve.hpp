#include <cstdint>
#include <vector>

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


std::vector<uint8_t> flag_sieve(const int64_t);
std::vector<int64_t> to_primes(const std::vector<uint8_t>);
std::vector<int64_t> sieve(const int64_t);