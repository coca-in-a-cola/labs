#pragma once

#include <chrono>
#include <iostream>
#include "./lib/Sort.hpp"
#include "../Shared/Definitions.h"
#include "RandomArray.hpp"

namespace Sort {
    constexpr int_t N_MAX = 1000;
    constexpr int_t REPEATS_MAX = 20;

    int main(int argc, char **argv) {
        std::cout << "Сравнение скорости выполнения quickSort и insertionsSort" << std::endl;
        std::cout << "на массивах длиной от 0 до 100 [на примере int]" << std::endl;

        using clock = std::chrono::steady_clock;

        // этот хак по идее частично отключает оптимизации компилятора
        volatile int sink = 0;

        float_t result = .0f;

        auto csvPath = Helpers::getFullPath("../data/graph.csv");
        std::ofstream csv(csvPath);
        csv.imbue(std::locale::classic());
        csv << "n,quick_ns_per_run,ins_ns_per_run\n";

        for (int_t n = 1; n <= N_MAX; ++n) {
            constexpr int repeats = REPEATS_MAX;

            auto base = randomArray(n);
            auto arr  = new int_t[n];
            auto copy = new int_t[n];

            std::chrono::nanoseconds tQuick{0}, tIns{0};

            for (int r = 0; r < repeats; ++r) {
                std::copy(base, base + n, arr);
                auto s1 = clock::now();
                sort(arr, arr + n, [](int a,int b){ return a < b; });
                auto e1 = clock::now();
                tQuick += std::chrono::duration_cast<std::chrono::nanoseconds>(e1 - s1);
                sink += arr[0];

                std::copy(base, base + n, copy);
                auto s2 = clock::now();
                insertionsSort(copy, copy + n, [](int a,int b){ return a < b; });
                auto e2 = clock::now();
                tIns += std::chrono::duration_cast<std::chrono::nanoseconds>(e2 - s2);
                sink += copy[0];
            }

            auto avgQuickTime = tQuick.count() / repeats;
            auto avgInsTime = tIns.count() / repeats;

            auto currentResult = (1 - (float)avgQuickTime / (float)avgInsTime) * 100.0f;
            result = (result * (n - 1) + currentResult) / n;

            csv << n << ',' << avgQuickTime << ',' << avgInsTime << '\n';

            delete[] base;
            delete[] arr;
            delete[] copy;
        }

        Helpers::printsh(
            "QuickSort быстрее InsertSort на {}% при рзмерах 1...{} и пороге {}",
            std::round(result),
            N_MAX,
            INSERTION_TRESHOLD
        );
        Helpers::prints("запустите через google tests, чтобы увидеть тесты");
        Helpers::input<std::string>("");

        csv.close();
        return 0;
    }
}