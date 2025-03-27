#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "lv2p_meta.h"

#include "qstri_utili.h"
#include "lv2p_decla.h"
// #include "kcomm_struct.h"
// #include "proje_entit/build_proje_entit.h"

#include "field_utili.h"
#include "debug_funct_co.h"

//

static char *find_srcn_l2dn(lv2p_expa_t *desexp, lv2p_expa_t *souexp, lv2p_prop *l2_nod) {
    // OSEVPF("[FUNC]:field_lv2pn_nosi, l2_nod->lv2d_name:|%s|\n", l2_nod->lv2d_name);
    char *fiesrc;
    fiesrc = match_field_lev1d(desexp->lv1dat, souexp->lv1dat, l2_nod);
    // if (fiesrc) OSEVPF("lev1d, fiesrc:|%s|\n", fiesrc);
    if (!fiesrc)
        fiesrc = match_field_lv2po(souexp->lv2nod, l2_nod);
    // OSEVPF("end, find_srcn_l2dn, fiesrc:|%s|\n", fiesrc);
    return fiesrc;
}

// lscpy(field_str, "xx, ax, cx"); // for test

int field_lv2me_ensi(char *field_str, lv2pme **lv2mep) {
    // OSEVPF("[FUNC]:field_lv2me_ensi\n");
    lv2p_expa_t *desexp = lv2mep[0x00]->lv2expt;
    lv2p_prop *l2_nod = desexp->lv2nod;
    if (ACCE_COTRL_INVAL == l2_nod->access) {
        MK_ZERO(field_str);
        return 0x00;
    }
    // OSEVPF("[FUNC]:----- desexp -----\n");
    // PRIN_lv2p_expa_tx(lv2mep[0x00]->lv2expt);
    // OSEVPF("[FUNC]:----- souexp -----\n");
    // PRIN_lv2p_expa_tx(lv2mep[0x01]->lv2expt);
    // OSEVPF("[FUNC]:----- end -----\n");
    //
    if (!strcmp(lv2mep[0x01]->lv2pn, lv2mep[0x00]->lv2pn)) {
        field_str = lscpy(field_str, l2_nod->name);
        for (++l2_nod; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod) {
            field_str = lccpy(field_str, ',');
            field_str = lscpy(field_str, l2_nod->name);
        }
        return 0x00;
    }
    //
    lv2p_expa_t *souexp = lv2mep[0x01]->lv2expt;
    char *fiesrc = find_srcn_l2dn(desexp, souexp, l2_nod);
    if (!fiesrc) return -1;
    field_str = lscpy(field_str, fiesrc);
    for (++l2_nod; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod) {
        fiesrc = find_srcn_l2dn(desexp, souexp, l2_nod);
        if (!fiesrc) return -1;
        field_str = lccpy(field_str, ',');
        field_str = lscpy(field_str, fiesrc);
    }
    //
    return 0x00;
}

//

int field_lv2me_resi(char *field_str, lv2pme *lv2me) {

    return 0x00;
}

//

int field_lv2me_reco(char *field_str, lv2pme *lv2me) {

    return 0x00;
}

//

#define FILLI_FIRESU_ZERO(FIRES) { \
    MK_ZERO(FIRES->field_str1); \
    MK_ZERO(FIRES->rfmtst1); \
    MK_ZERO(FIRES->field_str2); \
    MK_ZERO(FIRES->rfmtst2); \
    FIRES->rescod[0x00] = FIELD_FROM_EXCEP; \
    MK_ZERO(FIRES->fmtstd_co); \
}

// l2_nod->size
#define GENER_FORMAT_TYPE(LAST_STR, FMTCH, SIZE) { \
    if ('s' == FMTCH) { \
        LAST_STR = lsprif(LAST_STR, "%us", SIZE); \
    } else LAST_STR = lccpy(LAST_STR, FMTCH); \
}

