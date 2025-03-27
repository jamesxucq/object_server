
/* 
 * File:   searq_reen.h
 * Author: James Xu
 *
 * Created on 2022.10.21, AM 8:59
 */

#ifndef SEARQ_REEN_H
#define SEARQ_REEN_H

#include "query_bzl.h"
#include "rive_bzl.h"
#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int searq_qcont_lv2pn_ore(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu, int scoun, contain **rconp);

    //
    int searq_qcont_lv2pn_reen(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu, contain *scont);
    int searq_qcont_decla_reen(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu, lv2pme *lv2dme, contain *scont);


#ifdef __cplusplus
}
#endif

#endif /* SEARQ_REEN_H */

