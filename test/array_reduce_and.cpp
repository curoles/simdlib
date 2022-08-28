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

static bool test4_hxor()
{
    static const std::size_t SIZE = 8*5 + 5;

    simd::std_array<uint64_t, SIZE> array;

    for (std::size_t i = 0; i < SIZE; ++i) {
        array[i] = (1ul << i);
    }

    uint64_t res = simd::array_reduce_xor<uint64_t>(array, 0ul);

    ASSERT(res == ((1ul << SIZE) - 1),
        "fail %lx vs %lx", res, ((1ul << SIZE) - 1));

    return true;
}
#endif

static bool test5_hand()
{
    static const std::size_t SIZE = 8*5 + 5;

    alignas(simd::arch_default_vsz_bytes)
    std::array<uint64_t, SIZE> array;

    for (std::size_t i = 0; i < SIZE; ++i) {
        array[i] = ~((1ul << (i+1)) - 1);
    }

    //uint64_t res = simd::array_reduce<simd::op::Hand<simd::U64x8>, uint64_t >(array, ~0ul);
    uint64_t res = simd::array_reduce_and<uint64_t>(array, ~0ul);

    ASSERT(res == ~((1ul << SIZE) - 1),
        "fail %lx vs %lx", res, ~((1ul << SIZE) - 1));

    return true;
}

static bool test6_hor()
{
    static const std::size_t SIZE = 8*5 + 5;

    simd::std_array<uint64_t, SIZE> array;

    for (std::size_t i = 0; i < SIZE; ++i) {
        array[i] = (1ul << i);
    }

    uint64_t res = simd::array_reduce_or<uint64_t>(array, 0ul);

    ASSERT(res == ((1ul << SIZE) - 1),
        "fail %lx vs %lx", res, ((1ul << SIZE) - 1));

    return true;
}

static void __attribute__((noinline)) test15_hand(bool use_simd, std::size_t times)
{
    static const std::size_t SIZE = 1024*10;

    //alignas(simd::arch_default_vsz_bytes)
    //std::array<uint64_t, SIZE> array;
    simd::std_array<uint64_t, SIZE> array;

    volatile uint64_t res = ~0ul;

    if (use_simd) {
        for (std::size_t i = 0; i < times; ++i) {
            res = res & simd::array_reduce_and<uint64_t>(array, ~0ul);
        }
    }
    else {
        for (std::size_t i = 0; i < times; ++i) {
            for (std::size_t j = 0; j < SIZE; ++j) {
                res = res & array[j];
            }
        }
    }
}

static void __attribute__((noinline)) test16_hand(bool use_simd, std::size_t times)
{
    static const std::size_t SIZE = 1024*1024;

    //std::vector<uint64_t, simd::aligned_allocator<uint64_t> > array;
    simd::std_vector<uint64_t> array;
    array.resize(SIZE, ~0ul);

    volatile uint64_t res = ~0ul;

    if (use_simd) {
        for (std::size_t i = 0; i < times; ++i) {
            res = res & simd::array_reduce_and<uint64_t>(array, ~0ul);
        }
    }
    else {
        for (std::size_t i = 0; i < times; ++i) {
            for (std::size_t j = 0; j < SIZE; ++j) {
                res = res & array[j];
            }
        }
    }
}

static void __attribute__((noinline)) do_measure1(std::size_t times)
{
    auto t1 = test::benchmark(std::function{test15_hand}, true, times);
    auto t2 = test::benchmark(std::function{test15_hand}, false, times);
    printf("std::array VEC: %lu SCALAR: %lu times: %lu\n", t1.count(), t2.count(), times);
}

static void __attribute__((noinline)) do_measure2(std::size_t times)
{
    auto t1 = test::benchmark(std::function{test16_hand}, true, times);
    auto t2 = test::benchmark(std::function{test16_hand}, false, times);
    printf("std::vector VEC: %lu SCALAR: %lu times: %lu\n", t1.count(), t2.count(), times);
}

int main(int argc, char** argv)
{
    ASSERT(test::check_cpu_simd_support(), "CPU does not have required SIMD support");

    ASSERT(test1_hand(), "test1_hand failed");
    ASSERT(test2_hor(), "test2_hor failed");
#if !defined(__x86_64__)
    ASSERT(test3_hxor(), "test3_hxor failed");
    ASSERT(test4_hxor(), "test4_hxor failed");
#endif
    ASSERT(test5_hand(), "test5_hand failed");
    ASSERT(test6_hor(), "test6_hor failed");

    std::size_t times{1};
    if (argc > 1) {
        times = strtol(argv[1], nullptr, 10);
    }
    do_measure1(times * 100);
    do_measure2(times);

    return 0;
}
