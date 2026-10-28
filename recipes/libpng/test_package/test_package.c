#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

#define WIDTH 4
#define HEIGHT 3

typedef struct {
  png_byte *data;
  size_t size;
  size_t position;
} memory_buffer;

static void write_to_memory(png_structp png, png_bytep bytes, size_t length)
{
  memory_buffer *buffer = (memory_buffer *)png_get_io_ptr(png);
  png_byte *grown = realloc(buffer->data, buffer->size + length);
  if (!grown)
    png_error(png, "out of memory");
  buffer->data = grown;
  memcpy(buffer->data + buffer->size, bytes, length);
  buffer->size += length;
}

static void flush_memory(png_structp png)
{
  (void)png;
}

static void read_from_memory(png_structp png, png_bytep bytes, size_t length)
{
  memory_buffer *buffer = (memory_buffer *)png_get_io_ptr(png);
  if (buffer->position + length > buffer->size)
    png_error(png, "read past end of buffer");
  memcpy(bytes, buffer->data + buffer->position, length);
  buffer->position += length;
}

static void fill_pixels(png_byte pixels[HEIGHT][WIDTH * 4])
{
  int x, y;
  for (y = 0; y < HEIGHT; ++y) {
    for (x = 0; x < WIDTH; ++x) {
      pixels[y][x * 4 + 0] = (png_byte)(x * 60);
      pixels[y][x * 4 + 1] = (png_byte)(y * 80);
      pixels[y][x * 4 + 2] = (png_byte)(x + y);
      pixels[y][x * 4 + 3] = 255;
    }
  }
}

static int write_png(memory_buffer *buffer, png_byte pixels[HEIGHT][WIDTH * 4])
{
  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info = png_create_info_struct(png);
  png_bytep rows[HEIGHT];
  int y;
  if (setjmp(png_jmpbuf(png))) {
    png_destroy_write_struct(&png, &info);
    return 0;
  }
  png_set_write_fn(png, buffer, write_to_memory, flush_memory);
  png_set_IHDR(png, info, WIDTH, HEIGHT, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);
  for (y = 0; y < HEIGHT; ++y)
    rows[y] = pixels[y];
  png_set_rows(png, info, rows);
  png_write_png(png, info, PNG_TRANSFORM_IDENTITY, NULL);
  png_destroy_write_struct(&png, &info);
  return 1;
}

static int read_png(memory_buffer *buffer, png_byte pixels[HEIGHT][WIDTH * 4])
{
  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info = png_create_info_struct(png);
  png_bytep rows[HEIGHT];
  int y;
  if (setjmp(png_jmpbuf(png))) {
    png_destroy_read_struct(&png, &info, NULL);
    return 0;
  }
  png_set_read_fn(png, buffer, read_from_memory);
  for (y = 0; y < HEIGHT; ++y)
    rows[y] = pixels[y];
  png_read_info(png, info);
  if (png_get_image_width(png, info) != WIDTH || png_get_image_height(png, info) != HEIGHT ||
      png_get_color_type(png, info) != PNG_COLOR_TYPE_RGB_ALPHA || png_get_bit_depth(png, info) != 8) {
    png_destroy_read_struct(&png, &info, NULL);
    return 0;
  }
  png_read_image(png, rows);
  png_read_end(png, NULL);
  png_destroy_read_struct(&png, &info, NULL);
  return 1;
}

int main()
{
  png_byte written[HEIGHT][WIDTH * 4];
  png_byte read_back[HEIGHT][WIDTH * 4];
  memory_buffer buffer = {NULL, 0, 0};
  int result = EXIT_FAILURE;

  printf("Compiled with libpng %s; using libpng %s.\n", PNG_LIBPNG_VER_STRING, png_libpng_ver);

  fill_pixels(written);
  memset(read_back, 0, sizeof(read_back));
  if (!write_png(&buffer, written)) {
    fprintf(stderr, "writing PNG failed\n");
  } else if (memcmp(buffer.data, "\x89PNG\r\n\x1a\n", 8) != 0) {
    fprintf(stderr, "missing PNG signature\n");
  } else if (!read_png(&buffer, read_back)) {
    fprintf(stderr, "reading PNG failed\n");
  } else if (memcmp(written, read_back, sizeof(written)) != 0) {
    fprintf(stderr, "pixels differ after round trip\n");
  } else {
    printf("PNG round trip of %dx%d RGBA image (%lu bytes) succeeded\n", WIDTH, HEIGHT, (unsigned long)buffer.size);
    result = EXIT_SUCCESS;
  }
  free(buffer.data);
  return result;
}
