
/* 
 * File:   packing.h
 * Author: James Xu
 *
 * Created on 2022.10.7, AM 10:17
 */

#ifndef PACKING_H
#define PACKING_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OSEV_OBID_T
#define OSEV_OBID_T

#pragma pack(1)

    struct _osv_oid_t_ {
        unsigned int osev_unique; // machine_unique
        unsigned int time_stamp;
        unsigned int counter;
    };
#pragma pack()

    typedef struct _osv_oid_t_ osv_oid_t;

#endif  /* OSEV_OBID_T */

    //
#include <wiredtiger.h>
    typedef struct __wt_item PK_ITEM;

    //

    struct _pk_node_ {
        const void *data;
        size_t size;
    };

    typedef struct _pk_node_ PK_NODE;

    //
    typedef struct __pk_pack_stream PK_PACK_STREAM;

    // struct
    int paki_struct_pack(void *buffer, size_t len, const char *format, ...);
    int paki_struct_size(size_t *lenp, const char *format, ...);
    int paki_struct_unpack(const void *buffer, size_t len, const char *format, ...);
    int paki_item_pack(PK_ITEM *item, const char *format, ...);

    //
#define PACKING_KEY_PACK(BUFFE, KEY_POIN) (((unsigned long long *)(KEY_POIN))[0x00] = (BUFFE))
#define PACKING_KEY_UNPACK(BUFFE, KEY_POIN) ((BUFFE) = ((unsigned long long *)(KEY_POIN))[0x00])

    // stream
    int paki_stream_open(const char *format, const void *buffer, size_t size, PK_PACK_STREAM **psp);
    int paki_stream_close(PK_PACK_STREAM *ps, size_t *usedp);
    // add by james 20230607
    size_t paki_stream_leng(PK_PACK_STREAM *ps);
    // extend by james 20230529
#define RESET_STREAM_FORMAT 0x0001
#define RESET_STREAM_DATA   0x0002
    void paki_stream_reset(PK_PACK_STREAM *ps, uint32_t reset);

    // pack
    int paki_pack_item(PK_PACK_STREAM *ps, PK_ITEM *item);
#define paki_pack_ITEM(PS, ITEM) paki_pack_item(PS, ITEM);
    int paki_pack_int(PK_PACK_STREAM *ps, int64_t i);
    int paki_pack_stri(PK_PACK_STREAM *ps, const char *s);
    int paki_pack_strz(PK_PACK_STREAM *ps, const char *s);
    int paki_pack_uint(PK_PACK_STREAM *ps, uint64_t u);
    // extend by james 20230525
    int paki_pack_byte(PK_PACK_STREAM *ps, int8_t i);
    int paki_pack_ubyte(PK_PACK_STREAM *ps, uint8_t u);
    int paki_pack_short(PK_PACK_STREAM *ps, int16_t i);
    int paki_pack_ushort(PK_PACK_STREAM *ps, uint16_t u);
    int paki_pack_int32(PK_PACK_STREAM *ps, int32_t i);
    int paki_pack_uint32(PK_PACK_STREAM *ps, uint32_t u);
    int paki_pack_int64(PK_PACK_STREAM *ps, int64_t i);
    int paki_pack_uint64(PK_PACK_STREAM *ps, uint64_t u);
    int paki_pack_float(PK_PACK_STREAM *ps, float f);
    int paki_pack_double(PK_PACK_STREAM *ps, double d);
    int paki_pack_recod(PK_PACK_STREAM *ps, uint64_t u);
    int paki_pack_obid(PK_PACK_STREAM *ps, osv_oid_t *o);
    // add by james 20230607
    int paki_pack_node(PK_PACK_STREAM *ps, PK_NODE *node);

    // unpack
    int paki_unpack_item(PK_PACK_STREAM *ps, PK_ITEM *item);
    int paki_unpack_ITEM(PK_PACK_STREAM *ps, PK_ITEM *item);
    int paki_unpack_int(PK_PACK_STREAM *ps, int64_t *ip);
    int paki_unpack_stri(PK_PACK_STREAM *ps, const char **spp);
    int paki_unpack_STRI(PK_PACK_STREAM *ps, char *sp, size_t sl); // deep copy
#define paki_unpack_strz(PS, SP) paki_unpack_stri(PS, SP)
    int paki_unpack_STRZ(PK_PACK_STREAM *ps, char *sp); // deep copy
    int paki_unpack_uint(PK_PACK_STREAM *ps, uint64_t *up);

    // extend by james 20230525
    int paki_unpack_byte(PK_PACK_STREAM *ps, int8_t *ip);
    int paki_unpack_ubyte(PK_PACK_STREAM *ps, uint8_t *up);
    int paki_unpack_short(PK_PACK_STREAM *ps, int16_t *ip);
    int paki_unpack_ushort(PK_PACK_STREAM *ps, uint16_t *up);
    int paki_unpack_int32(PK_PACK_STREAM *ps, int32_t *ip);
    int paki_unpack_uint32(PK_PACK_STREAM *ps, uint32_t *up);
    int paki_unpack_int64(PK_PACK_STREAM *ps, int64_t *ip);
    int paki_unpack_uint64(PK_PACK_STREAM *ps, uint64_t *up);
    int paki_unpack_float(PK_PACK_STREAM *ps, float *fp);
    int paki_unpack_double(PK_PACK_STREAM *ps, double *dp);
    int paki_unpack_obid(PK_PACK_STREAM *ps, osv_oid_t **opp);
    int paki_unpack_OBID(PK_PACK_STREAM *ps, osv_oid_t *op); // deep copy
    int paki_unpack_recod(PK_PACK_STREAM *ps, uint64_t *up);
    // add by james 20230607
    int paki_unpack_node(PK_PACK_STREAM *ps, PK_NODE *node);
    int paki_unpack_entit(PK_PACK_STREAM *ps, osv_oid_t **opp, PK_ITEM *enti);

    // add by james 20230921
    int paki_iunpak_stri(PK_ITEM *item, const char **sp);
#define paki_iunpak_strz(PS, SP) paki_iunpak_stri(PS, SP)
    int paki_iunpak_byte(PK_ITEM *item, int8_t *ip);
    int paki_iunpak_ubyte(PK_ITEM *item, uint8_t *up);
    int paki_iunpak_short(PK_ITEM *item, int16_t *ip);
    int paki_iunpak_ushort(PK_ITEM *item, uint16_t *up);
    int paki_iunpak_int32(PK_ITEM *item, int32_t *ip);
    int paki_iunpak_uint32(PK_ITEM *item, uint32_t *up);
    int paki_iunpak_int64(PK_ITEM *item, int64_t *ip);
    int paki_iunpak_uint64(PK_ITEM *item, uint64_t *up);
    int paki_iunpak_float(PK_ITEM *item, float *fp);
    int paki_iunpak_double(PK_ITEM *item, double *dp);
    int paki_iunpak_obid(PK_ITEM *item, osv_oid_t **op);
    int paki_iunpak_recod(PK_ITEM *item, uint64_t *up);

#ifdef __cplusplus
}
#endif

#endif /* PACKING_H */

