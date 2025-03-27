
/* 
 * File:   dropq.h
 * Author: James Xu
 *
 * Created on 2017.4.11, AM10:14
 */

#ifndef DROPQ_H
#define DROPQ_H

#include "rive_bzl.h"
#include "contain.h"
#include "conattr.h"

#ifdef __cplusplus
extern "C" {
#endif

    // -1:error 0x00:ok 0x01:exception

    inline int drop_qcont_conta(riv_sessi_t *seion, rive_ha *stora_ha, char *basen, osv_oid_t *cont_obid, char *contn) {
        int drop_valu = stora_ha->dorp_contai(seion, contn);
        if (!drop_valu)
            drop_valu = dele_cont_atti(cont_obid, basen);
        return drop_valu;
    }


#ifdef __cplusplus
}
#endif

#endif /* DROPQ_H */

