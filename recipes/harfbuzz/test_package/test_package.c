#include <harfbuzz/hb.h>

#include <stdio.h>

int main(void)
{
    const char *text = "Hello";
    hb_buffer_t *buffer = hb_buffer_create();
    hb_face_t *face = hb_face_create(hb_blob_get_empty(), 0);
    hb_font_t *font = hb_font_create(face);
    unsigned int glyph_count = 0;
    int result = 1;

    hb_buffer_add_utf8(buffer, text, -1, 0, -1);
    hb_buffer_guess_segment_properties(buffer);

    if (hb_shape_full(font, buffer, NULL, 0, NULL) && hb_buffer_get_glyph_infos(buffer, &glyph_count) && glyph_count == 5
        && hb_buffer_get_content_type(buffer) == HB_BUFFER_CONTENT_TYPE_GLYPHS) {
        printf("harfbuzz %s shaped %u glyphs\n", hb_version_string(), glyph_count);
        result = 0;
    } else {
        fprintf(stderr, "unexpected shaping result: %u glyphs\n", glyph_count);
    }

    hb_font_destroy(font);
    hb_face_destroy(face);
    hb_buffer_destroy(buffer);
    return result;
}
