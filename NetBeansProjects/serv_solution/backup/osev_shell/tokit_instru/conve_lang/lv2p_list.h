
/* 
 * File:   lv2p_list.h
 * Author: James Xu
 *
 * Created on 2017.6.23, AM 9:34
 */

#ifndef LVTP_LIST_H
#define LVTP_LIST_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    struct _integra_ocl_ {
        char lev1n[LVON_LENGTH];
        struct _integra_ocl_ *next;
    };

    typedef struct _integra_ocl_ levon;

    //

    struct _method_ {
        char lev1n[LVON_LENGTH];
        char param_type[PAMTYP_LENGTH];
        char lev1_cont[LARGE_TEXT_SIZE];
        struct _method_ *next;
    };

    typedef struct _method_ method;

    //

    struct _class_meta_ {
        osv_oid_t lv2p_obid;
        char lv2pn[LVTN_LENGTH];
        unsigned long long versio; // 0x00:disable >0x00:is version
        bool_osv iextern; // 0x00: internal 0x01: external
        unsigned integral; // integrality
        levon *levo_list;
        char lv2p_decl[LARGE_TEXT_SIZE];
        method *meth_list;
    };

    typedef struct _class_meta_ class_meta;

    //
    levon *appe_slist_new(levon **lsth);

    inline void slist_dele(levon *slist) {
        levon *slsnd;
        while ((slsnd = slist)) {
            slist = slist->next;
            free(slsnd);
        }
    }

    method *appe_mlist_new(method **mlsth);

    inline void mlist_dele(method *mlist) {
        method *mlsnd;
        while ((mlsnd = mlist)) {
            mlist = mlist->next;
            free(mlsnd);
        }
    }
    //
#define CLAM_STRU_DELE(LVTDI); \
    slist_dele(LVTDI.levo_list); \
    mlist_dele(LVTDI.meth_list);

#define RETU_DELM(CLAM, RET_VAL) { \
        slist_dele(CLAM.levo_list); \
        mlist_dele(CLAM.meth_list); \
        return RET_VAL; \
    }

#ifdef __cplusplus
}
#endif

#endif /* LVTP_LIST_H */

