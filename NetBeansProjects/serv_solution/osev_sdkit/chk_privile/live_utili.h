
/* 
 * File:   live_utili.h
 * Author: James Xu
 *
 * Created on 2018.3.22, PM 3:23
 */

#ifndef LIVE_UTILI_H
#define LIVE_UTILI_H

#include "kcomm_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _priv_cont_ {
        char *cont_name; // contain name
        char *lv2pn_type;
    };

    typedef struct _priv_cont_ priv_cont;

    //
#define DEFA_ROLE_LVTP  "role"
#define DEFA_USER_LVTP  "user"
    //
#define AUTH_ROLES_CONT  "roles_con"
#define AUTH_OUSER_CONT  "osev_user_con" // osev user
#define AUTH_BUSER_CONT  "base_user_con" // developer 

    //

    extern priv_cont _priv_data_[];
    int chk_privi_data(cont_lsmp *conda_stm, lv2pm_hmap *lv2pm_stm, priv_cont *priv_data);
#ifdef _DEBUG
    int user_recu_prin(base_valu *admbv, char *contn);
#endif
    int live_recu_load(liv_list **llsth, base_valu *admbv, char *contn);
    int live_insert(base_valu *admbv, char *contn, void *inse_data);
    int live_load(valu_memo_t *load_data, base_valu *admbv, char *contn, osv_oid_t *roue_obid);
    int loop_load(loop_memo_t *load_data, base_valu *admbv, char *contn, osv_oid_t *roue_obid);
    int loop_save(base_valu *admbv, char *contn, loop_memo_t *save_data, osv_oid_t *roue_obid);
    int live_remove(base_valu *admbv, char *contn, osv_oid_t *roue_obid);



#ifdef __cplusplus
}
#endif

#endif /* LIVE_UTILI_H */

