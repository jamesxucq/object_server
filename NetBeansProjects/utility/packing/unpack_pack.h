
/* 
 * File:   unpack_pack.h
 * Author: james
 *
 * Created on 2023.6.9, AM 9:17
 */

#ifndef UNPACK_PACK_H
#define UNPACK_PACK_H

#ifdef __cplusplus
extern "C" {
#endif

    // __pack_write --
    // Pack a value into a buffer.

    static inline int __pack_write_item(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
        size_t s, pad;
        uint8_t *oldp;
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
        return (0);
    }

    static inline int __pack_write_stri(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
        PK_SIZE_CHECK_PACK(pv->size, maxlen);
        memcpy(*pp, pv->u.s, pv->size);
        *pp += pv->size;
        return (0);
    }

    static inline int __pack_write_strz(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
        size_t s, pad;
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
        return (0);
    }

    static inline int __pack_write_obid(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
        PK_SIZE_CHECK_PACK(sizeof (osv_oid_t), maxlen);
        memcpy(*pp, pv->u.o, sizeof (osv_oid_t));
        *pp += sizeof (osv_oid_t);
        return (0);
    }

    static inline int __pack_write_byte(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
        // Translate to maintain ordering with the sign bit.
        PK_SIZE_CHECK_PACK(1, maxlen);
        **pp = (uint8_t) (pv->u.i + 0x80);
        *pp += 1;
        return (0);
    }

    static inline int __pack_write_ubyte(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
        PK_SIZE_CHECK_PACK(1, maxlen);
        **pp = (uint8_t) pv->u.u;
        *pp += 1;
        return (0);
    }

    static inline int __pack_write_short(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_PACK(1, maxlen);
        PK_RET(__pk_vpack_int(pp, maxlen, pv->u.i));
        return (0);
    }

    static inline int __pack_write_ushort(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_PACK(1, maxlen);
        PK_RET(__pk_vpack_uint(pp, maxlen, pv->u.u));
        return (0);
    }

    static inline int __pack_write_int32(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_PACK(1, maxlen);
        PK_RET(__pk_vpack_int(pp, maxlen, pv->u.i));
        return (0);
    }

    static inline int __pack_write_uint32(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_PACK(1, maxlen);
        PK_RET(__pk_vpack_uint(pp, maxlen, pv->u.u));
        return (0);
    }

    static inline int __pack_write_int64(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_PACK(1, maxlen);
        PK_RET(__pk_vpack_int(pp, maxlen, pv->u.i));
        return (0);
    }

    static inline int __pack_write_uint64(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_PACK(1, maxlen);
        PK_RET(__pk_vpack_uint(pp, maxlen, pv->u.u));
        return (0);
    }

    static inline int __pack_write_recod(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
        PK_SIZE_CHECK_PACK(sizeof (uint64_t), maxlen);
        *(uint64_t *) *pp = pv->u.u;
        *pp += sizeof (uint64_t);
        return (0);
    }

    static inline int __pack_write_float(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
        PK_SIZE_CHECK_PACK(sizeof (float), maxlen);
        *(float *) *pp = pv->u.f;
        *pp += sizeof (float);
        return (0);
    }

    static inline int __pack_write_double(PK_PACK_VALUE *pv, uint8_t **pp, size_t maxlen) {
        PK_SIZE_CHECK_PACK(sizeof (double), maxlen);
        *(double *) *pp = pv->u.d;
        *pp += sizeof (double);
        return (0);
    }

    // __unpack_read --
    // Read a packed value from a buffer.

    static inline int __unpack_read_item(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
        size_t s;
        if (pv->havesize)
            s = pv->size;
        else s = maxlen;
        PK_SIZE_CHECK_UNPACK(s, maxlen);
        pv->u.item.data = *pp;
        pv->u.item.size = s;
        *pp += s;
        return (0);
    }

    static inline int __unpack_read_ITEM(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
        size_t s;
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        PK_RET(__pk_vunpack_uint(pp, maxlen, &pv->u.u));
        // FALLTHROUGH
        if (pv->havesize)
            s = pv->size;
        else if (pv->type == 'U')
            s = (size_t) pv->u.u;
        else s = maxlen;
        PK_SIZE_CHECK_UNPACK(s, maxlen);
        pv->u.item.data = *pp;
        pv->u.item.size = s;
        *pp += s;
        return (0);
    }

    static inline int __unpack_read_stri(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
        size_t s;
        if (pv->type == 's' || pv->havesize) {
            s = pv->size;
            PK_ASSERT(s != 0);
        } else
            s = strlen((const char *) *pp) + 1;
        if (s > 0)
            pv->u.s = (const char *) *pp;
        PK_SIZE_CHECK_UNPACK(s, maxlen);
        *pp += s;
        return (0);
    }

    static inline int __unpack_read_STRI(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
        if (pv->type == 's' || pv->havesize) {
            pv->rsl = pv->size;
            PK_ASSERT(pv->rsl != 0);
        } else
            pv->rsl = strlen((const char *) *pp) + 1;
        if (pv->rsl > 0)
            pv->u.s = (const char *) *pp;
        PK_SIZE_CHECK_UNPACK(pv->rsl, maxlen);
        *pp += pv->rsl;
        return (0);
    }

    static inline int __unpack_read_obid(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
        PK_SIZE_CHECK_UNPACK(sizeof (osv_oid_t), maxlen);
        pv->u.o = (osv_oid_t *) * pp;
        *pp += sizeof (osv_oid_t);
        return (0);
    }

    static inline int __unpack_read_byte(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
        // Translate to maintain ordering with the sign bit.
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        pv->u.i = (int8_t) (*(*pp)++ -0x80);
        return (0);
    }

    static inline int __unpack_read_ubyte(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        pv->u.u = *(*pp)++;
        return (0);
    }

    static inline int __unpack_read_short(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        PK_RET(__pk_vunpack_int(pp, maxlen, &pv->u.i));
        return (0);
    }

    static inline int __unpack_read_ushort(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        PK_RET(__pk_vunpack_uint(pp, maxlen, &pv->u.u));
        return (0);
    }

    static inline int __unpack_read_int32(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        PK_RET(__pk_vunpack_int(pp, maxlen, &pv->u.i));
        return (0);
    }

    static inline int __unpack_read_uint32(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        PK_RET(__pk_vunpack_uint(pp, maxlen, &pv->u.u));
        return (0);
    }

    static inline int __unpack_read_int64(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        PK_RET(__pk_vunpack_int(pp, maxlen, &pv->u.i));
        return (0);
    }

    static inline int __unpack_read_uint64(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        PK_RET(__pk_vunpack_uint(pp, maxlen, &pv->u.u));

        return (0);
    }

    static inline int __unpack_read_recod(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
        PK_SIZE_CHECK_UNPACK(sizeof (uint64_t), maxlen);
        pv->u.u = *(const uint64_t *) *pp;
        *pp += sizeof (uint64_t);
        return (0);
    }

    static inline int __unpack_read_float(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
        PK_SIZE_CHECK_UNPACK(sizeof (float), maxlen);
        pv->u.f = *(const float *) *pp;
        *pp += sizeof (float);
        return (0);
    }

    static inline int __unpack_read_double(PK_PACK_VALUE *pv, const uint8_t **pp, size_t maxlen) {
        PK_SIZE_CHECK_UNPACK(sizeof (double), maxlen);
        pv->u.d = *(const double *) *pp;
        *pp += sizeof (double);
        return (0);
    }

#ifdef __cplusplus
}
#endif

#endif /* UNPACK_PACK_H */

