#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>
#include "parms_style.h"
#include "debug_funct_osv.h"


// RRR

/*
Format    C Type    Java type    Python type    Notes
x         N/A       N/A          N/A            pad byte, no associated value
b         int8_t    byte         int            signed byte
B         uint8_t   byte         int            unsigned byte
h         int16_t   short        int            signed 16-bit
H         uint16_t  short        int            unsigned 16-bit
i         int32_t   int          int            signed 32-bit
I         uint32_t  int          int            unsigned 32-bit
l         int32_t   int          int            signed 32-bit
L         uint32_t  int          int            unsigned 32-bit
q         int64_t   long         int            signed 64-bit
Q         uint64_t  long         int            unsigned 64-bit
r         uint64_t  long         int            record number
s         char[]    String       str            fixed-length string
S         char[]    String       str            NUL-terminated string
t         uint8_t   byte         int            fixed-length bit field
u         WT_ITEM * byte[]       str            raw byte array
// extend float / double
f         float       
d         double  
 */

// ("aa", 11, "bb", "cc", 33, 55);

unsigned long long encod_list_loop(char *pscon, const char **pamvp) {
    OSEVPF("[FUNC]:encod_list_loop\n");
    unsigned long long binlen;
    unsigned long long lenval = 0x00;
    for (; pamvp[0x00]; ++pamvp) {
        switch (check_pamvu_nodtyp((char *) pamvp[0x00])) {
            case DATY_INVAL:
                _LOG_WARN("case: DATY_INVAL");
                lenval = INVA_ULOLO_VALU;
                break;
            case DATY_BYTE:
                OSEVPF("DATY_BYTE:|%s|\n", pamvp[0x00]);
                BYTE_PAMSTYL(pscon, pamvp[0x00])
                lenval += sizeof (byte_entit);
                break;
            case DATY_UBYTE:
                OSEVPF("DATY_UBYTE:|%s|\n", pamvp[0x00]);
                UBYTE_PAMSTYL(pscon, pamvp[0x00])
                lenval += sizeof (ubyte_entit);
                break;
            case DATY_SHORT:
                OSEVPF("DATY_SHORT:|%s|\n", pamvp[0x00]);
                SHORT_PAMSTYL(pscon, pamvp[0x00])
                lenval += sizeof (short_entit);
                break;
            case DATY_USHORT:
                OSEVPF("DATY_USHORT:|%s|\n", pamvp[0x00]);
                USHORT_PAMSTYL(pscon, pamvp[0x00])
                lenval += sizeof (ushort_entit);
                break;
            case DATY_INT:
                OSEVPF("DATY_INT:|%s|\n", pamvp[0x00]);
                INT_PAMSTYL(pscon, pamvp[0x00])
                lenval += sizeof (int_entit);
                break;
            case DATY_UINT:
                OSEVPF("DATY_UINT:|%s|\n", pamvp[0x00]);
                UINT_PAMSTYL(pscon, pamvp[0x00])
                lenval += sizeof (uint_entit);
                break;
            case DATY_LLONG:
                OSEVPF("DATY_LONG:|%s|\n", pamvp[0x00]);
                LLONG_PAMSTYL(pscon, pamvp[0x00])
                lenval += sizeof (llong_entit);
                break;
            case DATY_ULLONG:
                OSEVPF("DATY_ULONG:|%s|\n", pamvp[0x00]);
                ULLONG_PAMSTYL(pscon, pamvp[0x00])
                lenval += sizeof (ullong_entit);
                break;
            case DATY_OBID:
                OSEVPF("DATY_OBID\n");
                OBID_PAMSTYL(pscon, (pamvp[0x00] + ESCA_OBIDCON_PART))
                lenval += sizeof (obid_entit);
                break;
            case DATY_FLOAT:
                OSEVPF("DATY_FLOAT:|%s|\n", pamvp[0x00]);
                FLOAT_PAMSTYL(pscon, pamvp[0x00])
                lenval += sizeof (float_entit);
                break;
            case DATY_DOUBLE:
                OSEVPF("DATY_DOUBLE:|%s|\n", pamvp[0x00]);
                DOUBLE_PAMSTYL(pscon, pamvp[0x00])
                lenval += sizeof (double_entit);
                break;
            case DATY_STRI:
                OSEVPF("DATY_STRI:|%s|\n", pamvp[0x00]);
                quote_decode((char *) pamvp[0x00]);
                STRI_PAMSTYL(pscon, lenval, pamvp[0x00])
                break;
            case DATY_STRZ:
                OSEVPF("DATY_STRZ:|%s|\n", pamvp[0x00]);
                quote_decode((char *) pamvp[0x00]);
                STRZ_PAMSTYL(pscon, lenval, pamvp[0x00])
                break;
            case DATY_BINARY:
                OSEVPF("DATY_BINARY\n");
                binlen = ((unsigned long long*) (pamvp[0x00] + ESCA_ENCOLEN_PART))[0x00];
                BINARY_PAMSTYL(pscon, lenval, ((char *) pamvp[0x00] + ESCA_ENTICON_PART), binlen)
                break;
            default:
                _LOG_WARN("default: DATY_INVAL");
                lenval = INVA_ULOLO_VALU;
                break;
        }
        // OSEVPF("lenval:%d\n", lenval);
    }
    //
    return lenval;
}

