#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "lv2p_meta/lv2me_ite.h"
#include "trans/trans_utili.h"

#include "lv2p_list.h"
#include "filli_clang.h"
#include "debug_funct_oi.h"

//

lv2p_attri *creat_lv2p_atti(lv2pm_hmap *lv2pm_stm, osv_oid_t *lv2p_obid, char *lv2pn) {
    lv2p_attri *lv2ai = mallo_lv2pai();
    if (!lv2ai) return NULL;
    //
    OBID_BINARY_COPY(&lv2ai->lv2p_obid, lv2p_obid)
    strcpy(lv2ai->lv2pn, lv2pn);
    lv2ai->versio = CLASS_INIT_VERSION;
    lv2ai->iexter = CLASS_INIT_INTERNAL;
    INITI_INTEG_INHER(lv2ai)
    //
    cache_insert(lv2ai->lv2pn, lv2ai, lv2pm_stm->lv2pan_hm);
    cache_insert(&lv2ai->lv2p_obid, lv2ai, lv2pm_stm->lv2pao_hm);
    return lv2ai;
}

// 0x00:hand refer zero. >0x00:refer number <0x00:error

int destr_lv2p_atti(lv2pm_hmap *lv2pm_stm, osv_oid_t *lv2p_obid) {
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2p_obid, lv2pm_stm->lv2pao_hm);
    if (!lv2ai) return -1;
    //
    cache_remove(lv2ai->lv2pn, lv2pm_stm->lv2pan_hm);
    cache_remove(lv2p_obid, lv2pm_stm->lv2pao_hm);
    dele_lv2pai(lv2ai);
    return 0x00;
}

int delet_lv2p_atti(lv2pm_hmap *lv2pm_stm, char *lv2pn) {
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    cache_remove(&lv2ai->lv2p_obid, lv2pm_stm->lv2pao_hm);
    cache_remove(lv2pn, lv2pm_stm->lv2pan_hm);
    dele_lv2pai(lv2ai);
    return 0x00;
}

//

integra *appe_integ_list(integra **olsth, int range_type, char *lv2pn, char *lev1n) {
    OSEVPF("[FUNC]:appe_integ_list, lv2pn:|%s| lev1n:|%s|\n", lv2pn, lev1n);
    integra *olsnd = new_integ_list(olsth);
    if (!olsnd) return NULL;
    olsnd->rang_type = range_type;
    strcpy(olsnd->lv2pn, lv2pn);
    strcpy(olsnd->lev1n, lev1n);
    //
    return olsnd;
}

integra *dele_integ_iden(integra **olsth, char *lv2pn, char *lev1n) {
    OSEVPF("[FUNC]:dele_integ_iden, lv2pn:|%s| lev1n:|%s|\n", lv2pn, lev1n);
    integra *prev_nod;
    integra *olsnd = olsth[0x00];
    if (strcmp(lv2pn, olsnd->lv2pn) || strcmp(lev1n, olsnd->lev1n)) {
        prev_nod = olsnd;
        olsnd = olsnd->next;
        while (olsnd) {
            if (!strcmp(lv2pn, olsnd->lv2pn) && !strcmp(lev1n, olsnd->lev1n)) {
                prev_nod->next = olsnd->next;
                break;
            }
            prev_nod = olsnd;
            olsnd = olsnd->next;
        }
    } else *olsth = olsnd->next;
    //
    return olsnd;
}

integra *dele_integ_lv2p(integra **olsth, char *lv2pn) {
    integra *prev_nod;
    integra *olsnd = olsth[0x00];
    if (strcmp(lv2pn, olsnd->lv2pn)) {
        prev_nod = olsnd;
        olsnd = olsnd->next;
        while (olsnd) {
            if (!strcmp(lv2pn, olsnd->lv2pn)) {
                prev_nod->next = olsnd->next;
                break;
            }
            prev_nod = olsnd;
            olsnd = olsnd->next;
        }
    } else *olsth = olsnd->next;
    //
    return olsnd;
}

