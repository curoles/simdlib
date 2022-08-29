#pragma once

namespace simd::op {

template<typename VT>
VT eq(VT a, VT b) {return tvx::veq(a, b);}

//template<IsFloatingPoint VT>
//VT eq_quiet(VT a, VT b) {return tvx::veqq(a, b);}

template<IsIntegral VTR, IsFloatingPoint VT>
VTR eq(VT a, VT b) {return tvx::veq_u(a, b);}

//template<typename VT>
//simd::PMask eq_mask(VT a, VT b) {return tvx::veq_XXX?(a, b);}

} // namespace simd::op