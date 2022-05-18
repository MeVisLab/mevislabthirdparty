
#include <iostream>

#include <vigra/multi_array.hxx>
#include <vigra/impex.hxx>
#include <vigra/random_forest.hxx>

using namespace vigra;

int main(int argc, char **argv)
{
    try
    {
        ImageImportInfo info(argv[1]);

        if(info.isGrayscale()) {
            MultiArray<2, UInt8> in(info.width(), info.height());
            importImage(info, in);
        }
        else {
            MultiArray<2, RGBValue<UInt8> > in(info.width(), info.height());
            importImage(info, in);
        }
    }
    catch (std::exception & e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

#ifndef HasHDF5
    std::cout << "HasHDF5 is not defined!" << std::endl;
    return 1;
#endif

    try
    {
        ::vigra::rf::algorithms::HClustering hc;
        // check that HDF5 can be used:
        hc.save("test.txt", "prefix");
    }
    catch (std::exception & e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
