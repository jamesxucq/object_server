#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "../cli_struct.h"
#include "../cli_macro.h"
#include "../cli_bzl.h"
#include "defau_utili.h"
#include "conve_utili.h"
#include "valid_logic.h"

#include "instr_pretr.h"
#include "../debug_funct_sh.h"

//

int check_clie_use(char **pamvp) {
    KILL_QUOTE(pamvp)
            //
            unsigned int inde = 0x00;
    for (; pamvp[0x00]; ++pamvp) ++inde;
    if ((0x01 != inde) && (0x03 != inde))
        return -1;
    return 0x00;
}

//

static int conv_osev_comd(unsigned int invok, char **pamvp, char *_sline_) {
    CLIEPF("[FUNC]:conv_osev_comd\n");
    KILL_QUOTE(pamvp)
            int conv_valu = -1;
    //
    switch (invok) {
        case CMDI_OPEN:
            CLIEPF("INSM_OPEN\n");
            if (defva_ocomd_open(pamvp, _sline_))
                break;
            conv_valu = oconv_open_styl(pamvp);
            break;
        case CMDI_CLOSE:
            CLIEPF("INSM_CLOSE\n");
            // quote_decode(pamvp[0x00]);
            conv_valu = oconv_close_styl(pamvp);
            break;
        case CMDI_INVAL:
        default:
            _LOG_WARN("default: invok");
            break;
    }
    //
    CLIEPF("conv_osev_comd, conv_valu:%d\n", conv_valu);
    return conv_valu;
}

static int conv_base_comd(const char *objide, unsigned int invok, char **pamvp, char *_sline_) {
    CLIEPF("[FUNC]:conv_base_comd\n");
    KILL_QUOTE(pamvp)
            int conv_valu = -1;
    //
    switch (invok) {
        case CMDI_OPEN:
            CLIEPF("INSM_OPEN\n");
            if (defva_bcomd_open(pamvp, _sline_))
                break;
            conv_valu = bconv_open_styl(pamvp, objide, &_ocli_clie_);
            break;
        case CMDI_CLOSE:
            CLIEPF("INSM_CLOSE\n");
            // quote_decode(pamvp[0x00]);
            conv_valu = bconv_close_styl(pamvp, objide, _sline_, &_ocli_clie_);
            break;
        case CMDI_INVAL:
        default:
            _LOG_WARN("default: invok");
            break;
    }
    //
    CLIEPF("conv_base_comd, conv_valu:%d\n", conv_valu);
    return conv_valu;
}

//

static int conv_osev_stat(unsigned int invok, char **pamvp, char *_sline_) {
    CLIEPF("[FUNC]:conv_osev_stat\n");
    KILL_QUOTE(pamvp)
            int conv_valu = -1;
    //
    switch (invok) {
        case STAI_ECHO:
            CLIEPF("STAM_ECHO\n");
            if (defva_ostat_echo(pamvp, _sline_))
                break;
            conv_valu = oconv_echo_styl((char **) pamvp);
            break;
        case STAI_STATUS:
            CLIEPF("STAM_STATUS\n");
            // quote_decode(pamvp[0x00]);
            defva_ostat_status(pamvp, _sline_);
            if (ochk_status_pamvs(pamvp))
                break;
            conv_valu = oconv_status_styl(pamvp);
            break;
        case STAI_STATIS:
            CLIEPF("STAM_STATIS\n");
            // quote_decode(pamvp[0x00]);
            defva_ostat_statis(pamvp, _sline_);
            if (ochk_statis_pamvs(pamvp))
                break;
            conv_valu = oconv_statis_styl(pamvp);
            break;
        case STAI_INVAL:
        default:
            _LOG_WARN("default: invok");
            break;
    }
    //
    CLIEPF("conv_osev_stat, conv_valu:%d\n", conv_valu);
    return conv_valu;
}

static int conv_base_stat(const char *objide, unsigned int invok, char **pamvp, char *_sline_) {
    CLIEPF("[FUNC]:conv_base_stat\n");
    KILL_QUOTE(pamvp)
            int conv_valu = -1;
    //
    switch (invok) {
        case STAI_ECHO:
            CLIEPF("STAM_ECHO\n");
            if (defva_bstat_echo(pamvp, _sline_))
                break;
            conv_valu = bconv_echo_styl((char **) pamvp, objide, _sline_, &_ocli_clie_);
            break;
        case STAI_STATUS:
            CLIEPF("STAM_STATUS\n");
            // quote_decode(pamvp[0x00]);
            defva_bstat_status(pamvp, _sline_);
            if (bchk_status_pamvs(pamvp))
                break;
            conv_valu = bconv_status_styl(pamvp, objide, &_ocli_clie_);
            break;
        case STAI_STATIS:
            CLIEPF("STAM_STATIS\n");
            // quote_decode(pamvp[0x00]);
            defva_bstat_statis(pamvp, _sline_);
            if (bchk_statis_pamvs(pamvp))
                break;
            conv_valu = bconv_statis_styl(pamvp, objide, _sline_, &_ocli_clie_);
            break;
        case STAI_INVAL:
        default:
            _LOG_WARN("default: invok");
            break;
    }
    //
    CLIEPF("conv_base_stat, conv_valu:%d\n", conv_valu);
    return conv_valu;
}

//

