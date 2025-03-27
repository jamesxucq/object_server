
/* 
 * File:   tran_gcc_cpp.h
 * Author: James Xu
 *
 * Created on 2017.5.16, AM10:53
 */

#ifndef TRAN_GCC_CPP_H
#define TRAN_GCC_CPP_H

#include "../../clit_struct.h"
#include "../../cstri_utili.h"
#include "../kstri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 0x00:OK -1:error
    int trans_gcc_cpp(char **pamvp, clit_resu *resul, osev_clie *oclie);


#ifdef __cplusplus
}
#endif

#endif /* TRAN_GCC_CPP_H */

