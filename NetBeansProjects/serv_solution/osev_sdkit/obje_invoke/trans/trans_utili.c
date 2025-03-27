#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "ostri_utili.h"
#include "filli_clang.h"
#include "lev1_decla.h"
#include "lv2p_decla.h"

#include "trans_utili.h"
#include "debug_funct_oi.h"

/*
test<[xx=8 int, ax int], [cx int] auto, tst(xx), tpp(ax)>
test:tst<(void)int> {return 0x00;}
test:tpp<(void)int, (x int)> {return 0x01;}
test:test<(void)int> {return x;}
 */

// -1:error 0x00:inn_out 0x01:inn 0x02:out

static int split_inner_metho(char *lev1n, char *inner_metho, char *lev1_cont) {
    lev1_cont = split_metho_ident(lev1n, lev1_cont);
    if (!lev1_cont) return -1;
    int iotyp = split_ibind_head(inner_metho, lev1_cont);
    // OSEVPF("pim iotyp:%d inner_metho:|%s|\n", iotyp, inner_metho);
    return iotyp;
}

// -1:error 0x00:ok

static int split_const_metho(char *const_type, char *lev1_cont) {
    lev1_cont = pass_space(lev1_cont);
    if (!lev1_cont) return -1;
    if (split_chead(const_type, lev1_cont))
        return -1;
    // OSEVPF("pim iotyp:%d inner_metho:|%s|\n", iotyp, inner_metho);
    return 0x00;
}

// <[xx=8 int, ax int], ttt(), [cx int] auto, teet:tpp(ax), tst(xx, cx), tpp(ax)>;
// <[user_name char(32), password char(32), salt char(16), role_obid char(96)]>;

int parse_class_meta(lv2p_prop *l2_nod, char *lv2p_cont) {
    //. OSEVPF("parse_class_meta. lv2p_cont:|%s|\n", lv2p_cont);
    char *toksp, *notok;
    toksp = lv2p_cont;
    //
    char node_cont[LVTNOD_LENGTH];
    char acce_cont[PARAM_LENGTH];
    int acces_cotrl;
    lv2p_prop *lv2nod = l2_nod;
    unsigned int inde = 0x00;
    while ((toksp = prod_prop_node(node_cont, acce_cont, toksp))) {
        // OSEVPF("--- node_cont:|%s|, acces:|%s|\n", node_cont, acce_cont);
        acces_cotrl = gener_acces_cotrl(acce_cont);
        if (ACCE_COTRL_INVAL == acces_cotrl)
            return -1;
        for (notok = node_cont; notok && (LVTNOD_COUNT > inde); ++inde, ++lv2nod) {
            notok = split_prope(lv2nod->decla, notok);
            if (INVAL_POINT == notok)
                return -1;
            if (conv_bind_type(lv2nod->name, &lv2nod->potyp, &lv2nod->size, lv2nod->decla))
                return -1;
            lv2nod->access = acces_cotrl;
            // OSEVPF("------ decla:|%s|\n", lv2nod->decla);
            // OSEVPF("name:|%s| type:|%s| size:|%s| acces:%d\n", lv2nod->name, lv2nod->xxxxxtype, lv2nod->size, lv2nod->acces);
        }
    }
    lv2nod->access = ACCE_COTRL_INVAL;
    //
    return 0x00;
}

static int parse_clas_node(lv2p_prop *l2_nod, char *lv2p_cont) {
    char *toksp, *notok;
    toksp = pass_clasn(lv2p_cont);
    if (!toksp) return -1;
    //
    char node_cont[LVTNOD_LENGTH];
    char acce_cont[PARAM_LENGTH];
    char parms[PARAM_LENGTH];
    lv2p_prop *lv2nod = l2_nod;
    unsigned int inde = 0x00;
    while ((toksp = prod_prop_node(node_cont, acce_cont, toksp))) {
        // OSEVPF("node_cont:|%s|\n", node_cont);
        for (notok = node_cont; notok && (LVTNOD_COUNT > inde); ++inde, ++lv2nod) {
            notok = split_prope(parms, notok);
            if (INVAL_POINT == notok)
                return -1;
            if (conv_bind_type(lv2nod->name, &lv2nod->potyp, &lv2nod->size, parms))
                return -1; // todo: lv2nod->xxxxxtype lv2nod->size 
            // OSEVPF("name:|%s| type:|%s|\n", lv2nod[inde].name, lv2nod[inde].type);
        }
    }
    lv2nod->access = ACCE_COTRL_INVAL;
    //
    return 0x00;
}

