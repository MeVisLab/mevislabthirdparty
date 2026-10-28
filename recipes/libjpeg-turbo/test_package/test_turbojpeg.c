#include <stdio.h>
#include <stdlib.h>

#include "turbojpeg.h"

int main(int argc, char **argv)
{
  FILE *file;
  long file_size;
  unsigned char *jpeg_data;
  tjhandle handle;
  int width, height, subsampling, colorspace;

  if (argc < 2) {
    fprintf(stderr, "usage: %s <jpeg file>\n", argv[0]);
    return EXIT_FAILURE;
  }
  file = fopen(argv[1], "rb");
  if (file == NULL) {
    fprintf(stderr, "cannot open %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  fseek(file, 0, SEEK_END);
  file_size = ftell(file);
  fseek(file, 0, SEEK_SET);
  jpeg_data = malloc((size_t)file_size);
  if (fread(jpeg_data, 1, (size_t)file_size, file) != (size_t)file_size) {
    fprintf(stderr, "cannot read %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  fclose(file);

  handle = tj3Init(TJINIT_DECOMPRESS);
  if (handle == NULL) {
    fprintf(stderr, "tj3Init failed\n");
    return EXIT_FAILURE;
  }
  if (tj3DecompressHeader(handle, jpeg_data, (size_t)file_size) != 0) {
    fprintf(stderr, "tj3DecompressHeader failed: %s\n", tj3GetErrorStr(handle));
    return EXIT_FAILURE;
  }
  width = tj3Get(handle, TJPARAM_JPEGWIDTH);
  height = tj3Get(handle, TJPARAM_JPEGHEIGHT);
  subsampling = tj3Get(handle, TJPARAM_SUBSAMP);
  colorspace = tj3Get(handle, TJPARAM_COLORSPACE);
  tj3Destroy(handle);
  free(jpeg_data);

  if (width <= 0 || height <= 0 || subsampling < 0 || subsampling >= TJ_NUMSAMP) {
    fprintf(stderr, "unexpected header values %dx%d subsampling %d\n", width, height, subsampling);
    return EXIT_FAILURE;
  }
  printf("TurboJPEG: %s is %dx%d, subsampling %d, colorspace %d\n", argv[1], width, height, subsampling, colorspace);
  return EXIT_SUCCESS;
}
