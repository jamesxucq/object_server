
/* 
 * File:   chk_invok_parms.h
 * Author: james
 *
 * Created on 2023.3.27, PM 2:13
 */

#ifndef CHK_INVOK_PARMS_H
#define CHK_INVOK_PARMS_H

#ifdef __cplusplus
extern "C" {
#endif

#define CHECK_PARAM_ONE(PARAM) \
            if (!PARAM) { return -1; }

#define CHECK_PARAM_TWO(PARAMO, PARAMT) \
            if (!PARAMO || !PARAMT) { return -1; }


#ifdef __cplusplus
}
#endif

#endif /* CHK_INVOK_PARMS_H */

