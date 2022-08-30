#pragma once

namespace simd {

/// Find first element with specified value.
///
///
template<typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
std::optional<std::size_t>
array_find_first(const T val, const T* array, std::size_t nr_elem)
{
    auto ai = array_info<T,VSZ>(nr_elem);
    using VT = decltype(ai)::VT;

    VT vv = val - VT{};

    for (std::size_t i = 0; i < ai.nr_simd; ++i) {
        VT v = ai.load(array,i);
#if 1
        VT found = simd::op::eq(v, vv);
        for (std::size_t j = 0; j < ai.LEN; ++j) {
//printf("-- %lu:%lu: %lu=%lu cmp %lu\n", i, j, res[j], v[j], vv[j]);
            if (found[j] != 0) {
                return i*ai.LEN + j;
            }
        }
#else
        simd::PMask<VT> found = simd::op::eq_mask(v, vv);
        //for (int i=0; i < 16; ++i) printf("%d %u\n", i, (uint8_t)found.mask_[i]);
        //uint64_t bits = mov_p2r(tvx::pmask_t src);
        //if (bits) {
        //    ? = __builtin_ctz(bits);
        //    return ?;
        //}
#endif
    }

    for (std::size_t i = ai.nr_simd*ai.LEN; i < ai.nr_elem; ++i) {
        if (array[i] == val) { return i; }
    }

    return std::nullopt;
}

template<typename T, std::size_t VSZ = simd::arch_default_vsz_bits>
std::optional<std::size_t>
array_find_first(const T val, std::span<const T> array)
{
    return simd::array_find_first<T,VSZ>(val, array.data(), array.size());
}

} // namespace simd