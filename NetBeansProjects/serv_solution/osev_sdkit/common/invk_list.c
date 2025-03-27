#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "invk_list.h"

//
#define IVKLIST_APPEND(head, add) { \
    LDECLTYPE(head) _tmp; \
    if (head) { \
        _tmp = head; \
        while (_tmp->next) _tmp = _tmp->next; \
        _tmp->next = add; \
    } else head = add; \
}

invk_list *appe_ivklist_new(invk_list **ivklsth) {
    invk_list *ilsnd = (invk_list *) malloc(sizeof (invk_list));
    if (!ilsnd) return NULL;
    // memset(ilsnd, '\0', sizeof (invk_list));
    ilsnd->next = NULL;
    //
    IVKLIST_APPEND(*ivklsth, ilsnd);
    return ilsnd;
}

