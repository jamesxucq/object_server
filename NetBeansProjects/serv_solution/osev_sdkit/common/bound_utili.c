
#include "bound_utili.h"

static inline uint64 get_strz_mlen(strz_t **strzp) {
    uint64 strz_mlen = 0x00;
    for (; strzp[0x00]; ++strzp)
        strz_mlen += 0x01 + (strzp[0x00])->slen;
    return strz_mlen;
}

static inline uint64 get_strz_asiz(strz_t **strzp) {
    uint64 strz_mlen = 0x00;
    for (; strzp[0x00]; ++strzp)
        strz_mlen += (strzp[0x00])->asiz;
    return strz_mlen;
}

static inline int fill_obje_strz(void *strz_head, strz_t **strzp) {
    char *strz_posi;
    for (; strzp[0x00]; ++strzp) {
        strz_posi = (strzp[0x00])->data;
        (strzp[0x00])->data = strz_head;
        strz_head = lscpy_stz(strz_head, strz_posi);
        (strzp[0x00])->asiz = 0x01 + (strzp[0x00])->slen;
    }
    return 0x00;
}

static inline int fill_lv2da_strz(void *strz_head, strz_t **strzp) {
    char *strz_posi;
    for (; strzp[0x00]; ++strzp) {
        strz_posi = ((strz_t *) strzp[0x00])->data;
        ((strz_t *) strzp[0x00])->data = strz_head;
        strz_head = lscpy_stz(strz_head, strz_posi);
        ((strz_t *) strzp[0x00])->slen = ((strz_t *) strzp[0x00])->asiz - 0x01;
    }
    return 0x00;
}

int conti_object_strz(valu_memo_t *obje_memp, lv2pme *lv2me) {
    OSEVPF("[FUNC]:conti_object_strz\n");
    uint64 strz_size = lv2me->data_size + get_strz_mlen(obje_memp->strzp);
    if (!valu_reallo(obje_memp, strz_size))
        return -1;
    if (fill_obje_strz(obje_memp->data + lv2me->data_size, obje_memp->strzp))
        return -1;
    obje_memp->data_size = strz_size;
    return 0x00;
}

int conti_object_sloop(loop_memo_t *obje_memp, lv2pme *lv2me) {
    OSEVPF("[FUNC]:conti_object_sloop\n");
    uint64 strz_size = lv2me->data_size + get_strz_mlen(obje_memp->strzp);
    if (!loop_reallo(obje_memp, strz_size))
        return -1;
    if (fill_obje_strz(obje_memp->data + lv2me->data_size, obje_memp->strzp))
        return -1;
    obje_memp->data_size = strz_size;
    //
    return 0x00;
}

int conti_object_lv2po(loop_memo_t *obje_memp, lv2pme *lv2me) {
    OSEVPF("[FUNC]:conti_object_lv2po\n");
    uint64 strz_size = OBJE_IDENTI_BLEN + lv2me->data_size + get_strz_asiz(obje_memp->strzp);
    OSEVPF("1 xxxxxxxxxx\n");
    if (!loop_reallo(obje_memp, strz_size))
        return -1;
    OSEVPF("2 xxxxxxxxxx\n");
    if (fill_lv2da_strz(obje_memp->data + lv2me->data_size, obje_memp->strzp))
        return -1;
    obje_memp->data_size = strz_size;
    //
    OSEVPF("end conti_object_lv2po\n");
    return 0x00;
}

