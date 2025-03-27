
#include "cstri_utili.h"
#include "conve_utili.h"

#include "../../debug_funct_sh.h"

// (a int, b int)
// (a int, int, c int)

static int conv_oinvk_fmts(char *fmtst, char *line_oivk) {
    char ostyp[PAMTYP_LENGTH] = {"\0"};
    // OSEVPF("line_oivk:|%s|\n", line_oivk);
    unsigned int inde = 0x00;
    if ((line_oivk = split_void(line_oivk))) {
        line_oivk = split_oinvk_iden(ostyp, line_oivk);
        for (; line_oivk && (PARAM_COUNT >= inde); ++inde) {
            // OSEVPF("line_oivk:|%s|\n", line_oivk);
            fmtst = ostyp_format_char(fmtst, ostyp);
            // OSEVPF("prop_type:|%s| fmtst:|%s|\n", prop_type, fmtst);
            line_oivk = split_oinvk_iden(ostyp, line_oivk);
        }
    } else MK_ZERO(fmtst);
    //
    return 0x00;
}

// trans-serve
// out invoke param type
// (a int, b int)

int conv_oinvk_type(char *fmtst, char *line_oivk) {
    char ostyp[PAMTYP_LENGTH] = {"\0"};
    // OSEVPF("line_oivk:|%s|\n", line_oivk);
    unsigned int inde = 0x00;
    if ((line_oivk = split_void(line_oivk))) {
        line_oivk = split_oinvk(ostyp, line_oivk);
        for (; line_oivk && (PARAM_COUNT >= inde); ++inde) {
            // OSEVPF("line_oivk:|%s|\n", line_oivk);
            fmtst = ostyp_format_char(fmtst, ostyp);
            // OSEVPF("prop_type:|%s| fmtst:|%s|\n", prop_type, fmtst);
            line_oivk = split_oinvk(ostyp, line_oivk);
        }
    } else MK_ZERO(fmtst);
    //
    return 0x00;
}

// trans-serve
// ident = taat:tpp<(x int), (a int)int>
// ident = taat:tpp(a int, int) int

int conv_oinvk_ident(char *fmtst, char *ident) {
    // OSEVPF("ident:|%s|\n", ident);
    if (!strchr(ident, '<'))
        return conv_oinvk_fmts(fmtst, ident);
    //
    char line_oivk[LVON_LENGTH];
    // -1:error 0x00:inn_out 0x01:inn 0x02:out
    int iotyp = split_oinvk_head(line_oivk, ident);
    // OSEVPF("iotyp = %d line_oivk:|%s|\n", iotyp, line_oivk);
    if ((-1 == iotyp) || (0x01 == iotyp))
        return -1;
    conv_oinvk_type(fmtst, line_oivk);
    return 0x00;
}

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

//

static int conv_bind_type(char *name, uint32 *potyp, uint32 *size, char *conte) {
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
        for (notok = node_cont; LVTNOD_COUNT > inde; ++inde, ++lv2nod) {
            notok = split_prope(parms, notok);
            if (INVAL_POINT == notok)
                return -1;
            if (conv_bind_type(lv2nod->name, &lv2nod->potyp, &lv2nod->size, parms))
                return -1; // todo: lv2nod->potyp lv2nod->size 
            // OSEVPF("name:|%s| type:|%s|\n", lv2nod[inde].name, lv2nod[inde].type);
        }
    }
    lv2nod->access = ACCE_COTRL_INVAL;
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

//

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
#define CONST_TYPE_TOK "int"
#define CHECK_CONST_TYPE(const_type) strcmp(CONST_TYPE_TOK, const_type)

// check inner invoke argument data type

