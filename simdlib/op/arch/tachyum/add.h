#pragma once

namespace simd::op {

template<typename VT>
VT add(VT a, VT b) {return tvx::vadd(a, b);}

template<typename VT>
VT mul(VT a, VT b) {return tvx::vmul(a, b);}

} // namespace simd::op