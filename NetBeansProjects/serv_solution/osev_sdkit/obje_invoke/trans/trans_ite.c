#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "ostri_utili.h"
#include "trans_utili.h"
#include "inheri/inheri_ite.h"

#include "istri_utili.h"
#include "trans_ite.h"
#include "lv2p_expand.h"
#include "lev1_decla.h"
#include "filli_clang.h"
#include "debug_funct_oi.h"

//

int lv2p_clang_ite(lv2p_prop *l2_nod, char *basen, lv2p_decl_t *lv2dt) {
    // OSEVPF("[FUNC]:lv2p_clang_ite\n");
    // colum colu_data[LVTNOD_COUNT];
    copy_lv2p_prop(l2_nod, lv2dt->lv2nod);
    //
    lev1_decl_t *lv1d = lv2dt->meth;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        switch (lv1d->levtyp) {
            case LVTP_INHE_LEVO:
                if (inser_lv1da_ite(l2_nod, basen, lv1d->inhe_lv2n, lv1d->ident))
                    return -1;
                break;
            case LVTP_INHE_LVTP:
                if (inser_lv2po_ite(l2_nod, basen, lv1d->inhe_lv2n))
                    return -1;
                break;
            case LVTP_INHE_CLAS:
                if (inser_clapo_ite(l2_nod, basen, lv1d->inhe_lv2n[0x00]))
                    return -1;
                break;
        }
    }
    // char colu_types[TYPES_LENGTH];
    // build_columns_types(colu_types, l2_nod);
    // if (crea_lv2p_colu(colu_data, l2_nod))
    // return -1;
    // PRIN_lv2p_prop_array(l2_nod);
    // PRIN_colum(colu_data);
    // if (!filli_rllv2p_conte(clang_cont, lv2dt->lv2pn, l2_nod, colu_types, colu_data))
    // return -1;
    //
    return 0x00;
}

// reload class

int class_clang_ite(char *clang_cont, char *basen, lv2p_decl_t *lv2dt) {
    // OSEVPF("[FUNC]:class_clang_ite\n");
    lv2p_prop l2_nod[LVTNOD_COUNT];
    colum colu_data[LVTNOD_COUNT];
    copy_lv2p_prop(l2_nod, lv2dt->lv2nod);
    //
    lev1_decl_t *lv1d = lv2dt->meth;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        switch (lv1d->levtyp) {
            case LVTP_INHE_LEVO:
                if (inser_lv1da_ite(l2_nod, basen, lv1d->inhe_lv2n, lv1d->ident))
                    return -1;
                break;
            case LVTP_INHE_LVTP:
                if (inser_lv2po_ite(l2_nod, basen, lv1d->inhe_lv2n))
                    return -1;
                break;
            case LVTP_INHE_CLAS:
                if (inser_clapo_ite(l2_nod, basen, lv1d->inhe_lv2n[0x00]))
                    return -1;
                break;
        }
    }
    //
    char colu_types[TYPES_LENGTH];
    build_columns_types(colu_types, l2_nod);
    if (crea_lv2p_colu(colu_data, l2_nod))
        return -1; // 
    // PRIN_lv2p_prop_array(l2_nod);
    // PRIN_colum(colu_data);
    if (!filli_rllv2p_conte(clang_cont, lv2dt->lv2pn, l2_nod, colu_types, colu_data))
        return -1;
    //
    return 0x00;
}

//

static int parse_meth_data(conve_metho *metho, char *lev1_cont) {
    lev1_cont = split_metho_conte(metho->lv2pn, metho->lev1n, lev1_cont);
    if (!lev1_cont) return -1;
    // OSEVPF("lv2pn:|%s|\n", metho->lv2pn);
    // OSEVPF("meth_name:|%s|\n", metho->lev1n);
    lev1_cont = split_head(metho->oivk_retyp, metho->line_oivk, metho->ibind, lev1_cont);
    if (!lev1_cont) return -1;
    if (const_oinvk_pmtyp(metho->oivk_fmtsp, metho->line_oivk))
        return -1;
    // OSEVPF("line_oivk:|%s|\n", metho->line_oivk);
    // OSEVPF("ibind:|%s|\n", metho->ibind);
    split_body(metho->lev1_body, lev1_cont);
    // OSEVPF("lev1_body:|%s|\n", metho->lev1_body);
    return 0x00;
}

