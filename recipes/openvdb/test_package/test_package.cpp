#include <openvdb/openvdb.h>
#include <iostream>

int main()
{
    openvdb::initialize();

    openvdb::FloatGrid::Ptr grid = openvdb::FloatGrid::create();
    std::cout << "Testing random access:" << std::endl;

    openvdb::FloatGrid::Accessor accessor = grid->getAccessor();
    openvdb::Coord xyz(1000, -200000000, 30000000);
    accessor.setValue(xyz, 1.0);

    std::cout << "Grid" << xyz << " = " << accessor.getValue(xyz) << std::endl;

    xyz.reset(1000, 200000000, -30000000);

    std::cout << "Grid" << xyz << " = " << accessor.getValue(xyz) << std::endl;

    accessor.setValue(xyz, 2.0);
    accessor.setValue(openvdb::Coord::min(), 3.0f);
    accessor.setValue(openvdb::Coord::max(), 4.0f);

    std::cout << "Testing sequential access:" << std::endl;

    for (openvdb::FloatGrid::ValueOnCIter iter = grid->cbeginValueOn(); iter; ++iter) {
        std::cout << "Grid" << iter.getCoord() << " = " << *iter << std::endl;
    }
}
