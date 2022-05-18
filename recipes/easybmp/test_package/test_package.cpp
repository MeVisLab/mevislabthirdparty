#include "EasyBMP.h"
#include <iostream>


int main(int argc, char* argv[])
{
    std::cout << "Using EasyBMP Version " << _EasyBMP_Version_ << std::endl;

    SetEasyBMPwarningsOff();

    BMP image;
    image.CreateStandardColorTable();

    return 0;
}
