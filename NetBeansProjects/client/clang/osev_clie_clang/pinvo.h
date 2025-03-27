
/* 
 * File:   pinvo.h
 * Author: James Xu
 *
 * Created on 2017.6.15, PM2:21
 */

#ifndef PINVO_H
#define PINVO_H

#include "clie_struct.h"
// #include "dstri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // trans-serve
    unsigned long long parse_invok_metho(pamstyl_t *pscon, char *pamcon);

    // trans-serve
    unsigned long long parse_qinup_entit(pamstyl_t *pscon, char *pamcon, char *fmtst);


#ifdef __cplusplus
}
#endif

#endif /* PINVO_H */

