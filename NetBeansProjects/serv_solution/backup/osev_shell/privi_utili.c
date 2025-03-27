
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "commo_macro.h"
#include "osev_datyp.h"

#include "privi_utili.h"
#include "debug_funct_sh.h"

//
// "12p34p" "1,2+,3,4+" "1 2p 3 4p"

static const struct stui_node level_value_dict[] = {
    {"1", SBLV_ONE},
    {"2+", SBLV_TWOP},
    {"3", SBLV_THRE},
    {"4+", SBLV_FOUP},
    {NULL, 0x00}
};

static const struct stui_node level_alpha_dict[] = {
    {"1", SBLV_ONE},
    {"2p", SBLV_TWOP},
    {"3", SBLV_THRE},
    {"4p", SBLV_FOUP},
    {NULL, 0x00}
};

//

static char *leve_alph(char *alph_valu, char *stri) {
    if (isdigit(stri[0x00])) alph_valu[0x00] = stri[0x00];
    else return NULL;
    if (isalpha((stri + 0x01)[0x00])) {
        alph_valu[0x01] = (++stri)[0x00];
    } else alph_valu[0x01] = '\0';
    //
    return stri;
}

// "12p34p" "12+34+"
// "1 2p 3 4p" "1 2+ 3 4+"
// "1,2p,3,4p" "1,2+,3,4+"

uint32 gengr_level(char *leve_stri) {
    // CLIEPF("leve_stri:|%s|\n", leve_stri);
    char alph_stri[0x03];
    uint32 lev_valu, priv_code = 0x00;
    //
    alph_stri[0x02] = '\0';
    char *lstok = leve_stri;
    for (; lstok[0x00]; ++lstok) {
        if (' ' == lstok[0x00] || ',' == lstok[0x00])
            continue;
        if (!(lstok = leve_alph(alph_stri, lstok)))
            return 0x00;
        // CLIEPF("alph_stri:|%s|\n", alph_stri);
        KV_STUI_EQUA(lev_valu, level_value_dict, alph_stri)
        if (!lev_valu) KV_STUI_EQUA(lev_valu, level_alpha_dict, alph_stri)
            if (!lev_valu) return 0x00;
        //
        if (SBLV_ONE & lev_valu)
            priv_code |= (BLVO_EXECU | BLVO_WRITE | BLVO_READ);
        else if (SBLV_TWOP & lev_valu)
            priv_code |= (BLVT_EXECU | BLVT_WRITE | BLVT_READ);
        else if (SBLV_THRE & lev_valu)
            priv_code |= (BLVH_EXECU | BLVH_WRITE | BLVH_READ);
        else if (SBLV_FOUP & lev_valu)
            priv_code |= (BLVF_EXECU | BLVF_WRITE | BLVF_READ);
    }
    //
    CLIEPF("priv_code:|%08X|\n", priv_code);
    return priv_code;
}

//
// "f7e6fa4bd931435c03000000:1,2p,3,4p"
#define INVA_DIST   -1
#define ONLY_BASE   0x01
#define BASE_LEVE   0x02
#define BASE_CONTA  0x03

static void take_symbol(char *symbol, char *stri) {
    char *toksp = pass_blank(stri);
    if (toksp) {
        char *tokep = strchr(toksp + 0x01, ' ');
        if (tokep) tokep[0x00] = '\0';
        strcpy(symbol, toksp);
    }
}

// "12p34p" "12+34+"
// "1 2p 3 4p" "1 2+ 3 4+"
// "1,2p,3,4p" "1,2+,3,4+"

static inline int valid_effec_blevs(char *lvco_str) {
    char *lstok = lvco_str;
    while (lstok[0x00]) {
#ifdef _DEBUG
        printf("lstok:|%s|\n", lstok);
#endif // _DEBUG
        switch (lstok[0x00]) {
            case '1':
                break;
            case '2':
                ++lstok;
                if ('+' != lstok[0x00] && 'p' != lstok[0x00])
                    return -1;
                break;
            case '3':
                break;
            case '4':
                ++lstok;
                if ('+' != lstok[0x00] && 'p' != lstok[0x00])
                    return -1;
                break;
            default:
                return -1;
                break;
        }
        for (++lstok; lstok[0x00] && (' ' == lstok[0x00] || ',' == lstok[0x00]); ++lstok);
    }
    //
    return 0x00;
}

