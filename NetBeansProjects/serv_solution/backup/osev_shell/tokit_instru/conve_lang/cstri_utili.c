#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "../common/ccomm_types.h"
#include "cstri_utili.h"
#include "../../debug_funct_sh.h"

//
static const char *vari_type_tab[] = {
    "int",
    "short",
    "long",
    "char",
    "float",
    "double",
    NULL
};

//

static char *couple_bracket(char *stri) {
    if (!stri || '(' != stri[0x00]) return NULL;
    char *bktok = stri + 0x01;
    //
    for (; '\0' != bktok[0x00]; ++bktok) {
        if ('(' == bktok[0x00]) {
            for (++bktok; isdigit(bktok[0x00]); ++bktok);
            if (')' != bktok[0x00]) return NULL;
        } else if (')' == bktok[0x00]) break;
    }
    if ('\0' == bktok[0x00]) return NULL;
    //
    return bktok;
}

//

static char *split_lv2pn(char *lv2pn, char *lv2_dec) {
    char *toksp = pass_blank(lv2_dec);
    if (!toksp) return NULL;
    char *tokep = strpbrk(toksp, " <");
    if (!tokep) return NULL;
    strzcpy(lv2pn, toksp, tokep - toksp);
    //
    return tokep;
}

//

static char *bound_node(char *conte, char *data) {
    char *toksp = pass_blank(data);
    if (!toksp) return NULL;
    if ('<' == toksp[0x00]) toksp = pass_blank(toksp + 0x01);
    for (; '[' == toksp[0x00]; toksp = pass_blank(toksp + 0x01)) {
        for (; ']' != toksp[0x00]; ++toksp);
        for (; ',' != toksp[0x00]; ++toksp);
    }
    //
    char *tokep = strpbrk(toksp, " (");
    if (!tokep) return NULL;
    strzcpy(conte, toksp, tokep - toksp);
    //
    tokep = strchr(tokep + 0x01, ')');
    if (!tokep) return NULL;
    tokep = strpbrk(tokep + 0x01, ",>");
    if (tokep) ++tokep;
    return tokep;
}

// -1:error 0x00:constructor 0x01:normal

int chk_norma_const(char *lv2_dec, char *lev1n) {
    char lv2pn[LVTN_LENGTH];
    char *detok = split_lv2pn(lv2pn, lv2_dec);
    if (!detok) return -1;
    if (!strcmp(lev1n, lv2pn)) return 0x00;
    // CLIEPF("cmt lv2_dec:|%s| lev1n:|%s|\n", lv2_dec, lev1n);
    char bound[LVON_LENGTH];
    while ((detok = bound_node(bound, detok))) {
        // CLIEPF("bound:|%s|\n", bound);
        if (!strcmp(lev1n, bound))
            return 0x01;
    }
    // CLIEPF("cmt not found:|%s|\n", lev1n);
    return -1;
}

//
/*
 <(void)int>
 <(x int)>
 <(void)int, (x int)>
 */

// -1:error 0x01:single 0x02:double
// inte_coun

static int inte_count(char **last_chrp, char *meth_inte, char *lev1_cont) {
    char *toksp = strchr(lev1_cont, '<');
    if (!toksp) return -1;
    char *tokep = strchr(toksp + 0x01, '>');
    if (!tokep) return -1;
    //
    strzcpy(meth_inte, toksp, tokep - toksp + 0x01);
    int inte_coun = 0x00;
    for (toksp = meth_inte; '\0' != toksp[0x00]; ++toksp) {
        if ('(' == toksp[0x00]) {
            toksp = couple_bracket(toksp);
            if (!toksp) break;
            inte_coun++;
        }
    }
    //
    if (last_chrp) *last_chrp = tokep + 0x01;
    return inte_coun;
}

// -1:error 0x00:inn_out 0x01:inn 0x02:out

static int iointe_type_ensi(char *meth_inte) {
    char *toksp = strchr(meth_inte, '(');
    if (!toksp) return -1;
    char *tokep = couple_bracket(toksp);
    if (!tokep) return -1;
    //
    int iotyp = 0x01;
    for (++tokep; '\0' != tokep[0x00]; ++tokep) {
        if (isalpha(tokep[0x00])) {
            iotyp = 0x02;
            break;
        }
    }
    //
    return iotyp;
}

//

