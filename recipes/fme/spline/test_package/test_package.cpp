#include <iostream>
#include <spline.h>

int main(int argc, char* argv[])
{
    if(spline::s_len_trim("abc   ") != 3) {
        return 1;
    }

    spline::timestamp();

    return 0;
}
