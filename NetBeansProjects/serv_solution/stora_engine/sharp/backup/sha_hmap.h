/* 
 * File:   sha_hmap.h
 * Author: Administrator
 */

#ifndef SHAHMAP_H
#define	SHAHMAP_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <string.h>

struct sha_node {
    void *key;
    void *data;
    struct sha_node *next;
};

struct _shamap_ {
    unsigned int (*gethash)(void *);
    int (*compare)(void *, void *);
    unsigned int hashsize;
    unsigned int count;
    struct sha_node **hmaplist;
};

typedef struct _shamap_ shamap;

shamap *sha_create(unsigned int (*keyfunc)(void *), int (*compare)(void *, void *), unsigned int size);
void sha_dele(shamap *smap);
void sha_insert(void *key, void *data, shamap *smap);
void sha_remove(void *key, shamap *smap);
void *sha_value(void *key, shamap *smap);
void sha_for_each_do(shamap *smap, int (call_back) (void *, void *));
int sha_count(shamap *smap);

#ifdef	__cplusplus
}
#endif

#endif	/* SHAHMAP_H */

