
/* 
 * File:   osev_datyp.h
 * Author: James Xu
 *
 * Created on 2024.4.25, AM 9:36
 */

#ifndef OSEV_DATYP_H
#define OSEV_DATYP_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#ifndef int8
#define int8 char
#endif

#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef int16
#define int16 short
#endif

#ifndef uint16
#define uint16 unsigned short
#endif

#ifndef int32
#define int32 int
#endif

#ifndef uint32
#define uint32 unsigned int
#endif

#ifndef int64
#define int64 long long int
#endif

#ifndef uint64
#define uint64 unsigned long long int
#endif

#ifndef obid
#define obid osv_oid_t
#endif

    // {"float", "float"},
    // {"double", "double"},
    // {"char", "char"},

#ifndef strnz
#define stinz char *
#endif

#ifndef __cplusplus
#ifndef byte
#define byte (unsigned char)
#endif
#endif

    //

#ifdef __cplusplus
}
#endif

#endif /* OSEV_DATYP_H */

