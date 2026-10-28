#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <webp/decode.h>
#include <webp/demux.h>
#include <webp/encode.h>
#include <webp/mux.h>

#define WIDTH 8
#define HEIGHT 4

int main()
{
    uint8_t rgba[WIDTH * HEIGHT * 4];
    uint8_t *encoded = NULL;
    uint8_t *decoded = NULL;
    size_t encoded_size;
    int width = 0;
    int height = 0;
    int canvas_width = 0;
    int canvas_height = 0;
    WebPData data;
    WebPDemuxer *demux;
    WebPMux *mux;
    int i;

    printf("WebP encoder %x, decoder %x\n", WebPGetEncoderVersion(), WebPGetDecoderVersion());

    for (i = 0; i < WIDTH * HEIGHT; ++i) {
        rgba[i * 4 + 0] = (uint8_t)(i * 7);
        rgba[i * 4 + 1] = (uint8_t)(i * 3);
        rgba[i * 4 + 2] = (uint8_t)(255 - i);
        rgba[i * 4 + 3] = (uint8_t)(200 + (i % 50));
    }

    encoded_size = WebPEncodeLosslessRGBA(rgba, WIDTH, HEIGHT, WIDTH * 4, &encoded);
    if (encoded_size == 0 || encoded == NULL) {
        fprintf(stderr, "WebPEncodeLosslessRGBA failed\n");
        return EXIT_FAILURE;
    }

    decoded = WebPDecodeRGBA(encoded, encoded_size, &width, &height);
    if (decoded == NULL || width != WIDTH || height != HEIGHT || memcmp(rgba, decoded, sizeof(rgba)) != 0) {
        fprintf(stderr, "WebPDecodeRGBA round trip failed (%dx%d)\n", width, height);
        return EXIT_FAILURE;
    }

    data.bytes = encoded;
    data.size = encoded_size;
    demux = WebPDemux(&data);
    if (demux == NULL || WebPDemuxGetI(demux, WEBP_FF_CANVAS_WIDTH) != WIDTH ||
        WebPDemuxGetI(demux, WEBP_FF_CANVAS_HEIGHT) != HEIGHT || WebPDemuxGetI(demux, WEBP_FF_FRAME_COUNT) != 1) {
        fprintf(stderr, "WebPDemux failed\n");
        return EXIT_FAILURE;
    }
    WebPDemuxDelete(demux);

    mux = WebPMuxCreate(&data, 0);
    if (mux == NULL || WebPMuxGetCanvasSize(mux, &canvas_width, &canvas_height) != WEBP_MUX_OK ||
        canvas_width != WIDTH || canvas_height != HEIGHT) {
        fprintf(stderr, "WebPMuxCreate failed\n");
        return EXIT_FAILURE;
    }
    WebPMuxDelete(mux);

    WebPFree(decoded);
    WebPFree(encoded);
    printf("WebP round trip of %dx%d image (%lu bytes) succeeded\n", WIDTH, HEIGHT, (unsigned long)encoded_size);
    return EXIT_SUCCESS;
}
