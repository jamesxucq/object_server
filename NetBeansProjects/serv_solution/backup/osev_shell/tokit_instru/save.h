
/* 
 * File:   save.h
 * Author: James Xu
 *
 * Created on 2017.4.20, PM3:53
 */

#ifndef SAVE_H
#define SAVE_H

#include "../cli_struct.h"
#include "../cstri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    // 0x00:OK -1:error
    int kits_save(char **pamvp, clie_resu *resul);

#ifdef __cplusplus
}
#endif

#endif /* SAVE_H */

