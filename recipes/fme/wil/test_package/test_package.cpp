#include <cstdlib>
#include <iostream>
#include <wil/resource.h>


int main(void)
{
    SetLastError(42);
    auto error42 = wil::last_error_context();

    return EXIT_SUCCESS;
}
