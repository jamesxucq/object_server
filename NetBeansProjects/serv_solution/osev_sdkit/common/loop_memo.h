
/* 
 * File:   loop_memo.h
 * Author: James Xu
 *
 * Created on 2023.6.2, PM 9:19
 */

#ifndef LOOP_MEMO_H
#define LOOP_MEMO_H

// #include <stdio.h>
// #include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_macro.h"

#include "valu_memo.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _loop_memo_t_ {
        uint64 allo_size;
        void *data;
        uint64 data_size;
        void *dest;
        strz_t *strzp[FMTST_COUNT_ZTAI];
        char *lv2p_fmtsd; // lv2p data format string
    };
    typedef struct _loop_memo_t_ loop_memo_t;

    inline void *minit_dest(loop_memo_t *loop_memp, void *data, uint64 size) {
        OSEVPF("[FUNC]:minit_dest\n");
        loop_memp->data = data;
        loop_memp->dest = malloc(size);
        if (!loop_memp->dest) return NULL;
        loop_memp->allo_size = size;
        loop_memp->strzp[0x00] = NULL;
        return loop_memp;
    }

    inline void free_dest(loop_memo_t *loop_memp) {
        OSEVPF("[FUNC]:free_dest\n");
        if (loop_memp->dest)
            free(loop_memp->dest);
    }

    inline void *loop_malloc(loop_memo_t *loop_memp, lv2pme *lv2me) {
        OSEVPF("[FUNC]:loop_malloc\n");
        loop_memp->data = malloc(lv2me->data_size);
        if (!loop_memp->data) return NULL;
        loop_memp->dest = malloc(lv2me->data_size);
        if (!loop_memp->dest) {
            free(loop_memp->data);
            loop_memp->data = NULL;
            return NULL;
        }
        loop_memp->allo_size = lv2me->data_size;
        if (lv2me->fixed_float_tm) {
            loop_memp->lv2p_fmtsd = lv2me->lv2p_fmtsd_tm;
            if (get_strz_posi(loop_memp->strzp, loop_memp->data, lv2me->lv2p_fmtsd_tm))
                return NULL;
        } else loop_memp->strzp[0x00] = NULL;
        return loop_memp;
    }

    inline void *loop_reallo(loop_memo_t *loop_memp, uint64 size) {
        OSEVPF("[FUNC]:loop_reallo, size:%llu loop_memp->allo_size:%llu\n", size, loop_memp->allo_size);
        if (size <= loop_memp->allo_size)
            return loop_memp;
        if (VARI_OBJE_SIZE > size) size = size << 0x01;
        OSEVPF("1 size:%llu\n", size);
        void *real_memo = realloc(loop_memp->data, size);
        if (!real_memo) return NULL;
        loop_memp->data = real_memo;
        OSEVPF("2 size:%llu\n", size);
        real_memo = realloc(loop_memp->dest, size);
        if (!real_memo) {
            free(loop_memp->data);
            loop_memp->data = NULL;
            return NULL;
        }
        loop_memp->dest = real_memo;
        loop_memp->allo_size = size;
        if (loop_memp->strzp[0x00]) {
            OSEVPF("3 size:%llu\n", size);
            if (get_strz_posi(loop_memp->strzp, loop_memp->data, loop_memp->lv2p_fmtsd))
                return NULL;
        }
        return loop_memp;
    }

    //
    void free_loop(loop_memo_t *loop_memp);

    //

#ifdef __cplusplus
}
#endif

#endif /* LOOP_MEMO_H */

