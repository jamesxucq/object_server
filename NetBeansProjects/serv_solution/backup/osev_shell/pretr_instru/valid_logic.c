
#include <stdio.h>

#include "../cli_macro.h"
#include "../cstri_utili.h"
#include "../cli_struct.h"

#include "valid_logic.h"
#include "../debug_funct_sh.h"

int valid_levon_exten(unsigned int levivk, char **pamvp) {
    CLIEPF("[FUNC]:lconv_levtp_param\n");
    int conv_valu = 0x00;
    switch (levivk) {
        case LVTP_POST:
            break;
        case LVTP_LIST:
        case LVTP_CREAT:
        case LVTP_DROP:
        case LVTP_REPLA:
        case LVTP_INTEGRA:
        case LVTP_RELOAD:
            break;
        case LVTP_INVAL:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return conv_valu;
}

int valid_levon_pamvs(unsigned int levivk, char **pamvp) {
    CLIEPF("[FUNC]:lconv_levtp_param\n");
    int conv_valu = 0x00;
    switch (levivk) {
        case LVTP_POST:
            break;
        case LVTP_LIST:
        case LVTP_CREAT:
        case LVTP_DROP:
        case LVTP_REPLA:
        case LVTP_INTEGRA:
        case LVTP_RELOAD:
            break;
        case LVTP_INVAL:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return conv_valu;
}

//

int valid_levtp_pamvs(unsigned int levivk, char **pamvp) {
    CLIEPF("[FUNC]:lconv_levtp_param\n");
    int conv_valu = 0x00;
    switch (levivk) {
        case LVTP_POST:
            break;
        case LVTP_LIST:
        case LVTP_CREAT:
        case LVTP_DROP:
        case LVTP_REPLA:
        case LVTP_INTEGRA:
        case LVTP_RELOAD:
            break;
        case LVTP_INVAL:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return conv_valu;
}

