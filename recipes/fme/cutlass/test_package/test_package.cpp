#include <cute/layout.hpp>
#include <cute/util/print.hpp>

#include <cutlass/layout/matrix.h>
#include <cutlass/version.h>

#include <iostream>

int main()
{
    using namespace cute;

    int M = 3;
    int N = 4;
    auto shape = make_shape(M, N);

    auto layoutCol = make_layout(shape, LayoutLeft{});
    auto layoutRow = make_layout(shape, LayoutRight{});
    auto strideCol = stride(layoutCol);
    auto strideRow = stride(layoutRow);

    std::cout << "CUTLASS version: " << cutlass::getVersionMajor() << "."
              << cutlass::getVersionMinor() << "." << cutlass::getVersionPatch() << std::endl;
}