static int split_cotype_sio(char *const_type, char *meth_inte, int iotyp) {
    char *toksp, *tokep;
    if (0x02 == iotyp) {
        toksp = strrchr(meth_inte, ')');
        if (!toksp) return -1;
        for (++toksp; ' ' == toksp[0x00]; ++toksp);
        tokep = strchr(toksp + 0x01, '>');
        if (!tokep) return -1;
        for (; ' ' == tokep[-1]; --tokep);
        strzcpy(const_type, toksp, tokep - toksp);
    }
    //
    return 0x00;
}

// -1:error 

int split_chead(char *const_type, char *meth_decl) {
    // CLIEPF("ph lev1_cont:|%s|\n", lev1_cont);
    char meth_inte[LVON_LENGTH];
    if (0x01 != inte_count(NULL, meth_inte, meth_decl))
        return -1;
    // -1:error 0x00:inn_out 0x01:inn 0x02:out
    int iotyp = iointe_type_ensi(meth_inte);
    if (0x02 != iotyp) return -1;
    split_cotype_sio(const_type, meth_inte, iotyp);
    //
    return 0x00;
}

//

char *split_metho_ident(char *lev1n, char *ident) {
    char *toksp = pass_blank(ident);
    if (!toksp) return NULL;
    char *tokep = strchr(toksp + 0x01, ':');
    if (!tokep) return NULL;
    //
    toksp = strpbrk(tokep + 0x01, " <");
    if (!toksp) return NULL;
    strzcpy(lev1n, tokep + 0x01, toksp - tokep - 0x01);
    //
    return toksp;
}

//

static int split_iointe_sii(char *ibind, char *meth_inte, int iotyp) {
    char *toksp, *tokep;
    if (0x01 == iotyp) {
        toksp = strchr(meth_inte, '(');
        if (!toksp) return -1;
        tokep = strchr(toksp + 0x01, ')');
        if (!tokep) return -1;
        strzcpy(ibind, toksp, tokep - toksp + 0x01);
    }
    //
    return 0x00;
}

// -1:error 0x00:inn_out 0x01:out_inn

static int iointe_type_do(char *meth_inte) {
    char *toksp = meth_inte;
    int check_times = 0x02;
    int ointe_coun = 0x00;
    int iotyp = 0x00;
    //
    while (check_times--) {
        toksp = strchr(toksp, '(');
        if (!toksp) return -1;
        char *tokep = couple_bracket(toksp);
        if (!tokep) return -1;
        //
        char *toknp = ++tokep;
        for (; '\0' != toknp[0x00]; ++toknp) {
            if (',' == toknp[0x00]) {
                break;
            } else if (isalpha(toknp[0x00])) {
                iotyp = check_times;
                ointe_coun++;
                break;
            }
        }
        //
        toksp = strchr(toknp, ',');
    }
    //
    return 0x01 == ointe_coun ? iotyp : -1;
}

static int split_iointe_doi(char *ibind, char *meth_inte, int iotyp) {
    char *tokep, *toksp = meth_inte;
    if (iotyp) {
        toksp = strchr(toksp, '(');
        if (!toksp) return -1;
        tokep = strchr(toksp + 0x01, ')');
        if (!tokep) return -1;
        toksp = strchr(tokep + 0x01, ',');
        if (!toksp) return -1;
    }
    toksp = strchr(toksp, '(');
    if (!toksp) return -1;
    tokep = strchr(toksp + 0x01, ')');
    if (!tokep) return -1;
    strzcpy(ibind, toksp, tokep - toksp + 0x01);
    //
    return 0x00;
}

// -1:error 0x00:inn_out 0x01:inn 0x02:out

int split_ibind_head(char *ibind, char *meth_decl) {
    // CLIEPF("phe lev1_cont:|%s|\n", lev1_cont);
    char meth_inte[LVON_LENGTH];
    int iotyp = -1;
    // CLIEPF("phe inte_coun:%d\n", inte_coun);
    switch (inte_count(NULL, meth_inte, meth_decl)) {
        case 0x01:
            iotyp = iointe_type_ensi(meth_inte);
            // CLIEPF("its iotyp:%d\n", iotyp);
            if (-1 == iotyp || 0x02 == iotyp) break;
            split_iointe_sii(ibind, meth_inte, iotyp);
            break;
        case 0x02:
            iotyp = iointe_type_do(meth_inte);
            // CLIEPF("itd iotyp:%d\n", iotyp);
            if (-1 == iotyp) break;
            split_iointe_doi(ibind, meth_inte, iotyp);
            iotyp = 0x00;
            break;
        default:
            _LOG_WARN("default: inte_coun");
            return -1;
            break;
    }
    //
    return iotyp;
}

//

