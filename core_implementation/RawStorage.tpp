#pragma once
#include "RawStorage.h"

namespace core_implementation {
    template<class T>
    RawStorage<T>::RawStorage(): _data(nullptr), _capacity(0) {}
    template<class T>
    RawStorage<T>::RawStorage(std::size_t capacity): _data(nullptr), _capacity(capacity) {
        if (_capacity>0) {
            _data = _allocator.allocate(_capacity);
        }
    }

    template<class T>
    RawStorage<T>::~RawStorage() {
        if (_data) {
            _allocator.deallocate(_data, _capacity);
        }
    }

    template<class T>
    T *RawStorage<T>::data() {
        return _data;
    }

    template<class T>
    const T *RawStorage<T>::data() const {
        return _data;
    }

    template<class T>
    std::size_t RawStorage<T>::capacity() const {
        return _capacity;
    }

    template<class T>
    RawStorage<T>::RawStorage(RawStorage &&other) noexcept : _data(other._data), _capacity(other._capacity) {
        other._data = nullptr;
        other._capacity = 0;
    }

    template<class T>
    RawStorage<T> &RawStorage<T>::operator=(RawStorage &&other) noexcept {
        if (this != &other) {
            if (_data) {
                _allocator.deallocate(_data, _capacity);
            }
            _data = other._data;
            _capacity = other._capacity;
            other._data = nullptr;
            other._capacity = 0;
        }
        return *this;
    }
}