//

static int trans_bind_parm_norm(char *lev1_body, char (*form_bind)[PARAM_LENGTH], char (*actu_bind)[PARAM_LENGTH]) {
    // OSEVPF("[FUNC]:trans_bind_parm_norm\n");
    char body_str[LARGE_TEXT_SIZE];
    char node_str[LINE_LENGTH];
    //
    strcpy(body_str, lev1_body);
    char *last_str = body_str;
    char *last_body = lev1_body;
    //
    char (*formp)[PARAM_LENGTH], (*actup)[PARAM_LENGTH];
    int node_type;
    while (last_str && '\0' != last_str[0x00]) {
        // OSEVPF("-------- last_str:|%s|\n", last_str);
        last_str = split_toke(node_str, &node_type, last_str);
        // OSEVPF("node_type:%d node_str:|%s|\n", node_type, node_str);
        if (!node_type) {
            formp = form_bind;
            actup = actu_bind;
            for (; '\0' != (*formp)[0x00]; ++formp, ++actup) {
                if (!strcmp(node_str, formp[0x00])) {
                    // OSEVPF("formp:|%s| node_str:|%s|\n", formp[0x00], node_str);
                    char *last_nod = lscpy(node_str, "this->");
                    lscpy(last_nod, actup[0x00]);
                    // OSEVPF("node_str:|%s| actup:|%s|\n", node_str, actup[0x00]);
                    break;
                }
            }
        }
        last_body = lscpy(last_body, node_str);
    }
    //
    return 0x00;
}

static int tran_oivk_parm(char *lev1_body, char (*form_oivk)[PARAM_LENGTH]) {
    // OSEVPF("[FUNC]:tran_oivk_parm\n");
    char body_str[LARGE_TEXT_SIZE];
    char node_str[LINE_LENGTH];
    //
    strcpy(body_str, lev1_body);
    char *last_str = body_str;
    char *last_body = lev1_body;
    //
    char (*formp)[PARAM_LENGTH];
    int node_type;
    while (last_str && '\0' != last_str[0x00]) {
        // OSEVPF("-------- last_str:|%s|\n", last_str);
        last_str = split_toke(node_str, &node_type, last_str);
        // OSEVPF("node_type:%d node_str:|%s|\n", node_type, node_str);
        if (!node_type) {
            formp = form_oivk;
            for (; '\0' != (*formp)[0x00]; ++formp) {
                if (!strcmp(node_str, formp[0x00])) {
                    // OSEVPF("formp:|%s| node_str:|%s|\n", formp[0x00], node_str);
                    char *last_nod = lscpy(node_str, "pamvp->");
                    lscpy(last_nod, formp[0x00]);
                    // OSEVPF("node_str:|%s| actup:|%s|\n", node_str, actup[0x00]);
                    break;
                }
            }
        }
        last_body = lscpy(last_body, node_str);
    }
    //
    return 0x00;
}

