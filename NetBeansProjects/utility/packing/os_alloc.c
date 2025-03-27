
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "os_errno.h"
#include "os_alloc.h"
#include "error.h"

// add by james 20230608
// #include "../jemalloc/jemalloc.h"

// __pk_calloc ANSI calloc function.

int __pk_calloc(size_t number, size_t size, void *retp) {
    void *p;

    // Defensive: if our caller doesn't handle errors correctly, ensure a free won't fail.
    *(void **) retp = NULL;

    // This function MUST handle a NULL WT_SESSION_IMPL handle.
    assert(number != 0 && size != 0);

    if ((p = calloc(number, size)) == NULL)
        PK_RET_MSG(__pk_errno(), "memory allocation of %Iu bytes failed", size * number);

    *(void **) retp = p;
    return (0);
}

// __pk_free_int -- ANSI free function.

void __pk_free_int(const void *p_arg) {
    void *p;

    p = *(void **) p_arg;
    if (p == NULL) return; /* ANSI C free semantics */

    // If there's a serialization bug we might race with another thread. We can't avoid the race
    // (and we aren't willing to flush memory), but we minimize the window by clearing the free
    // address, hoping a racing thread will see, and won't free, a NULL pointer.
    *(void **) p_arg = NULL;

    free(p);
}
