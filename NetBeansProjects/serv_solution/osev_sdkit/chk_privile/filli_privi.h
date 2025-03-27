
/* 
 * File:   filli_privi.h
 * Author: James Xu
 *
 * Created on 2018.3.19, PM 2:18
 */

#ifndef FILLI_PRIVI_H
#define FILLI_PRIVI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 
    void oprin_role_name(respo_ctrl *resctl, role_privi *ropriv);
    void bprin_role_name(respo_ctrl *resctl, role_privi *ropriv, role_privi *sto_ropri);
    void oprin_role_all(respo_ctrl *resctl, liv_list *role_list);
    void bprin_role_all(respo_ctrl *resctl, liv_list *role_list);

    //
    void filli_user_name(respo_ctrl *resctl, user_privi *uepriv);
    void filli_user_all(respo_ctrl *resctl, liv_list *ouse_list);


#ifdef __cplusplus
}
#endif

#endif /* FILLI_PRIVI_H */

