
/* 
 * File:   compa_style.h
 * Author: James Xu
 *
 * Created on 2023.10.16, PM 3:12
 */

#ifndef COMPA_STYLE_H
#define COMPA_STYLE_H

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

    struct _obje_compa_ {
        unsigned long long colen; // content length
        char data[0x00];
    };
#pragma pack()

    typedef struct _obje_compa_ obje_compa;

    //
    // decode param style
    // unsigned 
#define COMPA_BYTE(NVALU, PSCON) { \
    NVALU = ((char *) PSCON)[0x00]; \
    PSCON += sizeof(char); \
}

    //
#define COMPA_UBYTE(NVALU, PSCON) { \
    NVALU = ((unsigned char *) PSCON)[0x00]; \
    PSCON += unsigned sizeof(char); \
}    

    //
#define COMPA_SHORT(NVALU, PSCON) { \
    NVALU = ((short *) PSCON)[0x00]; \
    PSCON += sizeof(short); \
}  

    //
#define COMPA_USHORT(NVALU, PSCON) { \
    NVALU = ((unsigned short *) PSCON)[0x00]; \
    PSCON += sizeof(unsigned short); \
}  

    //
#define COMPA_INT(NVALU, PSCON) { \
    NVALU = ((int *) PSCON)[0x00]; \
    PSCON += sizeof(int); \
}

    //
#define COMPA_UINT(NVALU, PSCON) { \
    NVALU = ((unsigned int *) PSCON)[0x00]; \
    PSCON += sizeof(unsigned int); \
}  

    //
#define COMPA_LLONG(NVALU, PSCON) { \
    NVALU = ((long long *) PSCON)[0x00]; \
    PSCON += sizeof(long long); \
}  

    //
#define COMPA_ULLONG(NVALU, PSCON) { \
    NVALU = ((unsigned long long *) PSCON)[0x00]; \
    PSCON += sizeof(unsigned long long); \
}

    //
#define COMPA_OBJID(NVALU, PSCON) { \
    memcpy(NVALU, PSCON, sizeof (osv_oid_t)); \
    PSCON += sizeof (osv_oid_t); \
}
    
    //
#define COMPA_FLOAT(NVALU, PSCON) { \
    NVALU = ((float *) PSCON)[0x00]; \
    PSCON += sizeof(float); \
}

    //
#define COMPA_DOUBLE(NVALU, PSCON) { \
    NVALU = ((double *) PSCON)[0x00]; \
    PSCON += sizeof(double); \
}

    //

#define COMPA_STRI(NVALU, PSCON, LEN_VALU) { \
    memcpy(NVALU, PSCON, LEN_VALU); \
    PSCON += LEN_VALU; \
}

    //
    // colen is 0x01 + strlen(str)
#define COMPA_STRZ(NVALU, PSCON) { \
    unsigned long long colen = NULL_TERMINA_LENG + (unsigned long long)strlen(PSCON); \
    memcpy(NVALU, PSCON, colen); \
    PSCON += colen; \
}

    //

#define COMPA_BINA(NVALU, PSCON) { \
    unsigned long long olen = ((obje_compa *) PSCON)->colen; \
    memcpy(NVALU, ((obje_compa *) PSCON)->data, olen); \
    PSCON = ((obje_compa *) PSCON)->data + olen; \
}

    //

#define COMPA_BINA_EXT(NVALU, PSCON) { \
    unsigned long long olen = ((obje_compa *) PSCON)->colen; \
    memcpy(NVALU, ((obje_compa *) PSCON)->data, olen); \
    PSCON = ((obje_compa *) PSCON)->data + olen; \
}

#ifdef __cplusplus
}
#endif

#endif /* COMPA_STYLE_H */

