
/* 
 * File:   explain.h
 * Author: James Xu
 *
 * Created on 2024.5.17, PM 4:34
 */

#ifndef EXPLAIN_H
#define EXPLAIN_H

#include "../clit_struct.h"
#include "../cstri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 0x00:OK -1:error
    int kits_explain(char **pamvp, clit_resu *resul, osev_clie *oclie);


#ifdef __cplusplus
}
#endif

#endif /* EXPLAIN_H */

