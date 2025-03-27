#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "riv_hmap.h"

#define hashinde(key, rmap) ((rmap->gethash)(key) % (rmap->hashsize))

inline struct rive_node *cnod_new(void *key, void *data) {
    struct rive_node *cnod = malloc(sizeof (struct rive_node));
    if(!cnod) return NULL;
    cnod->key = key;
    cnod->data = data;
    cnod->next = NULL;
    return cnod;
}

void clist_append(struct rive_node **root, void *key, void *data) {
    struct rive_node *new, *posi;
    //
    new = cnod_new(key, data);
    if (NULL == *root) {
        *root = new;
    } else {
        for (posi = *root; NULL != posi->next; posi = posi->next);
        posi->next = new;
    }
}

int clist_update(struct rive_node *root, void *key, void *data, int (*compare)(void *, void *)) {
    struct rive_node *posi;
    for (posi = root; NULL != posi; posi = posi->next) {
        if (compare(key, posi->key)) {
            posi->data = data;
            return 0;
        }
    }
    return -1;
}

inline struct rive_node *cnod_dele(struct rive_node *nod) {
    struct rive_node *next = nod->next;
    free(nod);
    return (next);
}

int clist_remove(struct rive_node **root, void *key, int (*compare)(void *, void *)) {
    struct rive_node *posi, *prev;
    //
    if (NULL == *root) return -1;
    if (compare((*root)->key, key)) {
        *root = cnod_dele(*root);
        return 0;
    }
    //
    prev = *root;
    for (posi = prev->next; NULL != posi; posi = posi->next) {
        if (compare(posi->key, key)) {
            prev->next = cnod_dele(posi);
            return 0;
        }
        prev = posi;
    }
    return -1;
}

rivhmap *rive_create(unsigned int (*keyfunc)(void *), int (*compare)(void *, void *), unsigned int size) {
    int length = sizeof (struct rive_node *) * size;
    //
    rivhmap *rmap = (rivhmap *) malloc(sizeof (rivhmap));
    if(!rmap) return NULL;
    memset(rmap, '\0', sizeof (rivhmap));
    rmap->gethash = keyfunc;
    rmap->compare = compare;
    rmap->hashsize = size;
    rmap->count = 0;
    //
    rmap->hmaplist = malloc(length);
    if (NULL == rmap->hmaplist) {
        free(rmap);
        return NULL;
    }
    memset(rmap->hmaplist, '\0', length);
    //
    return rmap;
}

void rive_dele(rivhmap *rmap) {
    unsigned int inde;
    struct rive_node *posi;
    //
    if (NULL == rmap) return;
    for (inde = 0; inde < rmap->hashsize; inde++)
        for (posi = rmap->hmaplist[inde]; NULL != posi; posi = cnod_dele(posi));
    //
    free(rmap->hmaplist);
    free(rmap);
}

void rive_insert(void *key, void *data, rivhmap *rmap) {
    unsigned int inde = hashinde(key, rmap);
    struct rive_node *root = rmap->hmaplist[inde];
    //
    if (0 != clist_update(root, key, data, rmap->compare)) { //(1)
        clist_append(&(rmap->hmaplist[inde]), key, data);
        rmap->count++;
    }
}

void rive_remove(void *key, rivhmap *rmap) {
    unsigned int inde = hashinde(key, rmap);
    if (0 == clist_remove(&(rmap->hmaplist[inde]), key, rmap->compare)) {
        rmap->count--;
    }
}

void *rive_value(void *key, rivhmap *rmap) {
    struct rive_node *posi;
    unsigned int inde = hashinde(key, rmap);
    for (posi = rmap->hmaplist[inde]; NULL != posi; posi = posi->next) {
        if (rmap->compare(key, posi->key)) {
            return (posi->data);
        }
    }
    return NULL;
}

void rive_for_each_do(rivhmap *rmap, int (call_back) (void *, void *)) {
    unsigned int inde = 0;
    struct rive_node *posi;
    for (inde = 0; inde < rmap->hashsize; inde++) {
        for (posi = rmap->hmaplist[inde]; NULL != posi; posi = posi->next) {
            call_back(posi->key, posi->data);
        }
    }
}

inline int rive_count(rivhmap *rmap) {
    return rmap->count;
}