int fires_lv2pn_type_enco(field_resul_co *fieres, lv2pme **lv2mep) {
    OSEVPF("[FUNC]:fires_lv2pn_type_noco\n");
    lv2p_expa_t *desexp = lv2mep[0x00]->lv2expt;
    lv2p_prop *l2_nod = desexp->lv2nod;
    if (ACCE_COTRL_INVAL == l2_nod->access) {
        FILLI_FIRESU_ZERO(fieres);
        return 0x00;
    }
    //
    char *fiesrc;
    char fmtch;
    lv2p_expa_t *souexp1 = lv2mep[0x01]->lv2expt;
    lv2p_expa_t *souexp2 = lv2mep[0x02]->lv2expt;
    char *last_str1 = fieres->field_str1;
    char *last_typ1 = fieres->rfmtst1;
    char *last_str2 = fieres->field_str2;
    char *last_typ2 = fieres->rfmtst2;
    char *last_rcod = (char *) fieres->rescod;
    char *last_typd = fieres->fmtstd_co;
    for (; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod) {
        fmtch = potyp_fmtst_tab[l2_nod->potyp];
        GENER_FORMAT_TYPE(last_typd, fmtch, l2_nod->size)
        //
        fiesrc = match_field_lev1d(desexp->lv1dat, souexp1->lv1dat, l2_nod);
        if (!fiesrc) {
            fiesrc = match_field_lev1d(desexp->lv1dat, souexp2->lv1dat, l2_nod);
            if (!fiesrc) {
                fiesrc = match_field_lv2po(souexp1->lv2nod, l2_nod);
                if (!fiesrc) {
                    fiesrc = match_field_lv2po(souexp2->lv2nod, l2_nod);
                    if (!fiesrc) return -1;
                    last_str2 = lscpy(lccpy(last_str2, ','), fiesrc);
                    GENER_FORMAT_TYPE(last_typ2, fmtch, l2_nod->size)
                    last_rcod = lccpy(last_rcod, FIELD_FROM_TWO);
                    continue;
                }
                last_str1 = lscpy(lccpy(last_str1, ','), fiesrc);
                GENER_FORMAT_TYPE(last_typ1, fmtch, l2_nod->size)
                last_rcod = lccpy(last_rcod, FIELD_FROM_ONE);
                continue;
            }
            last_str2 = lscpy(lccpy(last_str2, ','), fiesrc);
            GENER_FORMAT_TYPE(last_typ2, fmtch, l2_nod->size)
            last_rcod = lccpy(last_rcod, FIELD_FROM_TWO);
            continue;
        }
        last_str1 = lscpy(lccpy(last_str1, ','), fiesrc);
        GENER_FORMAT_TYPE(last_typ1, fmtch, l2_nod->size)
        last_rcod = lccpy(last_rcod, FIELD_FROM_ONE);
        continue;
    }
    fieres->field_str1[0x00] = ' ';
    fieres->field_str2[0x00] = ' ';
    SET_FIXED_FLOAT(fieres->fixed_float_co, fieres->fmtstd_co)
    fieres->data_size = lv2mep[0x00]->data_size;
    //
    return 0x00;
}

// fires_lv2pn_item_noco

