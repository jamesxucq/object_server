
/* 
 * File:   debug_funct_sh.h
 * Author: james
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
#define CLIEPF printf
#else 
#define CLIEPF(fmt, ...)
#endif
    
    //
    void p_cli_instru(cli_inst *cinst);
    void p_instru(cli_inst *cinst);
    void p_clie_auth(osvp_auth *clie_auth, const char *osvp_uri);
    void p_sh_lv2p_expa_t(lv2p_expa_t *lv2expt);
    
#ifdef _DEBUG
#define PRIN_cli_instru p_cli_instru
#define PRIN_instru p_instru
#define PRIN_clie_auth p_clie_auth
#define PRIN_sh_lv2p_expa_t p_sh_lv2p_expa_t
#else
#define PRIN_cli_instru(...)
#define PRIN_instru(...)
#define PRIN_clie_auth(...)
#define PRIN_sh_lv2p_expa_t(...)
#endif
    
#ifdef __cplusplus
}
#endif

#endif /* DEBUG_FUNCT_SH_H */

