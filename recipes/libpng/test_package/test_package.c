#include <stdio.h>
#include <string.h>
#include <png.h>

int main()
{
  printf("Compiled with libpng %s; using libpng %s.\n", PNG_LIBPNG_VER_STRING, png_libpng_ver);
  return 0;
}
