#include <iostream>
#include <memory>
#include <string>
#include <xylib/xylib.h>

int main()
{
    std::cout << "xylib version: " << xylib_get_version() << std::endl;

    const std::string text = "1.0 10.5\n2.0 20.5\n3.0 30.5\n";
    std::unique_ptr<xylib::DataSet> dataset(xylib::load_string(text, "text"));
    if (!dataset || dataset->get_block_count() != 1)
    {
        std::cerr << "expected one block" << std::endl;
        return 1;
    }

    const xylib::Block *block = dataset->get_block(0);
    if (block->get_column_count() != 2 || block->get_point_count() != 3)
    {
        std::cerr << "unexpected block shape: " << block->get_column_count() << "x"
                  << block->get_point_count() << std::endl;
        return 1;
    }

    const double x = block->get_column(1).get_value(2);
    const double y = block->get_column(2).get_value(2);
    if (x != 3.0 || y != 30.5)
    {
        std::cerr << "unexpected values: " << x << " " << y << std::endl;
        return 1;
    }
    std::cout << "parsed " << block->get_point_count() << " points" << std::endl;
    return 0;
}
