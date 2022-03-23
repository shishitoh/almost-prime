#include <iostream>
#include <algorithm>
#include <chrono>
#include <unistd.h>

#include "almprm.hpp"

#define FUNC almprm2_1
#define FUNCSTR "almprm2_1"

int main() {

    std::chrono::high_resolution_clock::time_point begin, end;
    std::chrono::milliseconds ms = std::chrono::milliseconds(0);

    int k;
    int64_t n;

    std::cout << "k = ";
    std::cin >> k;
    std::cout << "n = ";
    std::cin >> n;

    constexpr int COUNT = 5;

    for (int i = 0; i < COUNT; ++i) {

        begin = std::chrono::high_resolution_clock::now();
        auto Pk = FUNC(k, n);
        end = std::chrono::high_resolution_clock::now();

        ms += std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);

        /*
        for (auto pk : Pk) {
            std::cout << pk << ' ';
        }
        std::cout << std::endl;
        */

        sleep(1);
    }

    std::cout << FUNCSTR << "(" << k << ", " << n << "): " << ms.count()/COUNT << " ms" << std::endl;
}