
#include "../kstri_utili.h"
#include "cstri_utili.h"
#include "conve_utili.h"
#include "filli_clang.h"
#include "lv2p_list.h"
#include "lev1_utili.h"
#include "seri_leng.h"

#include "conver.h"
#include "../../debug_funct_sh.h"

//
#define INIT_PARSE_METHO(METHO) \
    MK_ZERO(METHO.lv2pn); MK_ZERO(METHO.lev1n); \
    MK_ZERO(METHO.oivk_retyp_pm); MK_ZERO(METHO.line_oivk); \
    MK_ZERO(METHO.oivk_fmtsp_pm); MK_ZERO(METHO.ibind); \
    MK_ZERO(METHO.lev1_body);

//

static inline int conve_head_norm(char *line_oivk) {
    char oivk_data[PARAM_COUNT][PARAM_LENGTH];
    if (conv_oinvk_data(oivk_data, line_oivk))
        return -1;
    filli_ointe_comple(line_oivk, oivk_data);
    // CLIEPF("line_oivk:|%s|\n", line_oivk);
    return 0x00;
}

//

static int parse_meth_decla(parse_metho *metho, char *lev1_cont) {
    lev1_cont = split_metho_conte(metho->lv2pn, metho->lev1n, lev1_cont);
    if (!lev1_cont) return -1;
    // CLIEPF("clasn:|%s|\n", metho->lv2pn);
    // CLIEPF("meth_name:|%s|\n", metho->lev1n);
    lev1_cont = split_head(metho->oivk_retyp_pm, metho->line_oivk, metho->ibind, lev1_cont);
    if (!lev1_cont) return -1;
    // CLIEPF("oivk_type:|%s|\n", metho->oivk_type);
    // CLIEPF("line_oivk:|%s|\n", metho->line_oivk);
    // CLIEPF("ibind:|%s|\n", metho->ibind);
    return 0x00;
}

//

static char *conv_class_meth(char *clang_str, char *meth_decl, int norma_const) {
    parse_metho metho;
    INIT_PARSE_METHO(metho)
            // CLIEPF("meth_decl:|%s|\n", meth_decl);
    if (parse_meth_decla(&metho, meth_decl))
        return NULL;
    if (conve_head_norm(metho.line_oivk))
        return NULL;
    // -1:error 0x00:constructor 0x01:normal
    if (norma_const)
        clang_str = filli_metho_decla(clang_str, &metho);
    else clang_str = filli_const_decla(clang_str, &metho);
    //
    return clang_str;
}

//

static char *conv_elv2p_conte(char *clang_str, class_meta *clsmt, lv2p_expa_t *lv2expt) {
    // CLIEPF("[FUNC]:conv_elv2p_conte\n");
    clang_str = filli_elv2p_decla(clang_str, lv2expt->lv2nod);
    if (!clang_str) return NULL;
    clang_str = filli_lcon_decla(clang_str, clsmt->lv2pn, lv2expt->lv2nod);
    //
    clang_str = FILLI_METHO_SECTI(clang_str);
    // -1:error 0x00:constructor 0x01:normal
    int norma_const;
    method *menod = clsmt->meth_list;
    for (; menod; menod = menod->next) {
        norma_const = chk_norma_const(clsmt->lv2p_decl, menod->lev1n);
        if (-1 == norma_const) return NULL;
        clang_str = conv_class_meth(clang_str, menod->lev1_cont, norma_const);
        if (!clang_str) return NULL;
    }
    //
    return clang_str;
}

char *conve_lv2p_conte(char *clang_cont, class_meta *clsmt, lv2p_expa_t *lv2expt) {
    // CLIEPF("[FUNC]:conve_lv2p_conte\n");
    clang_cont = FILLI_ELVTP_HEAD(clang_cont, clsmt->lv2pn);
    //
    clang_cont = filli_lv2p_based(clang_cont, clsmt, lv2expt);
    if (!clang_cont) return NULL;
    clang_cont = conv_elv2p_conte(clang_cont, clsmt, lv2expt);
    if (!clang_cont) return NULL;
    //
    clang_cont = FILLI_ELVTP_TAIL(clang_cont);
    // CLIEPF("end conve_lv2p_conte:\n%s\n", clang_cont);
    return clang_cont;
}

//