char *split_argu_node(char *conte, char *data) {
    char *toksp = strchr(data, '(');
    if (!toksp) return NULL;
    char *tokep = strchr(toksp + 0x01, ')');
    if (!tokep) return NULL;
    //
    strzcpy(conte, toksp + 0x01, tokep - toksp - 0x01);
    return ++tokep;
}

//

static inline int imeth_node(char *toksp, char *tokep) {
    for (--tokep; toksp <= tokep; --tokep) {
        if (' ' == toksp[0x00]) continue;
        if (':' == toksp[0x00]) return 0x01;
        break;
    }
    //
    return 0x00;
}

char *prod_prop_node(char *conte, char *attri, char *data) {
    // OSEVPF("prod_prop_node, data:|%s|\n", data);
    char *toksp, *tokep;
    //
    toksp = strchr(data, '[');
    if (!toksp) return NULL;
    tokep = strchr(toksp + 0x01, ']');
    if (!tokep) return NULL;
    strzcpy(conte, toksp + 0x01, tokep - toksp - 0x01);
    // OSEVPF("tokep:|%s|\n", tokep);
    PASS_TBLANK(toksp, tokep + 0x01)
    if (',' != toksp[0x00] && '>' != toksp[0x00]) {
        tokep = strpbrk(toksp, " ,");
        strzcpy(attri, toksp, tokep - toksp);
    } else MK_ZERO(attri);
    // OSEVPF("attri:|%s|\n", attri);
    return ++tokep;
}

char *prod_prop_item(char *conte, char *data) {
    char *toksp, *tokep;
    do {
        toksp = strchr(data, '[');
        if (!toksp) return NULL;
        tokep = strchr(toksp + 0x01, ']');
        if (!tokep) return NULL;
    } while (imeth_node(data, toksp));
    //
    strzcpy(conte, toksp + 0x01, tokep - toksp - 0x01);
    return ++tokep;
}

char *cprod_prop_node(char *conte, char *data) {
    char *toksp, *tokep;
    do {
        toksp = strchr(data, '[');
        if (!toksp) return NULL;
        tokep = strchr(toksp + 0x01, ']');
        if (!tokep) return NULL;
    } while (imeth_node(data, toksp));
    //
    strzcpy(conte, toksp + 0x01, tokep - toksp - 0x01);
    return ++tokep;
}

//

int split_class_actu(char *actu_head, char *lv2_dec, char *meth_name) {
    // CLIEPF("lv2_dec:|%s|\n", lv2_dec);
    // CLIEPF("meth_name:|%s|\n", meth_name);
    char *toksp = strstr(lv2_dec, meth_name);
    if (!toksp) return -1;
    toksp += strlen(meth_name);
    toksp = strchr(toksp, '(');
    if (!toksp) return -1;
    char *tokep = strchr(toksp, ')');
    if (!tokep) return -1;
    //
    strzcpy(actu_head, toksp, tokep - toksp + 0x01);
    // CLIEPF("actu_head:|%s|\n", actu_head);
    return 0x00;
}

//

static char *split_actual(char *actu_bind, char *pamvu) {
    char *tokep, *toksp = pamvu;
    for (; ',' == toksp[0x00]
            || ' ' == toksp[0x00]
            || '(' == toksp[0x00]; ++toksp);
    if ('\0' == toksp[0x00]) return NULL;
    tokep = strpbrk(toksp + 0x01, ", )");
    if (!tokep) return NULL;
    strzcpy(actu_bind, toksp, tokep - toksp);
    //
    return ++tokep;
}

//

int split_class_meth(char (*actu_bind)[PARAM_LENGTH], char *actu_head) {
    // CLIEPF("actu_head:|%s|\n", actu_head);
    unsigned int inde = 0x00;
    if ((actu_head = split_void(actu_head))) {
        for (; actu_head && ('\0' != actu_head[0x00]) && (PARAM_COUNT >= inde); ++inde, ++actu_bind) {
            // CLIEPF("actu_head:|%s|\n", actu_head);
            actu_head = split_actual(actu_bind[0x00], actu_head);
            // CLIEPF("actu_bind[inde]:|%s|\n", actu_bind[inde]);
        }
    }
    // CLIEPF("inde:%d\n", inde);
    MK_ZERO(actu_bind[0x00]);
    //
    return 0x00;
}

//
static osv_str_t PARM_VOID_TOK = osv_stri("void");

