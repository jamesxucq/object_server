#ifndef UTLIST_H
#define UTLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#define LDECLTYPE(x) __typeof(x)
    //
#define DL_APPEND(head, add) \
if (head) { \
    (add)->prev = (head); \
    if((head)->next) (head)->next->prev = (add); \
    (add)->next = (head)->next; \
    (head)->next = (add); \
} else { \
    (head) = (add); \
    (head)->prev = (head); \
    (head)->next = NULL; \
}

//
#define DL_DELETE(head, del) \
if ((del) == (head)) { \
    if((del)->next) (del)->next->prev = (del)->next; \
    (head) = (del)->next; \
} else { \
    (del)->prev->next = (del)->next; \
    if ((del)->next) (del)->next->prev = (del)->prev; \
}

//

#ifdef __cplusplus
}
#endif

#endif /* UTLIST_H */

