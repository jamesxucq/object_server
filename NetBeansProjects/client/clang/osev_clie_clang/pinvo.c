#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "function/funct_header.h"
#include "pinvo.h"


//

static char *delim_start(char *stri) {
    for (; isalnum(stri[0x00]) || ('_' == stri[0x00]); ++stri);
    return stri;
}

static char *delim_end(char *stri) {
    for (; '\0' != stri[0x00] && !isalnum(stri[0x00]); ++stri);
    return stri;
}


//  0x00:only method / command 0x01:object method
#define INVA_OLITYP             -1
#define INVOK_INSTRU_OLITYP     0x00
#define OBJE_INVOK_OLITYP       0x01
#define LEVE_INVOK_OLITYP       0x02   
#define OBJE_LEVIVK_OLITYP      0x03   

static int inst_lvikoi_type(char *space) {
    char *toksp, *tokep;
    //
    if (':' == *space) { // 0x00:only invok / command; 0x01:level invok
        toksp = delim_start(++space);
        if (!toksp) {
            if (space == toksp)
                return INVA_OLITYP;
            return INVOK_INSTRU_OLITYP; // 0x00:only invok / command
        }
        tokep = delim_end(toksp);
        if (tokep && toksp) {
            for (; tokep >= toksp; ++toksp) {
                if (':' == toksp[0x00])
                    return LEVE_INVOK_OLITYP; // 0x03:level invok
            }
        }
    } else {
        toksp = delim_start(space);
        if (!toksp) return INVOK_INSTRU_OLITYP; // 0x00:only invok / command
        tokep = delim_end(toksp);
        if (tokep && toksp) {
            for (; tokep >= toksp; ++toksp) {
                if (':' == toksp[0x00]) {
                    toksp = delim_start(tokep);
                    if (!toksp) return INVA_OLITYP;
                    tokep = delim_end(toksp);
                    if (tokep && toksp) {
                        for (; tokep >= toksp; ++toksp) {
                            if (':' == toksp[0x00])
                                return OBJE_LEVIVK_OLITYP; // 0x02:object level invok
                        }
                    }
                    return OBJE_INVOK_OLITYP; // 0x01:objide invok
                }
            }
        }
        //
    }
    //
    return INVOK_INSTRU_OLITYP;
}

static char *build_space_conte(char *obje_invk, char *coline) {
    char *toksp = coline;
    for (; '\0' != toksp[0x00] && ' ' == toksp[0x00]; ++toksp);
    //
    char *cutok = toksp;
    for (; '\0' != cutok[0x00]; ++cutok)
        if ('(' == cutok[0x00] || '<' == cutok[0x00]) break;

    //
    char *tokep = cutok;
    for (; toksp != tokep && ' ' == tokep[-1]; --tokep);
    //
    strzcpy(obje_invk, toksp, tokep - toksp);
    return cutok;
}

#define SPACE_DELIM_TOK ':'

static int check_sptok(char *start, char *end) {
    // OSEVPF("start:|%s| end:|%s|\n", start, end);
    if (start == end) return 0x00;
    else if (start && end) {
        for (; end >= start; ++start) {
            if (SPACE_DELIM_TOK == start[0x00])
                return 0x00;
        }
    }
    //
    return -1;
}

static int split_space_array(char *space_array[SPACE_COUNT], char *space) {
    char *cutok = space;
    //
    unsigned int inde = 0x00;
    for (; '\0' != cutok[0x00]; ++inde) {
        char *delisp = delim_start(cutok);
        char *deliep = delim_end(delisp);
        if (check_sptok(delisp, deliep))
            return -1;
        //
        space_array[inde] = cutok;
        MK_ZERO(delisp);
        // OSEVPF("space_array[inde]:|%s|\n", space_array[inde]);
        cutok = deliep;
    }
    space_array[inde] = NULL;
    //
    return 0x00;
}