integra *find_integ_iden(integra *olist, char *lv2pn, char *lev1n) {
    OSEVPF("[FUNC]:find_integ_iden, lv2pn:|%s|, lev1n:|%s|\n", lv2pn, lev1n);
    for (; olist; olist = olist->next) {
        OSEVPF("olist->lv2pn:|%s|, olist->lev1n:|%s|\n", olist->lv2pn, olist->lev1n);
        if (!strcmp(lv2pn, olist->lv2pn) && !strcmp(lev1n, olist->lev1n))
            break;
    }
    return olist;
}

//

lv1_cont *find_l1cnod_name(lv1_cont *l1lsnd, char *lev1n) {
    OSEVPF("[FUNC]:find_l1cnod_name\n");
    while (l1lsnd) {
        OSEVPF("lev1n:|%s| meth_name:|%s|\n", lev1n, l1lsnd->lev1n);
        if (!strcmp(lev1n, l1lsnd->lev1n))
            break;
        l1lsnd = l1lsnd->next;
    }
    //
    return l1lsnd;
}

lv1_cont *find_l1cnod_decl(lv1_cont *l1lsnd, char *lev1n, char *decla) {
    char fmtsop[FMTST_COUNT_ZTAI]; // fmtsop
    if (conv_oinvk_decla(fmtsop, decla))
        return NULL;
    OSEVPF("[FUNC]:find_l1cnod_decl\n");
    while (l1lsnd) {
        OSEVPF("lev1n:|%s| meth_name:|%s|\n", lev1n, l1lsnd->lev1n);
        if (!strcmp(lev1n, l1lsnd->lev1n) && !strcmp(fmtsop, l1lsnd->oivk_fmtsp_oc))
            break;
        l1lsnd = l1lsnd->next;
    }
    //
    return l1lsnd;
}

lv1_cont *find_l1cnod_iden(lv1_cont *l1lsnd, char *lev1n, char *fmtsop) {
    OSEVPF("[FUNC]:find_l1cnod_iden\n");
    while (l1lsnd) {
        OSEVPF("lev1n:|%s| meth_name:|%s|\n", lev1n, l1lsnd->lev1n);
        OSEVPF("fmtsop:|%s| meth_fmtsp:|%s|\n", fmtsop, l1lsnd->oivk_fmtsp_oc);
        if (!strcmp(lev1n, l1lsnd->lev1n) && !strcmp(fmtsop, l1lsnd->oivk_fmtsp_oc))
            break;
        l1lsnd = l1lsnd->next;
    }
    //
    return l1lsnd;
}

lv1_cont *dele_l1cnod_iden(lv1_cont **l1clsth, char *lev1n, char *fmtsop) {
    lv1_cont *l1lsnd = *l1clsth;
    lv1_cont *prev_nod;
    if (!l1lsnd) return NULL;
    //
    if (strcmp(lev1n, l1lsnd->lev1n) || strcmp(fmtsop, l1lsnd->oivk_fmtsp_oc)) {
        prev_nod = l1lsnd;
        l1lsnd = l1lsnd->next;
        while (l1lsnd) {
            if (!strcmp(lev1n, l1lsnd->lev1n) && !strcmp(fmtsop, l1lsnd->oivk_fmtsp_oc)) {
                prev_nod->next = l1lsnd->next;
                break;
            }
            prev_nod = l1lsnd;
            l1lsnd = l1lsnd->next;
        }
    } else *l1clsth = l1lsnd->next;
    //
    return l1lsnd;
}

lv1_cont *dele_l1cnod_decl(lv1_cont **l1clsth, char *lev1n, char *decla) {
    char fmtsop[FMTST_COUNT_ZTAI]; // fmtsop
    if (conv_oinvk_decla(fmtsop, decla))
        return NULL;
    //
    lv1_cont *l1lsnd = *l1clsth;
    lv1_cont *prev_nod;
    if (!l1lsnd) return NULL;
    //
    if (strcmp(lev1n, l1lsnd->lev1n) || strcmp(fmtsop, l1lsnd->oivk_fmtsp_oc)) {
        prev_nod = l1lsnd;
        l1lsnd = l1lsnd->next;
        while (l1lsnd) {
            if (!strcmp(lev1n, l1lsnd->lev1n) && !strcmp(fmtsop, l1lsnd->oivk_fmtsp_oc)) {
                prev_nod->next = l1lsnd->next;
                break;
            }
            prev_nod = l1lsnd;
            l1lsnd = l1lsnd->next;
        }
    } else *l1clsth = l1lsnd->next;
    //
    return l1lsnd;
}

