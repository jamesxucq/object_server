
#include "osev_common/utility/last_stri.h"
#include "osev_common/osev_macro.h"
#include "osev_common/memo_utili.h"
#include "osev_common/obid.h"

#include "../function/funct_header.h"

#include "parsing.h"

//

static char *next_parm(char *pamcon, char *stri) {
    char *toksp, *tokep;
    char cutok;
    //
    for (toksp = stri; '\0' != toksp[0x00]; ++toksp) {
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

int split_instru_pamvs(const char **pamvp, char *_pline_, char *line_txt) {
    char pamcon[PARAM_LENGTH];
    // OSEVPF("[FUNC]param_parsing line_txt:|%s|\n", line_txt);
    //
    unsigned int inde = 0x00;
    for (; ('\0' != line_txt[0x00]) && PARAM_COUNT > inde; ++inde, ++pamvp) {
        line_txt = next_parm(pamcon, line_txt);
        // OSEVPF("[FUNC]param_parsing pase_tok:|%s|\n", pase_tok);
        if ('\0' == pamcon[0x00]) break;
        LSCPY_O(pamvp[0x00], pamcon, _pline_);
        // OSEVPF("[FUNC]param_parsing pamvp[0x00]:|%s|\n", pamvp[0x00]);
    }
    pamvp[0x00] = NULL;
    //
    return 0x00;
}

//