static int parse_meth_data(parse_metho *metho, char *lev1_cont) {
    lev1_cont = split_metho_conte(metho->lv2pn, metho->lev1n, lev1_cont);
    if (!lev1_cont) return -1;
    // OSEVPF("lv2pn:|%s|\n", metho->lv2pn);
    // OSEVPF("meth_name:|%s|\n", metho->lev1n);
    lev1_cont = split_head(metho->oivk_retyp_pm, metho->line_oivk, metho->ibind, lev1_cont);
    if (!lev1_cont) return -1;
    metho->retyp_valu = const_retype_value(metho->oivk_retyp_pm);
    if (conv_oinvk_type(metho->oivk_fmtsp_pm, metho->line_oivk))
        return -1;
    // OSEVPF("oivk_type:|%s|\n", metho->oivk_type);
    // OSEVPF("line_oivk:|%s|\n", metho->line_oivk);
    // OSEVPF("ibind:|%s|\n", metho->ibind);
    split_body(metho->lev1_body, lev1_cont);
    // OSEVPF("lev1_body:|%s|\n", metho->lev1_body);
    return 0x00;
}

//

static int conve_bind_parm_cons(char *lev1_body, char (*lv2p_prop)[PARAM_LENGTH]) {
    char body_str[LARGE_TEXT_SIZE];
    char node_str[LINE_LENGTH];
    // CLIEPF("conve_bind_parm_cons\n");
    char *last_str = body_str;
    strcpy(body_str, lev1_body);
    //
    char (*clasp)[PARAM_LENGTH];
    int node_type;
    while (last_str && '\0' != last_str[0x00]) {
        // CLIEPF("-------- last_str:|%s|\n", last_str);
        last_str = split_toke(node_str, &node_type, last_str);
        // CLIEPF("node_type:%d node_str:|%s|\n", node_type, node_str);
        if (!node_type) {
            clasp = lv2p_prop;
            for (; '\0' != (*clasp)[0x00]; ++clasp) {
                if (!strcmp(node_str, clasp[0x00])) {
                    // CLIEPF("node_str:|%s|\n", node_str);
                    char *last_nod = lscpy(node_str, "this->");
                    lscpy(last_nod, clasp[0x00]);
                    // CLIEPF("node_str:|%s| clasp[inde]:|%s|\n", node_str, clasp[inde]);
                    break;
                }
            }
        }
        lev1_body = lscpy(lev1_body, node_str);
    }
    //
    return 0x00;
}

static int conve_body_decla(char *lev1_body) {
    char body_cont[LARGE_TEXT_SIZE];
    char node_cont[LINE_LENGTH];
    char line_cont[LINE_LENGTH];
    // CLIEPF("conve_body_decla\n");
    char *last_str = body_cont;
    strcpy(body_cont, lev1_body);
    //
    MK_ZERO(line_cont);
    while ('\0' != last_str[0x00]) {
        last_str = node_line(node_cont, last_str);
        // CLIEPF("node_cont:|%s|\n", node_cont);
        if (check_decla(node_cont)) {
            conv_decla(line_cont, node_cont);
            // CLIEPF("line_cont:|%s|\n", line_cont);
            lev1_body = lscpy(lev1_body, line_cont);
            MK_ZERO(line_cont);
        } else lev1_body = lscpy(lev1_body, node_cont);
    }
    //
    return 0x00;
}

//

static int conve_body_cons(char *lev1_body, char (*lv2p_prop)[PARAM_LENGTH]) {
    // CLIEPF("lev1_body:|%s|\n", lev1_body);
    conve_bind_parm_cons(lev1_body, lv2p_prop);
    conve_body_decla(lev1_body);
    // CLIEPF("lev1_body:|%s|\n", lev1_body);
    return 0x00;
}

//

static char *conve_metho_const(char *clang_str, char *lev1_cont, char *lv2_dec) {
    parse_metho metho;
    INIT_PARSE_METHO(metho)
    if (parse_meth_data(&metho, lev1_cont))
        return NULL;
    //
    char lv2p_prop[LVTNOD_COUNT][PARAM_LENGTH];
    if (split_class_prope(lv2p_prop, lv2_dec))
        return NULL;
    conv_lv2p_cons(lv2p_prop);
    //
    if (conve_head_norm(metho.line_oivk))
        return NULL;
    if (conve_body_cons(metho.lev1_body, lv2p_prop))
        return NULL;
    //
    return filli_const_defin(clang_str, &metho);
}

//

