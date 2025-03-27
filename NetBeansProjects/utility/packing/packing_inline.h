
/* Throughout this code we have to be aware of default argument conversion.
 * Refer to Chapter 8 of "Expert C Programming" by Peter van der Linden for the gory details. The
 * short version is that we have less cases to deal with because the compiler promotes shorter types
 * to int or unsigned int. */

#include "packing.h"

typedef struct {

    union {
        int64_t i;
        uint64_t u;
        const char *s;
        PK_ITEM item;
        float f; /* add by james 20230525 */
        double d; /* add by james 20230525 */
        osv_oid_t *o; /* add by james 20230525 */
        PK_NODE node; /* add by james 20230605 */
        //
        size_t size; /* add by james 20230605 */
    } u;
    uint32_t size;
    int8_t havesize;
    char type;
    size_t rsl; /* add by james 20230605, result string length */
} PK_PACK_VALUE;

// Default to size = 1 if there is no size prefix.
#define PK_PACK_VALUE_INIT \
    {                      \
        {0}, 1, 0, 0, 0    \
    }
#define PK_DECL_PACK_VALUE(pv) PK_PACK_VALUE pv = PK_PACK_VALUE_INIT

typedef struct {
    const char *cur, *end, *orig;
    unsigned long repeats;
    PK_PACK_VALUE lastv;
} PK_PACK;

#define PK_PACK_INIT                                  \
    {                                                 \
        NULL, NULL, NULL, NULL, 0, PK_PACK_VALUE_INIT \
    }
#define PK_DECL_PACK(pack) PK_PACK pack = PK_PACK_INIT

typedef struct {
    PK_CONFIG config;
    char buf[20];
    int count;
    bool iskey;
    int genname;
} PK_PACK_NAME;

// __pack_initn --
// Initialize a pack iterator with the specified string and length.

static inline int __pack_initn(PK_PACK *pack, const char *fmt, size_t len) {
    if (*fmt == '@' || *fmt == '<' || *fmt == '>')
        return (EINVAL);
    if (*fmt == '.')
        ++fmt;

    pack->cur = pack->orig = fmt;
    pack->end = fmt + len;
    pack->repeats = 0;
    return (0);
}

// __pack_init --
// Initialize a pack iterator with the specified string.

static inline int __pack_init(PK_PACK *pack, const char *fmt) {
    return (__pack_initn(pack, fmt, strlen(fmt)));
}

static inline void __pack_reset(PK_PACK *pack) {
    pack->cur = pack->orig;
    pack->repeats = 0;
}

// __pack_name_init --
// Initialize the name of a pack iterator.

static inline void __pack_name_init(PK_CONFIG_ITEM *names, bool iskey, PK_PACK_NAME *pn) {
    PK_CLEAR(*pn);
    pn->iskey = iskey;

    if (names->str != NULL)
        __pk_config_subinit(&pn->config, names);
    else
        pn->genname = 1;
}

// __pack_name_next --
// Get the next field type from a pack iterator.

static inline int __pack_name_next(PK_PACK_NAME *pn, PK_CONFIG_ITEM *name) {
    PK_CONFIG_ITEM ignore;

    if (pn->genname) {
        PK_RET(
                __pk_snprintf(pn->buf, sizeof (pn->buf), (pn->iskey ? "key%d" : "value%d"), pn->count));
        PK_CLEAR(*name);
        name->str = pn->buf;
        name->len = strlen(pn->buf);

        // C++ treats nested structure definitions differently to C, as such we need to use scope
        // resolution to fully define the type.

#ifdef __cplusplus
        name->type = PK_CONFIG_ITEM::PK_CONFIG_ITEM_STRING;
#else
        name->type = PK_CONFIG_ITEM_STRING;
#endif
        pn->count++;
    } else
        PK_RET(__pk_config_next(&pn->config, name, &ignore));

    return (0);
}

// __pack_next --
// Next pack iterator.

