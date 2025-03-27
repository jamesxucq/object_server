
/* 
 * File:   chk_reque_param.h
 * Author: James Xu
 *
 * Created on 2023.3.27, AM 11:13
 */

#ifndef CHK_REQUE_PARAM_H
#define CHK_REQUE_PARAM_H

#ifdef __cplusplus
extern "C" {
#endif

    //errno
#define CHECK_SINGLE_PARAM(RESCTL, ERRNO, PARAM) \
            if (!PARAM) { \
                PDAT_EXCEPTIO_TAIL(RESCTL, ERRNO) \
                return -1; \
            }

#define CHECK_COUPLE_PARAM(RESCTL, ERRNO, PARAM_I, PARAM_II) \
            if (!PARAM_I || !PARAM_II) { \
                PDAT_EXCEPTIO_TAIL(RESCTL, ERRNO) \
                return -1; \
            }

#define CHECK_THREE_PARAM(RESCTL, ERRNO, PARAM_I, PARAM_II, PARAM_III) \
            if (!PARAM_I || !PARAM_II || !PARAM_III) { \
                PDAT_EXCEPTIO_TAIL(RESCTL, ERRNO) \
                return -1; \
            }

#ifdef __cplusplus
}
#endif

#endif /* CHK_REQUE_PARAM_H */

