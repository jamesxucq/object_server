
/* 
 * File:   fixed_float.h
 * Author: James Xu
 *
 * Created on 2024.3.8, AM 10:00
 */

#ifndef FIXED_FLOAT_H
#define FIXED_FLOAT_H

#ifdef __cplusplus
extern "C" {
#endif

    // 0x00:fixed 0x01:float
#define SET_FIXED_FLOAT(FIXED_FLOAT, FMTSTD) { \
    if (strchr(FMTSTD, 'S')) { \
        FIXED_FLOAT = 0x01; \
    } else FIXED_FLOAT = 0x00; \
}


#ifdef __cplusplus
}
#endif

#endif /* FIXED_FLOAT_H */

