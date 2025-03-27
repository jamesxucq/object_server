
/* 
 * File:   debug_funct_cp.h
 * Author: James Xu
 *
 * Created on 2022.11.18, AM 9:09
 */

#ifndef DEBUG_FUNCT_CP_H
#define DEBUG_FUNCT_CP_H

#include "kcomm_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    char *p_role_privi(char *last_str, role_privi *ropriv);
    void p_role_privi_list(liv_list *role_list);
    void p_user_privi_list(liv_list *user_list);
    void p_user_all(liv_list *ouse_list);
    void p_dist_privi(dist_privi *priv_poin);
    char *echo_role_privi(char *last_str, role_privi *ropriv);
    char *echo_dist_privi(char *last_str, dist_privi *priv_poin);

#ifdef _DEBUG
#define PRIN_role_privi p_role_privi
#define PRIN_role_privi_list p_role_privi_list
#define PRIN_user_privi_list p_user_privi_list
#define PRIN_user_all p_user_all
#define PRIN_dist_privi p_dist_privi
#define PRIN_echo_role_privi echo_role_privi
#define PRIN_echo_dist_privi echo_dist_privi
#else
#define PRIN_role_privi(...)
#define PRIN_role_privi_list(...)
#define PRIN_user_privi_list(...)
#define PRIN_user_all(...)
#define PRIN_dist_privi(...)
#define PRIN_echo_role_privi(...)
#define PRIN_echo_dist_privi(...)
#endif

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_FUNCT_CP_H */

