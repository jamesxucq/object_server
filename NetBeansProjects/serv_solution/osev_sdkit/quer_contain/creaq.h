
/* 
 * File:   creaq.h
 * Author: James Xu
 *
 * Created on 2017.4.11, AM10:14
 */

#ifndef CREAQ_H
#define CREAQ_H

#include "rive_bzl.h"
#include "contain.h"
#include "creaq_utili/creaq_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // -1:error 0x00:ok 0x01:exception
    int creat_qcont_normal(base_valu *baval, char **pamvp);

#ifdef __cplusplus
}
#endif

#endif /* CREAQ_H */

