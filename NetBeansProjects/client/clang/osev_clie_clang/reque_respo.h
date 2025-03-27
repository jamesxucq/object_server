
/* 
 * File:   reque_respo.h
 * Author: James Xu
 *
 * Created on 2017.4.27, PM3:03
 */

#ifndef REQUE_RESPO_H
#define REQUE_RESPO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_macro.h"
#include "osev_datyp.h"
#include "clie_macro.h"

    //`

#define REQU_MEMORY_TYPE 0x00
#define REQU_STREAM_TYPE 0x01

    struct _requ_data_t_ {
        unsigned int requ_type; // 0x01:stream / 0x00:memory
        unsigned long long requ_leng;
        FILE *requ_stram;
        char requ_memo[REQU_DATA_SIZE];
    };

    typedef struct _requ_data_t_ requ_data_t;

#define CAT_REQDAT_QLN(REQU, HEAD) \
    (REQU).requ_leng = REQU_HEAD_BLEN + ((requ_head*) HEAD)->content_length;

    //
#pragma pack(1)

    struct _resp_data_t_ {
        RESPON_HEAD
        FILE *resp_stram;
        char resp_memo[RESP_DATA_SIZE];
    };
#pragma pack(0)

    typedef struct _resp_data_t_ resp_data_t;

#ifdef __cplusplus
}
#endif

#endif /* REQUE_RESPO_H */

