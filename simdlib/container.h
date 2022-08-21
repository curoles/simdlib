#pragma once

#include <span>

#if defined(__tachyum__)
namespace simd { constexpr std::size_t arch_default_vsz_bits = 512; }
#elif defined(__x86_64__)
namespace simd { constexpr std::size_t arch_default_vsz_bits = 512; }
#else
#error Unknown CPU architecture
#endif

namespace simd { constexpr std::size_t arch_default_vsz_bytes = arch_default_vsz_bits / 8; }

#include "container/array.h"