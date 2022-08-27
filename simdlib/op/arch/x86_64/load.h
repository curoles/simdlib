#pragma once

namespace simd::op {

/// Aligned memory load with mask.
///
/// Causes segmentation fault if `mem` is not aligned by sizeof(VT).
///
template<typename VT>
VT load(const typename simd::value_type<VT>::type* mem, simd::PMask<VT> mask) {
    VT v{};
    if constexpr(sizeof(VT)==512/8) {
        if constexpr(simd::len<VT>()==8)       return (VT)_mm512_mask_load_epi64((__m512i)v, mask(), (VT*)mem);
        else if constexpr(simd::len<VT>()==16) return (VT)_mm512_mask_load_epi32((__m512i)v, mask(), (VT*)mem);
        else if constexpr(simd::len<VT>()==32) return (VT)_mm512_mask_loadu_epi16((__m512i)v, mask(), (VT*)mem);
        else if constexpr(simd::len<VT>()==64) return (VT)_mm512_mask_loadu_epi8((__m512i)v, mask(), (VT*)mem);
    }
}

/// Aligned memory store with mask.
///
///
template<typename VT>
void store(typename simd::value_type<VT>::type* mem, VT v, simd::PMask<VT> mask) {
    if constexpr(sizeof(VT)==512/8) {
        if constexpr(simd::len<VT>()==8)       _mm512_mask_store_epi64(mem, mask(), (__m512i)v);
        else if constexpr(simd::len<VT>()==16) _mm512_mask_store_epi32(mem, mask(), (__m512i)v);
        else if constexpr(simd::len<VT>()==32) _mm512_mask_store_epi16(mem, mask(), (__m512i)v);
        else if constexpr(simd::len<VT>()==64) _mm512_mask_store_epi8(mem, mask(), (__m512i)v);
    }
}

} // namespace simd::op