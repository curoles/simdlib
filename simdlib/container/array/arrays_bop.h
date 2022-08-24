#pragma once

namespace simd {

/// Binary operation between elements of 2 arrays.
///
///
template<typename Op, typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
void arrays_bop(T* dst_array, const T* array1, const T* array2, std::size_t nr_elem)
{
    auto ai = array_info<T,VSZ>(nr_elem);
    using VT = decltype(ai)::VT;

    #pragma GCC unroll 2
    #pragma GCC ivdep // asserts that there are no loop-carried dependencies
    for (std::size_t i = 0; i < ai.nr_simd; ++i) {
        VT v1 = ai.load(array1, i);
        VT v2 = ai.load(array2, i);
        ai.store(dst_array, i, Op(v1, v2));
    }

    if (a.nr_tail_elem) {
        //tvx::pmask_t mask = tvx::_pmask(a.nr_tail_elem * sizeof(T));
        VT v1 = ai.load(array1, ai.nr_simd, mask);
        VT v2 = ai.load(array2, ai.nr_simd, mask);
        ai.store(dst_array, ai.nr_simd, Op(v1, v2), mask);
    }


    return acum;
}

/// Binary operation between elements of 2 arrays.
///
/// span can be C array or contiguous STL container.
///
template<typename Op, typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
void arrays_bop(std::span<T> dst_array, std::span<const T> array1, std::span<const T> array2)
{
    assert(array2.size() >= array1.size());
    assert(dst_array.size() >= array1.size());

    simd::arrays_bop<Op,T,VSZ>(dst_array.data(), array1.data(), array2.data(), array1.size());
}

} // namespace