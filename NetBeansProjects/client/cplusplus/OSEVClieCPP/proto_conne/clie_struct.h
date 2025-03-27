
/* 
 * File:   clie_struct.h
 * Author: James Xu
 *
 * Created on 2017.6.22, PM 2:09
 */

#ifndef CLIE_STRUCT_H
#define CLIE_STRUCT_H

//
#include "osev_common/osev_macro.h"
#include "clie_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _pamstyl_t_ {
        char pamstyl_memo[BINA_ARRAY_LEN];
        unsigned long long colen;
    };

    typedef struct _pamstyl_t_ pamstyl_t;


    //

#ifdef __cplusplus
}
#endif

#endif /* CLIE_STRUCT_H */