static inline int __pack_next(PK_PACK *pack, PK_PACK_VALUE *pv) {
    char *endsize;

    if (pack->repeats > 0) {
        *pv = pack->lastv;
        --pack->repeats;
        return (0);
    }

next:
    if (pack->cur == pack->end)
        return (PK_NOTFOUND);

    if (__pk_isdigit((u_char) * pack->cur)) {
        pv->havesize = 1;
        pv->size = PK_STORE_SIZE(strtoul(pack->cur, &endsize, 10));
        pack->cur = endsize;
    } else {
        pv->havesize = 0;
        pv->size = 1;
    }

    pv->type = *pack->cur++;
    pack->repeats = 0;

    switch (pv->type) {
        case 'S':
            return (0);
        case 's':
            if (pv->size < 1)
                PK_RET_MSG(EINVAL,
                    "Fixed length strings must be at least 1 byte in format '%.*s'",
                    (int) (pack->end - pack->orig), pack->orig);
        case 'x':
            return (0);
        case 't':
            if (pv->size < 1 || pv->size > 8)
                PK_RET_MSG(EINVAL,
                    "Bitfield sizes must be between 1 and 8 bits in format '%.*s'",
                    (int) (pack->end - pack->orig), pack->orig);
        case 'u':
            // Special case for items with a size prefix.
            pv->type = (!pv->havesize && *pack->cur != '\0') ? 'U' : 'u';
            return (0);
        case 'U':
            // Don't change the type. 'U' is used internally, so this type was already changed to
            // explicitly include the size.
            return (0);
        case 'b':
        case 'h':
        case 'i':
        case 'B':
        case 'H':
        case 'I':
        case 'l':
        case 'L':
        case 'q':
        case 'Q':
        case 'o': // add by james 20230525
        case 'f': // add by james 20230525
        case 'd': // add by james 20230525
        case 'r':
        case 'R':
            // Integral types repeat <size> times.
            if (pv->size == 0)
                goto next;
            pv->havesize = 0;
            pack->repeats = pv->size - 1;
            pack->lastv = *pv;
            return (0);
        default:
            PK_RET_MSG(EINVAL, "Invalid type '%c' found in format '%.*s'", pv->type,
                    (int) (pack->end - pack->orig), pack->orig);
    }
}

#define PK_PACK_GET(pv, ap)                                        \
    do {                                                           \
        PK_ITEM *__item;                                           \
        switch ((pv).type) {                                       \
        case 'x':                                                  \
            break;                                                 \
        case 's':                                                  \
        case 'S':                                                  \
            (pv).u.s = va_arg(ap, const char *);                   \
            break;                                                 \
        case 'U':                                                  \
        case 'u':                                                  \
            __item = va_arg(ap, PK_ITEM *);                        \
            (pv).u.item.data = __item->data;                       \
            (pv).u.item.size = __item->size;                       \
            break;                                                 \
        case 'b':                                                  \
        case 'h':                                                  \
        case 'i':                                                  \
            (pv).u.i = va_arg(ap, int);                            \
            break;                                                 \
        case 'B':                                                  \
        case 'H':                                                  \
        case 'I':                                                  \
        case 't':                                                  \
            (pv).u.u = va_arg(ap, unsigned int);                   \
            break;                                                 \
        case 'l':                                                  \
            (pv).u.i = va_arg(ap, long);                           \
            break;                                                 \
        case 'L':                                                  \
            (pv).u.u = va_arg(ap, unsigned long);                  \
            break;                                                 \
        case 'q':                                                  \
            (pv).u.i = va_arg(ap, int64_t);                        \
            break;                                                 \
        case 'Q':                                                  \
        case 'r':                                                  \
        case 'R':                                                  \
            (pv).u.u = va_arg(ap, uint64_t);                       \
            break;                                                 \
        case 'o': /* add by james 20230525 */                      \
            (pv).u.o = va_arg(ap, osv_oid_t *);                    \
            break;                                                 \
        case 'f': /* add by james 20230525 */                      \
            (pv).u.f = va_arg(ap, double);                         \
            break;                                                 \
        case 'd': /* add by james 20230525 */                      \
            (pv).u.d = va_arg(ap, double);                         \
            break;                                                 \
        default:                                                   \
            /* User format strings have already been validated. */ \
            /* return (__pk_illegal_value((pv).type));*/           \
            return -1;                                             \
        }                                                          \
    } while (0)

// __pack_size --
// Get the size of a packed value.

