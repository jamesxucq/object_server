
/* 
 * File:   debug_funct_sh.h
 * Author: James Xu
 *
 * Created on 2022.11.16, AM 9:59
 */

#ifndef DEBUG_FUNCT_SH_H
#define DEBUG_FUNCT_SH_H

#include "cinstru.h"
#include "osvp_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#ifdef _DEBUG
#define CLIT_PF printf
#else 
#define CLIT_PF(fmt, ...)
#endif
    
    //
    void p_clit_instru(clit_inst *cinst);
    void p_instru(clit_inst *cinst);
    void p_clit_auth(osvp_auth *clie_auth, const char *osvp_uri);
    void p_sh_lv2p_expa_t(lv2p_expa_t *lv2expt);
    
#ifdef _DEBUG
#define PRIN_clit_instru p_clit_instru
#define PRIN_instru p_instru
#define PRIN_clit_auth p_clit_auth
#define PRIN_sh_lv2p_expa_t p_sh_lv2p_expa_t
#else
#define PRIN_clit_instru(...)
#define PRIN_instru(...)
#define PRIN_clit_auth(...)
#define PRIN_sh_lv2p_expa_t(...)
#endif
    
#ifdef __cplusplus
}
#endif

#endif /* DEBUG_FUNCT_SH_H */

