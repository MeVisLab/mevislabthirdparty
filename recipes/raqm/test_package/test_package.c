#include <raqm.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    const char *text = "Hello raqm";
    raqm_t *rq = raqm_create();
    FT_Library library = NULL;
    FT_Face face = NULL;
    int result = 1;

    if (!rq) {
        fprintf(stderr, "raqm_create failed\n");
        return 1;
    }

    printf("raqm version: %s\n", RAQM_VERSION_STRING);

    if (!raqm_set_text_utf8(rq, text, strlen(text)) || !raqm_set_par_direction(rq, RAQM_DIRECTION_LTR)
        || !raqm_set_language(rq, "en", 0, strlen(text))) {
        fprintf(stderr, "setting up raqm text failed\n");
    } else if (argc < 2) {
        printf("no font file given, skipping layout\n");
        result = 0;
    } else if (FT_Init_FreeType(&library) != 0 || FT_New_Face(library, argv[1], 0, &face) != 0
               || FT_Set_Char_Size(face, 0, 16 * 64, 72, 72) != 0) {
        fprintf(stderr, "loading font %s failed\n", argv[1]);
    } else if (!raqm_set_freetype_face(rq, face) || !raqm_layout(rq)) {
        fprintf(stderr, "raqm_layout failed\n");
    } else {
        size_t glyph_count = 0;
        raqm_glyph_t *glyphs = raqm_get_glyphs(rq, &glyph_count);
        if (glyphs && glyph_count > 0) {
            printf("laid out %zu glyphs\n", glyph_count);
            result = 0;
        } else {
            fprintf(stderr, "raqm_get_glyphs returned no glyphs\n");
        }
    }

    raqm_destroy(rq);
    if (face) {
        FT_Done_Face(face);
    }
    if (library) {
        FT_Done_FreeType(library);
    }
    return result;
}
