#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "jemalloc/jemalloc.h"
#include "hash_map.h"

#define SUM2HEX(SUM, HMAP) ((SUM) % (HMAP->hashsize))

static struct map_nod *mnod_new(unsigned int key, void *data) {
    struct map_nod *mnod = malloc(sizeof (struct map_nod));
    if (!mnod) return NULL;
    mnod->key = key;
    mnod->data = data;
    mnod->next = NULL;
    return mnod;
}

static void mlist_append(struct map_nod **root, unsigned int key, void *data) {
    struct map_nod *new, *posi;
    //
    new = mnod_new(key, data);
    if (NULL == *root) {
        *root = new;
    } else {
        for (posi = *root; NULL != posi->next; posi = posi->next);
        posi->next = new;
    }
}

static int mlist_update(struct map_nod *root, unsigned int key, void *data, void (*freefunc)(void *)) {
    struct map_nod *posi;
    for (posi = root; NULL != posi; posi = posi->next) {
        if (key == posi->key) {
            freefunc(posi->data);
            posi->data = data;
            return 0x00;
        }
    }
    return -1;
}

static inline struct map_nod *mnod_dele(struct map_nod *mnod, void (*freefunc)(void *)) {
    struct map_nod *next = mnod->next;
    freefunc(mnod->data);
    free(mnod);
    return (next);
}

static inline void mnod_link_dele(struct map_nod *mnod, void (*freefunc)(void *)) {
    struct map_nod *next;
    for (; mnod; mnod = next) {
        next = mnod->next;
        freefunc(mnod->data);
        free(mnod);
    }
}

static int mlist_remove(struct map_nod **root, unsigned int key, void (*freefunc)(void *)) {
    struct map_nod *posi, *prev;
    //
    if (NULL == *root) return 0x00;
    if ((*root)->key == key) {
        *root = mnod_dele(*root, freefunc);
        return 0x00;
    }
    //
    prev = *root;
    for (posi = prev->next; NULL != posi; posi = posi->next) {
        if (posi->key == key) {
            prev->next = mnod_dele(posi, freefunc);
            return 0x00;
        }
        prev = posi;
    }
    //
    return -1;
}

hashmap *hmap_create(void (*freefunc)(void *), unsigned int size) {
    int length = sizeof (struct map_nod *) * size;
    //
    hashmap *hmap = malloc(sizeof (hashmap));
    if (!hmap)return NULL;
    hmap->freefunc = freefunc;
    hmap->hashsize = size;
    hmap->count = 0x00;
    //
    hmap->hmaplist = malloc(length);
    if (NULL == hmap->hmaplist) {
        free(hmap);
        return NULL;
    }
    memset(hmap->hmaplist, '\0', length);
    //
    return hmap;
}

void hmap_destroy(hashmap *hmap) {
    if (NULL == hmap) return;
    //
    unsigned int inde = 0x00;
    for (; inde < hmap->hashsize; ++inde)
        mnod_link_dele(hmap->hmaplist[inde], hmap->freefunc);
    //
    free(hmap->hmaplist);
    free(hmap);
}

void hmap_clear(hashmap *hmap) {
    if (NULL == hmap) return;
    //
    unsigned int inde = 0x00;
    for (; inde < hmap->hashsize; ++inde)
        mnod_link_dele(hmap->hmaplist[inde], hmap->freefunc);
    //
    memset(hmap->hmaplist, '\0', sizeof (struct map_nod *) * hmap->hashsize);
    hmap->count = 0x00;
}

void hmap_insert(unsigned int key, void *data, hashmap *hmap) {
    unsigned int inde = SUM2HEX(key, hmap);
    struct map_nod *root = hmap->hmaplist[inde];
    //
    if (0x00 != mlist_update(root, key, data, hmap->freefunc)) { //(1)
        mlist_append(&(hmap->hmaplist[inde]), key, data);
        hmap->count++;
    }
}

void hmap_remove(unsigned int key, hashmap *hmap) {
    unsigned int inde = SUM2HEX(key, hmap);
    if (0x00 == mlist_remove(&(hmap->hmaplist[inde]), key, hmap->freefunc)) {
        hmap->count--;
    }
}

void *hmap_value(unsigned int key, hashmap *hmap) {
    struct map_nod *posi;
    unsigned int inde = SUM2HEX(key, hmap);
    for (posi = hmap->hmaplist[inde]; NULL != posi; posi = posi->next) {
        if (key == posi->key) {
            return (posi->data);
        }
    }
    return NULL;
}

void hmap_for_each_do(hashmap *hmap, int(*call_back) (unsigned int, void *)) {
    struct map_nod *posi;
    unsigned int inde = 0x00;
    for (; inde < hmap->hashsize; ++inde) {
        for (posi = hmap->hmaplist[inde]; NULL != posi; posi = posi->next) {
            call_back(posi->key, posi->data);
        }
    }
}


