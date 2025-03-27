#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>
#include <ctype.h>

#include "last_stri.h"

//

char *lsprif(char *dest_last, const char *format, ...) {
    va_list arg;
    int done;
    //
    va_start(arg, format);
    done = vsprintf(dest_last, format, arg);
    va_end(arg);
    if (0x00 > done) return NULL;
    //
    return dest_last + done;
}

char *lsncpy(char *dest_last, const char *src, size_t n) {
    char c;
    //
    if (n >= 4) {
        size_t n4 = n >> 2;
        for (;;) {
            c = *src++;
            *dest_last = c;
            if (c == '\0') break;
            ++dest_last;
            c = *src++;
            *dest_last = c;
            if (c == '\0') break;
            ++dest_last;
            c = *src++;
            *dest_last = c;
            if (c == '\0') break;
            ++dest_last;
            c = *src++;
            *dest_last = c;
            if (c == '\0') break;
            ++dest_last;
            if (--n4 == 0) goto last_chars;
        }
        return dest_last;
    }
last_chars:
    n &= 3;
    if (n == 0) {
        *dest_last = '\0';
        return dest_last;
    }
    for (;;) {
        c = *src++;
        *dest_last = c;
        if (c == '\0') break;
        ++dest_last;
        if (--n == 0) {
            *dest_last = '\0';
            return dest_last;
        }
    }
    //
    return dest_last;
}

// aaa|bbb|ccc|ddd 1:aaa 2:bbb 3:ccc 4:ddd

char *strsplit(char *str, const char *delim) {
    char *toksp;
    static char *tokep;
    //
    if (!str) {
        if (!tokep) return NULL;
        toksp = tokep + strlen(delim);
    } else toksp = str;
    //
    tokep = strstr(toksp, delim);
    if (tokep) *tokep = '\0';
    //
    return toksp;
}

char *strlchr(const char *str) {
    char *char_ptr;
    unsigned long int *longword_ptr;
    unsigned long int longword, himagic, lomagic;
    //
    for (char_ptr = (char *) str; ((unsigned long int) char_ptr & (sizeof (longword) - 1)) != 0; ++char_ptr) {
        if (*char_ptr == '\0')
            return (char_ptr - 1);
    }
    //
    longword_ptr = (unsigned long int *) char_ptr;
    himagic = 0x80808080L;
    lomagic = 0x01010101L;
    if (sizeof (longword) > 4) {
        himagic = ((himagic << 16) << 16) | himagic;
        lomagic = ((lomagic << 16) << 16) | lomagic;
    }
    if (sizeof (longword) > 8) abort();
    //
    for (;;) {
        longword = *longword_ptr++;
        if (((longword - lomagic) & ~longword & himagic) != 0) {
            char *cp = (char *) (longword_ptr - 1);
            //
            if (cp[0x00] == 0)
                return (cp - 1);
            if (cp[1] == 0)
                return cp;
            if (cp[2] == 0)
                return (cp + 1);
            if (cp[3] == 0)
                return (cp + 2);
            if (sizeof (longword) > 4) {
                if (cp[4] == 0)
                    return (cp + 3);
                if (cp[5] == 0)
                    return (cp + 4);
                if (cp[6] == 0)
                    return (cp + 5);
                if (cp[7] == 0)
                    return (cp + 6);
            }
        }
    }
}

char *strend(const char *str) {
    char *char_ptr;
    unsigned long int *longword_ptr;
    unsigned long int longword, himagic, lomagic;
    //
    for (char_ptr = (char *) str; ((unsigned long int) char_ptr & (sizeof (longword) - 1)) != 0; ++char_ptr) {
        if (*char_ptr == '\0')
            return char_ptr;
    }
    //
    longword_ptr = (unsigned long int *) char_ptr;
    himagic = 0x80808080L;
    lomagic = 0x01010101L;
    if (sizeof (longword) > 4) {
        himagic = ((himagic << 16) << 16) | himagic;
        lomagic = ((lomagic << 16) << 16) | lomagic;
    }
    if (sizeof (longword) > 8) abort();
    //
    for (;;) {
        longword = *longword_ptr++;
        if (((longword - lomagic) & ~longword & himagic) != 0) {
            char *cp = (char *) (longword_ptr - 1);
            //
            if (cp[0x00] == 0)
                return cp;
            if (cp[1] == 0)
                return (cp + 1);
            if (cp[2] == 0)
                return (cp + 2);
            if (cp[3] == 0)
                return (cp + 3);
            if (sizeof (longword) > 4) {
                if (cp[4] == 0)
                    return (cp + 4);
                if (cp[5] == 0)
                    return (cp + 5);
                if (cp[6] == 0)
                    return (cp + 6);
                if (cp[7] == 0)
                    return (cp + 7);
            }
        }
    }
}