static int creat_objide_levivk(char *objide, char *levivk, char *invok, char **space_array) {
    objide = lscpy(objide, space_array[0x00]);
    //
    char **arrp_tok = space_array + 0x01;
    char *penult_tok = arrp_tok[0x00];
    if (!penult_tok) return -1;
    char *last_tok = (++arrp_tok)[0x00];
    if (!last_tok) return -1;
    //
    for (++arrp_tok; arrp_tok[0x00]; ++arrp_tok) {
        objide = lccpy(objide, ':');
        objide = lscpy(objide, penult_tok);
        penult_tok = last_tok;
        last_tok = arrp_tok[0x00];
    }
    lscpy(levivk, penult_tok);
    lscpy(invok, last_tok);
    //
    return 0x00;
}

static char *decod_objide_levivk(char *objide, char *levivk, char *invok, char *coline) {
    char space_conte[OBJN_LENGTH + LEVE_LENGTH + LVON_LENGTH];
    char *pase_tok = build_space_conte(space_conte, coline);
    // OSEVPF("space_conte:|%s| space:|%s|\n", space_conte, space);
    //
    char *space_array[SPACE_COUNT];
    if (split_space_array(space_array, space_conte))
        return NULL;
    //
    if (creat_objide_levivk(objide, levivk, invok, space_array))
        return NULL;
    return pase_tok;
}

//

static char *split_levivk_space(char *name, char *space) {
    char *toksp, *tokep;
    //
    for (toksp = space; '\0' != toksp[0x00]; ++toksp) {
        if (' ' != toksp[0x00] && ':' != toksp[0x00])
            break;
    }
    for (tokep = toksp; '\0' != tokep[0x00]; ++tokep) {
        if (' ' == tokep[0x00] || '(' == tokep[0x00] || '<' == tokep[0x00])
            break;
    }
    //
    strzcpy(name, toksp, tokep - toksp);
    return tokep;
}

static char *split_levivk_invok(char *levivk, char *invok, char *space) {
    // CLIEPF("[FUNC] split_levivk_invok space:|%s|\n", space);
    char *toksp, *tokep;
    //
    for (toksp = space; '\0' != toksp[0x00]; ++toksp)
        if (' ' != toksp[0x00] && ':' != toksp[0x00]) break;
    for (tokep = toksp; '\0' != tokep[0x00]; ++tokep)
        if (' ' == tokep[0x00] || ':' == tokep[0x00]) break;
    strzcpy(levivk, toksp, tokep - toksp);
    //
    for (toksp = tokep; '\0' != toksp[0x00]; ++toksp)
        if (' ' != toksp[0x00] && ':' != toksp[0x00]) break;
    for (tokep = toksp; '\0' != tokep[0x00]; ++tokep)
        if (' ' == tokep[0x00] || '(' == tokep[0x00] || '<' == tokep[0x00]) break;
    strzcpy(invok, toksp, tokep - toksp);
    //
    return tokep;
}

static char *split_objide_levivk(char *objide, char *levivk, char *space) {
    // CLIEPF("[FUNC] split_objide_levivk space:|%s|\n", space);
    char *toksp, *tokep;
    //
    for (toksp = space; '\0' != toksp[0x00]; ++toksp)
        if (' ' != toksp[0x00] && ':' != toksp[0x00]) break;
    for (tokep = toksp; '\0' != tokep[0x00]; ++tokep)
        if (' ' == tokep[0x00] || ':' == tokep[0x00]) break;
    strzcpy(objide, toksp, tokep - toksp);
    //
    for (toksp = tokep; '\0' != toksp[0x00]; ++toksp)
        if (' ' != toksp[0x00] && ':' != toksp[0x00]) break;
    for (tokep = toksp; '\0' != tokep[0x00]; ++tokep)
        if (' ' == tokep[0x00] || '(' == tokep[0x00] || '<' == tokep[0x00]) break;
    strzcpy(levivk, toksp, tokep - toksp);
    //
    return tokep;
}
//

