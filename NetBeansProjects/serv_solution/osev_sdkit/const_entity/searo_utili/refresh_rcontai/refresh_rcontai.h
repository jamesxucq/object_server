
/* 
 * File:   refresh_rcontai.h
 * Author: James Xu
 *
 * Created on 2024.6.5, PM 2:37
 */

#ifndef REFRESH_RCONTAI_H
#define REFRESH_RCONTAI_H

#include "rive_bzl.h"
#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int chk_rcont_versi(int rcoun, cont_versi *rcove, cont_lsmp *conda_stm);
    int updat_rcont_versi(int rcoun, cont_versi *rcove, cont_lsmp *conda_stm);

    //
    int rcontai_predica_refresh_rdsi(contain *contp, base_valu *baval, lv2pme *lv2me);
    int rcontai_objid_refresh_rdsi(contain *contp, base_valu *baval);
    int rcontai_traver_refresh_rdsi(contain *contp, base_valu *baval);

    //
    int rcontai_predica_refresh_rdco(contain *contp, base_valu *baval, lv2pme *lv2me);
    int rcontai_objid_refresh_rdco(contain *contp, base_valu *baval);
    int rcontai_traver_refresh_rdco(contain *contp, base_valu *baval);

#ifdef __cplusplus
}
#endif

#endif /* REFRESH_RCONTAI_H */

