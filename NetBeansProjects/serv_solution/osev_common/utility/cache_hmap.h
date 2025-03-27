/* 
 * File:   cache_hmap.h
 * Author: James Xu
 */

#ifndef CACHEHMAP_H
#define CACHEHMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

    struct cache_node {
        const void *key;
        void *data;
        //
        struct cache_node *next;
    };

    struct _cachemap_ {
        unsigned int (*gethash)(const void *);
        int (*compare)(const void *, const void *);
        unsigned int hashsize;
        unsigned int count;
        struct cache_node **hmaplist;
    };

    typedef struct _cachemap_ cachemap;

    // size = 2^n
    cachemap *cache_create(unsigned int (*keyfunc)(const void *), int (*compare)(const void *, const void *), unsigned int size);
    void cache_destroy(cachemap *cmap);
    void cache_clear(cachemap *cmap);
    void cache_insert(const void *key, void *data, cachemap *cmap);
    void cache_remove(const void *key, cachemap *cmap);
    void *cache_value(const void *key, cachemap *cmap);
    void cache_for_each_do(cachemap *cmap, int (*call_back) (const void *, void *));
    void cache_each_data(cachemap *cmap, void (*call_back) (void *));
    //

    inline int cache_count(cachemap *cmap) {
        return cmap->count;
    }

#ifdef __cplusplus
}
#endif

#endif /* CACHEHMAP_H */

