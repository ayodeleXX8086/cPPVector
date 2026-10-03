//
// Created by Ayomide Ayodele on 8/3/26.
//

#ifndef VECTORS_VECTORS_H
#define VECTORS_VECTORS_H
#include <cstddef>
#include <string>

#include "RawStorage.h"

namespace core_implementation {
    class VectorBoundsError: public std::exception {
        std::string message;
    public:
        VectorBoundsError(std::size_t index, std::size_t size);
        const char* what() const noexcept override;
    };

    template <class T>
    class Vectors {
        RawStorage<T> _storage;
        std::size_t _size;
        void copy_from(const Vectors<T> &other);
        void grow();
        void initialization(std::initializer_list<T> list);
        static T* allocate(std::size_t n);
        static void deallocate(T* p) noexcept;
    public:
        Vectors();
        explicit Vectors(std::size_t size);
        Vectors(std::initializer_list<T> list);
        ~Vectors();
        Vectors(const Vectors & other);
        Vectors& operator=(const Vectors & other);
        Vectors(Vectors && other) noexcept;
        Vectors& operator=(Vectors && other) noexcept;

        T& operator[](std::size_t index);
        const T& operator[](std::size_t index) const;

        void push_back(const T& value);
        void push_back(T&& value);
        void pop_back();
        std::size_t size() const noexcept;
        std::size_t capacity() const noexcept;

        const T* data() const noexcept;
        const T* begin() const noexcept;
        T* end() noexcept;
        T* begin() noexcept;
        const T* end() const noexcept;
    };
} // core_implementation
#include "Vectors.tpp"
#endif //VECTORS_VECTORS_H