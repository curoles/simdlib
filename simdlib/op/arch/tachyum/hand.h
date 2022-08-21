#pragma once

namespace simd::op {

template<typename VT>
inline auto hand(VT v) {return tvx::hand(v)[0];}

template<typename VT>
inline auto hor(VT v) {return tvx::hor(v)[0];}

template<typename VT>
inline auto hxor(VT v) {return tvx::hxor(v)[0];}

}