int fires_lv2pn_item_enco(field_resul_co *fieres, lv2pme **lv2mep) {
    OSEVPF("[FUNC]:fires_lv2pn_item_noco\n");
    lv2p_expa_t *desexp = lv2mep[0x00]->lv2expt;
    lv2p_prop *l2_nod = desexp->lv2nod;
    if (ACCE_COTRL_INVAL == l2_nod->access) {
        FILLI_FIRESU_ZERO(fieres);
        return 0x00;
    }
    //
    char *fiesrc;
    char fmtch;
    lv2p_expa_t *souexp1 = lv2mep[0x01]->lv2expt;
    lv2p_expa_t *souexp2 = lv2mep[0x02]->lv2expt;
    char *last_str1 = fieres->field_str1;
    char *last_typ1 = fieres->rfmtst1;
    char *last_str2 = fieres->field_str2;
    char *last_typ2 = fieres->rfmtst2;
    char *last_rcod = (char *) fieres->rescod;
    char *last_typd = fieres->fmtstd_co;
    for (; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod) {
        fmtch = potyp_fmtst_tab[l2_nod->potyp];
        GENER_FORMAT_TYPE(last_typd, fmtch, l2_nod->size)
        //
        fiesrc = match_field_lev1d(desexp->lv1dat, souexp1->lv1dat, l2_nod);
        if (!fiesrc) {
            fiesrc = match_field_lev1d(desexp->lv1dat, souexp2->lv1dat, l2_nod);
            if (!fiesrc) {
                fiesrc = match_field_lv2po(souexp1->lv2nod, l2_nod);
                if (!fiesrc) {
                    fiesrc = match_field_lv2po(souexp2->lv2nod, l2_nod);
                    if (!fiesrc) return -1;
                    last_str2 = lscpy(lccpy(last_str2, ','), fiesrc);
                    GENER_FORMAT_TYPE(last_typ2, fmtch, l2_nod->size)
                    last_rcod = lccpy(last_rcod, FIELD_FROM_TWO);
                    continue;
                }
                last_str1 = lscpy(lccpy(last_str1, ','), fiesrc);
                GENER_FORMAT_TYPE(last_typ1, fmtch, l2_nod->size)
                last_rcod = lccpy(last_rcod, FIELD_FROM_ONE);
                continue;
            }
            last_str2 = lscpy(lccpy(last_str2, ','), fiesrc);
            GENER_FORMAT_TYPE(last_typ2, fmtch, l2_nod->size)
            last_rcod = lccpy(last_rcod, FIELD_FROM_TWO);
            continue;
        }
        last_str1 = lscpy(lccpy(last_str1, ','), fiesrc);
        GENER_FORMAT_TYPE(last_typ1, fmtch, l2_nod->size)
        last_rcod = lccpy(last_rcod, FIELD_FROM_ONE);
        continue;
    }
    fieres->field_str1[0x00] = ' ';
    fieres->field_str2[0x00] = ' ';
    SET_FIXED_FLOAT(fieres->fixed_float_co, fieres->fmtstd_co)
    fieres->data_size = lv2mep[0x00]->data_size;
    //
    return 0x00;
}

//

int find_lv2pn_meta(lv2pme **lv2mep, lv2pm_hmap *lv2pm_stm, char *desl2n, contain **sconp) {
    lv2mep[0x00] = (lv2pme *) cache_value(desl2n, lv2pm_stm->lv2pmn_hm);
    for (++lv2mep; sconp[0x00]; ++lv2mep, ++sconp) {
        lv2mep[0x00] = (lv2pme *) cache_value(&sconp[0x00]->lv2p_type, lv2pm_stm->lv2pmo_hm);
        if (!lv2mep) return -1;
    }
    //
    return 0x00;
}

int find_lv2po_meta(lv2pme **lv2mep, lv2pm_hmap *lv2pm_stm, osv_oid_t *desl2o, contain **sconp) {
    lv2mep[0x00] = (lv2pme *) cache_value(desl2o, lv2pm_stm->lv2pmo_hm);
    for (++lv2mep; sconp[0x00]; ++lv2mep, ++sconp) {
        lv2mep[0x00] = (lv2pme *) cache_value(&sconp[0x00]->lv2p_type, lv2pm_stm->lv2pmo_hm);
        if (!lv2mep) return -1;
    }
    //
    return 0x00;
}

//

int find_lv2pm_meta(lv2pme **lv2mep, lv2pm_hmap *lv2pm_stm, lv2pme *lv2dme, contain **sconp) {
    lv2mep[0x00] = lv2dme;
    for (++lv2mep; sconp[0x00]; ++lv2mep, ++sconp) {
        lv2mep[0x00] = (lv2pme *) cache_value(&sconp[0x00]->lv2p_type, lv2pm_stm->lv2pmo_hm);
        if (!lv2mep) return -1;
    }
    //
    return 0x00;
}

//