//
// test:tpp<(void)int, (x int)>

static int conv_inne_type(DATA_TYPE *potyp, char *conte) {
    // OSEVPF("bd conte:|%s| ", conte);
    char *matok = strchr(conte, ' ');
    if (matok) {
        while (' ' == matok[0x00]) ++matok;
        KV_STIN_EQUA(potyp[0x00], ostyp_potyp_dict, matok)
    }
    // OSEVPF("dtype:|%s| \n", dtype);
    return 0x00;
}

//

static int parse_inner_type(DATA_TYPE *inner_type, char *inner_metho) {
    char node_cont[LVTNOD_LENGTH];
    split_argu_node(node_cont, inner_metho);
    // OSEVPF("pit node_cont:|%s|\n", node_cont);
    char parms[PARAM_LENGTH];
    char *notok = node_cont;
    for (; notok; ++inner_type) {
        notok = split_prope(parms, notok);
        if (INVAL_POINT == notok)
            return -1;
        // OSEVPF("pit parms:|%s|\n", parms);
        conv_inne_type(inner_type, parms);
        // OSEVPF("inner_type[inde++]:|%s|\n", inner_type[inde - 0x01]);
    }
    inner_type[0x00] = DATY_INVAL;
    //
    return 0x00;
}

//
#define FIND_POTYP_ZTAI(POTYP, ARRAY, NAME) { \
    lv2p_prop *l2_nod = ARRAY; \
    for(; '\0' != l2_nod->name[0x00]; ++l2_nod) \
        if(!strcmp(NAME, l2_nod->name)) break; \
    POTYP = l2_nod->potyp; \
}

// 

static int parse_clas_metho(DATA_TYPE *meth_data, lv2p_prop *lv2nod, char *lv2p_cont, char *lev1n) {
    // OSEVPF("parse_clas_metho\n");
    char actu_head[LVON_LENGTH];
    if (split_class_actu(actu_head, lv2p_cont, lev1n))
        return -1;
    //
    char actu_bind[PARAM_COUNT][PARAM_LENGTH];
    if (split_class_meth(actu_bind, actu_head))
        return -1;
    //
    char (*actup)[PARAM_LENGTH] = actu_bind;
    for (; '\0' != (*actup)[0x00]; ++actup, ++meth_data) {
        FIND_POTYP_ZTAI(meth_data[0x00], lv2nod, actu_bind[0x00]);
        // OSEVPF("actu_bind:|%s| meth_data:|%s|\n", actu_bind[inde], meth_data[inde]);
    }
    meth_data[0x00] = DATY_INVAL;
    //
    return 0x00;
}

static int check_inner_type(DATA_TYPE *inner_metho, DATA_TYPE *meth_data) {
    unsigned int inde = 0x00;
    for (; PARAM_COUNT > inde; ++inde, ++inner_metho, ++meth_data) {
        // OSEVPF("cit inde:%d ", inde);
        // OSEVPF("inner_metho:|%s| meth_data:|%s|\n", inner_metho[inde], meth_data[inde]);
        if ((DATY_INVAL == inner_metho[0x00]) || (DATY_INVAL == meth_data[0x00])) {
            if (DATY_INVAL != inner_metho[0x00] || DATY_INVAL != meth_data[0x00])
                return -1;
            break;
        }
        if (inner_metho[0x00] != meth_data[0x00])
            return -1;
    }
    // OSEVPF("pass check inner type!\n");
    return 0x00;
}

