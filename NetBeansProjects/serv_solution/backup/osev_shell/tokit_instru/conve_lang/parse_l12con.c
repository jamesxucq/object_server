#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../kstri_utili.h"
#include "commo_header.h"
#include "cstri_utili.h"
#include "parse_lv2p_atti.h"
#include "lv2p_list.h"

#include "parse_l12con.h"
#include "../../debug_funct_sh.h"

//

static int parse_metho_decla(method **mlsth, char *lv2p_cont) {
    // CLIEPF("[FUNC]:parse_metho_decla\n");
    char *tokep, *toksp;
    method *menod;
    char l1nsps[LVON_LENGTH];
    // CLIEPF("lv2p_cont:|%s|\n", lv2p_cont);
    char *lev1n;
    if (!(toksp = kill_inval(lv2p_cont)))
        return 0x00;
    while (toksp) {
        tokep = find_metho_decla(l1nsps, toksp);
        // CLIEPF("l1nsps:|%s|\n", l1nsps);
        if ((lev1n = l1nsps_delim(l1nsps))) {
            // CLIEPF("lev1n:|%s|\n", lev1n);
            menod = appe_mlist_new(mlsth);
            if (!menod) return -1;
            strcpy(menod->lev1n, lev1n);
            // CLIEPF("toksp:|%s| tokep:|%s|\n", toksp, tokep);
            strzcpy(menod->lev1_cont, toksp, tokep - toksp);
            // CLIEPF("lev1_cont:|%s|\n", menod->lev1_cont);
        }
        toksp = kill_inval(tokep);
    }
    // CLIEPF("end, parse_metho_decla\n");
    return 0x00;
}

static int parse_metho_conte(method **mlsth, char *lv2p_cont) {
    char *tokep, *toksp;
    method *menod;
    char l1nsps[LVON_LENGTH];
    // CLIEPF("pm lv2p_cont:|%s|\n", lv2p_cont);
    char *lev1n;
    if (!(toksp = kill_inval(lv2p_cont)))
        return 0x00;
    while (toksp) {
        tokep = find_metho_defin(l1nsps, toksp);
        if ((lev1n = l1nsps_delim(l1nsps))) {
            menod = appe_mlist_new(mlsth);
            if (!menod) return -1;
            strcpy(menod->lev1n, lev1n);
            strzcpy(menod->lev1_cont, toksp, tokep - toksp);
            // CLIEPF("meth_name:|%s| lev1_cont:|%s|\n", menod->meth_name, menod->lev1_cont);
        }
        toksp = kill_inval(tokep);
    }
    //
    return 0x00;
}

//

class_meta *parse_lv2p_cont(class_meta *clsmt, char *lv2p_cont) {
    // CLIEPF("[FUNC]:parse_lv2p_cont\n");
    char acont[LARGE_TEXT_SIZE];
    //
    lv2p_cont = split_lv2p_atti(acont, lv2p_cont);
    if (!lv2p_cont) return NULL;
    if (!parse_lv2p_atti(clsmt, acont))
        return NULL;
    //
    lv2p_cont = split_class_conte(clsmt->lv2p_decl, lv2p_cont);
    if (!lv2p_cont) return NULL;
    if (parse_metho_decla(&clsmt->meth_list, lv2p_cont)) {
        mlist_dele(clsmt->meth_list);
        return NULL;
    }
    //
    return clsmt;
}

class_meta *parse_lev1_cont(class_meta *clsmt, char *lev1_cont) {
    char acont[LARGE_TEXT_SIZE];
    //
    lev1_cont = split_lv2p_atti(acont, lev1_cont);
    if (!lev1_cont) return NULL;
    if (!parse_lv2p_atti(clsmt, acont))
        return NULL;
    //
    lev1_cont = split_class_conte(clsmt->lv2p_decl, lev1_cont);
    if (!lev1_cont) return NULL;
    if (parse_metho_conte(&clsmt->meth_list, lev1_cont)) {
        mlist_dele(clsmt->meth_list);
        return NULL;
    }
    //
    return clsmt;
}

