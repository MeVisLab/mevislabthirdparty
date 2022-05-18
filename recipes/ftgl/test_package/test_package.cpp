#include <FTSize.h>
#include <FTGLTextureFont.h>
#include <iostream>

int main(int argc, char**  argv)
{
    std::cout << "Trying to create FTSize." << std::endl;
    FTSize *layout = new FTSize();
    std::cout << "Trying to create font." << std::endl;
    FTGLTextureFont *font = new FTGLTextureFont(argv[1]);
    std::cout << "Error: " << font->Error() << std::endl;
    return 0;
}
