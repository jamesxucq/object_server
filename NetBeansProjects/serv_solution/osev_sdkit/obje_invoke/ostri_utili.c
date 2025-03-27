#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "kcstr_utili.h"
#include "ostri_utili.h"
#include "lv2p_decla.h"

//

char *split_metho_conte(OUT char *lv2pn, OUT char *lev1n, char *lev1_cont) {
    char *toksp;
    PASS_TBLANK(toksp, lev1_cont)
            char *tokep = strchr(toksp + 0x01, ':');
    if (!tokep) return NULL;
    if (lv2pn) strzcpy(lv2pn, toksp, tokep - toksp);
    //
    toksp = strpbrk(tokep + 0x01, " <");
    if (!toksp) return NULL;
    strzcpy(lev1n, tokep + 0x01, toksp - tokep - 0x01);
    //
    return toksp;
}

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

/*
static int imeth_node(char *toksp, char *tokep) {
    for (--tokep; toksp <= tokep; --tokep) {
        if (' ' == toksp[0x00]) continue;
        if (':' == toksp[0x00]) return 0x01;
        break;
    }
    //
    return 0x00;
}

char *prod_prop_node(char *conte, char attri, char *data) {
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
 */

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

char *split_metho_ident(OUT char *lev1n, char *ident) {
    char *toksp;
    PASS_TBLANK(toksp, ident)
            char *tokep = strchr(toksp + 0x01, ':');
    if (!tokep) return NULL;
    //
    toksp = strpbrk(tokep + 0x01, " <");
    if (!toksp) return NULL;
    strzcpy(lev1n, tokep + 0x01, toksp - tokep - 0x01);
    //
    return toksp;
}

