#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "jemalloc/jemalloc.h"
#include "hash_table.h"

#define HASH_INDE(KEY, HTAB) ((HTAB->gethash)(KEY) % (HTAB->hashsize))
#define SUM2HEX(SUM, HTAB) ((SUM) % (HTAB->hashsize))

static struct tab_nod *tnod_new(const void *key, void *data) {
    struct tab_nod *tnod = malloc(sizeof (struct tab_nod));
    if (!tnod) return NULL;
    tnod->key = key;
    tnod->data = data;
    tnod->next = NULL;
    return tnod;
}

static void hlist_append(struct tab_nod **root, const void *key, void *data) {
    struct tab_nod *new, *posi;
    //
    new = tnod_new(key, data);
    if (NULL == *root) {
        *root = new;
    } else {
        for (posi = *root; NULL != posi->next; posi = posi->next);
        posi->next = new;
    }
}

static int hlist_update(struct tab_nod *root, const void *key, void *data, int (*compare)(const void *, const void *)) {
    struct tab_nod *posi;
    for (posi = root; NULL != posi; posi = posi->next) {
        if (compare(key, posi->key)) {
            posi->data = data;
            return 0x00;
        }
    }
    return -1;
}

static inline struct tab_nod *tnod_dele(struct tab_nod *tnod) {
    struct tab_nod *next = tnod->next;
    free(tnod);
    return (next);
}

static inline void tnod_link_dele(struct tab_nod *tnod) {
    struct tab_nod *next;
    for (; tnod; tnod = next) {
        next = tnod->next;
        free(tnod);
    }
}

static int hlist_remove(struct tab_nod **root, const void *key, int (*compare)(const void *, const void *)) {
    struct tab_nod *posi, *prev;
    //
    if (NULL == *root) return 0x00;
    if (compare(key, (*root)->key)) {
        *root = tnod_dele(*root);
        return 0x00;
    }
    //
    prev = *root;
    for (posi = prev->next; NULL != posi; posi = posi->next) {
        if (compare(key, posi->key)) {
            prev->next = tnod_dele(posi);
            return 0x00;
        }
        prev = posi;
    }
    //
    return -1;
}

hashtable *hash_create(unsigned int (*keyfunc)(const void *), int (*compare)(const void *, const void *), unsigned int size) {
    int length = sizeof (struct tab_nod *) * size;
    //
    hashtable *htab = malloc(sizeof (hashtable));
    if (!htab) return NULL;
    htab->gethash = keyfunc;
    htab->compare = compare;
    htab->hashsize = size;
    htab->count = 0x00;
    //
    htab->hashlist = malloc(length);
    if (NULL == htab->hashlist) {
        free(htab);
        return NULL;
    }
    memset(htab->hashlist, '\0', length);
    //
    return htab;
}

void hash_destroy(hashtable *htab) {
    if (NULL == htab) return;
    //
    unsigned int inde = 0x00;
    for (; inde < htab->hashsize; ++inde)
        tnod_link_dele(htab->hashlist[inde]);
    //
    free(htab->hashlist);
    free(htab);
}

void hash_insert(const void *key, void *data, hashtable *htab) {
    unsigned int inde = HASH_INDE(key, htab);
    struct tab_nod *root = htab->hashlist[inde];
    //
    if (0x00 != hlist_update(root, key, data, htab->compare)) { //(1)
        hlist_append(&(htab->hashlist[inde]), key, data);
        htab->count++;
    }
}

void hash_insert_adler32(const void *key, void *data, unsigned int sum, hashtable *htab) {
    unsigned int inde = SUM2HEX(sum, htab);
    struct tab_nod *root = htab->hashlist[inde];
    //
    if (0x00 != hlist_update(root, key, data, htab->compare)) { //(1)
        hlist_append(&(htab->hashlist[inde]), key, data);
        htab->count++;
    }
}

void hash_remove(const void *key, hashtable *htab) {
    unsigned int inde = HASH_INDE(key, htab);
    if (0x00 == hlist_remove(&(htab->hashlist[inde]), key, htab->compare)) {
        htab->count--;
    }
}

void *hash_value(const void *key, hashtable *htab) {
    struct tab_nod *posi;
    unsigned int inde = HASH_INDE(key, htab);
    for (posi = htab->hashlist[inde]; NULL != posi; posi = posi->next) {
        if (htab->compare(key, posi->key)) {
            return (posi->data);
        }
    }
    return NULL;
}

struct tab_nod *hash_value_adler32(unsigned int sum, hashtable *htab) {
    unsigned int inde = SUM2HEX(sum, htab);
    return htab->hashlist[inde];
}

void *hash_value_md5(const void *key, struct tab_nod *root, hashtable *htab) {
    struct tab_nod *posi;
    //
    for (posi = root; NULL != posi; posi = posi->next) {
        if (htab->compare(key, posi->key)) {
            return (posi->data);
        }
    }
    return NULL;
}

void hash_for_each_do(hashtable *htab, int(*call_back) (const void *, void *)) {
    struct tab_nod *posi;
    unsigned int inde = 0x00;
    for (; inde < htab->hashsize; ++inde) {
        for (posi = htab->hashlist[inde]; NULL != posi; posi = posi->next) {
            call_back(posi->key, posi->data);
        }
    }
}


