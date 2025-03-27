
/* 
 * File:   respo_pack.h
 * Author: James Xu
 *
 * Created on 2022.10.5, AM 9:36
 */

#ifndef RESPO_PACK_H
#define RESPO_PACK_H

#include "third_party.h"
#include "commo_macro.h"
#include "osev_datyp.h"
#include "obid.h"

#ifdef __cplusplus
extern "C" {
#endif

    // compress data
#define RESPON_ATTACH_LENGTH (sizeof (osv_oid_i) + sizeof (uint32))

    //
#pragma pack(1)

    struct _resp_node_t_ {
        osv_oid_i obid;
        uint32 leng;
        char data[0x00];
    };

#pragma pack()

    typedef struct _resp_node_t_ resp_node_t;

    //
    int resp_data_pack(void *buffe, size_t *lenp, PK_ITEM *key, PK_ITEM *value);
    int resp_data_pack_obid(void *buffe, size_t *lenp, osv_oid_i *obid, PK_ITEM *value);

    //
    int resp_data_unpack();

    //
    int resp_data_size();


#ifdef __cplusplus
}
#endif

#endif /* RESPO_PACK_H */

