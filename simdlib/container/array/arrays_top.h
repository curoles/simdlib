#pragma once

namespace simd {

/// Ternary operation between elements of 3 arrays.
///
///
template<typename Op, typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
void arrays_top(T* dst_array, const T* array1, const T* array2,  const T* array3, std::size_t nr_elem)
{
    auto ai = array_info<T,VSZ>(nr_elem);
    using VT = decltype(ai)::VT;

    #pragma GCC unroll 2
    #pragma GCC ivdep // asserts that there are no loop-carried dependencies
    for (std::size_t i = 0; i < ai.nr_simd; ++i) {
        VT v1 = ai.load(array1, i);
        VT v2 = ai.load(array2, i);
        VT v3 = ai.load(array3, i);
        ai.store(dst_array, i, Op::d(v1, v2, v3));
    }

    if (ai.nr_tail_elem) {
        auto mask = decltype(ai)::MASK::make_set_first_n(ai.nr_tail_elem);
        VT v1 = ai.load(array1, ai.nr_simd, mask);
        VT v2 = ai.load(array2, ai.nr_simd, mask);
        VT v3 = ai.load(array3, ai.nr_simd, mask);
        ai.store(dst_array, ai.nr_simd, Op::d(v1, v2, v3), mask);
    }
}

/// Ternary operation between elements of 3 arrays.
///
/// span can be C array or contiguous STL container.
///
template<typename Op, typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
void arrays_top(std::span<T> dst_array, std::span<const T> array1, std::span<const T> array2, std::span<const T> array3)
{
    assert(array2.size() >= array1.size());
    assert(array3.size() >= array1.size());
    assert(dst_array.size() >= array1.size());

    simd::arrays_top<Op,T,VSZ>(dst_array.data(), array1.data(), array2.data(), array3.data(), array1.size());
}

} // namespace