char *split_void(char *pamvu) {
    char *toksp = pamvu;
    for (; ',' == toksp[0x00]
            || ' ' == toksp[0x00]
            || '(' == toksp[0x00]; ++toksp);
    if ('\0' == toksp[0x00]) return NULL;
    if (!strncmp(PARM_VOID_TOK.data, toksp, PARM_VOID_TOK.slen))
        return NULL;
    //
    char *tokep = toksp;
    for (; ',' == tokep[0x00] || ' ' == tokep[0x00]; ++tokep) {
        if ('\0' == tokep[0x00] || ')' == tokep[0x00])
            return NULL;
        else if (isalnum(tokep[0x00])) break;
    }
    //
    return toksp;
}

//

char *split_oinvk_ext(char *oivk_data, char *pamvu) {
    // CLIEPF("ex pamvu:|%s|\n", pamvu);
    char *tokep, *toksp = pamvu;
    for (; ',' == toksp[0x00] || ' ' == toksp[0x00] || '(' == toksp[0x00] || ')' == toksp[0x00]; ++toksp) {
        if ('\0' == toksp[0x00]) return toksp;
    }
    tokep = strpbrk(toksp + 0x01, ",)");
    if (!tokep) return NULL;
    strzcpy(oivk_data, toksp, tokep - toksp);
    //
    toksp = strchr(toksp + 0x01, ' ');
    if (!toksp) return NULL;
    for (; ' ' == toksp[0x00]; ++toksp);
    tokep = strpbrk(toksp + 0x01, ", )");
    if (!tokep) return NULL;
    //
    return ++tokep;
}

//

char *split_metho_conte(OUT char *lv2pn, OUT char *lev1n, char *lev1_cont) {
    char *toksp = pass_blank(lev1_cont);
    if (!toksp) return NULL;
    char *tokep = strchr(toksp + 0x01, ':');
    if (!tokep) return NULL;
    strzcpy(lv2pn, toksp, tokep - toksp);
    //
    toksp = strpbrk(tokep + 0x01, " <");
    if (!toksp) return NULL;
    strzcpy(lev1n, tokep + 0x01, toksp - tokep - 0x01);
    //
    return toksp;
}

//

static int split_iointe_sin(char *oivk_type, char *line_oivk, char *ibind, char *meth_inte, int iotyp) {
    char *toksp, *tokep;
    CLIEPF("pis meth_inte:|%s|\n", meth_inte);
    // 0x01:inn 0x02:out
    if (0x01 == iotyp) {
        toksp = strchr(meth_inte, '(');
        if (!toksp) return -1;
        tokep = couple_bracket(toksp);
        if (!tokep) return -1;
        strzcpy(ibind, toksp, tokep - toksp + 0x01);
    } else if (0x02 == iotyp) {
        toksp = strchr(meth_inte, '(');
        if (!toksp) return -1;
        tokep = couple_bracket(toksp);
        if (!tokep) return -1;
        strzcpy(line_oivk, toksp, tokep - toksp + 0x01);
        //
        toksp = tokep + 0x01;
        for (; '\0' != toksp[0x00] && ' ' == toksp[0x00]; ++toksp);
        tokep = strpbrk(toksp, " ,>");
        if (!tokep) return -1;
        strzcpy(oivk_type, toksp, tokep - toksp);
    }
    //
    return 0x00;
}

static int parse_iointe_don(char *oivk_type, char *line_oivk, char *ibind, char *meth_inte, int iotyp) {
    char *tokep, *toksp;
    CLIEPF("[FUNC]:parse_iointe_don meth_inte:|%s|\n", meth_inte);
    // 0x00:inn_out 0x01:out_inn
    toksp = strchr(meth_inte, '(');
    if (!toksp) return -1;
    tokep = couple_bracket(toksp);
    if (!tokep) return -1;
    if (iotyp) {
        strzcpy(line_oivk, toksp, tokep - toksp + 0x01);
        //
        toksp = tokep + 0x01;
        for (; '\0' != toksp[0x00] && ' ' == toksp[0x00]; ++toksp);
        tokep = strpbrk(toksp, " ,");
        if (!tokep) return -1;
        strzcpy(oivk_type, toksp, tokep - toksp);
    } else {
        strzcpy(ibind, toksp, tokep - toksp + 0x01);
    }
    //
    toksp = strchr(toksp + 0x01, ',');
    if (!toksp) return -1;
    //
    toksp = strchr(toksp, '(');
    if (!toksp) return -1;
    tokep = couple_bracket(toksp);
    if (!tokep) return -1;
    if (iotyp) {
        strzcpy(ibind, toksp, tokep - toksp + 0x01);
    } else {
        strzcpy(line_oivk, toksp, tokep - toksp + 0x01);
        //
        toksp = tokep + 0x01;
        for (; '\0' != toksp[0x00] && ' ' == toksp[0x00]; ++toksp);
        tokep = strpbrk(toksp, " ,>");
        if (!tokep) return -1;
        strzcpy(oivk_type, toksp, tokep - toksp);
    }
    //
    return 0x00;
}

