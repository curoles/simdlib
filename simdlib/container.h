#pragma once

#include <span>

namespace simd { constexpr std::size_t arch_default_vsz_bytes = arch_default_vsz_bits / 8; }
namespace simd { constexpr std::size_t arch_max_vsz_bytes = arch_max_vsz_bits / 8; }

#include "container/array.h"
