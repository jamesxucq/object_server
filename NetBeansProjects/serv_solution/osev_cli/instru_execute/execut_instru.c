#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "commo_header.h"

#include "../clit_macro.h"
#include "../clit_struct.h"
#include "../cinstru.h"
#include "../clit_obje.h"
#include "../connect.h"
#include "../osvp_utili.h"

#include "execut_instru.h"
#include "../debug_funct_sh.h"

//
// 0:ok -1:err

static int hand_clie_conne(clit_resu *resul, const char *conne_str) {
    char osvp_uri[OSVPURI_LENGTH];
    strcpy(osvp_uri, conne_str);
    quote_decode(osvp_uri);
    //
    if (OSVPURI_ILLEGAL == parse_conne_ospuri(&_ocli_auth_, osvp_uri))
        return -1;
    _conne_type_ = get_conne_type((char *) osvp_uri);
    // CLIT_PF("[FUNC] hand_clie_conne conne_type:%d osvp_uri:|%s|\n", conne_type, osvp_uri);
    switch (_conne_type_) {
        case OSEV_CONNE:
            CLIT_PF("------ cli connect to %s osev.\n", osvp_uri);
            if (conne_osev(&_ocli_clie_, &_ocli_auth_))
                return -1;
            INIT_OSEV_OBID(&_ocli_clie_.clie_obid);
            CLIT_PF("------ cli connect OK.\n");
            break;
        case BASE_CONNE:
            CLIT_PF("------ cli connect to %s base.\n", osvp_uri);
            if (conne_base(&_ocli_clie_, &_ocli_auth_))
                return -1;
            INIT_OSEV_OBID(&_ocli_clie_.clie_obid);
            CLIT_PF("------ cli connect OK.\n");
            break;
        case NULL_CONNE:
        default:
            _LOG_WARN("default: _conne_type_");
            return -1;
            break;
    }
    //
    return 0x00;
}

//

static int clie_execu(clit_resu *resul, clit_inst *cinst) {
    int exec_valu = 0x00;
    switch (cinst->inst_levtyp) {
        case INST_CONNE:
            // quote_decode(cinst->pamcon[0x00]);
            exec_valu = hand_clie_conne(resul, cinst->pamcon[0x00]);
            break;
        case INST_EXIT:
        case INST_BYE:
            break;
        case INST_CLIINF:
            break;
        default:
            _LOG_WARN("default: inst_levtyp");
            break;
    }
    //
    return exec_valu;
}

//

// 0:ok -1:err

static int hand_clie_use(clit_resu *resul, const char **pamvp) {
    CLIT_PF("[FUNC]:hand_clie_use base:|%s|\n", pamvp[0x00]);
    if (chk_clien_conne()) return -1;
    //
    CLIT_PF("------ cli disconne.\n");
    // xKILL_QUOTE(pamvp)
    if (pamvp[0x01]) {
        if (conne_base_auth(&_ocli_clie_, pamvp[0x00], pamvp[0x01], pamvp[0x02])) {
            // cli connection exception, reconnect to osev
            conne_osev(&_ocli_clie_, &_ocli_auth_);
            INIT_OSEV_OBID(&_ocli_clie_.clie_obid);
            return -1;
        }
    } else {
        if (conne_base_noau(&_ocli_clie_, pamvp[0x00])) {
            // cli connection exception, reconnect to osev
            conne_osev(&_ocli_clie_, &_ocli_auth_);
            INIT_OSEV_OBID(&_ocli_clie_.clie_obid);
            return -1;
        }
    }
    //
    return 0x00;
}

//

