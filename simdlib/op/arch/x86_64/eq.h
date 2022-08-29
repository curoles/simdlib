#pragma once

namespace simd::op {

template<typename VT>
VT eq(VT a, VT b);

template<>
inline simd::U64x8 eq<simd::U64x8>(simd::U64x8 a, simd::U64x8 b) {
    __mmask8 mask = _mm512_cmpeq_epi64_mask ((__m512i)a, (__m512i)b);
    return (simd::U64x8)_mm512_mask_blend_epi64(mask, (__m512i)(0 - simd::U64x8{}), (__m512i)(1 - simd::U64x8{}));
}

template<>
inline simd::U32x16 eq<simd::U32x16>(simd::U32x16 a, simd::U32x16 b) {
    __mmask16 mask = _mm512_cmpeq_epi32_mask ((__m512i)a, (__m512i)b);
    return (simd::U32x16)_mm512_mask_blend_epi32(mask, (__m512i)(0 - simd::U32x16{}), (__m512i)(1 - simd::U32x16{}));
}


} // namespace simd::op