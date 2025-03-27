
#include "commo_header.h"
#include "kcomm_header.h"
#include "robk_lev1_bzl.h"
#include "debug_funct_ci.h"

//

void p_lv2p_clang(char *clang_cont) {
    printf("----- lv2p clang_cont -----|\n");
    printf("|%s|\n", clang_cont);
    printf("|----------------------\n");
}

//

void p_lev1_clang(char *clang_cont) {
    printf("----- lev1 clang_cont -----|\n");
    printf("|%s|\n", clang_cont);
    printf("|----------------------\n");
}

/*
void p_reloc_envir(reloc_envir *env_rlc) {
    printf("----- p_reloc_envir\n");
    printf("lv2pn:|%s|\n", env_rlc->lv2pn);
    printf("bakup_libra:|%d|\n", env_rlc->bakup_libra);
    printf("lev1_librn:|%s|\n", env_rlc->lev1_librn);
}

void p_replc_envir(replc_envir *envrpc) {

}
 */

void p_lev1_meta(lev1_meta *lev1m) {
    printf("----- lev1_meta -----\n");
    printf("layout:%08X\n", lev1m->layout);
    if (HAVE_CLASN & lev1m->layout) printf("lv2pn:|%s|\n", lev1m->lv2pn);
    if (HAVE_METHN & lev1m->layout) printf("lev1n:|%s|\n", lev1m->lev1n);
    if (HAVE_DECLA & lev1m->layout) {
        printf("decla:|%s|\n", lev1m->decla);
        printf("--- oivk_retyp_om:%d\n", lev1m->oivk_retyp_om);
        printf("--- oivk_fmtsp_om:|%s|\n", lev1m->oivk_fmtsp_om);
        printf("--- oivk_size_om:%d\n", lev1m->oivk_size_om);
    }
    if (HAVE_BODY & lev1m->layout) printf("body:|%s|\n", lev1m->body);
    printf("---------------------\n");
}

void p_replm_envir(replm_envir *envrpm) {
    printf("----- p_replm_envir\n");
    printf("lv2pn:|%s|\n", envrpm->lv2pn);
    printf("handn:|%s|\n", envrpm->handn);
    printf("bakup_libra:|%d|\n", envrpm->bakup_libra);
    printf("lev1_librn:|%s|\n", envrpm->lev1_librn);
}

void p_relom_envir(relom_envir *envrlm) {
    printf("----- p_relom_envir\n");
    printf("lv2pn:|%s|\n", envrlm->lv2pn);
    printf("handn:|%s|\n", envrlm->handn);
    printf("bakup_libra:|%d|\n", envrlm->bakup_libra);
    printf("lev1_librn:|%s|\n", envrlm->lev1_librn);
}

