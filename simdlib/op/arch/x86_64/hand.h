#pragma once

namespace simd::op {

template<typename VT>
inline simd::value_type<VT>::type hand(VT v);

template<typename VT>
inline simd::value_type<VT>::type hor(VT v);

template<typename VT>
inline simd::value_type<VT>::type hxor(VT v);

template<>
inline uint64_t hand<simd::U64x8>(simd::U64x8 v) {
    return _mm512_reduce_and_epi64((__m512i)v);
}

template<>
inline uint32_t hand<simd::U32x16>(simd::U32x16 v) {
    return _mm512_reduce_and_epi32((__m512i)v);
}

template<>
inline uint64_t hor<simd::U64x8>(simd::U64x8 v) {
    return _mm512_reduce_or_epi64((__m512i)v);
}

template<>
inline uint32_t hor<simd::U32x16>(simd::U32x16 v) {
    return _mm512_reduce_or_epi32((__m512i)v);
}


}