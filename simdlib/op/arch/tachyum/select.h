#pragma once

namespace simd::op {

// `Dest[i] = mask[i]? a[i] : b[i];`
template<typename VT>
VT select(VT a, VT b, simd::PMask<VT> mask) {
    return tvx::vsel(mask, a, b);
}



} // namespace simd::op