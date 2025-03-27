#include "odata_list.h"

//
struct odata_list *_odata_list_;

//
#define OLIST_APPEND(head, add) { \
    LDECLTYPE(head) _tmp; \
    add->next = NULL; \
    if (head) { \
        _tmp = head; \
        while (_tmp->next) _tmp = _tmp->next; \
        _tmp->next = add; \
    } else head = add; \
}

struct odata_list *appe_olist_new(struct odata_list **olsth) {
    struct odata_list *olistmp = (struct odata_list *) malloc(sizeof (struct odata_list));
    if (!olistmp) return NULL;
    memset(olistmp, '\0', sizeof (struct odata_list));
    //
    OLIST_APPEND(*olsth, olistmp);
    return olistmp;
}

inline void olist_dele(struct odata_list *olist) {
    struct odata_list *olistmp;
    while (olist) {
        olistmp = olist;
        olist = olist->next;
        action_del(olistmp->odata_hm);
        free(olistmp);
    }
}

//