static int tran_oivk_reval(char *lev1_body, int oivk_retyp) {
    OSEVPF("[FUNC]:tran_oivk_reval ---------------------------------\n");
    char body_str[LARGE_TEXT_SIZE];
    char node_str[LINE_LENGTH];
    //
    strcpy(body_str, lev1_body);
    char *last_str = body_str;
    char *last_body = lev1_body;
    //
    int last_reval = 0x00;
    int node_type;
    while (last_str && '\0' != last_str[0x00]) {
        // OSEVPF("-------- last_str:|%s|\n", last_str);
        last_str = split_toke(node_str, &node_type, last_str);
        OSEVPF("node_type:%d node_str:|%s|\n", node_type, node_str);
        if (last_reval && (0x02 == node_type)) {
            char *semic = node_str; // semicolon
            for (; semic[0x00]; ++semic) {
                if (';' == semic[0x00]) {
                    last_body = lscpy(last_body, "; return; }");
                    --last_reval;
                    break;
                }
            }
        } else if (!node_type) {
            if (!strcmp(node_str, "return")) {
                // OSEVPF("formp:|%s| node_str:|%s|\n", formp[0x00], node_str);
                switch (oivk_retyp) {
                    case RTYP_VOID:
                        break;
                    case RTYP_CHAR:
                        lscpy(node_str, "{ rvalu->retype.rchar = ");
                        break;
                    case RTYP_UCHA:
                        lscpy(node_str, "{ rvalu->retype.rucha = ");
                        break;
                    case RTYP_SHOR:
                        lscpy(node_str, "{ rvalu->retype.rshor = ");
                        break;
                    case RTYP_USHO:
                        lscpy(node_str, "{ rvalu->retype.rusho = ");
                        break;
                    case RTYP_INT:
                        lscpy(node_str, "{ rvalu->retype.rint = ");
                        break;
                    case RTYP_UINT:
                        lscpy(node_str, "{ rvalu->retype.ruint = ");
                        break;
                    case RTYP_LONG:
                        lscpy(node_str, "{ rvalu->retype.rlong = ");
                        break;
                    case RTYP_ULON:
                        lscpy(node_str, "{ rvalu->retype.rulong = ");
                        break;
                    case RTYP_LLON:
                        lscpy(node_str, "{ rvalu->retype.rllong = ");
                        break;
                    case RTYP_ULLO:
                        lscpy(node_str, "{ rvalu->retype.rullon = ");
                        break;
                    case RTYP_FLOA:
                        lscpy(node_str, "{ rvalu->retype.rfloa = ");
                        break;
                    case RTYP_DOUB:
                        lscpy(node_str, "{ rvalu->retype.rdoub = ");
                        break;
                    case RTYP_CHAP:
                        lscpy(node_str, "{ rvalu->retype.rchap = ");
                        break;
                    case RTYP_STRZ:
                        lscpy(node_str, "{ rvalu->retype.rstrz = ");
                        break;
                    default:
                        break;
                }
                // OSEVPF("node_str:|%s| actup:|%s|\n", node_str, actup[0x00]);
                ++last_reval;
            }
        }
        last_body = lscpy(last_body, node_str);
    }
    //
    return 0x00;
}

static int trans_bind_parm_cons(char *lev1_body, char (*lv2p_prop)[PARAM_LENGTH]) {
    // OSEVPF("[FUNC]:trans_bind_parm_cons\n");
    char body_str[LARGE_TEXT_SIZE];
    char node_str[LINE_LENGTH];
    //
    strcpy(body_str, lev1_body);
    char *last_str = body_str;
    char *last_body = lev1_body;
    //
    char (*lv2dap)[PARAM_LENGTH];
    int node_type;
    while (last_str && '\0' != last_str[0x00]) {
        // OSEVPF("-------- last_str:|%s|\n", last_str);
        last_str = split_toke(node_str, &node_type, last_str);
        // OSEVPF("node_type:%d node_str:|%s|\n", node_type, node_str);
        if (!node_type) {
            lv2dap = lv2p_prop;
            for (; '\0' != (*lv2dap)[0x00]; ++lv2dap) {
                if (!strcmp(node_str, lv2dap[0x00])) {
                    // OSEVPF("node_str:|%s|\n", node_str);
                    char *last_nod = lscpy(node_str, "this->");
                    lscpy(last_nod, lv2dap[0x00]);
                    // OSEVPF("node_str:|%s| lv2dap:|%s|\n", node_str, lv2dap[0x00]);
                    break;
                }
            }
        }
        last_body = lscpy(last_body, node_str);
    }
    //
    return 0x00;
}

//

