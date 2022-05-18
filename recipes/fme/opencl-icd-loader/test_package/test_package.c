#define CL_TARGET_OPENCL_VERSION 220
#include <CL/opencl.h>

int main() {
  cl_uint platformCount;
  clGetPlatformIDs(0, NULL, &platformCount);
  return 0;
}
