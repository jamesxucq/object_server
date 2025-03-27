#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "../clit_struct.h"
#include "../clit_macro.h"
#include "../clit_bzl.h"
#include "defau_utili.h"
#include "conve_utili.h"
#include "valid_logic.h"

#include "instr_pretr.h"
#include "../debug_funct_sh.h"

//

int pretr_clie_use(char **pamvp) {
    KILL_QUOTE(pamvp)
            //
    if (cchk_clie_use(pamvp))
        return -1;
    return 0x00;
}

//

static int hand_osev_post(char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:hand_osev_post\n");
    KILL_QUOTE(pamvp)
            int hand_valu = -1;
    //
    CLIT_PF("OPOST\n");
    // quote_decode(pamvp[0x00]);
    defva_opost(pamvp, _sline_);
    if (ochk_post(pamvp)) return -1;
    hand_valu = oconv_post_styl(pamvp);
    //
    CLIT_PF("hand_osev_post, hand_valu:%d\n", hand_valu);
    return hand_valu;
}

//

static int hand_base_post(const char *objide, char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:hand_base_post\n");
    KILL_QUOTE(pamvp)
            int hand_valu = -1;
    //
    CLIT_PF("BPOST\n");
    // quote_decode(pamvp[0x00]);
    defva_bpost(pamvp, _sline_);
    if (bchk_post(pamvp)) return -1;
    hand_valu = bconv_post_styl(pamvp, objide, &_ocli_clie_);
    //
    CLIT_PF("hand_base_post, hand_valu:%d\n", hand_valu);
    return hand_valu;
}

//

static int hand_osev_statu(unsigned int invok, char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:hand_osev_statu\n");
    KILL_QUOTE(pamvp)
            int hand_valu = -1;
    //
    switch (invok) {
        case STAIU_ECHO:
            CLIT_PF("STAIU_ECHO\n");
            if (defva_ostat_echo(pamvp, _sline_))
                break;
            hand_valu = oconv_echo_styl((char **) pamvp);
            break;
        case STAIU_STATIS:
            CLIT_PF("STAIU_STATIS\n");
            // quote_decode(pamvp[0x00]);
            defva_ostat_statis(pamvp, _sline_);
            if (ochk_statu_stati(pamvp))
                break;
            hand_valu = oconv_statis_styl(pamvp);
            break;
        case STAIU_INVALID:
        default:
            _LOG_WARN("STAIU_INVALID default: invok");
            break;
    }
    //
    CLIT_PF("hand_osev_statu, hand_valu:%d\n", hand_valu);
    return hand_valu;
}

static int hand_base_statu(const char *objide, unsigned int invok, char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:hand_base_statu\n");
    KILL_QUOTE(pamvp)
            int hand_valu = -1;
    //
    switch (invok) {
        case STAIU_ECHO:
            CLIT_PF("STAIU_ECHO\n");
            if (defva_bstat_echo(pamvp, _sline_))
                break;
            hand_valu = bconv_echo_styl((char **) pamvp, objide, _sline_, &_ocli_clie_);
            break;
        case STAIU_STATIS:
            CLIT_PF("STAIU_STATIS\n");
            // quote_decode(pamvp[0x00]);
            defva_bstat_statis(pamvp, _sline_);
            if (bchk_statu_stati(pamvp))
                break;
            hand_valu = bconv_statis_styl(pamvp, objide, _sline_, &_ocli_clie_);
            break;
        case STAIU_INVALID:
        default:
            _LOG_WARN("STAIU_INVALID default: invok");
            break;
    }
    //
    CLIT_PF("hand_base_statu, hand_valu:%d\n", hand_valu);
    return hand_valu;
}

//

static int hand_osev_comd(unsigned int invok, char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:hand_osev_comd\n");
    KILL_QUOTE(pamvp)
            int hand_valu = -1;
    //
    switch (invok) {
        case COMDI_OPEN:
            CLIT_PF("COMDI_OPEN\n");
            if (defva_ocomd_open(pamvp, _sline_))
                break;
            hand_valu = oconv_open_styl(pamvp);
            break;
        case COMDI_CLOSE:
            CLIT_PF("COMDI_CLOSE\n");
            // quote_decode(pamvp[0x00]);
            hand_valu = oconv_close_styl(pamvp);
            break;
        case COMDI_INVALID:
        default:
            _LOG_WARN("COMDI_INVALID default: invok");
            break;
    }
    //
    CLIT_PF("hand_osev_comd, hand_valu:%d\n", hand_valu);
    return hand_valu;
}

