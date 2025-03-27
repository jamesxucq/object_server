
/* 
 * File:   strz.h
 * Author: James Xu
 *
 * Created on 2023.6.13, AM 9:03
 */

#ifndef STRZ_H
#define STRZ_H

#ifdef __cplusplus
extern "C" {
#endif

#define STRZ_TYPE_OSEV                  0x00
#define STRZ_TYPE_USER                  0x0f
#define STRZ_TYPE_STAT                  0xf0

#pragma pack(1)

    struct _strz_t_ {
        unsigned char type; // 0x00:osev 0x0f:user 0xf0:stat
        char *data;
        unsigned long long slen; // string leng
        unsigned long long asiz; // alloc size
    };

#pragma pack()

    typedef struct _strz_t_ strz_t;

    //

#pragma pack(1)

    struct _strz_i_ {
        unsigned char type; // 0x00:osev 0x0f:user 0xf0:stat
        char *data;
        unsigned long long slen; // string leng
        unsigned long long asiz; // alloc size
    };

#pragma pack()

    typedef struct _strz_i_ strz_i;
    
    //
    
    inline char *lscpy_stz(char * dest_last, const char * src) {
        register char *d = dest_last;
        register const char *s = src;
        while ((*d = *s++)) ++d;
        return ++d;
    }

#ifdef __cplusplus
}
#endif

#endif /* STRZ_H */

