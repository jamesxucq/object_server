#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parms_style.h"

#include "packa_entit.h"
#include "debug_funct_osv.h"

//

static inline int check_packa_fmtst(char *fmtst, const char **pamvp) {
    char *endsize;
#ifdef _DEBUG
    uint64 sleng = 0x00;
#else /* _DEBUG */
    uint64 sleng;
#endif /* _DEBUG */
    unsigned long long colen;
    for (; pamvp[0x00] || fmtst[0x00]; ++pamvp, ++fmtst) {
        if (isdigit(fmtst[0x00])) {
            sleng = strtoul(fmtst, &endsize, 10);
            fmtst = endsize;
        }
        switch (check_pamvu_nodtyp((char *) pamvp[0x00])) {
            case DATY_INVAL:
                _LOG_WARN("case: DATY_INVAL");
                return -1;
                break;
            case DATY_BYTE:
                if ('b' != fmtst[0x00])
                    return -1;
                break;
            case DATY_UBYTE:
                if ('B' != fmtst[0x00])
                    return -1;
                break;
            case DATY_SHORT:
                if ('h' != fmtst[0x00])
                    return -1;
                break;
            case DATY_USHORT:
                if ('H' != fmtst[0x00])
                    return -1;
                break;
            case DATY_INT:
                if ('i' != fmtst[0x00])
                    return -1;
                break;
            case DATY_UINT:
                if ('I' != fmtst[0x00])
                    return -1;
                break;
            case DATY_LLONG:
                if ('q' != fmtst[0x00])
                    return -1;
                break;
            case DATY_ULLONG:
                if ('Q' != fmtst[0x00])
                    return -1;
                break;
            case DATY_OBID:
                if ('o' != fmtst[0x00])
                    return -1;
                break;
            case DATY_FLOAT:
                if ('f' != fmtst[0x00])
                    return -1;
                break;
            case DATY_DOUBLE:
                if ('d' != fmtst[0x00])
                    return -1;
                break;
            case DATY_STRI:
                quote_decode((char *) pamvp[0x00]);
                colen = strlen(pamvp[0x00]);
                if ((sleng < colen) || ('s' != fmtst[0x00]))
                    return -1;
                break;
            case DATY_STRZ:
                quote_decode((char *) pamvp[0x00]);
                if ('S' != fmtst[0x00])
                    return -1;
                break;
            case DATY_BINARY:
                colen = ((unsigned long long*) (pamvp[0x00] + ESCA_ENCOLEN_PART))[0x00];
                if ((sleng < colen) || ('s' != fmtst[0x00]))
                    return -1;
                break;
            default:
                _LOG_WARN("default: stri_valu");
                return -1;
                break;
        }
        // OSEVPF("lenval:%d\n", lenval);
    }
    //
    return 0x00;
}

//

static inline int field_pamvu_pack(PK_PACK_STREAM *pkps, const char *pamvu, char fmtok, uint64 sleng) {
    PK_ITEM item_valu;
    switch (fmtok) {
        case 'b':
            // paki_struct_unpack(item->data, item->size, "b", pamvu);
            if (paki_pack_byte(pkps, (char) atoi(pamvu)))
                return -1;
            break;
        case 't':
        case 'B':
            if (paki_pack_ubyte(pkps, (unsigned char) atoi(pamvu)))
                return -1;
            break;
        case 'h':
            if (paki_pack_short(pkps, (short) atoi(pamvu)))
                return -1;
            break;
        case 'H':
            if (paki_pack_ushort(pkps, (unsigned short) atoi(pamvu)))
                return -1;
            break;
        case 'i':
        case 'l':
            printf("*(int32_t *) pamvu:|%d|\n", *(int32_t *) pamvu);
            if (paki_pack_int32(pkps, (int) atoi(pamvu)))
                return -1;
            break;
        case 'I':
        case 'L':
            if (paki_pack_uint32(pkps, (unsigned int) atoi(pamvu)))
                return -1;
            break;
        case 'q':
            if (paki_pack_int64(pkps, (long long) atoll(pamvu)))
                return -1;
            break;
        case 'Q':
        case 'r':
            if (paki_pack_uint64(pkps, (unsigned long long) atoll(pamvu)))
                return -1;
            break;
        case 'R':
            if (paki_pack_recod(pkps, (unsigned long long) atoll(pamvu)))
                return -1;
            break;
        case 'o':
            if (paki_pack_obid(pkps, (osv_oid_t *) (pamvu + ESCA_OBIDCON_PART)))
                return -1;
            break;
        case 'f':
            if (paki_pack_float(pkps, strtof(pamvu, NULL)))
                return -1;
            break;
        case 'd':
            if (paki_pack_double(pkps, atof(pamvu)))
                return -1;
            break;
        case 's':
            // quote_decode((char *) pamvu);
            if (paki_pack_stri(pkps, (char *) pamvu))
                return -1;
            break;
        case 'S':
            // quote_decode((char *) pamvu);
            if (paki_pack_strz(pkps, (char *) pamvu))
                return -1;
            break;
        case 'u':
            item_valu.data = pamvu;
            item_valu.size = sleng;
            if (paki_pack_item(pkps, &item_valu))
                return -1;
            break;
        default:
            _LOG_WARN("default: fmtok");
            return -1;
            break;
    }
    return 0x00;
}

//

unsigned long long pack_list_loop(char *pscon, unsigned long long colen, const char **pamvp, char *fmtst) {
    OSEVPF("[FUNC]:pack_list_loop\n");
    if (check_packa_fmtst(fmtst, pamvp))
        return INVA_ULOLO_VALU;
    OSEVPF("fmtst:|%s|\n", fmtst);
    //
    PK_PACK_STREAM *pkps;
    if (paki_stream_open(fmtst, pscon, colen, &pkps))
        return INVA_ULOLO_VALU;
    //
    char *endsize;
#ifdef _DEBUG
    uint64 sleng = 0x00;
#else /* _DEBUG */
    uint64 sleng;
#endif /* _DEBUG */
    for (; pamvp[0x00] && fmtst[0x00]; ++pamvp, ++fmtst) {
        if (isdigit(fmtst[0x00])) {
            sleng = strtoul(fmtst, &endsize, 10);
            fmtst = endsize;
        }
        // OSEVPF("fmtst:|%c| sleng:|%llu|\n", fmtst[0x00], sleng);
        if (field_pamvu_pack(pkps, pamvp[0x00], fmtst[0x00], sleng)) {
            paki_stream_close(pkps, NULL);
            return INVA_ULOLO_VALU;
        }
    }
    //
    unsigned long long lenval = paki_stream_leng(pkps);
    paki_stream_close(pkps, NULL);
    return lenval;
}
