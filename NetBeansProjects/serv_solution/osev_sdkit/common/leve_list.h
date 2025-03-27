
/* 
 * File:   leve_list.h
 * Author: James Xu
 *
 * Created on 2021.11.26, PM2:39
 */

#ifndef LEVE_LIST_H
#define LEVE_LIST_H

#include "lev1_decla.h"
#include "lv2p_decla.h"

#ifdef __cplusplus
extern "C" {
#endif

    struct _lev1_list_ {
        lev1_meta lev1m;
        //
        struct _lev1_list_ *next;
    };

    typedef struct _lev1_list_ lev1_list;

    //

    lev1_list *appe_lev1_meta(lev1_list **lev1_lsth, lev1_meta *lev1m);
    lev1_list *appe_lev1_list(lev1_list **lev1_lsth);

    inline void dele_lev1_list(lev1_list *l1lst) {
        lev1_list *l1nod;
        while (l1lst) {
            l1nod = l1lst;
            l1lst = l1lst->next;
            free(l1nod);
        }
    }

    //
    int lev1_list_meth(lev1_list **lev1_lsth, char *basen, char *lv2pn, char *lev1n);
    int lev1_list_clas(lev1_list **lev1_lsth, char *basen, char *lv2pn); // == lev1_list_lv2pn
    int lev1_list_whol(lev1_list **lev1_lsth, char *basen);
    int lev1_list_lv2pn(lev1_list **lev1_lsth, char *basen, char *lv2pn); // == lev1_list_clas
    
    //

    struct _lv2p_list_ {
        lv2p_decl_t lv2dt;
        //
        struct _lv2p_list_ *next;
    };

    typedef struct _lv2p_list_ lv2p_list;

    //

    lv2p_list *appe_lv2p_list(lv2p_list **lv2p_lsth);

    inline void dele_lv2p_list(lv2p_list *l2lst) {
        lv2p_list *l2nod;
        while (l2lst) {
            l2nod = l2lst;
            l2lst = l2lst->next;
            free(l2nod);
        }
    }

    //
    int lv2p_list_clas(lv2p_list **lv2p_lsth, char *basen, char *lv2pn);
    int lv2p_list_whol(lv2p_list **lv2p_lsth, char *basen);

#ifdef __cplusplus
}
#endif

#endif /* LEVE_LIST_H */

