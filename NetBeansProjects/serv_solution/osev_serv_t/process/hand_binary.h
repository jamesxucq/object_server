#ifndef HAND_BINARY_H
#define HAND_BINARY_H

#include "proce_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    // handle recv 
    extern unsigned int(*requ_handler_tab[LEVTYP_COUNT][LEVIVK_COUNT])(reque_ctrl *, evdata *);

    // handle send
    extern unsigned int(*resp_handler_tab[LEVTYP_COUNT][LEVIVK_COUNT])(respo_ctrl *, evdata *);

#ifdef __cplusplus
}
#endif

#endif /* HAND_BINARY_H */