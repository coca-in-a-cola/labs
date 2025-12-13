#pragma once

#include <cstdlib>
#include <new>
#include <sstream>
#include <string>
#include <utility>

typedef int32_t int_t;

template <class T>
class Array final {
public:
    Array();
    explicit Array(int_t size);

    Array(const Array& other);
    Array(Array&& other) noexcept;

    ~Array();

    Array& operator=(Array other);

    friend void swap(Array& a, Array& b) noexcept {
        std::swap(a._maxSize, b._maxSize);
        std::swap(a._size, b._size);
        std::swap(a._items, b._items);
    }

    int_t size() const { return _size; }
    int_t capacity() const { return _maxSize; }

    const T& operator[](int_t i) const { return _items[i]; }
    T& operator[](int_t i) { return _items[i]; }

    int_t insert(const T& v);
    int_t insert(int_t index, const T& v);
    void remove(int_t index);

    [[nodiscard]] std::string to_string() const;

private:
    int_t _maxSize = 8;
    int_t _size = 0;
    T* _items = nullptr;

    template <class U>
    void init(int_t index, U&& v) { new(&_items[index]) T(std::forward<U>(v)); }

    static void erase(T* p, int_t n) noexcept {
        for (int_t i = 0; i < n; ++i) p[i].~T();
    }

    void checkIndex(i) {
        if (i < 0 || i > _size) throw std::out_of_range();
    }

    void grow();
};

#include "Array.inl"
