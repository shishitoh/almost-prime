#include <type_traits>
#include <functional>
#include <chrono>
#include <concepts>

template<typename Func, typename... Args>
std::invoke_result_t<Func, Args...>
timer(std::chrono::high_resolution_clock::duration *time, Func f, Args... args) {

    std::chrono::high_resolution_clock::time_point start, end;

    start = std::chrono::high_resolution_clock::now();
    auto ret = std::invoke(f, args...);
    end = std::chrono::high_resolution_clock::now();

    *time = end - start;

    return ret;
}