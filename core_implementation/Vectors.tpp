#pragma once

#include <utility>

#include "RawStorage.h"
#include "utils.h"
#include "Vectors.h"

namespace core_implementation {
    static_assert(std::is_nothrow_move_constructible_v<RawStorage<int>>,
                  "RawStorage move ctor must be noexcept — Vectors's move noexcept depends on it");
    static_assert(std::is_nothrow_move_assignable_v<RawStorage<int>>,
                  "RawStorage move assign must be noexcept — Vectors's move noexcept depends on it");

    template<class T>
    void Vectors<T>::initialization(std::initializer_list<T> list) {
        core_implementation::RawStorage<T> temp(list.size());
        std::size_t temp_size=0;
        try {
            const T* src=list.begin();
            for (std::size_t i = 0; i < list.size(); ++i, ++src) {
                std::construct_at(temp.data()+i, *src);
                temp_size++;
            }
        }catch (...) {
            if (temp_size!=0) {
                for (std::size_t i = 0; i < temp_size; ++i) {
                    core_implementation::destroy(temp.data()+i);
                }
            }
            throw;
        }
        _storage=std::move(temp);
        _size=list.size();
    }

    template<class T>
    Vectors<T>::Vectors(): _storage(), _size(0) {}

    template<class T>
    Vectors<T>::Vectors(std::initializer_list<T> list): Vectors() {
        initialization(list);
    }


    template<class T>
    Vectors<T>::~Vectors() {
        for (std::size_t i = 0; i < _size; ++i) {
            core_implementation::destroy(_storage.data()+i);
        }
    }
    template<class T>
    Vectors<T>::Vectors(const std::size_t size): _storage(size), _size(size) {
    }

    template<class T>
    Vectors<T>::Vectors(const Vectors &other): _storage(other.capacity()), _size(0) {
        try {
            copy_from(other);
        }catch (...) {
            if (_size!=0) {
                for (std::size_t i = 0; i < _size; ++i) {
                    core_implementation::destroy(_storage.data()+i);
                }
            }
            throw;
        }
    }

    template<class T>
    Vectors<T>::Vectors(Vectors &&other) noexcept: _storage(core_implementation::move(other._storage)), _size(other._size) {
        other._size=0;
    }

    template<class T>
    Vectors<T> &Vectors<T>::operator=(const Vectors &other) {
        if (this != &other) {
            std::size_t temp_size=0;
            RawStorage<T>temp(other.capacity());
            try {
                for (std::size_t i = 0; i < other.size(); ++i) {
                    std::construct_at(temp.data()+i, other[i]);
                    temp_size++;
                }
            }catch (...) {
                if (temp_size!=0) {
                    for (std::size_t i = 0; i < temp_size; ++i) {
                        core_implementation::destroy(temp.data()+i);
                    }
                }
                throw;
            }
            for (std::size_t i = 0; i < size(); ++i) {
                core_implementation::destroy(_storage.data()+i);
            }
            _size=other._size;
            _storage=std::move(temp);
        }
        return *this;
    }

    template<class T>
    Vectors<T> &Vectors<T>::operator=(Vectors &&other) noexcept {
        if (this!=&other) {
            for (std::size_t i = 0; i < size(); ++i) {
                core_implementation::destroy(_storage.data()+i);
            }
            _storage=core_implementation::move(other._storage);
            _size=other._size;
            other._size=0;
        }
        return *this;
    }

    template<class T>
    void Vectors<T>::copy_from(const Vectors<T> &other) {
            for (std::size_t i = 0; i < other.size(); ++i, ++_size) {
                std::construct_at(_storage.data()+i, other[i]);
            }
    }

    template<class T>
    T &Vectors<T>::operator[](std::size_t index) {
        return _storage.data()[index];
    }

    template<class T>
    const T &Vectors<T>::operator[](std::size_t index) const {
        return _storage.data()[index];
    }

    template <class T>
    void Vectors<T>::grow() {
        auto new_capacity=_storage.capacity()==0?1:_storage.capacity()*2;
        RawStorage<T>temp(new_capacity);
        std::size_t temp_size(0);
        try {
            for (std::size_t i = 0; i < size(); ++i) {
                std::construct_at(temp.data()+i, std::move_if_noexcept(_storage.data()[i]));
                temp_size++;
            }
        }catch (...) {
            if (temp_size!=0) {
                for (std::size_t i = 0; i < temp_size; ++i) {
                    core_implementation::destroy(temp.data()+i);
                }
            }
            throw;
        }
        for (std::size_t i = 0; i < size(); ++i) {
            core_implementation::destroy(_storage.data()+i);
        }
        _storage=std::move(temp);
    }

    template<class T>
    void Vectors<T>::push_back(const T &value) {
        if (_size==_storage.capacity()) {
            grow();
        }
        std::construct_at(_storage.data()+size(),value);
        _size++;
    }
    template<class T>
    void Vectors<T>::push_back(T &&value) {
        if (_size==_storage.capacity()) {
            grow();
        }
        std::construct_at(_storage.data()+size(),std::move(value));
        _size++;
    }

    template<class T>
    std::size_t Vectors<T>::size() const noexcept {
        return _size;
    }

    template<class T>
    const T* Vectors<T>::end() const noexcept {
        return _storage.data()+_size;
    }

    template<class T>
    std::size_t Vectors<T>::capacity() const noexcept {
        return _storage.capacity();
    }

    template<class T>
    const T* Vectors<T>::begin() const noexcept {
        return _storage.data();
    }

    template<class T>
    void Vectors<T>::pop_back() {
        if (_size!=0) {
            core_implementation::destroy(_storage.data()+_size-1);
            --_size;
        }
    }

    template<class T>
    const T *Vectors<T>::data() const noexcept {
        return _storage.data();
    }

    template<class T>
    T *Vectors<T>::begin() noexcept {
        return _storage.data();
    }

    template<class T>
    T *Vectors<T>::end() noexcept {
        return _storage.data()+_size;
    }

}
