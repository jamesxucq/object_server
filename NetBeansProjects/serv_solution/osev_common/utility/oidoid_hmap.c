#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "jemalloc/jemalloc.h"
#include "oidoid_hmap.h"

// #define HASH_INDE(key1, key2, omap) ((omap->gethash)(key1, key2) % (omap->hashsize))
// #define POW2N_MOD(nua, nub)  (nua & (nub - 0x01)) // x=2^n a=b%x-->a=b&(x-1)
#define HASH_INDE(KEY1, KEY2, OMAP) ((OMAP->gethash)(KEY1, KEY2) & (OMAP->hashsize - 0x01))

static struct ooid_node *onod_new(const void *key1, const void *key2, void *data) {
    struct ooid_node *onod = malloc(sizeof (struct ooid_node));
    if (!onod) return NULL;
    onod->key1 = key1;
    onod->key2 = key2;
    onod->data = data;
    onod->next = NULL;
    return onod;
}

static void olist_append(struct ooid_node **root, const void *key1, const void *key2, void *data) {
    struct ooid_node *new, *posi;
    //
    new = onod_new(key1, key2, data);
    if (NULL == *root) {
        *root = new;
    } else {
        for (posi = *root; NULL != posi->next; posi = posi->next);
        posi->next = new;
    }
}

static int olist_update(struct ooid_node *root, const void *key1, const void *key2, void *data, int (*compare)(const void *, const void *, const void *, const void *)) {
    struct ooid_node *posi;
    for (posi = root; NULL != posi; posi = posi->next) {
        if (compare(key1, posi->key1, key2, posi->key2)) {
            posi->data = data;
            return 0x00;
        }
    }
    return -1;
}

static inline struct ooid_node *onod_dele(struct ooid_node *onod, void (*freefunc)(void *)) {
    struct ooid_node *next = onod->next;
    freefunc(onod->data);
    free(onod);
    return (next);
}

static inline void onod_link_dele(struct ooid_node *onod, void (*freefunc)(void *)) {
    struct ooid_node *next;
    for (; onod; onod = next) {
        next = onod->next;
        freefunc(onod->data);
        free(onod);
    }
}

static int olist_remove(struct ooid_node **root, const void *key1, const void *key2, int (*compare)(const void *, const void *, const void *, const void *), void (*freefunc)(void *)) {
    struct ooid_node *posi, *prev;
    if (NULL == *root) return 0x00;
    if (compare(key1, (*root)->key1, key2, (*root)->key2)) {
        *root = onod_dele(*root, freefunc);
        return 0x00;
    }
    //
    prev = *root;
    for (posi = prev->next; NULL != posi; posi = posi->next) {
        if (compare(key1, posi->key1, key2, posi->key2)) {
            prev->next = onod_dele(posi, freefunc);
            return 0x00;
        }
        prev = posi;
    }
    //
    return -1;
}

oidoidmap *oidoid_create(unsigned int (*keyfunc)(const void *, const void *), int (*compare)(const void *, const void *, const void *, const void *), void (*freefunc)(void *), unsigned int size) {
    int length = sizeof (struct ooid_node *) * size;
    //
    oidoidmap *omap = (oidoidmap *) malloc(sizeof (oidoidmap));
    if (!omap) return NULL;
    omap->gethash = keyfunc;
    omap->compare = compare;
    omap->freefunc = freefunc;
    omap->hashsize = size;
    omap->count = 0x00;
    //
    omap->hmaplist = malloc(length);
    if (NULL == omap->hmaplist) {
        free(omap);
        return NULL;
    }
    memset(omap->hmaplist, '\0', length);
    //

    return omap;
}

void oidoid_destroy(oidoidmap *omap) {
    if (NULL == omap) return;
    //
    unsigned int inde = 0x00;
    for (; inde < omap->hashsize; ++inde)
        onod_link_dele(omap->hmaplist[inde], omap->freefunc);
    //
    free(omap->hmaplist);
    free(omap);
}

void oidoid_clear(oidoidmap *omap) {
    if (NULL == omap) return;
    //
    unsigned int inde = 0x00;
    for (; inde < omap->hashsize; ++inde)
        onod_link_dele(omap->hmaplist[inde], omap->freefunc);
    //
    memset(omap->hmaplist, '\0', sizeof (struct ooid_node *) * omap->hashsize);
    omap->count = 0x00;
}

void oidoid_insert(const void *key1, const void *key2, void *data, oidoidmap *omap) {
    // printf("oidoid_insert, key:|%s|\n", (char *) key);
    unsigned int inde = HASH_INDE(key1, key2, omap);
    struct ooid_node *root = omap->hmaplist[inde];
    // printf("inde:%u\n", inde);
    if (0x00 != olist_update(root, key1, key2, data, omap->compare)) { //(1)
        olist_append(&(omap->hmaplist[inde]), key1, key2, data);
        omap->count++;
    }
}

void oidoid_remove(const void *key1, const void *key2, oidoidmap *omap) {
    unsigned int inde = HASH_INDE(key1, key2, omap);
    if (0x00 == olist_remove(&(omap->hmaplist[inde]), key1, key2, omap->compare, omap->freefunc)) {
        omap->count--;
    }
}

void *oidoid_value(const void *key1, const void *key2, oidoidmap *omap) {
    // printf("oidoid_value, key:|%s|\n", (char *) key);
    struct ooid_node *posi;
    unsigned int inde = HASH_INDE(key1, key2, omap);
    // printf("inde:%u\n", inde);
    for (posi = omap->hmaplist[inde]; NULL != posi; posi = posi->next) {
        // printf("posi->key:|%s|\n", (char *) posi->key);
        if (omap->compare(key1, posi->key1, key2, posi->key2)) {
            return (posi->data);
        }
    }
    return NULL;
}

void oidoid_for_each_do(oidoidmap *omap, int (*call_back) (const void *, const void *, void *)) {
    struct ooid_node *posi;
    unsigned int inde = 0x00;
    for (; inde < omap->hashsize; ++inde) {
        for (posi = omap->hmaplist[inde]; NULL != posi; posi = posi->next) {
            call_back(posi->key1, posi->key2, posi->data);
        }
    }
}


