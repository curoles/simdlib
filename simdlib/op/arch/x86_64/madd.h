#pragma once

namespace simd::op {

template<typename VT>
inline VT madd(VT a, VT b, VT c);

template<>
inline simd::U64x8 madd<simd::U64x8>(simd::U64x8 a, simd::U64x8 b, simd::U64x8 c) {
    return (simd::U64x8)_mm512_madd52lo_epu64((__m512i)c, (__m512i)b, (__m512i)a);
}

//template<>
//inline simd::I32x16 madd<simd::I32x16>(simd::I32x16 a, simd::I32x16 b, simd::I32x16 c) {
//    return (simd::I32x16)_mm512_fmadd_epi32((__m512i)a, (__m512i)b, (__m512i)c);
//}

//template<>
//inline simd::U32x16 add<simd::U32x16>(simd::U32x16 a, simd::U32x16 b) {
//    return (simd::U32x16)_mm512_add_epi32((__m512i)a, (__m512i)b);
//}

//template<>
//inline simd::U16x32 add<simd::U16x32>(simd::U16x32 a, simd::U16x32 b) {
//    return (simd::U16x32)_mm512_add_epi16((__m512i)a, (__m512i)b);
//}

template<>
inline simd::F64x8 madd<simd::F64x8>(simd::F64x8 a, simd::F64x8 b, simd::F64x8 c) {
    return (simd::F64x8)_mm512_fmadd_pd((__m512d)a, (__m512d)b, (__m512d)c);
}

template<>
inline simd::F32x16 madd<simd::F32x16>(simd::F32x16 a, simd::F32x16 b, simd::F32x16 c) {
    return (simd::F32x16)_mm512_fmadd_ps((__m512)a, (__m512)b, (__m512)c);
}

} // namespace simd::op