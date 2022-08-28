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

#if 0
    //
    // “r” is a GPR “x” is a FPR/VPR and “Yp” is a predicate reg
    //
    // what if I need to specify size of “r” or “x”? like b,h,w,l
    // size will be automagically determined based on the size of the input/output object
    //
    static inline
    ArchMask mov_r2p(uint64_t src)
    {
        ArchMask dst;
        asm("pmov %[d], %[s]"
                : [d] "=Yp" (dst)
                : [s] "r" (src)
                :);
        return dst;
    }

    static inline
    uint64_t mov_p2r(ArchMask src)
    {
        uint64_t dst;
        asm("pmov %[d], %[s]"
                : [d] "=r" (dst)
                : [s] "Yp" (src)
                :);
        return dst;
    }

    ArchMask from_gpr(uint64_t src) {
        mask_ = mov_r2p(src);
        return mask_;
    }
#endif

};

} // namespace simd