//
// Created by Ayomide Ayodele on 8/3/26.
//
#include "Vectors.h"
namespace core_implementation {
    VectorBoundsError::VectorBoundsError(std::size_t index, std::size_t size) {
        message = "Error: Tried to access index " + std::to_string(index) + ", but vector size is only " + std::to_string(size);
    }

    const char* VectorBoundsError::what() const noexcept{
        return message.c_str();
    }
}
