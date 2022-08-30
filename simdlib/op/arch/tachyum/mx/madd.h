#pragma once

namespace simd::op::mx {

//template<typename VT>
//using columnType = VT;

/// DEST <- SRC1 * SRC2^T + SRC3
/// [8x8xI32] <- [8x32xI8] * [8x32xI8]^T + [8x8xI32] (2k <- 2k * 2k + 2k)
template<typename VT>
VT madd(VT a, VT b, VT c) {
    //return tvx::mmadd(a, b, c);
    VT d;
    asm("mmadd %v0, %v1, %v2, %v3"
            : "x" (d)
            : "x" (a)
            , "x" (b)
            , "x" (c)
            :);
    return d;
}


} // namespace simd::op