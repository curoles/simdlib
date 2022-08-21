#pragma once

#if defined(__tachyum__)
#include <vxintrin.hpp>
#include "op/arch/tachyum/hand.h"
#elif defined(__x86_64__)
#include <immintrin.h>
#include "op/arch/x86_64/hand.h"
#else
#error Unknown CPU architecture
#endif

namespace simd::op {

template<typename VT>
struct Hand {
    using T = simd::value_type<VT>::type;
    Hand() = delete;
    static auto d(VT v) {return simd::op::hand(v);}
    static auto d(T a, T b) {return a & b;}
};

}