#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "./conve_lang/conv_gcc_cpp.h"
#include "conve.h"
#include "../debug_funct_sh.h"

//

static char *last_array(char **pamvp) {
    char *last_str = NULL;
    char **last_ptok = pamvp;
    for (; last_ptok[0x00]; ++last_ptok)
        last_str = last_ptok[0x00];
    //
    return last_str;
}

//
#define COMP_GCC_TOK "GCC"
#define COMP_MSVC_TOK "MSVC"
#define COMP_JAVAC_TOK "JAVAC"

// -1:error 0x00:unknow 0x01:class 0x02:conta
// comp_type

static int gener_compi_type(char **pamvp) {
    char *last_str = last_array(pamvp);
    if (!last_str) return -1;
    // CLIEPF("last_str:|%s|\n", last_str);
    if (!strcmp(COMP_GCC_TOK, last_str))
        return 0x01;
    if (!strcmp(COMP_MSVC_TOK, last_str))
        return 0x02;
    if (!strcmp(COMP_JAVAC_TOK, last_str))
        return 0x03;
    //
    return 0x00;
}

//
// "GCC" "MSVC" "JAVAC"
// odb:list(lv2pn) | kits:convert(GCC); // fixme
// odb:list(lv2pn) | kits:convert(MSVC); // fixme
// odb:list(lv2pn, "ATTRIB|CONTENT") | kits:convert(JAVAC); // fixme
// 0x00:OK -1:error

int kits_conver(char **pamvp, clie_resu *resul, osev_clie *oclie) {
    CLIEPF("[FUNC]:kits_conver.\n");
    int conv_valu = 0x00;
    // pamvu = 1 = 2
    if (!pamvp[0x00] || (pamvp[0x01] && pamvp[0x02])) 
        return -1;
    //
    switch (gener_compi_type(pamvp)) {
        case 0x00:
            conv_valu = -1;
            break;
        case 0x01:
            conv_valu = conve_gcc_cpp(pamvp, resul, oclie);
            break;
        case 0x02:
            CLIEPF("fixme: MSVC\n");
            conv_valu = -1;
            break;
        case 0x03:
            CLIEPF("fixme: JAVAC\n");
            conv_valu = -1;
            break;
        case -1:
        default:
            _LOG_WARN("default: comp_type");
            conv_valu = -1;
            break;
    }
    //
    return conv_valu;
}