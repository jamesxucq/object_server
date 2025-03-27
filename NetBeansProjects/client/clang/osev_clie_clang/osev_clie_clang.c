#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "dstri_utili.h"
#include "osco_socks.h"
#include "parse_respo.h"
#include "clie_obje.h"
#include "clie_bzl.h"
#include "conatt.h"

#include "osev_clie_clang.h"

//

int osev_clie_create(OUT resp_data_t *crea_resp, OUT osev_clie *clie, osvp_auth *clie_auth) {
    OSEVPF("[FUNC]:osev_clie_create\n");
    INITI_CONATT_BZL(-1)
            // OSEVPF("addr:|%s| port:%d\n", addr, port);
            // OSEVPF("osev_base:|%s| uname:|%s| paswd:|%s|\n", osev_base, uname, paswd);
            unsigned char req_valid_memo[ESCA_ENTICON_PART + VALID_LENGTH];
    unsigned char salt_memo[ESCA_ENTICON_PART + SALT_LENGTH];
    MAKE_ESCHEAD_BINA(req_valid_memo, VALID_LENGTH);
    MAKE_ESCHEAD_BINA(salt_memo, SALT_LENGTH);
    const char *parms[0x05] = {clie_auth->authe.user_name, (char *) req_valid_memo, (char *) salt_memo, clie_auth->osev_base, NULL};
    //
    creat_authe_iacv(ESCA_ECONTE_POSI(req_valid_memo), ESCA_ECONTE_POSI(salt_memo), clie_auth->authe.user_name, clie_auth->authe.pass_word);
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, parms))
        return -1;
    //
    strcpy(clie->clie_name, clie_auth->osev_base);
    clie->conne_sock = osco_connect(&clie_auth->saddr);
    if (-1 == clie->conne_sock) {
        OSEVPF("client connect execep!\n");
        OSCO_CLOSE(clie->conne_sock);
        return -1;
    }
    if (clie_oscrea_bzl(crea_resp, clie->conne_sock, &pamsty)) {
        OSEVPF("client create error!\n");
        OSCO_CLOSE(clie->conne_sock);
        return -1;
    }
    if (OK != crea_resp->status_code) {
        OSEVPF("client create execep!\n");
        OSCO_CLOSE(clie->conne_sock);
        return crea_resp->status_code;
    }
    // stroid(&clie->clie_obid, crea_resp->resp_memo);
    OBID_BINARY_COPY(&clie->clie_obid, (osv_oid_t *) crea_resp->resp_memo)
#ifdef _DEBUG
            // OSEVPF("[DEBUG] osev_base:|%s| user_name:|%s|\n", authi->auth.osev_base, authi->auth.user_name);
            // char temp[33];
            // OSEVPF("[DEBUG] clie->clie_obid:|%s|\n", oidstr(temp, &clie->clie_obid));
            // OSEVPF("Client create OK!\n");
#endif
            return 0x00;
}