lv1_cont *modi_l1cnod_conte(lv1_cont *l1lsnd, char *lev1n, char *fmtsop, char *lev1_cont) {
    OSEVPF("[FUNC]:modi_l1cnod_conte\n");
    while (l1lsnd) {
        OSEVPF("lev1n:|%s| meth_name:|%s|\n", lev1n, l1lsnd->lev1n);
        if (!strcmp(lev1n, l1lsnd->lev1n) && !strcmp(fmtsop, l1lsnd->oivk_fmtsp_oc)) {
            strcpy(l1lsnd->conte, lev1_cont);
            break;
        }
        l1lsnd = l1lsnd->next;
    }
    return l1lsnd;
}

//

inherit *addi_imeth(inherit **ilsth, int rang_type, char *lv2pn, char *lev1n) {
    inherit *ilsnd = appe_ilist_new(ilsth);
    if (!ilsnd) return NULL;
    ilsnd->rang_type = rang_type;
    strcpy(ilsnd->lev1n, lev1n);
    strcpy(ilsnd->lv2pn, lv2pn);
    PRIN_inherit(ilsnd);
    return ilsnd;
}

inherit *addi_inhe_meth(inherit **ilsth, char *lv2pn, char *lev1n) {
    inherit *ilsnd = appe_ilist_new(ilsth);
    if (!ilsnd) return NULL;
    memset(ilsnd, '\0', sizeof (inherit));
    ilsnd->rang_type = INHE_TYPE_METH;
    strcpy(ilsnd->lev1n, lev1n);
    strcpy(ilsnd->lv2pn, lv2pn);
    PRIN_inherit(ilsnd);
    return ilsnd;
}

inherit *addi_inhe_lev1(inherit **ilsth, char *lv2pn, char *lev1n) {
    inherit *ilsnd = appe_ilist_new(ilsth);
    if (!ilsnd) return NULL;
    memset(ilsnd, '\0', sizeof (inherit));
    ilsnd->rang_type = INHE_TYPE_LEVO;
    strcpy(ilsnd->lev1n, lev1n);
    strcpy(ilsnd->lv2pn, lv2pn);
    PRIN_inherit(ilsnd);
    return ilsnd;
}

inherit *addi_inhe_lv2p(inherit **ilsth, char *lv2pn) {
    inherit *ilsnd = appe_ilist_new(ilsth);
    if (!ilsnd) return NULL;
    memset(ilsnd, '\0', sizeof (inherit));
    ilsnd->rang_type = INHE_TYPE_LVTP;
    MK_ZERO(ilsnd->lev1n);
    strcpy(ilsnd->lv2pn, lv2pn);
    PRIN_inherit(ilsnd);
    return ilsnd;
}

inherit *addi_inhe_clas(inherit **ilsth, char *lv2pn) {
    inherit *ilsnd = appe_ilist_new(ilsth);
    if (!ilsnd) return NULL;
    memset(ilsnd, '\0', sizeof (inherit));
    ilsnd->rang_type = INHE_TYPE_CLAS;
    MK_ZERO(ilsnd->lev1n);
    strcpy(ilsnd->lv2pn, lv2pn);
    PRIN_inherit(ilsnd);
    return ilsnd;
}