char *split_head(char *oivk_type, char *line_oivk, char *ibind, char *meth_decl) {
    // CLIEPF("ph lev1_cont:|%s|\n", lev1_cont);
    char meth_inte[LVON_LENGTH];
    int iotyp = -1;
    char *last_str = NULL;
    // CLIEPF("ph inte_coun:%d\n", inte_coun);
    switch (inte_count(&last_str, meth_inte, meth_decl)) {
        case 0x01:
            iotyp = iointe_type_ensi(meth_inte);
            // CLIEPF("its iotyp:%d\n", iotyp);
            if (-1 == iotyp) return NULL;
            if (split_iointe_sin(oivk_type, line_oivk, ibind, meth_inte, iotyp))
                return NULL;
            break;
        case 0x02:
            iotyp = iointe_type_do(meth_inte);
            // CLIEPF("itd iotyp:%d\n", iotyp);
            if (-1 == iotyp) return NULL;
            if (parse_iointe_don(oivk_type, line_oivk, ibind, meth_inte, iotyp))
                return NULL;
            break;
        default:
            _LOG_WARN("default: inte_coun");
            break;
    }
    //
    return last_str;
}

//

int split_class_prope(char (*lv2p_prop)[PARAM_LENGTH], char *lv2_dec) {
    // OSEVPF("[FUNC]:split_class_prope\n");
    char *toksp, *cotok;
    toksp = pass_clasn(lv2_dec);
    if (!toksp) return -1;
    //
    char node_cont[LVTNOD_LENGTH];
    char acce_cont[PARAM_LENGTH];
    unsigned int inde = 0x00;
    while ((toksp = prod_prop_node(node_cont, acce_cont, toksp))) {
        // OSEVPF("pcde node_cont:|%s|\n", node_cont);
        for (cotok = node_cont; cotok && (LVTNOD_COUNT > inde); ++inde, ++lv2p_prop) {
            cotok = split_prope(lv2p_prop[0x00], cotok);
            if (INVAL_POINT == cotok)
                return -1;
            // OSEVPF("pcde lv2p_prop[inde++]:|%s|\n", lv2p_prop[inde - 0x01]);
        }
    }
    MK_ZERO(lv2p_prop[0x00]);
    //
    return 0x00;
}

// trans-serve

int split_lv2p_prop(char *lv2pn, char (*lv2p_prop)[PARAM_LENGTH], char *lv2_dec) {
    char *detok, *toked;
    detok = split_lv2pn(lv2pn, lv2_dec);
    if (!detok) return -1;
    //
    char node_cont[LVTNOD_LENGTH];
    while ((detok = prod_prop_item(node_cont, detok))) {
        // CLIEPF("node_cont:|%s|\n", node_cont);
        for (toked = node_cont; toked; ++lv2p_prop) {
            toked = split_prope(lv2p_prop[0x00], toked);
            if (INVAL_POINT == toked)
                return -1;
            // CLIEPF("lv2p_prop[inde++]:|%s|\n", lv2p_prop[inde - 0x01]);
        }
    }
    MK_ZERO(lv2p_prop[0x00]);
    //
    return 0x00;
}

//

int split_class_name_prope(char *lv2pn, char (*lv2p_prop)[PARAM_LENGTH], char *lv2_dec) {
    char *toksp, *cotok;
    toksp = split_lv2pn(lv2pn, lv2_dec);
    if (!toksp) return -1;
    // OSEVPF("split_lv2p_prop, lv2pn:|%s|\n", lv2pn);
    //
    char node_cont[LVTNOD_LENGTH];
    char acce_cont[PARAM_LENGTH];
    unsigned int inde = 0x00;
    while ((toksp = prod_prop_node(node_cont, acce_cont, toksp))) {
        // OSEVPF("node_cont:|%s|\n", node_cont);
        for (cotok = node_cont; cotok && (LVTNOD_COUNT > inde); ++inde, ++lv2p_prop) {
            cotok = split_prope(lv2p_prop[0x00], cotok);
            if (INVAL_POINT == cotok)
                return -1;
            // OSEVPF("lv2p_prop[inde++]:|%s|\n", lv2p_prop[inde - 0x01]);
        }
    }
    MK_ZERO(lv2p_prop[0x00]);
    //
    return 0x00;
}

