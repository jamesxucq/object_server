
/* 
 * File:   last_stri.h
 * Author: James Xu
 *
 * Created on 2023.4.20, PM 2:20
 */

#ifndef LAST_STRI_H
#define LAST_STRI_H

#include <stddef.h>
#include <string.h>
#include <ctype.h>

#ifdef __cplusplus
extern "C" {
#endif

    // return: src end

    inline char *escpy(char * dest, const char * src) {
        register char *d = dest;
        register char *s = (char *) src;
        while ((*d++ = *s)) ++s;
        return s;
    }

    // return: dest end
    char *lsprif(char *dest_last, const char *format, ...);

    inline char *lscpy(char * dest_last, const char * src) {
        register char *d = dest_last;
        register const char *s = src;
        while ((*d = *s++)) ++d;
        return d;
    }

    inline char *lccpy(char * dest_last, const char src) {
        dest_last[0x00] = src;
        (++dest_last)[0x00] = '\0';
        return dest_last;
    }

    char *lsncpy(char * dest_last, const char *src, size_t n);

    inline char *lszcpy(char *dest_last, const char *source, size_t count) {
        while (count && (*dest_last++ = *source++)) count--; /* copy string */
        dest_last[0x00] = '\0';
        return (dest_last);
    }

#define LSCAT(DEST, SORC) lscpy(DEST + strlen(DEST), SORC) 

    inline char *lccat(char * dest, const char src) {
        dest += strlen(dest);
        dest[0x00] = src;
        (++dest)[0x00] = '\0';
        return dest;
    }

    inline char *lsncat(char *dest, const char *src, size_t n) {
        char *destptr = dest + strlen(dest);
        for (; n > 0 && (*destptr = *src) != '\0'; ++src, ++destptr, --n);
        if (n == 0) *destptr = '\0';
        return destptr;
    }

    // aaa|bbb|ccc|ddd return, 1:aaa 2:bbb 3:ccc 4:ddd
    char *strsplit(char *str, const char *delim);

    // a->A

    inline char *strupr(char *str) {
        char *toke = str;
        for (; toke[0x00]; ++toke) {
            if (toke[0x00] >= 'a' && toke[0x00] <= 'z')
                toke[0x00] ^= 0x20;
        }
        //
        return str;
    }
    // A->a

    inline char *strlow(char *str) {
        char *toke = str;
        for (; toke[0x00]; ++toke) {
            if (toke[0x00] >= 'A' && toke[0x00] <= 'Z')
                toke[0x00] ^= 0x20;
        }
        //
        return str;
    }

    // find ct from cs, pass "[]"and "()"

    inline char *ospbrk(const char *cs, const char *ct) {
        const char *sc1, *sc2;
        for (sc1 = cs; '\0' != *sc1; ++sc1) {
            if ('[' == *sc1) {
                ++sc1;
                while (']' != *sc1) {
                    if ('\0' == *sc1) return NULL;
                    ++sc1;
                }
            } else if ('(' == *sc1) {
                ++sc1;
                while (')' != *sc1) {
                    if ('\0' == *sc1) return NULL;
                    ++sc1;
                }
            }
            for (sc2 = ct; '\0' != *sc2; ++sc2) {
                if (*sc1 == *sc2)
                    return (char *) sc1;
            }
        }
        return NULL;
    }

    // s: start, n:find count, c:find char, from start to end

    inline char *strnchr(char *s, char c, size_t n) {
        while (*s != '\0' && n && *s != c) {
            ++s;
            n--;
        }
        return *s == c ? s : NULL;
    }
    // s: start, e:end, c:find char, from start to end

    inline char *osechr(char *s, char c, char *e) {
        while (*s != '\0' && e != s && *s != c) {
            ++s;
        }
        return *s == c ? s : NULL;
    }
    // s: start, e:end, c:find char, from end to start

    inline char *osrchr(char *s, char c, char *e) {
        while ((s <= e) && (c != *e)) {
            --e;
        }
        return c == *e ? e : NULL;
    }

    //
#define STRI_EXCHANGE(STR1, STR2, ESTR) { \
    ESTR = STR1; \
    STR1 = STR2; \
    STR2 = ESTR; \
    ESTR = NULL; \
}

    // find chr from str, pass ""

    inline char *qstrch(const char * str, int chr) {
        while (*str && *str != (char) chr) {
            if ('\\' == *str) ++str;
            else if ('"' == *str) {
                for (++str; '"' != *str; ++str) {
                    if (!*str) return NULL;
                    if ('\\' == *str) ++str;
                }
            }
            ++str;
        }
        return (*str == (char) chr) ? ((char *) str) : (NULL);
    }
    // find str2 from str1, pass ""

    inline char *qstrst(const char * str1, const char * str2) {
        char *cp = (char *) str1;
        char *s1, *s2;
        if (!*str2) return ((char *) str1);
        while (*cp) {
            if ('\\' == *cp) ++cp;
            else if ('"' == *cp) {
                for (++cp; '"' != *cp; ++cp) {
                    if (!*cp) return NULL;
                    if ('\\' == *cp) ++cp;
                }
            } else {
                s1 = cp;
                s2 = (char *) str2;
                while (*s1 && *s2 && !(*s1 - *s2)) ++s1, ++s2;
                if (!*s2) return (cp);
            }
            ++cp;
        }
        return (NULL);
    }
    // complare p1 and p2

    inline int ostrcmp(const char *p1, const char *p2) {
        const unsigned char *s1 = (const unsigned char *) p1;
        const unsigned char *s2 = (const unsigned char *) p2;
        unsigned char c1, c2;
        do {
            c1 = (unsigned char) *s1++;
            c2 = (unsigned char) *s2++;
            if (c1 == '\0')
                return c1 - c2;
        } while (c1 == c2);
        return c1 - c2;
    }

    char *strlchr(const char *str);
    // "xxxxx" return last char '\0'
    char *strend(const char *str);
    // copy src to dest and dest last char is  '\0'

    inline char *strzcpy(char *dest, const char *source, size_t count) {
        char *start = dest;
        while (count && (*dest++ = *source++)) --count; /* copy string */
        if (count) /* pad out with zeroes */
            while (--count) *dest++ = '\0';
        else *dest = '\0';
        return (start);
    }

    //

    inline char *strcpy_s(char *dest, size_t desiz, const char *source) {
        char *start = dest;
        for (--desiz; desiz && (*dest++ = *source++); --desiz); /* copy string */
        if (!desiz) *(dest) = '\0';
        return (start);
    }

    // "  xx xxx  " -> "xx"
