

/* 
 * File:   parms_style.h
 * Author: James Xu
 *
 * Created on 2017.5.18, PM2:29
 */

#ifndef PARMS_STYLE_H
#define PARMS_STYLE_H

//
#include <ctype.h>
#include "obid.h"
#include "osev_macro.h"
#include "memo_utili.h"
// #include "debug_funct_osv.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NULL_TERMINA_LENG   0x01

    // 

    enum _DATA_TYPE_ {
        DATY_INVAL = 0x00,
        DATY_BYTE, // b (int8)
        DATY_UBYTE, // B (uint8)
        DATY_SHORT, // h (int16/short)
        DATY_USHORT, // H (uint16)
        DATY_INT, // i/l (int32/int/long)
        DATY_UINT, // I/L (uint32/unsigned int/unsigned long)
        DATY_LLONG, // q (int64/long long) / quadruple
        DATY_ULLONG, // Q (uint64/unsigned long long)
        DATY_OBID, // o (byte)
        DATY_FLOAT, // f (float)
        DATY_DOUBLE, // d (double)
        DATY_STRI, // s (char)
        DATY_STRZ, // S (string)
        DATY_BINARY // e (byte)
    };

    typedef enum _DATA_TYPE_ DATA_TYPE;

    //
#pragma pack(1)

    struct _byte_entit_ {
        unsigned char notyp;
        char data;
    };

    struct _ubyte_entit_ {
        unsigned char notyp;
        unsigned char data;
    };

    struct _short_entit_ {
        unsigned char notyp;
        short data;
    };

    struct _ushort_entit_ {
        unsigned char notyp;
        unsigned short data;
    };

    struct _int_entit_ {
        unsigned char notyp;
        int data;
    };

    struct _uint_entit_ {
        unsigned char notyp;
        unsigned int data;
    };

    struct _llong_entit_ {
        unsigned char notyp;
        long long data;
    };

    struct _ullong_entit_ {
        unsigned char notyp;
        unsigned long long data;
    };

    struct _obid_entit_ {
        unsigned char notyp;
        osv_oid_t data;
    };

    struct _float_entit_ {
        unsigned char notyp;
        float data;
    };

    struct _double_entit_ {
        unsigned char notyp;
        double data;
    };

    struct _stri_entit_ {
        unsigned char notyp;
        unsigned long long colen; // content length
        char data[0x00];
    };

    struct _strz_entit_ {
        unsigned char notyp;
        unsigned long long colen; // content length
        char data[0x00];
    };

    struct _binary_entit_ {
        unsigned char notyp;
        unsigned long long colen; // content length
        char data[0x00];
    };

    struct _gener_entit_ {
        unsigned char notyp;
        unsigned long long colen; // content length
        char data[0x00];
    }; // virtual entity

#pragma pack()

    typedef struct _byte_entit_ byte_entit;
    typedef struct _ubyte_entit_ ubyte_entit;
    typedef struct _short_entit_ short_entit;
    typedef struct _ushort_entit_ ushort_entit;
    typedef struct _int_entit_ int_entit;
    typedef struct _uint_entit_ uint_entit;
    typedef struct _llong_entit_ llong_entit;
    typedef struct _ullong_entit_ ullong_entit;
    typedef struct _obid_entit_ obid_entit;
    typedef struct _float_entit_ float_entit;
    typedef struct _double_entit_ double_entit;
    typedef struct _stri_entit_ stri_entit;
    typedef struct _strz_entit_ strz_entit;
    typedef struct _binary_entit_ binary_entit;
    typedef struct _gener_entit_ gener_entit; // virtual entity

    // encode param style
    // unsigned 
#define BYTE_PAMSTYL(PSCON, SVALU) { \
    ((byte_entit *) PSCON)->notyp = (unsigned char) DATY_BYTE; \
    ((byte_entit *) PSCON)->data = (char)atoi(SVALU); \
    PSCON += sizeof(byte_entit); \
}