//

char *split_toke(char *node_str, int *node_type, char *body_text) {
    char *last_str = body_text;
    //
    if (isalpha(last_str[0x00]) || '_' == last_str[0x00]) {
        ++last_str;
        for (; isalnum(last_str[0x00]) || '_' == last_str[0x00]; ++last_str);
        lszcpy(node_str, body_text, last_str - body_text);
        *node_type = 0x00;
    } else if (isdigit(last_str[0x00])) {
        ++last_str;
        for (; isalnum(last_str[0x00]); ++last_str);
        lszcpy(node_str, body_text, last_str - body_text);
        *node_type = 0x01;
    } else {
        ++last_str;
        for (; !(isalnum(last_str[0x00]) || '_' == last_str[0x00]); ++last_str) {
            if ('\0' == last_str[0x00]) {
                lszcpy(node_str, body_text, last_str - body_text);
                *node_type = 0x02;
                return NULL;
            }
        }
        lszcpy(node_str, body_text, last_str - body_text);
        *node_type = 0x02;
    }
    //
    return last_str;
}

//

static char *parse_formal(char *form_bind, char *pamvu) {
    char *tokep, *toksp = pamvu;
    for (; ',' == toksp[0x00]
            || ' ' == toksp[0x00]
            || '(' == toksp[0x00]; ++toksp);
    if ('\0' == toksp[0x00]) return NULL;
    tokep = strchr(toksp + 0x01, ' ');
    if (!tokep) return NULL;
    strzcpy(form_bind, toksp, tokep - toksp);
    //
    tokep = strchr(++tokep, ',');
    if (!tokep) return NULL;
    //
    return ++tokep;
}

//

int split_meth_head(char (*form_bind)[PARAM_LENGTH], char *lev1_cont) {
    // CLIEPF("lev1_cont:|%s|\n", lev1_cont);
    unsigned int inde = 0x00;
    if ((lev1_cont = split_void(lev1_cont))) {
        for (; lev1_cont && ('\0' != lev1_cont[0x00]) && (PARAM_COUNT >= inde); ++inde, ++form_bind) {
            // CLIEPF("lev1_cont:|%s|\n", lev1_cont);
            lev1_cont = parse_formal(form_bind[0x00], lev1_cont);
            // CLIEPF("form_bind[inde]:|%s|\n", form_bind[inde]);
        }
    }
    // CLIEPF("param_type:|%s|\n", param_type);
    MK_ZERO(form_bind[0x00]);
    //
    return 0x00;
}

//

char *node_line(char *node_cont, char *conte) {
    char *last_str = conte;
    //
    for (; '\0' != last_str[0x00]; ++last_str) {
        if ('"' == last_str[0x00]) {
            ++last_str;
            for (; '\0' != last_str[0x00]; ++last_str) {
                if ('\\' == last_str[0x00]) ++last_str;
                else if ('"' == last_str[0x00]) break;
            }
        }
        if (';' == last_str[0x00] || '{' == last_str[0x00] || '}' == last_str[0x00]) {
            ++last_str;
            break;
        }
    }
    //
    lszcpy(node_cont, conte, last_str - conte);
    return last_str;
}

//

int check_decla(char *conte) {
    char *last_str = strlchr(conte);
    for (; conte != last_str && (';' == last_str[0x00] || ' ' == last_str[0x00]); --last_str);
    if (conte == last_str) return 0x00;
    if (')' == last_str[0x00]) {
        for (; conte != last_str && '(' != last_str[0x00]; --last_str);
        if (conte == last_str) return 0x00;
        for (--last_str; conte != last_str && ' ' == last_str[0x00]; --last_str);
        if (conte == last_str) return 0x00;
    }
    //
    char decla_type[LINE_LENGTH];
    char *detok = last_str;
    for (--last_str; conte != last_str && ' ' != last_str[0x00]; --last_str);
    if (conte == last_str) return 0x00;
    lszcpy(decla_type, last_str + 0x01, detok - last_str);
    // CLIEPF("decla_type:|%s|\n", decla_type);
    char **vari_ptyp = (char **) vari_type_tab;
    for (; vari_ptyp[0x00]; ++vari_ptyp) {
        if (!strcmp(decla_type, vari_ptyp[0x00]))
            return 0x01;
    }
    //
    return 0x00;
}

//