inherit *dele_imeth(inherit **ilsth, int rang_type, char *lv2pn, char *lev1n) {
    inherit *ilsnd = ilsth[0x00];
    inherit *prev_nod;
    if (!ilsnd) return NULL;
    // OSEVPF("ilsnd->lev1n:|%s|, ilsnd->fmtsop|%s|, ilsnd->clasns|%s|\n", ilsnd->lev1n, ilsnd->fmtsop, ilsnd->clasns);
    if ((rang_type != ilsnd->rang_type) || strcmp(lv2pn, ilsnd->lv2pn) || strcmp(lev1n, ilsnd->lev1n)) {
        prev_nod = ilsnd;
        ilsnd = ilsnd->next;
        while (ilsnd) {
            // OSEVPF("ilsnd->lev1n:|%s|, ilsnd->fmtsop|%s|, ilsnd->clasns|%s|\n", ilsnd->lev1n, ilsnd->fmtsop, ilsnd->clasns);
            if ((rang_type == ilsnd->rang_type) && !strcmp(lv2pn, ilsnd->lv2pn) && !strcmp(lev1n, ilsnd->lev1n)) {
                prev_nod->next = ilsnd->next;
                break;
            }
            prev_nod = ilsnd;
            ilsnd = ilsnd->next;
        }
    } else ilsth[0x00] = ilsnd->next;
    //
    return ilsnd;
}

inherit *dele_inhe_meth(inherit **ilsth, char *lv2pn, char *lev1n) {
    inherit *ilsnd = ilsth[0x00];
    inherit *prev_nod;
    if (!ilsnd) return NULL;
    // OSEVPF("ilsnd->lev1n:|%s|, ilsnd->fmtsop|%s|, ilsnd->clasns|%s|\n", ilsnd->lev1n, ilsnd->fmtsop, ilsnd->clasns);
    if ((INHE_TYPE_METH != ilsnd->rang_type) || strcmp(lv2pn, ilsnd->lv2pn) || strcmp(lev1n, ilsnd->lev1n)) {
        prev_nod = ilsnd;
        ilsnd = ilsnd->next;
        while (ilsnd) {
            // OSEVPF("ilsnd->lev1n:|%s|, ilsnd->fmtsop|%s|, ilsnd->clasns|%s|\n", ilsnd->lev1n, ilsnd->fmtsop, ilsnd->clasns);
            if ((INHE_TYPE_METH == ilsnd->rang_type) && !strcmp(lv2pn, ilsnd->lv2pn) && !strcmp(lev1n, ilsnd->lev1n)) {
                prev_nod->next = ilsnd->next;
                break;
            }
            prev_nod = ilsnd;
            ilsnd = ilsnd->next;
        }
    } else ilsth[0x00] = ilsnd->next;
    //
    return ilsnd;
}

inherit *dele_inhe_lev1(inherit **ilsth, char *lv2pn, char *lev1n) {
    inherit *ilsnd = ilsth[0x00];
    inherit *prev_nod;
    if (!ilsnd) return NULL;
    // OSEVPF("ilsnd->lev1n:|%s|, ilsnd->fmtsop|%s|, ilsnd->clasns|%s|\n", ilsnd->lev1n, ilsnd->fmtsop, ilsnd->clasns);
    if ((INHE_TYPE_LEVO != ilsnd->rang_type) || strcmp(lv2pn, ilsnd->lv2pn) || strcmp(lev1n, ilsnd->lev1n)) {
        prev_nod = ilsnd;
        ilsnd = ilsnd->next;
        while (ilsnd) {
            // OSEVPF("ilsnd->lev1n:|%s|, ilsnd->fmtsop|%s|, ilsnd->clasns|%s|\n", ilsnd->lev1n, ilsnd->fmtsop, ilsnd->clasns);
            if ((INHE_TYPE_LEVO == ilsnd->rang_type) && !strcmp(lv2pn, ilsnd->lv2pn) && !strcmp(lev1n, ilsnd->lev1n)) {
                prev_nod->next = ilsnd->next;
                break;
            }
            prev_nod = ilsnd;
            ilsnd = ilsnd->next;
        }
    } else ilsth[0x00] = ilsnd->next;
    //
    return ilsnd;
}

