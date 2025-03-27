
/* 
 * File:   finalize.h
 * Author: James Xu
 *
 * Created on 2017.4.1, AM8:52
 */

#ifndef FINALIZE_H
#define FINALIZE_H

#include "proce_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    extern void(*requ_finalize_tab[LEVTYP_COUNT][LEVIVK_COUNT])(session*);
    extern void(*resp_finalize_tab[LEVTYP_COUNT][LEVIVK_COUNT])(session*);

#ifdef __cplusplus
}
#endif

#endif /* FINALIZE_H */