// trans-serve
#define CONST_TYPE_TOK_I "int"
#define CONST_TYPE_TOK_II "int32"
#define CHECK_CONST_TYPE(const_type) (strcmp(CONST_TYPE_TOK_I, const_type) || strcmp(CONST_TYPE_TOK_II, const_type))

// check inner invoke argument nodat type

int valid_metho_legal(char *lev1_cont, char *lv2p_cont, int norma_const) {
    char coin_metho[LVON_LENGTH];
    char lev1n[LVON_LENGTH];
    // -1:error 0x00:constructor 0x01:normal
    if (norma_const) { // -1:error 0x00:inn_out 0x01:inn 0x02:out
        int inou_type = split_inner_metho(lev1n, coin_metho, lev1_cont);
        if ((-1 == inou_type) || (0x01 == inou_type))
            return -1;
        // OSEVPF("inou_type:%d lev1n:|%s| inner_metho:|%s|\n", inou_type, lev1n, coin_metho);
        // check the outside invoke
        DATA_TYPE inner_type[PARAM_COUNT];
        parse_inner_type(inner_type, coin_metho);
        // check inner invoke argum
        lv2p_prop lv2_nod[LVTNOD_COUNT];
        DATA_TYPE meth_data[PARAM_COUNT];
        parse_clas_node(lv2_nod, lv2p_cont);
        parse_clas_metho(meth_data, lv2_nod, lv2p_cont, lev1n);
        if (check_inner_type(inner_type, meth_data))
            return -1;
    } else { // const funct
        if (split_const_metho(coin_metho, lev1_cont))
            return -1;
        // OSEVPF("coin_metho:|%s|\n", coin_metho);
        if (CHECK_CONST_TYPE(coin_metho))
            return -1;
    }
    //
    return 0x00;
}

//

char *conv_decla(char *decla, char *conte) {
    // OSEVPF("[FUNC]:conv_decla\n");
    char type[PARAM_LENGTH], valu[PARAM_LENGTH];
    char vari[PARAM_COUNT][PARAM_LENGTH];
    int decla_type = split_decla(type, vari, valu, conte);
    //
    char (*varip)[PARAM_LENGTH] = vari;
    // unsigned int inde = 0x00;
    if (0x01 == decla_type) {
        decla = lscpy(decla, type);
        if ('\0' != (*varip)[0x00]) {
            decla = lccpy(decla, ' ');
            decla = lscpy(decla, varip[0x00]);
            ++varip;
        }
        for (; '\0' != (*varip)[0x00]; ++varip) {
            decla = lscpy(decla, ", ");
            decla = lscpy(decla, varip[0x00]);
        }
        decla = lscpy(decla, ";\n");
    } else if (0x02 == decla_type) {
        decla = lscpy(decla, type);
        if ('\0' != (*varip)[0x00]) {
            decla = lccpy(decla, ' ');
            decla = lscpy(decla, varip[0x00]);
            decla = lccpy(decla, '[');
            decla = lscpy(decla, valu);
            decla = lccpy(decla, ']');
            ++varip;
        }
        for (; '\0' != (*varip)[0x00]; ++varip) {
            decla = lscpy(decla, ", ");
            decla = lscpy(decla, varip[0x00]);
            decla = lccpy(decla, '[');
            decla = lscpy(decla, valu);
            decla = lccpy(decla, ']');
        }
        decla = lscpy(decla, ";\n");
    } else return NULL;
    // OSEVPF("end, conv_decla\n");
    return decla;
}

// trans-serve

static int conv_oinvk_pamvs(pamv_node *pamnod, char *conte) {
    char parm_arra[PARM_COLU_SIZE][PARAM_LENGTH];
    pamnod->attri = split_pamvu_colum(parm_arra, conte);
    if (parse_pamvu_colum(pamnod, parm_arra))
        return -1;
    PRIN_parm_node(pamnod);
    //
    return 0x00;
}