int base_clie_create(OUT resp_data_t *crea_resp, OUT osev_clie *clie, osvp_auth *clie_auth) {
    OSEVPF("[FUNC]:base_clie_create\n");
    INITI_CONATT_BZL(-1)
            // OSEVPF("addr:|%s| port:%d\n", addr, port);
            // OSEVPF("osev_base:|%s| uname:|%s| paswd:|%s|\n", osev_base, uname, paswd);
            unsigned char req_valid_memo[ESCA_ENTICON_PART + VALID_LENGTH];
    unsigned char salt_memo[ESCA_ENTICON_PART + SALT_LENGTH];
    MAKE_ESCHEAD_BINA(req_valid_memo, VALID_LENGTH);
    MAKE_ESCHEAD_BINA(salt_memo, SALT_LENGTH);
    const char *parms[0x05] = {clie_auth->authe.user_name, (char *) req_valid_memo, (char *) salt_memo, clie_auth->osev_base, NULL};
    //
    creat_authe_iacv(ESCA_ECONTE_POSI(req_valid_memo), ESCA_ECONTE_POSI(salt_memo), clie_auth->authe.user_name, clie_auth->authe.pass_word);
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, parms))
        return -1;
    //
    strcpy(clie->clie_name, clie_auth->osev_base);
    clie->conne_sock = osco_connect(&clie_auth->saddr);
    if (-1 == clie->conne_sock) {
        OSEVPF("client connect execep!\n");
        OSCO_CLOSE(clie->conne_sock);
        return -1;
    }
    if (clie_bscrea_bzl(crea_resp, clie->conne_sock, &pamsty)) {
        OSEVPF("client create error!\n");
        OSCO_CLOSE(clie->conne_sock);
        return -1;
    }
    if (OK != crea_resp->status_code) {
        OSEVPF("client create execep!\n");
        OSCO_CLOSE(clie->conne_sock);
        return crea_resp->status_code;
    }
    // stroid(&clie->clie_obid, crea_resp->resp_memo);
    OBID_BINARY_COPY(&clie->clie_obid, (osv_oid_t *) crea_resp->resp_memo)
#ifdef _DEBUG
            // OSEVPF("[DEBUG] osev_base:|%s| user_name:|%s|\n", authi->auth.osev_base, authi->auth.user_name);
            // char temp[33];
            // OSEVPF("[DEBUG] clie->clie_obid:|%s|\n", oidstr(temp, &clie->clie_obid));
            // OSEVPF("Client create OK!\n");
#endif
            return 0x00;
}

//

int kaliv_clie_continue(resp_head *kaliv_resp, const osev_clie *clie) {
    OSEVPF("[FUNC]:kaliv_clie_continue\n");
    CLIE_KALIVE_BZL(kaliv_resp, clie->conne_sock, &clie->clie_obid);
    return (OK == kaliv_resp->status_code) ? 0x00 : kaliv_resp->status_code;
}

// osev status // stat_obid: osev base obid
// osev privile // priv_obid: osev base obid

