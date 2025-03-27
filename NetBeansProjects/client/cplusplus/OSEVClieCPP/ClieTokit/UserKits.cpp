
#include <stdarg.h>

#include "third_party.h"

#include "osev_common/obid.h"
#include "UserKits.h"

//

#define PARAM_TYPE(FMTOK, SLENG, FMTST) { \
    char *endsize; \
    if (isdigit(FMTST[0x00])) { \
        SLENG = strtoul(FMTST, &endsize, 10); \
        FMTST = endsize; \
    } \
    FMTOK = FMTST[0x00]; \
    ++FMTST; \
}

// sFmtstr = "oiii"

int UserKits::LoopDeseri(PK_PACK_STREAM *pkps, char *sFmtstr, ...) {
    char fmtok;
    uint64 sleng;
    int upakValu;
    void *deseValu;
    //
    paki_stream_reset(pkps, RESET_STREAM_FORMAT);
    va_list ap;
    va_start(ap, sFmtstr);
    //
    PARAM_TYPE(fmtok, sleng, sFmtstr)
    while ('\0' != fmtok) {
        // CLIEPF("sleng:%llu fmtok:|%c|\n", sleng, fmtok);
        deseValu = va_arg(ap, void *);
        switch (fmtok) {
            case 'b':
                upakValu = paki_unpack_byte(pkps, (int8_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'B':
            case 't':
                upakValu = paki_unpack_ubyte(pkps, (uint8_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'h':
                upakValu = paki_unpack_short(pkps, (int16_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'H':
                upakValu = paki_unpack_ushort(pkps, (uint16_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'i':
            case 'l':
                upakValu = paki_unpack_int32(pkps, (int32_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'I':
            case 'L':
                upakValu = paki_unpack_uint32(pkps, (uint32_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'q':
                upakValu = paki_unpack_int64(pkps, (int64_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'Q':
            case 'R':
                upakValu = paki_unpack_uint64(pkps, (uint64_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'o':
                upakValu = paki_unpack_OBID(pkps, (osv_oid_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'f':
                upakValu = paki_unpack_float(pkps, (float *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'd':
                upakValu = paki_unpack_double(pkps, (double *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 's':
                upakValu = paki_unpack_STRI(pkps, (char *) deseValu, sleng);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'S':
                upakValu = paki_unpack_STRZ(pkps, (char *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            default:
                break;
        }
        PARAM_TYPE(fmtok, sleng, sFmtstr)
    }
    //
    va_end(ap);
    //
    return 0x00;
}
