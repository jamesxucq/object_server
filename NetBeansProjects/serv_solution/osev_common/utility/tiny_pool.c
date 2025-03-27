
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
// #include "jemalloc/jemalloc.h"
#include "tiny_pool.h"

//
static void *tiny_palloc_small(tiny_pool_t *pool, size_t size, uintptr_t align);
static void *tiny_palloc_block(tiny_pool_t *pool, size_t size);
static void *tiny_palloc_large(tiny_pool_t *pool, size_t size);

tiny_pool_t *tiny_create_pool(size_t size) {
    tiny_pool_t *p;
    //
    p = memalign(TINY_POOL_ALIGNMENT, size);
    if (p == NULL) {
        return NULL;
    }
    p->d.last = (u_char *) p + sizeof (tiny_pool_t);
    p->d.end = (u_char *) p + size;
    p->d.next = NULL;
    p->d.failed = 0;
    size = size - sizeof (tiny_pool_t);
    p->max = (size < TINY_MAX_ALLOC_FROM_POOL) ? size : TINY_MAX_ALLOC_FROM_POOL;
    p->current = p;
    p->large = NULL;
    p->cleanup = NULL;
    //
    return p;
}

void tiny_destroy_pool(tiny_pool_t *pool) {
    tiny_pool_t *p, *n;
    tiny_pool_large_t *l;
    tiny_pool_cleanup_t *c;
    //
    for (c = pool->cleanup; c; c = c->next) {
        if (c->handler) {
            c->handler(c->data);
        }
    }
    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
            free(l->alloc);
        }
    }
    for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
        free(p);
        if (n == NULL) {
            break;
        }
    }
}

void tiny_reset_pool(tiny_pool_t *pool) {
    tiny_pool_t *p;
    tiny_pool_large_t *l;
    //
    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
            free(l->alloc);
        }
    }
    for (p = pool; p; p = p->d.next) {
        p->d.last = (u_char *) p + sizeof (tiny_pool_t);
        p->d.failed = 0;
    }
    pool->current = pool;
    pool->large = NULL;
}

void *tiny_palloc(tiny_pool_t *pool, size_t size) {
    if (size <= pool->max) {
        return tiny_palloc_small(pool, size, 1);
    }
    return tiny_palloc_large(pool, size);
}

void *tiny_pnalloc(tiny_pool_t *pool, size_t size) {
    if (size <= pool->max) {
        return tiny_palloc_small(pool, size, 0);
    }
    return tiny_palloc_large(pool, size);
}

static void *tiny_palloc_small(tiny_pool_t *pool, size_t size, uintptr_t align) {
    u_char *m;
    tiny_pool_t *p;
    //
    p = pool->current;
    do {
        m = p->d.last;
        if (align) {
            m = tiny_align_ptr(m, TINY_ALIGNMENT);
        }
        if ((size_t) (p->d.end - m) >= size) {
            p->d.last = m + size;
            return m;
        }
        p = p->d.next;
    } while (p);
    return tiny_palloc_block(pool, size);
}

static void *tiny_palloc_block(tiny_pool_t *pool, size_t size) {
    u_char *m;
    size_t psize;
    tiny_pool_t *p, *new;
    //
    psize = (size_t) (pool->d.end - (u_char *) pool);
    m = memalign(TINY_POOL_ALIGNMENT, psize);
    if (m == NULL) {
        return NULL;
    }
    new = (tiny_pool_t *) m;
    new->d.end = m + psize;
    new->d.next = NULL;
    new->d.failed = 0;
    m += sizeof (tiny_pool_data_t);
    m = tiny_align_ptr(m, TINY_ALIGNMENT);
    new->d.last = m + size;
    for (p = pool->current; p->d.next; p = p->d.next) {
        if (p->d.failed++ > 4) {
            pool->current = p->d.next;
        }
    }
    p->d.next = new;
    //
    return m;
}

static void *tiny_palloc_large(tiny_pool_t *pool, size_t size) {
    void *p;
    uintptr_t n;
    tiny_pool_large_t *large;
    //
    p = malloc(size);
    if (p == NULL) {
        return NULL;
    }
    n = 0;
    for (large = pool->large; large; large = large->next) {
        if (large->alloc == NULL) {
            large->alloc = p;
            return p;
        }
        if (n++ > 3) {
            break;
        }
    }
    large = tiny_palloc_small(pool, sizeof (tiny_pool_large_t), 1);
    if (large == NULL) {
        free(p);
        return NULL;
    }
    large->alloc = p;
    large->next = pool->large;
    pool->large = large;
    //
    return p;
}

void *tiny_pmemalign(tiny_pool_t *pool, size_t size, size_t alignment) {
    void *p;
    tiny_pool_large_t *large;
    //
    p = memalign(alignment, size);
    if (p == NULL) {
        return NULL;
    }
    large = tiny_palloc_small(pool, sizeof (tiny_pool_large_t), 1);
    if (large == NULL) {
        free(p);
        return NULL;
    }
    large->alloc = p;
    large->next = pool->large;
    pool->large = large;
    //
    return p;
}

int tiny_pfree(tiny_pool_t *pool, void *p) {
    tiny_pool_large_t *l;
    for (l = pool->large; l; l = l->next) {
        if (p == l->alloc) {
            free(l->alloc);
            l->alloc = NULL;
            return 0x00;
        }
    }
    return -1;
}

void *tiny_pcalloc(tiny_pool_t *pool, size_t size) {
    void *p;
    p = tiny_palloc(pool, size);
    if (p) {
        memset(p, '\0', size);
    }
    return p;
}

tiny_pool_cleanup_t *tiny_pool_cleanup_add(tiny_pool_t *p, size_t size) {
    tiny_pool_cleanup_t *c;
    c = tiny_palloc(p, sizeof (tiny_pool_cleanup_t));
    if (c == NULL) {
        return NULL;
    }
    if (size) {
        c->data = tiny_palloc(p, size);
        if (c->data == NULL) {
            return NULL;
        }
    } else {
        c->data = NULL;
    }
    c->handler = NULL;
    c->next = p->cleanup;
    p->cleanup = c;
    return c;
}

#if 0

static void *tiny_get_cached_block(size_t size) {
    void *p;
    tiny_cached_block_slot_t *slot;
    if (tiny_cycle->cache == NULL) {
        return NULL;
    }
    slot = &tiny_cycle->cache[(size + tiny_pagesize - 1) / tiny_pagesize];
    slot->tries++;
    if (slot->number) {
        p = slot->block;
        slot->block = slot->block->next;
        slot->number--;
        return p;
    }
    return NULL;
}
#endif
