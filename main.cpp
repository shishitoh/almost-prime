#include <iostream>
#include <ranges>
#include <algorithm>
#include <chrono>
#include <cstring>
#include <unistd.h>

#include "almprm.h"
#include "timer.h"

using f_almprm = std::vector<int64_t> (*)(const int8_t, const int64_t);

constexpr char STR_VERS[][8] = {"1", "2_1", "2_2", "2_3", "3_1", "3_2", "3_3"};
constexpr f_almprm FUNCTIONS[] = {almprm1, almprm2_1, almprm2_2, almprm2_3, almprm3_1, almprm3_2, almprm3_3};
constexpr int DEFAULT_IDX = std::ranges::size(FUNCTIONS)-1;

/* 文字列が全部数字かを見る */
bool str_isnum(char *cp) {

    for (; *cp; cp++) {

        if (!std::isdigit(*cp)) {
            return false;
        }
    }
    return true;
}

/* コマンドラインオプションが正しいか確認して、ついでに指定されている関数のversionを表すindexを返す */
int args_validation_check(int argc, char *argv[]) {

    int idx = -1;

    if (argc >= 3 && str_isnum(argv[1]) && str_isnum(argv[2])) {
        if (argc == 3) {

            idx = DEFAULT_IDX;

        } else if (argv[3][0] == '-') {

            for (std::size_t i = 0; i < std::ranges::size(FUNCTIONS); i++) {
                if (std::strcmp(argv[3]+1, STR_VERS[i]) == 0) {
                    idx = i;
                    break;
                }
            }
        }
    }

    return idx;
}

int main(int argc, char *argv[]) {

    const int idx = args_validation_check(argc, argv);
    if (idx < 0) {
        fprintf(stdout, "ERROR: unrecognized options.\n\n");
        for (int i = 1; i < argc; ++i) {
            fprintf(stdout, "%d-th option: \"%s\"\n", i, argv[i]);
        }
        return 0;
    }

    const f_almprm almprm = FUNCTIONS[idx];
    const char *func_string = STR_VERS[idx];

    const int8_t k = atoi(argv[1]);
    const int64_t n = atoll(argv[2]);

    constexpr int COUNT = 5;

    std::chrono::milliseconds ms = std::chrono::milliseconds(0);

    for (int i = 0; i < COUNT; ++i) {

        std::chrono::high_resolution_clock::duration time;

        const auto Pk = timer(&time, almprm, k, n);

        ms += std::chrono::duration_cast<std::chrono::milliseconds>(time);

        /*
        for (auto pk : Pk) {
            std::cout << pk << " ";
        }
        std::cout << std::endl;
        */

        sleep(1);
    }

    std::cout << "almprm" << func_string << "(" << (int)k << ", " << n << "): " << ms.count()/COUNT << " ms" << std::endl;
}