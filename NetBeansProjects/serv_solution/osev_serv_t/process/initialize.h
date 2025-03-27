#ifndef INITIALIZE_H
#define INITIALIZE_H

#include "proce_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    extern unsigned int (*requ_initialize_tab[LEVTYP_COUNT][LEVIVK_COUNT])(session *, evdata *);
    extern unsigned int (*resp_initialize_tab[LEVTYP_COUNT][LEVIVK_COUNT])(session *, evdata *);

#ifdef __cplusplus
}
#endif

#endif /* INITIALIZE_H */