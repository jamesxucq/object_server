
/* 
 * File:   kcomm_types.h
 * Author: James Xu
 *
 * Created on 2023.3.17, AM 9:04
 */

#ifndef KCOMM_TYPES_H
#define KCOMM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

    /////////////////////////////////////////////
    extern const struct stst_node ostyp_clang_dict[];

    /////////////////////////////////////////////
    // int8_t uint8_t int16_t uint16_t int32_t uint32_t int64_t uint64_t char stri
    extern const struct stch_node ostyp_fmtst_dict[];

    /////////////////////////////////////////////
    // trans-serve
    extern const struct stin_node retyp_calle_dict[];

    /////////////////////////////////////////////
    // trans-serve
#define PARM_INVAL  0x0000
#define PARM_ARRAY  0x0001
#define PARM_DEFAU  0x0002 
#define PARM_NUMB   0x0100
#define PARM_OBID   0x0200
#define PARM_STRI   0x0400
#define PARM_STRZ   0x0800
#define PARM_BYTE   0x1000
    // trans-serve
    extern const struct stin_node ostyp_pamati_dict[];

    /////////////////////////////////////////////
    // trans-serve
    extern const struct stin_node ostyp_potyp_dict[];

    /////////////////////////////////////////////
    // trans-serve
    // int8_t uint8_t int16_t uint16_t int32_t uint32_t int64_t uint64_t char stri
    extern char potyp_fmtst_tab[];

    /////////////////////////////////////////////
    extern char *potyp_clang_tab[];

    /////////////////////////////////////////////
    extern char *potyp_ostyp_tab[];

    /////////////////////////////////////////////


#ifdef __cplusplus
}
#endif

#endif /* KCOMM_TYPES_H */

