
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "../cstri_utili.h"

#include "split_pamvs.h"
#include "../debug_funct_sh.h"

//

int split_instru_pamvus(const char **pamvp, char *_pline_, char *line_txt) {
    CLIEPF("[FUNC]split_instru_pamvus line_txt:|%s|\n", line_txt);
    char pamcon[PARAM_LENGTH];
    //
    unsigned int inde = 0x00;
    for (; ('\0' != line_txt[0x00]) && PARAM_COUNT > inde; ++inde, ++pamvp) {
        line_txt = next_pamvu(pamcon, line_txt);
        CLIEPF("line_txt:|%s|\n", line_txt);
        if ('\0' == pamcon[0x00]) break;
        LSCPY_O(pamvp[0x00], pamcon, _pline_);
        CLIEPF("pamvp[0x00]:|%s|\n", pamvp[0x00]);
    }
    pamvp[0x00] = NULL;
    //
    return 0x00;
}

