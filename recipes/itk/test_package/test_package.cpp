#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkMedianImageFilter.h>
#include <itkMetaImageIOFactory.h>
#include <itkNrrdImageIOFactory.h>
#include <itkPNGImageIOFactory.h>

#include <iostream>
#include <string>

namespace
{
    using ImageType2D = itk::Image<unsigned char, 2>;

    ImageType2D::Pointer createTestImage()
    {
        ImageType2D::Pointer image = ImageType2D::New();
        ImageType2D::RegionType region;
        region.SetSize({{16, 16}});
        image->SetRegions(region);
        image->Allocate(true);
        image->SetPixel({{8, 8}}, 200);
        image->SetPixel({{2, 3}}, 50);
        return image;
    }

    bool roundTrip(const ImageType2D::Pointer &image, const std::string &fileName)
    {
        try
        {
            itk::WriteImage(image, fileName);
            const ImageType2D::Pointer restored = itk::ReadImage<ImageType2D>(fileName);
            return restored->GetLargestPossibleRegion() == image->GetLargestPossibleRegion() &&
                   restored->GetPixel({{8, 8}}) == 200 && restored->GetPixel({{2, 3}}) == 50;
        }
        catch (const itk::ExceptionObject &error)
        {
            std::cerr << fileName << ": " << error.GetDescription() << std::endl;
            return false;
        }
    }
} // namespace

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

    itk::MetaImageIOFactory::RegisterOneFactory();
    itk::NrrdImageIOFactory::RegisterOneFactory();
    itk::PNGImageIOFactory::RegisterOneFactory();

    const ImageType2D::Pointer testImage = createTestImage();
    for (const char *fileName : {"test_package.mha", "test_package.nrrd", "test_package.png"})
    {
        if (!roundTrip(testImage, fileName))
        {
            return EXIT_FAILURE;
        }
    }

    using MedianFilterType = itk::MedianImageFilter<ImageType2D, ImageType2D>;
    MedianFilterType::Pointer median = MedianFilterType::New();
    median->SetInput(testImage);
    median->SetRadius(1);
    median->Update();
    if (median->GetOutput()->GetPixel({{8, 8}}) != 0)
    {
        std::cerr << "median filter did not remove the impulse" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
