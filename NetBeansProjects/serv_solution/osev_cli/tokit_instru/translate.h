
/* 
 * File:   translate.h
 * Author: James Xu
 *
 * Created on 2017.4.20, PM3:53
 */

#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "../clit_struct.h"
#include "../cstri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 0x00:OK -1:error
    int kits_translate(char **pamvp, clit_resu *resul, osev_clie *oclie);

#ifdef __cplusplus
}
#endif

#endif /* TRANSLATE_H */

