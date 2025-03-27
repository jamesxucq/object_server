
/* 
 * File:   searq.h
 * Author: James Xu
 *
 * Created on 2017.4.11, AM10:14
 */

#ifndef SEARQ_H
#define SEARQ_H

#include "query_bzl.h"
#include "rive_bzl.h"
#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int searq_qcont_conta(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu, contain *dcont, int scoun, contain **sconp);

    //
    int searq_qcont_lv2pn(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu, int scoun, contain **sconp);
    int searq_qcont_decla(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu, lv2pme *lv2dme, int scoun, contain **sconp);

#ifdef __cplusplus
}
#endif

#endif /* SEARQ_H */

