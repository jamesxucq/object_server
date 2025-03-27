
/* 
 * File:   misc.h
 * Author: james
 *
 * Created on 2022.9.27, PM 4:16
 */

#ifndef MISC_H
#define MISC_H

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef unsigned char u_char;

    //
    typedef signed char int8_t;
    typedef unsigned char uint8_t;
    typedef signed short int int16_t;
    typedef unsigned short int uint16_t;
    typedef signed int int32_t;
    typedef unsigned int uint32_t;
#if __WORDSIZE == 64
    typedef signed long int int64_t;
    typedef unsigned long int uint64_t;
#else
    typedef signed long long int int64_t;
    typedef unsigned long long int uint64_t;
#endif

#ifndef __ssize_t_defined // HAVE_SSIZE_T
    typedef int ssize_t;
#endif

    //
#define PK_UNUSED(var) (void)(var)

    //
#define PK_INTPACK64_MAXSIZE ((int)sizeof(int64_t) + 1)

#define PK_STORE_SIZE(s) ((uint32_t)(s))
#define PK_PTRDIFF(end, begin) ((size_t)((const uint8_t *)(end) - (const uint8_t *)(begin)))

    // Function return value and scratch buffer declaration and initialization.
#define PK_DECL_ITEM(i) PK_ITEM *i = NULL
#define PK_DECL_RET int ret = 0

#define PK_ASSERT(exp) assert(exp)
#define PK_CLEAR(s) memset(&(s), 0, sizeof(s))

    //
#define __pk_snprintf snprintf

    // Check if a string matches a byte string of len bytes.
#define PK_STRING_MATCH(str, bytes, len)                                                        \
    (((const char *)(str))[0] == ((const char *)(bytes))[0] && strncmp(str, bytes, len) == 0 && \
      (str)[len] == '\0')

    //
#define __pk_calloc_one(addr) __pk_calloc((size_t)1, sizeof(**(addr)), addr)

#define __pk_free(p)                     \
    do {                                 \
        void *__p = &(p);                \
        if (*(void **)__p != NULL)       \
            __pk_free_int(__p);          \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif /* MISC_H */