#define STRZCPY(DEST, SOURCE, COUNT) { \
    strzcpy(DEST, SOURCE, COUNT); \
    blank_decode(DEST); \
}
    // "  xx xxx  " -> "xx"
#define STRCPY(DEST, SOURCE) { \
    strcpy(DEST, SOURCE); \
    blank_decode(DEST); \
}

    // STRI="  xx xxx  " -> STRI="xx xxx  "
#define PASS_BLANK(STRI) { \
    for (; '\0' != STRI[0x00]; ++STRI) { \
        if (' ' != STRI[0x00]) break; \
    } \
}

    // STRI="_xx_xxx  xxxxx" -> STRI="  xxxxx"
#define PASS_NAME(STRI) { \
    for (; '\0' != STRI[0x00]; ++STRI) { \
        if (!isalnum(STRI[0x00]) && ('_' != STRI[0x00])) \
            break; \
    } \
}

    // STRI="  xx xxx  " -> TOKE="xx xxx  "
#define PASS_TBLANK(TOKE, STRI) { \
    for (TOKE = (STRI); '\0' != TOKE[0x00]; ++TOKE) { \
        if (' ' != TOKE[0x00]) break; \
    } \
}

    // STRI="xx xxx  " -> STRI=" xxx  "
#define FIND_BLANK(STRI) { \
    for (; '\0' != STRI[0x00]; ++STRI) { \
        if (' ' == STRI[0x00]) break; \
    } \
}

    // STRI="xx xxx  " -> TOKE=" xxx  "
