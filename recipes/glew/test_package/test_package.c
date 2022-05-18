#include <GL/glew.h>
#include <stdio.h>

int main()
{
    printf("GLEW version: %s\n", glewGetString(GLEW_VERSION));
    return 0;
}