inherit *dele_inhe_lv2p(inherit **ilsth, char *lv2pn) {
    inherit *ilsnd = ilsth[0x00];
    inherit *prev_nod;
    if (!ilsnd) return NULL;
    // OSEVPF("ilsnd->lev1n:|%s|, ilsnd->fmtsop|%s|, ilsnd->clasns|%s|\n", ilsnd->lev1n, ilsnd->fmtsop, ilsnd->clasns);
    if ((INHE_TYPE_LVTP != ilsnd->rang_type) || strcmp(lv2pn, ilsnd->lv2pn)) {
        prev_nod = ilsnd;
        ilsnd = ilsnd->next;
        while (ilsnd) {
            // OSEVPF("ilsnd->lev1n:|%s|, ilsnd->fmtsop|%s|, ilsnd->clasns|%s|\n", ilsnd->lev1n, ilsnd->fmtsop, ilsnd->clasns);
            if ((INHE_TYPE_LVTP == ilsnd->rang_type) && !strcmp(lv2pn, ilsnd->lv2pn)) {
                prev_nod->next = ilsnd->next;
                break;
            }
            prev_nod = ilsnd;
            ilsnd = ilsnd->next;
        }
    } else ilsth[0x00] = ilsnd->next;
    //
    return ilsnd;
}

inherit *dele_inhe_clas(inherit **ilsth, char *lv2pn) {
    inherit *ilsnd = ilsth[0x00];
    inherit *prev_nod;
    if (!ilsnd) return NULL;
    // OSEVPF("ilsnd->lev1n:|%s|, ilsnd->fmtsop|%s|, ilsnd->clasns|%s|\n", ilsnd->lev1n, ilsnd->fmtsop, ilsnd->clasns);
    if ((INHE_TYPE_CLAS != ilsnd->rang_type) || strcmp(lv2pn, ilsnd->lv2pn)) {
        prev_nod = ilsnd;
        ilsnd = ilsnd->next;
        while (ilsnd) {
            // OSEVPF("ilsnd->lev1n:|%s|, ilsnd->fmtsop|%s|, ilsnd->clasns|%s|\n", ilsnd->lev1n, ilsnd->fmtsop, ilsnd->clasns);
            if ((INHE_TYPE_CLAS == ilsnd->rang_type) && !strcmp(lv2pn, ilsnd->lv2pn)) {
                prev_nod->next = ilsnd->next;
                break;
            }
            prev_nod = ilsnd;
            ilsnd = ilsnd->next;
        }
    } else ilsth[0x00] = ilsnd->next;
    //
    return ilsnd;
}

//

inherit *find_inher_iden(inherit *ilist, char *lv2pn, char *lev1n) {
    for (; ilist; ilist = ilist->next) {
        if ((INHE_TYPE_LVTP | INHE_TYPE_CLAS) & ilist->rang_type) {
            if (!strcmp(lv2pn, ilist->lv2pn))
                break;
        } else if ((INHE_TYPE_METH | INHE_TYPE_LEVO) & ilist->rang_type) {
            if (!strcmp(lv2pn, ilist->lv2pn) && !strcmp(lev1n, ilist->lev1n))
                break;
        } else if (!strcmp(lv2pn, ilist->lv2pn) && !strcmp(lev1n, ilist->lev1n))
            break;
    }
    return ilist;
}

//

inherit *find_inher_levo(inherit *ilist, int rang_type, char *lv2pn, char *lev1n) {
    for (; ilist; ilist = ilist->next) {
        if ((INHE_TYPE_METH | INHE_TYPE_LEVO) & ilist->rang_type) {
            if ((rang_type == ilist->rang_type) && !strcmp(lv2pn, ilist->lv2pn) && !strcmp(lev1n, ilist->lev1n))
                break;
        }
    }
    return ilist;
}

inherit *find_inher_lvtp(inherit *ilist, int rang_type, char *lv2pn) {
    for (; ilist; ilist = ilist->next) {
        if ((INHE_TYPE_LVTP | INHE_TYPE_CLAS) & ilist->rang_type) {
            if ((rang_type == ilist->rang_type) && !strcmp(lv2pn, ilist->lv2pn))
                break;
        }
    }
    return ilist;
}