
/* 
 * File:   dropo_reen.h
 * Author: James Xu
 *
 * Created on 2022.10.26, PM 2:01
 */

#ifndef DROPO_REEN_H
#define DROPO_REEN_H

#include "dropo.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#define DROP_CONST_OBJID_REEN(RVCON, CONTP, DROP_OBID) _objid_const_drop_(RVCON, CONTP, DROP_OBID)
#define DROP_CONST_PREDI_REEN(CONTP, BAVAL, PARAM)  drop_const_predi(CONTP, BAVAL, PARAM)
#define DROP_CONST_TRAVE_REEN(CONTP, BAVAL)  drop_const_trave(CONTP, BAVAL)

#ifdef __cplusplus
}
#endif

#endif /* DROPO_REEN_H */

