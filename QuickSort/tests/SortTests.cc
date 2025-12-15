#pragma once

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <random>
#include <vector>

#include "../lib/Sort.hpp"
#include "../RandomArray.hpp"

namespace Sort {

template <class T, class Compare>
bool isSortedBy(const T* a, std::size_t n, Compare comp) {
    for (std::size_t i = 1; i < n; ++i)
        if (comp(a[i], a[i - 1])) return false;
    return true;
}

template <class T>
std::vector<T> toVec(const T* a, std::size_t n) {
    return std::vector<T>(a, a + n);
}

template <class T>
void fillReverse(T* a, std::size_t n) {
    for (std::size_t i = 0; i < n; ++i)
        a[i] = static_cast<T>(n - 1 - i);
}

template <class T>
void fillSorted(T* a, std::size_t n) {
    for (std::size_t i = 0; i < n; ++i)
        a[i] = static_cast<T>(i);
}

template <class T>
void fillManyDuplicates(T* a, std::size_t n) {
    for (std::size_t i = 0; i < n; ++i)
        a[i] = static_cast<T>(i % 5);
}

template <class T>
void fillAlmostSorted(T* a, std::size_t n) {
    fillSorted(a, n);
    if (n >= 4) std::swap(a[1], a[2]);
    if (n >= 8) std::swap(a[5], a[6]);
}

template <class T, class Compare>
void expectSameAsStdSort(T* a, std::size_t n, Compare comp) {
    auto expected = toVec(a, n);
    std::sort(expected.begin(), expected.end(), comp);

    Sort::sort(a, a + n, comp);

    ASSERT_TRUE(isSortedBy(a, n, comp));
    auto got = toVec(a, n);
    ASSERT_EQ(got.size(), expected.size());
    for (size_t i = 0; i < got.size(); ++i) {
        EXPECT_TRUE(got[i] == expected[i]) << " at index " << i << ": " << got[i] << " and " << expected[i];
        EXPECT_TRUE(got[i] == expected[i]) << " at index " << i << ": " << got[i] << " and" << expected[i];
    }
}

TEST(SortInt, EmptyRangeNoCrash) {
    int_t* a = nullptr;
    Sort::sort(a, a, [](int_t x, int_t y){ return x < y; });
    SUCCEED();
}

TEST(SortInt, SingleElementNoChange) {
    int_t a[1] = {42};
    Sort::sort(a, a + 1, [](int_t x, int_t y){ return x < y; });
    EXPECT_EQ(a[0], 42);
}

TEST(SortInt, AlreadySorted) {
    constexpr std::size_t n = 100;
    auto* a = new int_t[n];
    fillSorted(a, n);

    expectSameAsStdSort(a, n, [](int_t x, int_t y){ return x < y; });

    delete[] a;
}

TEST(SortInt, ReverseSorted) {
    constexpr std::size_t n = 200;
    auto* a = new int_t[n];
    fillReverse(a, n);

    expectSameAsStdSort(a, n, [](int_t x, int_t y){ return x < y; });

    delete[] a;
}

TEST(SortInt, ManyDuplicates) {
    constexpr std::size_t n = 300;
    auto* a = new int_t[n];
    fillManyDuplicates(a, n);

    expectSameAsStdSort(a, n, [](int_t x, int_t y){ return x < y; });

    delete[] a;
}

TEST(SortInt, AlmostSorted) {
    constexpr std::size_t n = 256;
    auto* a = new int_t[n];
    fillAlmostSorted(a, n);

    expectSameAsStdSort(a, n, [](int_t x, int_t y){ return x < y; });

    delete[] a;
}

TEST(SortInt, RandomFromRandomArray) {
    for (int_t n = 1; n <= 300; n += 23) {
        auto* a = randomArray(n);
        expectSameAsStdSort(a, static_cast<std::size_t>(n),
                            [](int_t x, int_t y){ return x < y; });
        delete[] a;
    }
}

TEST(SortInt, DescComparator) {
    constexpr std::size_t n = 150;
    auto* a = new int_t[n];
    fillManyDuplicates(a, n);

    expectSameAsStdSort(a, n, [](int_t x, int_t y){ return x > y; });

    delete[] a;
}

TEST(SortTestStruct, RandomTestStructsByKey) {
    for (int_t n : {1, 2, 3, 10, 64, 200}) {
        auto* a = randomStructArray(n);

        expectSameAsStdSort(a, static_cast<std::size_t>(n), TestStruct::comp);

        delete[] a;
    }
}

TEST(SortTestStruct, ManyEqualKeys) {
    constexpr int_t n = 200;
    auto* a = new TestStruct[n];
    for (int_t i = 0; i < n; ++i) {
        a[i].key = i % 5;
        a[i].payload = 1000 - i;
    }

    expectSameAsStdSort(a, static_cast<std::size_t>(n), TestStruct::comp);

    delete[] a;
}
}