
/* 
 * File:   iunpak_pack.h
 * Author: james
 *
 * Created on 2023.9.22, AM 9:15
 */

#ifndef IUNPAK_PACK_H
#define IUNPAK_PACK_H

#ifdef __cplusplus
extern "C" {
#endif

    // __iunpak_read --
    // Read a packed value from a buffer.

    static inline int __iunpak_read_stri(char **pv, const uint8_t *ip, size_t maxlen) {
        size_t s;
        s = strlen((const char *) ip) + 1;
        if (s > 0)
            *pv = (char *) ip;
        PK_SIZE_CHECK_UNPACK(s, maxlen);
        //
        return (0);
    }

    static inline int __iunpak_read_obid(osv_oid_t **pv, const uint8_t *ip, size_t maxlen) {
        PK_SIZE_CHECK_UNPACK(sizeof (osv_oid_t), maxlen);
        *pv = (osv_oid_t *) ip;
        return (0);
    }

    static inline int __iunpak_read_byte(int8_t *pv, const uint8_t *ip, size_t maxlen) {
        // Translate to maintain ordering with the sign bit.
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        *pv = (int8_t) (*ip - 0x80);
        return (0);
    }

    static inline int __iunpak_read_ubyte(uint8_t *pv, const uint8_t *ip, size_t maxlen) {
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        *pv = *(ip);
        return (0);
    }

    static inline int __iunpak_read_short(int16_t *pv, const uint8_t *ip, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        PK_RET(__pk_iunpack_int(ip, maxlen, (int64_t *) pv));
        return (0);
    }

    static inline int __iunpak_read_ushort(uint16_t *pv, const uint8_t *ip, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        PK_RET(__pk_iunpack_uint(ip, maxlen, (uint64_t *) pv));
        return (0);
    }

    static inline int __iunpak_read_int32(int32_t *pv, const uint8_t *ip, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        PK_RET(__pk_iunpack_int(ip, maxlen, (int64_t *) pv));
        return (0);
    }

    static inline int __iunpak_read_uint32(uint32_t *pv, const uint8_t *ip, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        PK_RET(__pk_iunpack_uint(ip, maxlen, (uint64_t *) pv));
        return (0);
    }

    static inline int __iunpak_read_int64(int64_t *pv, const uint8_t *ip, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        PK_RET(__pk_iunpack_int(ip, maxlen, (int64_t *) pv));
        return (0);
    }

    static inline int __iunpak_read_uint64(uint64_t *pv, const uint8_t *ip, size_t maxlen) {
        // Check that there is at least one byte available: the low-level routines treat zero length
        // as unchecked.
        PK_SIZE_CHECK_UNPACK(1, maxlen);
        PK_RET(__pk_iunpack_uint(ip, maxlen, (uint64_t *) pv));
        return (0);
    }

    static inline int __iunpak_read_recod(uint64_t *pv, const uint8_t *ip, size_t maxlen) {
        PK_SIZE_CHECK_UNPACK(sizeof (uint64_t), maxlen);
        *pv = *(const uint64_t *) ip;
        return (0);
    }

    static inline int __iunpak_read_float(float *pv, const uint8_t *ip, size_t maxlen) {
        PK_SIZE_CHECK_UNPACK(sizeof (float), maxlen);
        *pv = *(const float *) ip;
        return (0);
    }

    static inline int __iunpak_read_double(double *pv, const uint8_t *ip, size_t maxlen) {
        PK_SIZE_CHECK_UNPACK(sizeof (double), maxlen);
        *pv = *(const double *) ip;
        return (0);
    }



#ifdef __cplusplus
}
#endif

#endif /* IUNPAK_PACK_H */