// test<[xx=8 int, ax int], [cx int] auto, tst(xx), tpp(ax)>
// role <[role_type uint8, role_name char(32), priv_array char(1024)]>

static int split_type_size(uint32 *potyp, uint32 *size, char *conte) {
    char type[PAMTYP_LENGTH];
    //
    char *toksp = strchr(conte, '(');
    if (!toksp) {
        strcpy(type, conte);
        kill_blank(type);
        KV_STIN_EQUA(potyp[0x00], ostyp_potyp_dict, type)
        size[0x00] = 0x00;
        return 0x00;
    }
    //
    char *tokep = strchr(toksp + 0x01, ')');
    if (!tokep) return -1;
    strzcpy(type, conte, toksp - conte);
    kill_blank(type);
    KV_STIN_EQUA(potyp[0x00], ostyp_potyp_dict, type)
            //
            char size_stri[PAMTYP_LENGTH];
    strzcpy(size_stri, toksp + 0x01, tokep - toksp - 0x01);
    kill_blank(size_stri);
    size[0x00] = atoi(size_stri);
    //
    return 0x00;
}

int conv_bind_type(char *name, uint32 *potyp, uint32 *size, char *conte) {
    // OSEVPF("bp conte:|%s| ", conte);
    char *matok = strchr(conte, '=');
    if (matok) {
        for (; conte != matok && ' ' == matok[-1]; --matok);
        if (PARAM_LENGTH <= (matok - conte))
            return -1;
        strzcpy(name, conte, matok - conte);
        ++matok;
        for (; ' ' == matok[0x00]; ++matok);
        matok = strchr(matok, ' ');
        for (; ' ' == matok[0x00]; ++matok);
        // strcpy(type, matok);
        split_type_size(potyp, size, matok);
    } else {
        matok = strchr(conte, ' ');
        if (!matok) return -1;
        if (PARAM_LENGTH <= (matok - conte))
            return -1;
        strzcpy(name, conte, matok - conte);
        for (; ' ' == matok[0x00]; ++matok);
        // strcpy(type, matok);
        split_type_size(potyp, size, matok);
    }
    // OSEVPF("varia:|%s| lv2nod:|%s| \n", varia, lv2nod);
    return 0x00;
}

//
// ax=8 int => int ax
// ax char(16) => int ax[16]

static char *split_type_valu(char *type, char *valu, char *conte) {
    char *tvtok = strlchr(conte);
    //
    if (')' == tvtok[0x00]) {
        for (; conte != tvtok && '(' != tvtok[0x00]; --tvtok);
        if (conte == tvtok) return NULL;
        for (tvtok--; conte != tvtok && ' ' == tvtok[0x00]; --tvtok);
    }
    for (; conte != tvtok && ' ' != tvtok[0x00]; --tvtok);
    if (conte == tvtok) return NULL;
    strzcpy(valu, conte, tvtok - conte);
    strcpy(type, ++tvtok);
    //
    return conte;
}

static void conte_type_valu(char *conte, char *type, char *valu, char *size) {
    conte = lscpy(conte, type);
    conte = lccpy(conte, ' ');
    conte = lscpy(conte, valu);
    if (size[0x00]) {
        conte = lccpy(conte, '[');
        conte = lscpy(conte, size);
        lccpy(conte, ']');
    }
}

static void split_valu(char *valu) {
    char *vatok = strchr(valu, '=');
    if (vatok) vatok[0x00] = '\0';
}

static void split_type(char *size, char *type) {
    char *toksp = strchr(type, '(');
    if (toksp) {
        MK_ZERO(toksp);
        char *tokep = strchr(++toksp, ')');
        strzcpy(size, toksp, tokep - toksp);
    } else MK_ZERO(size);
}

// "CHAR" "STRI"

