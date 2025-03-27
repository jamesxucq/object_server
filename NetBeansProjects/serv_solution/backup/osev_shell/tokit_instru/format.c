#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "format.h"
#include "fmt_lang/fmt_xmlang.h"
#include "fmt_lang/fmt_binoid.h"
#include "../debug_funct_sh.h"

//
// kits:format(XML);
// kits:format(BINARY_OBID);

// 0x00:OK -1:error

int kits_format(char **pamvp, clie_resu *resul) {
    CLIEPF("[FUNC]:kits_format\n");
    // pamvu = 1
    if (!pamvp[0x00] || pamvp[0x01])
        return -1;
    //
    if (!strcmp(FMT_TYPE_XMLANG, pamvp[0x00])) {
        // CLIEPF("resul->resu_data:|%s|\n", resul->resu_data);
        // OSEVPF("resul->resu_leng:%d strlen(resul->resu_data):%d\n", resul->resu_leng, strlen(resul->resu_data));
        format_xmlang(resul);
    } else if (!strcmp(FMT_TYPE_BINOBID, pamvp[0x00])) {
        // CLIEPF("resul->resu_data:|%s|\n", resul->resu_data);
        // OSEVPF("resul->resu_leng:%d strlen(resul->resu_data):%d\n", resul->resu_leng, strlen(resul->resu_data));
        format_binoid(resul);
    } else {
        CliePrintWarn("Format not find \"%s\"!\n", pamvp[0x00]);
        return -1;
    }
    //
    return 0x00;
}