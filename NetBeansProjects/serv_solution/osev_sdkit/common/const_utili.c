
#include "commo_header.h"
#include "kcomm_header.h"
#include "const_utili.h"
#include "parms_style.h"

//

int chk_lev1_type(lv2p_prop *lv2nod, char **pamvp) {
    // OSEVPF("[FUNC]:chk_lev1_type\n");
    for (;;) {
        // OSEVPF("lv2nod->access:%d, lv2nod->xxxxxtype:|%s|\n", lv2nod->access, lv2nod->xxxxxtype);
        if (NULL == pamvp[0x00]) {
            if (ACCE_COTRL_INVAL != lv2nod->access)
                return -1;
            break;
        }
        if (ACCE_COTRL_INVAL == lv2nod->access)
            return -1;
        // OSEVPF("potyp:%d, ((unsigned char *) pamvp[0x00])[0x00]:|%d|\n", potyp, ((unsigned char *) pamvp[0x00])[0x00]);
        if (lv2nod->potyp != ((unsigned char *) pamvp[0x00])[0x00])
            return -1;
        //
        ++pamvp;
        ++lv2nod;
    }
    //
    return 0x00;
}

//

static inline void *filli_data_secti(void *data_sect, char *valu, char fmtok, uint64 sleng) {
    OSEVPF("[FUNC]:field_item_pack valu:|%d| fmtok:|%c|\n", (int) valu[0x00], fmtok);
    switch (fmtok) {
        case 'b':
            if (DATY_BYTE != valu[0x00])
                return NULL;
            memcpy(data_sect, ++valu, sizeof (char));
            data_sect += sizeof (char);
            break;
        case 'B':
            if (DATY_UBYTE != valu[0x00])
                return NULL;
            memcpy(data_sect, ++valu, sizeof (unsigned char));
            data_sect += sizeof (unsigned char);
            break;
        case 'h':
            if (DATY_SHORT != valu[0x00])
                return NULL;
            memcpy(data_sect, ++valu, sizeof (short));
            data_sect += sizeof (short);
            break;
        case 'H':
            if (DATY_USHORT != valu[0x00])
                return NULL;
            memcpy(data_sect, ++valu, sizeof (unsigned short));
            data_sect += sizeof (unsigned short);
            break;
        case 'i':
            if (DATY_INT != valu[0x00])
                return NULL;
            memcpy(data_sect, ++valu, sizeof (int));
            data_sect += sizeof (int);
            break;
        case 'I':
            if (DATY_UINT != valu[0x00])
                return NULL;
            memcpy(data_sect, ++valu, sizeof (unsigned int));
            data_sect += sizeof (unsigned int);
            break;
        case 'q':
            if (DATY_LLONG != valu[0x00])
                return NULL;
            memcpy(data_sect, ++valu, sizeof (long long));
            data_sect += sizeof (long long);
            break;
        case 'Q':
            if (DATY_ULLONG != valu[0x00])
                return NULL;
            memcpy(data_sect, ++valu, sizeof (unsigned long long));
            data_sect += sizeof (unsigned long long);
            break;
        case 'o':
            if (DATY_OBID != valu[0x00])
                return NULL;
            memcpy(data_sect, ++valu, sizeof (osv_oid_t));
            data_sect += sizeof (osv_oid_t);
            break;
        case 'f':
            if (DATY_FLOAT != valu[0x00])
                return NULL;
            memcpy(data_sect, ++valu, sizeof (float));
            data_sect += sizeof (float);
            break;
        case 'd':
            if (DATY_DOUBLE != valu[0x00])
                return NULL;
            memcpy(data_sect, ++valu, sizeof (double));
            data_sect += sizeof (double);
            break;
        case 's':
            if ((DATY_STRI != valu[0x00]) || (sleng < ((stri_entit *) valu)->colen))
                return NULL;
            memcpy(data_sect, ((stri_entit *) valu)->data, ((stri_entit *) valu)->colen);
            // data_sect += ((stri_entit *) valu)->colen;
            data_sect += sleng;
            break;
        case 'S':
            if (DATY_STRZ != valu[0x00])
                return NULL;
            // memcpy(data_sect, ((strz_entit *) valu)->data, ((strz_entit *) valu)->colen);
            // data_sect += ((strz_entit *) valu)->colen;
            ((strz_t *) data_sect)->data = ((strz_entit *) valu)->data;
            ((strz_t *) data_sect)->type = STRZ_TYPE_OSEV;
            ((strz_t *) data_sect)->asiz = ((strz_entit *) valu)->colen;
            data_sect += sizeof (strz_t);
            break;
        case 'u':
            if (DATY_BINARY != valu[0x00])
                return NULL;
            memcpy(data_sect, ((binary_entit *) valu)->data, ((binary_entit *) valu)->colen);
            data_sect += ((binary_entit *) valu)->colen;
            break;
        default:
            _LOG_WARN("default: DATY_INVAL");
            return NULL;
    }
    //
    return data_sect;
}

