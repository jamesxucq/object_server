
#include "utility/last_stri.h"

#include "pamstyl_utili.h"
#include "debug_funct_osv.h"

// (11, "bb", 22, "dd");

char *decod_gener_loop(char **pamvp, char *_data_line_, char *req_dat, unsigned long long req_len) {
    // OSEVPF("decod_gener_loop\n");
    char *end_tok = req_dat + req_len;
    //
    for (; end_tok > req_dat; ++pamvp) {
        switch (((unsigned char *) req_dat)[0x00]) {
            case DATY_BYTE:
            case DATY_UBYTE:
                // OSEVPF("decode_pamstyl byte\n");
                LAMCPY_BIN(pamvp[0x00], &((byte_entit *) req_dat)->data, sizeof (char), _data_line_);
                req_dat += sizeof (byte_entit);
                break;
            case DATY_SHORT:
            case DATY_USHORT:
                // OSEVPF("decode_pamstyl short\n");
                LAMCPY_BIN(pamvp[0x00], &((short_entit *) req_dat)->data, sizeof (short), _data_line_);
                req_dat += sizeof (short_entit);
                break;
            case DATY_INT:
            case DATY_UINT:
                // OSEVPF("decode_pamstyl int\n");
                LAMCPY_BIN(pamvp[0x00], &((int_entit *) req_dat)->data, sizeof (int), _data_line_);
                // OSEVPF("*((uint32 *) pamvp[0x00]):|%d|\n", *((uint32 *) pamvp[0x00]));
                req_dat += sizeof (int_entit);
                break;
            case DATY_LLONG:
            case DATY_ULLONG:
                // OSEVPF("decode_pamstyl long\n");
                LAMCPY_BIN(pamvp[0x00], &((llong_entit *) req_dat)->data, sizeof (long long), _data_line_);
                req_dat += sizeof (llong_entit);
                break;
            case DATY_OBID:
                // OSEVPF("decode_pamstyl obid\n");
                LAMCPY_BIN(pamvp[0x00], &((obid_entit *) req_dat)->data, sizeof (osv_oid_t), _data_line_);
                req_dat += sizeof (obid_entit);
                break;
            case DATY_FLOAT:
                // OSEVPF("decode_pamstyl float\n");
                LAMCPY_BIN(pamvp[0x00], &((float_entit *) req_dat)->data, sizeof (float), _data_line_);
                req_dat += sizeof (float_entit);
                break;
            case DATY_DOUBLE:
                // OSEVPF("decode_pamstyl double\n");
                LAMCPY_BIN(pamvp[0x00], &((double_entit *) req_dat)->data, sizeof (double), _data_line_);
                req_dat += sizeof (double_entit);
                break;
            case DATY_STRI:
                // OSEVPF("decode_pamstyl string\n");
                LSZCPY_O(pamvp[0x00], ((stri_entit *) req_dat)->data, ((stri_entit *) req_dat)->colen, _data_line_);
                req_dat += sizeof (stri_entit) + ((stri_entit *) req_dat)->colen;
                break;
            case DATY_STRZ:
                // OSEVPF("decode_pamstyl strz\n");
                LAMCPY_BIN(pamvp[0x00], ((strz_entit *) req_dat)->data, ((strz_entit *) req_dat)->colen, _data_line_);
                req_dat += sizeof (strz_entit) + ((strz_entit *) req_dat)->colen;
                break;
            case DATY_BINARY:
                // OSEVPF("decode_pamstyl binary\n");
                LAMCPY_BIN(pamvp[0x00], ((binary_entit *) req_dat)->data, ((binary_entit *) req_dat)->colen, _data_line_);
                req_dat += sizeof (binary_entit) + ((binary_entit *) req_dat)->colen;
                break;
            default:
                // _LOG_WARN("default: decode_pamstyl");
                return NULL;
                break;
        }
    }
    pamvp[0x00] = NULL;
    //
    return _data_line_;
}

// pams_valu *pamvu, (11, "bb", 22, "dd");