int split_decla(char *type, char (*varip)[PARAM_LENGTH], char *valu, char *decla) {
    char *last_str = strlchr(decla);
    for (; decla != last_str && (';' == last_str[0x00] || ' ' == last_str[0x00]); --last_str);
    if (decla == last_str) return 0x00;
    //
    char *detok = last_str;
    int decla_type = 0x00;
    if (')' == last_str[0x00]) {
        decla_type = 0x02;
        //
        for (; decla != last_str && '(' != last_str[0x00]; --last_str);
        if (decla == last_str) return 0x00;
        lszcpy(valu, last_str + 0x01, detok - last_str - 0x01);
        for (--last_str; decla != last_str && ' ' == last_str[0x00]; --last_str);
        if (decla == last_str) return 0x00;
    } else decla_type = 0x01;
    //
    detok = last_str;
    for (--last_str; decla != last_str && ' ' != last_str[0x00]; --last_str);
    if (decla == last_str) return 0x00;
    lszcpy(type, last_str + 0x01, detok - last_str);
    // CLIEPF("type:|%s| valu:|%s|\n", type, valu);
    //
    for (;; ++varip) {
        detok = last_str--;
        for (; decla != last_str && ',' != last_str[0x00]; --last_str);
        if (decla == last_str) {
            lszcpy(varip[0x00], last_str, detok - last_str);
            // CLIEPF("varip[inde]:|%s|\n", varip[inde]);
            break;
        }
        lszcpy(varip[0x00], last_str + 0x01, detok - last_str - 0x01);
        // CLIEPF("varip[inde]:|%s|\n", varip[inde]);
    }
    MK_ZERO((++varip)[0x00]);
    //
    return decla_type;
}

// trans-serve
// (a int, b int) 
// (a int, int, c int)

char *split_oinvk_iden(char *ostyp, char *pamvs) {
    char node_str[PARAM_LENGTH];
    // OSEVPF("----- pamvs:|%s|\n", pamvs);
    char *tokep, *toksp = pamvs;
    for (; ',' == toksp[0x00]
            || ' ' == toksp[0x00]
            || '(' == toksp[0x00]
            || ')' == toksp[0x00]
            || isdigit(toksp[0x00]); ++toksp);
    if ('\0' == toksp[0x00]) return NULL;
    //
    tokep = strpbrk(toksp + 0x01, ",)");
    if (!tokep) NULL;
    strzcpy(node_str, toksp, tokep - toksp);
    kill_blank(node_str);
    // OSEVPF("node_str:|%s|\n", node_str);
    toksp = strchr(node_str, ' ');
    if (toksp) {
        PASS_BLANK(toksp)
        strcpy(ostyp, toksp);
    } else strcpy(ostyp, node_str);
    //
    return ++tokep;
}

//

static int parse_iointe_sio(char *line_oivk, char *meth_inte, int iotyp) {
    char *toksp, *tokep;
    if (0x02 == iotyp) {
        toksp = strchr(meth_inte, '(');
        if (!toksp) return -1;
        tokep = strchr(toksp + 0x01, ')');
        if (!tokep) return -1;
        strzcpy(line_oivk, toksp, tokep - toksp + 0x01);
    }
    //
    return 0x00;
}

//

static int parse_iointe_doo(char *line_oivk, char *meth_inte, int iotyp) {
    char *tokep, *toksp = meth_inte;
    if (!iotyp) {
        toksp = strchr(toksp, '(');
        if (!toksp) return -1;
        tokep = strchr(toksp + 0x01, ')');
        if (!tokep) return -1;
        toksp = strchr(tokep + 0x01, ',');
        if (!toksp) return -1;
    }
    toksp = strchr(toksp, '(');
    if (!toksp) return -1;
    tokep = strchr(toksp + 0x01, ')');
    if (!tokep) return -1;
    strzcpy(line_oivk, toksp, tokep - toksp + 0x01);
    //
    return 0x00;
}

// trans-serve
// -1:error 0x00:inn_out 0x01:inn 0x02:out

int split_oinvk_head(char *line_oivk, char *meth_decl) {
    // OSEVPF("phe lev1_cont:|%s|\n", lev1_cont);
    char meth_inte[LVON_LENGTH];
    int iotyp = -1;
    // OSEVPF("phe inte_coun:%d\n", inte_coun);
    switch (inte_count(NULL, meth_inte, meth_decl)) {
        case 0x01:
            iotyp = iointe_type_ensi(meth_inte);
            // OSEVPF("its iotyp:%d\n", iotyp);
            if (-1 == iotyp || 0x01 == iotyp) break;
            parse_iointe_sio(line_oivk, meth_inte, iotyp);
            break;
        case 0x02:
            iotyp = iointe_type_do(meth_inte);
            // OSEVPF("itd iotyp:%d\n", iotyp);
            if (-1 == iotyp) break;
            parse_iointe_doo(line_oivk, meth_inte, iotyp);
            iotyp = 0x00;
            break;
        default:
            _LOG_WARN("default: inte_coun");
            return -1;
            break;
    }
    //
    return iotyp;
}

