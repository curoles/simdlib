#pragma once

namespace simd::op {

template<typename VT>
inline VT add(VT a, VT b);

template<>
inline simd::U64x8 add<simd::U64x8>(simd::U64x8 a, simd::U64x8 b) {
    return (simd::U64x8)_mm512_add_epi64((__m512i)a, (__m512i)b);
}

template<>
inline simd::U32x16 add<simd::U32x16>(simd::U32x16 a, simd::U32x16 b) {
    return (simd::U32x16)_mm512_add_epi32((__m512i)a, (__m512i)b);
}

template<>
inline simd::U16x32 add<simd::U16x32>(simd::U16x32 a, simd::U16x32 b) {
    return (simd::U16x32)_mm512_add_epi16((__m512i)a, (__m512i)b);
}

template<>
inline simd::F64x8 add<simd::F64x8>(simd::F64x8 a, simd::F64x8 b) {
    return (simd::F64x8)_mm512_add_pd((__m512d)a, (__m512d)b);
}

template<>
inline simd::F32x16 add<simd::F32x16>(simd::F32x16 a, simd::F32x16 b) {
    return (simd::F32x16)_mm512_add_ps((__m512)a, (__m512)b);
}


template<typename VT>
inline VT mul(VT a, VT b);

template<>
inline simd::U64x8 mul<simd::U64x8>(simd::U64x8 a, simd::U64x8 b) {
    return (simd::U64x8)_mm512_mullo_epi64((__m512i)a, (__m512i)b);
}

template<>
inline simd::U32x16 mul<simd::U32x16>(simd::U32x16 a, simd::U32x16 b) {
    return (simd::U32x16)_mm512_mullo_epi32((__m512i)a, (__m512i)b);
}

template<>
inline simd::U16x32 mul<simd::U16x32>(simd::U16x32 a, simd::U16x32 b) {
    return (simd::U16x32)_mm512_mullo_epi16((__m512i)a, (__m512i)b);
}

template<>
inline simd::F64x8 mul<simd::F64x8>(simd::F64x8 a, simd::F64x8 b) {
    return (simd::F64x8)_mm512_mul_pd((__m512d)a, (__m512d)b);
}

template<>
inline simd::F32x16 mul<simd::F32x16>(simd::F32x16 a, simd::F32x16 b) {
    return (simd::F32x16)_mm512_mul_ps((__m512)a, (__m512)b);
}

} // namespace simd::op