#define UBYTE_PAMSTYL(PSCON, SVALU) { \
    ((ubyte_entit *) PSCON)->notyp = (unsigned char) DATY_UBYTE; \
    ((ubyte_entit *) PSCON)->data = (unsigned char)atoi(SVALU); \
    PSCON += sizeof(ubyte_entit); \
}    

#define SHORT_PAMSTYL(PSCON, SVALU) { \
    ((short_entit *) PSCON)->notyp = (unsigned char) DATY_SHORT; \
    ((short_entit *) PSCON)->data = (short)atoi(SVALU); \
    PSCON += sizeof(short_entit); \
}  

#define USHORT_PAMSTYL(PSCON, SVALU) { \
    ((ushort_entit *) PSCON)->notyp = (unsigned char) DATY_USHORT; \
    ((ushort_entit *) PSCON)->data = (unsigned short)atoi(SVALU); \
    PSCON += sizeof(ushort_entit); \
}  

#define INT_PAMSTYL(PSCON, SVALU) { \
    ((int_entit *) PSCON)->notyp = (unsigned char) DATY_INT; \
    ((int_entit *) PSCON)->data = (int)atoi(SVALU); \
    /* printf("[FUNC]:INT_PAMSTYL:%d\n", ((int_entit *) PSCON)->data); */ \
    PSCON += sizeof (int_entit); \
}

#define UINT_PAMSTYL(PSCON, SVALU) { \
    ((uint_entit *) PSCON)->notyp = (unsigned char) DATY_UINT; \
    ((uint_entit *) PSCON)->data = (unsigned int)atoi(SVALU); \
    PSCON += sizeof(uint_entit); \
}  

#define LLONG_PAMSTYL(PSCON, SVALU) { \
    ((llong_entit *) PSCON)->notyp = (unsigned char) DATY_LLONG; \
    ((llong_entit *) PSCON)->data = (long long)atoll(SVALU); \
    PSCON += sizeof(llong_entit); \
}  

#define ULLONG_PAMSTYL(PSCON, SVALU) { \
    ((ullong_entit *) PSCON)->notyp = (unsigned char) DATY_ULLONG; \
    ((ullong_entit *) PSCON)->data = (unsigned long long)atoll(SVALU); \
    PSCON += sizeof(ullong_entit); \
}

#define OBID_PAMSTYL(PSCON, SVALU) { \
    ((obid_entit *) PSCON)->notyp = (unsigned char) DATY_OBID; \
    OBID_BINARY_COPY(&((obid_entit *) PSCON)->data, (osv_oid_t *) SVALU); \
    PSCON += sizeof(obid_entit); \
}

#define FLOAT_PAMSTYL(PSCON, SVALU) { \
    ((float_entit *) PSCON)->notyp = (unsigned char) DATY_FLOAT; \
    ((float_entit *) PSCON)->data = strtof(SVALU, NULL); \
    PSCON += sizeof(float_entit); \
}

#define DOUBLE_PAMSTYL(PSCON, SVALU) { \
    ((double_entit *) PSCON)->notyp = (unsigned char) DATY_DOUBLE; \
    ((double_entit *) PSCON)->data = atof(SVALU); \
    PSCON += sizeof(double_entit); \
}

    // colen is strlen(str)
#define STRI_PAMSTYL(PSCON, LEN_VALU, SVALU) { \
    ((stri_entit *) PSCON)->notyp = (unsigned char) DATY_STRI; \
    unsigned long long colen = (unsigned long long)strlen(SVALU); \
    ((stri_entit *) PSCON)->colen = colen; \
    memcpy(((stri_entit *) PSCON)->data, SVALU, colen); \
    PSCON = ((stri_entit *) PSCON)->data + colen; \
    LEN_VALU += (colen + sizeof(stri_entit)); \
}

    // colen is 0x01 + strlen(str)
