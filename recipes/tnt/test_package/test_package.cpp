#include <tnt.h>
#include <iostream>

class Test: public TNT::Matrix<float>
{
    using Matrix<float>::Matrix;
};

int main()
{
    Test t { 4, 3, 0.5f };
    return t.size() == 12 ? 0 : 1;
}
