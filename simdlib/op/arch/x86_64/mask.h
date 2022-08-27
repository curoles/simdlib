#pragma once

namespace simd {

/// SIMD Predicate Mask.
///
template<typename VT, std::size_t VSZ = simd::arch_default_vsz_bits>
class PMask
{
public:
    union ArchMask {
        uint8_t m8;
        uint16_t m16;
        uint32_t m32;
        uint64_t m64;
    };

    ArchMask mask_;

    auto operator()() const {
        if constexpr(simd::len<VT>() == 8) return mask_.m8;
        else if constexpr(simd::len<VT>() == 16) return mask_.m16;
        else if constexpr(simd::len<VT>() == 32) return mask_.m32;
        else if constexpr(simd::len<VT>() == 64) return mask_.m64;
    }

    PMask set_first_n(unsigned int n) {
        mask_.m64 = (1ul << n) - 1;
        return *this;
    }

    static inline PMask make_set_first_n(unsigned int n) {
        PMask m;
        return m.set_first_n(n);
    }
};

} // namespace simd