static uint32 levcon_type(char *lvco_str) {
    char *pbtok = pass_blank(lvco_str);
    if (!pbtok) return INVA_DIST;
    if (isalpha(pbtok[0x00]))
        return BASE_CONTA;
    if (isdigit(pbtok[0x00])) {
        if (valid_effec_blevs(pbtok))
            return BASE_CONTA;
        return BASE_LEVE;
    }
    return INVA_DIST;
}

// dist_type

static uint32 split_disti(char *basen, char *levcon, char *dist_iden) {
    char *ditok;
    //
    if ((ditok = strchr(dist_iden, ':'))) { // "odb:1" "odb:2p" "odb:contain"
        ditok[0x00] = '\0';
        take_symbol(basen, dist_iden); // basen=todb
        //
        switch (levcon_type(++ditok)) {
            case BASE_LEVE:
                strcpy(levcon, ditok);
                return BASE_LEVE;
                break;
            case BASE_CONTA:
                take_symbol(levcon, ditok);
                return BASE_CONTA;
                break;
            default:
                return INVA_DIST;
                break;
        }
    } else return ONLY_BASE; // todb
    //
    return INVA_DIST;
}

// "osev:privile"
// "odb:privile"
// "odb:1" 
// "odb:2p" 
// "odb:contain"
static osv_str_t OSEV_DEFAULT_TOK = osv_stri("osev");
static osv_str_t BASE_DEFAULT_TOK = osv_stri("odb");

uint32 parse_disti_scope(OUT uint32 *lev_valu, char *dist_iden, const char *objide) {
    CLIEPF("[FUNC]:parse_disti_scope\n");
    CLIEPF("dist_iden:|%s| objide:|%s|\n", dist_iden, objide);
    uint32 scop_valu = INVA_PRIVI;
    //
    char basen[BASE_LENGTH], levcon[OBJN_LENGTH];
    if (!strncmp(OSEV_DEFAULT_TOK.data, objide, OSEV_DEFAULT_TOK.slen)) {
        // osev:privile
        scop_valu = SCOP_OSEV;
    } else if (!strncmp(BASE_DEFAULT_TOK.data, objide, BASE_DEFAULT_TOK.slen)) {
        // odb:privile
        switch (split_disti(basen, levcon, dist_iden)) {
            case ONLY_BASE: // "todb" "odb"
                CLIEPF("ONLY_BASE\n");
                scop_valu = SCOP_BASE;
                lev_valu[0x00] = SBLV_ONE | SBLV_TWOP | SBLV_THRE | SBLV_FOUP;
                break;
            case BASE_LEVE: // "odb:2p"
                CLIEPF("BASE_LEVE\n");
                scop_valu = SCOP_BASE;
                strcpy(dist_iden, basen);
                lev_valu[0x00] = gengr_level(levcon);
                if (!lev_valu[0x00]) return INVA_PRIVI;
                break;
            case BASE_CONTA: // "odb:contain"
                CLIEPF("BASE_CONTA\n");
                sprintf(dist_iden, "%s:%s", basen, levcon);
                scop_valu = SCOP_CONT;
                lev_valu[0x00] = INVA_SBLV;
                break;
            default:
                _LOG_WARN("default: dist_type");
                scop_valu = INVA_PRIVI;
                lev_valu[0x00] = INVA_SBLV;
                break;
        }
    }
    //
    return scop_valu;
}

// admin

static const struct stui_node priv_osev_dict[] = {
    {"ALL_PRIVILE", OBJE_SERV_PALL}, //
    {"COMND", OVBP_COMND}, // 
    {"STATU", OVBP_STATU}, // 
    {"PRIVI", OVBP_PRIVI}, // 
    {"CLUST", OVBP_CLUST}, // 
    {NULL, 0x00}
};

//

static const struct stui_node priv_base_dict[] = {
    {"ALL_PRIVILE", BLVP_EXECU | BLVP_WRITE | BLVP_READ}, //
    {"EXECU", BLVP_EXECU}, // 
    {"WRITE", BLVP_WRITE}, // 
    {"READ", BLVP_READ}, // 
    {NULL, 0x00}
};

