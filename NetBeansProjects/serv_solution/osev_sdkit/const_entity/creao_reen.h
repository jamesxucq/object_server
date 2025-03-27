
/* 
 * File:   creao_reen.h
 * Author: James Xu
 *
 * Created on 2022.10.26, PM 2:00
 */

#ifndef CREAO_REEN_H
#define CREAO_REEN_H

#include "creao.h"

#ifdef __cplusplus
extern "C" {
#endif

    // -1:error 0x00:ok 0x01:exception

#define CREAT_CONST_ENTIT_REEN(CREAT_VALU, RESCTL, CURSO, STORA_HA, LVTPME, HANDO, BASEN, PAMVS) { \
    if (!PAMVS[0x00]) { \
        CREAT_VALU = _blank_defau_entit_(RESCTL, CURSO, STORA_HA, LVTPME); \
    } else { \
        char handn[HANDN_LENGTH]; \
        if (!filli_const_handn(handn, LVTPME->lv2pn, PAMVS)) \
            return -1; \
        lev1me *lv1me = (lev1me *) action_value(handn, (HANDO)->lev1n_hm); \
        if (lv1me) CREAT_VALU = _user_creat_entit_(RESCTL, CURSO, STORA_HA, lv1me, PAMVS); \
        else CREAT_VALU = _full_defau_entit_(RESCTL, CURSO, STORA_HA, LVTPME, BASEN, PAMVS); \
    } \
}


#ifdef __cplusplus
}
#endif

#endif /* CREAO_REEN_H */

