#pragma once

namespace simd {

template<typename T, std::size_t VSZ_BITS>
struct array_info
{
    array_info(std::size_t nr_elem):nr_elem(nr_elem){}

    static constexpr std::size_t VSZ = VSZ_BITS / 8;
    static constexpr std::size_t LEN = VSZ / sizeof(T);

    using VT = simd::make<T,LEN>::type;
    using MASK = simd::PMask<VT,VSZ_BITS>;

    const std::size_t nr_elem;
    const std::size_t nr_bytes = nr_elem * sizeof(T);
    const std::size_t nr_simd = nr_bytes / VSZ;
    const std::size_t nr_tail_bytes = nr_bytes - (nr_simd * VSZ);
    const std::size_t nr_tail_elem = nr_tail_bytes / sizeof(T);

    VT* at(T* array, std::size_t n) { return (VT*)&array[n*LEN]; }
    const VT* at(const T* array, std::size_t n) { return (const VT*)&array[n*LEN]; }

    inline VT load(const T* array, std::size_t n) { return simd::op::load(at(array, n)); }

    inline void store(T* array, std::size_t n, VT v) { simd::op::store(at(array, n), v); }

    inline VT load(const T* array, std::size_t n, MASK mask) {
        return simd::op::load((T*)at(array, n), mask);
    }

    inline void store(T* array, std::size_t n, VT v, MASK mask) {
        simd::op::store((T*)at(array, n), v, mask);
    }
};

} // namespace

#include "array/aligned_allocator.h"
#include "array/array_fill.h"
#include "array/array_reduce.h"
#include "array/array_reduce_and.h"
#include "array/array_find_first.h"
#include "array/array_find_max.h"
#include "array/arrays_bop.h"
#include "array/arrays_add.h"