#define STRZ_PAMSTYL(PSCON, LEN_VALU, SVALU) { \
    ((strz_entit *) PSCON)->notyp = (unsigned char) DATY_STRZ; \
    unsigned long long colen = NULL_TERMINA_LENG + (unsigned long long)strlen(SVALU); \
    ((strz_entit *) PSCON)->colen = colen; \
    memcpy(((strz_entit *) PSCON)->data, SVALU, colen); \
    PSCON = ((strz_entit *) PSCON)->data + colen; \
    LEN_VALU += (colen + sizeof(strz_entit)); \
}

#define BINARY_PAMSTYL(PSCON, LEN_VALU, SVALU, ENLEN) { \
    ((binary_entit *) PSCON)->notyp = (unsigned char) DATY_BINARY; \
    ((binary_entit *) PSCON)->colen = (unsigned long long)ENLEN; \
    memcpy(((binary_entit *) PSCON)->data, SVALU, ENLEN); \
    PSCON = ((binary_entit *) PSCON)->data + ENLEN; \
    LEN_VALU += (ENLEN + sizeof(binary_entit)); \
}

#define BINARY_PAMSTYL_EXT(PSCON, SVALU, ENLEN) { \
    ((binary_entit *) PSCON)->notyp = (unsigned char) DATY_BINARY; \
    ((binary_entit *) PSCON)->colen = (unsigned long long)ENLEN; \
    memcpy(((binary_entit *) PSCON)->data, SVALU, ENLEN); \
    PSCON = ((binary_entit *) PSCON)->data + ENLEN; \
}

