
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cinstru.h"
#include "clit_struct.h"
#include "osev_clie_clang.h"

#include"connect.h"
#include "debug_funct_sh.h"

// 0:ok -1:err

int conne_osev(osev_clie *oclie, osvp_auth *clie_auth) {
    resp_data_t crea_resp;
    if (osev_clie_create(&crea_resp, oclie, clie_auth)) {
        OSEVPrintErro("oclie create error!", crea_resp.status_code);
        outpu_excep_code(&crea_resp);
        return -1;
    }
    //
    return 0x00;
}

// 0:ok -1:err

int conne_base(osev_clie *oclie, osvp_auth *clie_auth) {
    resp_data_t crea_resp;
    if (base_clie_create(&crea_resp, oclie, clie_auth)) {
        OSEVPrintErro("oclie create error!", crea_resp.status_code);
        outpu_excep_code(&crea_resp);
        return -1;
    }
    //
    return 0x00;
}

// 0:ok -1:err

int reconne_base(osev_clie *oclie, osvp_auth *clie_auth) {
    resp_head dest_resp;
    if (done_clie_destroy(&dest_resp, oclie)) {
        OSEVPrintErro("oclie destroy error!", dest_resp.status_code);
        outpu_respo_code(dest_resp.status_code);
    }
    // _LOG_INFO("OSEV oclie destroy OK!");
    resp_data_t crea_resp;
    if (base_clie_create(&crea_resp, oclie, clie_auth)) {
        OSEVPrintErro("oclie create error!", crea_resp.status_code);
        outpu_excep_code(&crea_resp);
        return -1;
    }
    //
    return 0x00;
}

//

void quit_osev(osev_clie *oclie) {
    resp_head dest_resp;
    if (done_clie_destroy(&dest_resp, oclie)) {
        OSEVPrintErro("oclie destroy error!", dest_resp.status_code);
        outpu_respo_code(dest_resp.status_code);
    }
    // CLIT_PF("end quit_osev.\n");
}

//

