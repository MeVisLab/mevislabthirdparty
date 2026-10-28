#include <cuda_bf16.h>
#include <deep_gemm/common/math.cuh>
#include <deep_gemm/common/types.cuh>
#include <deep_gemm/impls/sm90_fp8_gemm_1d2d.cuh>

#include <cstdio>

int main()
{
    static_assert(deep_gemm::math::constexpr_ceil_div(10u, 4u) == 3u, "constexpr_ceil_div");
    static_assert(deep_gemm::math::constexpr_align(10u, 4u) == 12u, "constexpr_align");
    static_assert(deep_gemm::math::constexpr_gcd(12u, 18u) == 6u, "constexpr_gcd");
    static_assert(deep_gemm::is_m_grouped_contiguous(deep_gemm::GemmType::MGroupedContiguous),
                  "m grouped");
    static_assert(!deep_gemm::is_m_grouped_contiguous(deep_gemm::GemmType::Normal),
                  "not m grouped");
    static_assert(deep_gemm::get_element_size(deep_gemm::MmaKind::BF16) == 2, "bf16 element size");

    const unsigned blocks = deep_gemm::math::ceil_div(1000u, 128u);
    const unsigned aligned = deep_gemm::math::align(1000u, 128u);
    if (blocks != 8u || aligned != 1024u)
    {
        std::fprintf(stderr, "unexpected math results %u %u\n", blocks, aligned);
        return 1;
    }
    std::printf("deep_gemm host helpers: %u blocks, aligned to %u\n", blocks, aligned);
    return 0;
}
