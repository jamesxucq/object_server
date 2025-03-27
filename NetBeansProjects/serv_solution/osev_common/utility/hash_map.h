#ifndef _HASH_MAP_H
#define _HASH_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

    struct map_nod {
        unsigned int key;
        void *data;
        //
        struct map_nod *next;
    };

    struct _hashmap_ {
        void (*freefunc)(void *);
        unsigned int hashsize;
        unsigned int count;
        struct map_nod **hmaplist;
    };

    typedef struct _hashmap_ hashmap;

    // size = 2^n
    hashmap *hmap_create(void (*freefunc)(void *), unsigned int size);
    void hmap_destroy(hashmap *hmap);
    void hmap_clear(hashmap *hmap);
    void hmap_insert(unsigned int key, void *data, hashmap *hmap);
    void hmap_remove(unsigned int key, hashmap *hmap);
    void *hmap_value(unsigned int key, hashmap *hmap);
    void hmap_for_each_do(hashmap *hmap, int (*call_back) (unsigned int, void *));
    //

    inline int hmap_count(hashmap *hmap) {
        return hmap->count;
    }

#ifdef __cplusplus
}
#endif

#endif