char *decod_getyp_loop(pams_valu *pamvu, char *_data_line_, char *req_dat) {
    OSEVPF("decod_getyp_loop\n");
    unsigned char *pamtyp = pamvu->pamtyp;
    char **pamvp = pamvu->pamcon;
    unsigned long long *pmlen = pamvu->req_len;
    char *end_tok = req_dat + pamvu->req_len[0x00];
    //
    for (; end_tok > req_dat; ++pamtyp, ++pamvp, ++pmlen) {
        pamtyp[0x00] = ((unsigned char *) req_dat)[0x00];
        switch (((unsigned char *) req_dat)[0x00]) {
            case DATY_BYTE:
            case DATY_UBYTE:
                OSEVPF("decode_pamstyl byte\n");
                LAMCPY_BIN(pamvp[0x00], &((byte_entit *) req_dat)->data, sizeof (char), _data_line_);
                req_dat += sizeof (byte_entit);
                break;
            case DATY_SHORT:
            case DATY_USHORT:
                OSEVPF("decode_pamstyl short\n");
                LAMCPY_BIN(pamvp[0x00], &((short_entit *) req_dat)->data, sizeof (short), _data_line_);
                req_dat += sizeof (short_entit);
                break;
            case DATY_INT:
            case DATY_UINT:
                OSEVPF("decode_pamstyl int\n");
                LAMCPY_BIN(pamvp[0x00], &((int_entit *) req_dat)->data, sizeof (int), _data_line_);
                req_dat += sizeof (int_entit);
                break;
            case DATY_LLONG:
            case DATY_ULLONG:
                OSEVPF("decode_pamstyl long\n");
                LAMCPY_BIN(pamvp[0x00], &((llong_entit *) req_dat)->data, sizeof (long long), _data_line_);
                req_dat += sizeof (llong_entit);
                break;
            case DATY_OBID:
                OSEVPF("decode_pamstyl obid\n");
                LAMCPY_BIN(pamvp[0x00], &((obid_entit *) req_dat)->data, sizeof (osv_oid_t), _data_line_);
                req_dat += sizeof (obid_entit);
                break;
            case DATY_FLOAT:
                OSEVPF("decode_pamstyl float\n");
                LAMCPY_BIN(pamvp[0x00], &((float_entit *) req_dat)->data, sizeof (float), _data_line_);
                req_dat += sizeof (float_entit);
                break;
            case DATY_DOUBLE:
                OSEVPF("decode_pamstyl double\n");
                LAMCPY_BIN(pamvp[0x00], &((double_entit *) req_dat)->data, sizeof (double), _data_line_);
                req_dat += sizeof (double_entit);
                break;
            case DATY_STRI:
                OSEVPF("decode_pamstyl string\n");
                LSZCPY_O(pamvp[0x00], ((stri_entit *) req_dat)->data, ((stri_entit *) req_dat)->colen, _data_line_);
                pmlen[0x00] = ((binary_entit *) req_dat)->colen;
                req_dat += sizeof (stri_entit) + ((stri_entit *) req_dat)->colen;
                break;
            case DATY_STRZ:
                OSEVPF("decode_pamstyl strz\n");
                LAMCPY_BIN(pamvp[0x00], ((strz_entit *) req_dat)->data, ((strz_entit *) req_dat)->colen, _data_line_);
                pmlen[0x00] = ((binary_entit *) req_dat)->colen;
                req_dat += sizeof (strz_entit) + ((strz_entit *) req_dat)->colen;
                break;
            case DATY_BINARY:
                OSEVPF("decode_pamstyl binary\n");
                LAMCPY_BIN(pamvp[0x00], ((binary_entit *) req_dat)->data, ((binary_entit *) req_dat)->colen, _data_line_);
                pmlen[0x00] = ((binary_entit *) req_dat)->colen;
                req_dat += sizeof (binary_entit) + ((binary_entit *) req_dat)->colen;
                break;
            default:
                // _LOG_WARN("default: decode_pamstyl");
                return NULL;
                break;
        }
    }
    pamtyp[0x00] = DATY_INVAL;
    pamvp[0x00] = NULL;
    //
    return _data_line_;
}

