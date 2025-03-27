
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <stddef.h>
#include <errno.h>
#include <stdint.h>
#include <assert.h>

//
#include "misc.h"
#include "pk_internal.h"
#include "config.h"
#include "cur_json.h"
#include "error.h"
#include "misc_inline.h"
#include "misc.h"
#include "ctype_inline.h"
#include "intpack_inline.h"
#include "packing_inline.h"

#include "pack_api.h"


// paki_struct_pack --
// Pack a byte string (extension API).

int paki_struct_pack(void *buffer, size_t len, const char *format, ...) {
    PK_DECL_RET;
    va_list ap;

    va_start(ap, format);
    ret = __pk_struct_packv(buffer, len, format, ap);
    va_end(ap);

    return (ret);
}

int paki_item_pack(PK_ITEM *item, const char *format, ...) {
    PK_DECL_RET;
    va_list ap;

    va_start(ap, format);
    ret = __pk_struct_packi(item, format, ap);
    va_end(ap);

    return (ret);
}

// paki_struct_size --
// Calculate the size of a packed byte string (extension API).

int paki_struct_size(size_t *lenp, const char *format, ...) {
    PK_DECL_RET;
    va_list ap;

    va_start(ap, format);
    ret = __pk_struct_sizev(lenp, format, ap);
    va_end(ap);

    return (ret);
}

// paki_struct_unpack --
// Unpack a byte string (extension API).

int paki_struct_unpack(const void *buffer, size_t len, const char *format, ...) {
    PK_DECL_RET;
    va_list ap;

    va_start(ap, format);
    ret = __pk_struct_unpackv(buffer, len, format, ap);
    va_end(ap);

    return (ret);
}

// __pk_ext_struct_pack --
// Pack a byte string (extension API).

int __pk_ext_struct_pack(void *buffer, size_t len, const char *fmt, ...) {
    PK_DECL_RET;
    va_list ap;

    va_start(ap, fmt);
    ret = __pk_struct_packv(buffer, len, fmt, ap);
    va_end(ap);

    return (ret);
}

// __pk_ext_struct_size --
// Calculate the size of a packed byte string (extension API).

int __pk_ext_struct_size(size_t *lenp, const char *fmt, ...) {
    PK_DECL_RET;
    va_list ap;

    va_start(ap, fmt);
    ret = __pk_struct_sizev(lenp, fmt, ap);
    va_end(ap);

    return (ret);
}

// __pk_ext_struct_unpack --
// Unpack a byte string (extension API).

int __pk_ext_struct_unpack(const void *buffer, size_t len, const char *fmt, ...) {
    PK_DECL_RET;
    va_list ap;

    va_start(ap, fmt);
    ret = __pk_struct_unpackv(buffer, len, fmt, ap);
    va_end(ap);

    return (ret);
}
