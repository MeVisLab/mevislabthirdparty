#include <iostream>
#include <cstdint>
#include <tiffio.h>

int main(int argc, char* argv[])
{
    auto tif = TIFFOpen(argv[1], "r");
    if (tif == nullptr) {
        exit(1);
    }

    std::uint32_t w {}, h {};
    TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);

    auto raster = static_cast<std::uint32_t*>(_TIFFmalloc(w * h * sizeof(std::uint32_t)));
    if (raster != nullptr) {
        if (!TIFFReadRGBAImage(tif, w, h, raster, 0)) {
            exit(1);
        }
        _TIFFfree(raster);
    }

    TIFFClose(tif);

    exit(0);
}
