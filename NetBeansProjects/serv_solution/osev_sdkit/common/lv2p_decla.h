
/* 
 * File:   lv2p_decla.h
 * Author: James Xu
 *
 * Created on 20211021, AM10:18
 */

#ifndef LVTP_DECLA_H
#define LVTP_DECLA_H

// #include "commo_header.h"
// #include "seion_struct.h"
#include "obid.h"
#include "lev1_decla.h"

#ifdef __cplusplus
extern "C" {
#endif

    // property

    struct _lv2p_prop_ {
        uint32 access; // access control
        char name[PARAM_LENGTH];
        DATA_TYPE potyp;
        uint32 size;
        char decla[LVTD_LENGTH];
    };

    typedef struct _lv2p_prop_ lv2p_prop;

    //

    lv2p_prop *find_lv2p_prop(lv2p_prop *lv2_nod, lv2p_prop *lv2d);

    //

    struct _lv2p_decl_t_ {
        osv_oid_t lv2p_obid;
        char lv2pn[LVTN_LENGTH];
        lv2p_prop lv2nod[LVTNOD_COUNT];
        lev1_decl_t meth[LEVO_COUNT];
    }; // parse class decla

    typedef struct _lv2p_decl_t_ lv2p_decl_t;

    //

    struct _lv1_cont_ {
        char lev1n[LVON_LENGTH];
        CALLER_TYPE oivk_retyp_oc; // need
        char oivk_fmtsp_oc[FMTST_COUNT_ZTAI]; // out invoke params format string // need
        int oivk_size_oc; // oivk struct length // need
        char conte[LARGE_TEXT_SIZE];
        //
        struct _lv1_cont_ *next;
    };

    typedef struct _lv1_cont_ lv1_cont;

    //
    lv1_cont *appe_l1clst_new(lv1_cont **l1clsth);
    lv1_cont *appe_l1clst_conte(lv1_cont **l1clsth, char *lev1_cont);

#define LVOCND_DELE(LOC_NOD) free(LOC_NOD)

    inline void l1clst_dele(lv1_cont *l1lsnd) {
        lv1_cont *l1c_nod;
        while ((l1c_nod = l1lsnd)) {
            l1lsnd = l1lsnd->next;
            free(l1c_nod);
        }
    }

    //

    struct _lv2p_decl_i_ {
        char lv2pn[LVTN_LENGTH];
        char lv2p_decl[LARGE_TEXT_SIZE];
        lv1_cont *l1con_list;
    }; // parse class file

    typedef struct _lv2p_decl_i_ lv2p_decl_i;

    //
#define INIT_LVTP_DECL(LVTPDI) \
    (LVTPDI).lv2pn[0x00] = '\0'; \
    (LVTPDI).lv2p_decl[0x00] = '\0'; \
    (LVTPDI).l1con_list = NULL;
    //

    // LVTP_LVTP_LEVO
    int parse_lv2pd_decla(lv2p_decl_t *lv2dt, char *lv2_dec);
    int parse_lv2pd_nonam(lv2p_decl_t *lv2dt, char *lv2_dec);
    // LVTP_LVTP_LEVO
    int parse_lv2pd_clasp(lv2p_decl_t *lv2dt, char *lv2d_path);
    int parse_lv2pd_clasn(lv2p_decl_t *lv2dt, char *basen, char *lv2pn);

    // LVTP_INHE_LEVO LVTP_INHE_LVTP
    int build_lv2pd_conte(lv2p_decl_t *lv2dt, char *lv2_dec, char *basen);
    int build_lv2pd_nonam(lv2p_decl_t *lv2dt, char *lv2_dec, char *basen);
    // LVTP_INHE_LEVO LVTP_INHE_LVTP
    int build_lv2pd_clasp(lv2p_decl_t *lv2dt, char *lv2p_path, char *basen);
    int build_lv2pd_clasn(lv2p_decl_t *lv2dt, char *basen, char *lv2pn);

    //
    void copy_lv2p_prop(OUT lv2p_prop *l2_nod, lv2p_prop *lv2nod);

    // trans-serve
    char *split_class_conte(char *lv2_dec, char *lv2p_cont);
    char *split_metho_decla(char *lv2p_cont);

    //
    int parse_lev2p_prope(OUT lv2p_prop *lv2nod, char *basen, char *lv2pn);

    //
    char *find_defin_decla_ext(char *lvnsps, char *lev1_invk, char *lv2p_cont);

    // trans-serve

    inline char *l1nsps_delim(char *l1nsps) {
        char *stri = strchr(l1nsps, ':');
        if (stri) ++stri;
        return stri;
    }

    //
    int filli_inner_parms(lev1_inne_t *innep, lv2p_prop *lv2nod);

#ifdef __cplusplus
}
#endif

#endif /* LVTP_DECLA_H */