static int trans_body_decla(char *lev1_body) {
    // OSEVPF("[FUNC]:trans_body_decla, lev1_body:|%s|\n", lev1_body);
    char body_cont[LARGE_TEXT_SIZE];
    char node_cont[LINE_LENGTH];
    char line_cont[LINE_LENGTH];
    //
    strcpy(body_cont, lev1_body);
    char *last_str = body_cont;
    char *last_body = lev1_body;
    //
    MK_ZERO(line_cont);
    while ('\0' != last_str[0x00]) {
        last_str = node_line(node_cont, last_str);
        // OSEVPF("node_cont:|%s|\n", node_cont);
        if (check_decla(node_cont)) {
            conv_decla(line_cont, node_cont);
            // OSEVPF("line_cont:|%s|\n", line_cont);
            last_body = lscpy(last_body, line_cont);
            MK_ZERO(line_cont);
        } else last_body = lscpy(last_body, node_cont);
    }
    // OSEVPF("end, trans_body_decla\n");
    return 0x00;
}

//

static inline int trans_head_norm(char *line_oivk, char *lv2pn, char *lev1n, char *fmtsop) {
    // OSEVPF("lv2pn:|%s|\n", lv2pn);
    filli_normal_pmoik(line_oivk, lv2pn, lev1n, fmtsop);
    // OSEVPF("line_oivk:|%s|\n", line_oivk);
    return 0x00;
}

static inline int tran_head_cons(char *line_oivk, char *lv2pn, char *lev1n, char *fmtsop) {
    // OSEVPF("lv2pn:|%s|\n", lv2pn);
    filli_constr_pmoik(line_oivk, lv2pn, lev1n, fmtsop);
    // OSEVPF("line_oivk:|%s|\n", line_oivk);
    return 0x00;
}

static int trans_body_norm(char *lev1_body, char (*form_bind)[PARAM_LENGTH], char (*actu_bind)[PARAM_LENGTH], char (*form_oivk)[PARAM_LENGTH], char *oivk_retyp) {
    // OSEVPF("[FUNC]:trans_body_norm\n");
    // OSEVPF("lev1_body:|%s|\n", lev1_body);
    trans_bind_parm_norm(lev1_body, form_bind, actu_bind);
    tran_oivk_parm(lev1_body, form_oivk);
    int oivk_valu;
    KV_STIN_EQUA(oivk_valu, retyp_calle_dict, oivk_retyp);
    tran_oivk_reval(lev1_body, oivk_valu);
    trans_body_decla(lev1_body);
    // OSEVPF("[FUNC]:trans_body_norm, lev1_body:|%s|\n", lev1_body);
    return 0x00;
}

static int trans_body_cons(char *lev1_body, char (*lv2p_prop)[PARAM_LENGTH], char (*form_oivk)[PARAM_LENGTH]) {
    // OSEVPF("lev1_body:|%s|\n", lev1_body);
    trans_bind_parm_cons(lev1_body, lv2p_prop);
    tran_oivk_parm(lev1_body, form_oivk);
    trans_body_decla(lev1_body);
    // OSEVPF("lev1_body:|%s|\n", lev1_body);
    return 0x00;
}

//

#define INIT_PARSE_METHO(METHO) \
    MK_ZERO(METHO.lv2pn); MK_ZERO(METHO.lev1n); \
    MK_ZERO(METHO.oivk_retyp); MK_ZERO(METHO.line_oivk); \
    MK_ZERO(METHO.oivk_fmtsp); MK_ZERO(METHO.ibind); \
    MK_ZERO(METHO.lev1_body);

