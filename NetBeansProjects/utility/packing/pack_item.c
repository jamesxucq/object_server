
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <stddef.h>
#include <errno.h>
#include <stdint.h>
#include <assert.h>

//
#include "os_alloc.h"
#include "misc.h"
#include "pk_internal.h"
#include "config.h"
#include "cur_json.h"
#include "error.h"
#include "misc_inline.h"
#include "ctype_inline.h"
#include "intpack_inline.h"
#include "packing_inline.h"
#include "unpack_pack.h"
#include "iunpak_pack.h"

#include "pack_api.h"

//

int paki_iunpak_obid(PK_ITEM *item, osv_oid_t **op) {
    // Lower-level packing routines treat a length of zero as unchecked.
    if (0x00 >= item->size)
        return (ENOMEM);

    PK_RET(__iunpak_read_obid(op, (const uint8_t *) item->data, (size_t) item->size));
    // *op = pv.u.o;
    return (0);
}

// paki_unpack_stri -- Unpack a string.

int paki_iunpak_stri(PK_ITEM *item, const char **sp) {
    // Lower-level packing routines treat a length of zero as unchecked.
    if (0x00 >= item->size)
        return (ENOMEM);

    PK_RET(__iunpak_read_stri((char **) sp, (const uint8_t *) item->data, (size_t) item->size));
    // *sp = pv.u.s;
    return (0);
}

// extend by james 20230922

int paki_iunpak_byte(PK_ITEM *item, int8_t *ip) {
    // Lower-level packing routines treat a length of zero as unchecked.
    if (0x00 >= item->size)
        return (ENOMEM);

    PK_RET(__iunpak_read_byte(ip, (const uint8_t *) item->data, (size_t) item->size));
    // *ip = pv.u.i;
    return (0);
}
// extend by james 20230922

int paki_iunpak_ubyte(PK_ITEM *item, uint8_t *up) {
    // Lower-level packing routines treat a length of zero as unchecked.
    if (0x00 >= item->size)
        return (ENOMEM);

    PK_RET(__iunpak_read_ubyte(up, (const uint8_t *) item->data, (size_t) item->size));
    // *up = pv.u.u;
    return (0);
}
// extend by james 20230922

int paki_iunpak_short(PK_ITEM *item, int16_t *ip) {
    // Lower-level packing routines treat a length of zero as unchecked.
    if (0x00 >= item->size)
        return (ENOMEM);

    PK_RET(__iunpak_read_short(ip, (const uint8_t *) item->data, (size_t) item->size));
    // *ip = pv.u.i;
    return (0);
}
// extend by james 20230922

int paki_iunpak_ushort(PK_ITEM *item, uint16_t *up) {
    // Lower-level packing routines treat a length of zero as unchecked.
    if (0x00 >= item->size)
        return (ENOMEM);

    PK_RET(__iunpak_read_ushort(up, (const uint8_t *) item->data, (size_t) item->size));
    // *up = pv.u.u;
    return (0);
}
// extend by james 20230922

int paki_iunpak_int32(PK_ITEM *item, int32_t *ip) {
    // Lower-level packing routines treat a length of zero as unchecked.
    if (0x00 >= item->size)
        return (ENOMEM);

    PK_RET(__iunpak_read_int32(ip, (const uint8_t *) item->data, (size_t) item->size));
    // *ip = pv.u.i;
    return (0);
}
// extend by james 20230922

int paki_iunpak_uint32(PK_ITEM *item, uint32_t *up) {
    // Lower-level packing routines treat a length of zero as unchecked.
    if (0x00 >= item->size)
        return (ENOMEM);

    PK_RET(__iunpak_read_uint32(up, (const uint8_t *) item->data, (size_t) item->size));
    // *up = pv.u.u;
    return (0);
}
// extend by james 20230922

int paki_iunpak_int64(PK_ITEM *item, int64_t *ip) {
    // Lower-level packing routines treat a length of zero as unchecked.
    if (0x00 >= item->size)
        return (ENOMEM);

    PK_RET(__iunpak_read_int64(ip, (const uint8_t *) item->data, (size_t) item->size));
    // *ip = pv.u.i;
    return (0);
}
// extend by james 20230922

int paki_iunpak_uint64(PK_ITEM *item, uint64_t *up) {
    // Lower-level packing routines treat a length of zero as unchecked.
    if (0x00 >= item->size)
        return (ENOMEM);

    PK_RET(__iunpak_read_uint64(up, (const uint8_t *) item->data, (size_t) item->size));
    // *up = pv.u.u;
    return (0);
}

int paki_iunpak_recod(PK_ITEM *item, uint64_t *up) {
    // Lower-level packing routines treat a length of zero as unchecked.
    if (0x00 >= item->size)
        return (ENOMEM);

    PK_RET(__iunpak_read_recod(up, (const uint8_t *) item->data, (size_t) item->size));
    // *up = pv.u.u;
    return (0);
}

// extend by james 20230922

int paki_iunpak_float(PK_ITEM *item, float *fp) {
    // Lower-level packing routines treat a length of zero as unchecked.
    if (0x00 >= item->size)
        return (ENOMEM);

    PK_RET(__iunpak_read_float(fp, (const uint8_t *) item->data, (size_t) item->size));
    // *fp = pv.u.f;
    return (0);
}
// extend by james 20230922

int paki_iunpak_double(PK_ITEM *item, double *dp) {
    // Lower-level packing routines treat a length of zero as unchecked.
    if (0x00 >= item->size)
        return (ENOMEM);

    PK_RET(__iunpak_read_double(dp, (const uint8_t *) item->data, (size_t) item->size));
    // *dp = pv.u.d;
    return (0);
}

