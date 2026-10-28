#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    GLFWwindow* window;
    int major = 0;
    int minor = 0;
    int revision = 0;
    int width = 0;
    int height = 0;

    glfwGetVersion(&major, &minor, &revision);
    printf("GLFW %d.%d.%d (%s)\n", major, minor, revision, glfwGetVersionString());
    if (major != GLFW_VERSION_MAJOR || minor != GLFW_VERSION_MINOR || revision != GLFW_VERSION_REVISION) {
        fprintf(stderr, "runtime version does not match header version %d.%d.%d\n", GLFW_VERSION_MAJOR,
                GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
        return EXIT_FAILURE;
    }

    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_NULL);
    if (!glfwInit()) {
        fprintf(stderr, "glfwInit failed with error %d\n", glfwGetError(NULL));
        return EXIT_FAILURE;
    }
    if (glfwGetPlatform() != GLFW_PLATFORM_NULL) {
        fprintf(stderr, "unexpected platform %d\n", glfwGetPlatform());
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(640, 480, "Window name", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "glfwCreateWindow failed with error %d\n", glfwGetError(NULL));
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwGetWindowSize(window, &width, &height);
    if (width != 640 || height != 480) {
        fprintf(stderr, "unexpected window size %dx%d\n", width, height);
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
