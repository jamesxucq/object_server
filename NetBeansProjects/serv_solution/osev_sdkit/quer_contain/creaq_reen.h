
/* 
 * File:   creaq_reen.h
 * Author: James Xu
 *
 * Created on 2022.10.26, PM 1:53
 */

#ifndef CREAQ_REEN_H
#define CREAQ_REEN_H

#include "rive_bzl.h"
#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

    // -1:error 0x00:ok 0x01:exception
    int creat_qcont_static_reen(base_valu *baval, char **pamvp);

    // -1:error 0x00:ok 0x01:exception
    int creat_qcont_dynamic_reen(base_valu *baval, char **pamvp, unsigned char creat_conditype);
    
#ifdef __cplusplus
}
#endif

#endif /* CREAQ_REEN_H */

