/**@file
 * @brief Macros and functions for testing.
 * @author Igor Lesik 2022
 */
#pragma once

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <limits>
#include <type_traits>
#include <array>
#include <chrono>
#include <functional>

#define STRFY(x) #x

#define ENABLE_ASSERT

#ifdef ENABLE_ASSERT
#define ASSERT(x, fmt, ...) \
    if (!(x)) { \
        fprintf(stderr, "%s:%d:[%s]: %s\n" fmt "\n", \
            __FILE__, __LINE__, __PRETTY_FUNCTION__, STRFY(x), ##__VA_ARGS__); \
        fflush(NULL); \
        abort(); \
  }
#else
#define ASSERT(x, fmt, ...)
#endif

namespace test {

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::fabs(x-y) <= std::numeric_limits<T>::epsilon() * std::fabs(x+y) * ulp
        // unless the result is subnormal
        || std::fabs(x-y) < std::numeric_limits<T>::min();
}

template<typename... Args>
std::chrono::milliseconds benchmark(std::function<void(Args...)> fun, Args... args)
{
    auto startTime = std::chrono::system_clock::now();
    fun(args...);
    auto endTime = std::chrono::system_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    return elapsed;
}

} // end namespace test