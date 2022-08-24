#pragma once

namespace simd::op {

/// Aligned memory load.
///
/// Causes segmentation fault if `mem` is not aligned by sizeof(VT).
///
template<typename VT>
VT load(const VT* mem) {
    return *mem;
}

template<typename VT>
VT load_unaligned(const VT* mem) {
    VT v;
    // __builtin_memcpy knows when to use un-aligned load
    // FIXME TODO why is it so slow???
    __builtin_memcpy(&v, mem, sizeof(VT));
    return v;
}

/// Aligned memory store.
///
///
template<typename VT>
void store(VT* mem, VT v) {
    *mem = v;
}

template<typename VT>
VT fill(typename simd::value_type<VT>::type val) {
    return val - VT{};
}

} // namespace simd::op