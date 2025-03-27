
/* 
 * File:   bitcpy.h
 * Author: James Xu
 *
 * Created on 2023.6.6, PM 4:47
 */

#ifndef BITCPY_H
#define BITCPY_H

#ifdef __cplusplus
extern "C" {
#endif

#define BIT8_BINCPY(DAT2, DAT1) *(uint8_t *)DAT2 = *(uint8_t *)DAT1
#define BIT16_BINCPY(DAT2, DAT1) *(uint16_t *)DAT2 = *(uint16_t *)DAT1
#define BIT32_BINCPY(DAT2, DAT1) *(uint32_t *)DAT2 = *(uint32_t *)DAT1
#define BIT64_BINCPY(DAT2, DAT1) *(uint64_t *)DAT2 = *(uint64_t *)DAT1

    //

#define BITCPY(DAT2, DAT1, SIZE) { \
    switch (SIZE) { \
        case 0x01: \
            BIT8_BINCPY(DAT2, DAT1); \
            break; \
        case 0x02: \
            BIT16_BINCPY(DAT2, DAT1); \
            break; \
        case 0x03: \
            BIT32_BINCPY(DAT2, DAT1); \
            break; \
        case 0x04: \
            BIT64_BINCPY(DAT2, DAT1); \
            break; \
        default: \
            break; \
    } \
}

#ifdef __cplusplus
}
#endif

#endif /* BITCPY_H */