static int hand_osev_inten(clit_resu *resul, unsigned int levivk, unsigned int invok, const char *objide, const char **pamvp) {
    CLIT_PF("[FUNC]:hand_osev_inten objide:|%s|\n", objide);
    if (chk_clien_conne()) return -1;
    //
    resp_data_t osev_resp;
    if (osev_leve_inte(&osev_resp, levivk, invok, &_ocli_clie_, &_ocli_clie_.clie_obid, pamvp)) {
        OSEVPrintErro("hand osev error!", osev_resp.status_code);
        outpu_excep_code(&osev_resp);
        return -1;
    }
    memcpy(resul->resu_data, osev_resp.resp_memo, osev_resp.content_length);
    resul->resu_leng = osev_resp.content_length;
    resul->resu_type = 0x00;
    // CLIT_PF("none response:\n%s\n", none_str);
    return 0x00;
}

static int hand_base_inten(clit_resu *resul, unsigned int levivk, unsigned int invok, const char *objide, const char **pamvp) {
    CLIT_PF("[FUNC]:hand_base_inten\n");
    CLIT_PF("objide:|%s| levivk:|%u| pamvp[0x00]:|%s|\n", objide, levivk, pamvp[0x00]);
    if (chk_clien_conne()) return -1;
    //
    osv_oid_t base_obid;
    resp_data_t osev_resp;
    gener_base_obid(&base_obid, &_ocli_clie_.clie_obid);
    if (base_leve_inte(&osev_resp, levivk, invok, &_ocli_clie_, &base_obid, pamvp)) {
        OSEVPrintErro("hand osev error!", osev_resp.status_code);
        outpu_excep_code(&osev_resp);
        return -1;
    }
    memcpy(resul->resu_data, osev_resp.resp_memo, osev_resp.content_length);
    resul->resu_leng = osev_resp.content_length;
    resul->resu_type = 0x00;
    // CLIT_PF("none response:\n%s\n", none_str);
    return 0x00;
}

static int hand_clie_quit() {
    // CLIT_PF("[FUNC]:hand_clie_quit.\n");
    reset_colle_cache();
    reset_conta_cache();
    reset_base_cache();
    //
    CLIT_PF("------ clie disconne.\n");
    quit_osev(&_ocli_clie_);
    // CLIT_PF("end hand_clie_quit.\n");
    return 0x00;
}

//

static int osvb_execu(clit_resu *resul, clit_inst *cinst) {
    int exec_valu = 0x00;
    switch (cinst->inst_levtyp) {
        case INST_EXIT:
            exec_valu = hand_clie_quit();
            break;
        case INST_USE:
            exec_valu = hand_clie_use(resul, cinst->pamcon);
            break;
        case INST_OSEV:
            exec_valu = hand_osev_inten(resul, cinst->inst_levivk, cinst->inst_invok, cinst->obje_iden, cinst->pamcon);
            break;
        case INST_BASE:
            exec_valu = hand_base_inten(resul, cinst->inst_levivk, cinst->inst_invok, cinst->obje_iden, cinst->pamcon);
            break;
        case INST_QUIT:
            exec_valu = hand_clie_quit();
            break;
        default:
            _LOG_WARN("default: inst_levtyp");
            break;
    }
    //
    return exec_valu;
}

//
// 0:ok -1:err

static int hand_base_quit() {
    CLIT_PF("------ clear client cache.\n");
    reset_colle_cache();
    reset_conta_cache();
    //
    if (OSEV_CONNE == _conne_type_) {
        CLIT_PF("------ cli connect to %s.\n", _ocli_auth_.osev_base);
        if (quit_cont(&_ocli_clie_, &_ocli_auth_))
            return -1;
        INIT_OSEV_OBID(&_ocli_clie_.clie_obid);
    } else if (BASE_CONNE == _conne_type_) {
        CLIT_PF("------ cli disconne.\n");
        _quit_osev_(&_ocli_clie_);
    }
    //
    return 0x00;
}

//

