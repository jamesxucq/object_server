
/* 
 * File:   tstri_utili.h
 * Author: James Xu
 *
 * Created on 2017.6.27, PM 3:30
 */

#ifndef TSTRI_UTILI_H
#define TSTRI_UTILI_H

#include "commo_header.h"
#include "../common/ccomm_types.h"

#ifdef __cplusplus
extern "C" {
#endif

    // -1:error 0x00:constructor 0x01:normal
    // #define METHO_CONST_TYPE    0x00
    // #define METHO_NORMA_TYPE    0x01
    int chk_norma_const(char *lv2_dec, char *lev1n);

    //

    inline char *pass_space(char *lev1_cont) {
        char *cotok = strchr(lev1_cont, '<');
        if (!cotok) return NULL;
        return cotok;
    }

    //

    int split_chead(char *const_type, char *meth_decl);
    int split_ibind_head(char *ibind, char *meth_decl);
    char *split_metho_ident(char *lev1n, char *ident);
    char *split_argu_node(char *conte, char *data);

    // trans-serve

    inline char *split_prope(char *data, char *conte) {
        char *toksp = conte;
        for (; ' ' == toksp[0x00] || ',' == toksp[0x00]; ++toksp);
        char *tokep = strchr(toksp, ',');
        if (tokep) {
            if (LVTD_LENGTH <= (tokep - toksp))
                return INVAL_POINT;
            strzcpy(data, toksp, tokep - toksp);
        } else {
            if (LVTD_LENGTH <= strlen(toksp))
                return INVAL_POINT;
            strcpy(data, toksp);
        }
        return tokep;
    }

    // trans-serve

    inline char *pass_clasn(char *lv2_dec) {
        char *detok = pass_blank(lv2_dec);
        if (!detok) return NULL;
        detok = strpbrk(detok, " <");
        if (!detok) return NULL;
        return detok;
    }
    char *prod_prop_node(char *conte, char *attri, char *data);
    char *prod_prop_item(char *conte, char *data);

    //
    int split_class_actu(char *actu_head, char *lv2_dec, char *meth_name);
    int split_class_meth(char (*actu_bind)[PARAM_LENGTH], char *actu_head);

    //
    char *split_void(char *pamvu);
    char *split_oinvk_ext(char *oivk_data, char *pamvu);
    char *split_metho_conte(OUT char *lv2pn, OUT char *lev1n, char *lev1_cont);

    //
    char *split_head(char *oivk_type, char *line_oivk, char *ibind, char *meth_decl);

    // trans-serve

    inline int const_retype_value(char *oivk_type) {
        int oivk_valu;
        KV_STIN_EQUA(oivk_valu, retyp_calle_dict, oivk_type);
        return oivk_valu;
    }

    // trans-serve

    inline void split_body(char *lev1_body, char *lev1_cont) {
        char *cotok = strchr(lev1_cont, '{');
        if (cotok) strcpy(lev1_body, cotok);
    }

    // trans-serve
    int split_class_prope(char (*lv2p_prop)[PARAM_LENGTH], char *lv2_dec);
    int split_lv2p_prop(char *lv2pn, char (*lv2p_prop)[PARAM_LENGTH], char *lv2_dec);
    int split_class_name_prope(char *lv2pn, char (*lv2p_prop)[PARAM_LENGTH], char *lv2_dec);

    //
    char *split_toke(char *node_str, int *node_type, char *body_text);
    int split_meth_head(char (*form_bind)[PARAM_LENGTH], char *lev1_cont);

    //
    int check_decla(char *conte);
    char *node_line(char *node_cont, char *conte);
    int split_decla(char *type, char (*varip)[PARAM_LENGTH], char *valu, char *decla);

    // trans-serve
    char *split_oinvk_iden(char *ostyp, char *pamvs);

    // trans-serve

    inline char *ostyp_format_char(char *fmtst, char *ostyp) {
        if (strchr(ostyp, '&')) fmtst = lccpy(fmtst, 'R');
        KV_STCH_LCPY(fmtst, ostyp_fmtst_dict, ostyp);
        return fmtst;
    }

    // trans-serve
    int split_oinvk_head(char *line_oivk, char *meth_decl);
    // trans-serve
    char *split_oinvk(char *ostyp, char *pamvs);

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
    char *split_oinvk_node(char *oivk_node, char *pamvs);
    // trans-serve
    unsigned int split_pamvu_colum(char (*parm_arra)[PARAM_LENGTH], char *conte);
    // trans-serve
    int parse_pamvu_colum(pamv_node *pamnod, char (*parm_arra)[PARAM_LENGTH]);

    //

#ifdef __cplusplus
}
#endif

#endif /* TSTRI_UTILI_H */