//

char *decod_getyp_stram(pams_valu *pamvu, char *_data_line_, char *req_dat, char *req_sta) {
    OSEVPF("decod_getyp_stram\n");
    unsigned char *pamtyp = pamvu->pamtyp;
    char **pamvp = pamvu->pamcon;
    unsigned long long *pmlen = pamvu->req_len;
    char *end_tok = req_dat + pamvu->req_len[0x00];
    //
    for (; end_tok > req_dat; ++pamtyp, ++pamvp, ++pmlen) {
        pamtyp[0x00] = ((unsigned char *) req_dat)[0x00];
        switch (((unsigned char *) req_dat)[0x00]) {
            case DATY_OBID:
                // OSEVPF("decode_pamstyl DATY_OBID\n");
                LAMCPY_BIN(pamvp[0x00], &((obid_entit *) req_dat)->data, sizeof (osv_oid_t), _data_line_);
                req_dat += sizeof (obid_entit);
                break;
            case DATY_STRI:
                // OSEVPF("decode_pamstyl DATY_STRI\n");
                LSZCPY_O(pamvp[0x00], ((stri_entit *) req_dat)->data, ((stri_entit *) req_dat)->colen, _data_line_);
                pmlen[0x00] = ((stri_entit *) req_dat)->colen;
                req_dat += sizeof (stri_entit) + ((stri_entit *) req_dat)->colen;
                break;
            case DATY_BINARY:
                // OSEVPF("decode_pamstyl DATY_BINARY\n");
                // LAMCPY_BIN(pamvp[0x00], ((binary_entit *) req_dat)->data, ((binary_entit *) req_dat)->colen, _data_line_);
                LAMEQU_ULL(pamvp[0x00], ((binary_entit *) req_dat)->data - req_sta, _data_line_);
                pmlen[0x00] = ((binary_entit *) req_dat)->colen;
                req_dat += sizeof (binary_entit) + ((binary_entit *) req_dat)->colen;
                break;
            default:
                // _LOG_WARN("default: decode_pamstyl");
                return NULL;
                break;
        }
    }
    pamtyp[0x00] = DATY_INVAL;
    pamvp[0x00] = NULL;
    //
    return _data_line_;
}


// pams_valu *pamvu, (11) ("bb") (22) ("dd");

