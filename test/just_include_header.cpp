#include "simdlib/simdlib.h"

#include "test_assert.h"

int main()
{
    simd::make<float,8>::type my_simd_vector;
    static_assert(std::is_same_v<simd::F32x8, decltype(my_simd_vector)>);

    static_assert(std::is_same_v<float, simd::value_type<simd::F32x8>::type>);

    static_assert(simd::len<simd::U32x8>() == 8 and sizeof(simd::U32x8) == (4*8));

    return 0;
}
