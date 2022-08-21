#pragma once

namespace simd {

template<typename T, std::size_t VSZ_BITS>
struct array_info
{
    array_info(std::size_t nr_elem):nr_elem(nr_elem){}

    static constexpr std::size_t VSZ = VSZ_BITS / 8;
    static constexpr std::size_t LEN = VSZ / sizeof(T);

    using VT = simd::make<T,LEN>::type;

    const std::size_t nr_elem;
    const std::size_t nr_bytes = nr_elem * sizeof(T);
    const std::size_t nr_simd = nr_bytes / VSZ;
    const std::size_t nr_tail_bytes = nr_bytes - (nr_simd * VSZ);
    const std::size_t nr_tail_elem = nr_tail_bytes / sizeof(T);

    VT* at(T* array, std::size_t n) { return (VT*)&array[n*LEN]; }
    const VT* at(const T* array, std::size_t n) { return (const VT*)&array[n*LEN]; }
};

} // namespace

#include "array/array_reduce.h"