static inline int __pack_size(PK_PACK_VALUE * pv, size_t * vp) {
    size_t s, pad;

    switch (pv->type) {
        case 'x':
            *vp = pv->size;
            return (0);
        case 'j':
        case 'J':
        case 'K':
            // These formats are only used internally.
            if (pv->type == 'j' || pv->havesize)
                s = pv->size;
            else {
                ssize_t len;

                // The string was previously validated.
                len = __pk_json_strlen((const char *) pv->u.item.data, pv->u.item.size);
                PK_ASSERT(len >= 0);
                s = (size_t) len + (pv->type == 'K' ? 0 : 1);
            }
            *vp = s;
            return (0);
        case 's':
        case 'S':
            if (pv->type == 's' || pv->havesize) {
                s = pv->size;
                PK_ASSERT(s != 0);
            } else
                s = strlen(pv->u.s) + 1;
            *vp = s;
            return (0);
        case 'U':
        case 'u':
            s = pv->u.item.size;
            pad = 0;
            if (pv->havesize && pv->size < s)
                s = pv->size;
            else if (pv->havesize)
                pad = pv->size - s;
            if (pv->type == 'U')
                s += __pk_vsize_uint(s + pad);
            *vp = s + pad;
            return (0);
        case 'b':
        case 'B':
        case 't':
            *vp = 1;
            return (0);
        case 'h':
        case 'i':
        case 'l':
        case 'q':
            *vp = __pk_vsize_int(pv->u.i);
            return (0);
        case 'H':
        case 'I':
        case 'L':
        case 'Q':
        case 'r':
            *vp = __pk_vsize_uint(pv->u.u);
            return (0);
        case 'R':
            *vp = sizeof (uint64_t);
            return (0);
        case 'o': // add by james 20230525
            *vp = sizeof (osv_oid_t);
            return (0);
        case 'f': // add by james 20230525
            *vp = sizeof (float);
            return (0);
        case 'd': // add by james 20230525
            *vp = sizeof (double);
            return (0);
    }

    PK_RET_MSG(EINVAL, "unknown pack-value type: %c", (int) pv->type);
}

// __pack_write --
// Pack a value into a buffer.

static inline int __pack_write(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
    size_t s, pad;
    uint8_t *oldp;

    switch (pv->type) {
        case 'x':
            PK_SIZE_CHECK_PACK(pv->size, maxlen);
            memset(*pp, 0, pv->size);
            *pp += pv->size;
            break;
        case 's':
            PK_SIZE_CHECK_PACK(pv->size, maxlen);
            memcpy(*pp, pv->u.s, pv->size);
            *pp += pv->size;
            break;
        case 'S':
            /* When preceded by a size, that indicates the maximum number of bytes the string can store,
             * this does not include the terminating NUL character. In a string with characters less
             * than the specified size, the remaining bytes are NULL padded. */
            if (pv->havesize) {
                s = __pk_strnlen(pv->u.s, pv->size);
                pad = (s < pv->size) ? pv->size - s : 0;
            } else {
                s = strlen(pv->u.s);
                pad = 1;
            }
            PK_SIZE_CHECK_PACK(s + pad, maxlen);
            if (s > 0)
                memcpy(*pp, pv->u.s, s);
            *pp += s;
            if (pad > 0) {
                memset(*pp, 0, pad);
                *pp += pad;
            }
            break;
        case 'j':
        case 'J':
        case 'K':
            // These formats are only used internally.
            s = pv->u.item.size;
            if ((pv->type == 'j' || pv->havesize) && pv->size < s) {
                s = pv->size;
                pad = 0;
            } else if (pv->havesize)
                pad = pv->size - s;
            else if (pv->type == 'K')
                pad = 0;
            else
                pad = 1;
            if (s > 0) {
                oldp = *pp;
                PK_RET(__pk_json_strncpy((char **) pp, maxlen, (const char *) pv->u.item.data, s));
                maxlen -= (size_t) (*pp - oldp);
            }
            if (pad > 0) {
                PK_SIZE_CHECK_PACK(pad, maxlen);
                memset(*pp, 0, pad);
                *pp += pad;
            }
            break;
        case 'U':
        case 'u':
            s = pv->u.item.size;
            pad = 0;
            if (pv->havesize && pv->size < s)
                s = pv->size;
            else if (pv->havesize)
                pad = pv->size - s;
            if (pv->type == 'U') {
                oldp = *pp;
                // Check that there is at least one byte available: the low-level routines treat zero
                // length as unchecked.
                PK_SIZE_CHECK_PACK(1, maxlen);
                PK_RET(__pk_vpack_uint(pp, maxlen, s + pad));
                maxlen -= (size_t) (*pp - oldp);
            }
            PK_SIZE_CHECK_PACK(s + pad, maxlen);
            if (s > 0)
                memcpy(*pp, pv->u.item.data, s);
            *pp += s;
            if (pad > 0) {
                memset(*pp, 0, pad);
                *pp += pad;
            }
            break;
        case 'b':
            // Translate to maintain ordering with the sign bit.
            PK_SIZE_CHECK_PACK(1, maxlen);
            **pp = (uint8_t) (pv->u.i + 0x80);
            *pp += 1;
            break;
        case 'B':
        case 't':
            PK_SIZE_CHECK_PACK(1, maxlen);
            **pp = (uint8_t) pv->u.u;
            *pp += 1;
            break;
        case 'h':
        case 'i':
        case 'l':
        case 'q':
            // Check that there is at least one byte available: the low-level routines treat zero length
            // as unchecked.
            PK_SIZE_CHECK_PACK(1, maxlen);
            PK_RET(__pk_vpack_int(pp, maxlen, pv->u.i));
            break;
        case 'H':
        case 'I':
        case 'L':
        case 'Q':
        case 'r':
            // Check that there is at least one byte available: the low-level routines treat zero length
            // as unchecked.
            PK_SIZE_CHECK_PACK(1, maxlen);
            PK_RET(__pk_vpack_uint(pp, maxlen, pv->u.u));
            break;
        case 'R':
            PK_SIZE_CHECK_PACK(sizeof (uint64_t), maxlen);
            *(uint64_t *) *pp = pv->u.u;
            *pp += sizeof (uint64_t);
            break;
        case 'o': // add by james 20230525
            PK_SIZE_CHECK_PACK(sizeof (osv_oid_t), maxlen);
            memcpy(*pp, pv->u.o, sizeof (osv_oid_t));
            *pp += sizeof (osv_oid_t);
            break;
        case 'f': // add by james 20230525
            PK_SIZE_CHECK_PACK(sizeof (float), maxlen);
            *(float *) *pp = pv->u.f;
            *pp += sizeof (float);
            break;
        case 'd': // add by james 20230525
            PK_SIZE_CHECK_PACK(sizeof (double), maxlen);
            *(double *) *pp = pv->u.d;
            *pp += sizeof (double);
            break;
        default:
            PK_RET_MSG(EINVAL, "unknown pack-value type: %c", (int) pv->type);
    }

    return (0);
}