int valid_metho_legal(char *lev1_cont, char *lv2p_cont, int norma_const) {
    char coin_metho[LVON_LENGTH];
    char lev1n[LVON_LENGTH];
    // OSEVPF("norma_const:%d\n", norma_const);
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

// trans-serve

/*
static int conv_oinvk_pamvs(pamv_node *pamnod, char *conte) {
    char parm_arra[PARM_COLU_SIZE][PARAM_LENGTH];
    pamnod->attri = split_pamvu_colum(parm_arra, conte);
    if (parse_pamvu_colum(pamnod, parm_arra))
        return -1;
    // PRIN_parm_node(pamnod);
    //
    return 0x00;
}
 */

#ifdef _DEBUG
/*
static const struct stsi_node vari_valu_dict[] = {
    {"int", "int", 0x00},
    {"unsigned int", "uint", 0x00},
    {"short", "short", 0x00},
    {"unsigned short", "ushort", 0x00},
    {"long", "long", 0x00},
    {"unsigned long", "ulong", 0x00},
    {"char", "char", 0x00},
    {"unsigned char", "uchar", 0x00},
    {"float", "float", 0x00},
    {"double", "double", 0x00},
    {"char []", "strcpy", 0x01},
    {"char *", "strcpy", 0x01},
    {NULL, NULL, -1}
};
 */
#endif

int conv_oinvk_pamvs(char *parm, char *data) {
    char *tokep = strchr(data, ' ');
    parm = lscpy(parm, tokep + 0x01);
#ifdef _DEBUG
    // char *value;
    // int type;
    // KVV_STSI_EQUA(value, type, vari_valu_dict, parm)
    // CLIEPF("+++ conve_para parm:|%s| value:|%s| type:|%d|\n", parm, value, type);
#endif
    parm = lccpy(parm, ' ');
    lszcpy(parm, data, tokep - data);
    // CLIEPF("+++ conve_para parm:|%s| data:|%s|\n", parm, data);
    return 0x00;
}

//

/*

#define ASSI_BYTE_TOK "memcpy" 
#define ASSI_CHAR_TOK "strcpy"

//

static void filli_pamvu_text(OUT char *parm, OUT char *pars, pamv_node *pamnod, char *notok) {
    char *value;
    KV_STST_EQUA(value, ostyp_clang_dict, pamnod->type);
    char *last_str = lscpy(parm, value);
    last_str = lccpy(last_str, ' ');
    last_str = lscpy(last_str, pamnod->name);
    if (PARM_ARRAY & pamnod->attri) lsprif(last_str, "[%s]", pamnod->array);
    // OSEVPF("parms, [0]:|%d| [1]:|%d|\n", *((int *) (parms[0x00] + 0x01)), ((int *) (parms[0x01] + 0x01))[0x00]);
    if (PARM_DEFAU & pamnod->attri) {
        if (PARM_NUMB & pamnod->attri) {
            last_str = lscpy(pars, pamnod->name);
            lsprif(last_str, " = ((%s*)(%s[0x00]+0x01))[0x00];", value, notok);
        } else if (PARM_BYTE & pamnod->attri) {
            last_str = lsprif(pars, "%s(%s", ASSI_BYTE_TOK, pamnod->name);
            lsprif(last_str, ", %s[0x00], %s);", notok, pamnod->array);
        } else if ((PARM_CHAR | PARM_STRZ) & pamnod->attri) {
            last_str = lsprif(pars, "%s(%s", ASSI_CHAR_TOK, pamnod->name);
            lsprif(last_str, ", %s[0x00]);", notok);
        }
    } else {
        if (PARM_NUMB & pamnod->attri) {
            last_str = lscpy(pars, pamnod->name);
            lsprif(last_str, " = ((%s*)(%s[0x00]+0x01))[0x00];", value, notok);
        } else if (PARM_BYTE & pamnod->attri) {
            last_str = lsprif(pars, "%s(%s", ASSI_BYTE_TOK, pamnod->name);
            lsprif(last_str, ", %s[0x00], %s);", notok, pamnod->array);
        } else if ((PARM_CHAR | PARM_STRZ) & pamnod->attri) {
            last_str = lsprif(pars, "%s(%s", ASSI_CHAR_TOK, pamnod->name);
            lsprif(last_str, ", %s[0x00]);", notok);
        }
    }
}

// trans-serve
#define PARM_TOK    "valu"

int conv_oinvk_data(char (*oivk_data)[PARAM_LENGTH], char (*oik_dat)[PARAM_LENGTH], char *line_oivk) {
    pamv_node pamnod;
    char *last_str;
    // OSEVPF("fmtsp:|%s|\n", fmtsp);
    // OSEVPF("line_oivk:|%s|\n", line_oivk);
    char conte[PARAM_LENGTH];
    unsigned int inde = 0x00;
    if ((last_str = split_void(line_oivk))) {
        for (; ('\0' != last_str[0x00]) && (PARAM_COUNT >= inde); ++inde, ++oivk_data, ++oik_dat) {
            // OSEVPF("last_str:|%s|\n", last_str);
            last_str = split_oinvk_node(conte, last_str);
            if (!last_str) break;
            // OSEVPF("ex oivk_data:|%s|\n", conte);
            conv_oinvk_pamvs(&pamnod, conte);
            filli_pamvu_text(oivk_data[0x00], oik_dat[0x00], &pamnod, PARM_TOK);
            // OSEVPF("+++ conve_para parm:|%s| pars:|%s| data:|%s|\n", parm, pars, data);
            // OSEVPF("oivk_data[inde]:|%s|\n", oivk_data[inde]);
        }
    }
    MK_ZERO(oivk_data[0x00]);
    MK_ZERO(oik_dat[0x00]);
    //
    return 0x00;
}
 */

int conv_oinvk_data(char (*oivk_data)[PARAM_LENGTH], char *line_oivk) {
    char *last_str;
    // CLIEPF("conv_oinvk_data line_oivk:|%s|\n", line_oivk);
    char conte[PARAM_LENGTH];
    unsigned int inde = 0x00;
    if ((last_str = split_void(line_oivk))) {
        for (; ('\0' != last_str[0x00]) && (PARAM_COUNT >= inde); ++inde, ++oivk_data) {
            // CLIEPF("last_str:|%s|\n", last_str);
            last_str = split_oinvk_ext(conte, last_str);
            if (!last_str) return -1;
            // CLIEPF("ex oivk_data:|%s|\n", conte);
            conv_oinvk_pamvs(oivk_data[0x00], conte);
            // CLIEPF("oivk_data[inde]:|%s|\n", oivk_data[inde]);
        }
    }
    MK_ZERO(oivk_data[0x00]);
    //
    return 0x00;
}

//
#define CONST_TYPE_TOK "int"
#define CHECK_CONST_TYPE(const_type) strcmp(CONST_TYPE_TOK, const_type)

// check inner invoke argument data type

static char *split_type_valu(char *type, char *valu, char *conte) {
    char *cotok = strlchr(conte);
    //
    if (')' == cotok[0x00]) {
        for (; conte != cotok && '(' != cotok[0x00]; --cotok);
        if (conte == cotok) return NULL;
        for (--cotok; conte != cotok && ' ' == cotok[0x00]; --cotok);
    }
    for (; conte != cotok && ' ' != cotok[0x00]; --cotok);
    if (conte == cotok) return NULL;
    strcpy(type, cotok);
    strzcpy(valu, conte, cotok - conte);
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

//

static int conv_node_styl_decl(char *data) {
    char type[PARAM_LENGTH], valu[PARAM_LENGTH];
    char size[PARAM_LENGTH];
    //
    if (!split_type_valu(type, valu, data))
        return -1;
    // CLIEPF("1 type:|%s| valu:|%s|\n", type, valu);
    split_valu(valu);
    split_type(size, type);
    KV_STST_COPY(type, ostyp_clang_dict, type)
    // CLIEPF("2 type:|%s| valu:|%s| size:|%s|\n", type, valu, size);
    conte_type_valu(data, type, valu, size);
    //
    return 0x00;
}

//

int conv_clas_decl(char (*lv2p_prop)[PARAM_LENGTH]) {
    for (; '\0' != (*lv2p_prop)[0x00]; ++lv2p_prop) {
        if (conv_node_styl_decl(lv2p_prop[0x00]))
            return -1;
        // CLIEPF("lv2p_prop[inde]:|%s|\n", lv2p_prop[inde]);
    }
    return 0x00;
}

// test<[xx=8 int, ax int], [cx int] auto, tst(xx), tpp(ax)>

static int conv_node_styl_cons(char *data) {
    // CLIEPF("bp conte:|%s| ", conte);
    char *datok = strchr(data, '=');
    if (datok) {
        for (; data != datok && ' ' == datok[-1]; --datok);
        MK_ZERO(datok);
    } else {
        datok = strchr(data, ' ');
        if (!datok) return -1;
        MK_ZERO(datok);
    }
    // CLIEPF("varia:|%s| lv2nod:|%s| \n", varia, lv2nod);
    return 0x00;
}

int conv_lv2p_cons(char (*lv2p_prop)[PARAM_LENGTH]) {
    for (; '\0' != (*lv2p_prop)[0x00]; ++lv2p_prop) {
        conv_node_styl_cons(lv2p_prop[0x00]);
        // CLIEPF("lv2p_prop[inde]:|%s|\n", lv2p_prop[0x00]);
    }
    return 0x00;
}

//

char *conv_decla(char *decla, char *conte) {
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
    //
    return decla;
}



