

#include "lv2p_list.h"

#define CLIST_APPEND(head, add) { \
    LDECLTYPE(head) _tmp; \
    add->next = NULL; \
    if (head) { \
        _tmp = head; \
        while (_tmp->next) _tmp = _tmp->next; \
        _tmp->next = add; \
    } else head = add; \
}

//

method *appe_mlist_new(method **mlsth) {
    method *menod = (method *) malloc(sizeof (method));
    if (!menod) return NULL;
    memset(menod, '\0', sizeof (method));
    //
    CLIST_APPEND(*mlsth, menod);
    return menod;
}

levon *appe_slist_new(levon **olsth) {
    levon *olsnd = (levon *) malloc(sizeof (levon));
    if (!olsnd) return NULL;
    memset(olsnd, '\0', sizeof (levon));
    //
    CLIST_APPEND(*olsth, olsnd);
    return olsnd;
}

