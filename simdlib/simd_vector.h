/**@file
 * @brief  SIMD vector types defined with `__attribute__ ((vector_size ...`.
 * @author Igor Lesik 2022
 */
#pragma once

#include <functional>

#include "simdlib/elemtypes.h"

namespace simd {

/// Compile-time SIMD vector type maker.
///
/// Metaprogramming facility to dconstruct SIMD vector type in compile-time.
/// ```c++
/// simd::make<float,8>::type my_simd_vector;
/// static_assert(std::is_same<simd::F32x8, decltype(my_simd_vector)>::value);
/// ```
///
template <typename T, unsigned N> struct make {typedef void type;};


#define SIMD_VEC_ATTR(count, type)  __attribute__ ((vector_size (count*sizeof(type))))

#define DEF_SIMD_VEC(Type,mn,count) \
/** SIMD vector Type[count] */ \
using mn##x##count = Type SIMD_VEC_ATTR(count, Type); \
/** Specialize template make<Type,count>::type */ \
template <> struct make<Type,count> {typedef simd::mn##x##count type;};

#define DEF_SIMD_VEC2(type,mn) DEF_SIMD_VEC(type,mn,2)
#define DEF_SIMD_VEC4(type,mn) DEF_SIMD_VEC(type,mn,4) DEF_SIMD_VEC2(type,mn)
#define DEF_SIMD_VEC8(type,mn) DEF_SIMD_VEC(type,mn,8) DEF_SIMD_VEC4(type,mn)
#define DEF_SIMD_VEC16(type,mn) DEF_SIMD_VEC(type,mn,16) DEF_SIMD_VEC8(type,mn)
#define DEF_SIMD_VEC32(type,mn) DEF_SIMD_VEC(type,mn,32) DEF_SIMD_VEC16(type,mn)
#define DEF_SIMD_VEC64(type,mn) DEF_SIMD_VEC(type,mn,64) DEF_SIMD_VEC32(type,mn)

DEF_SIMD_VEC64(simd::u8,  U8)
DEF_SIMD_VEC64(simd::i8,  I8)
DEF_SIMD_VEC32(simd::u16, U16)
DEF_SIMD_VEC32(simd::i16, I16)
DEF_SIMD_VEC16(simd::u32, U32)
DEF_SIMD_VEC16(simd::i32, I32)
DEF_SIMD_VEC16(simd::f32, F32)
DEF_SIMD_VEC8 (simd::u64, U64)
DEF_SIMD_VEC8 (simd::i64, I64)
DEF_SIMD_VEC8 (simd::f64, F64)
DEF_SIMD_VEC4 (simd::u128,U128)
DEF_SIMD_VEC4 (simd::i128,I128)


#undef SIMD_VEC_ATTR
#undef DEF_SIMD_VEC
#undef DEF_SIMD_VEC2
#undef DEF_SIMD_VEC4
#undef DEF_SIMD_VEC8
#undef DEF_SIMD_VEC16
#undef DEF_SIMD_VEC32
#undef DEF_SIMD_VEC64

/// Get SIMD vector element value type.
///
/// Example:
/// ```c++
/// static_assert(std::is_same_v<float, simd::value_type<simd::F32x8>::type>);
/// ```
///
template <typename T>
struct value_type {
    using type = decltype(((T){})[0]);
};

/// Get SIMD vector length (number of elements).
///
/// Example:
/// ```c++
/// static_assert(simd::len<simd::U32x8>() == 8 and sizeof(simd::U32x8) == (4*8));
/// ```
///
/// Example:
/// ```c++
///    simd::U64x8 v;
///    static_assert(simd::len<decltype(v)>() == 8);
/// ```
template <typename T>
constexpr std::size_t len()
{
    return sizeof(T)/sizeof(typename value_type<T>::type);
}

/// Get SIMD vector length (number of elements).
///
/// Example:
/// ```c++
///    simd::U64x8 v;
///    static_assert(simd::len(v) == 8);
/// ```
template <typename T>
constexpr std::size_t len(T&)
{
    return simd::len<T>();
}

template<typename VT/*, typename... Args*/>
using foreach_fun_t = std::function<void(typename simd::value_type<VT>::type, std::size_t i/*, Args...*/)>;

template<typename VT/*, typename... Args*/>
void foreach(VT v, foreach_fun_t<VT/*,Args...*/> fun/*, Args... args*/)
{
    for (std::size_t i = 0; i < simd::len(v); ++i) {
        fun(v[i], i/*, args...*/);
    }
}

template<typename VT> concept IsIntegral = std::is_integral_v<typename simd::value_type<VT>::type>;
template<typename VT> concept IsSignedIntegral = std::is_integral_v<typename simd::value_type<VT>::type>
                                                && std::is_signed_v<typename simd::value_type<VT>::type>;
template<typename VT> concept IsFloatingPoint = std::is_floating_point_v<typename simd::value_type<VT>::type>;

} // end namespace simd