static int8_t check_type(char *prop_type) {
    if (!strcasecmp(prop_type, "byte"))
        return COLU_BYTE;
    else if (!strcasecmp(prop_type, "char"))
        return COLU_CHAR;
    else if (!strcasecmp(prop_type, "string"))
        return COLU_STRI;
    return COLU_NUMB;
}

static int conv_node_styl_decl(char *nodat) {
    char type[PARAM_LENGTH], valu[PARAM_LENGTH];
    char size[PARAM_LENGTH];
    //
    if (!split_type_valu(type, valu, nodat))
        return -1;
    split_valu(valu);
    // OSEVPF("1 type:|%s| valu:|%s|\n", type, valu);
    split_type(size, type);
    KV_STST_COPY(type, ostyp_clang_dict, type);
    // OSEVPF("2 type:|%s| valu:|%s| size:|%s|\n", type, valu, size);
    conte_type_valu(nodat, type, valu, size);
    //
    return 0x00;
}

//

int conv_clas_decl(char (*lv2p_prop)[PARAM_LENGTH]) {
    for (; '\0' != (*lv2p_prop)[0x00]; ++lv2p_prop) {
        // OSEVPF("1 lv2p_prop:|%s|\n", lv2p_prop[0x00]);
        if (conv_node_styl_decl(lv2p_prop[0x00]))
            return -1;
        // OSEVPF("2 lv2p_prop:|%s|\n", lv2p_prop[0x00]);
    }
    return 0x00;
}

int conv_lv2p_decl(lv2p_prop *l2_nod) {
    for (; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod) {
        // OSEVPF("1 l2_nod->decla:|%s|\n", l2_nod->decla);
        if (conv_node_styl_decl(l2_nod->decla))
            return -1;
        // OSEVPF("2 l2_nod->decla:|%s|\n", l2_nod->decla);
    }
    return 0x00;
}

// test<[xx=8 int, ax int], [cx int] auto, tst(xx), tpp(ax)>

static int conv_node_styl_cons(char *nodat) {
    // OSEVPF("bp conte:|%s| ", conte);
    char *matok = strchr(nodat, '=');
    if (matok) {
        for (; nodat != matok && ' ' == matok[-1]; --matok);
        MK_ZERO(matok);
    } else {
        matok = strchr(nodat, ' ');
        if (!matok) return -1;
        MK_ZERO(matok);
    }
    // OSEVPF("varia:|%s| lv2nod:|%s| \n", varia, lv2nod);
    return 0x00;
}

void conv_lv2p_cons(char (*lv2p_prop)[PARAM_LENGTH]) {
    for (; '\0' != (*lv2p_prop)[0x00]; ++lv2p_prop) {
        conv_node_styl_cons(lv2p_prop[0x00]);
        // OSEVPF("lv2p_prop[inde]:|%s|\n", lv2p_prop[inde]);
    }
}

//

int crea_lv2p_colu(colum *colu_data, lv2p_prop *l2_nod) {
    // OSEVPF("[FUNC]:crea_lv2p_colu\n");
    char prop_type[PARAM_LENGTH];
    for (; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod, ++colu_data) {
        if (!split_type_valu(prop_type, colu_data->name, l2_nod->decla))
            return -1;
        split_valu(colu_data->name);
        // OSEVPF("1 l2_nod->decla:|%s| type:|%s| colu_data->name:|%s|\n", l2_nod->decla, prop_type, colu_data->name);
        split_type(colu_data->size, prop_type);
        colu_data->type = check_type(prop_type);
        // OSEVPF("2 colu_data->name:|%s| size:|%s| type:%d\n", colu_data->name, colu_data->size, colu_data->type);
    }
    colu_data->type = COLU_END;
    return 0x00;
}

// trans-serve
// out invoke param type
// (a int, b int)

