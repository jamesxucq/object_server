/* 
 * File:   exceptio.h
 * Author: James Xu
 *
 * Created on
 */

#ifndef EXCEPTIO_H
#define EXCEPTIO_H

#include "proce_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    extern void(*rvse_exceptio_tab[LEVTYP_COUNT][LEVIVK_COUNT])(session*);

#ifdef __cplusplus
}
#endif

#endif /* EXCEPTIO_H */

