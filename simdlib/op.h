#pragma once

#include "op/load.h"

#if defined(__tachyum__)
#include <vxintrin.hpp>
#include "op/arch/tachyum/hand.h"
#include "op/arch/tachyum/hadd.h"
#elif defined(__x86_64__)
#include <immintrin.h>
#include "op/arch/x86_64/hand.h"
#include "op/arch/x86_64/hadd.h"
#else
#error Unknown CPU architecture
#endif
