
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

#include "pack_api.h"
#include "pack_stream.h"


// paki_pack_start -- Open a stream for packing.
// paki_stream_open -- Open a stream for unpacking.

int paki_stream_open(const char *format, const void *buffer, size_t size, PK_PACK_STREAM **psp) {
    PK_DECL_RET;
    PK_PACK_STREAM *ps;

    PK_RET(__pk_calloc_one(&ps));
    PK_ERR(__pack_init(&ps->pack, format));
    ps->start = buffer;
    ps->p = (void *) buffer;
    ps->end = ps->p + size;
    *psp = ps;

    if (0) {
err:
        (void) paki_stream_close(ps, NULL);
    }
    return (ret);
}

// paki_stream_close -- Close a packing stream.

int paki_stream_close(PK_PACK_STREAM *ps, size_t *usedp) {
    if (usedp != NULL) *usedp = PK_PTRDIFF(ps->p, ps->start);
    __pk_free(ps);
    return (0);
}

// paki_pack_item -- Pack an item.

int paki_pack_item(PK_PACK_STREAM *ps, PK_ITEM *item) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('u' == pv.type || 'U' == pv.type) {
        pv.u.item.data = item->data;
        pv.u.item.size = item->size;
        PK_RET(__pack_write_item(&pv, &ps->p, (size_t) (ps->end - ps->p)));
    } else return EINVAL;

    return (0);
}

// paki_pack_int -- Pack a signed integer.

int paki_pack_int(PK_PACK_STREAM *ps, int64_t i) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    switch (pv.type) {
        case 'b':
        case 'h':
        case 'i':
        case 'l':
        case 'q':
            pv.u.i = i;
            PK_RET(__pack_write(&pv, &ps->p, (size_t) (ps->end - ps->p)));
            break;
        default:
            return EINVAL;
    }

    return (0);
}

int paki_pack_obid(PK_PACK_STREAM *ps, osv_oid_t *o) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('o' == pv.type) {
        pv.u.o = o;
        PK_RET(__pack_write_obid(&pv, &ps->p, (size_t) (ps->end - ps->p)));
    } else return EINVAL;
    return (0);
}

// paki_pack_stri -- Pack a string.

int paki_pack_stri(PK_PACK_STREAM *ps, const char *s) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('s' == pv.type) {
        pv.u.s = s;
        PK_RET(__pack_write_stri(&pv, &ps->p, (size_t) (ps->end - ps->p)));
    } else return EINVAL;

    return (0);
}

int paki_pack_strz(PK_PACK_STREAM *ps, const char *s) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('S' == pv.type) {
        pv.u.s = s;
        PK_RET(__pack_write_strz(&pv, &ps->p, (size_t) (ps->end - ps->p)));
    } else return EINVAL;

    return (0);
}

// paki_pack_uint -- Pack an unsigned int.

int paki_pack_uint(PK_PACK_STREAM *ps, uint64_t u) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    switch (pv.type) {
        case 'B':
        case 'H':
        case 'I':
        case 'L':
        case 'Q':
        case 'R':
        case 'r':
        case 't':
            pv.u.u = u;
            PK_RET(__pack_write(&pv, &ps->p, (size_t) (ps->end - ps->p)));
            break;
        default:
            return EINVAL;
    }

    return (0);
}

// paki_unpack_item -- Unpack an item.

