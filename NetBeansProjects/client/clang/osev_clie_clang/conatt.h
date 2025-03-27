
/* 
 * File:   conatt.h
 * Author: James Xu
 *
 * Created on 2024.1.11., PM 2:09
 */

#ifndef CONATT_H
#define CONATT_H

#ifdef __cplusplus
extern "C" {
#endif

    // #include "commo_header.h"

    struct _cont_atti_ {
        char fmtst[FMTST_COUNT_ZTAI]; // todo:
        unsigned long long data_size;
        unsigned long long last_active; // last active time
        // osv_atomic_t _object_counter_;
    };

    typedef struct _cont_atti_ cont_atti;

    void dele_conat(void *data);

#ifdef __cplusplus
}
#endif

#endif /* CONATT_H */