int const_oinvk_pmtyp(char *fmtsop, char *line_oivk) { // construct fmtsop
    char ostyp[PAMTYP_LENGTH] = {"\0"};
    // OSEVPF("line_oivk:|%s|\n", line_oivk);
    unsigned int inde = 0x00;
    if ((line_oivk = split_void(line_oivk))) {
        line_oivk = split_oinvk(ostyp, line_oivk);
        for (; line_oivk && (PARAM_COUNT >= inde); ++inde) {
            // OSEVPF("line_oivk:|%s|\n", line_oivk);
            fmtsop = ostyp_format_char(fmtsop, ostyp);
            // OSEVPF("prop_type:|%s| fmtsop:|%s|\n", prop_type, fmtsop);
            line_oivk = split_oinvk(ostyp, line_oivk);
        }
    } else MK_ZERO(fmtsop);
    //
    return 0x00;
}

// (a int, b int) int
// (a int, int, c int) int

static int const_oinvk_fmtsp(char *fmtsop, char *line_oivk) { // construct fmtsop
    char ostyp[PAMTYP_LENGTH] = {"\0"};
    // OSEVPF("line_oivk:|%s|\n", line_oivk);
    unsigned int inde = 0x00;
    if ((line_oivk = split_void(line_oivk))) {
        line_oivk = split_oinvk_iden(ostyp, line_oivk);
        for (; line_oivk && (PARAM_COUNT >= inde); ++inde) {
            // OSEVPF("line_oivk:|%s|\n", line_oivk);
            fmtsop = ostyp_format_char(fmtsop, ostyp);
            // OSEVPF("prop_type:|%s| fmtsop:|%s|\n", prop_type, fmtsop);
            line_oivk = split_oinvk_iden(ostyp, line_oivk);
        }
    } else MK_ZERO(fmtsop);
    //
    return 0x00;
}

// trans-serve
// ident = taat:tpp<(x int), (a int)int>
// ident = taat:tpp(a int, int) int

int conv_oinvk_fmtsp(char *fmtsop, char *ident) {
    // OSEVPF("ident:|%s|\n", ident);
    if (!strchr(ident, '<'))
        return const_oinvk_fmtsp(fmtsop, ident);
    //
    char line_oivk[LVON_LENGTH];
    // -1:error 0x00:inn_out 0x01:inn 0x02:out
    int iotyp = split_oinvk_head(line_oivk, ident);
    // OSEVPF("iotyp = %d line_oivk:|%s|\n", iotyp, line_oivk);
    if ((-1 == iotyp) || (0x01 == iotyp))
        return -1;
    const_oinvk_pmtyp(fmtsop, line_oivk);
    return 0x00;
}

// (a int, b int) int
// (a int, int, c int) int

static int const_oinvk_fmtsr(char *retype, char *line_oivk) { // construct return type
    // OSEVPF("line_oivk:|%s|\n", line_oivk);
    line_oivk = strchr(line_oivk, '(');
    if (!line_oivk) return -1;
    line_oivk = strchr(line_oivk, ')');
    if (!line_oivk) return -1;
    ++line_oivk;
    PASS_BLANK(line_oivk);
    //
    char *tokep = 0x01 + line_oivk;
    for (; ' ' != tokep[0x00] && '\0' != tokep[0x00]; ++tokep);
    strzcpy(retype, line_oivk, tokep - line_oivk);
    //
    return 0x00;
}

// ident = taat:tpp<(x int), (a int)int>
// ident = taat:tpp(a int, int) int

int conv_oinvk_retyp(char *ident) {
    // OSEVPF("ident:|%s|\n", ident);
    char retype[PAMTYP_LENGTH];
    if (!strchr(ident, '<')) {
        const_oinvk_fmtsr(retype, ident);
        return const_retype_value(retype);
    }
    // -1:error 0x00:inn_out 0x01:inn 0x02:out
    int iotyp = split_oinvk_retyp(retype, ident);
    // OSEVPF("iotyp = %d line_oivk:|%s|\n", iotyp, line_oivk);
    if ((-1 == iotyp) || (0x01 == iotyp))
        return -1;
    return const_retype_value(retype);
}

// ident = taat:tpp<(x int), (a int)int>

