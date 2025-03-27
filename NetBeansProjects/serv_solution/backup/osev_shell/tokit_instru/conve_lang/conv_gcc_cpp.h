
/* 
 * File:   conv_gcc_cpp.h
 * Author: James Xu
 *
 * Created on 2017.5.16, AM10:53
 */

#ifndef CONV_GCC_CPP_H
#define CONV_GCC_CPP_H

#include "../../cli_struct.h"
#include "../../cstri_utili.h"
#include "../kstri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 0x00:OK -1:error
    int conve_gcc_cpp(char **pamvp, clie_resu *resul, osev_clie *oclie);


#ifdef __cplusplus
}
#endif

#endif /* CONV_GCC_CPP_H */

