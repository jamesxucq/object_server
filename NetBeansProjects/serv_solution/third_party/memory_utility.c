// #include "jemalloc/jemalloc.h"
#include "memory_utility.h"

#define MALLOC_MAX 0x40000000 // 1G

void *new_array(unsigned long num, unsigned int size, int use_calloc) {
    if (num >= MALLOC_MAX / size)
        return NULL;
    return use_calloc ? calloc(num, size) : malloc(num * size);
}

void *realloc_array(void *ptr, unsigned int size, size_t num) {
    if (num >= MALLOC_MAX / size)
        return NULL;
    if (!ptr) return malloc(size * num);
    return realloc(ptr, size * num);
}
