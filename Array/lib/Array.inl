#pragma once
#include <sstream>
#include <string>
#include <format>
#include "Array.hpp"

namespace YAR {
    template <class T>
    Array<T>::Array() {
        _items = static_cast<T*>(std::malloc(sizeof(T) * _maxSize));
        if (!_items) throw std::bad_alloc();
    }

    template <class T>
    Array<T>::Array(int_t size): _maxSize(size) {
        if (size < 0) {
            throw std::bad_alloc();
        }

        _items = static_cast<T*>(std::malloc(sizeof(T) * _maxSize));
        if (!_items) throw std::bad_alloc();
    }

    template <class T>
    Array<T>::Array(const Array& other): _maxSize(other._maxSize), _size(other._size) {
        _items = static_cast<T*>(std::malloc(sizeof(T) * _maxSize));
        if (!_items) throw std::bad_alloc();

        int_t built = 0;
        try {
            for (; built < _size; ++built) new(&_items[built]) T(other._items[built]);
        } catch (...) {
            erase(_items, built);
            std::free(_items);
            _items = nullptr;
            _maxSize = _size = 0;
            throw;
        }
    }

    template <class T>
    Array<T>::Array(Array&& other) noexcept
        : _maxSize(std::exchange(other._maxSize, 0)),
        _size(std::exchange(other._size, 0)),
        _items(std::exchange(other._items, nullptr)) {}

    template <class T>
    Array<T>::~Array() {
        if (_items) {
            erase(_items, _size);
            std::free(_items);
        }
    }

    template <class T>
    Array<T>& Array<T>::operator=(Array other) {
        swap(*this, other);

        return *this;
    }

    template <class T>
    int_t Array<T>::insert(const T& v) {
        if (_size >= _maxSize) grow();
        init(_size, v);
        return _size++;
    }

    template <class T>
    int_t Array<T>::insert(int_t index, const T& v) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range(std::format("invalid index {} at array", index));
        }

        if (_size >= _maxSize) {
            grow();
        }

        for (int_t i = _size; i > index; --i) {
            init((i), std::move(_items[i - 1]));
            _items[i - 1].~T();
        }

        init(index, v);
        ++_size;
        return index;
    }

    template <class T>
    void Array<T>::remove(int_t index) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range(std::format("invalid index {} at array", index));
        }

        _items[index].~T();
        for (int_t i = index; i < _size - 1; ++i) {
            init(i, std::move(_items[i + 1]));
            _items[i + 1].~T();
        }
        --_size;
    }

    template <class T>
    void Array<T>::grow() {
        int_t newCap = static_cast<int_t>(_maxSize * 2 + 1);

        T* newData = static_cast<T*>(std::malloc(sizeof(T) * newCap));
        if (!newData) throw std::bad_alloc();

        int_t index = 0;
        try {
            for (; index < _size; ++index) new(&newData[index]) T(std::move(_items[index]));
        } catch (...) {
            erase(newData, index);
            std::free(newData);
            throw;
        }

        erase(_items, _size);
        std::free(_items);

        _items = newData;
        _maxSize = newCap;
    }

    template <class T>
    std::string Array<T>::to_string() const {
        std::ostringstream os;

        os << "[";
        for (int i = 0; i < _size; ++i) {
            if (i) os << ", ";
            os << _items[i];
        }
        os << "]";

        return os.str();
    }

}