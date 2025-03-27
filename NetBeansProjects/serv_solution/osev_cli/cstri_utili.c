#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>

#include "commo_header.h"
#include "osev_clie_clang.h"
#include "cstri_utili.h"
#include "debug_funct_sh.h"

char _runcomd_directory_[PATH_MAX];

int creat_runcomd_directory(char *comd_dire, char *leve_dire) {
    char lcomd_name[PATH_MAX + 0x01];
    sprintf(_runcomd_directory_, "%s/%s", getenv("HOME"), comd_dire);
    if (access(_runcomd_directory_, F_OK)) {
        if (mkdir(_runcomd_directory_, 0755)) {
            perror("mkdir error!");
            return -1;
        }
        sprintf(lcomd_name, "%s/%s", _runcomd_directory_, leve_dire);
        if (mkdir(lcomd_name, 0755)) {
            perror("mkdir error!");
            return -1;
        }
    }
    return 0x00;
}

char *runcomd_name(char *file_name) {
    static char rcomd_name[PATH_MAX + 0x01];
    if ('\0' == _runcomd_directory_[0x00])
        return NULL;
    sprintf(rcomd_name, "%s/%s", _runcomd_directory_, file_name);
    // CLIT_PF("[FUNC]runcomd_name:|%s|\n", rcmd_name);
    return rcomd_name;
}

char *levecomd_name(char *leve_dire, char *file_name) {
    static char lcomd_name[PATH_MAX + 0x02];
    if ('\0' == _runcomd_directory_[0x00])
        return NULL;
    sprintf(lcomd_name, "%s/%s/%s", _runcomd_directory_, leve_dire, file_name);
    // CLIT_PF("[FUNC]runcomd_name:|%s|\n", rcmd_name);
    return lcomd_name;
}

//

static char *delim_start(char *stri) {
    for (; isalnum(*stri) || ('_' == *stri); ++stri) {
        if ('\0' == *stri)
            return NULL;
    }
    return stri;
}

static char *delim_end(char *stri) {
    for (; '\0' != *stri && !isalnum(*stri); ++stri);
    return stri;
}


// INVA_OLITYP:error  INVOK_INSTRU_OLITYP:only invok / command; OBJE_INVOK_OLITYP:object invok; 
// LEVE_INVOK_OLITYP:object level invok; OBJE_LEVIVK_OLITYP:level invok
// :query // 0x00
// conne // 0x00
// objide:query // 0x01
// objide:query:echo // 0x02
// objide: // -1

