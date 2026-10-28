#include <libdeflate.h>

#include <stdio.h>
#include <string.h>

int main(void)
{
    char input[4096];
    char compressed[8192];
    char decompressed[sizeof(input)];
    size_t compressed_size;
    size_t decompressed_size = 0;
    struct libdeflate_compressor *compressor = libdeflate_alloc_compressor(6);
    struct libdeflate_decompressor *decompressor = libdeflate_alloc_decompressor();
    int result = 1;

    for (size_t i = 0; i < sizeof(input); i++) {
        input[i] = (char)('a' + (i % 7));
    }

    compressed_size = libdeflate_deflate_compress(compressor, input, sizeof(input), compressed, sizeof(compressed));
    if (compressed_size == 0 || compressed_size >= sizeof(input)) {
        fprintf(stderr, "compression failed, compressed size %zu\n", compressed_size);
    } else if (libdeflate_deflate_decompress(decompressor, compressed, compressed_size, decompressed,
                                             sizeof(decompressed), &decompressed_size) != LIBDEFLATE_SUCCESS) {
        fprintf(stderr, "decompression failed\n");
    } else if (decompressed_size != sizeof(input) || memcmp(input, decompressed, sizeof(input)) != 0) {
        fprintf(stderr, "decompressed data differs from input\n");
    } else {
        printf("compressed %zu bytes to %zu bytes and back\n", sizeof(input), compressed_size);
        result = 0;
    }

    libdeflate_free_decompressor(decompressor);
    libdeflate_free_compressor(compressor);
    return result;
}