#define BINARY_PAMSTYL_NAKED(PSCON, SVALU, ENLEN) { \
    memcpy(PSCON, SVALU, ENLEN); \
    PSCON += ENLEN; \
}

    // encode param style

    inline char *byte_pamstyl(char *pscon, char svalu) {
        ((byte_entit *) pscon)->notyp = (unsigned char) DATY_BYTE;
        ((byte_entit *) pscon)->data = svalu;
        return pscon + sizeof (byte_entit);
    }

    inline char *ubyte_pamstyl(char *pscon, unsigned char svalu) {
        ((ubyte_entit *) pscon)->notyp = (unsigned char) DATY_UBYTE;
        ((ubyte_entit *) pscon)->data = svalu;
        return pscon + sizeof (ubyte_entit);
    }

    inline char *short_pamstyl(char *pscon, short svalu) {
        ((short_entit *) pscon)->notyp = (unsigned char) DATY_SHORT;
        ((short_entit *) pscon)->data = svalu;
        return pscon + sizeof (short_entit);
    }

    inline char *ushort_pamstyl(char *pscon, unsigned short svalu) {
        ((ushort_entit *) pscon)->notyp = (unsigned char) DATY_USHORT;
        ((ushort_entit *) pscon)->data = svalu;
        return pscon + sizeof (ushort_entit);
    }

    inline char *int_pamstyl(char *pscon, int svalu) {
        ((int_entit *) pscon)->notyp = (unsigned char) DATY_INT;
        ((int_entit *) pscon)->data = svalu;
        return pscon + sizeof (int_entit);
    }

    inline char *uint_pamstyl(char *pscon, unsigned int svalu) {
        ((uint_entit *) pscon)->notyp = (unsigned char) DATY_UINT;
        ((uint_entit *) pscon)->data = svalu;
        return pscon + sizeof (uint_entit);
    }

    inline char *llong_pamstyl(char *pscon, long long svalu) {
        ((llong_entit *) pscon)->notyp = (unsigned char) DATY_LLONG;
        ((llong_entit *) pscon)->data = svalu;
        return pscon + sizeof (llong_entit);
    }

    inline char *ullong_pamstyl(char *pscon, unsigned long long svalu) {
        ((ullong_entit *) pscon)->notyp = (unsigned char) DATY_ULLONG;
        ((ullong_entit *) pscon)->data = svalu;
        return pscon + sizeof (ullong_entit);
    }

    inline char *obid_pamstyl(char *pscon, osv_oid_t *svalu) {
        ((obid_entit *) pscon)->notyp = (unsigned char) DATY_OBID;
        OBID_BINARY_COPY(&((obid_entit *) pscon)->data, svalu)
        return pscon + sizeof (obid_entit);
    }

    inline char *float_pamstyl(char *pscon, float svalu) {
        ((float_entit *) pscon)->notyp = (unsigned char) DATY_FLOAT;
        ((float_entit *) pscon)->data = svalu;
        return pscon + sizeof (float_entit);
    }

    inline char *double_pamstyl(char *pscon, double svalu) {
        ((double_entit *) pscon)->notyp = (unsigned char) DATY_DOUBLE;
        ((double_entit *) pscon)->data = svalu;
        return pscon + sizeof (double_entit);
    }

    inline char *stri_pamstyl(char *pscon, char *svalu) {
        ((stri_entit *) pscon)->notyp = (unsigned char) DATY_STRI;
        unsigned long long colen = (unsigned long long) strlen(svalu);
        ((stri_entit *) pscon)->colen = colen;
        memcpy(((stri_entit *) pscon)->data, svalu, colen);
        return ((stri_entit *) pscon)->data + colen;
    }

    inline char *strz_pamstyl(char *pscon, char *svalu) {
        ((strz_entit *) pscon)->notyp = (unsigned char) DATY_STRZ;
        unsigned long long colen = NULL_TERMINA_LENG + (unsigned long long) strlen(svalu);
        ((strz_entit *) pscon)->colen = colen;
        memcpy(((strz_entit *) pscon)->data, svalu, colen);
        return ((strz_entit *) pscon)->data + colen;
    }

    inline char *binary_pamstyl(char *pscon, void *svalu, unsigned long long colen) {
        ((binary_entit *) pscon)->notyp = (unsigned char) DATY_BINARY;
        ((binary_entit *) pscon)->colen = colen;
        memcpy(((binary_entit *) pscon)->data, svalu, colen);
        return ((binary_entit *) pscon)->data + colen;
    }

    inline char *binary_pamstyl_naked(char *pscon, void *svalu, unsigned long long enlen) {
        memcpy(pscon, svalu, enlen);
        return pscon + enlen;
    }

    inline char *stri_pamstyl_ext(char *pscon, const char *svalu, unsigned long long colen) {
        ((stri_entit *) pscon)->notyp = (unsigned char) DATY_STRI;
        ((stri_entit *) pscon)->colen = colen;
        memcpy(((stri_entit *) pscon)->data, svalu, colen);
        return ((stri_entit *) pscon)->data + colen;
    }

    inline char *strz_pamstyl_ext(char *pscon, char *svalu, unsigned long long colen) {
        ((strz_entit *) pscon)->notyp = (unsigned char) DATY_STRZ;
        ((strz_entit *) pscon)->colen = colen;
        memcpy(((strz_entit *) pscon)->data, svalu, colen);
        return ((strz_entit *) pscon)->data + colen;
    }

    // DATA_TYPE notyp

    DATA_TYPE check_pamvu_nodtyp(char *data);

    // ("aa", 11, "bb", "cc", 33, 55);
    unsigned long long encod_list_loop(char *pscon, const char **pamvp);
    // ("aa"); // (22);
    unsigned long long encod_list_once(char *pscon, const char *pamvu);

    // decode param style
    // unsigned 
#define PAMSTYL_BYTE(NVALU, PSCON) { \
    if (DATY_BYTE != ((byte_entit *) PSCON)->notyp) \
        return NULL; \
    NVALU = ((byte_entit *) PSCON)->data; \
    PSCON += sizeof(byte_entit); \
}

    //
#define PAMSTYL_UBYTE(NVALU, PSCON) { \
    if (DATY_UBYTE != ((ubyte_entit *) PSCON)->notyp) \
        return NULL; \
    NVALU = ((ubyte_entit *) PSCON)->data; \
    PSCON += sizeof(ubyte_entit); \
}    

    //
