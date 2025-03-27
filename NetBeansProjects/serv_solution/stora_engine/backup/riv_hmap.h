/* 
 * File:   riv_hash.h
 * Author: Administrator
 */

#ifndef RIV_HASH_H
#define	RIV_HASH_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <string.h>

struct rive_node {
    void *key;
    void *data;
    struct rive_node *next;
};

struct _rivhmap_ {
    unsigned int (*gethash)(void *);
    int (*compare)(void *, void *);
    unsigned int hashsize;
    unsigned int count;
    struct rive_node **hmaplist;
};

typedef struct _rivhmap_ rivhmap;

rivhmap *rive_create(unsigned int (*keyfunc)(void *), int (*compare)(void *, void *), unsigned int size);
void rive_dele(rivhmap *rmap);
void rive_insert(void *key, void *data, rivhmap *rmap);
void rive_remove(void *key, rivhmap *rmap);
void *rive_value(void *key, rivhmap *rmap);
void rive_for_each_do(rivhmap *rmap, int (call_back) (void *, void *));
int rive_count(rivhmap *rmap);

#ifdef	__cplusplus
}
#endif

#endif	/* RIV_HASH_H */

