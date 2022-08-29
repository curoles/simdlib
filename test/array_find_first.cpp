#include "simdlib/simdlib.h"

#include "test_assert.h"


static bool test1()
{
    static const std::size_t SIZE = 8*5 + 5;

    simd::std_array<uint64_t, SIZE> array;

    for (std::size_t i = 0; i < SIZE; ++i) {
        array[i] = i;
    }

    std::size_t index = simd::array_find_first<uint64_t>(SIZE-1, array).value_or(0);

    ASSERT(index == (SIZE - 1), "fail %lx vs %lx", index, SIZE-1);

    return true;
}

static void __attribute__((noinline)) test2(bool use_simd, std::size_t times)
{
    static const std::size_t SIZE = 1024*1024;

    simd::std_vector<uint64_t> array;
    array.resize(SIZE, 12345);

    array[SIZE-1] = SIZE-1;

    volatile std::size_t found_at_index;

    if (use_simd) {
        for (std::size_t i = 0; i < times; ++i) {
            found_at_index = simd::array_find_first<uint64_t>(SIZE-1, array).value_or(~0ul);
            ASSERT(found_at_index == (SIZE - 1), "fail %lx vs %lx", found_at_index, SIZE-1);
        }
    }
    else {
        for (std::size_t i = 0; i < times; ++i) {
            for (std::size_t j = 0; j < SIZE; ++j) {
                if (array[j] == (SIZE-1)) {found_at_index = j; break;}
            }
            ASSERT(found_at_index == (SIZE - 1), "fail %lx vs %lx", found_at_index, SIZE-1);
        }
    }
}

static void __attribute__((noinline)) do_measure(std::size_t times)
{
    auto t1 = test::benchmark(std::function{test2}, true, times);
    auto t2 = test::benchmark(std::function{test2}, false, times);
    printf("VEC: %lu SCALAR: %lu times: %lu\n", t1.count(), t2.count(), times);
}

int main(int argc, char** argv)
{
    ASSERT(test::check_cpu_simd_support(), "CPU does not have required SIMD support");

    ASSERT(test1(), "test1 failed");

    std::size_t times{1};
    if (argc > 1) {
        times = strtol(argv[1], nullptr, 10);
    }
    do_measure(times);

    return 0;
}