#define FIND_TBLANK(TOKE, STRI) { \
    for (TOKE = (STRI); '\0' != TOKE[0x00]; ++TOKE) { \
        if (' ' == TOKE[0x00]) break; \
    } \
}

    // "  xx xxx  " -> "xx xxx  "

    inline char *pass_blank(char *blkstr) {
        for (; '\0' != blkstr[0x00]; ++blkstr) {
            if (' ' != blkstr[0x00]) return blkstr;
        }
        return NULL;
    }
    // "  xx xxx  " -> "  xx xxx"

    inline char *pass_rblak(char *blkstr) {
        char *toke = blkstr;
        while ('\0' != toke[0x00]) ++toke;
        for (--toke; blkstr <= toke; --toke) {
            if (' ' != toke[0x00]) {
                (++toke)[0x00] = '\0';
                break;
            }
        }
        if (blkstr > toke) (blkstr)[0x00] = '\0';
        return blkstr;
    }
    // "  xx xxx  " -> "xx xxx"

    inline char *kill_blank(char *blkstr) {
        char *toksp, *tokep;
        if (!blkstr) return NULL;
        tokep = blkstr;
        while (' ' == tokep[0x00] && '\0' != tokep[0x00]) ++tokep;
        if ('\0' == tokep[0x00]) {
            blkstr[0x00] = '\0';
            return blkstr;
        }
        toksp = blkstr;
        if (tokep == toksp) {
            while ('\0' != toksp[0x00]) ++toksp;
        } else for (; '\0' != tokep[0x00]; ++toksp, ++tokep) toksp[0x00] = tokep[0x00];
        for (--toksp; blkstr <= toksp; --toksp) {
            if (' ' != toksp[0x00]) {
                (++toksp)[0x00] = '\0';
                break;
            }
        }
        if (blkstr > toksp) (blkstr)[0x00] = '\0';
        //
        return blkstr;
    }

    // "  xx xxx  " -> "xx"

    inline char *blank_decode(char *blkstr) {
        char *toksp, *tokep;
        if (' ' == blkstr[0x00]) {
            tokep = toksp = blkstr;
            for (++toksp; '\0' != toksp[0x00] && ' ' == toksp[0x00]; ++toksp);
            for (; '\0' != toksp[0x00] && ' ' != toksp[0x00]; ++toksp)
                *tokep++ = *toksp;
        } else {
            tokep = blkstr;
            for (++tokep; '\0' != tokep[0x00] && ' ' != tokep[0x00]; ++tokep);
        }
        tokep[0x00] = '\0';
        return blkstr;
    }

    // STRI="  \nxx\n xxx  " -> TOKE="xx\n xxx  "