char *decod_getyp_once(pams_valu *pamvu, char *_data_line_, char *req_dat) {
    // OSEVPF("decod_getyp_once\n");
    unsigned char *pamtyp = pamvu->pamtyp;
    char **pamvp = pamvu->pamcon;
    unsigned long long *pmlen = pamvu->req_len;
    //
    pamtyp[0x00] = ((unsigned char *) req_dat)[0x00];
    switch (((unsigned char *) req_dat)[0x00]) {
        case DATY_BYTE:
        case DATY_UBYTE:
            // OSEVPF("decode_pamstyl byte\n");
            LAMCPY_BIN(pamvp[0x00], &((byte_entit *) req_dat)->data, sizeof (char), _data_line_);
            break;
        case DATY_SHORT:
        case DATY_USHORT:
            // OSEVPF("decode_pamstyl short\n");
            LAMCPY_BIN(pamvp[0x00], &((short_entit *) req_dat)->data, sizeof (short), _data_line_);
            break;
        case DATY_INT:
        case DATY_UINT:
            // OSEVPF("decode_pamstyl int\n");
            LAMCPY_BIN(pamvp[0x00], &((int_entit *) req_dat)->data, sizeof (int), _data_line_);
            break;
        case DATY_LLONG:
        case DATY_ULLONG:
            // OSEVPF("decode_pamstyl long\n");
            LAMCPY_BIN(pamvp[0x00], &((llong_entit *) req_dat)->data, sizeof (long long), _data_line_);
            break;
        case DATY_OBID:
            // OSEVPF("decode_pamstyl obid\n");
            LAMCPY_BIN(pamvp[0x00], &((obid_entit *) req_dat)->data, sizeof (osv_oid_t), _data_line_);
            break;
        case DATY_FLOAT:
            // OSEVPF("decode_pamstyl float\n");
            LAMCPY_BIN(pamvp[0x00], &((float_entit *) req_dat)->data, sizeof (float), _data_line_);
            break;
        case DATY_DOUBLE:
            // OSEVPF("decode_pamstyl double\n");
            LAMCPY_BIN(pamvp[0x00], &((double_entit *) req_dat)->data, sizeof (double), _data_line_);
            break;
        case DATY_STRI:
            // OSEVPF("decode_pamstyl string\n");
            LSZCPY_O(pamvp[0x00], ((stri_entit *) req_dat)->data, ((stri_entit *) req_dat)->colen, _data_line_);
            pmlen[0x00] = ((binary_entit *) req_dat)->colen;
            break;
        case DATY_STRZ:
            // OSEVPF("decode_pamstyl strz\n");
            LAMCPY_BIN(pamvp[0x00], ((strz_entit *) req_dat)->data, ((strz_entit *) req_dat)->colen, _data_line_);
            pmlen[0x00] = ((binary_entit *) req_dat)->colen;
            break;
        case DATY_BINARY:
            // OSEVPF("decode_pamstyl binary\n");
            LAMCPY_BIN(pamvp[0x00], ((binary_entit *) req_dat)->data, ((binary_entit *) req_dat)->colen, _data_line_);
            pmlen[0x00] = ((binary_entit *) req_dat)->colen;
            break;
        default:
            // _LOG_WARN("default: decode_pamstyl");
            return NULL;
            break;
    }
    (++pamtyp)[0x00] = DATY_INVAL;
    (++pamvp)[0x00] = NULL;
    //
    return _data_line_;
}

// LARGE_TEXT_SIZE // DATY_STRI ("aaaaa");

char *decod_txti_once(char **pamvp, char *_data_line_, char *req_dat) {
    LSCPY_INI(pamvp[0x00], _data_line_);
    if (!pamstyl_stri(pamvp[0x00], req_dat)) {
        pamvp[0x00] = NULL;
        return NULL;
    }
    LSCPY_FIN(_data_line_, pamvp[0x00]);
    pamvp[0x01] = NULL;
    return _data_line_;
}

// LARGE_TEXT_SIZE // DATY_STRZ ("aaaaa");

char *decod_txtz_once(char **pamvp, char *_data_line_, char *req_dat) {
    LSCPY_INI(pamvp[0x00], _data_line_);
    if (!pamstyl_strz(pamvp[0x00], req_dat)) {
        pamvp[0x00] = NULL;
        return NULL;
    }
    LSCPY_FIN(_data_line_, pamvp[0x00]);
    pamvp[0x01] = NULL;
    return _data_line_;
}

//
// DATY_BINARY (object)

char *decod_binary_once(char **pamvp, char *_data_line_, char *req_dat) {
    unsigned long long enlen;
    LAMCPY_INI(pamvp[0x00], _data_line_);
    if (!pamstyl_binary(pamvp[0x00], &enlen, req_dat)) {
        pamvp[0x00] = NULL;
        return NULL;
    }
    LAMCPY_FIN(_data_line_, enlen);
    pamvp[0x01] = NULL;
    return _data_line_;
}

char *decod_obid_once(char **pamvp, char *_data_line_, char *req_dat) {
    LAMCPY_INI(pamvp[0x00], _data_line_);
    if (!pamstyl_obid((osv_oid_t *) pamvp[0x00], req_dat)) {
        pamvp[0x00] = NULL;
        return NULL;
    }
    LAMCPY_FIN(_data_line_, PSTY_OBID_ELEN);
    pamvp[0x01] = NULL;
    return _data_line_;
}