int const_lv2p_prop(loop_memo_t *obje_memp, char **pamvp, lv2pme *lv2me) {
    OSEVPF("[FUNC]:const_lv2p_prop\n");
    char *endsize;
#ifdef _DEBUG
    uint64 sleng = 0x00;
#else /* _DEBUG */
    uint64 sleng;
#endif /* _DEBUG */
    char *fmtst = lv2me->lv2p_fmtsd_tm;
    char *last_dat = PASS_OBIDEN_SECTI((char *) obje_memp->data);
    for (; fmtst[0x00] && (NULL != pamvp[0x00]); ++fmtst, ++pamvp) {
        if (isdigit(fmtst[0x00])) {
            sleng = strtoul(fmtst, &endsize, 10);
            fmtst = endsize;
        }
        // OSEVPF("fmtst:|%c| sleng:|%llu|\n", fmtst[0x00], sleng);
        last_dat = filli_data_secti(last_dat, pamvp[0x00], fmtst[0x00], sleng);
        if (!last_dat) return -1;
    }
    OSEVPF("last_dat - obje_memp->data:%ld\n", last_dat - (char *) obje_memp->data);
    if (obje_memp->strzp[0x00]) {
        if (conti_object_lv2po(obje_memp, lv2me))
            return -1;
    } else obje_memp->data_size = lv2me->data_size;
    //
    OSEVPF("end const_lv2p_prop\n");
    return 0x00;
}

//

static inline int filli_paki_secti(PK_PACK_STREAM *pkps, char *valu, char fmtok, uint64 sleng) {
    // OSEVPF("[FUNC]:filli_paki_secti valu:|%d| fmtok:|%c|\n", (int) valu[0x00], fmtok);
    PK_ITEM item_valu;
    switch (fmtok) {
        case 'b':
            if (DATY_BYTE != valu[0x00])
                return -1;
            if (paki_pack_byte(pkps, *(int8_t *) ++valu))
                return -1;
            break;
        case 'B':
            if (DATY_UBYTE != valu[0x00])
                return -1;
            if (paki_pack_ubyte(pkps, *(uint8_t *) ++valu))
                return -1;
            break;
        case 'h':
            if (DATY_SHORT != valu[0x00])
                return -1;
            if (paki_pack_short(pkps, *(int16_t *) ++valu))
                return -1;
            break;
        case 'H':
            if (DATY_USHORT != valu[0x00])
                return -1;
            if (paki_pack_ushort(pkps, *(uint16_t *) ++valu))
                return -1;
            break;
        case 'i':
            if (DATY_INT != valu[0x00])
                return -1;
            if (paki_pack_int32(pkps, *(int32_t *) ++valu))
                return -1;
            break;
        case 'I':
            if (DATY_UINT != valu[0x00])
                return -1;
            if (paki_pack_uint32(pkps, *(uint32_t *) ++valu))
                return -1;
            break;
        case 'q':
            if (DATY_LLONG != valu[0x00])
                return -1;
            if (paki_pack_int64(pkps, *(int64_t *) ++valu))
                return -1;
            break;
        case 'Q':
            if (DATY_ULLONG != valu[0x00])
                return -1;
            if (paki_pack_uint64(pkps, *(uint64_t *) ++valu))
                return -1;
            break;
        case 'o':
            if (DATY_OBID != valu[0x00])
                return -1;
            if (paki_pack_obid(pkps, (osv_oid_t *) ++valu))
                return -1;
            break;
        case 'f':
            if (DATY_FLOAT != valu[0x00])
                return -1;
            if (paki_pack_float(pkps, *(float *) ++valu))
                return -1;
            break;
        case 'd':
            if (DATY_DOUBLE != valu[0x00])
                return -1;
            if (paki_pack_double(pkps, *(double *) ++valu))
                return -1;
            break;
        case 's':
            if ((DATY_STRI != valu[0x00]) || (sleng < ((stri_entit *) valu)->colen))
                return -1;
            if (paki_pack_stri(pkps, ((stri_entit *) valu)->data))
                return -1;
            break;
        case 'S':
            if (DATY_STRZ != valu[0x00])
                return -1;
            // OSEVPF("((strz_entit *) valu)->colen:|%llu|\n", ((strz_entit *) valu)->colen);
            // OSEVPF("((strz_entit *) valu)->data:|%s|\n", ((strz_entit *) valu)->data);
            if (paki_pack_strz(pkps, ((strz_entit *) valu)->data))
                return -1;
            break;
        case 'u':
            if (DATY_BINARY != valu[0x00])
                return -1;
            item_valu.data = ((binary_entit *) valu)->data;
            item_valu.size = ((binary_entit *) valu)->colen;
            if (paki_pack_item(pkps, &item_valu))
                return -1;
            break;
        default:
            _LOG_WARN("default: fmtok");
            break;
    }
    return 0x00;
}

