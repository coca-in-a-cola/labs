#pragma once

#include <chrono>
#include <cmath>
#include <iomanip>
#include <map>
#include <random>
#include <string>
#include <format>

namespace Sort {

    struct TestStruct {
        int key{};
        int payload{};

        // для корректной работы тестов
        bool operator==(const TestStruct& other) const {
            return key == other.key && payload == other.payload;
        }

        [[nodiscard]] std::string to_string() const {
            return std::format("key {} payload {}", key, payload);
        }

        static bool comp(const TestStruct& a, const TestStruct& b) {
            if (a.key != b.key) return a.key < b.key;
            return a.payload < b.payload;
        }
    };

    std::ostream &operator<<(std::ostream &os, TestStruct const &m) { 
        return os << m.to_string();
    }

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

    TestStruct* randomStructArray(int_t length) {
        static thread_local std::mt19937 gen{123456u};
        static thread_local std::uniform_int_distribution<int> keyDist{-50, 50};
        static thread_local std::uniform_int_distribution<int> payloadDist{0, 100000};

        auto* result = new TestStruct[length];
        for (int_t i = 0; i < length; ++i) {
            result[i].key = keyDist(gen);
            result[i].payload = payloadDist(gen);
        }
        return result;
    }
}