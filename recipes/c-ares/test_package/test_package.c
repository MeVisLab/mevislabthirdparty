#include <stdio.h>
#include <ares.h>

int main(void)
{
    int status;
    ares_channel_t *channel = NULL;

    int version = 0;
    const char *version_str = NULL;

    status = ares_library_init(ARES_LIB_INIT_ALL);
    if (status != ARES_SUCCESS) {
        fprintf(stderr, "ares_library_init failed: %s\n", ares_strerror(status));
        return 1;
    }

    version_str = ares_version(&version);
    if (version_str == NULL) {
        fprintf(stderr, "ares_version returned NULL\n");
        ares_library_cleanup();
        return 1;
    }

    status = ares_init_options(&channel, NULL, 0);
    if (status != ARES_SUCCESS) {
        fprintf(stderr, "ares_init_options failed: %s\n", ares_strerror(status));
        ares_library_cleanup();
        return 1;
    }

    printf("c-ares version: %s\n", version_str);

    ares_destroy(channel);
    ares_library_cleanup();

    return 0;
}