#define KILL_INVAL(TOKE, STRI) { \
    for (TOKE = STRI; '\0' != TOKE[0x00]; ++TOKE) { \
        if (' ' != TOKE[0x00] && '\n' != TOKE[0x00]) break; \
    } \
}
    // "  \nxx\n xxx  " -> "xx\n xxx  "

    inline char *kill_inval(char *inv_str) {
        for (; '\0' != inv_str[0x00]; ++inv_str) {
            if (' ' != inv_str[0x00] && '\n' != inv_str[0x00])
                return inv_str;
        }
        return NULL;
    }

    // "  ;\nxx\n xxx  " -> "xx\n xxx  "

    inline char *kill_semic(char *inv_str) {
        for (; '\0' != inv_str[0x00]; ++inv_str) {
            if (';' != inv_str[0x00]
                    && ' ' != inv_str[0x00]
                    && '\n' != inv_str[0x00])
                return inv_str;
        }
        return NULL;
    }

    // return str alpha or number

    inline char *straln(char *str) {
        for (; '\0' != str[0x00]; ++str) {
            if (isalnum(str[0x00])) return str;
        }
        return NULL;
    }
    // return str alpha

    inline char *stralp(char *str) {
        for (; '\0' != str[0x00]; ++str) {
            if (isalpha(str[0x00])) return str;
        }
        return NULL;
    }
    // return str digit

    inline char *strdig(char *str) {
        for (; '\0' != str[0x00]; ++str) {
            if (isdigit(str[0x00])) return str;
        }
        return NULL;
    }
    // return str digit or quote

    inline char *strpar(char *str) {
        for (; '\0' != str[0x00]; ++str) {
            if ('"' == str[0x00] || isalnum(str[0x00]))
                return str;
        }
        return NULL;
    }

    // "\"xxxxx\"" -> "xxxxx"

    inline char *quote_decode(char *quostr) {
        char *tokep;
        for (; '\0' != quostr[0x00]; ++quostr) {
            if ('\\' == quostr[0x00]) ++quostr;
            else if ('"' == quostr[0x00]) {
                tokep = quostr;
                ++quostr;
                while ('\0' != quostr[0x00]) {
                    if ('\\' == quostr[0x00]) {
                        tokep[0x00] = quostr[0x00];
                        ++quostr;
                        ++tokep;
                    } else if ('"' == quostr[0x00]) break;
                    tokep[0x00] = quostr[0x00];
                    ++quostr;
                    ++tokep;
                }
                tokep[0x00] = '\0';
                break;
            }
        }
        return quostr;
    }
    // kill quote from string array
#define KILL_QUOTE(STRI) { \
    char **ptok = STRI; \
    for (; ptok[0x00]; ++ptok) quote_decode(ptok[0x00]); \
}

    //

#define LSCPY_O(DEST, SORC, LAST) { \
    DEST = LAST; \
    LAST = lscpy(LAST, SORC); \
    ++LAST; \
}

#define LSCPY_INI(DEST, LAST) DEST = LAST;
#define LSCPY_FIN(LAST, DEST) { \
    LAST = strend(DEST); \
    ++LAST; \
}

#define LSZCPY_O(DEST, SORC, COUN, LAST) { \
    DEST = LAST; \
    LAST = lszcpy(LAST, SORC, COUN); \
    ++LAST; \
}

    //
    char *next_dirpath(char *path, char *subdir);

    // "aaa|bbb|ccc" -> LINE_TXT="bbb"
#define TEXT_SPLIT(LINE_TXT, STRI, DELIM, TOKEP) { \
    char *toksp; \
    if(STRI) { \
        toksp = STRI; \
        TOKEP = strstr(toksp, DELIM); \
        if (TOKEP) *TOKEP = '\0'; \
        LINE_TXT = toksp; \
    } else LINE_TXT = NULL; \
}
    // "aaa|bbb|ccc" -> LINE_TXT="bbb"
#define SPLIT_TOKEN(LINE_TXT, DELIM, TOKEP) { \
    char *toksp; \
    if(TOKEP) { \
        toksp = TOKEP + strlen(DELIM); \
        TOKEP = strstr(toksp, DELIM); \
        if (TOKEP) *TOKEP = '\0'; \
        LINE_TXT = toksp; \
    } else LINE_TXT = NULL; \
}

    // "aaa bbb ccc" -> TVALU="bbb"
#define SPLIT_VALUE(TVALU, LINE_TXT) { \
    char *toksp, *tokep; \
    toksp = strchr(LINE_TXT, ' '); \
    if (toksp) *toksp = '\0'; \
    ++toksp; \
    tokep = strrchr(toksp, ' '); \
    if (tokep) *tokep = '\0'; \
    TVALU = toksp; \
}

    // "aaa: bbb" -> TVALU="bbb"
#define SPLIT_LINE(TVALU, LINE_TXT) { \
    char *toke; \
    toke = strstr(LINE_TXT, ": "); \
    if (toke) *toke = '\0'; \
    TVALU = toke + 2; \
}


#ifdef __cplusplus
}
#endif

#endif /* LAST_STRI_H */

