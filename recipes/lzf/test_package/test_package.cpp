#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <lzf.h>

int main()
{
    const char *in_buf = "Hello World! Hello World! Hello World! Hello World! Hello World! Hello World!";
    unsigned int in_size = strlen(in_buf);

    char *out_buf = (char*) malloc(in_size * 2);
    unsigned int out_size = lzf_compress(in_buf, in_size, out_buf, in_size * 2);

    char *de_buf = (char*) malloc(in_size * 2);
    unsigned int de_size = lzf_decompress(out_buf, out_size, de_buf, in_size * 2);

    if(in_size != de_size) {
        return 1;
    }

    if(memcmp(in_buf, de_buf, de_size) != 0) {
        return 1;
    }

    return 0;
}
