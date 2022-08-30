#pragma once

namespace simd::op {

template<typename VT>
struct Madd {
    using T = simd::value_type<VT>::type;
    Madd() = delete;
    static auto d(VT a, VT b, VT c) {return simd::op::madd(a, b, c);}
    static auto d(T a, T b, T c) {return (a * b) + c;}
};

} // namespace simd::op


namespace simd {

template<typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
void arrays_madd(std::span<T> dest, std::span<const T> a, std::span<const T> b, std::span<const T> c)
{
    using VT = array_info<T,VSZ>::VT;
    simd::arrays_top<simd::op::Madd<VT>,T,VSZ>(dest, a, b, c);
}

} // namespace simd