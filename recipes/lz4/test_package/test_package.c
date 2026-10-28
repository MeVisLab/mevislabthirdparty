#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lz4.h"

int main()
{
  const char input[] = "Conan Package Manager, Conan Package Manager, Conan Package Manager";
  const int input_size = (int)sizeof(input);
  char compressed[LZ4_COMPRESSBOUND(sizeof(input))];
  char decompressed[sizeof(input)];
  int compressed_size;
  int decompressed_size;

  printf("LZ4 Library version = %d\n", LZ4_versionNumber());

  compressed_size = LZ4_compress_default(input, compressed, input_size, (int)sizeof(compressed));
  if (compressed_size <= 0 || compressed_size >= input_size) {
    fprintf(stderr, "LZ4_compress_default failed: %d\n", compressed_size);
    return EXIT_FAILURE;
  }

  decompressed_size = LZ4_decompress_safe(compressed, decompressed, compressed_size, (int)sizeof(decompressed));
  if (decompressed_size != input_size || memcmp(input, decompressed, input_size) != 0) {
    fprintf(stderr, "LZ4_decompress_safe round trip failed: %d\n", decompressed_size);
    return EXIT_FAILURE;
  }

  printf("Compressed %d bytes to %d bytes\n", input_size, compressed_size);
  return EXIT_SUCCESS;
}
