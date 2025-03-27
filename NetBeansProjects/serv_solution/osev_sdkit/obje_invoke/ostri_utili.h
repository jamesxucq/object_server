
/* 
 * File:   ostri_utili.h
 * Author: James Xu
 *
 * Created on 2016.12.17, PM 3:39
 */

#ifndef OSTRI_UTILI_H
#define OSTRI_UTILI_H

#include "commo_header.h"
#include "kcomm_header.h"

#include "lv2p_decla.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    char *split_metho_conte(OUT char *lv2pn, OUT char *lev1n, char *lev1_cont);

    //
    char *prod_prop_node(char *conte, char *attri, char *data);
    char *split_argu_node(char *conte, char *data);

    // trans-serve
    // 

    inline char *split_prope(char *data, char *conte) {
        char *toksp = conte;
        for (; ' ' == toksp[0x00] || ',' == toksp[0x00]; ++toksp);
        char *tokep = strchr(toksp, ',');
        if (tokep) {
            if (LVTD_LENGTH <= (tokep - toksp))
                return NULL;
            strzcpy(data, toksp, tokep - toksp);
        } else {
            if (LVTD_LENGTH <= strlen(toksp))
                return NULL;
            strcpy(data, toksp);
        }
        return tokep;
    }

    // trans-serve

    inline char *pass_clasn(char *lv2_dec) {
        char *detok;
        PASS_TBLANK(detok, lv2_dec)
        detok = strpbrk(detok, " <");
        if (!detok) return NULL;
        return detok;
    }

    char *split_metho_ident(OUT char *lev1n, char *ident);

    //

    inline char *pass_space(char *lev1_cont) {
        char *cotok = strchr(lev1_cont, '<');
        if (!cotok) return NULL;
        return cotok;
    }

    char *split_head(char *oivk_type, char *line_oivk, char *ibind, char *meth_decl);
    // trans-serve

    inline int const_retype_value(char *oivk_type) {
        int oivk_valu;
        KV_STIN_EQUA(oivk_valu, retyp_calle_dict, oivk_type);
        return oivk_valu;
    }
    // trans-serve
    int split_oinvk_retyp(char *retype, char *meth_decl);
    int split_oinvk_head(char *line_oivk, char *meth_decl);
    int split_ibind_head(char *ibind, char *meth_decl);
    int split_chead(char *const_type, char *meth_decl);

    // trans-serve

    inline void split_body(char *lev1_body, char *lev1_cont) {
        char *cotok = strchr(lev1_cont, '{');
        if (cotok) strcpy(lev1_body, cotok);
    }

    int split_class_actu(char *actu_head, char *lv2_dec, char *lev1n);
    char *split_toke(char *node_str, int *node_type, char *body_text);
    int split_meth_head(char (*form_bind)[PARAM_LENGTH], char *lev1_cont);
    int split_meth_oivk(char (*form_oivk)[PARAM_LENGTH], char *lev1_cont);
    int split_class_meth(char (*actu_bind)[PARAM_LENGTH], char *actu_head);

    //
    char *split_void(char *parms);
    // trans-serve
    char *split_oinvk(char *ostyp, char *parms);
    // trans-serve
    char *split_oinvk_iden(char *ostyp, char *parms);
    // trans-serve
    char *split_oinvk_node(char *oivk_node, char *parms);

    // trans-serve
    int split_class_prope(char (*lv2p_prop)[PARAM_LENGTH], char *lv2_dec);
    int split_class_name_prope(char *lv2pn, char (*lv2p_prop)[PARAM_LENGTH], char *lv2_dec);

    // -1:error 0x00:constructor 0x01:normal
    // #define METHO_CONST_TYPE    0x00
    // #define METHO_NORMA_TYPE    0x01
    int chk_norma_const(char *lv2_dec, char *lev1n);

    //
    char *split_ibind(DATA_TYPE *prop_type, lv2p_prop *l2_nod, char *parms);
    char *split_ibind_lv2d(lv2p_prop *lv2nod, lv2p_prop *l2_nod, char *parms);
    char *split_ibind_pamvs(char *pamvu, char *parms);
    char *split_ibind_parap(char **pamvp, char *parms);

    // taat<[xx=8 int, ax int], teet:xxp(), [cx int] auto, tst(xx), [dx int] auto, teet:tpp(ax), txp(ax, cx)>;
    // LVTP_NORM_METH: txp(ax, cx) | clasn_inhe[0x00]:taat ident:txp
    // LVTP_INHE_METH: teet:tpp(ax) | clasn_inhe[0x00]:taat clasn_inhe[0x01]:teet ident:tpp
    // LVTP_INHE_LEVO: teet:tpp | clasn_inhe[0x00]:taat clasn_inhe[0x01]:teet ident:tpp
    // LVTP_INHE_LVTP: teet:txxp:xxoo | clasn_inhe[0x00]:taat clasn_inhe[0x01]:teep clasn_inhe[0x02]:txxp ident:xxoo
    // LVTP_INHE_CLAS: teet | clasn_inhe[0x00]:taat clasn_inhe[0x01]:teet ident:MK_ZERO
    char *parse_lev1d_node(lev1_decl_t *lev1d, char *data);

    //
    char *split_inher_clasn(OUT char **cinhep, char *_cline_);

    //

    inline char *echo_inher_clasn(OUT char *cline, char *lv2pn, char **inhe_l2np) {
        cline = lscpy(cline, lv2pn);
        for (; inhe_l2np[0x00]; ++inhe_l2np) {
            cline = lccpy(cline, ':');
            cline = lscpy(cline, inhe_l2np[0x00]);
        }
        return cline;
    }

    //

    inline char *last_lv2pn(char **lv2pnp) {
        char *last_lv2n = NULL;
        for (; lv2pnp[0x00]; ++lv2pnp)
            last_lv2n = lv2pnp[0x00];
        return last_lv2n;
    }

    //
    char *node_line(char *node_cont, char *conte);
    int check_decla(char *conte);
    int split_decla(char *type, char (*varip)[PARAM_LENGTH], char *valu, char *decla);

    // trans-serve
