
#include "osev_macro.h"
#include "stri_utili.h"
#include "../cinstru.h"
#include "../cli_obje.h"
#include "../cli_bzl.h"

#include "list.h"
#include "load.h"
#include "save.h"
#include "conve.h"
#include "pretty.h"
#include "key_valu.h"
#include "format.h"
#include "expand.h"

#include "execu_tokit_ite.h"
#include "../debug_funct_sh.h"

//

int execu_tolkit_ite(cli_inst *cinst, clie_resu *resul) {
    int hand_valu = 0x00;
    //
    switch (cinst->inst_levtyp) {
        case KITS_INVAL:
            CLIEPF("kits:invalid\n");
            break;
        case KITS_LIST:
            CLIEPF("kits:list, resu_type:%d resu_leng:%llu lv2p:|%s|\n",
                    resul->resu_type,
                    resul->resu_leng,
                    cinst->pamcon[0x00]);
            hand_valu = kits_list((char **) cinst->pamcon, resul, &_ocli_clie_);
            break;
        case KITS_LOAD:
            hand_valu = kits_load((char **) cinst->pamcon, resul);
            CLIEPF("kits:load, resu_type:%d resu_leng:%llu file_name:|%s|\n",
                    resul->resu_type,
                    resul->resu_leng,
                    cinst->pamcon[0x00]);
            break;
        case KITS_SAVE:
            CLIEPF("kits:save, resu_type:%d resu_leng:%llu file_name:|%s|\n",
                    resul->resu_type,
                    resul->resu_leng,
                    cinst->pamcon[0x00]);
            hand_valu = kits_save((char **) cinst->pamcon, resul);
            break;
        case KITS_CONVE:
            CLIEPF("kits:convert, resu_type:%d resu_leng:%llu comp_type:|%s|\n",
                    resul->resu_type,
                    resul->resu_leng,
                    cinst->pamcon[0x00]);
            hand_valu = kits_conver((char **) cinst->pamcon, resul, &_ocli_clie_);
            break;
        case KITS_PRETTY:
            CLIEPF("kits:pretty, resu_type:%d resu_leng:%llu fmtst:|%s|\n",
                    resul->resu_type,
                    resul->resu_leng,
                    cinst->pamcon[0x00]);
            hand_valu = kits_pretty((char **) cinst->pamcon, resul);
            break;
        case KITS_KEYVAL:
            CLIEPF("kits:key_value, resu_type:%d resu_leng:%llu keyval:|%s|\n",
                    resul->resu_type,
                    resul->resu_leng,
                    cinst->pamcon[0x00]);
            hand_valu = kits_keyval((char **) cinst->pamcon, resul);
            break;
        case KITS_FORMAT:
            CLIEPF("kits:format, resu_type:%d resu_leng:%llu fmtst:|%s|\n",
                    resul->resu_type,
                    resul->resu_leng,
                    cinst->pamcon[0x00]);
            hand_valu = kits_format((char **) cinst->pamcon, resul);
            break;
        case KITS_EXPAND:
            CLIEPF("kits:expand, resu_type:%d resu_leng:%llu lv2p:|%s|\n",
                    resul->resu_type,
                    resul->resu_leng,
                    cinst->pamcon[0x00]);
            hand_valu = kits_expand((char **) cinst->pamcon, resul, &_ocli_clie_);
            break;
        default:
            _LOG_WARN("default: inst_levtyp");
            break;
    }
    //
    return hand_valu;
}