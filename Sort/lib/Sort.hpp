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

    template <class T, class Compare>
    inline T* partrition(T *first, T *last, Compare comp) {
        auto mid = first + (last - first) / 2;
        auto pivotPointer = medianOfThree(first, mid, last - 1, comp);
        auto pivot = std::move(*pivotPointer);

        auto i = first;
        auto j = last - 1;

        while(true) {
            while(comp(*i, pivot)) ++i;
            while(comp(pivot, *j)) --j;

            if (i >= j) {
                *pivotPointer = std::move(pivot);
                return ++j;
            }

            std::swap(*i, *j);
            ++i;
            --j;
        }
    }

    template <class T, class Compare>
    void sort(T* first, T* last, Compare comp) {
        while (true) {
            const std::ptrdiff_t n = last - first;
            if (n <= 1) return;

            T* cut = partition(first, last, comp);

            // Tail recursion elimination
            if ((cut - first) < (last - cut)) {
                sort(first, cut, comp);
                first = cut;
            } else {
                sort(cut, last, comp);
                last = cut;
            }
        }
    }
}