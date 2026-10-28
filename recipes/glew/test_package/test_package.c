#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
    const GLubyte *version = glewGetString(GLEW_VERSION);
    const GLubyte *major = glewGetString(GLEW_VERSION_MAJOR);
    const GLubyte *minor = glewGetString(GLEW_VERSION_MINOR);
    const GLubyte *micro = glewGetString(GLEW_VERSION_MICRO);
    char expected[64];

    if (version == NULL || major == NULL || minor == NULL || micro == NULL) {
        fprintf(stderr, "glewGetString returned NULL\n");
        return EXIT_FAILURE;
    }
    snprintf(expected, sizeof(expected), "%s.%s.%s", major, minor, micro);
    if (strcmp((const char *)version, expected) != 0) {
        fprintf(stderr, "GLEW version '%s' does not match '%s'\n", version, expected);
        return EXIT_FAILURE;
    }
    if (glewIsSupported("GL_VERSION_1_1") != GL_FALSE) {
        fprintf(stderr, "glewIsSupported reported support without a GL context\n");
        return EXIT_FAILURE;
    }
    if (strcmp((const char *)glewGetErrorString(GLEW_OK), "No error") != 0) {
        fprintf(stderr, "unexpected glewGetErrorString(GLEW_OK): %s\n", glewGetErrorString(GLEW_OK));
        return EXIT_FAILURE;
    }

    printf("GLEW %s\n", version);
    return EXIT_SUCCESS;
}
