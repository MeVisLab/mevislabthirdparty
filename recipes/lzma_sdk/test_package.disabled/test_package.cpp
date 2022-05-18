#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <memory>

#include <LzmaEnc.h>
#include <LzmaDec.h>


static void *_lzmaAlloc(ISzAllocPtr, size_t size)
{
    return new uint8_t[size];
}

static void _lzmaFree(ISzAllocPtr, void *addr)
{
    if (!addr) {
        return;
    }

    delete[] reinterpret_cast<uint8_t *>(addr);
}

static ISzAlloc _allocFuncs = {
    _lzmaAlloc, _lzmaFree
};


std::unique_ptr<uint8_t[]> lzmaCompress(const uint8_t *input, uint32_t inputSize, uint32_t *outputSize)
{
    std::unique_ptr<uint8_t[]> result;

    CLzmaEncProps props;
    LzmaEncProps_Init(&props);

    if (inputSize >= (1 << 20)) {
        props.dictSize = 1 << 20;
    }
    else {
        props.dictSize = inputSize;
    }
    props.fb = 40;

    SizeT propsSize = 5;
    uint8_t propsEncoded[5];

    SizeT outputSize64 = inputSize * 1.5;
    if (outputSize64 < 1024) {
        outputSize64 = 1024;
    }

    auto output = std::make_unique<uint8_t[]>(outputSize64);

    int lzmaStatus = LzmaEncode(output.get(), &outputSize64, input, inputSize, &props, propsEncoded, &propsSize, 0, nullptr, &_allocFuncs, &_allocFuncs);

    *outputSize = outputSize64 + 13;
    if (lzmaStatus == SZ_OK) {
        result = std::make_unique<uint8_t[]>(outputSize64 + 13);
        uint8_t *resultData = result.get();

        memcpy(resultData, propsEncoded, 5);
        for (int i = 0; i < 8; i++) {
            resultData[5 + i] = (inputSize >> (i * 8)) & 0xFF;
        }

        memcpy(resultData + 13, output.get(), outputSize64);
    }

    return result;
}


std::unique_ptr<uint8_t[]> lzmaDecompress(const uint8_t *input, uint32_t inputSize, uint32_t *outputSize) {
    if (inputSize < 13) {
        return nullptr;
    }

    UInt64 size = 0;
    for (int i = 0; i < 8; i++) {
        size |= (input[5 + i] << (i * 8));
    }

    if (size <= (256 * 1024 * 1024)) {
        auto blob = std::make_unique<uint8_t[]>(size);

        ELzmaStatus lzmaStatus;
        SizeT procOutSize = size, procInSize = inputSize - 13;
        int status = LzmaDecode(blob.get(), &procOutSize, &input[13], &procInSize, input, 5, LZMA_FINISH_END, &lzmaStatus, &_allocFuncs);

        if (status == SZ_OK && procOutSize == size) {
            *outputSize = size;
            return blob;
        }
    }

    return nullptr;
}

int main(int argc, char **argv)
{
    const char *input = "Hello World! Hello World! Hello World! Hello World! Hello World! Hello World! Hello World! Hello World!";

    uint32_t compressedSize;
    auto compressedBlob = lzmaCompress((const uint8_t *)input, strlen(input), &compressedSize);
    if(compressedBlob == nullptr) {
        printf("Failed to compress data.\n");
        return 1;
    }

    uint32_t decompressedSize;
    auto decompressedBlob = lzmaDecompress(compressedBlob.get(), compressedSize, &decompressedSize);
    if(decompressedBlob == nullptr) {
        printf("Failed to decompress data.\n");
        return 1;
    }

    if(strlen(input) != decompressedSize) {
        printf("Length of input and decompressed data differ.\n");
        return 1;
    }

    if(memcmp(decompressedBlob.get(), decompressedBlob.get(), decompressedSize) != 0) {
        printf("input and decompressed data differ.\n");
        return 1;
    }

    return 0;
}
