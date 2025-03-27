
/* 
 * File:   const_bzl.h
 * Author: James Xu
 *
 * Created on 2016.12.17, PM 2:53
 */

#ifndef CONST_BZL_H
#define CONST_BZL_H

#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

    //int invobzl_create(char *data_directory);
    //int invobzl_destroy();
    
    //
    int enti_statu_echo_bzl(respo_ctrl *resctl, contain *contp);
    int enti_statu_attri_bzl(respo_ctrl *resctl, contain *contp, base_valu *baval);
    int enti_statu_stati_bzl(respo_ctrl *resctl, contain *contp, base_valu *baval);
    
    //
    int enti_creat_bzl(respo_ctrl *resctl, contain *contp, base_valu *baval, char **pamvp);
    int enti_drop_bzl(contain *contp, base_valu *baval, pams_valu *pamvu);
    int enti_updat_bzl(contain *contp, base_valu *baval, pams_valu *pamvu);
    int enti_inser_bzl(respo_ctrl *resctl, contain *contp, base_valu *baval, pams_valu *pamvu);
    // obje:search();
    int enti_searo_bzl(respo_ctrl *resctl, contain *contp, base_valu *baval, pams_valu *pamvu);
    //
    int enti_invok_bzl(respo_ctrl *resctl, contain *contp, base_valu *baval, pams_valu *pamvu);

    //


#ifdef __cplusplus
}
#endif

#endif /* CONST_BZL_H */