static char *split_instru(char *objide, char *levivk, char *invok, char *line_str) {
    char *pase_tok = pass_blank(line_str);
    if (!pase_tok) return NULL;
    //  0x00:only method / command 0x01:object method
    switch (inst_lvikoi_type(pase_tok)) {
        case INVOK_INSTRU_OLITYP:
            MK_ZERO(objide);
            // CLIEPF("cmd pase_tok:|%s|\n", pase_tok);
            pase_tok = split_levivk_space(levivk, pase_tok);
            // CLIEPF("cmd pase_tok:|%s|\n", pase_tok);
            break;
        case OBJE_INVOK_OLITYP:
            // CLIEPF("method pase_tok:|%s|\n", pase_tok);
            pase_tok = split_objide_levivk(objide, levivk, pase_tok);
            // CLIEPF("method pase_tok:|%s|\n", pase_tok);
            break;
        case LEVE_INVOK_OLITYP:
            MK_ZERO(objide);
            // CLIEPF("cmd pase_tok:|%s|\n", pase_tok);
            pase_tok = split_levivk_invok(levivk, invok, pase_tok);
            // CLIEPF("cmd pase_tok:|%s|\n", pase_tok);
            break;
        case OBJE_LEVIVK_OLITYP:
            pase_tok = decod_objide_levivk(objide, levivk, invok, pase_tok);
            break;
        case INVA_OLITYP:
        default:
            pase_tok = NULL;
            break;
    }
    //
    return pase_tok;
}

//

static char *next_parm(char *pamcon, char *space) {
    char *toksp, *tokep;
    char cutok;
    //
    for (toksp = space; '\0' != toksp[0x00]; ++toksp) {
        cutok = toksp[0x00];
        if (' ' != cutok && '(' != cutok && ')' != cutok && ',' != cutok && ';' != cutok && '>' != cutok)
            break;
    }
    //
    if ('"' == toksp[0x00]) {
        for (tokep = toksp + 0x01; '"' != tokep[0x00]; ++tokep)
            if ('\\' == tokep[0x00]) ++tokep;
        ++tokep;
        if ('S' == tokep[0x00] || 's' == tokep[0x00])
            ++tokep;
    } else {
        for (tokep = toksp; '\0' != tokep[0x00]; ++tokep) {
            if ('(' == tokep[0x00]) {
                int paren = 0x00;
                for (; '\0' != tokep[0x00]; ++tokep) {
                    if ('\\' == tokep[0x00]) {
                        ++tokep;
                        continue;
                    }
                    if ('(' == tokep[0x00]) {
                        ++paren;
                        continue;
                    }
                    if (')' == tokep[0x00]) {
                        --paren;
                        continue;
                    }
                    if (!paren) break;
                }
            }
            //
            cutok = tokep[0x00];
            if ('(' == cutok || ')' == cutok || ',' == cutok || ';' == cutok)
                break;
        }
    }
    strzcpy(pamcon, toksp, tokep - toksp);
    //
    for (; '\0' != tokep[0x00]; ++tokep) {
        cutok = tokep[0x00];
        if (' ' != cutok && '(' != cutok && ')' != cutok && ',' != cutok && ';' != cutok && '>' != cutok)
            break;
    }
    //
    return tokep;
}

//

static int split_instru_pamvs(const char **pamvp, char *_pline_, char *line_txt) {
    char pamcon[PARAM_LENGTH];
    // OSEVPF("[FUNC]param_parsing line_txt:|%s|\n", line_txt);
    //
    unsigned int inde = 0x00;
    for (; ('\0' != line_txt[0x00]) && PARAM_COUNT > inde; ++inde, ++pamvp) {
        line_txt = next_parm(pamcon, line_txt);
        // OSEVPF("[FUNC]param_parsing line_txt:|%s|\n", line_txt);
        if ('\0' == pamcon[0x00]) break;
        LSCPY_O(pamvp[0x00], pamcon, _pline_);
        // OSEVPF("[FUNC]param_parsing pamvp[0x00]:|%s|\n", pamvp[0x00]);
    }
    pamvp[0x00] = NULL;
    //
    return 0x00;
}

