#pragma once

namespace simd::op {

#if 0
template<typename VT>
auto hadd(VT v) requires simd::IsIntegral<VT> && (sizeof(VT) == 512/8)
{return v[0];}

template<typename VT>
auto hadd(VT v) requires simd::IsFloatingPoint<VT>
{return v[0];}
#endif

template<typename VT>
inline simd::value_type<VT>::type hadd(VT v);

template<>
inline uint64_t hadd<simd::U64x8>(simd::U64x8 v) {
    return _mm512_reduce_add_epi64((__m512i)v);
}

template<>
inline uint32_t hadd<simd::U32x16>(simd::U32x16 v) {
    return _mm512_reduce_add_epi32((__m512i)v);
}

template<>
inline double hadd<simd::F64x8>(simd::F64x8 v) {
    return _mm512_reduce_add_pd((__m512d)v);
}

template<>
inline float hadd<simd::F32x16>(simd::F32x16 v) {
    return _mm512_reduce_add_ps((__m512)v);
}

//template<>
//inline simd::f16 hadd<simd::F16x32>(simd::F16x32 v) {
//    return _mm512_reduce_add_ph((__m512h)v);
//}

template<typename VT>
inline simd::value_type<VT>::type hmul(VT v);

template<>
inline uint64_t hmul<simd::U64x8>(simd::U64x8 v) {
    return _mm512_reduce_mul_epi64((__m512i)v);
}

template<>
inline uint32_t hmul<simd::U32x16>(simd::U32x16 v) {
    return _mm512_reduce_mul_epi32((__m512i)v);
}

template<>
inline double hmul<simd::F64x8>(simd::F64x8 v) {
    return _mm512_reduce_mul_pd((__m512d)v);
}

template<>
inline float hmul<simd::F32x16>(simd::F32x16 v) {
    return _mm512_reduce_mul_ps((__m512)v);
}

//template<>
//inline simd::f16 hmul<simd::F16x32>(simd::F16x32 v) {
//    return _mm512_reduce_mul_ph((__m512h)v);
//}


} // namespace simd::op