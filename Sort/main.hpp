#pragma once

#include <chrono>
#include "Sort.hpp"
#include "../Shared/Helpers.h"

typedef int32_t int_t;

namespace Sort {
    int_t* randomArray(int_t length) {
        auto result = new int_t[length];

        for (int_t i = 0; i < length; ++i) {
            result[i] = Helpers::random();
        }

        return result;
    }

    int main(int argc, char **argv) {
        Helpers::printsh("Сравнение скорости выполнения quickSort и insertionsSort");
        Helpers::prints("на массивах длиной от 0 до 100 [на примере int]");

        std::chrono::steady_clock::time_point start;
        std::chrono::steady_clock::time_point end;

        for (int_t n = 1; n <= 100; ++n) {
            auto arr = randomArray(n);
            auto copy = new int_t[n];

            std::copy(arr, arr + n, copy); 

            start = std::chrono::high_resolution_clock::now();
            quickSort(arr, arr + n, [](int a, int b) { return a < b; });
            end = std::chrono::high_resolution_clock::now();

            auto diff1 = end - start;

            start = std::chrono::high_resolution_clock::now();
            insertionsSort(copy, copy + n, [](int a, int b) { return a < b; });
            end = std::chrono::high_resolution_clock::now();

            auto diff2 = end - start;

            std::cout << diff1 << "          " << diff2 << std::endl;
        }

        Helpers::prints("запустите через google tests, чтобы увидеть тесты");
        return 0;
    }
}