#pragma once

namespace simd::op {

// __builtin_memcpy shall know when to use un-aligned load
template<typename VT>
VT load(const VT* mem) {
#if 0
    VT v;
    __builtin_memcpy(&v, mem, sizeof(VT));
    return v;
#else
    return *mem;
#endif
}

//template<typename VT>
//VT load(typename simd::value_type<VT>::type * mem) {
//    VT v;
//    __builtin_memcpy(&v, mem, sizeof(VT));
//    return v;
//}

} // namespace simd::op