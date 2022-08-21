#pragma once

#if defined(__tachyum__)
#include <vxintrin.hpp>
#include "op/arch/tachyum/hand.h"
#elif defined(__x86_64__)
#include <immintrin.h>
#include "op/arch/x86_64/hand.h"
#else
#error Unknown CPU architecture
#endif