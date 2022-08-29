#include "simdlib/simdlib.h"

#include "test_assert.h"


static bool test1_find_max()
{
    static const std::size_t SIZE = 8*5 + 5;

    simd::std_array<uint64_t, SIZE> array;

    for (std::size_t i = 0; i < SIZE; ++i) {
        array[i] = i;
    }

    uint64_t maxval = simd::array_find_max<uint64_t>(array);

    ASSERT(maxval == (SIZE - 1), "fail %lx vs %lx", maxval, SIZE-1);

    return true;
}

static bool test2_find_max()
{
    static const std::size_t SIZE = 8*5 + 5;

    simd::std_array<double, SIZE> array;

    for (std::size_t i = 0; i < SIZE; ++i) {
        array[i] = i;
    }

    double maxval = simd::array_find_max<double>(array);

    ASSERT(maxval == (SIZE - 1), "fail %f vs %lu", maxval, SIZE-1);

    return true;
}

static bool test3_find_max()
{
    static const std::size_t SIZE = 16*5 + 5;

    simd::std_array<int32_t, SIZE> array;

    for (std::size_t i = 0; i < SIZE; ++i) {
        array[i] = -SIZE + i;
    }

    int32_t maxval = simd::array_find_max<int32_t>(array);

    ASSERT(maxval == -1, "fail %d vs %d", maxval, -1);

    return true;
}

static bool test4_find_min()
{
    static const std::size_t SIZE = 8*5 + 5;

    simd::std_array<uint64_t, SIZE> array;

    for (std::size_t i = 0; i < SIZE; ++i) {
        array[i] = i;
    }

    uint64_t minval = simd::array_find_min<uint64_t>(array);

    ASSERT(minval == 0, "fail %lu vs %lu", minval, 0ul);

    return true;
}

static bool test5_find_min()
{
    static const std::size_t SIZE = 8*5 + 5;

    simd::std_array<double, SIZE> array;

    for (std::size_t i = 0; i < SIZE; ++i) {
        array[i] = -SIZE + i;
    }

    double minval = simd::array_find_min<double>(array);

    ASSERT(minval == -SIZE, "fail %f vs %ld", minval, -SIZE);

    return true;
}

static bool test6_find_min()
{
    static const std::size_t SIZE = 16*5 + 5;

    simd::std_array<int32_t, SIZE> array;

    for (std::size_t i = 0; i < SIZE; ++i) {
        array[i] = -SIZE + i;
    }

    int32_t minval = simd::array_find_min<int32_t>(array);

    ASSERT(minval == (int32_t)(-SIZE), "fail %d vs %d", minval, (int32_t)(-SIZE));

    return true;
}

static void __attribute__((noinline)) test_measure(bool use_simd, std::size_t times)
{
    static const std::size_t SIZE = 1024*1024;

    simd::std_vector<uint64_t> array;
    array.resize(SIZE, 12345);

    for (std::size_t j = 0; j < SIZE; ++j) {array[j] = j;}
    array[SIZE-1] = SIZE-1;

    volatile uint64_t maxval{0};

    if (use_simd) {
        #pragma GCC unroll 1
        for (std::size_t i = 0; i < times; ++i) {
            maxval = simd::array_find_max<uint64_t>(array);
            ASSERT(maxval == (SIZE - 1), "fail %lu vs %lu", maxval, SIZE-1);
        }
    }
    else {
        #pragma GCC unroll 1
        for (std::size_t i = 0; i < times; ++i) {
            #pragma GCC unroll 1
            for (std::size_t j = 0; j < SIZE; ++j) {
                if (maxval < array[j]) {maxval = array[j];}
            }
            ASSERT(maxval == (SIZE - 1), "fail %lu vs %lu", maxval, SIZE-1);
        }
    }
}

static void __attribute__((noinline)) do_measure(std::size_t times)
{
    auto t1 = test::benchmark(std::function{test_measure}, true, times);
    auto t2 = test::benchmark(std::function{test_measure}, false, times);
    printf("VEC: %lu SCALAR: %lu times: %lu\n", t1.count(), t2.count(), times);
}

int main(int argc, char** argv)
{
    ASSERT(test::check_cpu_simd_support(), "CPU does not have required SIMD support");

    ASSERT(test1_find_max(), "test1_find_max failed");
    ASSERT(test2_find_max(), "test2_find_max failed");
    ASSERT(test3_find_max(), "test3_find_max failed");
    ASSERT(test4_find_min(), "test4_find_min failed");
    ASSERT(test5_find_min(), "test5_find_min failed");
    ASSERT(test6_find_min(), "test6_find_min failed");

    std::size_t times{1};
    if (argc > 1) {
        times = strtol(argv[1], nullptr, 10);
    }
    do_measure(times);

    return 0;
}
