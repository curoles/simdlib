#pragma once

namespace simd::op {

template<typename VT>
struct Add {
    using T = simd::value_type<VT>::type;
    Add() = delete;
    static auto d(VT a, VT b) {return simd::op::add(a, b);}
    static auto d(T a, T b) {return a + b;}
};

template<typename VT>
struct Mul {
    using T = simd::value_type<VT>::type;
    Mul() = delete;
    static auto d(VT a, VT b) {return simd::op::mul(a, b);}
    static auto d(T a, T b) {return a * b;}
};

} // namespace simd::op


namespace simd {

template<typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
void arrays_add(std::span<T> dest, std::span<const T> a, std::span<const T> b)
{
    using VT = array_info<T,VSZ>::VT;
    simd::arrays_bop<simd::op::Add<VT>,T,VSZ>(dest, a, b);
}

template<typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
void arrays_mul(std::span<T> dest, std::span<const T> a, std::span<const T> b)
{
    using VT = array_info<T,VSZ>::VT;
    simd::arrays_bop<simd::op::Mul<VT>,T,VSZ>(dest, a, b);
}

} // namespace simd