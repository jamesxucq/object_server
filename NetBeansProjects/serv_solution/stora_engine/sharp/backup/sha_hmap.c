#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sha_hmap.h"

#define hashinde(key, smap) ((smap->gethash)(key) % (smap->hashsize))

inline struct sha_node *snod_new(void *key, void *data) {
    struct sha_node *snod = malloc(sizeof (struct sha_node));
    if(!snod) return NULL;
    snod->key = key;
    snod->data = data;
    snod->next = NULL;
    return snod;
}

void slist_append(struct sha_node **root, void *key, void *data) {
    struct sha_node *new, *posi;
    //
    new = snod_new(key, data);
    if (NULL == *root) {
        *root = new;
    } else {
        for (posi = *root; NULL != posi->next; posi = posi->next);
        posi->next = new;
    }
}

int slist_update(struct sha_node *root, void *key, void *data, int (*compare)(void *, void *)) {
    struct sha_node *posi;
    for (posi = root; NULL != posi; posi = posi->next) {
        if (compare(key, posi->key)) {
            posi->data = data;
            return 0;
        }
    }
    return -1;
}

inline struct sha_node *snod_dele(struct sha_node *nod) {
    struct sha_node *next = nod->next;
    free(nod);
    return (next);
}

int slist_remove(struct sha_node **root, void *key, int (*compare)(void *, void *)) {
    struct sha_node *posi, *prev;
    //
    if (NULL == *root) return -1;
    if (compare((*root)->key, key)) {
        *root = snod_dele(*root);
        return 0;
    }
    //
    prev = *root;
    for (posi = prev->next; NULL != posi; posi = posi->next) {
        if (compare(posi->key, key)) {
            prev->next = snod_dele(posi);
            return 0;
        }
        prev = posi;
    }
    return -1;
}

shamap *sha_create(unsigned int (*keyfunc)(void *), int (*compare)(void *, void *), unsigned int size) {
    int length = sizeof (struct sha_node *) * size;
    //
    shamap *smap = (shamap *) malloc(sizeof (shamap));
    if(!smap) return NULL;
    memset(smap, '\0', sizeof (shamap));
    smap->gethash = keyfunc;
    smap->compare = compare;
    smap->hashsize = size;
    smap->count = 0;
    //
    smap->hmaplist = malloc(length);
    if (NULL == smap->hmaplist) {
        free(smap);
        return NULL;
    }
    memset(smap->hmaplist, '\0', length);
    //
    return smap;
}

void sha_dele(shamap *smap) {
    unsigned int inde;
    struct sha_node *posi;
    //
    if (NULL == smap) return;
    for (inde = 0; inde < smap->hashsize; inde++)
        for (posi = smap->hmaplist[inde]; NULL != posi; posi = snod_dele(posi));
    //
    free(smap->hmaplist);
    free(smap);
}

void sha_insert(void *key, void *data, shamap *smap) {
    unsigned int inde = hashinde(key, smap);
    struct sha_node *root = smap->hmaplist[inde];
    //
    if (0 != slist_update(root, key, data, smap->compare)) { //(1)
        slist_append(&(smap->hmaplist[inde]), key, data);
        smap->count++;
    }
}

void sha_remove(void *key, shamap *smap) {
    unsigned int inde = hashinde(key, smap);
    if (0 == slist_remove(&(smap->hmaplist[inde]), key, smap->compare)) {
        smap->count--;
    }
}

void *sha_value(void *key, shamap *smap) {
    struct sha_node *posi;
    unsigned int inde = hashinde(key, smap);
    for (posi = smap->hmaplist[inde]; NULL != posi; posi = posi->next) {
        if (smap->compare(key, posi->key)) {
            return (posi->data);
        }
    }
    return NULL;
}

void sha_for_each_do(shamap *smap, int (call_back) (void *, void *)) {
    unsigned int inde = 0;
    struct sha_node *posi;
    for (inde = 0; inde < smap->hashsize; inde++) {
        for (posi = smap->hmaplist[inde]; NULL != posi; posi = posi->next) {
            call_back(posi->key, posi->data);
        }
    }
}

inline int sha_count(shamap *smap) {
    return smap->count;
}

