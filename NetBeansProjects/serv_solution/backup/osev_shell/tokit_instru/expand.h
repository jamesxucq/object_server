
/* 
 * File:   expand.h
 * Author: james
 *
 * Created on 2024.5.17, PM 4:34
 */

#ifndef EXPAND_H
#define EXPAND_H

#include "../cli_struct.h"
#include "../cstri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 0x00:OK -1:error
    int kits_expand(char **pamvp, clie_resu *resul, osev_clie *oclie);


#ifdef __cplusplus
}
#endif

#endif /* EXPAND_H */

