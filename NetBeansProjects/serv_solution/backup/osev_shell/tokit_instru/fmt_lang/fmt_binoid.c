
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "../../debug_funct_sh.h"
#include "fmt_binoid.h"

//

int format_binoid(clie_resu *resul) {
    CLIEPF("[FUNC]:format_binoid\n");
    char resp_data[LARGE_CONTE_SIZE];
    //
    if (resul->resu_type) return -1;
    if (LARGE_CONTE_SIZE < resul->resu_leng) {
        CliePrintErro("Result leng more than LARGE_CONTE_SIZE!", -1);
        return -1;
    }
    if ((resul->resu_leng % OBJE_IDENTI_BLEN)) {
        CliePrintErro("Result leng error!", -1);
        return -1;
    }
    //
    strzcpy(resp_data, resul->resu_data, resul->resu_leng);
    char *posi_str = resp_data;
    char *last_str = resul->resu_data;
    char *end_str = resp_data + resul->resu_leng;
    for (; end_str > posi_str; posi_str += OBJE_IDENTI_BLEN) {
        last_str = oidstr_delim(last_str, (osv_oid_t *) posi_str);
        last_str = lccpy(last_str, '\n');
    }
    //
    resul->resu_leng = last_str - resul->resu_data;
    return 0x00;
}