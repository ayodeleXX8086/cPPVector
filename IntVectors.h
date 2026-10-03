//
// Created by Ayomide Ayodele on 6/6/26.
//

#ifndef VECTORS_VECTORS_H
#define VECTORS_VECTORS_H
#include <cstddef>
#include <exception>
#include <initializer_list>
#include <string>

class IntVectorBoundsError: public std::exception {
    std::string message;
    public:
    IntVectorBoundsError(std::size_t index, std::size_t size);
    const char* what() const noexcept override;
};

class IntVectors {
    public:
        IntVectors();
        explicit IntVectors(std::size_t capacity);
        IntVectors(std::initializer_list<int> list);
        ~IntVectors();
        IntVectors(const IntVectors& other);
        IntVectors &operator=(const IntVectors& other);
        IntVectors(IntVectors&& other) noexcept ;
        IntVectors &operator=(IntVectors&& other) noexcept ;
        int& operator[](std::size_t index);
        void push_back(int x);
        const int* begin() const noexcept;
        const int* end() const noexcept;
        std::size_t capacity() const noexcept;
        const int& operator[](std::size_t index) const;
        std::size_t size() const noexcept;

    private:
        int* data;
        std::size_t _size;
        std::size_t _capacity;
};
#endif //VECTORS_VECTORS_H