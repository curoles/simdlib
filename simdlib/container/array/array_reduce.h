#pragma once

namespace simd {

/// Reduce (fold) all elements of C array.
///
///
template<typename Op, typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
T array_reduce(const T* array, std::size_t nr_elem, T init)
{
    T acum{init};
    auto ai = array_info<T,VSZ>(nr_elem);
    using VT = decltype(ai)::VT;

    for (std::size_t i = 0; (i+1) < ai.nr_simd; i += 2) {
        VT v1 = ai.load(array,i);
        VT v2 = ai.load(array,i+1);
        acum = Op::d(acum, Op::d(Op::d(v1), Op::d(v2)));
    }

    if (ai.nr_simd % 2) {
        VT v = ai.load(array, ai.nr_simd-1);
        acum = Op::d(acum, Op::d(v));
    }
    //FIXME TODO rewrite with mask
    for (std::size_t i = ai.nr_simd*ai.LEN; i < ai.nr_elem; ++i) {
        acum = Op::d(acum, array[i]);
    }

    return acum;
}

/// Reduce contiguous sequence of objects.
///
/// span can be C array or STL container.
///
template<typename Op, typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
T array_reduce(std::span<const T> array, T init)
{
    return simd::array_reduce<Op,T,VSZ>(array.data(), array.size(), init);
}

} // namespace