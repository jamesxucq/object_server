#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse_lev1.h"

#include "../../debug_funct_sh.h"

//

static char *metho_decla(char *l1nsps, char *lv2p_cont) {
    char *tokep, *toksp;
    //
    toksp = strchr(lv2p_cont, '<');
    if (!toksp) return NULL;
    tokep = strchr(toksp + 0x01, '>');
    if (!tokep) return NULL;
    strzcpy(l1nsps, lv2p_cont, toksp - lv2p_cont);
    //
    tokep = strchr(tokep + 0x01, ';');
    if (!tokep) return NULL;
    return ++tokep;
}

static int check_l1nsps(char *lev1np[LEVO_COUNT], int posi, char *l1nsps) {
    unsigned int inde = 0x00;
    for (; posi > inde; ++inde) {
        if (!strcmp(l1nsps, lev1np[inde]))
            return 0x01;
    }
    //
    return 0x00;
}

int split_method(char *lev1np[LEVO_COUNT], char *_mline_, char *lv2p_cont) {
    char *tokep, *toksp;
    char l1nsps[LVON_LENGTH];
    CLIEPF("[FUNC]:split_method\n");
    CLIEPF("lv1pm lv2p_cont:|%s|\n", lv2p_cont);
    unsigned int inde = 0x00;
    if (!(toksp = kill_inval(lv2p_cont))) {
        lev1np[0x00] = NULL;
        return 0x00;
    }
    tokep = metho_decla(l1nsps, toksp);
    while (tokep) {
        if (!check_l1nsps(lev1np, inde, l1nsps)) {
            LSCPY_O(lev1np[inde], l1nsps, _mline_);
            CLIEPF("lev1n[%d]:|%s|\n", inde, lev1np[inde]);
            ++inde;
        }
        if (!(toksp = kill_inval(tokep)))
            break;
        tokep = metho_decla(l1nsps, toksp);
    }
    lev1np[inde] = NULL;
    CLIEPF("lev1n[%d]:|NULL|\n", inde);
    return 0x00;
}