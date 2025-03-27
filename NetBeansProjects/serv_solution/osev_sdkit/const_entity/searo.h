
/* 
 * File:   searo.h
 * Author: James Xu
 *
 * Created on 2017.4.11, AM10:01
 */

#ifndef SEARO_H
#define SEARO_H

#include "rive_bzl.h"
#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int searo_const_predi_ensi(respo_ctrl *resctl, contain *contp, base_valu *baval, char *pamvu);
    int searo_const_objid_ensi(respo_ctrl *resctl, contain *contp, base_valu *baval, osv_oid_i *searo_obid);
    int searo_const_trave_ensi(respo_ctrl *resctl, contain *contp, base_valu *baval);


#ifdef __cplusplus
}
#endif

#endif /* SEARO_H */

