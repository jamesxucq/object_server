
/* 
 * File:   searo_reen.h
 * Author: James Xu
 *
 * Created on 2022.10.26, PM 2:02
 */

#ifndef SEARO_REEN_H
#define SEARO_REEN_H

#include "rive_bzl.h"
#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int searo_const_predi_reen(respo_ctrl *resctl, contain *contp, base_valu *baval, char *pamvu);
    int searo_const_objid_reen(respo_ctrl *resctl, contain *contp, base_valu *baval, osv_oid_i *searo_obid);
    int searo_const_trave_reen(respo_ctrl *resctl, contain *contp, base_valu *baval);

#ifdef __cplusplus
}
#endif

#endif /* SEARO_REEN_H */

