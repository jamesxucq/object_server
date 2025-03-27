
/* 
 * File:   load.h
 * Author: James Xu
 *
 * Created on 2017420, PM3:53
 */

#ifndef LOAD_H
#define LOAD_H

#include "../cli_struct.h"
#include "../cstri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 0x00:OK -1:error
    int kits_load(char **pamvp, clie_resu *resul);


#ifdef __cplusplus
}
#endif

#endif /* LOAD_H */

