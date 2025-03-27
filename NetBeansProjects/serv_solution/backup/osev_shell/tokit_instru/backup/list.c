#include <pthread.h>

#include "commo_header.h"

#include "ustri_utili.h"
#include "../shell_bzl.h"
#include "./parse_list/parse_lev1.h"
#include "list.h"
#include "../debug_funct_sh.h"

// #define LIST_LEVT_OBJID     0x0001
#define INVO_LIST_OBJID "OBJID"
#define INVO_LIST_ATTRIB "ATTRIB"
#define INVO_LIST_CONTEN "CONTENT"

//

static int list_lev1_iden(char *lev1_cont, osv_oid_t *coll_oid, char *lev1n, osev_clie *oclie) {
    char *parms[0x03] = {lev1n, INVO_LIST_CONTEN, NULL};
    resp_data_t onel_resp;
    // CLIEPF("list_lev1_iden\n");
    if (obje_invok_list(&onel_resp, oclie, coll_oid, parms))
        return -1;
    if (OK != onel_resp.resp_code) {
        OSEVPrintErro("invok list error!", onel_resp.resp_code);
        outpu_excep_code(&onel_resp);
        return -1;
    }
    memcpy(lev1_cont, onel_resp.resp_data, onel_resp.resp_leng);
    lev1_cont[onel_resp.resp_leng] = '\0';
    //
    return onel_resp.resp_leng;
}

static int list_lev2_attri(char *lev2_cont, char *lev2n, osev_clie *oclie) {
    char *parms[0x03] = {lev2n, INVO_LIST_ATTRIB, NULL};
    resp_data_t twol_valu;
    //
    if (obje_colle_list(&twol_valu, oclie, parms))
        return -1;
    if (OK != twol_valu.resp_code) {
        OSEVPrintErro("colle list error!", twol_valu.resp_code);
        outpu_excep_code(&twol_valu);
        return -1;
    }
    memcpy(lev2_cont, twol_valu.resp_data, twol_valu.resp_leng);
    lev2_cont[twol_valu.resp_leng] = '\0';
    //
    return twol_valu.resp_leng;
}

static int list_lev2_conte(char *lev2_cont, char *lev2n, osev_clie *oclie) {
    char *parms[0x03] = {lev2n, INVO_LIST_CONTEN, NULL};
    resp_data_t twol_valu;
    //
    if (obje_colle_list(&twol_valu, oclie, parms))
        return -1;
    if (OK != twol_valu.resp_code) {
        OSEVPrintErro("colle list error!", twol_valu.resp_code);
        outpu_excep_code(&twol_valu);
        return -1;
    }
    memcpy(lev2_cont, twol_valu.resp_data, twol_valu.resp_leng);
    lev2_cont[twol_valu.resp_leng] = '\0';
    //
    return twol_valu.resp_leng;
}

//

static int split_lev2_lev1(char *lev2_decla, char *lev1np[LEVO_COUNT], char *_mline_, char *lev2_cont) {
    // CLIEPF("lev2_cont:|%s|\n", lev2_cont);
    char *last_str = split_class_conte(lev2_decla, lev2_cont);
    if (!last_str) return -1;
    int declen = last_str - lev2_cont;
    // CLIEPF("lev2_decla:|%s|\n", lev2_decla);
    // CLIEPF("last_str:|%s|\n", last_str);
    split_method(lev1np, _mline_, last_str);
    return declen;
}

// utili:list(lev2n);
// utili:list(lev2n, LEVO);
// utili:list(lev2n, LEVT);
// 0x00:OK -1:error

int utili_list(char **parmp, shel_resu *resul, osev_clie *oclie) {
    uint64 colen = 0x00;
    ssize_t revlen;
    // parms = 1 = 2
    if (!parmp[0x00] || (parmp[0x01] && parmp[0x02]))
        return -1;
    quote_decode(parmp[0x00]);
    CLIEPF("parmp[0x00]:|%s| parmp[0x01]:|%s|\n", parmp[0x00], parmp[0x01]);
    //
    unsigned int util_type = util_list_type(parmp[0x01]);
    CLIEPF("util_type:%u\n", util_type);
    char leve_conte[LARGE_TEXT_SIZE];
    if (ULST_LEVT_ATTRIB & util_type) {
        if (-1 == (revlen = list_lev2_attri(leve_conte, parmp[0x00], oclie)))
            return -1;
        if (0x00 >= APPEND_DATAS(resul->resu_stre, leve_conte, revlen))
            return -1;
        colen += revlen;
        CLIEPF("ULST_LEVT_ATTRIB:|%s|\n", leve_conte);
    }
    //
    char *lev1np[LEVO_COUNT];
    char _mline_[LARGE_TEXT_SIZE];
    char **lev1n;
    char lev2_decla[LARGE_TEXT_SIZE];
    if (ULST_LEVT_CONTE & util_type) {
        if (-1 == list_lev2_conte(leve_conte, parmp[0x00], oclie))
            return -1;
        CLIEPF("ULST_LEVT_CONTE:|%s|\n", leve_conte);
        // char lev2_decla[LARGE_TEXT_SIZE];
        if (0x00 >= (revlen = split_lev2_lev1(lev2_decla, lev1np, _mline_, leve_conte)))
            return -1;
        if (0x00 >= APPEND_DATAS(resul->resu_stre, lev2_decla, revlen))
            return -1;
        colen += revlen;
        CLIEPF("lev2_decla:|%s|\n", lev2_decla);
        // GET_COLLE_OIDE
        osv_oid_t *coll_oid = find_colle_oid(parmp[0x00], oclie);
        char lev1_cont[LARGE_TEXT_SIZE];
        lev1n = lev1np;
        for (; lev1n[0x00]; ++lev1n) {
            CLIEPF("lev1n[0x00]:|%s|\n", lev1n[0x00]);
            if (-1 == (revlen = list_lev1_iden(lev1_cont, coll_oid, lev1n[0x00], oclie)))
                return -1;
            if (0x00 >= APPEND_DATAS(resul->resu_stre, lev1_cont, revlen))
                return -1;
            colen += revlen;
            CLIEPF("lev1_cont:|%s|\n", lev1_cont);
        }
    }
    //
    if (ULST_LEVO_CONTE & util_type) {
        if (-1 == list_lev2_conte(leve_conte, parmp[0x00], oclie))
            return -1;
        CLIEPF("ULST_LEVT_CONTE:|%s|\n", leve_conte);
        // char lev2_decla[LARGE_TEXT_SIZE];
        if (0x00 >= split_lev2_lev1(lev2_decla, lev1np, _mline_, leve_conte))
            return -1;
        // GET_COLLE_OIDE
        osv_oid_t *coll_oid = find_colle_oid(parmp[0x00], oclie);
        char lev1_cont[LARGE_TEXT_SIZE];
        lev1n = lev1np;
        for (; lev1n[0x00]; ++lev1n) {
            CLIEPF("lev1n[0x00]:|%s|\n", lev1n[0x00]);
            if (-1 == (revlen = list_lev1_iden(lev1_cont, coll_oid, lev1n[0x00], oclie)))
                return -1;
            if (0x00 >= APPEND_DATAS(resul->resu_stre, lev1_cont, revlen))
                return -1;
            colen += revlen;
            CLIEPF("lev1_cont:|%s|\n", lev1_cont);
        }
    }
    //
    resul->resu_leng = colen;
    resul->resu_type = 0x01;
    CLIEPF("utili_list, resul->resu_leng:%llu\n", resul->resu_leng);
    return 0x00;
}
