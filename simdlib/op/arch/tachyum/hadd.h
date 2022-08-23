#pragma once

namespace simd::op {

template<typename VT>
auto hadd(VT v) {return tvx::hsum(v)[0];}

template<IsFloatingPoint VT>
auto hadd(VT v) {return tvx::hsumso(v)[0];}

template<typename VT>
auto hmul(VT v) {return tvx::hprod(v)[0];}

template<IsFloatingPoint VT>
auto hmul(VT v) {return tvx::hprodso(v)[0];}

} // namespace simd::op