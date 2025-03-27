#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_macro.h"


#include "lv2p_attri.h"

//
#define CLIST_APPEND(head, add) { \
    LDECLTYPE(head) _tmp; \
    if (head) { \
        _tmp = head; \
        while (_tmp->next) _tmp = _tmp->next; \
        _tmp->next = add; \
    } else head = add; \
}

//

integra *new_integ_list(integra **olsth) {
    integra *olsnd = (integra *) malloc(sizeof (integra));
    if (!olsnd) return NULL;
    // memset(olsnd, '\0', sizeof (integra));
    olsnd->next = NULL;
    //
    CLIST_APPEND(*olsth, olsnd);
    return olsnd;
}

//

inherit *appe_ilist_new(inherit **ilsth) {
    inherit *ilsnd = (inherit *) malloc(sizeof (inherit));
    if (!ilsnd) return NULL;
    // memset(ilsnd, '\0', sizeof (inherit));
    ilsnd->next = NULL;
    //
    CLIST_APPEND(*ilsth, ilsnd);
    return ilsnd;
}

//

void dele_lv2pai(void *lv2ai) {
    if (lv2ai) {
        olist_dele(((lv2p_attri *) lv2ai)->integ_list);
        ilist_dele(((lv2p_attri *) lv2ai)->inher_list);
        free(lv2ai);
    }
}