static int hand_lev1_syst(clit_resu *resul, unsigned int levivk, unsigned int invok, const char *lv2p_iden, const char **pamvp) {
    CLIT_PF("[FUNC]:hand_lev1_syst.\n");
    CLIT_PF("lv2p_iden:|%s|\n", lv2p_iden);
    osv_oid_t *lv2p_obid;
    if (strcmp(BASE_DEFAULT_VALUE, lv2p_iden)) {
        lv2p_obid = find_colle_obid(lv2p_iden, &_ocli_clie_);
    } else lv2p_obid = &_ocli_clie_.clie_obid;
    if (!lv2p_obid) {
        CLIT_PF("Not find the conta.\n");
        return -1;
    }
    //
    resp_data_t lev1_resp;
    if (leve_cont_one(&lev1_resp, levivk, invok, &_ocli_clie_, lv2p_obid, pamvp)) {
        OSEVPrintErro("hand lev1 error!", lev1_resp.status_code);
        outpu_excep_code(&lev1_resp);
        return -1;
    }
    memcpy(resul->resu_data, lev1_resp.resp_memo, lev1_resp.content_length);
    resul->resu_leng = lev1_resp.content_length;
    resul->resu_type = 0x00;
    // CLIT_PF("onel response:\n%s\n", onel_str);
    return 0x00;
}

static int leve_one_execu(clit_resu *resul, clit_inst *cinst) {
    int exec_valu = 0x00;
    switch (cinst->inst_levtyp) {
        case INST_CLILEV:
            break;
        case INST_QUIT:
            exec_valu = hand_base_quit();
            break;
        case INST_LEVO:
            exec_valu = hand_lev1_syst(resul, cinst->inst_levivk, cinst->inst_invok, cinst->obje_iden, cinst->pamcon);
            break;
        default:
            _LOG_WARN("default: inst_levtyp");
            break;
    }
    //
    return exec_valu;
}

//

static int hand_lv2p_syst(clit_resu *resul, unsigned int levivk, unsigned int invok, const char **pamvp) {
    CLIT_PF("[FUNC]:hand_lv2p_syst.\n");
    //
    resp_data_t lv2p_resp;
    if (leve_cont_twop(&lv2p_resp, levivk, invok, &_ocli_clie_, pamvp)) {
        OSEVPrintErro("hand lev2p error!", lv2p_resp.status_code);
        outpu_excep_code(&lv2p_resp);
        return -1;
    }
    memcpy(resul->resu_data, lv2p_resp.resp_memo, lv2p_resp.content_length);
    resul->resu_leng = lv2p_resp.content_length;
    resul->resu_type = 0x00;
    // CLIT_PF("twol response:\n%s\n", twol_str);
    erase_colle(pamvp[0x00], levivk);
    return 0x00;
}

static int leve_twop_execu(clit_resu *resul, clit_inst *cinst) {
    int exec_valu = 0x00;
    switch (cinst->inst_levtyp) {
        case INST_CLILEV:
            break;
        case INST_QUIT:
            exec_valu = hand_base_quit();
            break;
        case INST_LVTP:
            exec_valu = hand_lv2p_syst(resul, cinst->inst_levivk, cinst->inst_invok, cinst->pamcon);
            break;
        default:
            _LOG_WARN("default: inst_levtyp");
            break;
    }
    //
    return exec_valu;
}

//

static int hand_lev3_syst(clit_resu *resul, unsigned int levivk, unsigned int invok, const char *cont_iden, const char **pamvp) {
    CLIT_PF("[FUNC]:hand_lev3_syst.\n");
    osv_oid_t *cont_obid;
    if (strcmp(BASE_DEFAULT_VALUE, cont_iden)) {
        cont_obid = find_conta_obid(cont_iden, &_ocli_clie_);
    } else cont_obid = &_leve_defa_obje_.obje_obid;
    if (!cont_obid) {
        CLIT_PF("Not find the conta.\n");
        return -1;
    }
    //
    resp_data_t lev3_resp;
    if (leve_cont_thre(&lev3_resp, levivk, invok, &_ocli_clie_, cont_obid, pamvp)) {
        OSEVPrintErro("hand lev3 error!", lev3_resp.status_code);
        outpu_excep_code(&lev3_resp);
        return -1;
    }
    memcpy(resul->resu_data, lev3_resp.resp_memo, lev3_resp.content_length);
    resul->resu_leng = lev3_resp.content_length;
    resul->resu_type = 0x00;
    // CLIT_PF("resul->resu_leng:%llu\n", resul->resu_leng);
    // log_binary_file((unsigned char *)lev3_resp.resp_memo, lev3_resp.content_length, "./binary_code.bin_c");
    // CLIT_PF("thrl response:\n%s\n", thrl_str);
    return 0x00;
}