// ("aa"); // (22);

unsigned long long encod_list_once(char *pscon, const char *pamvu) {
    // OSEVPF("[FUNC]:encod_list_once\n");
    unsigned long long binlen;
    unsigned long long lenval = 0x00;
    //
    switch (check_pamvu_nodtyp((char *) pamvu)) {
        case DATY_INVAL:
            _LOG_WARN("case: DATY_INVAL");
            lenval = INVA_ULOLO_VALU;
            break;
        case DATY_BYTE:
            // OSEVPF("DATY_BYTE\n");
            BYTE_PAMSTYL(pscon, pamvu)
            lenval += sizeof (byte_entit);
            break;
        case DATY_UBYTE:
            // OSEVPF("DATY_UBYTE\n");
            UBYTE_PAMSTYL(pscon, pamvu)
            lenval += sizeof (ubyte_entit);
            break;
        case DATY_SHORT:
            // OSEVPF("DATY_SHORT\n");
            SHORT_PAMSTYL(pscon, pamvu)
            lenval += sizeof (short_entit);
            break;
        case DATY_USHORT:
            // OSEVPF("DATY_USHORT\n");
            USHORT_PAMSTYL(pscon, pamvu)
            lenval += sizeof (ushort_entit);
            break;
        case DATY_INT:
            // OSEVPF("DATY_INT\n");
            INT_PAMSTYL(pscon, pamvu)
            lenval += sizeof (int_entit);
            break;
        case DATY_UINT:
            // OSEVPF("DATY_UINT\n");
            UINT_PAMSTYL(pscon, pamvu)
            lenval += sizeof (uint_entit);
            break;
        case DATY_LLONG:
            // OSEVPF("DATY_LONG\n");
            LLONG_PAMSTYL(pscon, pamvu)
            lenval += sizeof (llong_entit);
            break;
        case DATY_ULLONG:
            // OSEVPF("DATY_ULONG\n");
            ULLONG_PAMSTYL(pscon, pamvu)
            lenval += sizeof (ullong_entit);
            break;
        case DATY_OBID:
            // OSEVPF("DATY_OBID\n");
            OBID_PAMSTYL(pscon, (pamvu + ESCA_OBIDCON_PART))
            lenval += sizeof (obid_entit);
            break;
        case DATY_FLOAT:
            // OSEVPF("DATY_FLOAT\n");
            FLOAT_PAMSTYL(pscon, pamvu)
            lenval += sizeof (float_entit);
            break;
        case DATY_DOUBLE:
            // OSEVPF("DATY_DOUBLE\n");
            DOUBLE_PAMSTYL(pscon, pamvu)
            lenval += sizeof (double_entit);
            break;
        case DATY_STRI:
            // OSEVPF("DATY_STRI\n");
            quote_decode((char *) pamvu);
            STRI_PAMSTYL(pscon, lenval, pamvu)
            break;
        case DATY_STRZ:
            // OSEVPF("DATY_STRZ\n");
            quote_decode((char *) pamvu);
            STRZ_PAMSTYL(pscon, lenval, pamvu)
            break;
        case DATY_BINARY:
            // OSEVPF("DATY_BINARY\n");
            binlen = ((unsigned long long*) (pamvu + ESCA_ENCOLEN_PART))[0x00];
            BINARY_PAMSTYL(pscon, lenval, ((char *) pamvu + ESCA_ENTICON_PART), binlen)
            break;
        default:
            _LOG_WARN("default: DATY_INVAL");
            lenval = INVA_ULOLO_VALU;
            break;
    }
    // OSEVPF("lenval:%d\n", lenval);
    return lenval;
}