static char *couple_bracket(char *stri) {
    if (!stri || '(' != stri[0x00])
        return NULL;
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

static int parse_iointe_sii(char *ibind, char *meth_inte, int iotyp) {
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

static int parse_iointe_sior(char *retype, char *meth_inte, int iotyp) {
    char *toksp, *tokep;
    if (0x02 == iotyp) {
        toksp = strchr(meth_inte, '(');
        if (!toksp) return -1;
        toksp = strchr(++toksp, ')');
        if (!toksp) return -1;
        ++toksp;
        PASS_BLANK(toksp);
        tokep = 0x01 + toksp;
        for (; ' ' != tokep[0x00] && '\0' != tokep[0x00]
                && ',' != tokep[0x00] && '>' != tokep[0x00]; ++tokep);
        strzcpy(retype, toksp, tokep - toksp);
    }
    //
    return 0x00;
}

//

static int parse_iointe_sin(char *oivk_type, char *line_oivk, char *ibind, char *meth_inte, int iotyp) {
    char *toksp, *tokep;
    // OSEVPF("pis meth_inte:|%s|\n", meth_inte);
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

static int parse_iointe_doi(char *ibind, char *meth_inte, int iotyp) {
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

static int parse_iointe_door(char *retype, char *meth_inte, int iotyp) {
    char *tokep, *toksp = meth_inte;
    if (!iotyp) {
        toksp = strchr(toksp, '(');
        if (!toksp) return -1;
        tokep = strchr(++toksp, ')');
        if (!tokep) return -1;
        toksp = strchr(tokep + 0x01, ',');
        if (!toksp) return -1;
    }
    toksp = strchr(toksp, '(');
    if (!toksp) return -1;
    toksp = strchr(++toksp, ')');
    if (!toksp) return -1;
    ++toksp;
    PASS_BLANK(toksp);
    tokep = 0x01 + toksp;
    for (; ' ' != tokep[0x00] && '\0' != tokep[0x00]
            && ',' != tokep[0x00] && '>' != tokep[0x00]; ++tokep);
    strzcpy(retype, toksp, tokep - toksp);
    //
    return 0x00;
}

//

static int parse_iointe_don(char *oivk_type, char *line_oivk, char *ibind, char *meth_inte, int iotyp) {
    // OSEVPF("[FUNC]:parse_iointe_don meth_inte:|%s|\n", meth_inte);
    char *tokep, *toksp;
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

//

char *split_head(char *oivk_type, char *line_oivk, char *ibind, char *meth_decl) {
    // OSEVPF("ph lev1_cont:|%s|\n", lev1_cont);
    char meth_inte[LVON_LENGTH];
    int iotyp = -1;
    char *last_str = NULL;
    // OSEVPF("ph inte_coun:%d\n", inte_coun);
    switch (inte_count(&last_str, meth_inte, meth_decl)) {
        case 0x01:
            iotyp = iointe_type_ensi(meth_inte);
            // OSEVPF("its iotyp:%d\n", iotyp);
            if (-1 == iotyp) return NULL;
            if (parse_iointe_sin(oivk_type, line_oivk, ibind, meth_inte, iotyp))
                return NULL;
            break;
        case 0x02:
            iotyp = iointe_type_do(meth_inte);
            // OSEVPF("itd iotyp:%d\n", iotyp);
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

int split_oinvk_retyp(char *retype, char *meth_decl) {
    // OSEVPF("phe lev1_cont:|%s|\n", lev1_cont);
    char meth_inte[LVON_LENGTH];
    int iotyp = -1;
    // OSEVPF("phe inte_coun:%d\n", inte_coun);
    switch (inte_count(NULL, meth_inte, meth_decl)) {
        case 0x01:
            iotyp = iointe_type_ensi(meth_inte);
            // OSEVPF("its iotyp:%d\n", iotyp);
            if (-1 == iotyp || 0x01 == iotyp) break;
            parse_iointe_sior(retype, meth_inte, iotyp);
            break;
        case 0x02:
            iotyp = iointe_type_do(meth_inte);
            // OSEVPF("itd iotyp:%d\n", iotyp);
            if (-1 == iotyp) break;
            parse_iointe_door(retype, meth_inte, iotyp);
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

// -1:error 0x00:inn_out 0x01:inn 0x02:out

int split_ibind_head(char *ibind, char *meth_decl) {
    // OSEVPF("phe lev1_cont:|%s|\n", lev1_cont);
    char meth_inte[LVON_LENGTH];
    int iotyp = -1;
    // OSEVPF("phe inte_coun:%d\n", inte_coun);
    switch (inte_count(NULL, meth_inte, meth_decl)) {
        case 0x01:
            iotyp = iointe_type_ensi(meth_inte);
            // OSEVPF("its iotyp:%d\n", iotyp);
            if (-1 == iotyp || 0x02 == iotyp) break;
            parse_iointe_sii(ibind, meth_inte, iotyp);
            break;
        case 0x02:
            iotyp = iointe_type_do(meth_inte);
            // OSEVPF("itd iotyp:%d\n", iotyp);
            if (-1 == iotyp) break;
            parse_iointe_doi(ibind, meth_inte, iotyp);
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

static int parse_cotype_sio(char *const_type, char *meth_inte, int iotyp) {
    // OSEVPF("meth_inte:|%s|\n", meth_inte);
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
    // OSEVPF("ph lev1_cont:|%s|\n", lev1_cont);
    char meth_inte[LVON_LENGTH];
    if (0x01 != inte_count(NULL, meth_inte, meth_decl))
        return -1;
    // -1:error 0x00:inn_out 0x01:inn 0x02:out
    int iotyp = iointe_type_ensi(meth_inte);
    if (0x02 != iotyp) return -1;
    parse_cotype_sio(const_type, meth_inte, iotyp);
    //
    return 0x00;
}

//

int split_class_actu(char *actu_head, char *lv2_dec, char *lev1n) {
    // OSEVPF("lv2_dec:|%s|\n", lv2_dec);
    // OSEVPF("lev1n:|%s|\n", lev1n);
    char *toksp = strstr(lv2_dec, lev1n);
    if (!toksp) return -1;
    toksp += strlen(lev1n);
    toksp = strchr(toksp, '(');
    if (!toksp) return -1;
    char *tokep = strchr(toksp, ')');
    if (!tokep) return -1;
    //
    strzcpy(actu_head, toksp, tokep - toksp + 0x01);
    // OSEVPF("actu_head:|%s|\n", actu_head);
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
        for (; !isalnum(last_str[0x00]) && '_' != last_str[0x00]; ++last_str) {
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

static char *parse_actual(char *actu_bind, char *pamvu) {
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

int split_meth_head(char (*form_bind)[PARAM_LENGTH], char *lev1_cont) {
    // OSEVPF("[FUNC]:split_meth_head\n");
    // OSEVPF("lev1_cont:|%s|\n", lev1_cont);
    unsigned int inde = 0x00;
    if ((lev1_cont = split_void(lev1_cont))) {
        for (; lev1_cont && ('\0' != lev1_cont[0x00]) && (PARAM_COUNT >= inde); ++inde, ++form_bind) {
            // OSEVPF("lev1_cont:|%s|\n", lev1_cont);
            lev1_cont = parse_formal(form_bind[0x00], lev1_cont);
            // OSEVPF("form_bind[0x00]:|%s|\n", form_bind[0x00]);
        }
    }
    MK_ZERO(form_bind[0x00]);
    //
    return 0x00;
}

int split_meth_oivk(char (*form_oivk)[PARAM_LENGTH], char *lev1_cont) {
    // OSEVPF("[FUNC]:split_meth_head\n");
    // OSEVPF("lev1_cont:|%s|\n", lev1_cont);
    unsigned int inde = 0x00;
    if ((lev1_cont = split_void(lev1_cont))) {
        for (; lev1_cont && ('\0' != lev1_cont[0x00]) && (PARAM_COUNT >= inde); ++inde, ++form_oivk) {
            // OSEVPF("lev1_cont:|%s|\n", lev1_cont);
            lev1_cont = parse_formal(form_oivk[0x00], lev1_cont);
            // OSEVPF("form_bind[0x00]:|%s|\n", form_bind[0x00]);
        }
    }
    MK_ZERO(form_oivk[0x00]);
    //
    return 0x00;
}

int split_class_meth(char (*actu_bind)[PARAM_LENGTH], char *actu_head) {
    // OSEVPF("[FUNC]:split_class_meth\n");
    // OSEVPF("actu_head:|%s|\n", actu_head);
    unsigned int inde = 0x00;
    if ((actu_head = split_void(actu_head))) {
        for (; actu_head && ('\0' != actu_head[0x00]) && (PARAM_COUNT >= inde); ++inde, ++actu_bind) {
            // OSEVPF("actu_head:|%s|\n", actu_head);
            actu_head = parse_actual(actu_bind[0x00], actu_head);
            // OSEVPF("actu_bind[0x00]:|%s|\n", actu_bind[0x00]);
        }
    }
    MK_ZERO(actu_bind[0x00]);
    //
    return 0x00;
}

//
static osv_str_t PARM_VOID_TOK = osv_stri("void");

char *split_void(char *parms) {
    for (; ',' == parms[0x00] || ' ' == parms[0x00]
            || '(' == parms[0x00]; ++parms);
    if ('\0' == parms[0x00]) return NULL;
    else if (!strncmp(PARM_VOID_TOK.data, parms, PARM_VOID_TOK.slen))
        return NULL;
    else if (')' == parms[0x00]) return NULL;
    return parms;
}

// trans-serve
// (a int, b int)

char *split_oinvk(char *ostyp, char *parms) {
    // OSEVPF("pamvu:|%s|\n", pamvu);
    char *tokep, *toksp = parms;
    for (; ',' == toksp[0x00] || ' ' == toksp[0x00] || '(' == toksp[0x00]
            || ')' == toksp[0x00] || isdigit(toksp[0x00]); ++toksp);
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
// (a int, b int) 
// (a int, int, c int)

char *split_oinvk_iden(char *ostyp, char *parms) {
    char node_str[PARAM_LENGTH];
    // OSEVPF("----- pamvu:|%s|\n", parms);
    char *tokep, *toksp = parms;
    for (; ',' == toksp[0x00] || ' ' == toksp[0x00] || '(' == toksp[0x00]
            || isdigit(toksp[0x00]); ++toksp);
    if (')' == toksp[0x00] || '\0' == toksp[0x00]) return NULL;
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
    return tokep;
}

// trans-serve

/*
char *split_oinvk_node(char *oivk_node, char *parms) {
    // OSEVPF("ex pamvu:|%s|\n", pamvu);
    char *tokep, *toksp = parms;
    for (; ',' == toksp[0x00]
            || ' ' == toksp[0x00]
            || '(' == toksp[0x00]
            || ')' == toksp[0x00]; ++toksp);
    if ('\0' == toksp[0x00]) return NULL;
    tokep = strpbrk(toksp + 0x01, ",)");
    if (!tokep) return NULL;
    strzcpy(oivk_node, toksp, tokep - toksp);
    //
    return ++tokep;
}
 */

char *split_oinvk_node(char *oivk_node, char *parms) {
    // OSEVPF("ex pamvu:|%s|\n", pamvu);
    char *tokep, *toksp = parms;
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

int split_class_name_prope(char *lv2pn, char (*lv2p_prop)[PARAM_LENGTH], char *lv2_dec) {
    char *toksp, *cotok;
    toksp = split_lv2pn(lv2pn, lv2_dec);
    if (!toksp) return -1;
    // OSEVPF("split_class_prope, lv2pn:|%s|\n", lv2pn);
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

static char *bound_node(char *conte, char *data) {
    char *toksp;
    PASS_TBLANK(toksp, data)
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
    if (!strcmp(lev1n, lv2pn)) return METHO_CONST_TYPE;
    OSEVPF("check lev1n:|%s| lv2_dec:|%s|\n", lev1n, lv2_dec);
    char bound[LVON_LENGTH];
    while ((detok = bound_node(bound, detok))) {
        // OSEVPF("bound:|%s|\n", bound);
        if (!strcmp(lev1n, bound))
            return METHO_NORMA_TYPE;
    }
    // OSEVPF("cmt not found:|%s|\n", lev1n);
    return -1;
}

// taat<[xx=8 int, ax int], teet:xxp(), [cx int] auto, tst(xx), [dx int] auto, teet:tpp(ax), txp(ax, cx)>;
// LVTP_NORM_METH: txp(ax, cx) | cinhep[0x00]:taat ident:txp
// LVTP_INHE_METH: teet:txxp:tpp(ax) | cinhep[0x00]:taat cinhep[0x01]:teet cinhep[0x02]:txxp ident:tpp
// LVTP_INHE_LEVO: teet:txxp:tpp | cinhep[0x00]:taat cinhep[0x01]:teet cinhep[0x02]:txxp ident:tpp
// LVTP_INHE_LVTP: teet:txxp:xxoo | cinhep[0x00]:taat cinhep[0x01]:teep cinhep[0x02]:txxp ident:xxoo
// LVTP_INHE_CLAS: teet | cinhep[0x00]:taat cinhep[0x01]:teet ident:MK_ZERO

char *parse_lev1d_node(lev1_decl_t *lev1d, char *data) {
    OSEVPF("[FUNC]:parse_lev1d_node, data:|%s|\n", data);
    char *toksp, *tokep;
    char *tok1, *tok2;
    toksp = data + 0x01;
    // pass data node
    tokep = ospbrk(toksp, ",><");
    if (!tokep) return NULL;
    while (osechr(toksp, '[', tokep)) {
        toksp = tokep + 0x01;
        tokep = ospbrk(toksp, ",><");
        if (!tokep) return NULL;
    }
    // parse conte node
    PASS_BLANK(toksp)
    tok1 = osrchr(toksp, ':', tokep);
    tok2 = osechr(toksp, '(', tokep);
    if (tok1 && tok2) {
        strzcpy(lev1d->_cline_, toksp, tok1 - toksp);
        pass_rblak(lev1d->_cline_);
        if (LVON_LENGTH <= (tok2 - (++tok1)))
            return NULL;
        strzcpy(lev1d->ident, tok1, tok2 - tok1);
        blank_decode(lev1d->ident);
        tok1 = tok2;
        tok2 = osechr(tok1, ')', tokep);
        if (!tok2) return NULL;
        strzcpy(lev1d->innep._iline_, tok1, tok2 - tok1 + 0x01);
        lev1d->levtyp = LVTP_INHE_METH;
    } else if (tok1 && !tok2) {
        strzcpy(lev1d->_cline_, toksp, tok1 - toksp);
        pass_rblak(lev1d->_cline_);
        if (LVON_LENGTH <= (tok2 - (++tok1)))
            return NULL;
        strzcpy(lev1d->ident, tok1, tokep - tok1);
        blank_decode(lev1d->ident);
        MK_ZERO(lev1d->innep._iline_);
        lev1d->levtyp = LVTP_LVTP_LEVO;
    } else if (!tok1 && tok2) {
        MK_ZERO(lev1d->_cline_);
        if (LVON_LENGTH <= (tok2 - toksp))
            return NULL;
        strzcpy(lev1d->ident, toksp, tok2 - toksp);
        pass_rblak(lev1d->ident);
        tok1 = tok2;
        tok2 = osechr(tok1, ')', tokep);
        if (!tok2) return NULL;
        strzcpy(lev1d->innep._iline_, tok1, tok2 - tok1 + 0x01);
        lev1d->levtyp = LVTP_NORM_METH;
    } else if (!tok1 && !tok2) {
        strzcpy(lev1d->_cline_, toksp, tokep - toksp);
        pass_rblak(lev1d->_cline_);
        MK_ZERO(lev1d->ident);
        MK_ZERO(lev1d->innep._iline_);
        lev1d->levtyp = LVTP_INHE_CLAS;
    }
    //
    return tokep;
}

char *split_inher_clasn(OUT char **cinhep, char *_cline_) {
    char *toksp, *tokep;
    if (NOT_ZERO(_cline_)) {
        toksp = _cline_;
        tokep = strchr(toksp, ':');
        for (; tokep; ++cinhep) {
            MK_ZERO(tokep);
            blank_decode(toksp);
            cinhep[0x00] = toksp;
            //
            toksp = ++tokep;
            tokep = strchr(toksp, ':');
        }
        blank_decode(toksp);
        cinhep[0x00] = toksp;
        ++cinhep;
    }
    //
    cinhep[0x00] = NULL;
    return _cline_;
}

//
#define FIND_POTYP_NONE(POTYP, ARRAY, NAME) { \
    for(; ACCE_COTRL_INVAL != ARRAY->access; ++ARRAY) \
        if(!strcmp(NAME, ARRAY->name)) break; \
    POTYP = ARRAY->potyp; \
}

char *split_ibind(DATA_TYPE *prop_type, lv2p_prop *l2_nod, char *parms) {
    char pamvu[PARAM_LENGTH];
    char *tokep, *toksp = parms;
    for (; ',' == toksp[0x00]
            || ' ' == toksp[0x00]
            || '(' == toksp[0x00]
            || ')' == toksp[0x00]; ++toksp);
    if ('\0' == toksp[0x00]) return NULL;
    //
    tokep = strpbrk(toksp + 0x01, ", )");
    if (!tokep) return NULL;
    strzcpy(pamvu, toksp, tokep - toksp);
    FIND_POTYP_NONE(prop_type[0x00], l2_nod, pamvu);
    // OSEVPF("pamvu:|%s| prop_type:|%d|\n", pamvu, prop_type[0x00]);
    return ++tokep;
}

#define FIND_LTNOD_NONE(NOVAL, ARRAY, NAME) { \
    for(; ACCE_COTRL_INVAL != ARRAY->access; ++ARRAY) \
        if(!strcmp(NAME, ARRAY->name)) break; \
    memcpy(NOVAL, ARRAY, sizeof(lv2p_prop)); \
}

char *split_ibind_lv2d(lv2p_prop *lv2nod, lv2p_prop *l2_nod, char *parms) {
    char pamvu[PARAM_LENGTH];
    // OSEVPF("pamvu:|%s|\n", pamvu);
    char *tokep, *toksp = parms;
    for (; ',' == toksp[0x00]
            || ' ' == toksp[0x00]
            || '(' == toksp[0x00]
            || ')' == toksp[0x00]; ++toksp);
    if ('\0' == toksp[0x00]) return NULL;
    //
    tokep = strpbrk(toksp + 0x01, ", )");
    if (!tokep) return NULL;
    strzcpy(pamvu, toksp, tokep - toksp);
    FIND_LTNOD_NONE(lv2nod, l2_nod, pamvu);
    //
    return ++tokep;
}

char *split_ibind_pamvs(char *pamvu, char *parms) {
    char *tokep, *toksp = parms;
    for (; ',' == toksp[0x00]
            || ' ' == toksp[0x00]
            || '(' == toksp[0x00]
            || ')' == toksp[0x00]; ++toksp);
    if ('\0' == toksp[0x00]) return NULL;
    //
    tokep = strpbrk(toksp + 0x01, ", )");
    if (!tokep) return NULL;
    strzcpy(pamvu, toksp, tokep - toksp);
    //
    return ++tokep;
}

//

char *split_ibind_parap(char **pamvp, char *parms) {
    char *tokep, *toksp = parms;
    for (; ',' == toksp[0x00]
            || ' ' == toksp[0x00]
            || '(' == toksp[0x00]
            || ')' == toksp[0x00]; ++toksp);
    if ('\0' == toksp[0x00]) return NULL;
    //
    tokep = strpbrk(toksp + 0x01, ", )");
    if (!tokep) return NULL;
    tokep[0x00] = '\0';
    pamvp[0x00] = toksp;
    //
    return ++tokep;
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

// |this->ax = aa;|

int check_decla(char *conte) {
    // OSEVPF("[FUNC]:check_decla\n");
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
    char *cotok = last_str;
    for (--last_str; conte != last_str && ' ' != last_str[0x00]; --last_str);
    if (conte == last_str) return 0x00;
    lszcpy(decla_type, last_str + 0x01, cotok - last_str);
    // OSEVPF("decla_type:|%s|\n", decla_type);
    char **vari_ptyp = (char **) vari_type_tab;
    for (; vari_ptyp[0x00]; ++vari_ptyp) {
        if (!strcmp(decla_type, vari_ptyp[0x00]))
            return 0x01;
    }
    // OSEVPF("end, check_decla\n");
    return 0x00;
}

//

int split_decla(OUT char *type, OUT char (*varip)[PARAM_LENGTH], OUT char *valu, char *decla) {
    // OSEVPF("[FUNC]:split_decla\n");
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
    // OSEVPF("type:|%s| valu:|%s|\n", type, valu);
    //
    while (++varip) {
        detok = last_str--;
        for (; decla != last_str && ',' != last_str[0x00]; --last_str);
        if (decla == last_str) {
            lszcpy(varip[0x00], last_str, detok - last_str);
            // OSEVPF("varip[inde]:|%s|\n", varip[inde]);
            break;
        }
        lszcpy(varip[0x00], last_str + 0x01, detok - last_str - 0x01);
        // OSEVPF("varip[inde]:|%s|\n", varip[inde]);
    }
    MK_ZERO((++varip)[0x00]);
    // OSEVPF("end, split_decla\n");
    return decla_type;
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
    if (((PARM_STRI | PARM_STRZ) & pamnod->attri) && (PARM_DEFAU & pamnod->attri))
        quote_decode(pamnod->defau);
    //
    return 0x00;
}

//

char *split_lv2pn_node(char **l2np_nod, char *lv2pn) {
    if ('\0' == lv2pn[0x00]) return NULL;
    //
    l2np_nod[0x00] = lv2pn;
    char *lntok = strchr(lv2pn, ':');
    if (lntok) {
        lntok[0x00] = '\0';
        ++lntok;
    } else lntok = strend(lv2pn);
    //
    return lntok;
}

//

int build_columns_types(char *types, lv2p_prop *l2_nod) {
    char type[PARAM_LENGTH], valu[PARAM_LENGTH], size[PARAM_LENGTH];
    //    
    for (; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod) {
        if (split_data_styl(type, valu, size, l2_nod->decla))
            return -1;
        // OSEVPF("lv2p_prop[inde]:|%s|\n", data[inde]);
        types = conve_types(types, type, size);
    }
    //
    return 0x00;
}

// "(xx, ax, cx)"

char *split_inner_parms(OUT char **pamvp, char *_iline_) {
    unsigned int inde = 0x00;
    if ((_iline_ = split_void(_iline_))) {
        for (; _iline_ && ('\0' != _iline_[0x00]) && (PARAM_COUNT >= inde); ++inde, ++pamvp) {
            // OSEVPF("_iline_:|%s|\n", _iline_);
            _iline_ = split_ibind_parap(pamvp, _iline_);
            // OSEVPF("innep:|%s|\n", pamvp[0x00]);
        }
    }
    //
    pamvp[0x00] = NULL;
    return _iline_;
}

