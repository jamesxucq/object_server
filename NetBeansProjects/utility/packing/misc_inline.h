
/* 
 * File:   misc_inline.h
 * Author: james
 *
 * Created on 2022.9.28, PM 4:26
 */

#ifndef MISC_INLINE_H
#define MISC_INLINE_H

#ifdef __cplusplus
extern "C" {
#endif

    //

    //__pk_strnlen --
    // Determine the length of a fixed-size string

    static inline size_t __pk_strnlen(const char *s, size_t maxlen) {
        size_t i;
        for (i = 0; i < maxlen && *s != '\0'; ++i, ++s);
        return (i);
    }


#ifdef __cplusplus
}
#endif

#endif /* MISC_INLINE_H */