#define PAMSTYL_SHORT(NVALU, PSCON) { \
    if (DATY_SHORT != ((short_entit *) PSCON)->notyp) \
        return NULL; \
    NVALU = ((short_entit *) PSCON)->data; \
    PSCON += sizeof(short_entit); \
}  

    //
#define PAMSTYL_USHORT(NVALU, PSCON) { \
    if (DATY_USHORT != ((ushort_entit *) PSCON)->notyp) \
        return NULL; \
    NVALU = ((ushort_entit *) PSCON)->data; \
    PSCON += sizeof(ushort_entit); \
}  

    //
#define PAMSTYL_INT(NVALU, PSCON) { \
    if (DATY_INT != ((int_entit *) PSCON)->notyp) \
        return NULL; \
    NVALU = ((int_entit *) PSCON)->data; \
    PSCON += sizeof (int_entit); \
}

    //
#define PAMSTYL_UINT(NVALU, PSCON) { \
    if (DATY_UINT != ((uint_entit *) PSCON)->notyp) \
        return NULL; \
    NVALU = ((uint_entit *) PSCON)->data; \
    PSCON += sizeof(uint_entit); \
}  

    //
#define PAMSTYL_LLONG(NVALU, PSCON) { \
    if (DATY_LLONG != ((llong_entit *) PSCON)->notyp) \
        return NULL; \
    NVALU = ((llong_entit *) PSCON)->data; \
    PSCON += sizeof(llong_entit); \
}  

    //
#define PAMSTYL_ULLONG(NVALU, PSCON) { \
    if (DATY_ULLONG != ((ullong_entit *) PSCON)->notyp) \
        return NULL; \
    NVALU = ((ullong_entit *) PSCON)->data; \
    PSCON += sizeof(ullong_entit); \
}

#define PAMSTYL_OBID(NVALU, PSCON) { \
    if (DATY_OBID != ((obid_entit *) PSCON)->notyp) \
        return NULL; \
    OBID_BINARY_COPY(NVALU, ((obid_entit *) PSCON)->data) \
    PSCON += sizeof(obid_entit); \
}

    //
#define PAMSTYL_FLOAT(NVALU, PSCON) { \
    if (DATY_FLOAT != ((float_entit *) PSCON)->notyp) \
        return NULL; \
    NVALU = ((float_entit *) PSCON)->data; \
    PSCON += sizeof (float_entit); \
}

    //
#define PAMSTYL_DOUBLE(NVALU, PSCON) { \
    if (DATY_DOUBLE != ((double_entit *) PSCON)->notyp) \
        return NULL; \
    NVALU = ((double_entit *) PSCON)->data; \
    PSCON += sizeof (double_entit); \
}

    //
    // colen is strlen(str)
#define PAMSTYL_STRI(NVALU, LEN_VALU, PSCON) { \
    if (DATY_STRI != ((stri_entit *) PSCON)->notyp) \
        return NULL; \
    unsigned long long colen = ((stri_entit *) PSCON)->colen; \
    memcpy(NVALU, ((stri_entit *) PSCON)->data, colen); \
    NVALU[colen] = '\0'; \
    PSCON = ((stri_entit *) PSCON)->data + colen; \
    LEN_VALU = (colen + sizeof (stri_entit)); \
}

    //
    // colen is 0x01 + strlen(str)
#define PAMSTYL_STRZ(NVALU, LEN_VALU, PSCON) { \
    if (DATY_STRZ != ((strz_entit *) PSCON)->notyp) \
        return NULL; \
    unsigned long long colen = ((strz_entit *) PSCON)->colen; \
    memcpy(NVALU, ((strz_entit *) PSCON)->data, colen); \
    PSCON = ((strz_entit *) PSCON)->data + colen; \
    LEN_VALU = (colen + sizeof (strz_entit)); \
}

    //
