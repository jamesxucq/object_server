
/* 
 * File:   pretty.h
 * Author: James Xu
 *
 * Created on 2017.4.20, PM3:52
 */

#ifndef PRETTY_H
#define PRETTY_H

#include "../cli_struct.h"
#include "../cstri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 0x00:OK -1:error
    int kits_pretty(char **pamvp, clie_resu *resul);


#ifdef __cplusplus
}
#endif

#endif /* PRETTY_H */

