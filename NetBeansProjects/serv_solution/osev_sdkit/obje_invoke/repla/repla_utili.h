
/* 
 * File:   repla_utili.h
 * Author: James Xu
 *
 * Created on 2021.11.29, AM10:33
 */

#ifndef REPLA_UTILI_H
#define REPLA_UTILI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#define REPLC_MORE_DATA     0x0001 // data
#define REPLC_LESS_DATA     0x0002 // data
#define REPLC_ADDI_METH     0x0003 // meth
#define REPLC_DELE_METH     0x0004 // meth
#define REPLC_BIND_CHAN     0x0005 // meth

    //

    struct _replc_list_ {
        unsigned int replc_type;
        int levtyp;
        char ident[PARAM_LENGTH];
        char lv2pn[LVTN_LENGTH];
        char fmtsp[FMTST_COUNT_ZTAI]; // fmtst
        //
        struct _replc_list_ *next;
    };

    typedef struct _replc_list_ replc_list;

    //

    replc_list *appe_replc_list(replc_list **rep_lsh);
    replc_list *appe_replc_iden(replc_list **rep_lsh, char *ident, unsigned int replc_type);
    replc_list *appe_replc_lv1d(replc_list **rep_lsh, lev1_decl_t *lev1d, unsigned int replc_type);

    inline void dele_replc_list(replc_list *replst) {
        replc_list *rlsnd;
        while (replst) {
            rlsnd = replst;
            replst = replst->next;
            free(rlsnd);
        }
    }

    // 0:not changed >0:new data is more <0:new data is less
    int chk_lv2p_prop(OUT replc_list **rep_lsh, lv2p_prop *exi_lv2po, lv2p_prop *new_lv2po);

    // 0:not changed >0:add new meth <0:dele meth 
    // 0:not changed >0:binding changed <0:error
    int chk_bind_meth(OUT replc_list **rep_lsh, lev1_decl_t *exi_meth, lev1_decl_t *new_meth);


#ifdef __cplusplus
}
#endif

#endif /* REPLA_UTILI_H */

