
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "../../cli_struct.h"
#include "pretty_ite.h"

// trans-serve

enum SHOW_TYPE {
    BYTE_TYP,
    UBYTE_TYP,
    SHOR_TYP,
    USHO_TYP,
    INT_TYP,
    UINT_TYP,
    LLON_TYP,
    ULLO_TYP,
    FLOA_TYP,
    DOUB_TYP,
    RECO_TYP,
    OBID_TYP,
    CHAR_TYP,
    STRZ_TYP,
    HEXA_TYP, // extend by james 20230620, for pretty prin_hexa
    NONE_TYP
};

static const struct chin_node fmtst_shtyp_dict[] = {
    {'b', BYTE_TYP}, // int8_t
    {'B', UBYTE_TYP}, // uint8_t
    {'t', UBYTE_TYP}, // uint8_t
    {'h', SHOR_TYP}, // int16_t
    {'H', USHO_TYP}, // uint16_t
    {'i', INT_TYP}, // int32_t
    {'I', UINT_TYP}, // uint32_t
    {'l', INT_TYP}, // int32_t
    {'L', UINT_TYP}, // uint32_t
    {'q', LLON_TYP}, // int64_t
    {'Q', ULLO_TYP}, // uint64_t
    {'o', OBID_TYP}, // object_id
    {'f', FLOA_TYP}, // float
    {'d', DOUB_TYP}, // double
    {'R', RECO_TYP}, // record number
    {'s', CHAR_TYP}, // char / byte
    {'S', STRZ_TYP}, // string
    {'x', HEXA_TYP}, // hexa // extend by james 20230620, for pretty prin_hexa
    {'\0', NONE_TYP} //
};

static char *print_type(uint32 *lv2datyp, uint64 *slenp, char *fmtst) {
    char *endsize;
    if (isdigit(fmtst[0x00])) {
        *slenp = strtoul(fmtst, &endsize, 10);
        fmtst = endsize;
    }
    KV_CHIN_EQUA((*lv2datyp), fmtst_shtyp_dict, fmtst[0x00]);
    return ++fmtst;
}

//

static char *prin_byte(char *resul_str, PK_PACK_STREAM *pkps) {
    // CLIEPF("prin_byte\n");
    int8_t byte_valu;
    if (paki_unpack_byte(pkps, &byte_valu))
        return NULL;
    return lsprif(resul_str, "|%hhd", byte_valu);
}

//

static char *prin_ubyte(char *resul_str, PK_PACK_STREAM *pkps) {
    printf("prin_ubyte\n");
    uint8_t ubyte_valu;
    if (paki_unpack_ubyte(pkps, &ubyte_valu))
        return NULL;
    return lsprif(resul_str, "|%hhu", ubyte_valu);
}

//

static char *prin_short(char *resul_str, PK_PACK_STREAM *pkps) {
    // CLIEPF("prin_short\n");
    int16_t shor_valu;
    if (paki_unpack_short(pkps, &shor_valu))
        return NULL;
    return lsprif(resul_str, "|%hd", shor_valu);
}

//

static char *prin_ushort(char *resul_str, PK_PACK_STREAM *pkps) {
    // CLIEPF("prin_ushort\n");
    uint16_t usho_valu;
    if (paki_unpack_ushort(pkps, &usho_valu))
        return NULL;
    return lsprif(resul_str, "|%hu", usho_valu);
}

//

static char *prin_int32(char *resul_str, PK_PACK_STREAM *pkps) {
    // CLIEPF("prin_int32\n");
    int32_t int_valu;
    if (paki_unpack_int32(pkps, &int_valu))
        return NULL;
    return lsprif(resul_str, "|%d", int_valu);
}

//

static char *prin_uint32(char *resul_str, PK_PACK_STREAM *pkps) {
    // CLIEPF("prin_uint32\n");
    uint32_t uint_valu;
    if (paki_unpack_uint32(pkps, &uint_valu))
        return NULL;
    return lsprif(resul_str, "|%u", uint_valu);
}

//

static char *prin_llong(char *resul_str, PK_PACK_STREAM *pkps) {
    // CLIEPF("prin_llong\n");
    int64_t llon_valu;
    if (paki_unpack_int64(pkps, &llon_valu))
        return NULL;
    return lsprif(resul_str, "|%lld", llon_valu);
}

//

static char *prin_ullon(char *resul_str, PK_PACK_STREAM *pkps) {
    // CLIEPF("prin_ullon\n");
    uint64_t ullo_valu;
    if (paki_unpack_uint64(pkps, &ullo_valu))
        return NULL;
    return lsprif(resul_str, "|%llu", ullo_valu);
}

//

static char *prin_float(char *resul_str, PK_PACK_STREAM *pkps) {
    // CLIEPF("prin_float\n");
    float floa_valu;
    if (paki_unpack_float(pkps, &floa_valu))
        return NULL;
    return lsprif(resul_str, "|%f", floa_valu);
}

//

static char *prin_double(char *resul_str, PK_PACK_STREAM *pkps) {
    // CLIEPF("prin_double\n");
    double doub_valu;
    if (paki_unpack_double(pkps, &doub_valu))
        return NULL;
    return lsprif(resul_str, "|%lf", doub_valu);
}

