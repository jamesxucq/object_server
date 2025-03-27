
#include "commo_header.h"
// #include "kcomm_header.h"

#include "loop_memo.h"
#include "kcstr_utili.h"
#include "bound_utili.h"

#include "solve_bound.h"
#include "loop_memo.h"

//

int bound_objec_data(valu_memo_t *obje_memp, unsigned long long *key, PK_ITEM *value, lv2pme *lv2me) {
    OSEVPF("[FUNC]:bound_objec_data\n");
    OSEVPF("lv2me->lv2p_fmtsd:|%s|\n", lv2me->lv2p_fmtsd_tm);
    PACKING_KEY_UNPACK(((osv_oid_i *) obje_memp->data)->stoid, key);
    PK_PACK_STREAM *pkps;
    if (paki_stream_open(lv2me->lv2p_fmtsd_tm, (void *) value->data, value->size, &pkps))
        return -1;
    //
    char *endsize;
#ifdef _DEBUG
    uint64 sleng = 0x00;
#else /* _DEBUG */
    uint64 sleng;
#endif /* _DEBUG */
    char *fmtst = lv2me->lv2p_fmtsd_tm;
    char *last_dat = PASS_OBIDEN_SECTI((char *) obje_memp->data);
    for (; fmtst[0x00]; ++fmtst) {
        if (isdigit(fmtst[0x00])) {
            sleng = strtoul(fmtst, &endsize, 10);
            fmtst = endsize;
        }
        // OSEVPF("fmtst:|%c| sleng:|%llu|\n", fmtst[0x00], sleng);
        last_dat = field_item_unpack(last_dat, pkps, fmtst[0x00], sleng);
        if (!last_dat) {
            // OSEVPF("ret one field_item_unpack\n");
            paki_stream_close(pkps, NULL);
            return -1;
        }
    }
    if (obje_memp->strzp[0x00]) {
        if (conti_object_strz(obje_memp, lv2me)) {
            paki_stream_close(pkps, NULL);
            return -1;
        }
    } else obje_memp->data_size = lv2me->data_size;
    //
    paki_stream_close(pkps, NULL);
    OSEVPF("end bound_objec_data\n");
    return 0x00;
}

//

int bound_objec_loop(loop_memo_t *obje_memp, unsigned long long *key, PK_ITEM *value, lv2pme *lv2me) {
    OSEVPF("[FUNC]:bound_objec_loop\n");
    OSEVPF("lv2me->lv2p_fmtsd:|%s|\n", lv2me->lv2p_fmtsd_tm);
    PACKING_KEY_UNPACK(((osv_oid_i *) obje_memp->data)->stoid, key);
    PK_PACK_STREAM *pkps;
    if (paki_stream_open(lv2me->lv2p_fmtsd_tm, (void *) value->data, value->size, &pkps))
        return -1;
    //
    char *endsize;
#ifdef _DEBUG
    uint64 sleng = 0x00;
#else /* _DEBUG */
    uint64 sleng;
#endif /* _DEBUG */
    char *fmtst = lv2me->lv2p_fmtsd_tm;
    char *last_dat = PASS_OBIDEN_SECTI((char *) obje_memp->data);
    for (; fmtst[0x00]; ++fmtst) {
        if (isdigit(fmtst[0x00])) {
            sleng = strtoul(fmtst, &endsize, 10);
            fmtst = endsize;
        }
        // OSEVPF("fmtst:|%c| sleng:|%llu|\n", fmtst[0x00], sleng);
        last_dat = field_item_unpack(last_dat, pkps, fmtst[0x00], sleng);
        if (!last_dat) {
            // OSEVPF("ret one field_item_unpack\n");
            paki_stream_close(pkps, NULL);
            return -1;
        }
    }
    if (obje_memp->strzp[0x00]) {
        if (conti_object_sloop(obje_memp, lv2me)) {
            paki_stream_close(pkps, NULL);
            return -1;
        }
    } else obje_memp->data_size = lv2me->data_size;
    //
    paki_stream_close(pkps, NULL);
    OSEVPF("end bound_objec_loop\n");
    return 0x00;
}

//

int solve_objec_loop(PK_ITEM *key, PK_ITEM *value, loop_memo_t *obje_memp, lv2pme *lv2me) {
    // OSEVPF("[FUNC]:solve_objec_loop\n");
    key->data = &(((osv_oid_i *) obje_memp->data)->stoid);
    key->size = sizeof (unsigned long long);
    value->data = ((char *) obje_memp->dest);
    PK_PACK_STREAM *pkps;
    if (paki_stream_open(lv2me->lv2p_fmtsd_tm, (void *) value->data, obje_memp->allo_size, &pkps))
        return -1;
    //
    char *endsize;
#ifdef _DEBUG
    uint64 sleng = 0x00;
#else /* _DEBUG */
    uint64 sleng;
#endif /* _DEBUG */
    char *fmtst = lv2me->lv2p_fmtsd_tm;
    char *last_dat = PASS_OBIDEN_SECTI((char *) obje_memp->data);
    for (; fmtst[0x00]; ++fmtst) {
        if (isdigit(fmtst[0x00])) {
            sleng = strtoul(fmtst, &endsize, 10);
            fmtst = endsize;
        }
        // OSEVPF("fmtst:|%c| sleng:|%llu|\n", fmtst[0x00], sleng);
        last_dat = field_item_pack(pkps, last_dat, fmtst[0x00], sleng);
        if (!last_dat) {
            paki_stream_close(pkps, NULL);
            return -1;
        }
    }
    value->size = paki_stream_leng(pkps);
    //
    paki_stream_close(pkps, NULL);
    return 0x00;
}

//

int solve_value_loop(PK_ITEM *value, loop_memo_t *obje_memp, lv2pme *lv2me) {
    // OSEVPF("[FUNC]:solve_value_loop\n");
    value->data = ((char *) obje_memp->dest);
    PK_PACK_STREAM *pkps;
    if (paki_stream_open(lv2me->lv2p_fmtsd_tm, (void *) value->data, obje_memp->allo_size, &pkps))
        return -1;
    //
    char *endsize;
#ifdef _DEBUG
    uint64 sleng = 0x00;
#else /* _DEBUG */
    uint64 sleng;
#endif /* _DEBUG */
    char *fmtst = lv2me->lv2p_fmtsd_tm;
    char *last_dat = PASS_OBIDEN_SECTI((char *) obje_memp->data);
    for (; fmtst[0x00]; ++fmtst) {
        if (isdigit(fmtst[0x00])) {
            sleng = strtoul(fmtst, &endsize, 10);
            fmtst = endsize;
        }
        // OSEVPF("fmtst:|%c| sleng:|%llu|\n", fmtst[0x00], sleng);
        last_dat = field_item_pack(pkps, last_dat, fmtst[0x00], sleng);
        if (!last_dat) {
            paki_stream_close(pkps, NULL);
            return -1;
        }
    }
    value->size = paki_stream_leng(pkps);
    //
    paki_stream_close(pkps, NULL);
    return 0x00;
}

