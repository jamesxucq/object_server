#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "ostri_utili.h"

#include "repla/repla_utili.h"
#include "filli_clang.h"
#include "debug_funct_oi.h"
#include "lev1_decla.h"


// 0:not changed >0:new data is more <0:new data is less;

int chk_lv2p_prop(replc_list **rep_lsh, lv2p_prop *exi_lv2po, lv2p_prop *new_lv2po) {
    OSEVPF("[FUNC]:chk_lv2p_prop\n");
    lv2p_prop *l2nod1 = new_lv2po;
    lv2p_prop *l2nod2;
    //
    for (; ACCE_COTRL_INVAL != l2nod1->access; ++l2nod1) {
        l2nod2 = find_lv2p_prop(exi_lv2po, l2nod1);
        if (!l2nod2) {
            if (!appe_replc_iden(rep_lsh, l2nod1->name, REPLC_MORE_DATA))
                return -1;
        } else MK_ZERO(l2nod2->name);
    }
    //
    l2nod2 = exi_lv2po;
    for (; ACCE_COTRL_INVAL != l2nod2->access; ++l2nod2) {
        if (NOT_ZERO(l2nod2->name)) {
            if (!appe_replc_iden(rep_lsh, l2nod2->name, REPLC_LESS_DATA))
                return -1;
        }
    }
    //
    return 0x00;
}

// 0x00:not change >0x00:changed <0x00:error

static int chk_bind_chan(lev1_inne_t *innep1, lev1_inne_t *innep2) {
    OSEVPF("[FUNC]:chk_bind_chan\n");
    if (innep2->inne_count != innep1->inne_count)
        return 0x01;
    char **parap1 = innep1->inne_pams;
    char **parap2 = innep2->inne_pams;
    for (; parap1[0x00] && parap2[0x00]; ++parap1, ++parap2) {
        if (strcmp(parap1[0x00], parap2[0x00]))
            return 0x01;
    }
    //
    return 0x00;
}

// 0:not changed >0:add new meth <0:dele meth

int chk_bind_meth(replc_list **rep_lsh, lev1_decl_t *exi_meth, lev1_decl_t *new_meth) {
    OSEVPF("chk_bind_meth\n");
    lev1_decl_t *lv1de1 = new_meth;
    lev1_decl_t *lv1de2;
    // OSEVPF("[FUNC]:appe_replc_lv1d, REPLC_ADDI_METH\n");
    for (; LVTP_TYPE_NONE != lv1de1->levtyp; ++lv1de1) {
        lv1de2 = find_lev1d(exi_meth, lv1de1);
        if (!lv1de2) {
            OSEVPF("REPLC_ADDI_METH\n");
            PRIN_lev1_decl(lv1de1);
            if (!appe_replc_lv1d(rep_lsh, lv1de1, REPLC_ADDI_METH))
                return -1;
        } else {
            // 0:not changed >0:binding changed <0:error
            if (chk_bind_chan(&lv1de2->innep, &lv1de1->innep)) {
                OSEVPF("REPLC_BIND_CHAN\n");
                PRIN_lev1_decl(lv1de1);
                if (!appe_replc_lv1d(rep_lsh, lv1de1, REPLC_BIND_CHAN))
                    return -1;
            }
            MK_ZERO(lv1de2->ident);
        }
    }
    // OSEVPF("appe_replc_lv1d, REPLC_DELE_METH\n");
    lv1de2 = exi_meth;
    for (; LVTP_TYPE_NONE != lv1de2->levtyp; ++lv1de2) {
        if (NOT_ZERO(lv1de2->ident)) {
            OSEVPF("REPLC_DELE_METH\n");
            PRIN_lev1_decl(lv1de2);
            if (!appe_replc_lv1d(rep_lsh, lv1de2, REPLC_DELE_METH))
                return -1;
        }
    }
    //
    return 0x00;
}

//

#define CLIST_APPEND(head, add) { \
    LDECLTYPE(head) _tmp; \
    if (head) { \
        _tmp = head; \
        while (_tmp->next) _tmp = _tmp->next; \
        _tmp->next = add; \
    } else head = add; \
}

replc_list *appe_replc_list(replc_list **rep_lsh) {
    replc_list *rlsnd = (replc_list *) malloc(sizeof (replc_list));
    if (!rlsnd) return NULL;
    // memset(rlsnd, '\0', sizeof (replc_list));
    rlsnd->next = NULL;
    //
    CLIST_APPEND(*rep_lsh, rlsnd);
    return rlsnd;
}

replc_list *appe_replc_iden(replc_list **rep_lsh, char *ident, unsigned int replc_type) {
    replc_list *rlsnd = (replc_list *) malloc(sizeof (replc_list));
    if (!rlsnd) return NULL;
    // memset(rlsnd, '\0', sizeof (replc_list));
    rlsnd->next = NULL;
    rlsnd->replc_type = replc_type;
    strcpy(rlsnd->ident, ident);
    //
    CLIST_APPEND(*rep_lsh, rlsnd);
    return rlsnd;
}

replc_list *appe_replc_lv1d(replc_list **rep_lsh, lev1_decl_t *lev1d, unsigned int replc_type) {
    replc_list *rlsnd = (replc_list *) malloc(sizeof (replc_list));
    if (!rlsnd) return NULL;
    // memset(rlsnd, '\0', sizeof (replc_list));
    rlsnd->next = NULL;
    rlsnd->replc_type = replc_type;
    rlsnd->levtyp = lev1d->levtyp;
    strcpy(rlsnd->ident, lev1d->ident);
    strcpy(rlsnd->lv2pn, lev1d->lv2pn);
    strcpy(rlsnd->fmtsp, lev1d->innep.inne_fmtsp);
    //
    CLIST_APPEND(*rep_lsh, rlsnd);
    return rlsnd;
}

//

