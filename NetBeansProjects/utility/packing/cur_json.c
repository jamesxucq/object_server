
#include <stddef.h>
#include <errno.h>

#include "error.h"
#include "cur_json.h"
#include "hex.h"
#include "misc.h"


// __pk_json_strlen --
// Return the number of bytes represented by a string in JSON format, or -1 if the format is incorrect.

ssize_t __pk_json_strlen(const char *src, size_t srclen) {
    size_t dstlen;
    u_char hi, lo;
    const char *srcend;

    dstlen = 0;
    srcend = src + srclen;
    while (src < srcend) {
        // JSON can include any UTF-8 expressed in 4 hex chars.
        if (*src == '\\') {
            if (*++src == 'u') {
                if (__pk_hex2byte((const u_char *) ++src, &hi))
                    return (-1);
                src += 2;
                if (__pk_hex2byte((const u_char *) src, &lo))
                    return (-1);
                src += 2;
                if (hi != 0)
                    // For our dump representation, every Unicode character on input represents a
                    // single byte.
                    return (-1);
            }
        } else
            src++;
        dstlen++;
    }
    if (src != srcend)
        return (-1); // invalid input, e.g. final char is '\\'
    return ((ssize_t) dstlen);
}

// __pk_json_strncpy --
// Copy bytes of string in JSON format to a destination, up to dstlen bytes. If dstlen is
// greater than the needed size, the result if zero padded.

int __pk_json_strncpy(char **pdst, size_t dstlen, const char *src, size_t srclen) {
    u_char hi, lo;
    char ch, *dst;
    const char *dstend, *srcend;

    dst = *pdst;
    dstend = dst + dstlen;
    srcend = src + srclen;
    while (src < srcend && dst < dstend) {
        // JSON can include any UTF-8 expressed in 4 hex chars.
        if ((ch = *src++) == '\\')
            switch (ch = *src++) {
                case 'u':
                    if (__pk_hex2byte((const u_char *) src, &hi) ||
                            __pk_hex2byte((const u_char *) src + 2, &lo))
                        PK_RET_MSG(EINVAL, "invalid Unicode within JSON string");
                    src += 4;
                    if (hi != 0)
                        PK_RET_MSG(EINVAL, "Unicode \"%6.6s\" byte out of range in JSON", src - 6);
                    *dst++ = (char) lo;
                    break;
                case 'f':
                    *dst++ = '\f';
                    break;
                case 'n':
                    *dst++ = '\n';
                    break;
                case 'r':
                    *dst++ = '\r';
                    break;
                case 't':
                    *dst++ = '\t';
                    break;
                case '"':
                case '\\':
                    *dst++ = ch;
                    break;
                default:
                    // return (__pk_illegal_value(ch));
                    return -1;
            } else
            *dst++ = ch;
    }
    if (src != srcend)
        PK_RET_MSG(ENOMEM, "JSON string copy destination buffer too small");
    *pdst = dst;
    while (dst < dstend)
        *dst++ = '\0';
    return (0);
}
