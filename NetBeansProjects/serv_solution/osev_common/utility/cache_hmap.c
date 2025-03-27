#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "jemalloc/jemalloc.h"
#include "cache_hmap.h"

// #define HASH_INDE(key, cmap) ((cmap->gethash)(key) % (cmap->hashsize))
// #define POW2N_MOD(nua, nub)  (nua & (nub - 0x01)) // x=2^n a=b%x-->a=b&(x-1)
#define HASH_INDE(KEY, CMAP) ((CMAP->gethash)(KEY) & (CMAP->hashsize - 0x01))

static struct cache_node *cnod_new(const void *key, void *data) {
    struct cache_node *cnod = malloc(sizeof (struct cache_node));
    if (!cnod) return NULL;
    cnod->key = key;
    cnod->data = data;
    cnod->next = NULL;
    return cnod;
}

static void clist_append(struct cache_node **root, const void *key, void *data) {
    struct cache_node *new, *posi;
    //
    new = cnod_new(key, data);
    if (NULL == *root) {
        *root = new;
    } else {
        for (posi = *root; NULL != posi->next; posi = posi->next);
        posi->next = new;
    }
}

static int clist_update(struct cache_node *root, const void *key, void *data, int (*compare)(const void *, const void *)) {
    struct cache_node *posi;
    for (posi = root; NULL != posi; posi = posi->next) {
        if (compare(key, posi->key)) {
            posi->data = data;
            return 0x00;
        }
    }
    return -1;
}

static inline struct cache_node *cnod_dele(struct cache_node *cnod) {
    struct cache_node *next = cnod->next;
    free(cnod);
    return (next);
}

static inline void cnod_link_dele(struct cache_node *cnod) {
    struct cache_node *next;
    for (; cnod; cnod = next) {
        next = cnod->next;
        free(cnod);
    }
}

static int clist_remove(struct cache_node **root, const void *key, int (*compare)(const void *, const void *)) {
    struct cache_node *posi, *prev;
    //
    if (NULL == *root) return 0x00;
    if (compare(key, (*root)->key)) {
        *root = cnod_dele(*root);
        return 0x00;
    }
    //
    prev = *root;
    for (posi = prev->next; NULL != posi; posi = posi->next) {
        if (compare(key, posi->key)) {
            prev->next = cnod_dele(posi);
            return 0x00;
        }
        prev = posi;
    }
    //
    return -1;
}

cachemap *cache_create(unsigned int (*keyfunc)(const void *), int (*compare)(const void *, const void *), unsigned int size) {
    int length = sizeof (struct cache_node *) * size;
    //
    cachemap *cmap = (cachemap *) malloc(sizeof (cachemap));
    if (!cmap) return NULL;
    cmap->gethash = keyfunc;
    cmap->compare = compare;
    cmap->hashsize = size;
    cmap->count = 0x00;
    //
    cmap->hmaplist = malloc(length);
    if (NULL == cmap->hmaplist) {
        free(cmap);
        return NULL;
    }
    memset(cmap->hmaplist, '\0', length);
    //
    return cmap;
}

void cache_destroy(cachemap *cmap) {
    if (NULL == cmap) return;
    //
    unsigned int inde = 0x00;
    for (; inde < cmap->hashsize; ++inde)
        cnod_link_dele(cmap->hmaplist[inde]);
    //
    free(cmap->hmaplist);
    free(cmap);
}

void cache_clear(cachemap *cmap) {
    if (NULL == cmap) return;
    //
    unsigned int inde = 0x00;
    for (; inde < cmap->hashsize; ++inde)
        cnod_link_dele(cmap->hmaplist[inde]);
    //
    memset(cmap->hmaplist, '\0', sizeof (struct cache_node *) * cmap->hashsize);
    cmap->count = 0x00;
}

void cache_insert(const void *key, void *data, cachemap *cmap) {
    unsigned int inde = HASH_INDE(key, cmap);
    struct cache_node *root = cmap->hmaplist[inde];
    //
    if (0x00 != clist_update(root, key, data, cmap->compare)) { //(1)
        clist_append(&(cmap->hmaplist[inde]), key, data);
        cmap->count++;
    }
}

void cache_remove(const void *key, cachemap *cmap) {
    unsigned int inde = HASH_INDE(key, cmap);
    if (0x00 == clist_remove(&(cmap->hmaplist[inde]), key, cmap->compare)) {
        cmap->count--;
    }
}

void *cache_value(const void *key, cachemap *cmap) {
    struct cache_node *posi;
    unsigned int inde = HASH_INDE(key, cmap);
    for (posi = cmap->hmaplist[inde]; NULL != posi; posi = posi->next) {
        if (cmap->compare(key, posi->key)) {
            return (posi->data);
        }
    }
    return NULL;
}

void cache_for_each_do(cachemap *cmap, int (*call_back) (const void *, void *)) {
    struct cache_node *posi;
    unsigned int inde = 0x00;
    for (; inde < cmap->hashsize; ++inde) {
        for (posi = cmap->hmaplist[inde]; NULL != posi; posi = posi->next) {
            call_back(posi->key, posi->data);
        }
    }
}

void cache_each_data(cachemap *cmap, void (*call_back) (void *)) {
    struct cache_node *posi;
    unsigned int inde = 0x00;
    for (; inde < cmap->hashsize; ++inde) {
        for (posi = cmap->hmaplist[inde]; NULL != posi; posi = posi->next) {
            call_back(posi->data);
        }
    }
}