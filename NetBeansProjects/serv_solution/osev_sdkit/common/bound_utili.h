
/* 
 * File:   bound_utili.h
 * Author: James Xu
 *
 * Created on 2023.6.12, AM 8:35
 */

#ifndef BOUND_UTILI_H
#define BOUND_UTILI_H

#include "commo_header.h"
#include "loop_memo.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int conti_object_strz(valu_memo_t *obje_memp, lv2pme *lv2me);
    int conti_object_sloop(loop_memo_t *obje_memp, lv2pme *lv2me);

    //
    int conti_object_lv2po(loop_memo_t *obje_memp, lv2pme *lv2me);

#ifdef __cplusplus
}
#endif

#endif /* BOUND_UTILI_H */

