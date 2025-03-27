
/* 
 * File:   conve.h
 * Author: James Xu
 *
 * Created on 2017.4.20, PM3:53
 */

#ifndef CONVE_H
#define CONVE_H

#include "../cli_struct.h"
#include "../cstri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 0x00:OK -1:error
    int kits_conver(char **pamvp, clie_resu *resul, osev_clie *oclie);

#ifdef __cplusplus
}
#endif

#endif /* CONVE_H */