int paki_unpack_item(PK_PACK_STREAM *ps, PK_ITEM *item) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('u' == pv.type || 'U' == pv.type) {
        PK_RET(__unpack_read_item(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        item->data = pv.u.item.data;
        item->size = pv.u.item.size;
    } else return EINVAL;

    return (0);
}

int paki_unpack_ITEM(PK_PACK_STREAM *ps, PK_ITEM *item) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('u' == pv.type || 'U' == pv.type) {
        PK_RET(__unpack_read_ITEM(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        item->data = pv.u.item.data;
        item->size = pv.u.item.size;
    } else return EINVAL;

    return (0);
}

// paki_unpack_int -- Unpack a signed integer.

int paki_unpack_int(PK_PACK_STREAM *ps, int64_t *ip) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    switch (pv.type) {
        case 'b':
        case 'h':
        case 'i':
        case 'l':
        case 'q':
            PK_RET(__unpack_read(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
            *ip = pv.u.i;
            break;
        default:
            return EINVAL;
    }
    return (0);
}

int paki_unpack_obid(PK_PACK_STREAM *ps, osv_oid_t **opp) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('o' == pv.type) {
        PK_RET(__unpack_read_obid(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        *opp = pv.u.o;
    } else return EINVAL;
    return (0);
}

int paki_unpack_OBID(PK_PACK_STREAM *ps, osv_oid_t *op) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('o' == pv.type) {
        PK_RET(__unpack_read_obid(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        memcpy(op, pv.u.o, sizeof (osv_oid_t));
    } else return EINVAL;
    return (0);
}

// paki_unpack_stri -- Unpack a string.

int paki_unpack_stri(PK_PACK_STREAM *ps, const char **spp) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('s' == pv.type || 'S' == pv.type) {
        PK_RET(__unpack_read_stri(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        *spp = pv.u.s;
    } else return EINVAL;

    return (0);
}

int paki_unpack_STRI(PK_PACK_STREAM *ps, char *sp, size_t sl) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('s' == pv.type || 'S' == pv.type) {
        PK_RET(__unpack_read_STRI(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        memcpy(sp, pv.u.s, sl);
    } else return EINVAL;

    return (0);
}

int paki_unpack_STRZ(PK_PACK_STREAM *ps, char *sp) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('s' == pv.type || 'S' == pv.type) {
        PK_RET(__unpack_read_STRI(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        strcpy(sp, pv.u.s);
    } else return EINVAL;

    return (0);
}

// paki_unpack_uint -- Unpack an unsigned integer.

int paki_unpack_uint(PK_PACK_STREAM *ps, uint64_t *up) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    switch (pv.type) {
        case 'B':
        case 'H':
        case 'I':
        case 'L':
        case 'Q':
        case 'R':
        case 'r':
        case 't':
            PK_RET(__unpack_read(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
            *up = pv.u.u;
            break;
        default:
            return EINVAL;
    }
    return (0);
}

// extend by james 20230525

int paki_unpack_byte(PK_PACK_STREAM *ps, int8_t *ip) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('b' == pv.type) {
        PK_RET(__unpack_read_byte(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        *ip = pv.u.i;
    } else return EINVAL;
    return (0);
}
// extend by james 20230525

int paki_unpack_ubyte(PK_PACK_STREAM *ps, uint8_t *up) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('B' == pv.type || 't' == pv.type) {
        PK_RET(__unpack_read_ubyte(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        *up = pv.u.u;
    } else return EINVAL;
    return (0);
}
// extend by james 20230525

int paki_unpack_short(PK_PACK_STREAM *ps, int16_t *ip) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('h' == pv.type) {
        PK_RET(__unpack_read_short(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        *ip = pv.u.i;
    } else return EINVAL;
    return (0);
}
// extend by james 20230525

int paki_unpack_ushort(PK_PACK_STREAM *ps, uint16_t *up) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('H' == pv.type) {
        PK_RET(__unpack_read_ushort(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        *up = pv.u.u;
    } else return EINVAL;
    return (0);
}
// extend by james 20230525

int paki_unpack_int32(PK_PACK_STREAM *ps, int32_t *ip) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('i' == pv.type || 'l' == pv.type) {
        PK_RET(__unpack_read_int32(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        *ip = pv.u.i;
    } else return EINVAL;

    return (0);
}
// extend by james 20230525

int paki_unpack_uint32(PK_PACK_STREAM *ps, uint32_t *up) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('I' == pv.type || 'L' == pv.type) {
        PK_RET(__unpack_read_uint32(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        *up = pv.u.u;
    } else return EINVAL;

    return (0);
}
// extend by james 20230525

int paki_unpack_int64(PK_PACK_STREAM *ps, int64_t *ip) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('q' == pv.type) {
        PK_RET(__unpack_read_int64(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        *ip = pv.u.i;
    } else return EINVAL;
    return (0);
}
// extend by james 20230525

int paki_unpack_uint64(PK_PACK_STREAM *ps, uint64_t *up) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('Q' == pv.type || 'r' == pv.type) {
        PK_RET(__unpack_read_uint64(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        *up = pv.u.u;
    } else return EINVAL;

    return (0);
}

int paki_unpack_recod(PK_PACK_STREAM *ps, uint64_t *up) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('R' == pv.type) {
        PK_RET(__unpack_read_recod(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        *up = pv.u.u;
    } else return EINVAL;

    return (0);
}

// extend by james 20230525

int paki_unpack_float(PK_PACK_STREAM *ps, float *fp) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('f' == pv.type) {
        PK_RET(__unpack_read_float(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        *fp = pv.u.f;
    } else return EINVAL;
    return (0);
}
// extend by james 20230525

int paki_unpack_double(PK_PACK_STREAM *ps, double *dp) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('d' == pv.type) {
        PK_RET(__unpack_read_double(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        *dp = pv.u.d;
    } else return EINVAL;
    return (0);
}

//

void paki_stream_reset(PK_PACK_STREAM *ps, uint32_t reset) {
    if (RESET_STREAM_FORMAT & reset)
        __pack_reset(&ps->pack);

    if (RESET_STREAM_DATA & reset)
        ps->p = (void *) ps->start;
}

// extend by james 20230525

int paki_pack_byte(PK_PACK_STREAM *ps, int8_t i) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('b' == pv.type) {
        pv.u.i = i;
        PK_RET(__pack_write_byte(&pv, &ps->p, (size_t) (ps->end - ps->p)));
    } else return EINVAL;

    return (0);
}
// extend by james 20230525

int paki_pack_ubyte(PK_PACK_STREAM *ps, uint8_t u) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('B' == pv.type || 't' == pv.type) {
        pv.u.u = u;
        PK_RET(__pack_write_ubyte(&pv, &ps->p, (size_t) (ps->end - ps->p)));
    } else return EINVAL;

    return (0);
}
// extend by james 20230525

int paki_pack_short(PK_PACK_STREAM *ps, int16_t i) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('h' == pv.type) {
        pv.u.i = i;
        PK_RET(__pack_write_short(&pv, &ps->p, (size_t) (ps->end - ps->p)));
    } else return EINVAL;

    return (0);
}
// extend by james 20230525

int paki_pack_ushort(PK_PACK_STREAM *ps, uint16_t u) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('H' == pv.type) {
        pv.u.u = u;
        PK_RET(__pack_write_ushort(&pv, &ps->p, (size_t) (ps->end - ps->p)));
    } else return EINVAL;

    return (0);
}
// extend by james 20230525

int paki_pack_int32(PK_PACK_STREAM *ps, int32_t i) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('i' == pv.type || 'l' == pv.type) {
        pv.u.i = i;
        PK_RET(__pack_write_int32(&pv, &ps->p, (size_t) (ps->end - ps->p)));
    } else return EINVAL;

    return (0);
}
// extend by james 20230525

int paki_pack_uint32(PK_PACK_STREAM *ps, uint32_t u) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('I' == pv.type || 'L' == pv.type) {
        pv.u.u = u;
        PK_RET(__pack_write_uint32(&pv, &ps->p, (size_t) (ps->end - ps->p)));
    } else return EINVAL;

    return (0);
}
// extend by james 20230525

int paki_pack_int64(PK_PACK_STREAM *ps, int64_t i) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('q' == pv.type) {
        pv.u.i = i;
        PK_RET(__pack_write_int64(&pv, &ps->p, (size_t) (ps->end - ps->p)));
    } else return EINVAL;

    return (0);
}
// extend by james 20230525

int paki_pack_uint64(PK_PACK_STREAM *ps, uint64_t u) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('Q' == pv.type || 'r' == pv.type) {
        pv.u.u = u;
        PK_RET(__pack_write_uint64(&pv, &ps->p, (size_t) (ps->end - ps->p)));
    } else return EINVAL;

    return (0);
}

int paki_pack_recod(PK_PACK_STREAM *ps, uint64_t u) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('R' == pv.type) {
        pv.u.u = u;
        PK_RET(__pack_write_recod(&pv, &ps->p, (size_t) (ps->end - ps->p)));
    } else return EINVAL;

    return (0);
}

// extend by james 20230525

int paki_pack_float(PK_PACK_STREAM *ps, float f) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('f' == pv.type) {
        pv.u.f = f;
        PK_RET(__pack_write_float(&pv, &ps->p, (size_t) (ps->end - ps->p)));
    } else return EINVAL;

    return (0);
}
// extend by james 20230525

int paki_pack_double(PK_PACK_STREAM *ps, double d) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    if ('d' == pv.type) {
        pv.u.d = d;
        PK_RET(__pack_write_double(&pv, &ps->p, (size_t) (ps->end - ps->p)));
    } else return EINVAL;

    return (0);
}

size_t paki_stream_leng(PK_PACK_STREAM *ps) {
    return ps->p - ps->start;
}

// add by james 20230607

int paki_pack_node(PK_PACK_STREAM *ps, PK_NODE *node) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    pv.u.node.data = node->data;
    pv.u.node.size = node->size;
    PK_RET(__pack_write_node(&pv, &ps->p, (size_t) (ps->end - ps->p)));

    return (0);
}

// add by james 20230607

int paki_unpack_node(PK_PACK_STREAM *ps, PK_NODE *node) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__pack_next(&ps->pack, &pv));
    PK_RET(__unpack_read_node(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
    node->data = pv.u.node.data;
    node->size = pv.u.node.size;

    return (0);
}

//

int paki_unpack_entit(PK_PACK_STREAM *ps, osv_oid_t **opp, PK_ITEM *enti) {
    PK_DECL_PACK_VALUE(pv);

    // Lower-level packing routines treat a length of zero as unchecked.
    if (ps->p >= ps->end) return (ENOMEM);

    PK_RET(__unpack_read_obid(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
    *opp = pv.u.o;

    // Lower-level packing routines treat a length of zero as unchecked.
    enti->data = ps->p;
    enti->size = 0x00;
    while (!__pack_next(&ps->pack, &pv)) {
        if (ps->p >= ps->end) return (ENOMEM);
        PK_RET(__unpack_read_size(&pv, (const uint8_t **) &ps->p, (size_t) (ps->end - ps->p)));
        enti->size += pv.u.size;
    }
    //
    return (0);
}