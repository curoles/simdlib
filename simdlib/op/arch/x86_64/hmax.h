#pragma once

namespace simd::op {

template<typename VT>
inline simd::value_type<VT>::type hmax(VT v);

template<>
inline uint64_t hmax<simd::U64x8>(simd::U64x8 v) {
    return _mm512_reduce_max_epu64((__m512i)v);
}

template<>
inline int64_t hmax<simd::I64x8>(simd::I64x8 v) {
    return _mm512_reduce_max_epi64((__m512i)v);
}

template<>
inline uint32_t hmax<simd::U32x16>(simd::U32x16 v) {
    return _mm512_reduce_max_epu32((__m512i)v);
}

template<>
inline int32_t hmax<simd::I32x16>(simd::I32x16 v) {
    return _mm512_reduce_max_epi32((__m512i)v);
}

template<>
inline double hmax<simd::F64x8>(simd::F64x8 v) {
    return _mm512_reduce_max_pd((__m512d)v);
}

template<>
inline float hmax<simd::F32x16>(simd::F32x16 v) {
    return _mm512_reduce_max_ps((__m512)v);
}

template<typename VT>
inline simd::value_type<VT>::type hmin(VT v);

template<>
inline uint64_t hmin<simd::U64x8>(simd::U64x8 v) {
    return _mm512_reduce_min_epu64((__m512i)v);
}

template<>
inline int64_t hmin<simd::I64x8>(simd::I64x8 v) {
    return _mm512_reduce_min_epi64((__m512i)v);
}

template<>
inline uint32_t hmin<simd::U32x16>(simd::U32x16 v) {
    return _mm512_reduce_min_epu32((__m512i)v);
}

template<>
inline int32_t hmin<simd::I32x16>(simd::I32x16 v) {
    return _mm512_reduce_min_epi32((__m512i)v);
}

template<>
inline double hmin<simd::F64x8>(simd::F64x8 v) {
    return _mm512_reduce_min_pd((__m512d)v);
}

template<>
inline float hmin<simd::F32x16>(simd::F32x16 v) {
    return _mm512_reduce_min_ps((__m512)v);
}

} // namespace simd::op