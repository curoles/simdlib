#pragma once

namespace simd::op {

template<typename VT>
struct Hand {
    using T = simd::value_type<VT>::type;
    Hand() = delete;
    static auto d(VT v) {return simd::op::hand(v);}
    static auto d(T a, T b) {return a & b;}
};

template<typename VT>
struct Hor {
    using T = simd::value_type<VT>::type;
    Hor() = delete;
    static auto d(VT v) {return simd::op::hor(v);}
    static auto d(T a, T b) {return a | b;}
};

template<typename VT>
struct Hxor {
    using T = simd::value_type<VT>::type;
    Hxor() = delete;
    static auto d(VT v) {return simd::op::hxor(v);}
    static auto d(T a, T b) {return a ^ b;}
};

} // namespace simd::op

namespace simd {

template<typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
auto array_reduce_and(std::span<const T> array, T init)
{
    using VT = array_info<T,VSZ>::VT;
    using Op = simd::op::Hand<VT>;
    return simd::array_reduce<Op,T,VSZ>(array, init);
}

template<typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
auto array_reduce_or(std::span<const T> array, T init)
{
    using VT = array_info<T,VSZ>::VT;
    using Op = simd::op::Hor<VT>;
    return simd::array_reduce<Op,T,VSZ>(array, init);
}

template<typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
auto array_reduce_xor(std::span<const T> array, T init)
{
    using VT = array_info<T,VSZ>::VT;
    using Op = simd::op::Hxor<VT>;
    return simd::array_reduce<Op,T,VSZ>(array, init);
}

} // namespace simd