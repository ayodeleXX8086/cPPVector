//
// Created by Ayomide Ayodele on 8/6/26.
//

#ifndef VECTORS_UTILS_H
#define VECTORS_UTILS_H
#include <type_traits>

namespace core_implementation {
template <typename T1, typename T2>
    T2 copy(T1 start, T1 end, T2 dest) {
    while (start != end) {
        *dest++ = *start++;
    }
    return dest;
}
template <typename T1>
    constexpr std::remove_reference_t<T1>&& move(T1&& x)noexcept {
    return static_cast<std::remove_reference_t<T1>&&>(x);
}

template <typename T1>
    constexpr void destroy(T1* t)noexcept {
    t->~T1();
}

}
#endif //VECTORS_UTILS_H