static char *trans_metho_norma(char *clang_str, char *lev1_cont, char *lv2_dec) {
    // OSEVPF("[FUNC]:trans_metho_norma\n");
    conve_metho metho;
    INIT_PARSE_METHO(metho)
    if (parse_meth_data(&metho, lev1_cont))
        return NULL;
    char actu_head[LVON_LENGTH];
    if (split_class_actu(actu_head, lv2_dec, metho.lev1n))
        return NULL;
    //
    char form_bind[PARAM_COUNT][PARAM_LENGTH];
    char actu_bind[PARAM_COUNT][PARAM_LENGTH];
    if (split_meth_head(form_bind, metho.ibind))
        return NULL;
    if (split_class_meth(actu_bind, actu_head))
        return NULL;
    char form_oivk[PARAM_COUNT][PARAM_LENGTH];
    if (split_meth_oivk(form_oivk, metho.line_oivk))
        return NULL;
    //
    if (trans_head_norm(metho.line_oivk, metho.lv2pn, metho.lev1n, metho.oivk_fmtsp))
        return NULL;
    if (trans_body_norm(metho.lev1_body, form_bind, actu_bind, form_oivk, metho.oivk_retyp))
        return NULL;
    // OSEVPF("end, trans_body_norm\n");
    // OSEVPF("end, trans_metho_norma\n");
    return filli_metho_function(clang_str, &metho);
}

static char *trans_metho_const(char *clang_str, char *lev1_cont, char *lv2_dec) {
    conve_metho metho;
    INIT_PARSE_METHO(metho)
    if (parse_meth_data(&metho, lev1_cont))
        return NULL;
    //
    char lv2p_prop[LVTNOD_COUNT][PARAM_LENGTH];
    if (split_class_prope(lv2p_prop, lv2_dec))
        return NULL;
    conv_lv2p_cons(lv2p_prop);
    char form_oivk[PARAM_COUNT][PARAM_LENGTH];
    if (split_meth_oivk(form_oivk, metho.line_oivk))
        return NULL;
    //
    if (tran_head_cons(metho.line_oivk, metho.lv2pn, metho.lev1n, metho.oivk_fmtsp))
        return NULL;
    if (trans_body_cons(metho.lev1_body, lv2p_prop, form_oivk))
        return NULL;
    //
    return filli_const_function(clang_str, &metho);
}

//

static char *trans_ointe_parse(char *clang_str, char *lev1_cont) {
    conve_metho metho;
    INIT_PARSE_METHO(metho)
            //
    if (parse_meth_data(&metho, lev1_cont))
        return NULL;
    char oivk_data[PARAM_COUNT][PARAM_LENGTH];
    if (conv_oinvk_data(oivk_data, metho.line_oivk))
        return NULL;
    //
    clang_str = filli_include_head(clang_str);
    clang_str = filli_oinvk_struct(clang_str, &metho, oivk_data);
    return clang_str;
}

//

static char *trans_lv2p_prop(char *clang_str, char *lv2_dec) {
    char lv2pn[LVTN_LENGTH];
    char lv2p_prop[LVTNOD_COUNT][PARAM_LENGTH];
    // OSEVPF("lv2_dec:|%s|\n", lv2_dec);
    split_class_name_prope(lv2pn, lv2p_prop, lv2_dec);
    conv_clas_decl(lv2p_prop);
    // OSEVPF("lv2pn:|%s|\n", lv2pn);
    return filli_lv2po_struct(clang_str, lv2pn, lv2p_prop);
}

//

int metho_clang_ite(char *clang_cont, char *lev1_cont, char *lv2_dec, int norma_const) {
    OSEVPF("[FUNC]:metho_clang_ite lev1_cont:|%s|\n", lev1_cont);
    OSEVPF("lv2_dec:|%s|\n", lv2_dec);
    if (valid_metho_legal(lev1_cont, lv2_dec, norma_const))
        return -1;
    OSEVPF("PASSED, valid_metho_legal\n");
    clang_cont = trans_ointe_parse(clang_cont, lev1_cont);
    if (!clang_cont) return -1;
    OSEVPF("1a.\n");
    clang_cont = trans_lv2p_prop(clang_cont, lv2_dec);
    if (!clang_cont) return -1;
    OSEVPF("1b.\n");
    // -1:error 0x00:constructor 0x01:normal
    if (norma_const) {
        OSEVPF("1c.\n");
        clang_cont = trans_metho_norma(clang_cont, lev1_cont, lv2_dec);
        if (!clang_cont) return -1;
    } else {
        OSEVPF("1d.\n");
        clang_cont = trans_metho_const(clang_cont, lev1_cont, lv2_dec);
        if (!clang_cont) return -1;
    }
    OSEVPF("end, metho_clang_ite\n");
    OSEVPF("clang_cont:|%s|\n", clang_cont);
    return 0x00;
}

