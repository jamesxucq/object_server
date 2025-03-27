
#ifndef _BLOOM_H
#define _BLOOM_H

#include <stdlib.h>
#include <stdint.h>

typedef struct {
    size_t asize;
    unsigned char *a;
} BLOOM;

BLOOM *bloom_create(size_t size);
int bloom_destroy(BLOOM *bloom);
int bloom_setbit(BLOOM *bloom, int n, ...);
int bloom_check(BLOOM *bloom, int n, ...);

#endif

