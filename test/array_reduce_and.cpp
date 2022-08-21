#include "simdlib/simdlib.h"

#include "test_assert.h"

static bool test1_hand()
{
    simd::U64x8 v{0b110'011,0b111'111,0b111'111,0b111'111,0b111'111,0b111'111,0b111'111,0b111'111};

    static_assert(std::is_same_v<uint64_t, simd::value_type<simd::U64x8>::type>);
    static_assert(std::is_same_v<uint64_t, simd::value_type<decltype(v)>::type>);
    static_assert(simd::len<decltype(v)>() == 8);
    static_assert(simd::len(v) == 8);

    simd::u64 r = simd::op::hand(v);
 
    ASSERT(r == 0b110'011, "hand fail %lx vs %lx", r, 0b110'011LU);

    return true;
}

static bool test2_hor()
{
    simd::U64x8 v{0b1,0b11,0b111,0b1111,0b11'111,0b111'111,0b1'111'111,0b11'111'111};

    simd::u64 r = simd::op::hor(v);
 
    ASSERT(r == 0b11'111'111, "hor fail %lx vs %lx", r, 0b11'111'111LU);

    return true;
}

#if !defined(__x86_64__)
static bool test3_hxor()
{
    simd::U64x8 v{0b1,0b11,0b111,0b1111,0b11'111,0b111'111,0b1'111'111,0b11'111'111};

    simd::u64 r = simd::op::hxor(v);
 
    ASSERT(r == 0b1010'1010, "hxor fail %lx vs %lx", r, 0b1010'1010LU);

    return true;
}
#endif

#if 0
static bool test2()
{
    static const std::size_t SIZE = 8*5 + 5;

    std::array<uint64_t, SIZE> array;

    for (std::size_t i = 0; i < SIZE; ++i) {
        array[i] = ~((1ul << (i+1)) - 1);
    }

    uint64_t res = simd::array_reduce_and/*<uint64_t>*/(array);

    ASSERT(res == ~((1ul << SIZE) - 1),
        "fail %lx vs %lx", res, ~((1ul << SIZE) - 1));

    return true;
}
#endif
int main()
{
    ASSERT(test1_hand(), "test1_hand failed");
    ASSERT(test2_hor(), "test2_hor failed");
#if !defined(__x86_64__)
    ASSERT(test3_hxor(), "test3_hxor failed");
#endif

    return 0;
}
