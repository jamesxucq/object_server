
/* 
 * File:   memo_utili.h
 * Author: James Xu
 *
 * Created on 2023.9.12, PM 3:43
 */

#ifndef MEMO_UTILI_H
#define MEMO_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    // last memcpy
#define LAMCPY_BIN(DEST, SORC, LENG, LAST) { \
    DEST = LAST; \
    memcpy(LAST, SORC, LENG); \
    LAST += LENG; \
}
#define LAMCPY_INS(DEST, LENG, LAST) { \
    DEST = LAST; \
    LAST += LENG; \
}
#define LAMCPY_INI(DEST, LAST) DEST = LAST;
#define LAMCPY_FIN(LAST, LENG) LAST += LENG;

    // last equal unsigned long long
    // LAMEQU_ULL(pamvp[0x00], ((binary_entit *) req_dat)->data - sta_tok, _data_line_);
#define LAMEQU_ULL(DEST, VALU, LAST) { \
    DEST = LAST; \
    *((unsigned long long *) DEST) = (VALU); \
    LAST += sizeof(unsigned long long); \
}

    // escape
#define OBJE_IDENT_TYPE 0x07 // BEL, '\a'
#define BINA_ENTIT_TYPE 0x10 // DLE

#define ESCA_NODTYP_PART     0x0000
#define ESCA_OBIDCON_PART    0x0001    
#define ESCA_ENCOLEN_PART    0x0001
#define ESCA_ENTICON_PART    0x0009

    // escpae memcpy

#define ESMCPY_OBID(DEST, SORC) { \
    DEST[ESCA_NODTYP_PART] = OBJE_IDENT_TYPE; \
    ((osv_oid_i *) (DEST + ESCA_OBIDCON_PART))->stoid = ((osv_oid_i *)SORC)->stoid; \
    ((osv_oid_i *) (DEST + ESCA_OBIDCON_PART))->osev_unique = ((osv_oid_i *)SORC)->osev_unique; \
}

    //

#define ESCA_ECONTE_POSI(DEST) (DEST + ESCA_ENTICON_PART)

#define MAKE_ESCHEAD_BINA(DEST, SIZE) { \
    DEST[ESCA_NODTYP_PART] = BINA_ENTIT_TYPE; \
    ((unsigned long long*) (DEST + ESCA_ENCOLEN_PART))[0x00] = SIZE; \
}

#define ESMCPY_BINARY(DEST, SORC, SIZE) { \
    DEST[ESCA_NODTYP_PART] = BINA_ENTIT_TYPE; \
    ((unsigned long long*) (DEST + ESCA_ENCOLEN_PART))[0x00] = SIZE; \
    memcpy(DEST + ESCA_ENTICON_PART, SORC, SIZE); \
}

#define ESMCPY_BINARY_II(DEST, SRC_I, SRC_II, SIZE) { \
    DEST[ESCA_NODTYP_PART] = BINA_ENTIT_TYPE; \
    ((unsigned long long*) (DEST + ESCA_ENCOLEN_PART))[0x00] = 0x02 * SIZE; \
    memcpy(DEST + ESCA_ENTICON_PART, SRC_I, SIZE); \
    memcpy(DEST + ESCA_ENTICON_PART + SIZE, SRC_II, SIZE); \
}

#ifdef __cplusplus
}
#endif

#endif /* MEMO_UTILI_H */

