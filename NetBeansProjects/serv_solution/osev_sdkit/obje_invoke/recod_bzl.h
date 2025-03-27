
/* 
 * File:   recod_bzl.h
 * Author: James Xu
 *
 * Created on 2021112, AM9:42
 */

#ifndef RECOD_BZL_H
#define RECOD_BZL_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int recod_creac_bzl(char *basen, lv2p_decl_t *lv2dt, char *lv2_dec, lv2p_expa_t *lv2expt);
    int recod_replc_bzl(char *basen, lv2pm_hmap *lv2pm_stm, char *lv2pn, char *lv2_dec, lv2p_expa_t *lv2expt);

    //
    int recod_cream_bzl(char *basen, lev1_meta *lev1m, char *lev1_cont);
    int recod_replm_bzl(lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m, char *lev1_cont);


#ifdef __cplusplus
}
#endif

#endif /* RECOD_BZL_H */

