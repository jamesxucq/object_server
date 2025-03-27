
/* 
 * File:   instda_bzl.h
 * Author: James Xu
 *
 * Created on 2024.3.31, PM 3:08
 */

#ifndef INSTDA_BZL_H
#define INSTDA_BZL_H

#include "insta_utili.h"
#include "lv2in_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    lv2pme *lv2me_interp_bzl(base_valu *baval, char *lv2_dec);

    //
    lv2p_expa_t *lv2expt_interp_bzl(base_valu *baval, char *lv2_dec);


#ifdef __cplusplus
}
#endif

#endif /* INSTDA_BZL_H */

