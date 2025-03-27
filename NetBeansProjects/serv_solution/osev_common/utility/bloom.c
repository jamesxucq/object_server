
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
// #include "jemalloc/jemalloc.h"
#include "bloom.h"

#define SETBIT(a, n) (a[n/CHAR_BIT] |= (1<<(n%CHAR_BIT)))
#define GETBIT(a, n) (a[n/CHAR_BIT] & (1<<(n%CHAR_BIT)))

BLOOM *bloom_create(size_t size) {
    BLOOM *bloom;
    //
    if (!(bloom = malloc(sizeof (BLOOM))))
        return NULL;
    if (!(bloom->a = calloc((size + CHAR_BIT - 1) / CHAR_BIT, sizeof (char)))) {
        free(bloom);
        return NULL;
    }
    bloom->asize = size;
    //
    return bloom;
}

int bloom_destroy(BLOOM *bloom) {
    free(bloom->a);
    free(bloom);
    return 0x00;
}

int bloom_setbit(BLOOM *bloom, int n, ...) {
    va_list lst;
    uint32_t posi;
    unsigned int inde;
    //
    va_start(lst, n);
    for (inde = 0x00; inde < n; ++inde) {
        posi = va_arg(lst, uint32_t);
        SETBIT(bloom->a, posi % bloom->asize);
    }
    va_end(lst);
    //
    return 0x00;
}

int bloom_check(BLOOM *bloom, int n, ...) {
    va_list lst;
    uint32_t posi;
    unsigned int inde;
    //
    va_start(lst, n);
    for (inde = 0x00; inde < n; ++inde) {
        posi = va_arg(lst, uint32_t);
        if (!(GETBIT(bloom->a, posi % bloom->asize))) {
            return 0x00;
        }
    }
    va_end(lst);
    //
    return 0x01;
}
