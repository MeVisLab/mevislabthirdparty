#include <brotli/decode.h>
#include <brotli/encode.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

int main()
{
    std::string input = "Sed ut perspiciatis unde omnis iste natus error sit "
                        "voluptatem accusantium doloremque laudantium, totam rem "
                        "aperiam, eaque ipsa quae ab illo inventore veritatis et "
                        "quasi architecto beatae vitae dicta sunt explicabo.";
    uint8_t buffer[256];
    size_t isize = sizeof(buffer);

    BROTLI_BOOL result = BrotliEncoderCompress(
        BROTLI_DEFAULT_QUALITY, BROTLI_DEFAULT_WINDOW, BROTLI_DEFAULT_MODE,
        input.size(), reinterpret_cast<const uint8_t *>(input.c_str()),
        &isize, buffer
    );

    if (result != BROTLI_TRUE) {
        std::cout << "BrotliEncoderCompress failed" << std::endl;
        return EXIT_FAILURE;
    }

    char buffer2[256];
    size_t osize = sizeof(buffer2);
    result = BrotliDecoderDecompress(isize, buffer, &osize, reinterpret_cast<uint8_t *>(buffer2));

    if (result != BROTLI_TRUE) {
        std::cout << "BrotliDecoderDecompress failed" << std::endl;
        return EXIT_FAILURE;
    }

    if (osize != input.size()) {
        std::cout << "Size of input (" << input.size() << ") and output (" << osize << ") do not match" << std::endl;
        return EXIT_FAILURE;
    }

    if (strncmp(input.c_str(), buffer2, input.size())) {
        std::cout << "The original string could not be reconstructed" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "String was correctly reconstructed" << std::endl;

    return EXIT_SUCCESS;
}
