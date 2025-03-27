
/* 
 * File:   invokq.h
 * Author: James Xu
 *
 * Created on 2017.5.9, PM 4:13
 */

#ifndef INVOKQ_H
#define INVOKQ_H

#include "rive_bzl.h"
#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int invok_qcont_predi(respo_ctrl *resctl, contain *contp, lv2pme *lv2me, hand_hmap *hando_stm, rive_conne *rivcon, char **pamvp);
    int invok_qcont_objid(respo_ctrl *resctl, contain *contp, lv2pme *lv2me, hand_hmap *hando_stm, rive_conne *rivcon, char **pamvp);
    int invok_qcont_trave(respo_ctrl *resctl, contain *contp, lv2pme *lv2me, hand_hmap *hando_stm, rive_conne *rivcon, char **pamvp);


#ifdef __cplusplus
}
#endif

#endif /* INVOKQ_H */

