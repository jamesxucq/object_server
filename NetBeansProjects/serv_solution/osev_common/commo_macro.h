
#ifndef COMMO_MACRO_H
#define COMMO_MACRO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h>

    //

#ifndef OFF_T
#define OFF_T off_t
#endif

    //
    typedef unsigned char BYTE;

    //
#define POW2N_MOD(nua, nub)  (nua & (nub - 0x01)) // x=2^n a=b%x-->a=b&(x-1)

#define FCLOSE_SAFETY(fptr) if(fptr) fclose(fptr);
#define DELETE_SAFETY(mptr) if(mptr) free(mptr);

#define MK_ZERO(TEXT) TEXT[0x00] = '\0'
#define IS_ZERO(TEXT) ('\0' == TEXT[0x00])
#define NOT_ZERO(TEXT) ('\0' != TEXT[0x00])
#define MK_NONE(PONI) PONI = NULL

#define sslen(str) (sizeof(str) - 0x01)

    //
#ifndef CALLBACK
#define CALLBACK
#endif

#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif

#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef LDECLTYPE
#define LDECLTYPE(x) __typeof(x)
#endif

    //
#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#ifndef MAX_HOST_LEN
#define MAX_HOST_LEN 256
#endif

#ifndef PATH_LEN
#define PATH_LEN 128
#endif

#ifndef MAX_PATH_LEN
#define MAX_PATH_LEN    1024
#endif

#define INVA_POIN_VALU      ((void *) - 1)
#define INVA_UCHA_VALU      ((unsigned char) - 1)
#define INVA_UINT8_VALU     ((unsigned char) - 1)
#define INVA_UINT_VALU      ((unsigned int) - 1)
#define INVA_ULOLO_VALU     ((unsigned long long) - 1)

    //
#ifndef INVA_INDE_VALU
#define INVA_INDE_VALU      ((unsigned int) - 1)
#endif

    //
#define OUT
#define IN

    //
#define LOGI_XOR(A, B) ((A || B)&&!(A && B))

    //
#define MALLOC_NTAI(SIZE, COUN) malloc(SIZE * (0x01 + COUN))
#define REALLOC_NTAI(PTR, SIZE, COUN) realloc(PTR, SIZE * (0x01 + COUN))
#define MEMCPY_NTAI(DEST, SORC, SIZE, COUN) memcpy(DEST, SORC, SIZE * (0x01 + COUN)) 

#define INVAL_POINT (NULL - 0x01)

#ifdef __cplusplus
}
#endif

#endif /* COMMO_MACRO_H */

