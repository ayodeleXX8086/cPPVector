//
// Created by Ayomide Ayodele on 6/6/26.
//

#include "IntVectors.h"

#include <algorithm>
#include <iostream>

IntVectorBoundsError::IntVectorBoundsError(std::size_t index, std::size_t size) {
    message = "Error: Tried to access index " + std::to_string(index) + ", but vector size is only " + std::to_string(size);
}

const char* IntVectorBoundsError::what() const noexcept{
    return message.c_str();
}

IntVectors::IntVectors(std::size_t capacity): _size(0), _capacity(capacity<=0? 1 : capacity) {
    data = new int[_capacity];
}
IntVectors::~IntVectors() {
    _capacity=0;
    _size=0;
    delete[] data;
}
const int* IntVectors::begin() const noexcept{
    return data;
}

const int* IntVectors::end() const noexcept {
    return data+_size;
}
IntVectors::IntVectors(): data(new int[1]), _size(0), _capacity(1) {}
IntVectors::IntVectors(const IntVectors & other): data(new int[other._capacity]), _size(other._size), _capacity(other._capacity) {
    std::copy(other.data, other.data + other._size, data);
}
IntVectors::IntVectors(const std::initializer_list<int> list): _size(list.size()), _capacity(list.size()) {
    data = new int[_capacity];
    int* destPrt = data;;
    for (const int *src=list.begin(); src != list.end(); ++src, ++destPrt) {
        *destPrt = *src;
    }
}

IntVectors::IntVectors(IntVectors &&other) noexcept : data(other.data), _size(other._size), _capacity(other._capacity) {
    other.data = nullptr;
    other._size = 0;
    other._capacity = 0;
}
IntVectors& IntVectors::operator=(const IntVectors& other) {
    if (this==&other)return *this;
    int* tmpData = new int[other._capacity];
    std::copy(other.data, other.data + other._size, tmpData);
    delete[] data;
    data = tmpData;
    _size = other._size;
    _capacity = other._capacity;
    return *this;
}

std::size_t IntVectors::size() const noexcept{
    return _size;
}
int& IntVectors::operator[](std::size_t index) {
    if (index >= _size) throw IntVectorBoundsError(index, _size);
    return data[index];
}
const int& IntVectors::operator[](std::size_t index) const {
    if (index >= _size) throw IntVectorBoundsError(index, _size);
    return data[index];
}
void IntVectors::push_back(int x) {
    if (_size == _capacity) {
        int* tmpData = new int[_capacity * 2];
        std::copy(data, data + _size, tmpData);
        delete[] data;
        data = tmpData;
        _capacity *= 2;
    }
    int *data_ptr = &data[_size++];
    *data_ptr = x;
}

std::size_t IntVectors::capacity() const noexcept {
    return _capacity;
}
IntVectors &IntVectors::operator=(IntVectors &&other) noexcept {
    if (this!=&other) {
        delete[] data;
        data = other.data;
        _size = other._size;
        _capacity = other._capacity;

        other.data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }
    return *this;
}


