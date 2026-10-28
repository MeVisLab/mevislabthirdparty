#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jpeglib.h"

#define WIDTH 16
#define HEIGHT 16

static void fill_pixels(JSAMPLE pixels[HEIGHT][WIDTH * 3])
{
  int x, y;
  for (y = 0; y < HEIGHT; ++y) {
    for (x = 0; x < WIDTH; ++x) {
      pixels[y][x * 3 + 0] = 200;
      pixels[y][x * 3 + 1] = 100;
      pixels[y][x * 3 + 2] = 50;
    }
  }
}

static unsigned char *compress_image(JSAMPLE pixels[HEIGHT][WIDTH * 3], unsigned long *size)
{
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  unsigned char *buffer = NULL;
  JSAMPROW row;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  jpeg_mem_dest(&cinfo, &buffer, size);
  cinfo.image_width = WIDTH;
  cinfo.image_height = HEIGHT;
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, 95, TRUE);
  jpeg_start_compress(&cinfo, TRUE);
  while (cinfo.next_scanline < cinfo.image_height) {
    row = pixels[cinfo.next_scanline];
    jpeg_write_scanlines(&cinfo, &row, 1);
  }
  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);
  return buffer;
}

static int decompress_image(const unsigned char *buffer, unsigned long size, JSAMPLE pixels[HEIGHT][WIDTH * 3])
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  JSAMPROW row;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
  jpeg_mem_src(&cinfo, buffer, size);
  if (jpeg_read_header(&cinfo, TRUE) != JPEG_HEADER_OK) {
    jpeg_destroy_decompress(&cinfo);
    return 0;
  }
  jpeg_start_decompress(&cinfo);
  if (cinfo.output_width != WIDTH || cinfo.output_height != HEIGHT || cinfo.output_components != 3) {
    jpeg_destroy_decompress(&cinfo);
    return 0;
  }
  while (cinfo.output_scanline < cinfo.output_height) {
    row = pixels[cinfo.output_scanline];
    jpeg_read_scanlines(&cinfo, &row, 1);
  }
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  return 1;
}

int main(void)
{
  JSAMPLE written[HEIGHT][WIDTH * 3];
  JSAMPLE read_back[HEIGHT][WIDTH * 3];
  unsigned char *jpeg_data;
  unsigned long jpeg_size = 0;
  int channel;

  printf("libjpeg version %d\n", JPEG_LIB_VERSION);

  fill_pixels(written);
  memset(read_back, 0, sizeof(read_back));
  jpeg_data = compress_image(written, &jpeg_size);
  if (jpeg_data == NULL || jpeg_size == 0) {
    fprintf(stderr, "compression failed\n");
    return EXIT_FAILURE;
  }
  if (!decompress_image(jpeg_data, jpeg_size, read_back)) {
    fprintf(stderr, "decompression failed\n");
    return EXIT_FAILURE;
  }
  free(jpeg_data);

  for (channel = 0; channel < 3; ++channel) {
    if (abs((int)written[HEIGHT / 2][(WIDTH / 2) * 3 + channel] - (int)read_back[HEIGHT / 2][(WIDTH / 2) * 3 + channel]) > 4) {
      fprintf(stderr, "pixel channel %d differs too much after round trip\n", channel);
      return EXIT_FAILURE;
    }
  }
  printf("JPEG round trip of %dx%d image (%lu bytes) succeeded\n", WIDTH, HEIGHT, jpeg_size);
  return EXIT_SUCCESS;
}