// create

int solve_lv2p_prop(PK_ITEM *key, PK_ITEM *value, valu_memo_t *obje_memp, char **pamvp, lv2pme *lv2me) {
    // OSEVPF("[FUNC]:solve_lv2p_prop\n");
    key->data = &(((osv_oid_i *) obje_memp->data)->stoid);
    key->size = sizeof (unsigned long long);
    value->data = PASS_OBIDEN_SECTI((char *) obje_memp->data);
    PK_PACK_STREAM *pkps;
    if (paki_stream_open(lv2me->lv2p_fmtsd_tm, (void *) value->data, obje_memp->allo_size - OBJE_IDENTI_BLEN, &pkps))
        return -1;
    //
    char *endsize;
#ifdef _DEBUG
    uint64 sleng = 0x00;
#else /* _DEBUG */
    uint64 sleng;
#endif /* _DEBUG */
    char *fmtst = lv2me->lv2p_fmtsd_tm;
    for (; fmtst[0x00] && (NULL != pamvp[0x00]); ++fmtst, ++pamvp) {
        if (isdigit(fmtst[0x00])) {
            sleng = strtoul(fmtst, &endsize, 10);
            fmtst = endsize;
        }
        // OSEVPF("fmtst:|%c| sleng:|%llu|\n", fmtst[0x00], sleng);
        if (filli_paki_secti(pkps, pamvp[0x00], fmtst[0x00], sleng)) {
            paki_stream_close(pkps, NULL);
            return -1;
        }
    }
    value->size = paki_stream_leng(pkps);
    // OSEVPF("end const_lv2p_prop\n");
    paki_stream_close(pkps, NULL);
    return 0x00;
}

// update

int solve_obje_data(PK_ITEM *key, PK_ITEM *value, slov_memo_t *obje_memp, char **obje_datp, lv2pme *lv2me) {
    OSEVPF("[FUNC]:solve_obje_data\n");
    key->data = &(((osv_oid_i *) &((obid_entit *) obje_datp[0x00])->data)->stoid);
    key->size = sizeof (unsigned long long);
    value->data = (char *) obje_memp->data;
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
    char *valu = (++obje_datp)[0x00];
    for (; fmtst[0x00] && (NULL != valu); ++fmtst, valu = (++obje_datp)[0x00]) {
        if (isdigit(fmtst[0x00])) {
            sleng = strtoul(fmtst, &endsize, 10);
            fmtst = endsize;
        }
        // OSEVPF("fmtst:|%c| sleng:|%llu|\n", fmtst[0x00], sleng);
        if (filli_paki_secti(pkps, valu, fmtst[0x00], sleng)) {
            paki_stream_close(pkps, NULL);
            // OSEVPF("e filli_paki_secti, paki_stream_close\n");
            return -1;
        }
    }
    value->size = paki_stream_leng(pkps);
    paki_stream_close(pkps, NULL);
    return 0x00;
}

// insert

int solve_obje_valu(PK_ITEM *value, slov_memo_t *obje_memp, char **obje_datp, lv2pme *lv2me) {
    OSEVPF("[FUNC]:solve_obje_valu\n");
    value->data = (char *) obje_memp->data;
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
    char *valu = (++obje_datp)[0x00];
    for (; fmtst[0x00] && (NULL != valu); ++fmtst, valu = (++obje_datp)[0x00]) {
        if (isdigit(fmtst[0x00])) {
            sleng = strtoul(fmtst, &endsize, 10);
            fmtst = endsize;
        }
        // OSEVPF("fmtst:|%c| sleng:|%llu|\n", fmtst[0x00], sleng);
        if (filli_paki_secti(pkps, valu, fmtst[0x00], sleng)) {
            paki_stream_close(pkps, NULL);
            // OSEVPF("e filli_paki_secti, paki_stream_close\n");
            return -1;
        }
    }
    value->size = paki_stream_leng(pkps);
    paki_stream_close(pkps, NULL);
    return 0x00;
}

