#pragma once

namespace simd {

/// Find element with maximum value.
///
///
template<typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
T array_find_max(const T* array, std::size_t nr_elem)
{
    auto ai = array_info<T,VSZ>(nr_elem);
    using VT = decltype(ai)::VT;

    T maxel {array[0]};

    for (std::size_t i = 0; i < ai.nr_simd; ++i) {
        VT v = ai.load(array,i);
        maxel = std::max(maxel, simd::op::hmax(v));
    }

    //FIXME TODO once hsum intrinsic has mask, rewrite with hmax+mask
    for (std::size_t i = ai.nr_simd*ai.LEN; i < ai.nr_elem; ++i) {
        maxel = std::max(maxel, array[i]);
    }

    return maxel;
}

template<typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
T array_find_max(std::span<const T> array)
{
    return simd::array_find_max<T,VSZ>(array.data(), array.size());
}

/// Find element with minimum value.
///
///
template<typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
T array_find_min(const T* array, std::size_t nr_elem)
{
    auto ai = array_info<T,VSZ>(nr_elem);
    using VT = decltype(ai)::VT;

    T minel {array[0]};

    for (std::size_t i = 0; i < ai.nr_simd; ++i) {
        VT v = ai.load(array,i);
        minel = std::min(minel, simd::op::hmin(v));
    }

    //FIXME TODO once hsum intrinsic has mask, rewrite with hmin+mask
    for (std::size_t i = ai.nr_simd*ai.LEN; i < ai.nr_elem; ++i) {
        minel = std::min(minel, array[i]);
    }

    return minel;
}

template<typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
T array_find_min(std::span<const T> array)
{
    return simd::array_find_min<T,VSZ>(array.data(), array.size());
}

} // namespace simd