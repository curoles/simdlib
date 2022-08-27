#pragma once

namespace simd {

/// SIMD Predicate Mask.
///
template<typename VT, std::size_t VSZ = simd::arch_default_vsz_bits>
class PMask
{
public:
    using ArchMask = __mask_t;

    ArchMask mask_;

    operator ArchMask() const { return mask_; }

    ArchMask operator()() const { return mask_; }

    PMask set_first_n(unsigned int n) {
        mask_ = _pmask(n);
        return *this;
    }

    static inline PMask make_set_first_n(unsigned int n) {
        PMask m;
        return m.set_first_n(n * 8/*FIXME calculate shift based on VLEN*/);
    }
};

} // namespace simd