// add by james 20230607

/*
             PK_SIZE_CHECK_PACK(1, maxlen);
 **pp = (uint8_t) (pv->u.i + 0x80);
 *pp += 1;
 */

static inline int __pack_write_node(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
    switch (pv->u.node.size) {
        case 0x01:
            PK_SIZE_CHECK_PACK(1, maxlen);
            *(uint8_t *) *pp = *(uint8_t *) pv->u.node.data;
            *pp += 0x01;
            break;
        case 0x02:
            PK_SIZE_CHECK_PACK(2, maxlen);
            *(uint16_t *) *pp = *(uint16_t *) pv->u.node.data;
            *pp += 0x02;
            break;
        case 0x03:
            PK_SIZE_CHECK_PACK(3, maxlen);
            *(uint32_t *) *pp = *(uint32_t *) pv->u.node.data;
            *pp += 0x03;
            break;
        case 0x04:
            PK_SIZE_CHECK_PACK(4, maxlen);
            *(uint64_t *) *pp = *(uint64_t *) pv->u.node.data;
            *pp += 0x04;
            break;
        default:
            PK_SIZE_CHECK_PACK(pv->u.node.size, maxlen);
            memcpy(*pp, pv->u.node.data, pv->u.node.size);
            *pp += pv->u.node.size;
            break;
    }

    return (0);
}

// __unpack_read --
// Read a packed value from a buffer.

