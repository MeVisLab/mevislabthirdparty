#define CL_TARGET_OPENCL_VERSION 220
#include <CL/opencl.h>

#include <stdlib.h>
#include <stdio.h>

int main() {
    cl_platform_id platform = NULL;
    cl_uint num_platforms = 0;
    cl_device_type device_type = CL_DEVICE_TYPE_ALL;
    cl_int status = CL_SUCCESS;
    cl_image_format image_format = {CL_RGBA, CL_UNORM_INT8};

    if (CL_VERSION_2_2 != 1) {
        puts("Wrong OpenCL header version");
        return EXIT_FAILURE;
    }
    if (sizeof(cl_uint) != 4 || sizeof(cl_ulong) != 8 || sizeof(cl_float) != 4 || sizeof(cl_half) != 2) {
        puts("Unexpected OpenCL type sizes");
        return EXIT_FAILURE;
    }
    if (platform != NULL || num_platforms != 0 || status != CL_SUCCESS) {
        puts("Unexpected initial values");
        return EXIT_FAILURE;
    }
    if (device_type != (CL_DEVICE_TYPE_DEFAULT | CL_DEVICE_TYPE_CPU | CL_DEVICE_TYPE_GPU | CL_DEVICE_TYPE_ACCELERATOR |
                        CL_DEVICE_TYPE_CUSTOM | 0xFFFFFFF0)) {
        puts("Unexpected CL_DEVICE_TYPE_ALL value");
        return EXIT_FAILURE;
    }
    if (image_format.image_channel_order != CL_RGBA || image_format.image_channel_data_type != CL_UNORM_INT8) {
        puts("Unexpected cl_image_format contents");
        return EXIT_FAILURE;
    }
    if (CL_INVALID_VALUE >= 0 || CL_DEVICE_NOT_FOUND >= 0) {
        puts("Unexpected error code signs");
        return EXIT_FAILURE;
    }

    printf("OpenCL headers %d.%d\n", CL_TARGET_OPENCL_VERSION / 100, (CL_TARGET_OPENCL_VERSION / 10) % 10);
    return EXIT_SUCCESS;
}
