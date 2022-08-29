#pragma once

namespace simd::op {

template<typename VT>
auto hmax(VT v) {return tvx::hmax(v)[0];}

template<IsFloatingPoint VT>
auto hmax(VT v) {return tvx::hmax(v)[0];}

template<IsSignedIntegral VT>
auto hmax(VT v) {return tvx::hmaxs(v)[0];}

template<typename VT>
auto hmin(VT v) {return tvx::hmin(v)[0];}

template<IsFloatingPoint VT>
auto hmin(VT v) {return tvx::hmin(v)[0];}

template<IsSignedIntegral VT>
auto hmin(VT v) {return tvx::hmins(v)[0];}

} // namespace simd::op