
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "../cstri_utili.h"

#include "split_pamvs.h"
#include "../debug_funct_sh.h"

//

int split_instru_pamvus(const char **pamvp, char *_pline_, char *line_txt) {
    // CLIT_PF("[FUNC]split_instru_pamvus\n");
    char pamcon[PARAM_LENGTH];
    // CLIT_PF("line_txt:|%s|\n", line_txt);
    unsigned int inde = 0x00;
    for (; ('\0' != line_txt[0x00]) && PARAM_COUNT > inde; ++inde, ++pamvp) {
        // CLIT_PF("------------ |%p|\n", line_txt);
        line_txt = next_pamvu(pamcon, line_txt);
        // CLIT_PF("|%p|, line_txt:|%s|\n", line_txt, line_txt);
        if ('\0' == pamcon[0x00]) break;
        LSCPY_O(pamvp[0x00], pamcon, _pline_);
        // CLIT_PF("pamcon:|%s| pamvp[0x00]:|%s|\n", pamcon, pamvp[0x00]);
    }
    pamvp[0x00] = NULL;
    // CLIT_PF("[FUNC]end, split_instru_pamvus\n");
    return 0x00;
}

