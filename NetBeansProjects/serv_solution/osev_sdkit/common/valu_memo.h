
/* 
 * File:   valu_memo.h
 * Author: James Xu
 *
 * Created on 2023.9.13, PM 2:21
 */

#ifndef VALU_MEMO_H
#define VALU_MEMO_H

// #include <stdio.h>
// #include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _valu_memo_t_ {
        uint64 allo_size;
        void *data;
        uint64 data_size;
        strz_t *strzp[FMTST_COUNT_ZTAI];
        char *lv2p_fmtsd;
    };
    typedef struct _valu_memo_t_ valu_memo_t;

#define INIT_ZERO_VMEM {0x00, NULL, 0x00, {NULL}, NULL}

    //

    inline int get_strz_posi(strz_t **strzp, void *obje_data, char *fmtst) {
        OSEVPF("[FUNC]:get_strz_posi\n");
        char *endsize;
#ifdef _DEBUG
        uint64 sleng = 0x00;
#else /* _DEBUG */
        uint64 sleng;
#endif /* _DEBUG */
        char *last_dat = PASS_OBIDEN_SECTI((char *) obje_data);
        for (; fmtst[0x00]; ++fmtst) {
            OSEVPF("fmtst:|%c|\n", fmtst[0x00]);
            if (isdigit(fmtst[0x00])) {
                sleng = strtoul(fmtst, &endsize, 10);
                fmtst = endsize;
            } else if ('S' == fmtst[0x00]) {
                strzp[0x00] = (strz_t *) last_dat;
                strzp[0x00]->type = STRZ_TYPE_OSEV;
                ++strzp;
            }
            last_dat = field_item_pass(last_dat, fmtst[0x00], sleng);
        }
        strzp[0x00] = NULL;
        return 0x00;
    }

    //

#define MINIT_VALU(VALU_MEMO, DATA, SIZE) { \
        (VALU_MEMO)->allo_size = SIZE; \
        (VALU_MEMO)->data = DATA; \
        (VALU_MEMO)->strzp[0x00] = NULL; \
    }

    inline void *valu_malloc(valu_memo_t *valu_memp, lv2pme *lv2me) {
        OSEVPF("[FUNC]:valu_malloc\n");
        valu_memp->data = malloc(lv2me->data_size);
        if (!valu_memp->data) return NULL;
        valu_memp->allo_size = lv2me->data_size;
        if (lv2me->fixed_float_tm) {
            valu_memp->lv2p_fmtsd = lv2me->lv2p_fmtsd_tm;
            if (get_strz_posi(valu_memp->strzp, valu_memp->data, lv2me->lv2p_fmtsd_tm))
                return NULL;
        } else valu_memp->strzp[0x00] = NULL;
        return valu_memp;
    }

    inline void *valu_reallo(valu_memo_t *valu_memp, uint64 size) {
        // OSEVPF("[FUNC]:valu_reallo\n");
        if (size <= valu_memp->allo_size)
            return valu_memp;
        if (VARI_OBJE_SIZE > size) size = size << 0x01;
        void *real_memo = realloc(valu_memp->data, size);
        if (!real_memo) return NULL;
        valu_memp->data = real_memo;
        valu_memp->allo_size = size;
        if (valu_memp->strzp[0x00]) {
            if (get_strz_posi(valu_memp->strzp, valu_memp->data, valu_memp->lv2p_fmtsd))
                return NULL;
        }
        return valu_memp;
    }

    inline void free_valu(valu_memo_t *valu_memp) {
        // OSEVPF("[FUNC]:free_valu\n");
        if (valu_memp->data) {
            if (valu_memp->strzp[0x00]) {
                strz_t **strzp = valu_memp->strzp;
                for (; strzp[0x00]; ++strzp) {
                    if (STRZ_TYPE_USER & (strzp[0x00])->type) {
                        if ((strzp[0x00])->data)
                            free((strzp[0x00])->data);
                    }
                }
            }
            free(valu_memp->data);
        }
    }

#ifdef __cplusplus
}
#endif

#endif /* VALU_MEMO_H */