static const struct stui_node priv_cont_dict[] = {
    {"ALL_PRIVILE", QUEN_METH_PALL}, //
    // level three
    {"CPOST", ENTP_POST}, //
    {"CECHO", ENTP_ECHO}, //
    {"CCREA", ENTP_CREAT}, // 
    {"CDROP", ENTP_DROP}, //
    {"CSEAR", ENTP_SEARO}, // 
    {"CUPDA", ENTP_UPDAT}, // 
    {"CINSE", ENTP_INSER}, //
    {"CINVO", ENTP_INVOK}, // 
    // level foup
    {"QPOST", QUEP_POST}, //
    {"QECHO", QUEP_ECHO}, //
    {"QCREA", QUEP_CREAT}, // 
    {"QDROP", QUEP_DROP}, //
    {"QUPDA", QUEP_UPDAT}, // 
    {"QINSE", QUEP_INSER}, // 
    {"QSEAR", QUEP_SEARQ}, // 
    {"QINVO", QUEP_INVOK}, // 
    {"QFACT", QUEP_FACTO}, // 
    {NULL, 0x00}
};

static char *privi_actio(char *priv_stri, char *privi) {
    char *toksp = privi;
    for (; '|' == toksp[0x00] || ' ' == toksp[0x00] || ',' == toksp[0x00]; ++toksp);
    if ('\0' == toksp[0x00])
        return NULL;
    char *tokep = strpbrk(toksp + 0x01, "| ,");
    if (tokep) strzcpy(priv_stri, toksp, tokep - toksp);
    else tokep = escpy(priv_stri, toksp);
    //
    return tokep;
}

uint32 parse_osev_privi(char *privi) {
    CLIEPF("[FUNC]:parse_osev_privi\n");
    uint32 priv_valu = INVA_PRIVI;
    char priv_stri[PARAM_LENGTH];
    //
    char *pvtok = privi;
    while ((pvtok = privi_actio(priv_stri, pvtok))) {
        PRIVI_DICTI_VALUE(priv_valu, priv_osev_dict, priv_stri)
    }
    PRIVI_DICTI_VALUE(priv_valu, priv_osev_dict, priv_stri)
            //
    return priv_valu;
}

//

uint32 parse_base_privi(char *privi) {
    CLIEPF("[FUNC]:parse_base_privi\n");
    uint32 priv_valu = INVA_PRIVI;
    char priv_stri[PARAM_LENGTH];
    //
    char *pvtok = privi;
    while ((pvtok = privi_actio(priv_stri, pvtok))) {
        PRIVI_DICTI_VALUE(priv_valu, priv_base_dict, priv_stri)
    }
    PRIVI_DICTI_VALUE(priv_valu, priv_base_dict, priv_stri)
            //
    return priv_valu;
}

uint32 parse_cont_privi(char *privi) {
    CLIEPF("[FUNC]:parse_cont_privi\n");
    uint32 priv_valu = INVA_PRIVI;
    char priv_stri[PARAM_LENGTH];
    //
    char *pvtok = privi;
    while ((pvtok = privi_actio(priv_stri, pvtok))) {
        PRIVI_DICTI_VALUE(priv_valu, priv_cont_dict, priv_stri)
    }
    PRIVI_DICTI_VALUE(priv_valu, priv_cont_dict, priv_stri)
            //
    return priv_valu;
}

//

int ochk_priv_valu(uint32 priv_valu) {
    CLIEPF("[FUNC]:ochk_priv_valu\n");
    if (~(OVBP_COMND | OVBP_STATU | OVBP_PRIVI | OVBP_CLUST) & priv_valu)
        return -1;
    //
    return 0x00;
}

//

int bchk_priv_valu(uint32 priv_valu) {
    CLIEPF("[FUNC]:bchk_priv_valu\n");
    if (~(BLVP_EXECU | BLVP_WRITE | BLVP_READ) & priv_valu)
        return -1;
    //
    return 0x00;
}

int cchk_priv_valu(uint32 priv_valu) {
    CLIEPF("[FUNC]:cchk_priv_valu\n");
    if (~QUEN_METH_PALL & priv_valu)
        return -1;
    //
    return 0x00;
}











