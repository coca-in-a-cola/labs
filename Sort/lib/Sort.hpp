#pragma once
#include "Partition.hpp"

namespace Sort {
    template<typename T, typename Compare>
    inline void insertionsSort(T *first, T *last, Compare comp) {
        for (T *i = first + 1; i < last; ++i) {
            T key = std::move(*i);
            T *j = i;
            while (j > first && comp(key, *(j - 1))) {
                *j = std::move(*(j - 1));
                --j;
            }

            *j = std::move(key);
        }
    }

    template <class T, class Compare>
    void quickSort(T* first, T* last, Compare comp) {
        while (true) {
            const auto n = last - first;
            if (n <= 1) return;

            auto [lt, gt] = partition3(first, last, comp);

            auto leftBegin = first;
            auto leftEnd = lt;
            auto rightBegin = gt;
            auto rightEnd = last;

            if (leftBegin == leftEnd) {
                first = rightBegin;
                last = rightEnd;
                continue;
            }

            if (rightBegin == rightEnd) {
                first = leftBegin;
                last = rightBegin;
                continue;
            }

            if ((leftEnd - leftBegin) < (rightEnd - rightBegin)) {
                sort(leftBegin, leftEnd, comp);
                first = rightBegin;
                last = rightEnd;
                continue;
            }

            sort(rightBegin, rightEnd, comp);
            first = leftBegin;
            last = leftEnd;
        }
    }

    template <class T, class Compare>
    void sort(T* first, T* last, Compare comp) {
        const auto n = last - first;
        if (n <= 1) {
            return;
        }

        return quickSort(first, last, comp);
    }
}