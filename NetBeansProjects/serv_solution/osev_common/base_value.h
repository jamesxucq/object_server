
/* 
 * File:   base_value.h
 * Author: James Xu
 *
 * Created on 2023.5.3, AM 10:44
 */

#ifndef BASE_VALUE_H
#define BASE_VALUE_H

#include "rive_macro.h"
#include "conta_cache.h"
#include "insta_cache.h"

#ifdef __cplusplus
extern "C" {
#endif

    // base info

    struct _base_valu_ {
        char base_name[BASE_LENGTH]; // base name
        osv_oid_t base_obid; // base object id
        uint32 lvmsk_code; // running privile code
        rive_conne rivcon[STORA_ENGINE_COUNT]; // storage handle
        hand_hmap hando_stm; // lev1 object method data
        lv2pm_hmap lv2pm_stm; // levn_hm/lv2p object data
        cont_lsmp conda_stm; // container
        inst_hmap insda_stm;// instant
    };

    typedef struct _base_valu_ base_valu;


#ifdef __cplusplus
}
#endif

#endif /* BASE_VALUE_H */

