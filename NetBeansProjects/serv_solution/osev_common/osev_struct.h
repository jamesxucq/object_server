
/* 
 * File:   osev_struct.h
 * Author: James Xu
 *
 * Created on 2017.6.22, PM 9:47
 */

#ifndef OSEV_STRUCT_H
#define OSEV_STRUCT_H

#include <stdio.h>
#include <stddef.h>

// #include "commo_macro.h"
#include "third_party.h"
#include "osev_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    // generate // abstract
    // produce // data
    // build // binary
    // create // abstract
    // make // do
    // manufacture 
    // fill in // text
    // echo // output text

    // parse // binary
    // split // text
    // build // binary done

    //

    struct _pams_valu_ {
        unsigned long long req_len[PARAM_COUNT];
        FILE *pamstem;
        unsigned char pamtyp[PARAM_COUNT];
        char *pamcon[PARAM_COUNT];
    };

    typedef struct _pams_valu_ pams_valu;

#ifdef __cplusplus
}
#endif

#endif /* OSEV_STRUCT_H */

