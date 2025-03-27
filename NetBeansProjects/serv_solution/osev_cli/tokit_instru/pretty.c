#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"

#include "../clit_struct.h"
#include "pretty_utili/pretty_ite.h"

#include "../debug_funct_sh.h"
#include "pretty.h"

//
// kits:pretty("oisfd");
// 0x00:OK -1:error

int kits_pretty(char **pamvp, clit_resu *resul) {
    // CLIT_PF("[FUNC]:kits_pretty.\n");
    // pamvu = 1
    if (!pamvp[0x00] || pamvp[0x01])
        return -1;
    //
    if (resul->resu_type)
        return -1;
    if (LARGE_CONTE_SIZE < resul->resu_leng) {
        ClitPrintErro("Result leng more than LARGE_CONTE_SIZE!", -1);
        return -1;
    }
    //
    char resp_data[LARGE_CONTE_SIZE];
    memcpy(resp_data, resul->resu_data, resul->resu_leng);
    quote_decode(pamvp[0x00]);
    char fmtstr[FMTST_COUNT_ZTAI];
    build_packi_fmtst(fmtstr, pamvp[0x00]);
    // chk_resdat_type
    pretty_variable_echo(resul, fmtstr, pamvp[0x00], resp_data, resul->resu_leng);
    //
    return 0x00;
}