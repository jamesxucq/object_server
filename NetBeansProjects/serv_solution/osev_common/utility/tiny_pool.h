
#ifndef TINY_POOL_H
#define TINY_POOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    //
#define tiny_align(d, a)     (((d) + (a - 1)) & ~(a - 1))
#define tiny_align_ptr(p, a) (u_char *) (((uintptr_t) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))
    
#define TINY_ALIGNMENT   sizeof(unsigned long)
typedef struct tiny_pool_s tiny_pool_t;
    /*
     * TINY_MAX_ALLOC_FROM_POOL should be (tiny_pagesize - 1), i.e. 4095 on x86.
     * On Windows NT it decreases a number of locked pages in a kernel.
     */
#define TINY_MAX_ALLOC_FROM_POOL  4095
#define TINY_DEFAULT_POOL_SIZE    (16 * 1024)
#define TINY_POOL_ALIGNMENT       16
#define TINY_MIN_POOL_SIZE tiny_align((sizeof(tiny_pool_t) + 2 * sizeof(tiny_pool_large_t)), TINY_POOL_ALIGNMENT)

//
    typedef void (*tiny_pool_cleanup_pt)(void *data);
    typedef struct tiny_pool_cleanup_s tiny_pool_cleanup_t;
    struct tiny_pool_cleanup_s {
        tiny_pool_cleanup_pt handler;
        void *data;
        //
        tiny_pool_cleanup_t *next;
    };

    typedef struct tiny_pool_large_s tiny_pool_large_t;
    struct tiny_pool_large_s {
        tiny_pool_large_t *next;
        //
        void *alloc;
    };

    typedef struct {
        u_char *last;
        u_char *end;
        tiny_pool_t *next;
        //
        uintptr_t failed;
    } tiny_pool_data_t;

    struct tiny_pool_s {
        tiny_pool_data_t d;
        size_t max;
        tiny_pool_t *current;
        tiny_pool_large_t *large;
        tiny_pool_cleanup_t *cleanup;
    };

//
    void *tiny_alloc(size_t size);
    void *tiny_calloc(size_t size);

    tiny_pool_t *tiny_create_pool(size_t size);
    void tiny_destroy_pool(tiny_pool_t *pool);
    void tiny_reset_pool(tiny_pool_t *pool);

    void *tiny_palloc(tiny_pool_t *pool, size_t size);
    void *tiny_pnalloc(tiny_pool_t *pool, size_t size);
    void *tiny_pcalloc(tiny_pool_t *pool, size_t size);
    void *tiny_pmemalign(tiny_pool_t *pool, size_t size, size_t alignment);
    int tiny_pfree(tiny_pool_t *pool, void *p);

    tiny_pool_cleanup_t *tiny_pool_cleanup_add(tiny_pool_t *p, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* TINY_POOL_H */

