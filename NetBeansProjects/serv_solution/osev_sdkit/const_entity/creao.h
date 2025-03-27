
/* 
 * File:   creao.h
 * Author: James Xu
 *
 * Created on 2017.3.20, PM3:24
 */

#ifndef CREAO_H
#define CREAO_H

#include "commo_header.h"
#include "estri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // -1:error 0x00:ok 0x01:exception
    int _blank_defau_entit_(respo_ctrl *resctl, riv_curso_t *dcurso, rive_ha *stora_ha, lv2pme *lv2me);
    int _full_defau_entit_(respo_ctrl *resctl, riv_curso_t *dcurso, rive_ha *stora_ha, lv2pme *lv2me, char *basen, char **pamvp);
    int _user_creat_entit_(respo_ctrl *resctl, riv_curso_t *dcurso, rive_ha *stora_ha, lev1me *lv1me, char **pamvp);

    // -1:error 0x00:ok 0x01:exception

#define CREAT_CONST_ENTIT(CREAT_VALU, RESCTL, CURSO, STORA_HA, LVTPME, HANDO, BASEN, PAMVS) { \
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

    //
    int creat_eobje_echo(hand_hmap *hando_stm, char *lv2pn, char **pamvp);


#ifdef __cplusplus
}
#endif

#endif /* CREAO_H */