int osev_leve_inte(resp_data_t *osev_resp, unsigned int levivk, unsigned int invok, osev_clie *oclie, osv_oid_t *osev_obid, const char **pamvp) {
    int osev_valu = -1;
    //
    switch (levivk) {
        case OSEV_POST:
            // xKILL_QUOTE(pamvp + 0x01)
            osev_valu = osev_inten_post(osev_resp, oclie, osev_obid, pamvp);
            break;
        case OSEV_STATUS:
            // xKILL_QUOTE(pamvp + 0x01)
            if (STAIU_INVALID == invok) return -1;
            osev_valu = osev_inten_statu(osev_resp, oclie, osev_obid, osev_status_tab[invok], pamvp);
            break;
        case OSEV_COMAND:
            // xKILL_QUOTE(pamvp + 0x01)
            if (COMDI_INVALID == invok) return -1;
            osev_valu = osev_inten_comnd(osev_resp, oclie, osev_obid, osev_comand_tab[invok], pamvp);
            break;
        case OSEV_PRIVILE:
            // xKILL_QUOTE(pamvp + 0x01)
            if (PRIVI_INVALID == invok) return -1;
            osev_valu = osev_inten_privi(osev_resp, oclie, osev_obid, osev_privile_tab[invok], pamvp);
            break;
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return osev_valu;
}

//

int base_leve_inte(resp_data_t *base_resp, unsigned int levivk, unsigned int invok, osev_clie *oclie, osv_oid_t *base_obid, const char **pamvp) {
    int base_valu = -1;
    //
    switch (levivk) {
        case BASE_POST:
            // xKILL_QUOTE(pamvp + 0x01)
            base_valu = base_inten_post(base_resp, oclie, base_obid, pamvp);
            break;
        case BASE_STATUS:
            // xKILL_QUOTE(pamvp + 0x01)
            if (STAIU_INVALID == invok) return -1;
            base_valu = base_inten_statu(base_resp, oclie, base_obid, base_status_tab[invok], pamvp);
            break;
        case BASE_COMAND:
            // xKILL_QUOTE(pamvp + 0x01)
            if (COMDI_INVALID == invok) return -1;
            base_valu = base_inten_comnd(base_resp, oclie, base_obid, base_comand_tab[invok], pamvp);
            break;
        case BASE_PRIVILE:
            // xKILL_QUOTE(pamvp + 0x01)
            if (PRIVI_INVALID == invok) return -1;
            base_valu = base_inten_privi(base_resp, oclie, base_obid, base_privile_tab[invok], pamvp);
            break;
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return base_valu;
}
//

int quit_cont(osev_clie *oclie, osvp_auth *clie_auth) {
    resp_head dest_resp;
    if (done_clie_destroy(&dest_resp, oclie)) {
        OSEVPrintErro("oclie destroy error!", dest_resp.status_code);
        outpu_respo_code(dest_resp.status_code);
    }
    //
    resp_data_t crea_resp;
    if (osev_clie_create(&crea_resp, oclie, clie_auth)) {
        OSEVPrintErro("oclie create error!", crea_resp.status_code);
        outpu_excep_code(&crea_resp);
        return -1;
    }
    //
    return 0x00;
}

void _quit_osev_(osev_clie *oclie) {
    resp_head dest_resp;
    if (done_clie_destroy(&dest_resp, oclie)) {
        OSEVPrintErro("oclie destroy error!", dest_resp.status_code);
        outpu_respo_code(dest_resp.status_code);
    }
}

// modify method

int leve_cont_one(resp_data_t *lev1_resp, unsigned int levivk, unsigned int invok, osev_clie *oclie, osv_oid_t *lv2p_obid, const char **pamvp) {
    int lev1_valu = -1;
    //
    switch (levivk) {
        case LEVO_POST:
            // quote_decode(pamvp[0x00]);
            lev1_valu = lev1_invok_post(lev1_resp, oclie, lv2p_obid, pamvp);
            break;
        case LEVO_STATUS:
            // quote_decode(pamvp[0x00]);
            if (ISTATU_INVALID == invok) return -1;
            lev1_valu = lev1_invok_statu(lev1_resp, oclie, lv2p_obid, invok_status_tab[invok], pamvp);
            break;
        case LEVO_CREATE:
            // quote_decode(pamvp[0x00]);
            lev1_valu = lev1_invok_creat(lev1_resp, oclie, lv2p_obid, pamvp);
            break;
        case LEVO_REPLACE:
            // quote_decode(pamvp[0x00]);
            lev1_valu = lev1_invok_repla(lev1_resp, oclie, lv2p_obid, pamvp);
            break;
        case LEVO_DROP:
            // quote_decode(pamvp[0x00]);
            lev1_valu = lev1_invok_drop(lev1_resp, oclie, lv2p_obid, pamvp);
            break;
        case LEVO_INTEGRA:
            // quote_decode(pamvp[0x00]);
            lev1_valu = lev1_invok_integra(lev1_resp, oclie, lv2p_obid, pamvp);
            break;
        case LEVO_RELOAD:
            // quote_decode(pamvp[0x00]);
            lev1_valu = lev1_invok_reload(lev1_resp, oclie, lv2p_obid, pamvp);
            break;
        case LEVO_INVALID:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return lev1_valu;
}

// modify method

int leve_cont_twop(resp_data_t *lv2p_resp, unsigned int levivk, unsigned int invok, osev_clie *oclie, const char **pamvp) {
    CLIT_PF("[FUNC]:leve_cont_twop\n");
    int lv2p_valu = -1;
    //
    switch (levivk) {
        case LVTP_POST:
            // quote_decode(pamvp[0x00]);
            lv2p_valu = lv2p_colle_post(lv2p_resp, oclie, pamvp);
            break;
        case LVTP_STATUS:
            // quote_decode(pamvp[0x00]);
            if (CSTATU_INVALID == invok) return -1;
            lv2p_valu = lv2p_colle_statu(lv2p_resp, oclie, colle_status_tab[invok], pamvp);
            break;
        case LVTP_CREATE:
            // quote_decode(pamvp[0x00]);
            CLIT_PF("LVTP_CREATE, pamvp[0x00]:|%s|\n", pamvp[0x00]);
            CLIT_PF("LVTP_CREATE, pamvp[0x01]:|%s|\n", pamvp[0x01]);
            CLIT_PF("LVTP_CREATE, pamvp[0x02]:|%s|\n", pamvp[0x02]);
            lv2p_valu = lv2p_colle_creat(lv2p_resp, oclie, pamvp);
            break;
        case LVTP_REPLACE:
            // quote_decode(pamvp[0x00]);
            lv2p_valu = lv2p_colle_repla(lv2p_resp, oclie, pamvp);
            break;
        case LVTP_DROP:
            // quote_decode(pamvp[0x00]);
            lv2p_valu = lv2p_colle_drop(lv2p_resp, oclie, pamvp);
            break;
        case LVTP_INTEGRA:
            // quote_decode(pamvp[0x00]);
            lv2p_valu = lv2p_colle_integra(lv2p_resp, oclie, pamvp);
            break;
        case LVTP_RELOAD:
            // quote_decode(pamvp[0x00]);
            lv2p_valu = lv2p_colle_reload(lv2p_resp, oclie, pamvp);
            break;
        case LVTP_INVALID:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return lv2p_valu;
}

// modify method

int leve_cont_thre(resp_data_t *lev3_resp, unsigned int levivk, unsigned int invok, osev_clie *oclie, osv_oid_t *cont_obid, const char **pamvp) {
    cont_atti conat;
    int lev3_valu = -1;
    //
    switch (levivk) {
        case LEVT_POST:
            // quote_decode(pamvp[0x00]);
            lev3_valu = lev3_const_post(lev3_resp, oclie, cont_obid, pamvp);
            break;
        case LEVT_STATUS:
            // quote_decode(pamvp[0x00]);
            if (ESTATU_INVALID == invok) return -1;
            lev3_valu = lev3_const_statu(lev3_resp, oclie, cont_obid, const_status_tab[invok], pamvp);
            break;
        case LEVT_CREATE:
            lev3_valu = lev3_const_creat(lev3_resp, oclie, cont_obid, pamvp);
            break;
        case LEVT_DROP:
            // quote_decode(pamvp[0x00]);
            lev3_valu = lev3_const_drop(lev3_resp, oclie, cont_obid, pamvp);
            break;
        case LEVT_UPDATE:
            if (lev3_const_conat(&conat, oclie, cont_obid, FMTST_TIMEOUT_SECON))
                return -1;
            lev3_valu = lev3_const_updat(lev3_resp, oclie, cont_obid, pamvp, &conat);
            break;
        case LEVT_INSERT:
            if (lev3_const_conat(&conat, oclie, cont_obid, FMTST_TIMEOUT_SECON))
                return -1;
            lev3_valu = lev3_const_inser(lev3_resp, oclie, cont_obid, pamvp, &conat);
            break;
        case LEVT_SEARCH:
            // quote_decode(pamvp[0x00]);
            lev3_valu = lev3_const_searo(lev3_resp, oclie, cont_obid, pamvp);
            break;
        case LEVT_INVOKE:
            // xKILL_QUOTE(pamvp)
            lev3_valu = lev3_const_invok(lev3_resp, oclie, cont_obid, pamvp);
            break;
        case LEVT_INVALID:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return lev3_valu;
}

// modify method

int leve_cont_foup(resp_data_t *lv4p_resp, unsigned int levivk, unsigned int invok, osev_clie *oclie, const char **pamvp) {
    cont_atti conat;
    int lv4p_valu = -1;
    //
    switch (levivk) {
        case LVFP_POST:
            // quote_decode(pamvp[0x00]);
            lv4p_valu = lv4p_query_post(lv4p_resp, oclie, pamvp);
            break;
        case LVFP_STATUS:
            // quote_decode(pamvp[0x00]);
            if (QSTATU_INVALID == invok) return -1;
            lv4p_valu = lv4p_query_statu(lv4p_resp, oclie, query_status_tab[invok], pamvp);
            break;
        case LVFP_CREATE:
            // quote_decode(pamvp[0x00]);
            // quote_decode(pamvp[0x02]);
            lv4p_valu = lv4p_query_creat(lv4p_resp, oclie, pamvp);
            break;
        case LVFP_DROP:
            // quote_decode(pamvp[0x00]);
            lv4p_valu = lv4p_query_drop(lv4p_resp, oclie, pamvp);
            break;
        case LVFP_UPDATE:
            if (lv4p_query_conat(&conat, oclie, pamvp[0x00], FMTST_TIMEOUT_SECON))
                return -1;
            lv4p_valu = lv4p_query_updat(lv4p_resp, oclie, pamvp, &conat);
            break;
        case LVFP_INSERT:
            if (lv4p_query_conat(&conat, oclie, pamvp[0x00], FMTST_TIMEOUT_SECON))
                return -1;
            lv4p_valu = lv4p_query_inser(lv4p_resp, oclie, pamvp, &conat);
            break;
        case LVFP_SEARCH:
            lv4p_valu = lv4p_query_searq(lv4p_resp, oclie, pamvp);
            break;
        case LVFP_FACTORY:
            // quote_decode(pamvp[0x00]);
            lv4p_valu = lv4p_query_facto(lv4p_resp, oclie, pamvp);
            break;
        case LVFP_INVOKE:
            // xKILL_QUOTE(pamvp)
            lv4p_valu = lv4p_query_invok(lv4p_resp, oclie, pamvp);
            break;
        case LVFP_INVALID:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return lv4p_valu;
}