#define PAMSTYL_BINARY(NVALU, LEN_VALU, PSCON) { \
    if (DATY_BINARY != ((binary_entit *) PSCON)->notyp) \
        return NULL; \
    unsigned long long olen = ((binary_entit *) PSCON)->colen; \
    memcpy(NVALU, ((binary_entit *) PSCON)->data, olen); \
    PSCON = ((binary_entit *) PSCON)->data + olen; \
    LEN_VALU = olen; \
}

    //
#define PAMSTYL_BINARY_EXT(NVALU, PSCON) { \
    if (DATY_BINARY != ((binary_entit *) PSCON)->notyp) \
        return NULL; \
    unsigned long long olen = ((binary_entit *) PSCON)->colen; \
    memcpy(NVALU, ((binary_entit *) PSCON)->data, olen); \
    PSCON = ((binary_entit *) PSCON)->data + olen; \
}

    // decode param style
#define PSTY_CHAR_ELEN   sizeof(byte_entit)

    inline char *pamstyl_byte(char *ovalu, char *pscon) {
        if (DATY_BYTE != ((byte_entit *) pscon)->notyp)
            return NULL;
        ovalu[0x00] = ((byte_entit *) pscon)->data;
        return pscon + sizeof (byte_entit);
    }

    inline char *pamstyl_ubyte(unsigned char *ovalu, char *pscon) {
        if (DATY_UBYTE != ((ubyte_entit *) pscon)->notyp)
            return NULL;
        ovalu[0x00] = ((ubyte_entit *) pscon)->data;
        return pscon + sizeof (ubyte_entit);
    }

#define PSTY_SHORT_ELEN   sizeof(short_entit)

    inline char *pamstyl_short(short *ovalu, char *pscon) {
        if (DATY_SHORT != ((short_entit *) pscon)->notyp)
            return NULL;
        ovalu[0x00] = ((short_entit *) pscon)->data;
        return pscon + sizeof (short_entit);
    }

    inline char *pamstyl_ushort(unsigned short *ovalu, char *pscon) {
        if (DATY_USHORT != ((ushort_entit *) pscon)->notyp)
            return NULL;
        ovalu[0x00] = ((ushort_entit *) pscon)->data;
        return pscon + sizeof (ushort_entit);
    }

#define PSTY_INT_ELEN   sizeof(int_entit)

    inline char *pamstyl_int(int *ovalu, char *pscon) {
        if (DATY_INT != ((int_entit *) pscon)->notyp)
            return NULL;
        ovalu[0x00] = ((int_entit *) pscon)->data;
        return pscon + sizeof (int_entit);
    }

    inline char *pamstyl_uint(unsigned int *ovalu, char *pscon) {
        if (DATY_UINT != ((uint_entit *) pscon)->notyp)
            return NULL;
        ovalu[0x00] = ((uint_entit *) pscon)->data;
        return pscon + sizeof (uint_entit);
    }

#define PSTY_LONG_ELEN   sizeof(llong_entit)

    inline char *pamstyl_llong(long *ovalu, char *pscon) {
        if (DATY_LLONG != ((llong_entit *) pscon)->notyp)
            return NULL;
        ovalu[0x00] = ((llong_entit *) pscon)->data;
        return pscon + sizeof (llong_entit);
    }

    inline char *pamstyl_ullong(unsigned long *ovalu, char *pscon) {
        if (DATY_ULLONG != ((ullong_entit *) pscon)->notyp)
            return NULL;
        ovalu[0x00] = ((ullong_entit *) pscon)->data;
        return pscon + sizeof (ullong_entit);
    }

#define PSTY_OBID_ELEN   sizeof(obid_entit)

    inline char *pamstyl_obid(osv_oid_t *ovalu, char *pscon) {
        if (DATY_OBID != ((obid_entit *) pscon)->notyp)
            return NULL;
        OBID_BINARY_COPY(ovalu, &((obid_entit *) pscon)->data)
        return pscon + sizeof (obid_entit);
    }