#define PARM_COLU_SIZE 0x04
    // trans-serve

    struct _pamv_node_ {
        char name[PARAM_LENGTH];
        char type[PARAM_LENGTH];
        char array[PARAM_LENGTH];
        char defau[PARAM_LENGTH];
        unsigned int attri;
    };
    // trans-serve
    typedef struct _pamv_node_ pamv_node;
    // trans-serve
    unsigned int split_pamvu_colum(char (*parm_arra)[PARAM_LENGTH], char *conte);
    // trans-serve
    int parse_pamvu_colum(pamv_node *pamnod, char (*parm_arra)[PARAM_LENGTH]);

    //

    inline char *split_inher_lv2pn(char *inhe_lv2n) {
        char *lv2pn = strrchr(inhe_lv2n, ':');
        return lv2pn ? ++lv2pn : inhe_lv2n;
    }

    //

    inline char *split_lev1n_lv2pn(char *lv2pn, char *lv2p_lev1) {
        char *lev1n = strrchr(lv2p_lev1, ':');
        if (!lev1n) return NULL;
        strzcpy(lv2pn, lv2p_lev1, lev1n - lv2p_lev1);
        return ++lev1n;
    }

    char *split_lv2pn_node(char **l2np_nod, char *lv2pn);

    //
    int build_columns_types(char *types, lv2p_prop *l2_nod);

    //

    inline int ilev1_pamvu_type(char *fmtsd, lv2p_prop * lv2nod) {
        for (; ACCE_COTRL_INVAL != lv2nod->access; ++lv2nod) {
            fmtsd = lccpy(fmtsd, potyp_fmtst_tab[lv2nod->potyp]);
        }
        return 0x00;
    }

    //
    char *split_inner_parms(OUT char **pamvp, char *_iline_);

    //

    inline char *build_handl_name(OUT char *handn, char *lv2pn, char *lev1n, char *fmtst) {
        handn = lscpy(handn, lv2pn);
        handn = lccpy(handn, '_');
        handn = lscpy(handn, lev1n);
        handn = lccpy(handn, '_');
        handn = lscpy(handn, fmtst);
        return handn;
    }

    //

    inline char *build_ihand_name(char *handn, char *lv2pn, char *lev1n, char *fmtst) {
        handn = lscpy(handn, lv2pn);
        handn = lccpy(handn, '_');
        handn = lscpy(handn, lev1n);
        handn = lccpy(handn, '_');
        handn = lscpy(handn, fmtst);
        return handn;
    }

#ifdef __cplusplus
}
#endif

#endif /* OSTRI_UTILI_H */