// trans-serve
// (a int, b int)

char *split_oinvk(char *ostyp, char *pamvs) {
    // OSEVPF("pamvs:|%s|\n", pamvs);
    char *tokep, *toksp = pamvs;
    for (; ',' == toksp[0x00]
            || ' ' == toksp[0x00]
            || '(' == toksp[0x00]
            || ')' == toksp[0x00]
            || isdigit(toksp[0x00]); ++toksp);
    if ('\0' == toksp[0x00]) return NULL;
    //
    toksp = strchr(toksp + 0x01, ' ');
    if (!toksp) return NULL;
    for (; ' ' == toksp[0x00]; ++toksp);
    tokep = strpbrk(toksp + 0x01, ", ()");
    if (!tokep) return NULL;
    strzcpy(ostyp, toksp, tokep - toksp);
    //
    return ++tokep;
}

// trans-serve

char *split_oinvk_node(char *oivk_node, char *pamvs) {
    // OSEVPF("ex pamvs:|%s|\n", pamvs);
    char *tokep, *toksp = pamvs;
    for (; ',' == toksp[0x00]
            || ' ' == toksp[0x00]
            || '(' == toksp[0x00]
            || ')' == toksp[0x00]; ++toksp);
    if ('\0' == toksp[0x00]) return NULL;
    tokep = toksp;
    int paren = 0x00;
    for (++tokep; tokep[0x00]; ++tokep) {
        if ('(' == tokep[0x00]) ++paren;
        else if (')' == tokep[0x00]) {
            if (!paren) break;
            --paren;
        } else if (',' == tokep[0x00]) break;
    }
    strzcpy(oivk_node, toksp, tokep - toksp);
    //
    return ++tokep;
}

// trans-serve

unsigned int split_pamvu_colum(char (*parm_arra)[PARAM_LENGTH], char *conte) {
    // OSEVPF("split_pamvu_colum:|%s|\n", data);
    unsigned int attrib = 0x00;
    //
    char *tokep, *toksp = conte;
    unsigned int inde = 0x00;
    for (; toksp && '\0' != toksp[0x00] && PARM_COLU_SIZE > inde; ++inde, ++parm_arra) {
        tokep = strpbrk(toksp, " =()");
        if (tokep) {
            switch (tokep[0x00]) {
                case ' ':
                    strzcpy(parm_arra[0x00], toksp, tokep - toksp);
                    break;
                case '=':
                    if (toksp != tokep) strzcpy(parm_arra[0x00], toksp, tokep - toksp);
                    attrib |= PARM_DEFAU;
                    break;
                case '(':
                case ')':
                    strzcpy(parm_arra[0x00], toksp, tokep - toksp);
                    attrib |= PARM_ARRAY;
                    break;
            }
            PASS_TBLANK(toksp, tokep + 0x01)
        } else {
            strcpy(parm_arra[0x00], toksp);
            toksp = NULL;
        }
        // OSEVPF("parm_arra[%d]:|%s|\n", inde, parm_arra[inde]);
    }
    //
    return attrib;
}

// trans-serve

int parse_pamvu_colum(pamv_node *pamnod, char (*parm_arra)[PARAM_LENGTH]) {
    strcpy(pamnod->name, parm_arra[0x00]);
    if (PARM_DEFAU & pamnod->attri) {
        strcpy(pamnod->defau, (++parm_arra)[0x00]);
        strcpy(pamnod->type, (++parm_arra)[0x00]);
        if (PARM_ARRAY & pamnod->attri) strcpy(pamnod->array, (++parm_arra)[0x00]);
    } else {
        strcpy(pamnod->type, (++parm_arra)[0x00]);
        if (PARM_ARRAY & pamnod->attri) strcpy(pamnod->array, (++parm_arra)[0x00]);
    }
    KV_STIN_OR(pamnod->attri, ostyp_pamati_dict, pamnod->type);
    if ((PARM_STRI & pamnod->attri) && (PARM_DEFAU & pamnod->attri))
        quote_decode(pamnod->defau);
    //
    return 0x00;
}