int osev_inten_post(resp_data_t *post_resp, const osev_clie *clie, osv_oid_t *post_obid, const char **pamvp) {
    OSEVPF("[FUNC]:osev_inten_post\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_OSEV_BZL(post_resp, clie->conne_sock, OPOST, post_obid, &pamsty);
    //
    return (OK == post_resp->status_code) ? 0x00 : post_resp->status_code;
}

int osev_inten_statu(resp_data_t *statu_resp, const osev_clie *clie, osv_oid_t *stat_obid, unsigned int layout, const char **pamvp) {
    OSEVPF("[FUNC]:osev_inten_statu, layout:|%04x|\n", layout);
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_OSEV_BZL(statu_resp, clie->conne_sock, OSTATUS | layout, stat_obid, &pamsty);
    //
    return (OK == statu_resp->status_code) ? 0x00 : statu_resp->status_code;
}

int osev_inten_comnd(resp_data_t *comnd_resp, const osev_clie *clie, osv_oid_t *comd_obid, unsigned int layout, const char **pamvp) {
    OSEVPF("[FUNC]:osev_inten_comnd, layout:|%04x|\n", layout);
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_OSEV_BZL(comnd_resp, clie->conne_sock, OCOMAND | layout, comd_obid, &pamsty);
    //
    return (OK == comnd_resp->status_code) ? 0x00 : comnd_resp->status_code;
}

int osev_inten_privi(resp_data_t *privi_resp, const osev_clie *clie, osv_oid_t *priv_obid, unsigned int layout, const char **pamvp) {
    OSEVPF("[FUNC]:osev_inten_privi, layout:|%04x|\n", layout);
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_OSEV_BZL(privi_resp, clie->conne_sock, OPRIVI | layout, priv_obid, &pamsty);
    //
    return (OK == privi_resp->status_code) ? 0x00 : privi_resp->status_code;
}


// base status // stat_obid: osev base obid;
// base privile // priv_obid: osev base obid

int base_inten_post(resp_data_t *post_resp, const osev_clie *clie, osv_oid_t *post_obid, const char **pamvp) {
    OSEVPF("[FUNC]:base_inten_post\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_BASE_BZL(post_resp, clie->conne_sock, BPOST, post_obid, &pamsty);
    //
    return (OK == post_resp->status_code) ? 0x00 : post_resp->status_code;
}

int base_inten_statu(resp_data_t *statu_resp, const osev_clie *clie, osv_oid_t *stat_obid, unsigned int layout, const char **pamvp) {
    OSEVPF("[FUNC]:base_inten_statu, layout:|%04x|\n", layout);
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_BASE_BZL(statu_resp, clie->conne_sock, BSTATUS | layout, stat_obid, &pamsty);
    //
    return (OK == statu_resp->status_code) ? 0x00 : statu_resp->status_code;
}

int base_inten_comnd(resp_data_t *comnd_resp, const osev_clie *clie, osv_oid_t *comd_obid, unsigned int layout, const char **pamvp) {
    OSEVPF("[FUNC]:base_inten_comnd, layout:|%04x|\n", layout);
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_BASE_BZL(comnd_resp, clie->conne_sock, BCOMAND | layout, comd_obid, &pamsty);
    //
    return (OK == comnd_resp->status_code) ? 0x00 : comnd_resp->status_code;
}

int base_inten_privi(resp_data_t *privi_resp, const osev_clie *clie, osv_oid_t *priv_obid, unsigned int layout, const char **pamvp) {
    OSEVPF("[FUNC]:base_inten_privi, layout:|%04x|\n", layout);
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_BASE_BZL(privi_resp, clie->conne_sock, BPRIVI | layout, priv_obid, &pamsty);
    //
    return (OK == privi_resp->status_code) ? 0x00 : privi_resp->status_code;
}


// method invoke
// parm[0x00]:name space parm[0x01]:list type

int lev1_invok_post(resp_data_t *invok_resp, const osev_clie *clie, osv_oid_t *lv2p_obid, const char **pamvp) {
    OSEVPF("[FUNC]:lev1_invok_post\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_INVOK_BZL(invok_resp, clie->conne_sock, INVO_POST, lv2p_obid, &pamsty);
    //
    return (OK == invok_resp->status_code) ? 0x00 : invok_resp->status_code;
}

int lev1_invok_statu(resp_data_t *invok_resp, const osev_clie *clie, osv_oid_t *lv2p_obid, unsigned int layout, const char **pamvp) {
    OSEVPF("[FUNC]:lev1_invok_statu, layout:|%04x|\n", layout);
    pamstyl_t pamsty;
    pack_disti_pamstyl(&pamsty, pamvp);
    CLIE_INVOK_BZL(invok_resp, clie->conne_sock, INVO_STATU | layout, lv2p_obid, &pamsty);
    //
    return (OK == invok_resp->status_code) ? 0x00 : invok_resp->status_code;
}

int lev1_invok_creat(resp_data_t *invok_resp, const osev_clie *clie, osv_oid_t *lv2p_obid, const char **pamvp) {
    OSEVPF("[FUNC]:lev1_invok_creat\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_dstri_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_INVOK_BZL(invok_resp, clie->conne_sock, INVO_CREAT, lv2p_obid, &pamsty);
    //
    return (OK == invok_resp->status_code) ? 0x00 : invok_resp->status_code;
}

int lev1_invok_repla(resp_data_t *invok_resp, const osev_clie *clie, osv_oid_t *lv2p_obid, const char **pamvp) {
    OSEVPF("[FUNC]:lev1_invok_repla\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_INVOK_BZL(invok_resp, clie->conne_sock, INVO_REPLA, lv2p_obid, &pamsty);
    //
    return (OK == invok_resp->status_code) ? 0x00 : invok_resp->status_code;
}

int lev1_invok_drop(resp_data_t *invok_resp, const osev_clie *clie, osv_oid_t *lv2p_obid, const char **pamvp) {
    OSEVPF("[FUNC]:lev1_invok_drop\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_dstri_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_INVOK_BZL(invok_resp, clie->conne_sock, INVO_DROP, lv2p_obid, &pamsty);
    //
    return (OK == invok_resp->status_code) ? 0x00 : invok_resp->status_code;
}

int lev1_invok_integra(resp_data_t *invok_resp, const osev_clie *clie, osv_oid_t *lv2p_obid, const char **pamvp) {
    OSEVPF("[FUNC]:lev1_invok_integra\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_dstri_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_INVOK_BZL(invok_resp, clie->conne_sock, INVO_INTEGRA, lv2p_obid, &pamsty);
    //
    return (OK == invok_resp->status_code) ? 0x00 : invok_resp->status_code;
}

int lev1_invok_reload(resp_data_t *invok_resp, const osev_clie *clie, osv_oid_t *lv2p_obid, const char **pamvp) {
    OSEVPF("[FUNC]:lev1_invok_reload\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_dstri_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_INVOK_BZL(invok_resp, clie->conne_sock, INVO_RELOAD, lv2p_obid, &pamsty);
    //
    return (OK == invok_resp->status_code) ? 0x00 : invok_resp->status_code;
}
// class invoke
// class colle // modify method
// parm[0x00]:name space parm[0x01]:list type

int lv2p_colle_post(resp_data_t *colle_resp, const osev_clie *clie, const char **pamvp) {
    OSEVPF("[FUNC]:lv2p_colle_post\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_COLLE_BZL(colle_resp, clie->conne_sock, COLE_POST, &clie->clie_obid, &pamsty);
    //
    return (OK == colle_resp->status_code) ? 0x00 : colle_resp->status_code;
}

int lv2p_colle_statu(resp_data_t *colle_resp, const osev_clie *clie, unsigned int layout, const char **pamvp) {
    OSEVPF("[FUNC]:lv2p_colle_statu, layout:|%04x|\n", layout);
    pamstyl_t pamsty;
    pack_disti_pamstyl(&pamsty, pamvp);
    CLIE_COLLE_BZL(colle_resp, clie->conne_sock, COLE_STATU | layout, &clie->clie_obid, &pamsty);
    //
    return (OK == colle_resp->status_code) ? 0x00 : colle_resp->status_code;
}

int lv2p_colle_creat(resp_data_t *colle_resp, const osev_clie *clie, const char **pamvp) {
    OSEVPF("[FUNC]:lv2p_colle_creat\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_dstri_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_COLLE_BZL(colle_resp, clie->conne_sock, COLE_CREAT, &clie->clie_obid, &pamsty);
    //
    return (OK == colle_resp->status_code) ? 0x00 : colle_resp->status_code;
}

int lv2p_colle_repla(resp_data_t *colle_resp, const osev_clie *clie, const char **pamvp) {
    OSEVPF("[FUNC]:lv2p_colle_repla\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_COLLE_BZL(colle_resp, clie->conne_sock, COLE_REPLA, &clie->clie_obid, &pamsty);
    //
    return (OK == colle_resp->status_code) ? 0x00 : colle_resp->status_code;
}

int lv2p_colle_drop(resp_data_t *colle_resp, const osev_clie *clie, const char **pamvp) {
    OSEVPF("[FUNC]:lv2p_colle_drop\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_dstri_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_COLLE_BZL(colle_resp, clie->conne_sock, COLE_DROP, &clie->clie_obid, &pamsty);
    //
    return (OK == colle_resp->status_code) ? 0x00 : colle_resp->status_code;
}

int lv2p_colle_integra(resp_data_t *colle_resp, const osev_clie *clie, const char **pamvp) {
    OSEVPF("[FUNC]:lv2p_colle_integra\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_dstri_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_COLLE_BZL(colle_resp, clie->conne_sock, COLE_INTEGRA, &clie->clie_obid, &pamsty);
    //
    return (OK == colle_resp->status_code) ? 0x00 : colle_resp->status_code;
}

int lv2p_colle_reload(resp_data_t *colle_resp, const osev_clie *clie, const char **pamvp) {
    OSEVPF("[FUNC]:lv2p_colle_reload\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_dstri_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_COLLE_BZL(colle_resp, clie->conne_sock, COLE_RELOAD, &clie->clie_obid, &pamsty);
    //
    return (OK == colle_resp->status_code) ? 0x00 : colle_resp->status_code;
}

// construct
// construct // modify method

int lev3_const_post(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp) {
    OSEVPF("[FUNC]:lev3_const_post\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_CONST_BZL(const_resp, clie->conne_sock, ENTI_POST, cont_obid, &pamsty);
    //
    return (OK == const_resp->status_code) ? 0x00 : const_resp->status_code;
}

int lev3_const_statu(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, unsigned int layout, const char **pamvp) {
    OSEVPF("[FUNC]:lev3_const_statu, layout:|%04x|\n", layout);
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_CONST_BZL(const_resp, clie->conne_sock, ENTI_STATU | layout, cont_obid, &pamsty);
    //
    return (OK == const_resp->status_code) ? 0x00 : const_resp->status_code;
}

int lev3_const_creat(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp) {
    OSEVPF("[FUNC]:lev3_const_creat\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_CONST_BZL(const_resp, clie->conne_sock, ENTI_CREAT, cont_obid, &pamsty);
    //
    return (OK == const_resp->status_code) ? 0x00 : const_resp->status_code;
}

int lev3_const_drop(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp) {
    OSEVPF("[FUNC]:lev3_const_drop\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_CONST_BZL(const_resp, clie->conne_sock, ENTI_DROP, cont_obid, &pamsty);
    //
    return (OK == const_resp->status_code) ? 0x00 : const_resp->status_code;
}

// char fmtst[FMTST_COUNT_ZTAI]; // todo:

int lev3_const_updat(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp, cont_atti * conat) {
    OSEVPF("[FUNC]:lev3_const_updat\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_paki(&pamsty, pamvp, conat->fmtst))
        return -1;
    CLIE_CONST_BZL(const_resp, clie->conne_sock, ENTI_UPDAT, cont_obid, &pamsty);
    //
    return (OK == const_resp->status_code) ? 0x00 : const_resp->status_code;
}

int lev3_const_inser(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp, cont_atti * conat) {
    OSEVPF("[FUNC]:lev3_const_inser\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_paki(&pamsty, pamvp, conat->fmtst))
        return -1;
    CLIE_CONST_BZL(const_resp, clie->conne_sock, ENTI_INSER, cont_obid, &pamsty);
    //
    return (OK == const_resp->status_code) ? 0x00 : const_resp->status_code;
}

int lev3_const_searo(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp) {
    OSEVPF("[FUNC]:lev3_const_searo\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_CONST_BZL(const_resp, clie->conne_sock, ENTI_SEARO, cont_obid, &pamsty);
    //
    return (OK == const_resp->status_code) ? 0x00 : const_resp->status_code;
}

int lev3_const_invok(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp) {
    OSEVPF("[FUNC]:lev3_const_invok\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_einvo_pamstyl(&pamsty, (char **) pamvp))
        return -1;
    CLIE_CONST_BZL(const_resp, clie->conne_sock, ENTI_INVOK, cont_obid, &pamsty);
    //
    return (OK == const_resp->status_code) ? 0x00 : const_resp->status_code;
}

// query // modify method

int lv4p_query_post(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp) {
    OSEVPF("[FUNC]:lv4p_query_post\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_POST, &clie->clie_obid, &pamsty);
    //
    return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
}

int lv4p_query_statu(resp_data_t *query_resp, const osev_clie *clie, unsigned int layout, const char **pamvp) {
    OSEVPF("[FUNC]:lv4p_query_statu, layout:|%04x|\n", layout);
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_STATU | layout, &clie->clie_obid, &pamsty);
    //
    return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
}

int lv4p_query_creat(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp) {
    OSEVPF("[FUNC]:lv4p_query_creat\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_CREAT, &clie->clie_obid, &pamsty);
    //
    return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
}

int lv4p_query_drop(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp) {
    OSEVPF("[FUNC]:lv4p_query_drop\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_dstri_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_DROP, &clie->clie_obid, &pamsty);
    //
    return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
}

int lv4p_query_updat(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp, cont_atti * conat) {
    OSEVPF("[FUNC]:lv4p_query_updat\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_qinup_paki(&pamsty, pamvp, conat->fmtst))
        return -1;
    CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_UPDAT, &clie->clie_obid, &pamsty);
    //
    return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
}

int lv4p_query_inser(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp, cont_atti * conat) {
    OSEVPF("[FUNC]:lv4p_query_inser\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_qinup_paki(&pamsty, pamvp, conat->fmtst))
        return -1;
    CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_INSER, &clie->clie_obid, &pamsty);
    //
    return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
}

int lv4p_query_searq(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp) {
    OSEVPF("[FUNC]:lv4p_query_searq\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_SEARQ, &clie->clie_obid, &pamsty);
    //
    return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
}

int lv4p_query_invok(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp) {
    OSEVPF("[FUNC]:lv4p_query_invok\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_qinvo_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_INVOK, &clie->clie_obid, &pamsty);
    //
    return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
}

int lv4p_query_facto(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp) {
    OSEVPF("[FUNC]:lv4p_query_facto\n");
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
        return -1;
    CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_FACTO, &clie->clie_obid, &pamsty);
    //
    return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
}

// get lv2pn version
// parm[0x00]:name space parm[0x01]:list type
// #define LIST_LVTP_ATTRIB    0x0002
#define LVTP_LIST_ATTRIB    "2I"

// trans-serve

int lv2p_colle_versi(unsigned long long *lv2p_versi, const osev_clie *clie, const char *lv2pn) {
    OSEVPF("[FUNC]:lv2p_colle_versi\n");
    const char *parms[0x03] = {lv2pn, LVTP_LIST_ATTRIB, NULL};
    resp_data_t colle_resp;
    pamstyl_t pamsty;
    pack_disti_pamstyl(&pamsty, parms);
    CLIE_COLLE_BZL(&colle_resp, clie->conne_sock, COLE_STATU | CSTAT_LIST, &clie->clie_obid, &pamsty);
    //
    if (OK != colle_resp.status_code) return colle_resp.status_code;
    if (!parse_colle_versi(lv2p_versi, &colle_resp))
        return -1;
    return 0x00;
}

int lv2p_colle_extern(bool_osv *lv2p_extern, const osev_clie *clie, const char *lv2pn) {
    OSEVPF("[FUNC]:lv2p_colle_extern\n");
    const char *parms[0x03] = {lv2pn, LVTP_LIST_ATTRIB, NULL};
    resp_data_t colle_resp;
    pamstyl_t pamsty;
    pack_disti_pamstyl(&pamsty, parms);
    CLIE_COLLE_BZL(&colle_resp, clie->conne_sock, COLE_STATU | CSTAT_LIST, &clie->clie_obid, &pamsty);
    //
    if (OK != colle_resp.status_code) return colle_resp.status_code;
    if (!parse_colle_extern(lv2p_extern, &colle_resp))
        return -1;
    //
    return 0x00;
}

//
// #define LIST_LVTP_CONTEN    0x0020
#define LVTP_LIST_CONTEN    "32I"

int lv2p_colle_conte(char *lv2p_conte, const osev_clie *clie, const char *lv2pn) {
    OSEVPF("[FUNC]:lv2p_colle_conte\n");
    const char *parms[0x03] = {lv2pn, LVTP_LIST_CONTEN, NULL};
    resp_data_t colle_resp;
    pamstyl_t pamsty;
    pack_disti_pamstyl(&pamsty, parms);
    CLIE_COLLE_BZL(&colle_resp, clie->conne_sock, COLE_STATU | CSTAT_LIST, &clie->clie_obid, &pamsty);
    //
    if (OK != colle_resp.status_code) return colle_resp.status_code;
    if (!parse_colle_conte(lv2p_conte, &colle_resp))
        return -1;
    return 0x00;
}

// parm[0x00]:name space parm[0x01]:list type

int lev1_invok_conte(char *lev1_conte, const osev_clie *clie, osv_oid_t *lv2p_obid, const char *lev1n) {
    OSEVPF("[FUNC]:lev1_invok_conte\n");
    const char *parms[0x03] = {lev1n, LVTP_LIST_CONTEN, NULL};
    resp_data_t invok_resp;
    pamstyl_t pamsty;
    pack_disti_pamstyl(&pamsty, parms);
    CLIE_INVOK_BZL(&invok_resp, clie->conne_sock, INVO_STATU | ISTAT_LIST, lv2p_obid, &pamsty);
    //
    if (OK != invok_resp.status_code) return invok_resp.status_code;
    if (!parse_invok_conte(lev1_conte, &invok_resp))
        return -1;
    return 0x00;
}

// unsigned long long last_active

int lev3_const_conat(cont_atti *conat, const osev_clie *clie, osv_oid_t *cont_obid, long time_out) {
    OSEVPF("[FUNC]:lev3_const_conat\n");
    cont_atti *find_coat = find_conatt_bzl(conat, (osv_oid_t *) & clie->clie_obid, cont_obid);
    if (find_coat) {
        unsigned long long now_time = time(NULL);
        if (time_out > (now_time - conat->last_active))
            return 0x00;
    }
    //
    resp_data_t const_resp;
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_none_pamstyl(&pamsty))
        return -1;
    CLIE_CONST_BZL(&const_resp, clie->conne_sock, ENTI_STATU | ESTAT_ATTRIB, cont_obid, &pamsty);
    //
    if (OK != const_resp.status_code) return const_resp.status_code;
    if (!parse_const_conat(conat, &const_resp))
        return -1;
    build_local_fmtst(conat->fmtst);
    conat->last_active = time(NULL);
    //
    if (find_coat) {
        updat_conatt_bzl(find_coat, conat);
    } else {
        inser_conatt_bzl((osv_oid_t *) & clie->clie_obid, cont_obid, conat);
    }
    //
    return 0x00;
}

//

int lv4p_query_conat(cont_atti *conat, const osev_clie *clie, const char *cont_iden, long time_out) {
    OSEVPF("[FUNC]:lv4p_query_conat\n");
    if (OBJE_IDENT_TYPE != ((char *) cont_iden)[ESCA_NODTYP_PART])
        return -1;
    cont_atti *find_coat = find_conatt_bzl(conat, (osv_oid_t *) & clie->clie_obid, (osv_oid_t *) ((char *) cont_iden + ESCA_OBIDCON_PART));
    if (find_coat) {
        unsigned long long now_time = time(NULL);
        if (time_out > (now_time - conat->last_active))
            return 0x00;
    }
    //
    const char *parms[0x02] = {cont_iden, NULL};
    resp_data_t query_resp;
    pamstyl_t pamsty;
    if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, parms))
        return -1;
    CLIE_QUERY_BZL(&query_resp, clie->conne_sock, QUER_STATU | QSTAT_ATTRIB, &clie->clie_obid, &pamsty);
    //
    if (OK != query_resp.status_code) return query_resp.status_code;
    if (!parse_query_conat(conat, &query_resp))
        return -1;
    conat->last_active = time(NULL);
    //
    if (find_coat) {
        updat_conatt_bzl(find_coat, conat);
    } else {
        inser_conatt_bzl((osv_oid_t *) & clie->clie_obid, (osv_oid_t *) ((char *) cont_iden + ESCA_OBIDCON_PART), conat);
    }
    //
    return 0x00;
}















