
/* 
 * File:   dropo.h
 * Author: James Xu
 *
 * Created on 2017.4.11, AM10:01
 */

#ifndef DROPO_H
#define DROPO_H

#include "rive_bzl.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    // -1:error 0x00:ok 0x01:exception
    int drop_const_predi(contain *contp, base_valu *baval, char *pamvu);

    //
    int _objid_const_drop_(rive_conne *rivcon, contain *contp, osv_oid_i *drop_obid);
#define DROP_CONST_OBJID(RVCON, CONTP, DROP_OBID) _objid_const_drop_(RVCON, CONTP, DROP_OBID)
    int drop_const_trave(contain *contp, base_valu *baval);

#ifdef __cplusplus
}
#endif

#endif /* DROPO_H */