//

static char *itran_ointe_parse(char *clang_str, char *lev1_cont, lev1id *lev1i) {
    conve_metho metho;
    INIT_PARSE_METHO(metho)
            //
    if (parse_meth_data(&metho, lev1_cont))
        return NULL;
    char oivk_data[PARAM_COUNT][PARAM_LENGTH];
    if (conv_oinvk_data(oivk_data, metho.line_oivk))
        return NULL;
    //
    clang_str = filli_include_head(clang_str);
    clang_str = filli_oinvk_istruc(clang_str, &metho, oivk_data, lev1i->crea_lv2pn);
    return clang_str;
}

static char *itran_clas_data(char *clang_str, char *lv2_dec) {
    // OSEVPF("[FUNC]:itran_clas_data\n");
    char lv2pn[LVTN_LENGTH];
    char lv2p_prop[LVTNOD_COUNT][PARAM_LENGTH];
    // OSEVPF("lv2_dec:|%s|\n", lv2_dec);
    split_class_name_prope(lv2pn, lv2p_prop, lv2_dec);
    conv_clas_decl(lv2p_prop);
    // OSEVPF("lv2pn:|%s|\n", lv2pn);
    // OSEVPF("clang_str:|%s|\n", clang_str);
    // OSEVPF("[FUNC]:itran_clas_data END.\n");
    return filli_lv2po_struct(clang_str, lv2pn, lv2p_prop);
}

static char *itran_metho_bindi(char *clang_str, char *lev1_cont, char *lv2_dec, lev1id *lev1i) {
    // OSEVPF("itran_metho_bindi\n");
    conve_metho metho;
    INIT_PARSE_METHO(metho)
    if (parse_meth_data(&metho, lev1_cont))
        return NULL;
    char actu_head[LVON_LENGTH];
    if (split_class_actu(actu_head, lv2_dec, lev1i->inhe_lev1i))
        return NULL;
    // OSEVPF("itran_metho_bindi\n");
    //
    char form_bind[PARAM_COUNT][PARAM_LENGTH];
    char actu_bind[PARAM_COUNT][PARAM_LENGTH];
    if (split_meth_head(form_bind, metho.ibind))
        return NULL;
    if (split_class_meth(actu_bind, actu_head))
        return NULL;
    char form_oivk[PARAM_COUNT][PARAM_LENGTH];
    if (split_meth_oivk(form_oivk, metho.line_oivk))
        return NULL;
    //
    if (trans_head_norm(metho.line_oivk, lev1i->crea_lv2pn, metho.lev1n, metho.oivk_fmtsp))
        return NULL;
    if (trans_body_norm(metho.lev1_body, form_bind, actu_bind, form_oivk, metho.oivk_retyp))
        return NULL;
    //
    return filli_metho_ifunctio(clang_str, &metho, lev1i->crea_lv2pn);
}

int imeth_clang_ite(char *clang_cont, char *lev1_cont, char *lv2_dec, lev1id *lev1i) {
    // OSEVPF("[FUNC]:imeth_clang_ite, lev1_cont:|%s|\n", lev1_cont);
    // OSEVPF("lv2_dec:|%s|\n", lv2_dec);
    if (valid_metho_legal(lev1_cont, lv2_dec, 0x00))
        return -1;
    // OSEVPF("PASSED, valid_metho_legal\n");
    clang_cont = itran_ointe_parse(clang_cont, lev1_cont, lev1i);
    if (!clang_cont) return -1;
    clang_cont = itran_clas_data(clang_cont, lv2_dec);
    if (!clang_cont) return -1;
    clang_cont = itran_metho_bindi(clang_cont, lev1_cont, lv2_dec, lev1i);
    if (!clang_cont) return -1;
    // OSEVPF("3 clang_cont:|%s|\n", clang_cont);
    return 0x00;
}

