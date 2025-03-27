#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "jemalloc/jemalloc.h"
#include "action_hmap.h"

// #define HASH_INDE(key, amap) ((amap->gethash)(key) % (amap->hashsize))
// #define POW2N_MOD(nua, nub)  (nua & (nub - 0x01)) // x=2^n a=b%x-->a=b&(x-1)
#define HASH_INDE(KEY, AMAP) ((AMAP->gethash)(KEY) & (AMAP->hashsize - 0x01))

static struct acti_node *anod_new(const void *key, void *data) {
    struct acti_node *anod = malloc(sizeof (struct acti_node));
    if (!anod) return NULL;
    anod->key = key;
    anod->data = data;
    anod->next = NULL;
    return anod;
}

static void alist_append(struct acti_node **root, const void *key, void *data) {
    struct acti_node *new, *posi;
    //
    new = anod_new(key, data);
    if (NULL == *root) {
        *root = new;
    } else {
        for (posi = *root; NULL != posi->next; posi = posi->next);
        posi->next = new;
    }
}

static int alist_update(struct acti_node *root, const void *key, void *data, int (*compare)(const void *, const void *)) {
    struct acti_node *posi;
    for (posi = root; NULL != posi; posi = posi->next) {
        if (compare(key, posi->key)) {
            posi->data = data;
            return 0x00;
        }
    }
    return -1;
}

static inline struct acti_node *anod_dele(struct acti_node *anod, void (*freefunc)(void *)) {
    struct acti_node *next = anod->next;
    freefunc(anod->data);
    free(anod);
    return (next);
}

static inline void anod_link_dele(struct acti_node *anod, void (*freefunc)(void *)) {
    struct acti_node *next;
    for (; anod; anod = next) {
        next = anod->next;
        freefunc(anod->data);
        free(anod);
    }
}

static int alist_remove(struct acti_node **root, const void *key, int (*compare)(const void *, const void *), void (*freefunc)(void *)) {
    struct acti_node *posi, *prev;
    if (NULL == *root) return 0x00;
    if (compare(key, (*root)->key)) {
        *root = anod_dele(*root, freefunc);
        return 0x00;
    }
    //
    prev = *root;
    for (posi = prev->next; NULL != posi; posi = posi->next) {
        if (compare(key, posi->key)) {
            prev->next = anod_dele(posi, freefunc);
            return 0x00;
        }
        prev = posi;
    }
    //
    return -1;
}

actionmap *action_create(unsigned int (*keyfunc)(const void *), int (*compare)(const void *, const void *), void (*freefunc)(void *), unsigned int size) {
    int length = sizeof (struct acti_node *) * size;
    //
    actionmap *amap = (actionmap *) malloc(sizeof (actionmap));
    if (!amap) return NULL;
    amap->gethash = keyfunc;
    amap->compare = compare;
    amap->freefunc = freefunc;
    amap->hashsize = size;
    amap->count = 0x00;
    //
    amap->hmaplist = malloc(length);
    if (NULL == amap->hmaplist) {
        free(amap);
        return NULL;
    }
    memset(amap->hmaplist, '\0', length);
    //
    return amap;
}

void action_destroy(actionmap *amap) {
    if (NULL == amap) return;
    //
    unsigned int inde = 0x00;
    for (; inde < amap->hashsize; ++inde)
        anod_link_dele(amap->hmaplist[inde], amap->freefunc);
    //
    free(amap->hmaplist);
    free(amap);
}

void action_clear(actionmap *amap) {
    if (NULL == amap) return;
    //
    unsigned int inde = 0x00;
    for (; inde < amap->hashsize; ++inde)
        anod_link_dele(amap->hmaplist[inde], amap->freefunc);
    //
    memset(amap->hmaplist, '\0', sizeof (struct acti_node *) * amap->hashsize);
    amap->count = 0x00;
}

void action_insert(const void *key, void *data, actionmap *amap) {
    // printf("action_insert, key:|%s|\n", (char *) key);
    unsigned int inde = HASH_INDE(key, amap);
    struct acti_node *root = amap->hmaplist[inde];
    // printf("inde:%u\n", inde);
    if (0x00 != alist_update(root, key, data, amap->compare)) { //(1)
        alist_append(&(amap->hmaplist[inde]), key, data);
        amap->count++;
    }
}

void action_remove(const void *key, actionmap *amap) {
    unsigned int inde = HASH_INDE(key, amap);
    if (0x00 == alist_remove(&(amap->hmaplist[inde]), key, amap->compare, amap->freefunc)) {
        amap->count--;
    }
}

void *action_value(const void *key, actionmap *amap) {
    // printf("action_value, key:|%s|\n", (char *) key);
    struct acti_node *posi;
    unsigned int inde = HASH_INDE(key, amap);
    // printf("inde:%u\n", inde);
    for (posi = amap->hmaplist[inde]; NULL != posi; posi = posi->next) {
        // printf("posi->key:|%s|\n", (char *) posi->key);
        if (amap->compare(key, posi->key)) {
            return (posi->data);
        }
    }
    return NULL;
}

void action_for_each_do(actionmap *amap, int (*call_back) (const void *, void *)) {
    struct acti_node *posi;
    unsigned int inde = 0x00;
    for (; inde < amap->hashsize; ++inde) {
        for (posi = amap->hmaplist[inde]; NULL != posi; posi = posi->next) {
            call_back(posi->key, posi->data);
        }
    }
}


