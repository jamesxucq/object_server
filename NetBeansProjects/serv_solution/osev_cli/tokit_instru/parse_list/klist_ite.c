
#include "commo_header.h"
#include "osev_clie_clang.h"
#include "../../cstri_utili.h"

#include "parse_lev1.h"
#include "klist_ite.h"

// #define LIST_LVTP_OBJID     0x0001
#define INVO_LIST_OBJID        "1I"
// #define LIST_LVTP_ATTRIB    0x0002
#define INVO_LIST_ATTRIB       "2I"
// #define LIST_LVTP_EXPAND    0x0010
#define INVO_LIST_EXPAND       "16I"
// #define LIST_LVTP_CONTEN    0x0020
#define INVO_LIST_CONTEN       "32I"

//

int requ_lev1_iden(char *lev1_cont, osv_oid_t *coll_obid, char *lev1n, osev_clie *oclie) {
    const char *parms[0x03] = {lev1n, INVO_LIST_CONTEN, NULL};
    resp_data_t lev1_resp;
    // CLIT_PF("requ_lev1_iden\n");
    if (lev1_invok_statu(&lev1_resp, oclie, coll_obid, ISTAT_LIST, parms)) {
        OSEVPrintErro("invok list error!", lev1_resp.status_code);
        outpu_excep_code(&lev1_resp);
        return -1;
    }
    memcpy(lev1_cont, lev1_resp.resp_memo, lev1_resp.content_length);
    lev1_cont[lev1_resp.content_length] = '\0';
    //
    return lev1_resp.content_length;
}

int requ_lv2p_atti(char *lv2p_cont, const char *lv2pn, osev_clie *oclie) {
    const char *parms[0x03] = {lv2pn, INVO_LIST_ATTRIB, NULL};
    resp_data_t lv2p_resp;
    //
    if (lv2p_colle_statu(&lv2p_resp, oclie, CSTAT_LIST, parms)) {
        OSEVPrintErro("colle list error!", lv2p_resp.status_code);
        outpu_excep_code(&lv2p_resp);
        return -1;
    }
    memcpy(lv2p_cont, lv2p_resp.resp_memo, lv2p_resp.content_length);
    lv2p_cont[lv2p_resp.content_length] = '\0';
    //
    return lv2p_resp.content_length;
}

// extern integrality

int requ_lv2p_extint(bool_osv *lv2p_extern, bool_osv *lv2p_integr, char *lv2p_cont, const char *lv2pn, const osev_clie *oclie) {
    const char *parms[0x03] = {lv2pn, INVO_LIST_ATTRIB, NULL};
    resp_data_t lv2p_resp;
    //
    if (lv2p_colle_statu(&lv2p_resp, oclie, CSTAT_LIST, parms)) {
        OSEVPrintErro("colle list error!", lv2p_resp.status_code);
        outpu_excep_code(&lv2p_resp);
        return -1;
    }
    //
    if (OK != lv2p_resp.status_code) return lv2p_resp.status_code;
    if (!parse_colle_extint(lv2p_extern, lv2p_integr, &lv2p_resp))
        return -1;
    //
    memcpy(lv2p_cont, lv2p_resp.resp_memo, lv2p_resp.content_length);
    lv2p_cont[lv2p_resp.content_length] = '\0';
    //
    return lv2p_resp.content_length;
}

int requ_lv2p_expand(char *lv2p_cont, const char *lv2pn, osev_clie *oclie) {
    const char *parms[0x03] = {lv2pn, INVO_LIST_EXPAND, NULL};
    resp_data_t lv2p_resp;
    //
    if (lv2p_colle_statu(&lv2p_resp, oclie, CSTAT_LIST, parms)) {
        OSEVPrintErro("colle list error!", lv2p_resp.status_code);
        outpu_excep_code(&lv2p_resp);
        return -1;
    }
    memcpy(lv2p_cont, lv2p_resp.resp_memo, lv2p_resp.content_length);
    lv2p_cont[lv2p_resp.content_length] = '\0';
    //
    return lv2p_resp.content_length;
}

int requ_lv2p_conte(char *lv2p_cont, const char *lv2pn, osev_clie *oclie) {
    const char *parms[0x03] = {lv2pn, INVO_LIST_CONTEN, NULL};
    resp_data_t lv2p_resp;
    //
    if (lv2p_colle_statu(&lv2p_resp, oclie, CSTAT_LIST, parms)) {
        OSEVPrintErro("colle list error!", lv2p_resp.status_code);
        outpu_excep_code(&lv2p_resp);
        return -1;
    }
    memcpy(lv2p_cont, lv2p_resp.resp_memo, lv2p_resp.content_length);
    lv2p_cont[lv2p_resp.content_length] = '\0';
    //
    return lv2p_resp.content_length;
}

//

int split_lv2p_lev1(char *lv2p_decla, char *lev1np[LEVO_COUNT], char *_mline_, char *lv2p_cont) {
    // CLIT_PF("lv2p_cont:|%s|\n", lv2p_cont);
    char *last_str = split_class_conte(lv2p_decla, lv2p_cont);
    if (!last_str) return -1;
    int declen = last_str - lv2p_cont;
    // CLIT_PF("lv2p_decla:|%s|\n", lv2p_decla);
    // CLIT_PF("last_str:|%s|\n", last_str);
    split_method(lev1np, _mline_, last_str);
    return declen;
}
