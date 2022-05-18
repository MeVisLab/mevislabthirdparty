#include <itkImage.h>

int main(int, char *[])
{
    using ImageType = itk::Image<unsigned short, 3>;
    ImageType::Pointer image = ImageType::New();

    ImageType::IndexType start;
    start[0] = 0;
    start[1] = 0;
    start[2] = 0;

    ImageType::SizeType size;
    size[0] = 200;
    size[1] = 200;
    size[2] = 200;

    ImageType::RegionType region;

    region.SetSize(size);
    region.SetIndex(start);

    image->SetRegions(region);
    image->Allocate();

    return EXIT_SUCCESS;
}