static inline int __unpack_read(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
    size_t s;

    switch (pv->type) {
        case 'x':
            PK_SIZE_CHECK_UNPACK(pv->size, maxlen);
            *pp += pv->size;
            break;
        case 's':
        case 'S':
            if (pv->type == 's' || pv->havesize) {
                s = pv->size;
                PK_ASSERT(s != 0);
            } else
                s = strlen((const char *) *pp) + 1;
            if (s > 0)
                pv->u.s = (const char *) *pp;
            PK_SIZE_CHECK_UNPACK(s, maxlen);
            *pp += s;
            break;
        case 'U':
            // Check that there is at least one byte available: the low-level routines treat zero length
            // as unchecked.
            PK_SIZE_CHECK_UNPACK(1, maxlen);
            PK_RET(__pk_vunpack_uint(pp, maxlen, &pv->u.u));
            // FALLTHROUGH
        case 'u':
            if (pv->havesize)
                s = pv->size;
            else if (pv->type == 'U')
                s = (size_t) pv->u.u;
            else
                s = maxlen;
            PK_SIZE_CHECK_UNPACK(s, maxlen);
            pv->u.item.data = *pp;
            pv->u.item.size = s;
            *pp += s;
            break;
        case 'b':
            // Translate to maintain ordering with the sign bit.
            PK_SIZE_CHECK_UNPACK(1, maxlen);
            pv->u.i = (int8_t) (*(*pp)++ -0x80);
            break;
        case 'B':
        case 't':
            PK_SIZE_CHECK_UNPACK(1, maxlen);
            pv->u.u = *(*pp)++;
            break;
        case 'h':
        case 'i':
        case 'l':
        case 'q':
            // Check that there is at least one byte available: the low-level routines treat zero length
            // as unchecked.
            PK_SIZE_CHECK_UNPACK(1, maxlen);
            PK_RET(__pk_vunpack_int(pp, maxlen, &pv->u.i));
            break;
        case 'H':
        case 'I':
        case 'L':
        case 'Q':
        case 'r':
            // Check that there is at least one byte available: the low-level routines treat zero length
            // as unchecked.
            PK_SIZE_CHECK_UNPACK(1, maxlen);
            PK_RET(__pk_vunpack_uint(pp, maxlen, &pv->u.u));
            break;
        case 'R':
            PK_SIZE_CHECK_UNPACK(sizeof (uint64_t), maxlen);
            pv->u.u = *(const uint64_t *) *pp;
            *pp += sizeof (uint64_t);
            break;
        case 'o': // add by james 20230525
            PK_SIZE_CHECK_UNPACK(sizeof (osv_oid_t), maxlen);
            pv->u.o = (osv_oid_t *) * pp;
            *pp += sizeof (osv_oid_t);
            break;
        case 'f': // add by james 20230525
            PK_SIZE_CHECK_UNPACK(sizeof (float), maxlen);
            pv->u.f = *(const float *) *pp;
            *pp += sizeof (float);
            break;
        case 'd': // add by james 20230525
            PK_SIZE_CHECK_UNPACK(sizeof (double), maxlen);
            pv->u.d = *(const double *) *pp;
            *pp += sizeof (double);
            break;
        default:
            PK_RET_MSG(EINVAL, "unknown pack-value type: %c", (int) pv->type);
    }

    return (0);
}

// add by james 20230607

static inline int __unpack_read_node(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
    size_t s;

    switch (pv->type) {
        case 'x':
            PK_SIZE_CHECK_UNPACK(pv->size, maxlen);
            pv->u.node.data = *pp;
            pv->u.node.size = pv->size;
            *pp += pv->size;
            break;
        case 's':
        case 'S':
            if (pv->type == 's' || pv->havesize) {
                s = pv->size;
                PK_ASSERT(s != 0);
            } else
                s = strlen((const char *) *pp) + 1;
            if (s > 0)
                pv->u.s = (const char *) *pp;
            PK_SIZE_CHECK_UNPACK(s, maxlen);
            pv->u.node.data = *pp;
            pv->u.node.size = s;
            *pp += s;
            break;
        case 'U':
            // Check that there is at least one byte available: the low-level routines treat zero length
            // as unchecked.
            PK_SIZE_CHECK_UNPACK(1, maxlen);
            pv->u.node.data = *pp;
            PK_RET(__pk_vunpack_uint_size(pp, maxlen, &pv->u.node.size));
            // FALLTHROUGH
        case 'u':
            if (pv->havesize)
                s = pv->size;
            else if (pv->type == 'U')
                s = (size_t) pv->u.u;
            else
                s = maxlen;
            PK_SIZE_CHECK_UNPACK(s, maxlen);
            pv->u.node.data = *pp;
            pv->u.node.size = s;
            *pp += s;
            break;
        case 'b':
            // Translate to maintain ordering with the sign bit.
            PK_SIZE_CHECK_UNPACK(1, maxlen);
            pv->u.node.data = *pp;
            pv->u.node.size = sizeof (int8_t);
            ++(*pp);
            break;
        case 'B':
        case 't':
            PK_SIZE_CHECK_UNPACK(1, maxlen);
            pv->u.node.data = *pp;
            pv->u.node.size = sizeof (uint8_t);
            ++(*pp);
            break;
        case 'h':
        case 'i':
        case 'l':
        case 'q':
            // Check that there is at least one byte available: the low-level routines treat zero length
            // as unchecked.
            PK_SIZE_CHECK_UNPACK(1, maxlen);
            pv->u.node.data = *pp;
            PK_RET(__pk_vunpack_int_size(pp, maxlen, &pv->u.node.size));
            break;
        case 'H':
        case 'I':
        case 'L':
        case 'Q':
        case 'r':
            // Check that there is at least one byte available: the low-level routines treat zero length
            // as unchecked.
            PK_SIZE_CHECK_UNPACK(1, maxlen);
            pv->u.node.data = *pp;
            PK_RET(__pk_vunpack_uint_size(pp, maxlen, &pv->u.node.size));
            break;
        case 'R':
            PK_SIZE_CHECK_UNPACK(sizeof (uint64_t), maxlen);
            pv->u.node.data = *pp;
            pv->u.node.size = sizeof (uint64_t);
            *pp += sizeof (uint64_t);
            break;
        case 'o': // add by james 20230525
            PK_SIZE_CHECK_UNPACK(sizeof (osv_oid_t), maxlen);
            pv->u.node.data = *pp;
            pv->u.node.size = sizeof (osv_oid_t);
            *pp += sizeof (osv_oid_t);
            break;
        case 'f': // add by james 20230525
            PK_SIZE_CHECK_UNPACK(sizeof (float), maxlen);
            pv->u.node.data = *pp;
            pv->u.node.size = sizeof (float);
            *pp += sizeof (float);
            break;
        case 'd': // add by james 20230525
            PK_SIZE_CHECK_UNPACK(sizeof (double), maxlen);
            pv->u.node.data = *pp;
            pv->u.node.size = sizeof (double);
            *pp += sizeof (double);
            break;
        default:
            PK_RET_MSG(EINVAL, "unknown pack-value type: %c", (int) pv->type);
    }

    return (0);
}

