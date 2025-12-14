#pragma once

#include <gtest/gtest.h>

#include <string>
#include <utility>
#include "Array.hpp"

namespace YAR {

struct TrackableStruct {
    static inline int alive = 0;
    static inline int ctor = 0;
    static inline int copyCtor = 0;
    static inline int moveCtor = 0;
    static inline int dtor = 0;

    int x = 0;

    TrackableStruct() : x(0) { ++alive; ++ctor; }
    explicit TrackableStruct(int v) : x(v) { ++alive; ++ctor; }

    TrackableStruct(const TrackableStruct& o) : x(o.x) { ++alive; ++copyCtor; }
    TrackableStruct(TrackableStruct&& o) noexcept : x(o.x) { o.x = -1; ++alive; ++moveCtor; }

    TrackableStruct& operator=(const TrackableStruct& o) { x = o.x; return *this; }
    TrackableStruct& operator=(TrackableStruct&& o) noexcept { x = o.x; o.x = -1; return *this; }

    ~TrackableStruct() { --alive; ++dtor; }

    static void Reset() {
        alive = ctor = copyCtor = moveCtor = dtor = 0;
    }
};

TEST(ArrayBasic, DefaultCtorEmpty) {
    Array<int> a;
    EXPECT_EQ(a.size(), 0);
    EXPECT_GE(a.capacity(), 1);
}

TEST(ArrayBasic, InsertAtEndAndIndex) {
    Array<int> a(1);
    EXPECT_EQ(a.insert(10), 0);
    EXPECT_EQ(a.insert(20), 1);
    EXPECT_EQ(a.insert(1, 15), 1);

    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(a[0], 10);
    EXPECT_EQ(a[1], 15);
    EXPECT_EQ(a[2], 20);
}

TEST(ArrayBasic, RemoveShiftsLeft) {
    Array<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);

    a.remove(1);

    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 3);
}


TEST(ArrayBasic, RemoveOutOfRangeThrows) {
    Array<int> a;
    a.insert(1);

    EXPECT_THROW(a.remove(-1), std::out_of_range);
    EXPECT_THROW(a.remove(100), std::out_of_range);

    EXPECT_EQ(a.size(), 1);
    EXPECT_EQ(a[0], 1);
}

TEST(ArrayBasic, RemoveOutOfRangeKeepsState) {
    Array<int> a;
    a.insert(1);
    a.insert(2);

    EXPECT_THROW(a.remove(2), std::out_of_range);

    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
}

TEST(ArrayToString, Formats) {
    Array<int> a;
    EXPECT_EQ(a.to_string(), "[]");
    a.insert(7);
    a.insert(8);
    EXPECT_EQ(a.to_string(), "[7, 8]");
}

TEST(ArrayCopy, CopyCtorDeepCopy) {
    Array<std::string> a;
    a.insert("a");
    a.insert("b");

    Array<std::string> b(a);

    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(b[0], "a");
    EXPECT_EQ(b[1], "b");

    b[0] = "x";
    EXPECT_EQ(a[0], "a");
}

TEST(ArrayAssign, CopyAndSwapCopyAssignment) {
    Array<int> a;
    a.insert(1);
    a.insert(2);

    Array<int> b;
    b.insert(10);

    b = a;

    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
}

TEST(ArrayAssign, SelfAssignmentNoCorruption) {
    Array<int> a;
    for (int i = 0; i < 20; ++i) a.insert(i);

    a = a;

    EXPECT_EQ(a.size(), 20);
    for (int i = 0; i < 20; ++i) EXPECT_EQ(a[i], i);
}

TEST(ArrayMove, MoveCtorLeavesSourceValid) {
    Array<int> a;
    a.insert(1);
    a.insert(2);

    Array<int> b(std::move(a));

    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);

    EXPECT_GE(a.size(), 0);
    EXPECT_GE(a.capacity(), 0);
}

TEST(ArrayMove, MoveAssignmentViaCopyAndSwap) {
    Array<int> a;
    for (int i = 0; i < 5; ++i) a.insert(i);

    Array<int> b;
    b.insert(100);

    b = std::move(a);

    EXPECT_EQ(b.size(), 5);
    for (int i = 0; i < 5; ++i) EXPECT_EQ(b[i], i);
}

TEST(ArrayLifetime, DtorsCalledForElementsOnScopeExit) {
    TrackableStruct::Reset();
    {
        Array<TrackableStruct> a;
        a.insert(TrackableStruct{1});
        a.insert(TrackableStruct{2});
        a.insert(TrackableStruct{3});
        EXPECT_EQ(TrackableStruct::alive, 3);
    }
    EXPECT_EQ(TrackableStruct::alive, 0);
    EXPECT_GE(TrackableStruct::dtor, 3);
}

TEST(ArrayLifetime, InsertInMiddleDestroysShiftedFromSlots) {
    TrackableStruct::Reset();
    {
        Array<TrackableStruct> a;
        a.insert(TrackableStruct{1});
        a.insert(TrackableStruct{3});
        a.insert(1, TrackableStruct{2});

        EXPECT_EQ(a.size(), 3);
        EXPECT_EQ(a[0].x, 1);
        EXPECT_EQ(a[1].x, 2);
        EXPECT_EQ(a[2].x, 3);
        EXPECT_EQ(TrackableStruct::alive, 3);
    }
    EXPECT_EQ(TrackableStruct::alive, 0);
}

TEST(ArrayLifetime, RemoveDestroysExactlyOne) {
    TrackableStruct::Reset();
    {
        Array<TrackableStruct> a;
        a.insert(TrackableStruct{1});
        a.insert(TrackableStruct{2});
        a.insert(TrackableStruct{3});

        const int dtorBefore = TrackableStruct::dtor;
        a.remove(1);
        EXPECT_EQ(a.size(), 2);
        EXPECT_EQ(a[0].x, 1);
        EXPECT_EQ(a[1].x, 3);
        EXPECT_EQ(TrackableStruct::alive, 2);
        EXPECT_GE(TrackableStruct::dtor, dtorBefore + 1);
    }
    EXPECT_EQ(TrackableStruct::alive, 0);
}

TEST(ArrayReallocate, KeepsValuesAfterGrowth) {
    Array<int> a(1);
    for (int i = 0; i < 200; ++i) a.insert(i);

    EXPECT_EQ(a.size(), 200);
    for (int i = 0; i < 200; ++i) EXPECT_EQ(a[i], i);
}

}
