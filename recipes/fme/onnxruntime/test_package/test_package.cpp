#include <iostream>
#include <onnxruntime/onnxruntime_c_api.h>

int main()
{
    std::cout << OrtGetApiBase()->GetVersionString() << std::endl;
    return 0;
}
