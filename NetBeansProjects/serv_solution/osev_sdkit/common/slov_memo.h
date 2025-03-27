
/* 
 * File:   slov_memo.h
 * Author: James Xu
 *
 * Created on 2023.9.13, PM 2:25
 */

#ifndef SLOV_MEMO_H
#define SLOV_MEMO_H

// #include <stdio.h>
// #include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _slov_memo_t_ {
        uint64 allo_size;
        void *data;
    };
    typedef struct _slov_memo_t_ slov_memo_t;

    //

    inline void *slov_malloc(slov_memo_t *slov_memp, uint64 data_size) {
        OSEVPF("[FUNC]:slov_malloc\n");
        slov_memp->data = malloc(data_size);
        slov_memp->allo_size = data_size;
        if (!slov_memp->data) return NULL;
        return slov_memp;
    }

    inline void free_slov(slov_memo_t *slov_memp) {
        // OSEVPF("[FUNC]:free_slov\n");
        if (slov_memp->data)
            free(slov_memp->data);
    }

#ifdef __cplusplus
}
#endif

#endif /* SLOV_MEMO_H */