static int hand_base_comd(const char *objide, unsigned int invok, char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:hand_base_comd\n");
    KILL_QUOTE(pamvp)
            int hand_valu = -1;
    //
    switch (invok) {
        case COMDI_OPEN:
            CLIT_PF("COMDI_OPEN\n");
            if (defva_bcomd_open(pamvp, _sline_))
                break;
            hand_valu = bconv_open_styl(pamvp, objide, &_ocli_clie_);
            break;
        case COMDI_CLOSE:
            CLIT_PF("COMDI_CLOSE\n");
            // quote_decode(pamvp[0x00]);
            hand_valu = bconv_close_styl(pamvp, objide, _sline_, &_ocli_clie_);
            break;
        case COMDI_INVALID:
        default:
            _LOG_WARN("COMDI_INVALID default: invok");
            break;
    }
    //
    CLIT_PF("hand_base_comd, hand_valu:%d\n", hand_valu);
    return hand_valu;
}

//

static int hand_osev_priv(const char *objide, unsigned int invok, char **pamvp) {
    CLIT_PF("[FUNC]:hand_osev_priv\n");
    KILL_QUOTE(pamvp)
            int hand_valu = -1;
    //
    switch (invok) {
        case PRIVI_LIST:
            if (defva_opriv_list(pamvp))
                break;
            if (ochk_priv_list(pamvp))
                break;
            hand_valu = oconv_list_pamvs(pamvp);
            break;
        case PRIVI_ROLE:
            // quote_decode(pamvp[0x02]);
            if (defva_opriv_role(pamvp, objide))
                break;
            if (ochk_priv_role(pamvp, objide))
                break;
            hand_valu = oconv_role_pamvs(pamvp, objide);
            break;
        case PRIVI_USER:
            // quote_decode(pamvp[0x01]);
            if (defva_opriv_user(pamvp))
                break;
            if (ochk_priv_user(pamvp))
                break;
            hand_valu = oconv_user_pamvs(pamvp);
            break;
        case PRIVI_INVALID:
        default:
            _LOG_WARN("default: invok");
            break;
    }
    //
    return hand_valu;
}

static int hand_base_priv(const char *objide, unsigned int invok, char **pamvp) {
    CLIT_PF("[FUNC]:hand_base_priv\n");
    KILL_QUOTE(pamvp)
            int hand_valu = -1;
    //
    switch (invok) {
        case PRIVI_LIST:
            if (defva_bpriv_list(pamvp))
                break;
            if (bchk_priv_list(pamvp))
                break;
            hand_valu = bconv_list_pamvs(pamvp);
            break;
        case PRIVI_ROLE:
            // quote_decode(pamvp[0x02]);
            if (defva_bpriv_role(pamvp, objide))
                break;
            if (bchk_priv_role(pamvp, objide))
                break;
            hand_valu = bconv_role_pamvs(pamvp, objide);
            break;
        case PRIVI_USER:
            // quote_decode(pamvp[0x01]);
            if (defva_bpriv_user(pamvp))
                break;
            if (bchk_priv_user(pamvp))
                break;
            hand_valu = bconv_user_pamvs(pamvp);
            break;
        case PRIVI_INVALID:
        default:
            _LOG_WARN("default: invok");
            break;
    }
    //
    return hand_valu;
}

//

int pretr_osev_inte(const char *objide, unsigned int levivk, unsigned int invok, char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:pretr_osev_inte\n");
    int pretr_valu = -1;
    //
    switch (levivk) {
        case OSEV_POST:
            CLIT_PF("OSEV_POST\n");
            pretr_valu = hand_osev_post(pamvp, _sline_);
            break;
        case OSEV_STATUS:
            CLIT_PF("OSEV_STATUS\n");
            pretr_valu = hand_osev_statu(invok, pamvp, _sline_);
            break;
        case OSEV_COMAND:
            CLIT_PF("OSEV_COMAND\n");
            pretr_valu = hand_osev_comd(invok, pamvp, _sline_);
            break;
        case OSEV_PRIVILE:
            CLIT_PF("OSEV_PRIVILE\n");
            pretr_valu = hand_osev_priv(objide, invok, pamvp);
            break;
        case OSEV_INVALID:
        default:
            _LOG_WARN("OSEV_INVALID default: levivk");
            break;
    }
    //
    CLIT_PF("pretr_osev_inte, pretr_valu:%d\n", pretr_valu);
    return pretr_valu;
}

