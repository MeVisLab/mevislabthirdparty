#include <jemalloc/jemalloc.h>

void do_something(size_t i) 
{
    // Leak some memory.
    (void) je_malloc(i * 100);
}

int main(int argc, char **argv) 
{
    for (size_t i = 0; i < 1000; i++) {
        do_something(i);
    }

    // Dump allocator statistics to stderr.
    je_malloc_stats_print(NULL, NULL, NULL);
    
    return 0;
}