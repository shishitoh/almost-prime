#include <vector>

std::vector<int64_t> heap_merge(std::vector<std::vector<int64_t>> &);

void recursive_inplace_merge(std::vector<int64_t> &,
                     const std::vector<size_t> &,
                     const size_t, const size_t);