//

static unsigned long long bulid_invok_pamvs(pamstyl_t *pscon, char *pamcon) {
    // OSEVPF("[FUNC]:bulid_invok_pamvs\n");
    const char *invo_parms[PARAM_COUNT];
    char _iline_[LARGE_CONTE_SIZE];
    if (-1 == split_instru_pamvs(invo_parms, _iline_, pamcon))
        return INVA_ULOLO_VALU;
    if (-1 == pretr_functi_pamvs(invo_parms))
        return INVA_ULOLO_VALU;
    //
    unsigned long long colen = encod_list_loop(pscon->pamstyl_memo + sizeof (binary_entit), invo_parms);
    if (INVA_ULOLO_VALU == colen)
        return INVA_ULOLO_VALU;
    binary_entit *binen = (binary_entit *) pscon->pamstyl_memo;
    binen->notyp = DATY_BINARY;
    binen->colen = colen;
    pscon->colen = sizeof (binary_entit) + colen;
    //
    return pscon->colen;
}

unsigned long long parse_invok_metho(pamstyl_t *pscon, char *pamcon) {
    // OSEVPF("[FUNC]:parse_invok_metho\n");
    // OSEVPF("pamcon:|%s|\n", pamcon);
    char objide[OBJN_LENGTH];
    char inst_levivk[LVON_LENGTH];
    char inst_invok[LVON_LENGTH];
    pamcon = split_instru(objide, inst_levivk, inst_invok, pamcon);
    if (!pamcon) return INVA_ULOLO_VALU;
    // OSEVPF("objide:|%s| comd_meth:|%s|\n", objide, comd_meth);
    unsigned long long colen = strlen(objide);
    char *last_str = stri_pamstyl_ext(pscon->pamstyl_memo + sizeof (binary_entit), objide, colen);
    unsigned long long enlen = sizeof (stri_entit) + colen;
    colen = strlen(inst_levivk);
    last_str = stri_pamstyl_ext(last_str, inst_levivk, colen);
    enlen += (sizeof (stri_entit) + colen);
    //
    pamstyl_t ivk_lvhf;
    if (INVA_ULOLO_VALU == bulid_invok_pamvs(&ivk_lvhf, pamcon))
        return INVA_ULOLO_VALU;
    binary_pamstyl_naked(last_str, ivk_lvhf.pamstyl_memo, ivk_lvhf.colen);
    enlen += ivk_lvhf.colen;
    //
    binary_entit *binen = (binary_entit *) pscon->pamstyl_memo;
    binen->notyp = DATY_BINARY;
    binen->colen = enlen;
    pscon->colen = sizeof (binary_entit) + enlen;
    //
    return pscon->colen;
}

//

unsigned long long parse_qinup_entit(pamstyl_t *pscon, char *pamcon, char *fmtst) {
    // OSEVPF("[FUNC]:parse_qinup_entit\n");
    const char *qinu_parms[PARAM_COUNT];
    char _qline_[LARGE_CONTE_SIZE];
    if (-1 == split_instru_pamvs(qinu_parms, _qline_, pamcon))
        return INVA_ULOLO_VALU;
    if (-1 == pretr_functi_pamvs(qinu_parms))
        return INVA_ULOLO_VALU;
    //
    unsigned long long colen = pack_list_loop(pscon->pamstyl_memo + sizeof (binary_entit), BINA_ARRAY_LEN - sizeof (binary_entit), qinu_parms, fmtst);
    if (INVA_ULOLO_VALU == colen)
        return INVA_ULOLO_VALU;
    binary_entit *binen = (binary_entit *) pscon->pamstyl_memo;
    binen->notyp = DATY_BINARY;
    binen->colen = colen;
    pscon->colen = sizeof (binary_entit) + colen;
    //
    return pscon->colen;
}