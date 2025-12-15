#pragma once

namespace Sort {
    template <class T, class Compare>
    inline T* medianOfThree(T* a, T* b, T* c, Compare comp) {
        if (comp(*a, *b)) {
            if (comp(*b, *c)) return b;
            if (comp(*a, *c)) return c;
            return a;
        }

        if (comp(*a, *c)) return a;
        if (comp(*b, *c)) return c;
        return b;
    }

    // как я понял, это разбиение хорошо помогает сократить случаи сортировки,
    // когда рядом находятся несколько повторяющихся элементов
    // то есть условно три группы < == и >
    template <class T, class Compare>
    inline std::pair<T*, T*> partition3(T* first, T* last, Compare comp) {
        auto middle = first + (last - first) / 2;
        auto pivotPointer = medianOfThree(first, middle, last - 1, comp);
        auto pivot = *pivotPointer;

        auto leftSide = first;
        auto index  = first;
        auto rightSide = last;

        while (index < rightSide) {
            if (comp(*index, pivot)) {
                std::swap(*leftSide, *index);
                ++leftSide;
                ++index;
            } else if (comp(pivot, *index)) {
                --rightSide;
                std::swap(*index, *rightSide);
            } else {
                ++index;
            }
        }

        return {leftSide, rightSide};
    }
}