// add by james 20230607

static inline int __unpack_read_size(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
    size_t s;

    switch (pv->type) {
        case 'x':
            PK_SIZE_CHECK_UNPACK(pv->size, maxlen);
            pv->u.size = pv->size;
            *pp += pv->size;
            break;
        case 's':
        case 'S':
            if (pv->type == 's' || pv->havesize) {
                s = pv->size;
                PK_ASSERT(s != 0);
            } else
                s = strlen((const char *) *pp) + 1;
            if (s > 0)
                pv->u.s = (const char *) *pp;
            PK_SIZE_CHECK_UNPACK(s, maxlen);
            pv->u.size = s;
            *pp += s;
            break;
        case 'U':
            // Check that there is at least one byte available: the low-level routines treat zero length
            // as unchecked.
            PK_SIZE_CHECK_UNPACK(1, maxlen);
            PK_RET(__pk_vunpack_uint_size(pp, maxlen, &pv->u.size));
            // FALLTHROUGH
        case 'u':
            if (pv->havesize)
                s = pv->size;
            else if (pv->type == 'U')
                s = (size_t) pv->u.u;
            else
                s = maxlen;
            PK_SIZE_CHECK_UNPACK(s, maxlen);
            pv->u.size = s;
            *pp += s;
            break;
        case 'b':
            // Translate to maintain ordering with the sign bit.
            PK_SIZE_CHECK_UNPACK(1, maxlen);
            pv->u.size = sizeof (int8_t);
            ++(*pp);
            break;
        case 'B':
        case 't':
            PK_SIZE_CHECK_UNPACK(1, maxlen);
            pv->u.size = sizeof (uint8_t);
            ++(*pp);
            break;
        case 'h':
        case 'i':
        case 'l':
        case 'q':
            // Check that there is at least one byte available: the low-level routines treat zero length
            // as unchecked.
            PK_SIZE_CHECK_UNPACK(1, maxlen);
            PK_RET(__pk_vunpack_int_size(pp, maxlen, &pv->u.size));
            break;
        case 'H':
        case 'I':
        case 'L':
        case 'Q':
        case 'r':
            // Check that there is at least one byte available: the low-level routines treat zero length
            // as unchecked.
            PK_SIZE_CHECK_UNPACK(1, maxlen);
            PK_RET(__pk_vunpack_uint_size(pp, maxlen, &pv->u.size));
            break;
        case 'R':
            PK_SIZE_CHECK_UNPACK(sizeof (uint64_t), maxlen);
            pv->u.size = sizeof (uint64_t);
            *pp += sizeof (uint64_t);
            break;
        case 'o': // add by james 20230525
            PK_SIZE_CHECK_UNPACK(sizeof (osv_oid_t), maxlen);
            pv->u.size = sizeof (osv_oid_t);
            *pp += sizeof (osv_oid_t);
            break;
        case 'f': // add by james 20230525
            PK_SIZE_CHECK_UNPACK(sizeof (float), maxlen);
            pv->u.size = sizeof (float);
            *pp += sizeof (float);
            break;
        case 'd': // add by james 20230525
            PK_SIZE_CHECK_UNPACK(sizeof (double), maxlen);
            pv->u.size = sizeof (double);
            *pp += sizeof (double);
            break;
        default:
            PK_RET_MSG(EINVAL, "unknown pack-value type: %c", (int) pv->type);
    }

    return (0);
}

