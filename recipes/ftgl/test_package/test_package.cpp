#include <FTGLPolygonFont.h>
#include <FTSize.h>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " <font file>" << std::endl;
        return 1;
    }
    FTSize size;
    FTGLPolygonFont font(argv[1]);
    if (font.Error() != 0)
    {
        std::cerr << "loading font failed with FreeType error " << font.Error() << std::endl;
        return 1;
    }
    if (!font.FaceSize(24) || font.FaceSize() != 24 || font.Error() != 0)
    {
        std::cerr << "setting face size failed with FreeType error " << font.Error() << std::endl;
        return 1;
    }
    if (font.Ascender() <= 0.0f || font.Descender() >= 0.0f)
    {
        std::cerr << "unexpected font metrics: ascender " << font.Ascender() << " descender "
                  << font.Descender() << std::endl;
        return 1;
    }
    std::cout << "loaded font " << argv[1] << " with " << font.CharMapCount()
              << " charmaps, ascender " << font.Ascender() << std::endl;
    return 0;
}
