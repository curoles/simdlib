#pragma once

#include "op/load.h"

#if defined(__tachyum__)
#include <vxintrin.hpp>
namespace simd { constexpr std::size_t arch_default_vsz_bits = 512; }
namespace simd { constexpr std::size_t arch_max_vsz_bits = 512; }
#include "op/arch/tachyum/mask.h"
#include "op/arch/tachyum/load.h"
#include "op/arch/tachyum/hand.h"
#include "op/arch/tachyum/hadd.h"
#include "op/arch/tachyum/hmax.h"
#include "op/arch/tachyum/select.h"
#include "op/arch/tachyum/add.h"
#include "op/arch/tachyum/eq.h"
#include "op/arch/tachyum/mx/madd.h"
#elif defined(__x86_64__)
#include <immintrin.h>
namespace simd { constexpr std::size_t arch_default_vsz_bits = 512; }
namespace simd { constexpr std::size_t arch_max_vsz_bits = 512; }
#include "op/arch/x86_64/mask.h"
#include "op/arch/x86_64/load.h"
#include "op/arch/x86_64/hand.h"
#include "op/arch/x86_64/hadd.h"
#include "op/arch/x86_64/hmax.h"
#include "op/arch/x86_64/add.h"
#include "op/arch/x86_64/madd.h"
#include "op/arch/x86_64/eq.h"
#else
#error Unknown CPU architecture
#endif
