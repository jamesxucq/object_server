#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "load_conte.h"
#include "lev1_utili.h"
#include "lv2p_list.h"
#include "parse_l12con.h"
#include "conver.h"
#include "cstri_utili.h"
#include "filli_inline.h"
#include "filli_clang.h"
#include "parse_lv2p_atti.h"
#include "lv2p_expan.h"

#include "conv_gcc_cpp.h"
#include "../../debug_funct_sh.h"

//

static int conv_lev1_cont(clie_resu *resul, char *lev1_cont, char *lv2e_cont, osev_clie *oclie) {
    CLIEPF("[FUNC]:conv_lev1_cont\n");
    CLIEPF("lev1_cont:|%s|\n", lev1_cont);
    char clang_cont[CLANG_CONTE_SIZE];
    MK_ZERO(clang_cont);
    class_meta clsmt;
    memset(&clsmt, '\0', sizeof (class_meta));
    if (!parse_lev1_cont(&clsmt, lev1_cont))
        RETU_DELM(clsmt, -1)
        //
        lv2p_expa_t * lv2expt = parse_lv2expt_bzl(lv2e_cont);
    if (!lv2expt) {
        RETU_DELM(clsmt, -1);
        return -1;
    }
    //
    if (conve_lev1_conte(clang_cont, &clsmt, lv2expt, oclie->clie_name)) {
        free_lv2exp(lv2expt);
        RETU_DELM(clsmt, -1)
    }
    filli_lev1_conte(resul, clang_cont, clsmt.lv2pn, oclie->clie_name);
    //
    CLIEPF("End, conv_lev1_cont\n");
    free_lv2exp(lv2expt);
    CLAM_STRU_DELE(clsmt);
    return 0x00;
}

static int conv_lv2p_cont(clie_resu *resul, char *lv2p_cont, char *lv2e_cont, osev_clie *oclie) {
    CLIEPF("[FUNC]:conv_lv2p_cont\n");
    CLIEPF("lv2p_cont:|%s|\n", lv2p_cont);
    // CLIEPF("lv2e_cont:|%s|\n", lv2e_cont);
    char clang_cont[CLANG_CONTE_SIZE];
    MK_ZERO(clang_cont);
    class_meta clsmt;
    memset(&clsmt, '\0', sizeof (class_meta));
    if (!parse_lv2p_cont(&clsmt, lv2p_cont))
        RETU_DELM(clsmt, -1);
    //
    lv2p_expa_t *lv2expt = parse_lv2expt_bzl(lv2e_cont);
    if (!lv2expt) {
        RETU_DELM(clsmt, -1);
        return -1;
    }
    // CLIEPF("a1\n");
    if (!conve_lv2p_conte(clang_cont, &clsmt, lv2expt)) {
        free_lv2exp(lv2expt);
        RETU_DELM(clsmt, -1);
    }
    // CLIEPF("a2\n");
    filli_lv2p_conte(resul, clang_cont, clsmt.lv2pn, oclie->clie_name);
    //
    free_lv2exp(lv2expt);
    CLAM_STRU_DELE(clsmt);
    return 0x00;
}

// lv2p
// level-2+> kits:list(lv2pn) | kits:convert(GCC);
// level-2+> kits:list(lv2pn, LEVO) | kits:convert(GCC);
// level-2+> kits:list(lv2pn, LVTP) | kits:convert(GCC);
// level-2+> kits:list(lv2pn) | kits:convert(GCC);

// 0x00:OK -1:error

int conve_gcc_cpp(char **pamvp, clie_resu *resul, osev_clie *oclie) {
    CLIEPF("[FUNC]:conve_gcc_cpp\n");
    CLIEPF("resul->resu_type:%d comp_type:|%s| basen:|%s|\n", resul->resu_type, pamvp[0x00], oclie->clie_name);
    char conte_data[OSLAN_CONTE_SIZE];
    if (!load_conte_plain(conte_data, OSLAN_CONTE_SIZE - 0x01, resul))
        return -1;
    CLIEPF("conte_data:|%s|\n", conte_data);
    char lv2e_cont[OSLAN_CONTE_SIZE], lev1_cont[OSLAN_CONTE_SIZE], lv2p_cont[OSLAN_CONTE_SIZE];
    MK_ZERO(lv2e_cont);
    MK_ZERO(lev1_cont);
    MK_ZERO(lv2p_cont);
    unsigned int conte_type = split_conte_type(lv2e_cont, lv2p_cont, lev1_cont, conte_data);
    CLIEPF("conte_type:%08X\n", conte_type);
    if (!conte_type) return -1;
    // CLIEPF("2\n");
    if (KLST_LEVO_CONTE & conte_type) {
        if (conv_lev1_cont(resul, lev1_cont, lv2e_cont, oclie))
            return -1;
    }
    if (KLST_LVTP_CONTE & conte_type) {
        if (conv_lv2p_cont(resul, lv2p_cont, lv2e_cont, oclie))
            return -1;
    }
    //
    return 0x00;
}
