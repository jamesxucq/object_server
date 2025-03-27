/* 
 * File:   action_hmap.h
 * Author: James Xu
 */

#ifndef ACTION_HMAP_H
#define ACTION_HMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

    struct acti_node {
        const void *key;
        void *data;
        //
        struct acti_node *next;
    };

    struct _actionmap_ {
        unsigned int (*gethash)(const void *);
        int (*compare)(const void *, const void *);
        void (*freefunc)(void *);
        unsigned int hashsize;
        unsigned int count;
        struct acti_node **hmaplist;
    };

    typedef struct _actionmap_ actionmap;

    // size = 2^n
    actionmap *action_create(unsigned int (*keyfunc)(const void *), int (*compare)(const void *, const void *), void (*freefunc)(void *), unsigned int size);
    void action_destroy(actionmap *amap);
    void action_clear(actionmap *amap);
    void action_insert(const void *key, void *data, actionmap *amap);
    void action_remove(const void *key, actionmap *amap);
    void *action_value(const void *key, actionmap *amap);
    void action_for_each_do(actionmap *amap, int (*call_back) (const void *, void *));
    //

    inline int action_count(actionmap *amap) {
        return amap->count;
    }

#ifdef __cplusplus
}
#endif

#endif /* ACTION_HMAP_H */