static inline char *oidstr_se(char *obid_stri, cli_oid_t *obje_obid) {
    char *toksp = obid_stri;
    unsigned char *tokst = ((unsigned char *) obje_obid);
    unsigned int inde = 0x00;
    for (; inde < OBJE_IDENTI_BLEN; ++inde, ++tokst, ++toksp) {
        sprintf(toksp, "%02x", *tokst);
        ++toksp;
    }
    // obid_stri[24] = '\0';
    return obid_stri;
}

//

static char *prin_objid(char *resul_str, PK_PACK_STREAM *pkps) {
    // CLIEPF("prin_objid\n");
    osv_oid_t *oid_valu;
    if (paki_unpack_obid(pkps, &oid_valu))
        return NULL;
    char obid_stri[OBJE_IDENTI_ZLEN];
    oidstr_se(obid_stri, (cli_oid_t *) oid_valu);
    return lsprif(resul_str, "|%s", obid_stri);
}

static inline char *sidstr_se(char *plai_stid, cli_sid_t *obje_stid) {
    char *toksp = plai_stid;
    unsigned char *tokst = ((unsigned char *) obje_stid);
    unsigned int inde = 0x00;
    for (; inde < STOR_IDENTI_BLEN; ++inde, ++tokst, ++toksp) {
        sprintf(toksp, "%02x", *tokst);
        ++toksp;
    }
    // plai_stid[16] = '\0';
    return plai_stid;
}

// 

static char *prin_record(char *resul_str, PK_PACK_STREAM *pkps) {
    // CLIEPF("prin_record\n");
    uint64_t rcod_valu;
    if (paki_unpack_recod(pkps, &rcod_valu))
        return NULL;
    char plai_stid[STOR_IDENTI_ZLEN];
    sidstr_se(plai_stid, (cli_sid_t *) & rcod_valu);
    return lsprif(resul_str, "|%s", plai_stid);
}

// hexa printf

static inline char *prin_hexa(char *resul_str, PK_PACK_STREAM *pkps, uint64 slen) {
    char *stri_valu;
    if (paki_unpack_stri(pkps, (const char **) &stri_valu))
        return NULL;
    //
    char *toksp = lccpy(resul_str, '|');
    unsigned char *tokst = ((unsigned char *) stri_valu);
    unsigned int inde = 0x00;
    for (; inde < slen; ++inde, ++tokst, ++toksp) {
        sprintf(toksp, "%02x", *tokst);
        ++toksp;
    }
    // plai_stid[16] = '\0';
    return toksp;
}

//

static char *prin_char_array(char *resul_str, PK_PACK_STREAM *pkps, uint64 slen) {
    // CLIEPF("prin_char_arra\n");
    char *stri_valu;
    if (paki_unpack_stri(pkps, (const char **) &stri_valu))
        return NULL;
    stri_valu[slen] = '\0';
    return lsprif(resul_str, "|%s", stri_valu);
}

//

static char *prin_string(char *resul_str, PK_PACK_STREAM *pkps) {
    // CLIEPF("prin_string\n");
    char *stri_valu;
    if (paki_unpack_strz(pkps, (const char **) &stri_valu))
        return NULL;
    return lsprif(resul_str, "|%s", stri_valu);
}

//

static char *(*prin_tab[])(char *, PK_PACK_STREAM *) = {
    prin_byte,
    prin_ubyte,
    prin_short,
    prin_ushort,
    prin_int32,
    prin_uint32,
    prin_llong,
    prin_ullon,
    prin_float,
    prin_double,
    prin_record,
    prin_objid
};

// 0x00:OK -1:error

int pretty_variable_echo(clie_resu *resul, char *fmtstr, char *prestr, char *resp_data, uint64 quer_leng) {
    PK_PACK_STREAM *pkps;
    if (paki_stream_open(fmtstr, (void *) resp_data, quer_leng, &pkps))
        return -1;
    //
    uint32 vtype;
    uint64 sleng;
    char *fmtok, *last_str = resul->resu_data;
    unsigned int inde = 0x00;
    for (; quer_leng > paki_stream_leng(pkps); ++inde) {
        paki_stream_reset(pkps, RESET_STREAM_FORMAT);
        fmtok = prestr;
        while ('\0' != fmtok[0x00]) {
            fmtok = print_type(&vtype, &sleng, fmtok);
            // CLIEPF("vtype:%u sleng:%llu fmtok:|%s|\n", vtype, sleng, fmtok);
            switch (vtype) {
                case CHAR_TYP:
                    last_str = prin_char_array(last_str, pkps, sleng);
                    break;
                case STRZ_TYP:
                    last_str = prin_string(last_str, pkps);
                    break;
                case HEXA_TYP: // hexa // extend by james 20230620, for pretty prin_hexa
                    last_str = prin_hexa(last_str, pkps, sleng);
                    break;
                default:
                    last_str = prin_tab[vtype](last_str, pkps);
                    break;
            }
            if (!last_str) {
                CliePrintErro("Unpack respon error!", -1);
                return -1;
            }
        }
        last_str = lscpy(last_str, "|\n");
    }
    //
    paki_stream_close(pkps, NULL);
    last_str = lsprif(last_str, "found %d objectes.\n", inde);
    resul->resu_leng = last_str - resul->resu_data;
    //

    return 0x00;
}



