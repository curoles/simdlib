#pragma once

namespace simd::op {

/// Aligned memory load with mask.
///
/// Causes segmentation fault if `mem` is not aligned by sizeof(VT).
///
template<typename VT>
VT load(const typename simd::value_type<VT>::type* mem, simd::PMask<VT> mask) {
    return tvx::vld(mask(), (VT*)mem);
}

/// Aligned memory store with mask.
///
///
template<typename VT>
void store(typename simd::value_type<VT>::type* mem, VT v, simd::PMask<VT> mask) {
    tvx::vst((VT*)mem, mask, v);
}

} // namespace simd::op