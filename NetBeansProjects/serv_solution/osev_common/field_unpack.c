#include <stdlib.h>
#include <string.h>

#include "utility/strz.h"
#include "third_party.h"
#include "field_unpack.h"

//

char *field_item_unpack(char *last_dat, PK_PACK_STREAM *pkps, char fmtok, uint64_t sleng) {
    PK_ITEM item_valu;
    const char *stri_valu;
    switch (fmtok) {
        case 'b':
            if (paki_unpack_byte(pkps, (int8_t *) last_dat))
                return NULL;
            last_dat += sizeof (int8_t);
            break;
        case 't':
        case 'B':
            if (paki_unpack_ubyte(pkps, (uint8_t *) last_dat))
                return NULL;
            last_dat += sizeof (uint8_t);
            break;
        case 'h':
            if (paki_unpack_short(pkps, (int16_t *) last_dat))
                return NULL;
            last_dat += sizeof (int16_t);
            break;
        case 'H':
            if (paki_unpack_ushort(pkps, (uint16_t *) last_dat))
                return NULL;
            last_dat += sizeof (uint16_t);
            break;
        case 'i':
        case 'l':
            if (paki_unpack_int32(pkps, (int32_t *) last_dat))
                return NULL;
            last_dat += sizeof (int32_t);
            break;
        case 'I':
        case 'L':
            if (paki_unpack_uint32(pkps, (uint32_t *) last_dat))
                return NULL;
            last_dat += sizeof (uint32_t);
            break;
        case 'q':
            if (paki_unpack_int64(pkps, (int64_t *) last_dat))
                return NULL;
            last_dat += sizeof (int64_t);
            break;
        case 'Q':
        case 'r':
            if (paki_unpack_uint64(pkps, (uint64_t *) last_dat))
                return NULL;
            last_dat += sizeof (uint64_t);
            break;
        case 'R':
            if (paki_unpack_recod(pkps, (uint64_t *) last_dat))
                return NULL;
            last_dat += sizeof (uint64_t);
            break;
        case 'f':
            if (paki_unpack_float(pkps, (float *) last_dat))
                return NULL;
            last_dat += sizeof (float);
            break;
        case 'd':
            if (paki_unpack_double(pkps, (double *) last_dat))
                return NULL;
            last_dat += sizeof (double);
            break;
        case 's':
            if (paki_unpack_stri(pkps, &stri_valu))
                return NULL;
            memcpy(last_dat, stri_valu, sleng);
            last_dat += sleng;
            break;
        case 'S':
            if (paki_unpack_strz(pkps, (const char **) &((strz_t *) last_dat)->data))
                return NULL;
            ((strz_t *) last_dat)->type = STRZ_TYPE_OSEV;
            ((strz_t *) last_dat)->slen = strlen(((strz_t *) last_dat)->data);
            last_dat += sizeof (strz_t);
            break;
        case 'u':
            if (paki_unpack_item(pkps, &item_valu))
                return NULL;
            memcpy(last_dat, item_valu.data, item_valu.size);
            last_dat += item_valu.size;
            break;
        default:
            _LOG_WARN("default: fmtok");
            break;
    }
    //
    return last_dat;
}

//

char *field_item_pack(PK_PACK_STREAM *pkps, char *last_dat, char fmtok, uint64_t sleng) {
    PK_ITEM item_valu;
    switch (fmtok) {
        case 'b':
            // paki_struct_unpack(item->data, item->size, "b", last_dat);
            if (paki_pack_byte(pkps, *(int8_t *) last_dat))
                return NULL;
            last_dat += sizeof (int8_t);
            break;
        case 't':
        case 'B':
            if (paki_pack_ubyte(pkps, *(uint8_t *) last_dat))
                return NULL;
            last_dat += sizeof (uint8_t);
            break;
        case 'h':
            if (paki_pack_short(pkps, *(int16_t *) last_dat))
                return NULL;
            last_dat += sizeof (int16_t);
            break;
        case 'H':
            if (paki_pack_ushort(pkps, *(uint16_t *) last_dat))
                return NULL;
            last_dat += sizeof (uint16_t);
            break;
        case 'i':
        case 'l':
            if (paki_pack_int32(pkps, *(int32_t *) last_dat))
                return NULL;
            last_dat += sizeof (int32_t);
            break;
        case 'I':
        case 'L':
            if (paki_pack_uint32(pkps, *(uint32_t *) last_dat))
                return NULL;
            last_dat += sizeof (uint32_t);
            break;
        case 'q':
            if (paki_pack_int64(pkps, *(int64_t *) last_dat))
                return NULL;
            last_dat += sizeof (int64_t);
            break;
        case 'Q':
        case 'r':
            if (paki_pack_uint64(pkps, *(uint64_t *) last_dat))
                return NULL;
            last_dat += sizeof (uint64_t);
            break;
        case 'R':
            if (paki_pack_recod(pkps, *(uint64_t *) last_dat))
                return NULL;
            last_dat += sizeof (uint64_t);
            break;
        case 'f':
            if (paki_pack_float(pkps, *(float *) last_dat))
                return NULL;
            last_dat += sizeof (float);
            break;
        case 'd':
            if (paki_pack_double(pkps, *(double *) last_dat))
                return NULL;
            last_dat += sizeof (double);
            break;
        case 's':
            if (paki_pack_stri(pkps, (char *) last_dat))
                return NULL;
            last_dat += sleng;
            break;
        case 'S':
            if (paki_pack_strz(pkps, ((strz_t *) last_dat)->data))
                return NULL;
            last_dat += sizeof (strz_t);
            break;
        case 'u':
            item_valu.data = last_dat;
            item_valu.size = sleng;
            if (paki_pack_item(pkps, &item_valu))
                return NULL;
            last_dat += sleng;
            break;
        default:
            _LOG_WARN("default: fmtok");
            break;
    }
    return last_dat;
}