static int conv_osev_priv(const char *objide, unsigned int invok, char **pamvp) {
    CLIEPF("[FUNC]:conv_osev_priv\n");
    KILL_QUOTE(pamvp)
            int conv_valu = -1;
    //
    switch (invok) {
        case PRII_LIST:
            if (defva_opriv_list(pamvp))
                break;
            conv_valu = oconv_list_pamvs(pamvp);
            break;
        case PRII_ROLE:
            // quote_decode(pamvp[0x02]);
            if (defva_opriv_role(pamvp, objide))
                break;
            conv_valu = oconv_role_pamvs(pamvp, objide);
            break;
        case PRII_USER:
            // quote_decode(pamvp[0x01]);
            if (defva_opriv_user(pamvp))
                break;
            conv_valu = oconv_user_pamvs(pamvp);
            break;
        case PRII_INVAL:
        default:
            _LOG_WARN("default: invok");
            break;
    }
    //
    return conv_valu;
}

static int conv_base_priv(const char *objide, unsigned int invok, char **pamvp) {
    CLIEPF("[FUNC]:conv_base_priv\n");
    KILL_QUOTE(pamvp)
            int conv_valu = -1;
    //
    switch (invok) {
        case PRII_LIST:
            if (defva_bpriv_list(pamvp))
                break;
            conv_valu = bconv_list_pamvs(pamvp);
            break;
        case PRII_ROLE:
            // quote_decode(pamvp[0x02]);
            if (defva_bpriv_role(pamvp, objide))
                break;
            conv_valu = bconv_role_pamvs(pamvp, objide);
            break;
        case PRII_USER:
            // quote_decode(pamvp[0x01]);
            if (defva_bpriv_user(pamvp))
                break;
            conv_valu = bconv_user_pamvs(pamvp);
            break;
        case PRII_INVAL:
        default:
            _LOG_WARN("default: invok");
            break;
    }
    //
    return conv_valu;
}

//

int pretr_osev_inten(const char *objide, unsigned int levivk, unsigned int invok, char **pamvp, char *_sline_) {
    CLIEPF("[FUNC]:pretr_osev_inten\n");
    int conv_valu = -1;
    //
    switch (levivk) {
        case OSEV_COMAND:
            CLIEPF("INSM_OPEN\n");
            conv_valu = conv_osev_comd(invok, pamvp, _sline_);
            break;
        case OSEV_STATU:
            CLIEPF("INSM_CLOSE\n");
            conv_valu = conv_osev_stat(invok, pamvp, _sline_);
            break;
        case OSEV_PRIVI:
            CLIEPF("INSM_CLOSE\n");
            conv_valu = conv_osev_priv(objide, invok, pamvp);
            break;
        case OSEV_INVAL:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    CLIEPF("pretr_osev_inten, conv_valu:%d\n", conv_valu);
    return conv_valu;
}

//

int pretr_base_inten(const char *objide, unsigned int levivk, unsigned int invok, char **pamvp, char *_sline_) {
    CLIEPF("[FUNC]:pretr_base_inten\n");
    int conv_valu = -1;
    //            
    switch (levivk) {
        case BASE_COMAND:
            CLIEPF("INSM_OPEN\n");
            conv_valu = conv_base_comd(objide, invok, pamvp, _sline_);
            break;
        case BASE_STATU:
            CLIEPF("INSM_CLOSE\n");
            conv_valu = conv_base_stat(objide, invok, pamvp, _sline_);
            break;
        case BASE_PRIVI:
            CLIEPF("INSM_CLOSE\n");
            conv_valu = conv_base_priv(objide, invok, pamvp);
            break;
        case BASE_INVAL:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    CLIEPF("pretr_base_inten, conv_valu:%d\n", conv_valu);
    return conv_valu;
}

//

int pretr_cont_levon(uint32 run_level, unsigned int levivk, char **pamvp, char *_sline_) {
    int conv_valu = -1;
    // "level-1>" "taat|1>" default object
    KILL_QUOTE(pamvp)
            //
    if (defva_leve_one(levivk, pamvp, _sline_))
        return -1;
    if (LEVEL_EXTEND_SPACE & run_level) {
        if (lconv_levon_exten(levivk, pamvp, _sline_))
            return -1;
        conv_valu = valid_levon_exten(levivk, pamvp);
    } else {
        if (lconv_levon_pamvs(levivk, pamvp))
            return -1;
        conv_valu = valid_levon_pamvs(levivk, pamvp);
    }
    //
    return conv_valu;
}

int pretr_cont_levtp(unsigned int levivk, char **pamvp, char *_sline_) {
    KILL_QUOTE(pamvp)
            //
    if (defva_leve_twop(levivk, pamvp, _sline_))
        return -1;
    if (lconv_levtp_pamvs(levivk, pamvp))
        return -1;
    int conv_valu = valid_levtp_pamvs(levivk, pamvp);
    //
    return conv_valu;
}

int pretr_cont_levth(uint32 run_level, unsigned int levivk, char **pamvp, char *_sline_) {
    int conv_valu = -1;
    // "level-3>" "taat|3>" default object
    // KILL_QUOTE(pamvp) -> defva
    if (defva_leve_thre(levivk, pamvp, _sline_))
        return -1;
    //
    if (LEVEL_EXTEND_SPACE & run_level)
        conv_valu = lconv_levth_exten(levivk, pamvp, _sline_);
    else conv_valu = lconv_levth_pamvs(levivk, pamvp);
    //
    return conv_valu;
}

int pretr_cont_levfp(unsigned int levivk, char **pamvp, char *_sline_) {
    KILL_QUOTE(pamvp)
            //
    if (defva_leve_foup(levivk, pamvp, _sline_))
        return -1;
    int conv_valu = lconv_levfp_pamvs(levivk, pamvp);
    //
    return conv_valu;
}