// DATA_TYPE notyp

DATA_TYPE check_pamvu_nodtyp(char *data) {
    // OSEVPF("[FUNC]:check_pamvu_nodtyp data:|%s| ", data);
    DATA_TYPE notyp = DATY_INVAL;
    if (isdigit(data[0x00])) {
        for (++data; isdigit(data[0x00]); ++data);
        if ('\0' != data[0x00]) {
            switch (data[0x00]) {
                case 'b':
                    notyp = DATY_BYTE;
                    break;
                case 'B':
                    notyp = DATY_UBYTE;
                    break;
                case 'h':
                    notyp = DATY_SHORT;
                    break;
                case 'H':
                    notyp = DATY_USHORT;
                    break;
                case 'i':
                case 'l':
                    notyp = DATY_INT;
                    break;
                case 'I':
                case 'L':
                    notyp = DATY_UINT;
                    break;
                case 'q':
                    notyp = DATY_LLONG;
                    break;
                case 'Q':
                    notyp = DATY_ULLONG;
                    break;
                case '.':
                    for (++data; isdigit(data[0x00]); ++data);
                    if ('\0' != data[0x00]) {
                        switch (data[0x00]) {
                            case 'f':
                                notyp = DATY_FLOAT;
                                break;
                            case 'd':
                                notyp = DATY_DOUBLE;
                                break;
                            default:
                                notyp = DATY_STRI;
                                break;
                        }
                    } else notyp = DATY_FLOAT;
                    break;
                default:
                    notyp = DATY_STRI;
                    break;
            }
        } else notyp = DATY_INT;
    } else if ('"' == data[0x00]) {
        notyp = DATY_STRI;
        for (++data; '\0' != data[0x00]; ++data) {
            if ('"' == data[0x00]) {
                ++data;
                if ('\0' != data[0x00]) {
                    switch (data[0x00]) {
                        case 's':
                            notyp = DATY_STRI;
                            break;
                        case 'S':
                            notyp = DATY_STRZ;
                            break;
                        default:
                            notyp = DATY_STRI;
                            break;
                    }
                } else notyp = DATY_STRI;
                break;
            } else if ('\\' == data[0x00]) ++data;
        }
    } else if (isalpha(data[0x00]) || ispunct(data[0x00]) || '\0' == data[0x00]) {
        // ispunct(data[0x00]): '*', '<'
        notyp = DATY_STRI;
    } else if (OBJE_IDENT_TYPE == data[ESCA_NODTYP_PART]) {
        notyp = DATY_OBID;
    } else if (BINA_ENTIT_TYPE == data[ESCA_NODTYP_PART]) {
        notyp = DATY_BINARY;
    }
    // OSEVPF("notyp:%d\n", notyp);
    return notyp;
}


