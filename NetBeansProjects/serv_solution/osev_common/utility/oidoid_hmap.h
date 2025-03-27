
/* 
 * File:   oidoid_hmap.h
 * Author: James Xu
 *
 * Created on 2024.1.10, PM 5:40
 */

#ifndef OIDOID_HMAP_H
#define OIDOID_HMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

    struct ooid_node {
        const void *key1;
        const void *key2;
        void *data;
        //
        struct ooid_node *next;
    };

    struct _oidoidmap_ {
        unsigned int (*gethash)(const void *, const void *);
        int (*compare)(const void *, const void *, const void *, const void *);
        void (*freefunc)(void *);
        unsigned int hashsize;
        unsigned int count;
        struct ooid_node **hmaplist;
    };

    typedef struct _oidoidmap_ oidoidmap;

    // size = 2^n
    oidoidmap *oidoid_create(unsigned int (*keyfunc)(const void *, const void *), int (*compare)(const void *, const void *, const void *, const void *), void (*freefunc)(void *), unsigned int size);
    void oidoid_destroy(oidoidmap *omap);
    void oidoid_clear(oidoidmap *omap);
    void oidoid_insert(const void *key1, const void *key2, void *data, oidoidmap *omap);
    void oidoid_remove(const void *key1, const void *key2, oidoidmap *omap);
    void *oidoid_value(const void *key1, const void *key2, oidoidmap *omap);
    void oidoid_for_each_do(oidoidmap *omap, int (*call_back) (const void *, const void *, void *));
    //

    inline int oidoid_count(oidoidmap *omap) {
        return omap->count;
    }

#ifdef __cplusplus
}
#endif

#endif /* OIDOID_HMAP_H */

