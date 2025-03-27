
/* 
 * File:   debug_funct_ci.h
 * Author: James Xu
 *
 * Created on 2022.11.16, AM 9:45
 */

#ifndef DEBUG_FUNCT_CI_H
#define DEBUG_FUNCT_CI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    void p_lv2p_clang(char *clang_cont);
    void p_lev1_clang(char *clang_cont);
    // void p_reloc_envir(reloc_envir *env_rlc);
    // void p_replc_envir(replc_envir *envrpc);
    void p_lev1_meta(lev1_meta *lev1m);
    void p_replm_envir(replm_envir *envrpm);
    void p_relom_envir(relom_envir *envrlm);

#ifdef _DEBUG
#define PRIN_lv2p_clang p_lv2p_clang
#define PRIN_lev1_clang p_lev1_clang
    // #define PRIN_reloc_envir p_reloc_envir
    // #define PRIN_replc_envir p_replc_envir
#define PRIN_lev1_meta p_lev1_meta
#define PRIN_replm_envir p_replm_envir
#define PRIN_relom_envir p_relom_envir
#else
#define PRIN_lv2p_clang(...)
#define PRIN_lev1_clang(...)
    // #define PRIN_reloc_envir(...)
    // #define PRIN_replc_envir(...)
#define PRIN_lev1_meta(...)
#define PRIN_replm_envir(...)
#define PRIN_relom_envir(...)
#endif

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_FUNCT_CI_H */

