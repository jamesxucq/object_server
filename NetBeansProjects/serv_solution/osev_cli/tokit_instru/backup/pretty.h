
/* 
 * File:   pretty.h
 * Author: James Xu
 *
 * Created on 2017.4.20, PM3:52
 */

#ifndef PRETTY_H
#define PRETTY_H

#include "../shell_struct.h"
#include "../sstri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 0x00:OK -1:error
    int utili_pretty(char **paraep, shel_resu *resul);


#ifdef __cplusplus
}
#endif

#endif /* PRETTY_H */