//

int pretr_base_inte(const char *objide, unsigned int levivk, unsigned int invok, char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:pretr_base_inte\n");
    int pretr_valu = -1;
    //            
    switch (levivk) {
        case BASE_POST:
            CLIT_PF("BASE_POST\n");
            pretr_valu = hand_base_post(objide, pamvp, _sline_);
            break;
        case BASE_STATUS:
            CLIT_PF("BASE_STATUS\n");
            pretr_valu = hand_base_statu(objide, invok, pamvp, _sline_);
            break;
        case BASE_COMAND:
            CLIT_PF("BASE_COMAND\n");
            pretr_valu = hand_base_comd(objide, invok, pamvp, _sline_);
            break;
        case BASE_PRIVILE:
            CLIT_PF("BASE_PRIVILE\n");
            pretr_valu = hand_base_priv(objide, invok, pamvp);
            break;
        case BASE_INVALID:
        default:
            _LOG_WARN("BASE_INVALID default: levivk");
            break;
    }
    //
    CLIT_PF("pretr_base_inte, pretr_valu:%d\n", pretr_valu);
    return pretr_valu;
}

//

int pretr_conte_levon(uint32 run_level, unsigned int levivk, char **pamvp, char *_sline_) {
    int pretr_valu = -1;
    // "[txxt]-lev1>" default object
    KILL_QUOTE(pamvp)
            //
    if (LEVEL_EXTEND_SPACE & run_level) {
        if (defva_levon_exten(levivk, pamvp, _sline_))
            return -1;
        if (lconv_levon_exten(levivk, pamvp, _sline_))
            return -1;
        pretr_valu = valid_levon_exten(levivk, pamvp);
    } else {
        if (defva_levon_pamvs(levivk, pamvp, _sline_))
            return -1;
        if (lconv_levon_pamvs(levivk, pamvp))
            return -1;
        pretr_valu = valid_levon_pamvs(levivk, pamvp);
    }
    //
    return pretr_valu;
}

int pretr_conte_levtp(unsigned int levivk, unsigned int invok, char **pamvp, char *_sline_) {
    KILL_QUOTE(pamvp)
            //
    if (defva_levtp_pamvs(levivk, pamvp, _sline_))
        return -1;
    if (valid_levtp_pamvs(levivk, invok, pamvp))
        return -1;
    int pretr_valu = lconv_levtp_pamvs(levivk, invok, pamvp);
    //
    return pretr_valu;
}

int pretr_conte_levth(uint32 run_level, unsigned int levivk, char **pamvp, char *_sline_) {
    int pretr_valu = -1;
    // "[odb]lev3>" "[teet_con]lev3>" default object
    // KILL_QUOTE(pamvp) -> defv
    //
    if (LEVEL_EXTEND_SPACE & run_level) {
        if (defva_levth_exten(levivk, pamvp, _sline_))
            return -1;
        pretr_valu = lconv_levth_exten(levivk, pamvp, _sline_);
    } else {
        if (defva_levth_pamvs(levivk, pamvp, _sline_))
            return -1;
        pretr_valu = lconv_levth_pamvs(levivk, pamvp);
    }
    //
    return pretr_valu;
}

int pretr_conte_levfp(unsigned int levivk, unsigned int invok, char **pamvp, char *_sline_) {
    KILL_QUOTE(pamvp)
            //
    if (defva_levfp_pamvs(levivk, invok, pamvp, _sline_))
        return -1;
    if (valid_levfp_pamvs(levivk, invok, pamvp))
        return -1;
    int pretr_valu = lconv_levfp_pamvs(levivk, pamvp);
    //
    return pretr_valu;
}
