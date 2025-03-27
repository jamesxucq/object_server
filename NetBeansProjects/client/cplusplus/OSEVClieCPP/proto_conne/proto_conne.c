
#include "osev_common/commo_header.h"
#include "reque_respo.h"
#include "conatt.h"
#include "../parser/parse_respo.h"

#include "proto_conne.h"

// get lv2pn version
// parm[0x00]:name space parm[0x01]:list type
// #define LIST_LVTP_ATTRIB    0x0002
#define LVTP_LIST_ATTRIB    "2I"

// trans-serve

int lv2p_colle_versi(unsigned long long *lv2p_versi, const osev_clie *clie, const char *lv2pn) {
    const char *parms[0x03] = {lv2pn, LVTP_LIST_ATTRIB, NULL};
    resp_data_t colle_resp;
    pamstyl_t pamsty;
    pack_disti_pamstyl(&pamsty, parms);
    CLIE_COLLE_BZL(&colle_resp, clie->conne_sock, COLE_STATU | CSTAT_LIST, &clie->clie_obid, &pamsty);
    //
    if (OK != colle_resp.status_code)
        return colle_resp.status_code;
    if (!parse_colle_versi(lv2p_versi, &colle_resp))
        return -1;
    return 0x00;
}

//

int lv2p_colle_attrib(unsigned long long *lv2p_versi, unsigned int *lv2p_extern, const osev_clie *clie, const char *lv2pn) {
    const char *parms[0x03] = {lv2pn, LVTP_LIST_ATTRIB, NULL};
    resp_data_t colle_resp;
    pamstyl_t pamsty;
    pack_disti_pamstyl(&pamsty, parms);
    CLIE_COLLE_BZL(&colle_resp, clie->conne_sock, COLE_STATU | CSTAT_LIST, &clie->clie_obid, &pamsty);
    //
    if (OK != colle_resp.status_code)
        return colle_resp.status_code;
    if (!parse_colle_attrib(lv2p_versi, lv2p_extern, &colle_resp))
        return -1;
    return 0x00;
}

// unsigned long long last_active

int lev3_const_conat(cont_atti *conat, const osev_clie *clie, osv_oid_t *cont_obid, long time_out) {
    INITI_CONATT_BZL(-1)
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
