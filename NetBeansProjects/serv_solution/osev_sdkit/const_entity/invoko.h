
/* 
 * File:   invoko.h
 * Author: James Xu
 *
 * Created on 2017.4.11, AM10:01
 */

#ifndef INVOKO_H
#define INVOKO_H

#include "rive_bzl.h"
#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int invok_const_predi(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, char **pamvp);
    int invok_const_objid(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, char **pamvp);
    int invok_const_trave(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, char **pamvp);


#ifdef __cplusplus
}
#endif

#endif /* INVOKO_H */

