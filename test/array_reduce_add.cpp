#include "simdlib/simdlib.h"

#include "test_assert.h"

static bool test1_hadd()
{
    simd::U64x8 v{1,2,3,4,5,6,7,8};

    simd::u64 r = simd::op::hadd(v);
 
    ASSERT(r == 9*4, "hadd fail %lu vs %lu", r, 9LU * 4);

    return true;
}

static bool test2_hadd()
{
    simd::F64x8 v{1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8};

    double sum{0.0};
    for (std::size_t i = 0; i < simd::len(v); ++i) {sum += v[i];}

    simd::f64 r = simd::op::hadd(v);
 
    ASSERT(r == sum, "hadd fail %f vs %f", r, sum);

    return true;
}

static bool test3_hmul()
{
    simd::U64x8 v{1,2,3,4,5,6,7,8};

    uint64_t product{1};
    for (std::size_t i = 0; i < simd::len(v); ++i) {product *= v[i];}

    simd::u64 r = simd::op::hmul(v);
 
    ASSERT(r == product, "hmul fail %lu vs %lu", r, product);

    return true;
}

static bool test4_hmul()
{
    simd::F64x8 v{1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8};

    double product{1.0};
    //for (std::size_t i = 0; i < simd::len(v); ++i) {product *= v[i];}
    simd::foreach(v, [&product](double vv, std::size_t){product *= vv;});

    simd::f64 r = simd::op::hmul(v);
 
    ASSERT(r == product, "hmul fail %f vs %f", r, product);

    return true;
}

static bool test5_load()
{
    simd::U64x8 v{9, 10, 11, 12, 13, 14, 15, 16};
    alignas(simd::arch_max_vsz_bytes) uint64_t a[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    v = simd::op::load<simd::U64x8>(a, simd::PMask<simd::U64x8>::make_set_first_n(6));
 
    for (uint8_t i = 0; i < 6; ++i) {
        //printf("load [%i] %lu vs %lu\n", i, v[i], a[i]);
        ASSERT(v[i] == a[i], "load [%i] fail %lu vs %lu", i, v[i], a[i]);
    }

    //ASSERT(v[6] == 15, "load fail [%i] %lu vs %lu", 6, v[6], 15ul);
    //ASSERT(v[7] == 16, "load fail [%i] %lu vs %lu", 7, v[7], 16ul);

    return true;
}

static bool test6_store()
{
    simd::U64x8 v{9, 10, 11, 12, 13, 14, 15, 16};
    alignas(simd::arch_max_vsz_bytes) uint64_t a[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    simd::op::store(a, v, simd::PMask<simd::U64x8>::make_set_first_n(6));
 
    for (uint8_t i = 0; i < 6; ++i) {
        //printf("store [%i] %lu vs %lu\n", i, v[i], a[i]);
        ASSERT(v[i] == a[i], "store [%i] fail %lu vs %lu", i, v[i], a[i]);
    }

    return true;
}

static bool test7_fill()
{
    simd::std_array<uint64_t, 8+2> array{1,2,3,4,5,6,7,8,9,10};

    uint64_t val{777ul};
    simd::array_fill<decltype(array)::value_type>(array, val);

    for (auto v : array) {
        ASSERT(v == val, "%lu vs expected %lu", v, val);
    }

    return true;
}

static bool test8_hadd()
{
    static const std::size_t SIZE = 8*5 + 5;

    simd::std_array<uint64_t, SIZE> array;

    uint64_t sum{0};
    for (std::size_t i = 0; i < SIZE; ++i) {
        array[i] = i;
        sum += array[i];
    }

    uint64_t res = simd::array_reduce_add<uint64_t>(array, 0ul);

    ASSERT(res == sum, "fail %lx vs %lx", res, sum);

    return true;
}

static bool test9_hmul()
{
    static const std::size_t SIZE = 8*5 + 5;

    simd::std_array<uint64_t, SIZE> array;

    uint64_t product{1};
    for (std::size_t i = 0; i < SIZE; ++i) {
        array[i] = i;
        product *= array[i];
    }

    uint64_t res = simd::array_reduce_mul<uint64_t>(array, 1ul);

    ASSERT(res == product, "fail %lx vs %lx", res, product);

    return true;
}

int main(/*int argc, char** argv*/)
{
    ASSERT(test::check_cpu_simd_support(), "CPU does not have required SIMD support");

    ASSERT(test1_hadd(), "test1_hadd failed");
    ASSERT(test2_hadd(), "test2_hadd failed");
    ASSERT(test3_hmul(), "test3_hmul failed");
    ASSERT(test4_hmul(), "test4_hmul failed");
    ASSERT(test5_load(), "test5_load failed");
    ASSERT(test6_store(), "test6_store failed");
    ASSERT(test7_fill(), "test7_fill failed");
    ASSERT(test8_hadd(), "test8_hadd failed");
    ASSERT(test9_hmul(), "test9_hmul failed");

    return 0;
}