//

static char *itran_metho_whole(char *clang_str, char *lev1_cont, char *lv2_dec, lev1id *lev1i) {
    OSEVPF("itran_metho_whole\n");
    conve_metho metho;
    INIT_PARSE_METHO(metho)
    if (parse_meth_data(&metho, lev1_cont))
        return NULL;
    char actu_head[LVON_LENGTH];
    if (split_class_actu(actu_head, lv2_dec, metho.lev1n))
        return NULL;
    OSEVPF("itran_metho_whole\n");
    //
    char form_bind[PARAM_COUNT][PARAM_LENGTH];
    char actu_bind[PARAM_COUNT][PARAM_LENGTH];
    if (split_meth_head(form_bind, metho.ibind))
        return NULL;
    if (split_class_meth(actu_bind, actu_head))
        return NULL;
    char form_oivk[PARAM_COUNT][PARAM_LENGTH];
    if (split_meth_oivk(form_oivk, metho.line_oivk))
        return NULL;
    //
    if (trans_head_norm(metho.line_oivk, lev1i->crea_lv2pn, metho.lev1n, metho.oivk_fmtsp))
        return NULL;
    if (trans_body_norm(metho.lev1_body, form_bind, actu_bind, form_oivk, metho.oivk_retyp))
        return NULL;
    //
    return filli_metho_ifunctio(clang_str, &metho, lev1i->crea_lv2pn);
}

//

static char *itran_lv2p_prop(char *clang_str, char *lv2_dec, char *lv2p_decl) {
    // OSEVPF("[FUNC]:itran_lv2p_prop\n");
    char lv2pn[LVTN_LENGTH];
    char lv2p_prop[LVTNOD_COUNT][PARAM_LENGTH];
    // OSEVPF("lv2p_decl_t:|%s|\n", lv2p_decl_t);
    split_lv2pn(lv2pn, lv2_dec);
    split_class_prope(lv2p_prop, lv2p_decl);
    conv_clas_decl(lv2p_prop);
    // OSEVPF("lv2pn:|%s|\n", lv2pn);
    return filli_lv2po_struct(clang_str, lv2pn, lv2p_prop);
}

int ilev1_clang_ite(char *clang_cont, char *lv2_dec, char *lev1_cont, char *lv2p_decl, lev1id *lev1i) {
    OSEVPF("[FUNC]:ilev1_clang_ite, lev1_cont:|%s|\n", lev1_cont);
    // OSEVPF("lv2_dec:|%s|\n", lv2_dec);
    // OSEVPF("lv2p_decl_t:|%s|\n", lv2p_decl_t);
    clang_cont = itran_ointe_parse(clang_cont, lev1_cont, lev1i);
    if (!clang_cont) return -1;
    // OSEVPF("1 clang_cont:|%s|\n", clang_cont);
    clang_cont = itran_lv2p_prop(clang_cont, lv2_dec, lv2p_decl);
    if (!clang_cont) return -1;
    // OSEVPF("2 clang_cont:|%s|\n", clang_cont);
    clang_cont = itran_metho_whole(clang_cont, lev1_cont, lv2p_decl, lev1i);
    if (!clang_cont) return -1;
    OSEVPF("3 clang_cont:|%s|\n", clang_cont);
    return 0x00;
}

//

int chk_ibind_ite(lev1_decl_t *lev1d, lev1_meta *lev1m) {
    lev1_decl_t *lv1d = find_lev1d_iden(lev1d, lev1m->lv2pn, lev1m->lev1n);
    if (!lv1d) return -1;
    //
    char inne_fmtsp[FMTST_COUNT_ZTAI];
    if (conv_ibind_decla(inne_fmtsp, lev1m->decla))
        return -1;
    OSEVPF("lv1d->innep.inne_fmtsp:|%s| inne_fmtsp:|%s|\n", lv1d->innep.inne_fmtsp, inne_fmtsp);
    return strcmp(inne_fmtsp, lv1d->innep.inne_fmtsp);
}