int conv_oinvk_decla(char *fmtsop, char *decla) {
    char line_oivk[LVON_LENGTH];
    // -1:error 0x00:inn_out 0x01:inn 0x02:out
    int iotyp = split_oinvk_head(line_oivk, decla);
    if ((-1 == iotyp) || (0x01 == iotyp))
        return -1;
    const_oinvk_pmtyp(fmtsop, line_oivk);
    return 0x00;
}

//

int conv_oinvk_data(char (*oivk_data)[PARAM_LENGTH], char *line_oivk) {
    pamv_node pamnod;
    // OSEVPF("line_oivk:|%s|\n", line_oivk);
    char conte[PARAM_LENGTH];
    unsigned int inde = 0x00;
    if ((line_oivk = split_void(line_oivk))) {
        for (; ('\0' != line_oivk[0x00]) && (PARAM_COUNT >= inde); ++inde, ++oivk_data) {
            // OSEVPF("line_oivk:|%s|\n", line_oivk);
            line_oivk = split_oinvk_node(conte, line_oivk);
            if (!line_oivk) break;
            // OSEVPF("ex oivk_data:|%s|\n", conte);
            conv_oinvk_pamvs(&pamnod, conte);
            filli_parms_oinvk(oivk_data[0x00], &pamnod);
            // OSEVPF("+++ conve_para parm:|%s| pars:|%s| nodat:|%s|\n", parm, pars, nodat);
            // OSEVPF("oivk_data[inde]:|%s|\n", oivk_data[inde]);
        }
    }
    MK_ZERO(oivk_data[0x00]);
    //
    return 0x00;
}

//

int conv_ibind_type(char *fmtsip, char *ibin_decl) {
    char ostyp[PAMTYP_LENGTH] = {"\0"};
    // OSEVPF("ibin_decl:|%s|\n", ibin_decl);
    unsigned int inde = 0x00;
    if ((ibin_decl = split_void(ibin_decl))) {
        ibin_decl = split_oinvk(ostyp, ibin_decl);
        for (; ibin_decl && (PARAM_COUNT >= inde); ++inde) {
            // OSEVPF("ibin_decl:|%s|\n", ibin_decl);
            fmtsip = ostyp_format_char(fmtsip, ostyp);
            // OSEVPF("prop_type:|%s| fmtsip:|%s|\n", prop_type, fmtsip);
            ibin_decl = split_oinvk(ostyp, ibin_decl);
        }
    } else MK_ZERO(fmtsip);
    //
    return 0x00;
}

//

int conv_ibind_decla(char *fmtsip, char *meth_decl) {
    char ibind_decl[LVON_LENGTH];
    // -1:error 0x00:inn_out 0x01:inn 0x02:out
    int iotyp = split_ibind_head(ibind_decl, meth_decl);
    if ((-1 == iotyp) || (0x02 == iotyp))
        return -1;
    conv_ibind_type(fmtsip, ibind_decl);
    return 0x00;
}

//

#define FIND_POTYP_NONE(POTYP, ARRAY, NAME) { \
    lv2p_prop *l2_nod = ARRAY; \
    for(; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod) \
        if(!strcmp(NAME, l2_nod->name)) break; \
    POTYP = l2_nod->potyp; \
}

int lv2pd_ibind_fmtsp(char *fmtsip, lv2p_prop *lv2nod, char **pamvp) {
    if (!pamvp[0x00]) {
        MK_ZERO(fmtsip);
        return 0x00;
    }
    // 
    DATA_TYPE prop_type;
    for (; pamvp[0x00]; ++pamvp) {
        FIND_POTYP_NONE(prop_type, lv2nod, pamvp[0x00]);
        // OSEVPF("prop_type:|%s|, pamvp[0x00]:|%s|\n", prop_type, pamvp[0x00]);
        fmtsip = lccpy(fmtsip, potyp_fmtst_tab[prop_type]);
    }
    //
    return 0x00;
}
