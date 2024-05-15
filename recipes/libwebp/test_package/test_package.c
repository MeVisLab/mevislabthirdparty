#include <stdio.h>
#include <webp/decode.h>

int main()
{
    int version = WebPGetDecoderVersion();
    printf("Webp Decoder version: %d\n", version);
    return 0;
}