#define PK_UNPACK_PUT(pv, ap)                                      \
    do {                                                           \
        PK_ITEM *__item;                                           \
        switch ((pv).type) {                                       \
        case 'x':                                                  \
            break;                                                 \
        case 's':                                                  \
        case 'S':                                                  \
            *va_arg(ap, const char **) = (pv).u.s;                 \
            break;                                                 \
        case 'U':                                                  \
        case 'u':                                                  \
            __item = va_arg(ap, PK_ITEM *);                        \
            __item->data = (pv).u.item.data;                       \
            __item->size = (pv).u.item.size;                       \
            break;                                                 \
        case 'b':                                                  \
            *va_arg(ap, int8_t *) = (int8_t)(pv).u.i;              \
            break;                                                 \
        case 'h':                                                  \
            *va_arg(ap, int16_t *) = (short)(pv).u.i;              \
            break;                                                 \
        case 'i':                                                  \
        case 'l':                                                  \
            *va_arg(ap, int32_t *) = (int32_t)(pv).u.i;            \
            break;                                                 \
        case 'q':                                                  \
            *va_arg(ap, int64_t *) = (pv).u.i;                     \
            break;                                                 \
        case 'B':                                                  \
        case 't':                                                  \
            *va_arg(ap, uint8_t *) = (uint8_t)(pv).u.u;            \
            break;                                                 \
        case 'H':                                                  \
            *va_arg(ap, uint16_t *) = (uint16_t)(pv).u.u;          \
            break;                                                 \
        case 'I':                                                  \
        case 'L':                                                  \
            *va_arg(ap, uint32_t *) = (uint32_t)(pv).u.u;          \
            break;                                                 \
        case 'Q':                                                  \
        case 'r':                                                  \
        case 'R':                                                  \
            *va_arg(ap, uint64_t *) = (pv).u.u;                    \
            break;                                                 \
        case 'o': /* add by james 20230525 */                      \
            *va_arg(ap, osv_oid_t **) = (pv).u.o;                  \
            break;                                                 \
        case 'f': /* add by james 20230525 */                      \
            *va_arg(ap, float *) = (float)(pv).u.f;                \
            break;                                                 \
        case 'd': /* add by james 20230525 */                      \
            *va_arg(ap, double *) = (double)(pv).u.d;              \
            break;                                                 \
        default:                                                   \
            /* User format strings have already been validated. */ \
            /* return (__pk_illegal_value((pv).type));*/           \
            return -1;                                             \
        }                                                          \
    } while (0)

// __pk_struct_packv --
// Pack a byte string (va_list version).

static inline int __pk_struct_packv(void *buffer, size_t size, const char *fmt, va_list ap) {
    PK_DECL_PACK_VALUE(pv);
    PK_DECL_RET;
    PK_PACK pack;
    uint8_t *p, *end;

    p = (uint8_t *) buffer;
    end = p + size;

    if (fmt[1] == '\0' && fmt[0] != '\0') {
        pv.type = fmt[0];
        PK_PACK_GET(pv, ap);
        return (__pack_write(&pv, &p, size));
    }

    PK_RET(__pack_init(&pack, fmt));
    while ((ret = __pack_next(&pack, &pv)) == 0) {
        PK_PACK_GET(pv, ap);
        PK_RET(__pack_write(&pv, &p, (size_t) (end - p)));
    }
    PK_RET_NOTFOUND_OK(ret);

    // Be paranoid - __pack_write should never overflow.
    PK_ASSERT(p <= end);
    return (0);
}