#define PSTY_FLOAT_ELEN   sizeof(float_entit)

    inline char *pamstyl_float(float *ovalu, char *pscon) {
        if (DATY_FLOAT != ((float_entit *) pscon)->notyp)
            return NULL;
        ovalu[0x00] = ((float_entit *) pscon)->data;
        return pscon + sizeof (float_entit);
    }

#define PSTY_DOUBLE_ELEN   sizeof(double_entit)

    inline char *pamstyl_double(double *ovalu, char *pscon) {
        if (DATY_DOUBLE != ((double_entit *) pscon)->notyp)
            return NULL;
        ovalu[0x00] = ((double_entit *) pscon)->data;
        return pscon + sizeof (double_entit);
    }

#define PSTY_STRI_ELEN(pscon)   sizeof(stri_entit) + ((stri_entit *) pscon)->colen

    // colen is strlen(str)

    inline char *pamstyl_stri(char *ovalu, char *pscon) {
        if (DATY_STRI != ((stri_entit *) pscon)->notyp)
            return NULL;
        unsigned long long colen = ((stri_entit *) pscon)->colen;
        memcpy(ovalu, ((stri_entit *) pscon)->data, colen);
        ovalu[colen] = '\0';
        return ((stri_entit *) pscon)->data + colen;
    }

#define PSTY_STRZ_ELEN(pscon)   sizeof(strz_entit) + ((strz_entit *) pscon)->colen

    // colen is 0x01 + strlen(str)

    inline char *pamstyl_strz(char *ovalu, char *pscon) {
        if (DATY_STRZ != ((strz_entit *) pscon)->notyp)
            return NULL;
        unsigned long long colen = ((strz_entit *) pscon)->colen;
        memcpy(ovalu, ((strz_entit *) pscon)->data, colen);
        return ((strz_entit *) pscon)->data + colen;
    }

