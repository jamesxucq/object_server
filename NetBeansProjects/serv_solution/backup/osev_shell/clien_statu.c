
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "commo_header.h"

#include "third_party.h"
#include "cli_macro.h"
#include "osvp_utili.h"
#include "cinstru.h"
#include "cli_obje.h"

#include "clien_statu.h"
//

uint32 clie_runni_type(cli_inst *cinst, uint32 cli_mode) {
    uint32 clie_valu = cli_mode;
    //
    if (CITP_CLEV == cli_mode) {
        if (INST_QUIT == cinst->inst_levtyp) {
            if (OSEV_CONNE == _conne_type_) clie_valu = CITP_OSVB;
            else if (BASE_CONNE == _conne_type_) clie_valu = CITP_CLIE;
        }
    } else if (CITP_OSVB == cli_mode) {
        if (INST_USE == cinst->inst_levtyp) clie_valu = CITP_CLEV;
        else if (INST_QUIT == cinst->inst_levtyp) clie_valu = CITP_CLIE;
        else if (INST_EXIT == cinst->inst_levtyp) clie_valu = CLI_TYPE_EXIT;
    } else if (CITP_CLIE == cli_mode) {
        if (INST_CONNE == cinst->inst_levtyp) {
            // CLIEPF("clie_runni_type conne_type:%d\n", _conne_type_);
            if (OSEV_CONNE == _conne_type_) clie_valu = CITP_OSVB;
            else if (BASE_CONNE == _conne_type_) clie_valu = CITP_CLEV;
        } else if (INST_EXIT == cinst->inst_levtyp || INST_BYE == cinst->inst_levtyp)
            clie_valu = CLI_TYPE_EXIT;
    }
    //
    return clie_valu;
}

//

static const struct ssin_node level_value_dict[] = {
    {"1", "1", LVTP_ONE},
    {"2p", "2+", LVTP_TWOP},
    {"3", "3", LVTP_THRE},
    {"4p", "4+", LVTP_FOUP},
    {NULL, NULL, 0xFFFFFFFF}
};

//

static int check_level_colle(const char *coll_valu) {
    // CLIEPF("[FUNC]:check_level_colle, coll_valu:|%s|\n", coll_valu);
    osv_oid_t *coll_obid;
    coll_obid = find_colle_obid(coll_valu, &_ocli_clie_);
    if (!coll_obid) return 0x00;
    //
    strcpy(_leve_defa_obje_.obje_iden, coll_valu);
    OBID_BINARY_COPY(&_leve_defa_obje_.obje_obid, coll_obid);
    _leve_defa_obje_.changed = 0x01;
    // CLIEPF("check_level_conta, obje_iden:|%s|\n", _leve_defa_obje_.obje_iden);
    return 0x01;
}

static int check_level_conta(const char *cont_iden) {
    // CLIEPF("[FUNC]:check_level_conta, cont_iden:|%s|\n", cont_iden);
    osv_oid_t *cont_obid;
    cont_obid = find_conta_obid(cont_iden, &_ocli_clie_);
    if (!cont_obid) return 0x00;
    //
    strcpy(_leve_defa_obje_.obje_iden, cont_iden);
    OBID_BINARY_COPY(&_leve_defa_obje_.obje_obid, cont_obid)
    _leve_defa_obje_.changed = 0x01;
    // CLIEPF("check_level_conta, obje_iden:|%s|\n", _leve_defa_obje_.obje_iden);
    return 0x01;
}

static uint32 run_level_exte(uint32 last_level, const char *clie_valu) {
    // CLIEPF("[FUNC]:run_level_exte, last_level:%08X clie_valu:|%s|\n", last_level, clie_valu);
    uint32 run_level = last_level;
    //
    switch (ONLY_LEVEL_VALUE(last_level)) {
        case LVTP_ONE:
        case LVTP_TWOP:
            if (check_level_colle(clie_valu)) {
                run_level = LVTP_ONE;
                SET_EXTEND_SPACE(run_level);
            }
            break;
        case LVTP_THRE:
        case LVTP_FOUP:
            if (check_level_conta(clie_valu)) {
                run_level = LVTP_THRE;
                SET_EXTEND_SPACE(run_level);
            }
            break;
    }
    // CLIEPF("run_level_exte, run_level:%08X\n", run_level);
    return run_level;
}

uint32 clie_runni_level(cli_inst *cinst, uint32 last_level) {
    uint32 leve_valu = last_level;
    // CLIEPF("[FUNC]:cinst->inst_levtyp:%u\n", cinst->inst_levtyp);
    switch (cinst->inst_levtyp) {
        case INST_CONNE:
        case INST_USE:
            leve_valu = LVTP_FOUP;
            break;
        case INST_CLILEV:
            KV_SSIN_EQUA(leve_valu, level_value_dict, cinst->pamcon[0x00])
            if (0xFFFFFFFF == leve_valu) {
                quote_decode((char *) cinst->pamcon[0x00]);
                leve_valu = run_level_exte(last_level, cinst->pamcon[0x00]);
            }
            break;
        default:
            // _LOG_WARN("default: inst_levtyp");
            break;
    }
    // CLIEPF("[FUNC]clie_runni_level leve_valu:%d param:|%s|\n", leve_valu, cinst->pamcon[0x00]);
    return leve_valu;
}