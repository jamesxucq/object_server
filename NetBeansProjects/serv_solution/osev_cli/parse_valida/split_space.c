#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"

#include "split_space.h" 

//

char *build_space_value(char *space, char *cline) {
    PASS_BLANK(cline);
    char *toke = cline;
    //
    if (':' != toke[0x00])
        PASS_NAME(toke);
    while (toke[0x00]) {
        PASS_BLANK(toke)
        if (':' != toke[0x00]) break;
        ++toke;
        PASS_BLANK(toke)
        PASS_NAME(toke)
    }
    strzcpy(space, cline, toke - cline);
    //
    return toke;
}