int inst_lvikoi_type(char *space) {
    // CLIT_PF("[FUNC]inst_lvikoi_type space:|%s|\n", space);
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

//


#define SPACE_DELIM_TOK ':'

static int check_sptok(char *start, char *end) {
    // CLIT_PF("start:|%s| end:|%s|\n", start, end);
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

//

static int split_space_array(char *space_array[SPACE_COUNT], char *space) {
    char *satok = space;
    //
    unsigned int inde = 0x00;
    for (; '\0' != satok[0x00]; ++inde) {
        char *delisp = delim_start(satok);
        char *deliep = delim_end(delisp);
        if (check_sptok(delisp, deliep))
            return -1;
        //
        space_array[inde] = satok;
        MK_ZERO(delisp);
        // CLIT_PF("space_array[inde]:|%s|\n", space_array[inde]);
        satok = deliep;
    }
    space_array[inde] = NULL;
    //
    return 0x00;
}

static char *build_space_conte(char *obje_invk, char *coline) {
    char *toksp = coline;
    for (; '\0' != toksp[0x00] && ' ' == toksp[0x00]; ++toksp);
    //
    char *cotok = toksp;
    for (; '\0' != cotok[0x00]; ++cotok)
        if ('(' == cotok[0x00] || '<' == cotok[0x00]) break;

    //
    char *tokep = cotok;
    for (; toksp != tokep && ' ' == tokep[-1]; --tokep);
    //
    strzcpy(obje_invk, toksp, tokep - toksp);
    return cotok;
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

char *decod_objide_levivk(char *objide, char *levivk, char *invok, char *coline) {
    char space_conte[OBJN_LENGTH + LEVE_LENGTH + LVON_LENGTH];
    char *pase_tok = build_space_conte(space_conte, coline);
    // CLIT_PF("space_conte:|%s| stri:|%s|\n", space_conte, stri);
    char *space_array[SPACE_COUNT];
    if (split_space_array(space_array, space_conte))
        return NULL;
    //
    if (creat_objide_levivk(objide, levivk, invok, space_array))
        return NULL;
    return pase_tok;
}

//

char *split_levivk_space(char *levivk, char *space) {
    // CLIT_PF("[FUNC] split_levivk_space space:|%s|\n", space);
    char *toksp, *tokep;
    //
    for (toksp = space; '\0' != toksp[0x00]; ++toksp)
        if (' ' != toksp[0x00] && ':' != toksp[0x00]) break;
    for (tokep = toksp; '\0' != tokep[0x00]; ++tokep)
        if (' ' == tokep[0x00] || '(' == tokep[0x00] || '<' == tokep[0x00]) break;
    //
    strzcpy(levivk, toksp, tokep - toksp);
    return tokep;
}

char *split_levivk_invok(char *levivk, char *invok, char *space) {
    // CLIT_PF("[FUNC] split_levivk_invok space:|%s|\n", space);
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

char *split_objide_levivk(char *objide, char *levivk, char *space) {
    // CLIT_PF("[FUNC] split_objide_levivk space:|%s|\n", space);
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

char *next_pamvu(char *pamcon, char *coline) {
    char *toksp, *tokep;
    char cutok;
    //
    for (toksp = coline; '\0' != toksp[0x00]; ++toksp) {
        cutok = toksp[0x00];
        if ((' ' != cutok) && ('(' != cutok)
                && (')' != cutok) && (',' != cutok)
                && (';' != cutok) && ('>' != cutok))
            break;
    }
    //
    if ('"' == toksp[0x00]) {
        for (tokep = toksp + 0x01; ('\0' != tokep[0x00]) && ('"' != tokep[0x00]); ++tokep)
            if ('\\' == tokep[0x00]) ++tokep;
        if ('\0' != tokep[0x00]) {
            ++tokep;
            if ('S' == tokep[0x00] || 's' == tokep[0x00])
                ++tokep;
        }
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
            if (('(' == cutok) || (')' == cutok) || (',' == cutok) || (';' == cutok))
                break;
        }
    }
    strzcpy(pamcon, toksp, tokep - toksp);
    //
    for (; '\0' != tokep[0x00]; ++tokep) {
        cutok = tokep[0x00];
        if ((' ' != cutok) && ('(' != cutok)
                && (')' != cutok) && (',' != cutok)
                && (';' != cutok) && ('>' != cutok))
            break;
    }
    //
    return tokep;
}

//

static char *not_blank(char *stri) {
    // CLIT_PF("[FUNC]not_blank stri:|%s|\n", stri);
    for (; ' ' == *stri; ++stri);
    if ('\0' == *stri)
        return NULL;
    return stri;
}

static char *invoke_token(char *stri) {
    for (; '(' != *stri; ++stri) {
        if ('\0' == *stri) {
            return NULL;
        }
    }
    return stri;
}

char *define_token(char *stri) {
    for (; '<' != *stri; ++stri) {
        if ('\0' == *stri) {
            return NULL;
        }
    }
    return stri;
}

static char *have_delim(char *stri) {
    while (' ' == *stri) ++stri;
    if (':' == *stri) return stri;
    return NULL;
}

// 0:yes -1:no

int accep_clie_metho(char *line_str, const char* objide) {
    char *lstok = pass_blank(line_str);
    if (!lstok) return -1;
    //
    if (!strncasecmp(objide, lstok, strlen(objide))) {
        lstok += strlen(objide);
        if (!(lstok = have_delim(lstok)))
            return -1;
        ++lstok;
    }
    if (invoke_token(++lstok)) return 0x00;
    //
    return -1;
}

int accep_osev_metho(char *line_str, const char *clie_obje, const char *osev_obje) {
    char *lstok = pass_blank(line_str);
    if (!lstok) return -1;
    //
    if (!strncasecmp(clie_obje, lstok, strlen(clie_obje))) {
        lstok += strlen(clie_obje);
        if (!(lstok = have_delim(lstok)))
            return -1;
        ++lstok;
    } else if (!strncasecmp(osev_obje, lstok, strlen(osev_obje))) {
        lstok += strlen(osev_obje);
        if (!(lstok = have_delim(lstok)))
            return -1;
        ++lstok;
    }
    if (invoke_token(++lstok)) return 0x00;
    //
    return -1;
}

// 0:yes -1:no

int accep_base_metho(char *line_str, const char *clie_obje, const char *base_obje, const char *kits_obje) {
    char *lstok = pass_blank(line_str);
    if (!lstok) return -1;
    CLIT_PF("[FUNC]is_level_method lstok:|%s|\n", lstok);
    if (!strncasecmp(clie_obje, lstok, strlen(clie_obje))) {
        lstok += strlen(clie_obje);
    } else if (!strncasecmp(base_obje, lstok, strlen(base_obje))) {
        lstok += strlen(base_obje);
    } else if (!strncasecmp(kits_obje, lstok, strlen(kits_obje))) {
        lstok += strlen(kits_obje);
    } else return -1;
    //
    if (!(lstok = have_delim(lstok)))
        return -1;
    if (invoke_token(lstok + 0x02))
        return 0x00;
    //
    return -1;
}

// 0:yes -1:no

int accep_user_metho(char *line_str) {
    char *lstok = pass_blank(line_str);
    if (!lstok) return -1;
    if (strchr(lstok, ':')) {
        if (invoke_token(lstok + 0x02)) return 0x00;
    }
    return -1;
}

// 0:yes -1:no
// |txxt<[xx int32, ax int32, cx int32], tpp(cx, ax, xx)>;|
// <>;

int is_defin_class(char *line_str) {
    char *lstok = pass_blank(line_str);
    if (!lstok) return -1;
    //
    PASS_NAME(lstok);
    PASS_BLANK(lstok);
    if ('<' == lstok[0x00])
        return 0x00;
    //
    return -1;
}

// 0:yes -1:no
// |:tpp<(xo int32, ao int32)int32, (ci int32, ai int32, xi int32)> {xi = xo; ai = ao; return ci;}|
// :<>{}

int is_defin_metho(char *line_str) {
    char *lstok = pass_blank(line_str);
    if (!lstok) return -1;
    lstok = strchr(lstok, ':');
    if (!lstok) return -1;
    //
    ++lstok;
    PASS_BLANK(lstok);
    PASS_NAME(lstok);
    PASS_BLANK(lstok);
    if ('<' == lstok[0x00])
        return 0x00;
    //
    return -1;
}

// :();

int is_opera_invok(char *line_str) {
    char *lstok = pass_blank(line_str);
    if (!lstok) return -1;
    lstok = strchr(lstok, ':');
    if (!lstok) return -1;
    //
    for (;;) {
        ++lstok;
        PASS_BLANK(lstok);
        PASS_NAME(lstok);
        PASS_BLANK(lstok);
        switch (lstok[0x00]) {
            case':':
                continue;
                break;
            case '(':
                return 0x00;
                break;
            default:
                return -1;
                break;
        }
    }
    //
    return -1;
}

// :post("txxt", EXTERN, FALSE);

int is_opera_colle(char *line_str) {
    char *lstok = pass_blank(line_str);
    if (!lstok) return -1;
    lstok = strchr(lstok, ':');
    if (!lstok) return -1;
    //
    for (;;) {
        ++lstok;
        PASS_BLANK(lstok);
        PASS_NAME(lstok);
        PASS_BLANK(lstok);
        switch (lstok[0x00]) {
            case':':
                continue;
                break;
            case '(':
                return 0x00;
                break;
            default:
                return -1;
                break;
        }
    }
    //
    return -1;
}

// :();

int is_opera_const(char *line_str) {
    char *lstok = pass_blank(line_str);
    if (!lstok) return -1;
    lstok = strchr(lstok, ':');
    if (!lstok) return -1;
    //
    for (;;) {
        ++lstok;
        PASS_BLANK(lstok);
        PASS_NAME(lstok);
        PASS_BLANK(lstok);
        switch (lstok[0x00]) {
            case':':
                continue;
                break;
            case '(':
                return 0x00;
                break;
            default:
                return -1;
                break;
        }
    }
    //
    return -1;
}

// :();

int is_opera_query(char *line_str) {
    char *lstok = pass_blank(line_str);
    if (!lstok) return -1;
    lstok = strchr(lstok, ':');
    if (!lstok) return -1;
    //
    for (;;) {
        ++lstok;
        PASS_BLANK(lstok);
        PASS_NAME(lstok);
        PASS_BLANK(lstok);
        switch (lstok[0x00]) {
            case':':
                continue;
                break;
            case '(':
                return 0x00;
                break;
            default:
                return -1;
                break;
        }
    }
    //
    return -1;
}

// NULL:continue NOT_NULL:finish

static char *pass_parms(char *stri) {
    int quote_deep = 0x00;
    //
    for (; '\0' != *stri; ++stri) {
        if ('\\' == *stri) ++stri;
        else if ('"' == *stri) {
            ++quote_deep;
            for (++stri; '"' != *stri; ++stri) {
                if (!*stri) return NULL;
                if ('\\' == *stri) ++stri;
            }
            --quote_deep;
        } else if (')' == *stri) return stri;
    }
    //
    return NULL;
}

// 0x00:finish 0x01:continue -1:error 

int invok_metho_finis(char *line_str) {
    static int end_step;
    // CLIT_PF("[FUNC]invok_metho_finis line_str:|%s|\n", line_str);
    // CLIT_PF("end_step:%d\n", end_step);
    char *lstok = line_str;
    if (!end_step) {
        lstok = strchr(++lstok, '(');
        // CLIT_PF("0 [FUNC]invok_metho_finis lstok:|%s|\n", lstok);
        if (lstok) end_step = 0x01;
    }
    if (0x01 == end_step) {
        lstok = pass_parms(++lstok);
        // CLIT_PF("1 [FUNC]invok_metho_finis lstok:|%s|\n", lstok);
        if (lstok) end_step = 0x02;
    }
    if (0x02 == end_step) {
        lstok = qstrch(++lstok, ';');
        // CLIT_PF("2 [FUNC]invok_metho_finis lstok:|%s|\n", lstok);
        if (lstok) end_step = 0x03;
    }
    if (0x03 == end_step) {
        end_step = 0x00;
        // CLIT_PF("3 [FUNC]invok_metho_finis lstok:|%s|\n", lstok);
        if (not_blank(++lstok)) return -1;
        else return 0x00;
    }
    // CLIT_PF("end_step:%d\n", end_step);
    return 0x01;
}

//
// |txxt<[xx int32, ax int32, cx int32], tpp(cx, ax, xx)>;|
// <>;

int class_defin_finis(char *line_str) {
    static int end_step;
    //
    char *lstok = line_str;
    if (!end_step) {
        lstok = strchr(++lstok, '<');
        if (lstok) end_step = 0x01;
    }
    if (0x01 == end_step) {
        lstok = strchr(++lstok, '>');
        if (lstok) end_step = 0x02;
    }
    if (0x02 == end_step) {
        lstok = strchr(++lstok, ';');
        if (lstok) end_step = 0x03;
    }
    if (0x03 == end_step) {
        end_step = 0x00;
        if (not_blank(++lstok)) return -1;
        else return 0x00;
    }
    //
    return 0x01;
}

// NULL:continue NOT_NULL:finish

static char *chk_brace_couple(char *stri) {
    int brace_deep = 0x00;
    //
    for (; '\0' != *stri; ++stri) {
        if ('\\' == *stri) ++stri;
        else if ('"' == *stri) {
            for (++stri; '"' != *stri; ++stri) {
                if (!*stri) return NULL;
                if ('\\' == *stri) ++stri;
            }
        } else if ('{' == *stri) ++brace_deep;
        else if ('}' == *stri) {
            --brace_deep;
            if (!brace_deep) return stri;
        }
    }
    //
    return NULL;
}

// :<>{}

int metho_defin_finis(char *line_str) {
    // CLIT_PF("[FUNC]:metho_defin_finis line_str:|%s|\n", line_str);
    static int end_step;
    //
    char *lstok = line_str;
    if (!end_step) {
        lstok = strchr(lstok, ':');
        if (lstok) end_step = 0x01;
    }
    if (0x01 == end_step) {
        lstok = strchr(++lstok, '<');
        if (lstok) end_step = 0x02;
    }
    if (0x02 == end_step) {
        lstok = strchr(++lstok, '>');
        if (lstok) end_step = 0x03;
    }
    if (0x03 == end_step) {
        lstok = strchr(++lstok, '{');
        if (lstok) end_step = 0x04;
    }
    if (0x04 == end_step) {
        lstok = chk_brace_couple(lstok);
        if (lstok) end_step = 0x05;
    }
    if (0x05 == end_step) {
        end_step = 0x00;
        if (not_blank(++lstok)) return -1;
        else return 0x00;
    }
    //
    return 0x01;
}

// :();

int opera_invok_finis(char *line_str) {
    static int end_step;
    //
    char *lstok = line_str;
    if (!end_step) {
        lstok = strchr(lstok, ':');
        if (lstok) end_step = 0x01;
    }
    if (0x01 == end_step) {
        lstok = strchr(++lstok, '(');
        if (lstok) end_step = 0x02;
    }
    if (0x02 == end_step) {
        lstok = strchr(++lstok, ')');
        if (lstok) end_step = 0x03;
    }
    if (0x03 == end_step) {
        lstok = strchr(++lstok, ';');
        if (lstok) end_step = 0x04;
    }
    if (0x04 == end_step) {
        end_step = 0x00;
        if (not_blank(++lstok)) return -1;
        else return 0x00;
    }
    //
    return 0x01;
}

// :();

int opera_colle_finis(char *line_str) {
    static int end_step;
    //
    char *lstok = line_str;
    if (!end_step) {
        lstok = strchr(lstok, ':');
        if (lstok) end_step = 0x01;
    }
    if (0x01 == end_step) {
        lstok = strchr(++lstok, '(');
        if (lstok) end_step = 0x02;
    }
    if (0x02 == end_step) {
        lstok = strchr(++lstok, ')');
        if (lstok) end_step = 0x03;
    }
    if (0x03 == end_step) {
        lstok = strchr(++lstok, ';');
        if (lstok) end_step = 0x04;
    }
    if (0x04 == end_step) {
        end_step = 0x00;
        if (not_blank(++lstok)) return -1;
        else return 0x00;
    }
    //
    return 0x01;
}

// :();

int opera_const_finis(char *line_str) {
    static int end_step;
    //
    char *lstok = line_str;
    if (!end_step) {
        lstok = strchr(lstok, ':');
        if (lstok) end_step = 0x01;
    }
    if (0x01 == end_step) {
        lstok = strchr(++lstok, '(');
        if (lstok) end_step = 0x02;
    }
    if (0x02 == end_step) {
        lstok = strchr(++lstok, ')');
        if (lstok) end_step = 0x03;
    }
    if (0x03 == end_step) {
        lstok = strchr(++lstok, ';');
        if (lstok) end_step = 0x04;
    }
    if (0x04 == end_step) {
        end_step = 0x00;
        if (not_blank(++lstok)) return -1;
        else return 0x00;
    }
    //
    return 0x01;
}

// :();

int opera_query_finis(char *line_str) {
    static int end_step;
    //
    char *lstok = line_str;
    if (!end_step) {
        lstok = strchr(lstok, ':');
        if (lstok) end_step = 0x01;
    }
    if (0x01 == end_step) {
        lstok = strchr(++lstok, '(');
        if (lstok) end_step = 0x02;
    }
    if (0x02 == end_step) {
        lstok = strchr(++lstok, ')');
        if (lstok) end_step = 0x03;
    }
    if (0x03 == end_step) {
        lstok = strchr(++lstok, ';');
        if (lstok) end_step = 0x04;
    }
    if (0x04 == end_step) {
        end_step = 0x00;
        if (not_blank(++lstok)) return -1;
        else return 0x00;
    }
    //
    return 0x01;
}

//

char *have_nspace(char *pamcon) {
    char *cotok = pamcon;
    for (; '\0' != cotok[0x00]; ++cotok) {
        if (':' == cotok[0x00]) return cotok;
    }
    return NULL;
}

// INVO_STATU COLE_STATU 
#define LEVE_OBJE_TOK "odb"
static const char *lv12p_invok_tab[] = {"post", "status", "create", "replace", "drop", "integra", "reload", NULL};

#define LEVE_CLIE_TOK "clie"
static const char *clie_invok_tab[] = {"level", "quit", NULL};

int is_creat_metho(const char *objide, char *invok) {
    char **ptok;
    if (!strcasecmp(LEVE_CLIE_TOK, objide)) {
        ptok = (char **) clie_invok_tab;
        for (; ptok[0x00]; ++ptok) {
            if (!strcasecmp(invok, ptok[0x00]))
                return 0x01;
        }
    }
    //
    ptok = (char **) lv12p_invok_tab;
    for (; ptok[0x00]; ++ptok) {
        if (!strcasecmp(invok, ptok[0x00]))
            return 0x01;
    }
    //
    return 0x00;
}

int is_creat_class(const char *objide, char *invok) {
    char **ptok;
    if (!strcasecmp(LEVE_CLIE_TOK, objide)) {
        ptok = (char **) clie_invok_tab;
        for (; ptok[0x00]; ++ptok) {
            if (!strcasecmp(invok, ptok[0x00]))
                return 0x01;
        }
    }
    //
    if (!strcasecmp(LEVE_OBJE_TOK, objide)) {
        ptok = (char **) lv12p_invok_tab;
        for (; ptok[0x00]; ++ptok) {
            if (!strcasecmp(invok, ptok[0x00]))
                return 0x01;
        }
    }
    //
    return 0x00;
}

//

int have_defa_obje(char *line_str) {
    char *lstok = line_str;
    for (; (' ' == lstok[0x00]) && ('\0' != lstok[0x00]); ++lstok);
    if (':' == lstok[0x00]) return 0x00;
    //
    return 0x01;
}

//

int check_redirect_obje(char *line_str) {
    char *lstok = qstrch(line_str + 0x01, ':');
    if (!lstok) return -1;
    //
    lstok = qstrch(++lstok, '(');
    if (!lstok) return -1;
    lstok = qstrch(++lstok, ')');
    if (!lstok) return -1;
    lstok = qstrch(++lstok, '>');
    if (!lstok) return -1;
    lstok = qstrch(++lstok, ';');
    if (!lstok) return -1;
    //
    return 0x00;
}

//

int single_instru(char (*inst_stri)[LARGE_TEXT_SIZE], char *cline_stri) {
    lscpy(inst_stri[0x00], cline_stri);
    *(++inst_stri)[0x00] = '\0';
    return 0x00;
}

int multi_instru(char (*inst_stri)[LARGE_TEXT_SIZE], char *cline_stri) {
    char *toksp = cline_stri;
    char *pipetok = qstrch(toksp, '|');
    for (; pipetok; ++inst_stri) {
        char *last_str = lszcpy(inst_stri[0x00], toksp, pipetok - toksp);
        lccpy(last_str, ';');
        toksp = pipetok + 0x01;
        pipetok = qstrch(toksp, '|');
    }
    lscpy(inst_stri[0x00], toksp);
    ++inst_stri;
    (*inst_stri)[0x00] = '\0';
    //
    return 0x00;
}

//

char *analy_const_eobje_exte(char *parms_cont, char *line_str) {
    char *toksp = qstrch(line_str, '(');
    if (!toksp) return NULL;
    char *tokep = qstrch(++toksp, ')');
    if (!tokep) return NULL;
    lszcpy(parms_cont, toksp, tokep - toksp);
    //
    return parms_cont;
}

//

char *analy_const_eobje_redi(char *redi_obje, char *parms_cont, char *line_str) {
    char *toksp = qstrch(line_str, '(');
    if (!toksp) return NULL;
    char *tokep = qstrch(++toksp, ')');
    if (!tokep) return NULL;
    lszcpy(parms_cont, toksp, tokep - toksp);
    //
    toksp = qstrch(tokep + 0x01, '>');
    if (!toksp) return NULL;
    for (++toksp; '\0' != toksp[0x00] && ' ' == toksp[0x00]; ++toksp);
    tokep = qstrch(toksp + 0x01, ';');
    if (!tokep) return NULL;
    for (; toksp != tokep && ' ' == tokep[-1]; --tokep);
    strzcpy(redi_obje, toksp, tokep - toksp);
    //
    return redi_obje;
}



#ifdef _CREAT_COBJE_REDIRECT
// odb-lv4p> witi:witi("taat_con", "txxt") > odb;
// rive:rive("tvtv", "test") > odb;
// odb:create("tvtv", "rive", "test");

char *analy_const_cobje(char *redi_obje, char *parms_cont, char *line_str, char *lv2pn) {
    char coline[PARAM_COUNT * PARAM_LENGTH];
    char *toksp = qstrch(line_str, '(');
    if (!toksp) return NULL;
    char *tokep = qstrch(++toksp, ')');
    if (!tokep) return NULL;
    lszcpy(coline, toksp, tokep - toksp);
    //
    char *deli_tok = qstrch(coline, ',');
    if (!deli_tok) return NULL;
    deli_tok++;
    parms_cont = lszcpy(parms_cont, coline, deli_tok - coline);
    parms_cont = lsprif(parms_cont, " \"%s\",", lv2pn);
    parms_cont = lscpy(parms_cont, deli_tok);
    //
    toksp = qstrch(tokep + 0x01, '>');
    if (!toksp) return NULL;
    for (++toksp; '\0' != toksp[0x00] && ' ' == toksp[0x00]; ++toksp);
    tokep = qstrch(toksp + 0x01, ';');
    if (!tokep) return NULL;
    for (; toksp != tokep && ' ' == tokep[-1]; --tokep);
    strzcpy(redi_obje, toksp, tokep - toksp);
    //
    return redi_obje;
}

#else
// rive:rive("tvtv", "test");
// odb:create("tvtv", "rive", "test");

char *analy_const_cobje(char *parms_cont, char *line_str, char *lv2pn) {
    char coline[PARAM_COUNT * PARAM_LENGTH];
    char *toksp = qstrch(line_str, '(');
    if (!toksp) return NULL;
    char *tokep = qstrch(++toksp, ')');
    if (!tokep) return NULL;
    lszcpy(coline, toksp, tokep - toksp);
    //
    char *deli_tok = qstrch(coline, ',');
    if (!deli_tok) return NULL;
    deli_tok++;
    parms_cont = lszcpy(parms_cont, coline, deli_tok - coline);
    parms_cont = lsprif(parms_cont, " \"%s\",", lv2pn);
    parms_cont = lscpy(parms_cont, deli_tok);
    //
    return parms_cont;
}

#endif // _CREAT_COBJE_REDIRECT

// xxx:open("12p34p");

char *analy_statu_open(char *parms_cont, char *line_str, char *objide) {
    char coline[PARAM_COUNT * PARAM_LENGTH];
    char *toksp = qstrch(line_str, '(');
    if (!toksp) return NULL;
    char *tokep = qstrch(++toksp, ')');
    if (!tokep) return NULL;
    lszcpy(coline, toksp, tokep - toksp);
    //
    parms_cont = lsprif(parms_cont, "\"%s\",", objide);
    lscpy(parms_cont, coline);
    //
    return parms_cont;
}

//

char *analy_statu_statis(char *parms_cont, char *line_str, char *objide) {
    char coline[PARAM_COUNT * PARAM_LENGTH];
    char *toksp = qstrch(line_str, '(');
    if (!toksp) return NULL;
    char *tokep = qstrch(++toksp, ')');
    if (!tokep) return NULL;
    lszcpy(coline, toksp, tokep - toksp);
    //
    char *deli_tok = qstrch(coline, ',');
    if (deli_tok) {
        deli_tok++;
        parms_cont = lszcpy(parms_cont, coline, deli_tok - coline);
        parms_cont = lsprif(parms_cont, " \"%s\", %s", objide, deli_tok);
    } else lsprif(parms_cont, "%s, \"%s\"", coline, objide);
    //
    return parms_cont;
}

//

char *find_parms_conte(char *parms, char *coline) {
    char *toksp = qstrch(coline, '(');
    if (!toksp) return NULL;
    char *tokep = qstrch(toksp + 0x01, ')');
    if (!tokep) return NULL;
    //
    strzcpy(parms, toksp + 0x01, tokep - toksp - 0x01);
    quote_decode(parms);
    return parms;
}

//
#define BUFFER_SIZE          0x1000  // 4K
#define CLIEW_PROMPT "    WARN: "
#define CLIEW_PROMPT_LENG 0x000a

void ClitPrintWarn(const char *fmt, ...) {
    char buffer[BUFFER_SIZE];
    strcpy(buffer, CLIEW_PROMPT);
    //
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buffer + CLIEW_PROMPT_LENG, BUFFER_SIZE - CLIEW_PROMPT_LENG - 0x01, fmt, ap);
    va_end(ap);
    //
    fprintf(stderr, "%s", buffer);
}

//

char *inser_tail(char **strp, char *posi) {
    char **ptok = strp;
    //
    for (; ptok[0x00] && posi != ptok[0x00]; ++ptok);
    if (!ptok[0x00]) return NULL;
    //
    for (; strp != ptok; --ptok)
        ptok[0x00] = ptok[-1];
    ptok[0x00] = posi;
    //
    return posi;
}

// static osv_str_t kits_stri = osv_stri("kits");
static osv_str_t command_stri = osv_stri("command");
static osv_str_t status_stri = osv_stri("status");
static osv_str_t privile_stri = osv_stri("privile");
static const osv_str_t *appe_objide_tab[] = {&command_stri, &status_stri, &privile_stri, NULL};

int valid_osev_objide(char *objide) {
    osv_str_t **ptok = (osv_str_t **) appe_objide_tab;
    for (; ptok[0x00]; ++ptok) {
        if (!strncmp(objide, ptok[0x00]->data, ptok[0x00]->slen))
            return 0x01;
    }
    //
    return 0x00;
}

int split_last_obje(char *last_obje, const char *objide) {
    char *oitok = strrchr(objide, ':');
    if (oitok) strcpy(last_obje, ++oitok);
    else strcpy(last_obje, objide);
    kill_blank(last_obje);
    //
    return 0x00;
}

//
