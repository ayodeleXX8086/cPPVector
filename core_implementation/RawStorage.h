//
// Created by Ayomide Ayodele on 8/17/26.
//

#ifndef VECTORS_RAWSTORAGE_H
#define VECTORS_RAWSTORAGE_H
#include <memory>

namespace core_implementation {
    template <class T>
   class RawStorage {
    private:
        std::allocator<T> _allocator;
        T* _data;
        std::size_t _capacity;
    public:
        RawStorage();
        explicit RawStorage(std::size_t capacity);
        ~RawStorage();
        RawStorage(const RawStorage&) = delete;
        RawStorage& operator=(const RawStorage&) = delete;
        RawStorage(RawStorage&& other) noexcept;
        RawStorage& operator=(RawStorage&& other) noexcept;
        T* data();
        const T* data() const;
        std::size_t capacity() const;
    };
}
#include "RawStorage.tpp"
#endif //VECTORS_RAWSTORAGE_H