static int leve_three_execu(clit_resu *resul, clit_inst *cinst) {
    int exec_valu = 0x00;
    switch (cinst->inst_levtyp) {
        case INST_CLILEV:
            break;
        case INST_QUIT:
            exec_valu = hand_base_quit();
            break;
        case INST_LEVT:
            exec_valu = hand_lev3_syst(resul, cinst->inst_levivk, cinst->inst_invok, cinst->obje_iden, cinst->pamcon);
            break;
        default:
            _LOG_WARN("default: inst_levtyp");
            break;
    }
    //
    return exec_valu;
}

//

static int hand_lv4p_syst(clit_resu *resul, unsigned int levivk, unsigned int invok, const char **pamvp) {
    CLIT_PF("[FUNC]:hand_lv4p_syst.\n");
    resp_data_t lv4p_resp;
    if (leve_cont_foup(&lv4p_resp, levivk, invok, &_ocli_clie_, pamvp)) {
        OSEVPrintErro("hand lev4p error!", lv4p_resp.status_code);
        outpu_excep_code(&lv4p_resp);
        return -1;
    }
    memcpy(resul->resu_data, lv4p_resp.resp_memo, lv4p_resp.content_length);
    resul->resu_leng = lv4p_resp.content_length;
    resul->resu_type = 0x00;
    // log_binary_file((unsigned char *)lv4p_resp.resp_memo, lv4p_resp.content_length, "./binary_code.bin_c");
    // CLIT_PF("foul response:\n%s\n", foul_str)
    erase_conta(pamvp[0x00], levivk);
    return 0x00;
}

static int leve_foup_execu(clit_resu *resul, clit_inst *cinst) {
    int exec_valu = 0x00;
    switch (cinst->inst_levtyp) {
        case INST_CLILEV:
            break;
        case INST_QUIT:
            exec_valu = hand_base_quit();
            break;
        case INST_LVFP:
            exec_valu = hand_lv4p_syst(resul, cinst->inst_levivk, cinst->inst_invok, cinst->pamcon);
            break;
        default:
            _LOG_WARN("default: inst_levtyp");
            break;
    }
    //
    return exec_valu;
}

//

int execu_instru_comd(clit_resu *resul, clit_stat_t *clit_stat, clit_inst *cinst) {
    int exec_valu = 0x00;
    switch (clit_stat->cli_mode) {
        case CITP_CLIE:
            exec_valu = clie_execu(resul, cinst);
            break;
        case CITP_OSVB:
            exec_valu = osvb_execu(resul, cinst);
            break;
        case CITP_CLEV:
            switch (ONLY_LEVEL_VALUE(clit_stat->run_level)) {
                case LVTP_ONE:
                    exec_valu = leve_one_execu(resul, cinst);
                    break;
                case LVTP_TWOP:
                    exec_valu = leve_twop_execu(resul, cinst);
                    break;
                case LVTP_THRE:
                    exec_valu = leve_three_execu(resul, cinst);
                    break;
                case LVTP_FOUP:
                    exec_valu = leve_foup_execu(resul, cinst);
                    break;
                default:
                    _LOG_WARN("default: run_level");
                    break;
            }
            break;
        default:
            _LOG_WARN("default: cli_mode");
            break;
    }
    //
    return exec_valu;
}
