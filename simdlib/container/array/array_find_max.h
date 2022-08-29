#pragma once

namespace simd::op {

template<typename VT>
struct Hmax {
    using T = simd::value_type<VT>::type;
    Hmax() = delete;
    static auto d(VT v) {return simd::op::hmax(v);}
    static auto d(T a, T b) {return std::max(a, b);}
};

template<typename VT>
struct Hmin {
    using T = simd::value_type<VT>::type;
    Hmin() = delete;
    static auto d(VT v) {return simd::op::hmin(v);}
    static auto d(T a, T b) {return std::min(a, b);}
};

} // namespace simd::op

namespace simd {

/// In array find element with maximum value.
///
///
template<typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
auto array_find_max(std::span<const T> array)
{
    using VT = array_info<T,VSZ>::VT;
    using Op = simd::op::Hmax<VT>;
    return simd::array_reduce<Op,T,VSZ>(array, array[0]);
}

/// In array find element with minimum value.
///
///
template<typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
auto array_find_min(std::span<const T> array)
{
    using VT = array_info<T,VSZ>::VT;
    using Op = simd::op::Hmin<VT>;
    return simd::array_reduce<Op,T,VSZ>(array, array[0]);
}

} // namespace simd
