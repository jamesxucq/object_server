#ifndef UTLIST_H
#define UTLIST_H

#ifdef	__cplusplus
extern "C" {
#endif

#define LDECLTYPE(x) __typeof(x)
/******************************************************************************
 * singly linked list macros (non-circular)                                   *
 *****************************************************************************/
#define LL_APPEND(head, add) { \
    (add)->next = head; \
    head = add; \
}

#define LL_DELETE(head, del) { \
    LDECLTYPE(head) _tmp; \
    if ((head) == (del)) (head)=(head)->next; \
    else { \
        _tmp = head; \
        while (_tmp->next && (_tmp->next != (del))) _tmp = _tmp->next; \
        if (_tmp->next) _tmp->next = ((del)->next); \
    } \
}

#define LL_FOREACH(head, el) for(el=head; el; el=el->next)

/******************************************************************************
 * circular doubly linked list macros                                         *
 *****************************************************************************/
#define CDL_APPEND(head, add) { \
    if (head) { \
        (add)->prev = (head)->prev; \
        (add)->next = (head); \
        (head)->prev = (add); \
        (add)->prev->next = (add); \
    } else { \
        (add)->prev = (add); \
        (add)->next = (add); \
    } \
    (head)=(add); \
}

#define CDL_DELETE(head, del) { \
    if (((head)==(del)) && ((head)->next == (head))) { \
        (head) = 0L; \
    } else { \
        (del)->next->prev = (del)->prev; \
        (del)->prev->next = (del)->next; \
        if ((del) == (head)) (head)=(del)->next; \
    } \
}

#define CDL_FOREACH(head, el) \
    for(el=head; el; el=(el->next==head?0L:el->next)) 

#ifdef	__cplusplus
}
#endif
    
#endif /* UTLIST_H */

