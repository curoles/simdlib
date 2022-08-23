/**@file
 * @brief  Define types that can be elements of SIMD vector.
 * @author Igor Lesik 2022
 */
#pragma once

#include <cstdint>

namespace simd {

using u128 = __uint128_t;
using i128 =  __int128_t;
using u64 = uint64_t;
using i64 =  int64_t;
using u32 = uint32_t;
using i32 =  int32_t;
using u16 = uint16_t;
using i16 =  int16_t;
using u8  = uint8_t;
using i8  =  int8_t;

using f32 = float;
using f64 = double;

//FIXME TODO f16, f8, f4
//using f16 = _Float16;

} // end namespace simd