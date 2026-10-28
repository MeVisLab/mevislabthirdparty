#include <dlpack/dlpack.h>

#include <cstdint>
#include <cstdio>

static int deleterCalls = 0;

static void deleteTensor(DLManagedTensorVersioned *)
{
    ++deleterCalls;
}

int main()
{
    float data[6] = {1, 2, 3, 4, 5, 6};
    int64_t shape[2] = {2, 3};

    DLManagedTensorVersioned managed{};
    managed.version.major = DLPACK_MAJOR_VERSION;
    managed.version.minor = DLPACK_MINOR_VERSION;
    managed.deleter = deleteTensor;
    managed.dl_tensor.data = data;
    managed.dl_tensor.device = DLDevice{kDLCPU, 0};
    managed.dl_tensor.ndim = 2;
    managed.dl_tensor.dtype = DLDataType{kDLFloat, 32, 1};
    managed.dl_tensor.shape = shape;

    const DLTensor &tensor = managed.dl_tensor;
    const float *values = static_cast<const float *>(tensor.data);
    const float last = values[tensor.shape[0] * tensor.shape[1] - 1];
    managed.deleter(&managed);

    if (tensor.dtype.bits / 8 != sizeof(float) || last != 6.0f || deleterCalls != 1)
    {
        std::printf("unexpected tensor state\n");
        return 1;
    }
    std::printf("dlpack %d.%d ok\n", managed.version.major, managed.version.minor);
    return 0;
}
