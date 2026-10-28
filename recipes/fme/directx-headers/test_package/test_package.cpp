#include <directx/d3d12.h>
#include <dxguids/dxguids.h>

#include <cstdio>

int main()
{
    if (!IsEqualGUID(IID_ID3D12Device, __uuidof(ID3D12Device)))
    {
        std::fprintf(stderr, "IID_ID3D12Device does not match __uuidof(ID3D12Device)\n");
        return 1;
    }
    if (IsEqualGUID(IID_ID3D12Device, IID_ID3D12CommandQueue))
    {
        std::fprintf(stderr, "distinct interfaces share a GUID\n");
        return 1;
    }
    D3D12_FEATURE_DATA_D3D12_OPTIONS options = {};
    if (options.TiledResourcesTier != D3D12_TILED_RESOURCES_TIER_NOT_SUPPORTED ||
        D3D12_FEATURE_D3D12_OPTIONS != static_cast<D3D12_FEATURE>(0))
    {
        std::fprintf(stderr, "unexpected D3D12 enum values\n");
        return 1;
    }
    std::printf("DirectX headers: D3D12_SDK_VERSION %u\n",
                static_cast<unsigned>(D3D12_SDK_VERSION));
    return 0;
}