/*
 static inline int __pk_struct_sizev(size_t *sizep, const char *fmt, va_list ap) {
    PK_DECL_PACK_VALUE(pv);
    PK_DECL_RET;
    PK_PACK pack;
    size_t v;

 *sizep = 0;

    if (fmt[1] == '\0' && fmt[0] != '\0') {
        pv.type = fmt[0];
        PK_PACK_GET(pv, ap);
        return (__pack_size(&pv, sizep));
    }

    PK_RET(__pack_init(&pack, fmt));
    while ((ret = __pack_next(&pack, &pv)) == 0) {
        PK_PACK_GET(pv, ap);
        PK_RET(__pack_size(&pv, &v));
 *sizep += v;
    }
    PK_RET_NOTFOUND_OK(ret);

    return (0);
}
 */

static inline int __pk_struct_packi(PK_ITEM *item, const char *fmt, va_list ap) {
    PK_DECL_PACK_VALUE(pv);
    PK_DECL_RET;
    PK_PACK pack;
    size_t v;
    uint8_t *p, *end;

    size_t size = item->size;
    item->size = 0;
    p = (uint8_t *) item->data;
    end = p + size;

    if (fmt[1] == '\0' && fmt[0] != '\0') {
        pv.type = fmt[0];
        PK_PACK_GET(pv, ap);
        PK_RET(__pack_size(&pv, &item->size));
        return (__pack_write(&pv, &p, size));
    }

    PK_RET(__pack_init(&pack, fmt));
    while ((ret = __pack_next(&pack, &pv)) == 0) {
        PK_PACK_GET(pv, ap);
        PK_RET(__pack_size(&pv, &v));
        item->size += v;
        PK_RET(__pack_write(&pv, &p, (size_t) (end - p)));
    }
    PK_RET_NOTFOUND_OK(ret);

    // Be paranoid - __pack_write should never overflow.
    PK_ASSERT(p <= end);
    return (0);
}

// __pk_struct_sizev --
// Calculate the size of a packed byte string (va_list version).

static inline int __pk_struct_sizev(size_t *sizep, const char *fmt, va_list ap) {
    PK_DECL_PACK_VALUE(pv);
    PK_DECL_RET;
    PK_PACK pack;
    size_t v;

    *sizep = 0;

    if (fmt[1] == '\0' && fmt[0] != '\0') {
        pv.type = fmt[0];
        PK_PACK_GET(pv, ap);
        return (__pack_size(&pv, sizep));
    }

    PK_RET(__pack_init(&pack, fmt));
    while ((ret = __pack_next(&pack, &pv)) == 0) {
        PK_PACK_GET(pv, ap);
        PK_RET(__pack_size(&pv, &v));
        *sizep += v;
    }
    PK_RET_NOTFOUND_OK(ret);

    return (0);
}

// __pk_struct_unpackv --
// Unpack a byte string (va_list version).

static inline int __pk_struct_unpackv(const void *buffer, size_t size, const char *fmt, va_list ap) {
    PK_DECL_PACK_VALUE(pv);
    PK_DECL_RET;
    PK_PACK pack;
    const uint8_t *p, *end;

    p = (uint8_t *) buffer;
    end = p + size;

    if (fmt[1] == '\0' && fmt[0] != '\0') {
        pv.type = fmt[0];
        PK_RET(__unpack_read(&pv, &p, size));
        PK_UNPACK_PUT(pv, ap);
        return (0);
    }

    PK_RET(__pack_init(&pack, fmt));
    while ((ret = __pack_next(&pack, &pv)) == 0) {
        PK_RET(__unpack_read(&pv, &p, (size_t) (end - p)));
        PK_UNPACK_PUT(pv, ap);
    }
    PK_RET_NOTFOUND_OK(ret);

    //　Be paranoid - __pack_write should never overflow.
    PK_ASSERT(p <= end);

    return (0);
}

/*　__pk_struct_size_adjust --
 *     Adjust the size field for a packed structure. Sometimes we want to include the size as a
 *     field in a packed structure. This is done by calling __pk_struct_size with the expected
 *     format and a size of zero. Then we want to pack the structure using the final size. This
 *     function adjusts the size appropriately (taking into account the size of the final size or
 *     the size field itself).　*/

static inline void __pk_struct_size_adjust(size_t *sizep) {
    size_t curr_size, field_size, prev_field_size;

    curr_size = *sizep;
    prev_field_size = 1;

    while ((field_size = __pk_vsize_uint(curr_size)) != prev_field_size) {
        curr_size += field_size - prev_field_size;
        prev_field_size = field_size;
    }

    // Make sure the field size we calculated matches the adjusted size.
    PK_ASSERT(field_size == __pk_vsize_uint(curr_size));

    *sizep = curr_size;
}
