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

static bool test5_fill()
{
    simd::std_array<uint64_t, 8+2> array{1,2,3,4,5,6,7,8,9,10};

    uint64_t val{777ul};
    simd::array_fill<decltype(array)::value_type>(array, val);

    for (auto v : array) {
        ASSERT(v == val, "%lu vs expected %lu", v, val);
    }

    return true;
}

int main(/*int argc, char** argv*/)
{
    ASSERT(test1_hadd(), "test1_hadd failed");
    ASSERT(test2_hadd(), "test2_hadd failed");
    ASSERT(test3_hmul(), "test3_hmul failed");
    ASSERT(test4_hmul(), "test4_hmul failed");
    ASSERT(test5_fill(), "test5_fill failed");

    return 0;
}
