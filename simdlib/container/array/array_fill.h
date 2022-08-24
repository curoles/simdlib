#pragma once

namespace simd {

/// Set all elements of C array to a value.
///
///
template<typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
void array_fill(T* array, std::size_t nr_elem, T val)
{
    auto ai = array_info<T,VSZ>(nr_elem);
    using VT [[maybe_unused]] = decltype(ai)::VT;

    VT filler{simd::op::fill<VT>(val)};

    #pragma GCC unroll 2
    #pragma GCC ivdep // asserts that there are no loop-carried dependencies
    for (std::size_t i = 0; i < ai.nr_simd; ++i) {
        ai.store(array, i, filler);
    }

#if 1
    #pragma GCC unroll 8
    #pragma GCC ivdep
    for (std::size_t i = ai.nr_simd*ai.LEN; i < ai.nr_elem; ++i) {
        array[i] = val;
    }
#else
    if (a.nr_tail_elem) {
        //tvx::pmask_t mask = tvx::_pmask(a.nr_tail_elem * sizeof(T));
        ai.store(array, ai.nr_simd, filler, mask);
    }
#endif
}

/// Fill array with a value.
///
/// span can be C array or contiguous STL container.
///
template<typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
void array_fill(std::span<T> array, T val)
{
    simd::array_fill<T,VSZ>(array.data(), array.size(), val);
}

} // namespace simd