#define PSTY_OBJE_ELEN(pscon)   sizeof(binary_entit) + ((binary_entit *) pscon)->colen

    inline char *pamstyl_binary(void *ovalu, unsigned long long *colen, char *pscon) {
        if (DATY_BINARY != ((binary_entit *) pscon)->notyp)
            return NULL;
        unsigned long long olen = ((binary_entit *) pscon)->colen;
        memcpy(ovalu, ((binary_entit *) pscon)->data, olen);
        colen[0x00] = olen;
        return ((binary_entit *) pscon)->data + olen;
    }

    inline char *pamstyl_stri_ext(char *ovalu, unsigned long long *enlen, char *pscon) {
        if (DATY_STRI != ((stri_entit *) pscon)->notyp)
            return NULL;
        unsigned long long colen = ((stri_entit *) pscon)->colen;
        memcpy(ovalu, ((stri_entit *) pscon)->data, colen);
        ovalu[colen] = '\0';
        enlen[0x00] = sizeof (stri_entit) + colen;
        return ((stri_entit *) pscon)->data + colen;
    }

    inline char *pamstyl_strz_ext(char *ovalu, unsigned long long *enlen, char *pscon) {
        if (DATY_STRZ != ((strz_entit *) pscon)->notyp)
            return NULL;
        unsigned long long colen = ((strz_entit *) pscon)->colen;
        memcpy(ovalu, ((strz_entit *) pscon)->data, colen);
        enlen[0x00] = sizeof (strz_entit) + colen;
        return ((strz_entit *) pscon)->data + colen;
    }

    inline char *pamstyl_binary_ext(void *ovalu, unsigned long long *enlen, char *pscon) {
        if (DATY_BINARY != ((binary_entit *) pscon)->notyp)
            return NULL;
        unsigned long long colen = ((binary_entit *) pscon)->colen;
        memcpy(ovalu, pscon, sizeof (binary_entit) + colen);
        enlen[0x00] = sizeof (binary_entit) + colen;
        return ((binary_entit *) pscon)->data + colen;
    }

    inline char *decode_pamstyl_enleng(unsigned long long *enlen, char *pscon) {
        switch (((unsigned char *) pscon)[0x00]) {
            case DATY_BYTE:
            case DATY_UBYTE:
#ifdef _DEBUG
                printf("decode_pamstyl byte\n");
#endif // _DEBUG
                enlen[0x00] = sizeof (byte_entit);
                break;
            case DATY_SHORT:
            case DATY_USHORT:
#ifdef _DEBUG
                printf("decode_pamstyl short\n");
#endif // _DEBUG
                enlen[0x00] = sizeof (short_entit);
                break;
            case DATY_INT:
            case DATY_UINT:
#ifdef _DEBUG
                printf("decode_pamstyl int\n");
#endif // _DEBUG
                enlen[0x00] = sizeof (int_entit);
                break;
            case DATY_LLONG:
            case DATY_ULLONG:
#ifdef _DEBUG
                printf("decode_pamstyl long\n");
#endif // _DEBUG
                enlen[0x00] = sizeof (llong_entit);
                break;
            case DATY_OBID:
#ifdef _DEBUG
                printf("decode_pamstyl BOID\n");
#endif // _DEBUG
                enlen[0x00] = sizeof (obid_entit);
                break;
            case DATY_FLOAT:
#ifdef _DEBUG
                printf("decode_pamstyl float\n");
#endif // _DEBUG
                enlen[0x00] = sizeof (float_entit);
                break;
            case DATY_DOUBLE:
#ifdef _DEBUG
                printf("decode_pamstyl double\n");
#endif // _DEBUG
                enlen[0x00] = sizeof (double_entit);
                break;
            case DATY_STRI:
#ifdef _DEBUG
                printf("decode_pamstyl string\n");
#endif // _DEBUG
                enlen[0x00] = sizeof (stri_entit) + ((stri_entit *) pscon)->colen;
                break;
            case DATY_STRZ:
#ifdef _DEBUG
                printf("decode_pamstyl strz\n");
#endif // _DEBUG
                enlen[0x00] = sizeof (strz_entit) + ((strz_entit *) pscon)->colen;
                break;
            case DATY_BINARY:
#ifdef _DEBUG
                printf("decode_pamstyl binary\n");
#endif // _DEBUG
                enlen[0x00] = sizeof (binary_entit) + ((binary_entit *) pscon)->colen;
                break;
            default:
                // _LOG_WARN("default: decode_pamstyl");
                // enlen[0x00] = (unsigned long long) - 1;
                return NULL;
                break;
        }
        //
        return pscon + enlen[0x00];
    }

    //

    inline char *unpak_binary_conte(char *pscon) {
        if (DATY_BINARY != ((binary_entit *) pscon)->notyp)
            return NULL;
        return (((binary_entit *) pscon)->colen) ? ((binary_entit *) pscon)->data : NULL;
    }

    //

    inline char *unpak_conte_leng(unsigned long long *colen, char *pscon) {
        if (DATY_BINARY != ((binary_entit *) pscon)->notyp)
            return NULL;
        colen[0x00] = ((binary_entit *) pscon)->colen;
        return (colen[0x00]) ? ((binary_entit *) pscon)->data : NULL;
    }

    //
#define READ_HEAD_SIZE  (CONTA_LENGTH * 0x02)

    inline int read_requ_head(char *req_had, FILE *fscon) {
        rewind(fscon);
        if ((sizeof (stri_entit) + sizeof (binary_entit)) >= fread(req_had, 0x01, READ_HEAD_SIZE, fscon))
            return -1;
        return 0x00;
    }

    //

    inline unsigned long long creat_binary_size(char *pscon) {
        if (DATY_BINARY != ((binary_entit *) pscon)->notyp)
            return 0x00;
        return ((binary_entit *) pscon)->colen + sizeof (binary_entit);
    }

#ifdef __cplusplus
}
#endif

#endif /* PARMS_STYLE_H */

