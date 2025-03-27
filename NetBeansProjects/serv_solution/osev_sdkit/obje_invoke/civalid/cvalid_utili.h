
/* 
 * File:   valid_utili.h
 * Author: James Xu
 *
 * Created on 2021.11.15, PM2:53
 */

#ifndef VALID_UTILI_H
#define VALID_UTILI_H

#include "repla/repla_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int valid_replc_addim(char *basen, replc_list *rep_nod);
    int valid_replc_delem(char *basen, replc_list *rep_nod);
    int valid_replc_bindm(char *basen, replc_list *rep_nod);

    //
    int valid_dropc_integ(char *basen, char *lv2pn, integra *olist);
    lev1_decl_t *chk_same_lev1n(lev1_decl_t *lev1d, lev1_decl_t *lv1d);

    //

    struct _lv2iex_ {
        char lv2pn[LVTN_LENGTH];
        bool_osv iexter; // 0x00: internal 0x01: external
        inherit *inher_list;
        //
        struct _lv2iex_ *next;
    };

    typedef struct _lv2iex_ lv2iex;

#define INITI_LVTIEX_LVTPN(LTE_NOD, LVTPN) { \
    strcpy(LTE_NOD->lv2pn, LVTPN); \
    LTE_NOD->inher_list = NULL; \
    LTE_NOD->next = NULL; \
}

    //

    struct _lv2ex_conte_ {
        lv2iex *l2ie_list;
        lv2iex *l2ie_posi;
        lv2iex *l2ie_last;
    };

    typedef struct _lv2ex_conte_ lv2ex_conte;

    //

    inline void initi_lv2ex_conte(lv2ex_conte * l2ie_cont) {
        l2ie_cont->l2ie_list = NULL;
        l2ie_cont->l2ie_posi = NULL;
        l2ie_cont->l2ie_last = NULL;
    }
    //

    inline void final_lv2ex_conte(lv2ex_conte *l2ie_cont) {
        lv2iex *elsnd;
        lv2iex *l2e_nod = l2ie_cont->l2ie_list;
        //
        while ((elsnd = l2e_nod)) {
            ilist_dele(l2e_nod->inher_list);
            l2e_nod = l2e_nod->next;
            free(elsnd);
        }
    }
    //

    inline lv2iex *get_l2ie_node(lv2ex_conte *l2ie_cont) {
        lv2iex *l2e_nod = l2ie_cont->l2ie_posi;
        if (l2e_nod)
            l2ie_cont->l2ie_posi = l2e_nod->next;
        //
        return l2e_nod;
    }
    //

    inline lv2iex *appe_lv2ie_init(lv2ex_conte *l2ie_cont, char *lv2pn) {
        lv2iex *l2e_nod = (lv2iex *) malloc(sizeof (lv2iex));
        if (!l2e_nod) return NULL;
        INITI_LVTIEX_LVTPN(l2e_nod, lv2pn)
        //
        l2ie_cont->l2ie_list = l2e_nod;
        l2ie_cont->l2ie_posi = l2e_nod;
        l2ie_cont->l2ie_last = l2e_nod;
        //
        return l2e_nod;
    }

    inline lv2iex *appe_lv2ie_new(lv2ex_conte *l2ie_cont, char *lv2pn) {
        lv2iex *l2e_nod = (lv2iex *) malloc(sizeof (lv2iex));
        if (!l2e_nod) return NULL;
        INITI_LVTIEX_LVTPN(l2e_nod, lv2pn)
        //
        l2ie_cont->l2ie_last->next = l2e_nod;
        l2ie_cont->l2ie_last = l2e_nod;
        //
        return l2e_nod;
    }

    //
    int valid_iextec_ite(char *basen, char *lv2pn);

    //

#ifdef __cplusplus
}
#endif

#endif /* VALID_UTILI_H */

