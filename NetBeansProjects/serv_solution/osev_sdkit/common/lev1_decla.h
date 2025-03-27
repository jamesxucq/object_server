
/* 
 * File:   lev1_decla.h
 * Author: James Xu
 *
 * Created on 20211021, AM10:18
 */

#ifndef LEVO_DECLA_H
#define LEVO_DECLA_H

#include "osev_macro.h"
#include "commo_macro.h"
#include "osev_datyp.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _lev1id_ {
        char crea_lv2pn[LVTN_LENGTH]; // need
        char crea_lev1n[LVON_LENGTH]; // need
        char inhe_lev1i[LVON_LENGTH];
        char supe_lv2pn[LVTN_LENGTH];
        // char oivk_retyp[PAMTYP_LENGTH]; // delete by james 20231125
        // char inne_fmtsp_oi[FMTST_COUNT_ZTAI]; // delete by james 20231125
        CALLER_TYPE oivk_retyp_oi; // need
        char oivk_fmtsp_oi[FMTST_COUNT_ZTAI]; // out invoke params format string // need
        int oivk_size_oi; // oivk struct length // need
    };

    typedef struct _lev1id_ lev1id; // lev2 inhe method 

    //
#define LVTP_TYPE_EXCE  -1  // virtual, error
#define LVTP_TYPE_NONE  0x00 // virtual, end
#define LVTP_NORM_METH  0x01 // methn( , , ) // normal method, current class self method
#define LVTP_INHE_METH  0x02 // lv2pn:methn( , , ) // inherit method, bind current data
#define LVTP_INHE_LEVO  0x04 // lv2pn:methn // inherit method and data
#define LVTP_INHE_LVTP  0x08 // lv2pn:sub_clasn // inherit sub class
#define LVTP_INHE_CLAS  0x10 // lv2pn // inherit whole class
#define LVTP_LVTP_LEVO  0x80 // virtual, inher lev1 or lv2p

    struct _lev1_inne_i_ {
        char inne_pams[PARAM_COUNT][PARAM_LENGTH];
        int inne_count;
        char inne_fmtsp[FMTST_COUNT_ZTAI]; //  meth binding param type
    };

    typedef struct _lev1_inne_i_ lev1_inne_i;

    //

    struct _lev1_decl_i_ {
        int levtyp; // 0x01: normal method 0x02:inherit method 0x04: inherit class
        char lv2pn[LVTN_LENGTH];
        char inhe_lv2n[INHE_COUNT][LVTN_LENGTH];
        char ident[LVON_LENGTH]; // lv2pn / methn
        //
        lev1_inne_i innep;
    };

    typedef struct _lev1_decl_i_ lev1_decl_i;

    //

    struct _lev1_inne_t_ {
        char *inne_pams[PARAM_COUNT];
        char _iline_[PARAM_LENGTH];
        int inne_count;
        char inne_fmtsp[FMTST_COUNT_ZTAI]; //  meth binding param type
    };

    typedef struct _lev1_inne_t_ lev1_inne_t;
    
    //

    struct _lev1_decl_t_ {
        int levtyp;
        char lv2pn[LVTN_LENGTH];
        char *inhe_lv2n[INHE_COUNT];
        char _cline_[LINE_LENGTH];
        char ident[LVON_LENGTH]; // lv2pn / lev1n
        //
        lev1_inne_t innep;
    };

    typedef struct _lev1_decl_t_ lev1_decl_t; // in lv2p decla method

    //

    lev1_decl_t *find_lev1d(lev1_decl_t *lev1d, lev1_decl_t *lv1d);
    lev1_decl_t *find_lev1d_iden(lev1_decl_t *lv1d, char *lv2pn, char *lev1n);
    lev1_decl_t *find_lev1d_lv1n(lev1_decl_t *lv1d, char *lev1n);

    //
#define HAVE_CLASN  0x0001
#define HAVE_METHN  0x0002
#define HAVE_DECLA  0x0004
#define HAVE_BODY   0x0008

    struct _lev1_meta_ {
        unsigned int layout;
        char lv2pn[LVTN_LENGTH];
        char lev1n[LVON_LENGTH];
        char decla[LVOD_LENGTH];
        char *body;
        //
        CALLER_TYPE oivk_retyp_om;
        char oivk_fmtsp_om[FMTST_COUNT_ZTAI]; // out invoke params format string
        int oivk_size_om; // oivk struct length
    }; // split method decla

    typedef struct _lev1_meta_ lev1_meta; // parse lev1 decla

    // AUTO, INVISI, HIDE
#define ACCE_COTRL_INVAL     0x00
#define ACCE_COTRL_AUTO      0x0001
#define ACCE_COTRL_INVISI    0x0002
#define ACCE_COTRL_HIDE      0x0004

    int gener_acces_cotrl(char *acce_cont);

    //
    void dupl_lev1_decl(OUT lev1_decl_t *des_lv1d, lev1_decl_t *src_lv1d);
    lev1_decl_t *appe_lev1_decl(OUT lev1_decl_t *lev1d, lev1_decl_t *lv1d);

#ifdef __cplusplus
}
#endif

#endif /* LEVO_DECLA_H */