static int conve_bind_parm_norm(char *lev1_body, char (*form_bind)[PARAM_LENGTH], char (*actu_bind)[PARAM_LENGTH]) {
    char body_str[LARGE_TEXT_SIZE];
    char node_str[LINE_LENGTH];
    // CLIEPF("conve_bind_parm_norm\n");
    char *last_str = body_str;
    strcpy(body_str, lev1_body);
    //
    char (*formp)[PARAM_LENGTH], (*actup)[PARAM_LENGTH];
    int node_type;
    while (last_str && '\0' != last_str[0x00]) {
        // CLIEPF("-------- last_str:|%s|\n", last_str);
        last_str = split_toke(node_str, &node_type, last_str);
        // CLIEPF("node_type:%d node_str:|%s|\n", node_type, node_str);
        if (!node_type) {
            formp = form_bind;
            actup = actu_bind;
            for (; '\0' != (*formp)[0x00]; ++formp, ++actup) {
                if (!strcmp(node_str, formp[0x00])) {
                    // CLIEPF("node_str:|%s|\n", node_str);
                    char *last_nod = lscpy(node_str, "this->");
                    lscpy(last_nod, actup[0x00]);
                    // CLIEPF("node_str:|%s| actu_bind[inde]:|%s|\n", node_str, actu_bind[inde]);
                    break;
                }
            }
        }
        lev1_body = lscpy(lev1_body, node_str);
    }
    //
    return 0x00;
}

//

static int conve_body_norm(char *lev1_body, char form_bind[PARAM_COUNT][PARAM_LENGTH], char actu_bind[PARAM_COUNT][PARAM_LENGTH]) {
    // CLIEPF("lev1_body:|%s|\n", lev1_body);
    conve_bind_parm_norm(lev1_body, form_bind, actu_bind);
    conve_body_decla(lev1_body);
    // CLIEPF("lev1_body:|%s|\n", lev1_body);
    return 0x00;
}

//

static char *conve_metho_norma(char *clang_str, char *lev1_cont, char *lv2_dec) {
    // OSEVPF("[FUNC]:conve_metho_norma\n");
    parse_metho metho;
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
    //
    if (conve_head_norm(metho.line_oivk))
        return NULL;
    if (conve_body_norm(metho.lev1_body, form_bind, actu_bind))
        return NULL;
    // OSEVPF("end, conve_body_norm\n");
    // OSEVPF("end, conve_metho_norma\n");
    return filli_metho_defin(clang_str, &metho);
}

//

static char *conv_meth_data(char *clang_cont, char *lev1_cont, char *lv2_dec, int norma_const) {
    // OSEVPF("[FUNC]:conv_meth_data lev1_cont:|%s|\n", lev1_cont);
    // OSEVPF("lv2_dec:|%s|\n", lv2_dec);
    if (valid_metho_legal(lev1_cont, lv2_dec, norma_const))
        return NULL;
    // OSEVPF("PASSED, valid_metho_legal\n");
    char *last_str;
    // -1:error 0x00:constructor 0x01:normal
    if (norma_const) {
        last_str = conve_metho_norma(clang_cont, lev1_cont, lv2_dec);
        if (!last_str) return NULL;
    } else {
        last_str = conve_metho_const(clang_cont, lev1_cont, lv2_dec);
        if (!last_str) return NULL;
    }
    // OSEVPF("end, metho_clang_ite\n");
    // OSEVPF("clang_cont:|%s|\n", clang_cont);
    return last_str;
}

//

int conve_lev1_conte(char *clang_cont, class_meta *clsmt, lv2p_expa_t *lv2expt, char *basen) {
    clang_cont = filli_stati_const(clang_cont, clsmt, lv2expt->lv2nod);
    if (!clang_cont) return -1;
    // serialize deserialize
    clang_cont = filli_meta_seria(clang_cont, clsmt->lv2pn, lv2expt->lv2nod);
    if (!clang_cont) return -1;
    clang_cont = filli_meta_deseri(clang_cont, clsmt->lv2pn, lv2expt->lv2nod);
    if (!clang_cont) return -1;
    clang_cont = filli_lcon_defin(clang_cont, clsmt->lv2pn, lv2expt->lv2nod);
    if (!clang_cont) return -1;
    // -1:error 0x00:constructor 0x01:normal
    int norma_const;
    method *menod = clsmt->meth_list;
    for (; menod; menod = menod->next) {
        norma_const = chk_norma_const(clsmt->lv2p_decl, menod->lev1n);
        if (-1 == norma_const) return -1;
        clang_cont = conv_meth_data(clang_cont, menod->lev1_cont, clsmt->lv2p_decl, norma_const);
        if (!clang_cont) return -1;
    }
    //
    return 0x00;
}

