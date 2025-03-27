
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "funct_header.h"
#include "fstoid.h"

// func:stroid("fdeac7ec9a385a6304000000", "fdeac7ec9a385a6304000000")
// func:stroid("bb7ddcfb10c0ff6401000000")

static char *valid_fstroid_type(char *stri) {
    PASS_BLANK(stri)
    if (strncmp(FUNCTION_TOK, stri, FUNCTION_SLEN))
        return NULL;
    stri += FUNCTION_SLEN;
    PASS_BLANK(stri)
    if (SPACE_DELIM_TOK != stri[0x00])
        return NULL;
    ++stri;
    PASS_BLANK(stri)
    if (strncmp(STROID_TOK, stri, STROID_SLEN))
        return NULL;
    stri += STROID_SLEN;
    //
    return stri;
}

// return oid count, -1 is error. 

int func_stroid(osv_oid_t *bina_oid, char *obje_iden) {
    obje_iden = valid_fstroid_type(obje_iden);
    if (!obje_iden) return -1;
    // CLIEPF("valid_fstroid_type:|%s|\n", last_str);
    return param_stroid(bina_oid, obje_iden);
}