#include <pthread.h>

#include "commo_header.h"

#include "kstri_utili.h"
#include "../clit_bzl.h"
#include "./parse_list/klist_ite.h"
#include "list.h"
#include "../debug_funct_sh.h"

// odb-lv2p> kits:list(lv2pn);
// odb-lv2p> kits:list(lv2pn, LEVO);
// odb-lv2p> kits:list(lv2pn, LEVO, FORCED);
// odb-lv2p> kits:list(lv2pn, LVTP);
// odb-lv2p> kits:list(lv2pn, LVTP, FORCED);
// odb-lv2p> kits:list(txxt, LVTP) | kits:format(XML);
// 0x00:OK -1:error

#define LIST_INTERN_FORCED    "FORCED"

//

int kits_list(char **pamvp, clit_resu *resul, osev_clie *oclie) {
    CLIT_PF("[FUNC]:kits_list.\n");
    uint64 colen = 0x00;
    ssize_t revlen;
    char leve_conte[LARGE_TEXT_SIZE];
    // pamvu = 1 = 2 = 3
    if (!pamvp[0x00] || (pamvp[0x01] && pamvp[0x02] && pamvp[0x03]))
        return -1;
    quote_decode(pamvp[0x00]);
    CLIT_PF("pamvp[0x00]:|%s| pamvp[0x01]:|%s|\n", pamvp[0x00], pamvp[0x01]);
    //
    unsigned int klst_type = build_klist_type((char *) pamvp[0x01]);
    if (!klst_type) return -1;
    CLIT_PF("klst_type:%u\n", klst_type);
    bool_osv lv2p_extern;
    bool_osv lv2p_integr;
    if (-1 == (revlen = requ_lv2p_extint(&lv2p_extern, &lv2p_integr, leve_conte, pamvp[0x00], oclie)))
        return -1;
    CLIT_PF("lv2p_extern:|%d| lv2p_integr:|%d|\n", lv2p_extern, lv2p_integr);
    if (!lv2p_integr) {
        ClitPrintInfo("This lv2p is not integral!");
        return -1;
    }
    if ((!lv2p_extern) && (!(pamvp[0x01] && pamvp[0x02]) || strcmp(LIST_INTERN_FORCED, pamvp[0x02]))) {
        ClitPrintInfo("This lv2p is internal, use FORCED!");
        return -1;
    }
    //
    rewind(resul->resu_stram);
    if (KLST_LVTP_ATTRIB & klst_type) {
        CLIT_PF("--- KLST_LVTP_ATTRIB\n");
        // if (-1 == (revlen = requ_lv2p_atti(leve_conte, pamvp[0x00], oclie)))
        // return -1;
        if (0x00 >= APPEND_DATAS(resul->resu_stram, leve_conte, revlen))
            return -1;
        colen += revlen;
        CLIT_PF("KLST_LVTP_ATTRIB:|%s|\n", leve_conte);
    }
    //
    if (KLST_LVTP_EXPAND & klst_type) {
        CLIT_PF("--- KLST_LVTP_EXPAND\n");
        if (-1 == (revlen = requ_lv2p_expand(leve_conte, pamvp[0x00], oclie)))
            return -1;
        if (0x00 >= APPEND_DATAS(resul->resu_stram, leve_conte, revlen))
            return -1;
        colen += revlen;
        CLIT_PF("KLST_LVTP_EXPAND:|%s|\n", leve_conte);
    }
    //
    if (KLST_LVTP_CONTE & klst_type) {
        CLIT_PF("--- KLST_LVTP_CONTE\n");
        if (-1 == (revlen = requ_lv2p_conte(leve_conte, pamvp[0x00], oclie)))
            return -1;
        if (0x00 >= APPEND_DATAS(resul->resu_stram, leve_conte, revlen))
            return -1;
        colen += revlen;
        CLIT_PF("KLST_LVTP_CONTE:|%s|\n", leve_conte);
    }
    //
    if (KLST_LEVO_CONTE & klst_type) {
        CLIT_PF("--- KLST_LEVO_CONTE\n");
        if (-1 == requ_lv2p_conte(leve_conte, pamvp[0x00], oclie))
            return -1;
        CLIT_PF("KLST_LVTP_CONTE:|%s|\n", leve_conte);
        char lv2p_decla[LARGE_TEXT_SIZE];
        char *lev1np[LEVO_COUNT];
        char _mline_[LARGE_CONTE_SIZE];
        if (0x00 >= (revlen = split_lv2p_lev1(lv2p_decla, lev1np, _mline_, leve_conte)))
            return -1;
        if (0x00 >= APPEND_DATAS(resul->resu_stram, lv2p_decla, revlen))
            return -1;
        colen += revlen;
        CLIT_PF("lv2p_decla:|%s|\n", lv2p_decla);
        // GET_COLLE_OBIDE
        osv_oid_t *coll_obid = find_colle_obid(pamvp[0x00], oclie);
        char lev1_cont[LARGE_TEXT_SIZE];
        char **lev1n = lev1np;
        for (; lev1n[0x00]; ++lev1n) {
            CLIT_PF("lev1n[0x00]:|%s|\n", lev1n[0x00]);
            if (-1 == (revlen = requ_lev1_iden(lev1_cont, coll_obid, lev1n[0x00], oclie)))
                return -1;
            if (0x00 >= APPEND_DATAS(resul->resu_stram, lev1_cont, revlen))
                return -1;
            colen += revlen;
            CLIT_PF("lev1_cont:|%s|\n", lev1_cont);
        }
    }
    //
    resul->resu_leng = colen;
    resul->resu_type = 0x01;
    CLIT_PF("kits_list, resul->resu_leng:%llu\n", resul->resu_leng);
    return 0x00;
}
