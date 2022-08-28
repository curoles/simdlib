#include "simdlib/simdlib.h"

#include "test_assert.h"

static bool test1_add()
{
    static const std::size_t SIZE = 8*5 + 5;

    simd::std_array<uint64_t, SIZE> array;

    for (std::size_t i = 0; i < SIZE; ++i) {
        array[i] = i;
    }

    simd::std_array<uint64_t, SIZE> res;
    simd::arrays_add<uint64_t>(res, array, array);

    for (std::size_t i = 0; i < SIZE; ++i) {
        ASSERT(res[i] == (array[i] + array[i]), "fail %lx vs %lx", res[i], (array[i] + array[i]));
    }

    return true;
}

static bool test2_mul()
{
    static const std::size_t SIZE = 8*5 + 5;

    simd::std_array<uint64_t, SIZE> array;

    for (std::size_t i = 0; i < SIZE; ++i) {
        array[i] = i;
    }

    simd::std_array<uint64_t, SIZE> res;
    simd::arrays_mul<uint64_t>(res, array, array);

    for (std::size_t i = 0; i < SIZE; ++i) {
        ASSERT(res[i] == (array[i] * array[i]), "fail %lx vs %lx", res[i], (array[i] * array[i]));
    }

    return true;
}

int main(/*int argc, char** argv*/)
{
    ASSERT(test::check_cpu_simd_support(), "CPU does not have required SIMD support");

    ASSERT(test1_add(), "test1_add failed");
    ASSERT(test2_mul(), "test2_mul failed");

    return 0;
}