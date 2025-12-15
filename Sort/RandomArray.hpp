#pragma once

#include <chrono>
#include <cmath>
#include <iomanip>
#include <map>
#include <random>

namespace Sort {
    // на полностью СЛУЧАЙНОМ массиве quickSort работает ХУЖЕ, нежели insertionSort
    // давайте сгенерируем примерный массив с разбиением по нормальному распределению
    int_t* randomArray(int_t length) {
        static thread_local std::mt19937 gen{123456u};
        static thread_local std::normal_distribution<double> dist{100.0, 20.0};

        auto* result = new int_t[length];
        for (int_t i = 0; i < length; ++i)
            result[i] = static_cast<int_t>(std::lround(dist(gen)));
        return result;
    }
}