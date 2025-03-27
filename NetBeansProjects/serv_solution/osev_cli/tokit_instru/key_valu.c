#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "../debug_funct_sh.h"
#include "key_valu.h"

//

enum SHOW_TYPE {
    BYTE_TYP,
    UBYTE_TYP,
    SHOR_TYP,
    USHO_TYP,
    INT_TYP,
    UINT_TYP,
    LLON_TYP,
    OBID_TYP,
    ULLO_TYP,
    FLOA_TYP,
    DOUB_TYP,
    RECO_TYP,
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

static char *prin_byte(char *resul_str, const char *resdat) {
    // CLIT_PF("prin_byte\n");
    int8_t byte_valu = *((int8_t *) resdat);
    return lsprif(resul_str, "|%hhd", byte_valu);
}

//

static char *prin_ubyte(char *resul_str, const char *resdat) {
    // CLIT_PF("prin_ubyte\n");
    uint8_t ubyte_valu = *((uint8_t *) resdat);
    return lsprif(resul_str, "|%hhu", ubyte_valu);
}

//

static char *prin_short(char *resul_str, const char *resdat) {
    // CLIT_PF("prin_short\n");
    int16_t shor_valu = *((int16_t *) resdat);
    return lsprif(resul_str, "|%hd", shor_valu);
}

//

static char *prin_ushort(char *resul_str, const char *resdat) {
    // CLIT_PF("prin_ushort\n");
    uint16_t usho_valu = *((uint16_t *) resdat);
    return lsprif(resul_str, "|%hu", usho_valu);
}

//

static char *prin_int32(char *resul_str, const char *resdat) {
    // CLIT_PF("prin_int32\n");
    int32_t int_valu = *((int32_t *) resdat);
    return lsprif(resul_str, "|%d", int_valu);
}

//

static char *prin_uint32(char *resul_str, const char *resdat) {
    // CLIT_PF("prin_uint32\n");
    uint32_t uint_valu = *((uint32_t *) resdat);
    return lsprif(resul_str, "|%u", uint_valu);
}

//

static char *prin_llong(char *resul_str, const char *resdat) {
    // CLIT_PF("prin_llong\n");
    int64_t llon_valu = *((int64_t *) resdat);
    return lsprif(resul_str, "|%lld", llon_valu);
}

//

static char *prin_ullon(char *resul_str, const char *resdat) {
    // CLIT_PF("prin_ullon\n");
    uint64_t ullo_valu = *((uint64_t *) resdat);
    return lsprif(resul_str, "|%llu", ullo_valu);
}

//

static char *prin_float(char *resul_str, const char *resdat) {
    // CLIT_PF("prin_float\n");
    float floa_valu = *((float *) resdat);
    return lsprif(resul_str, "|%f", floa_valu);
}

//

static char *prin_double(char *resul_str, const char *resdat) {
    // CLIT_PF("prin_double\n");
    double doub_valu = *((double *) resdat);
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

static char *prin_objid(char *resul_str, const char *resdat) {
    // CLIT_PF("prin_objid\n");
    char obid_stri[OBJE_IDENTI_ZLEN];
    oidstr_se(obid_stri, (cli_oid_t *) resdat);
    return lsprif(resul_str, "|%s", obid_stri);
}

static inline char *sidstr_se(char *stoid_stri, cli_sid_t *obje_stoid) {
    char *toksp = stoid_stri;
    unsigned char *tokst = ((unsigned char *) obje_stoid);
    unsigned int inde = 0x00;
    for (; inde < STOR_IDENTI_BLEN; ++inde, ++tokst, ++toksp) {
        sprintf(toksp, "%02x", *tokst);
        ++toksp;
    }
    // stoid_stri[16] = '\0';
    return stoid_stri;
}

// 

static char *prin_record(char *resul_str, const char *resdat) {
    // CLIT_PF("prin_record\n");
    char stoid_stri[STOR_IDENTI_ZLEN];
    sidstr_se(stoid_stri, (cli_sid_t *) resdat);
    return lsprif(resul_str, "|%s", stoid_stri);
}

// hexa printf

static inline char *prin_hexa(char *resul_str, const char *resdat, uint64 slen) {
    char *toksp = lccpy(resul_str, '|');
    unsigned char *tokst = ((unsigned char *) resdat);
    unsigned int inde = 0x00;
    for (; inde < slen; ++inde, ++tokst, ++toksp) {
        sprintf(toksp, "%02x", *tokst);
        ++toksp;
    }
    // stoid_stri[16] = '\0';
    return toksp;
}

//

static char *prin_char_array(char *resul_str, const char *resdat, uint64 slen) {
    // CLIT_PF("prin_char_arra\n");
    ((char *) resdat)[slen] = '\0';
    return lsprif(resul_str, "|%s", resdat);
}

//

static char *prin_string(char *resul_str, uint64 *slenp, const char *resdat) {
    // CLIT_PF("prin_string\n");
    slenp[0x00] = 0x01 + strlen(resdat);
    return lsprif(resul_str, "|%s", resdat);
}

//

static char *(*prin_tab[])(char *, const char *) = {
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

static size_t type_size_tab[] = {
    sizeof (int8_t),
    sizeof (uint8_t),
    sizeof (int16_t),
    sizeof (uint16_t),
    sizeof (int32_t),
    sizeof (uint32_t),
    sizeof (int64_t),
    sizeof (uint64_t),
    sizeof (float),
    sizeof (double),
    sizeof (uint64_t),
    sizeof (osv_oid_t)
};

// 0x00:OK -1:error

static int pretty_variable_echo(clit_resu *resul, char *prestr, char *resp_data, uint64 quer_leng) {
    char *resp_end = quer_leng + resp_data;
    char *posi_resp = resp_data;
    //
    uint32 vtype;
    uint64 sleng;
    char *fmtok, *last_str = resul->resu_data;
    unsigned int inde = 0x00;
    for (; resp_end > posi_resp; ++inde) {
        fmtok = prestr;
        while ('\0' != fmtok[0x00]) {
            fmtok = print_type(&vtype, &sleng, fmtok);
            // CLIT_PF("vtype:%u sleng:%llu fmtok:|%s|\n", vtype, sleng, fmtok);
            switch (vtype) {
                case CHAR_TYP:
                    last_str = prin_char_array(last_str, posi_resp, sleng);
                    posi_resp += sleng;
                    break;
                case STRZ_TYP:
                    last_str = prin_string(last_str, &sleng, posi_resp);
                    posi_resp += sleng;
                    break;
                case HEXA_TYP: // hexa // extend by james 20230620, for pretty prin_hexa
                    last_str = prin_hexa(last_str, posi_resp, sleng);
                    posi_resp += sleng;
                    break;
                default:
                    last_str = prin_tab[vtype](last_str, posi_resp);
                    posi_resp += type_size_tab[vtype];
                    break;
            }
            if (!last_str) {
                ClitPrintErro("Unpack respon error!", -1);
                return -1;
            }
        }
        last_str = lscpy(last_str, "|\n");
    }
    //
    last_str = lsprif(last_str, "found %d objectes.\n", inde);
    resul->resu_leng = last_str - resul->resu_data;
    //

    return 0x00;
}

// build fmtstr e->s 

inline void build_packi_fmtst(char *fmtstr, char *prestr) {
    for (; prestr[0x00]; ++prestr, ++fmtstr) {
        if ('x' == prestr[0x00])
            fmtstr[0x00] = 's';
        else fmtstr[0x00] = prestr[0x00];
    }
    fmtstr[0x00] = '\0';
}

// kits:key_value("oi");
// 0x00:OK -1:error

int kits_keyval(char **pamvp, clit_resu *resul) {
    CLIT_PF("[FUNC]:kits_keyval.\n");
    // pamvu = 1
    if (!pamvp[0x00] || pamvp[0x01])
        return -1;
    //
    if (resul->resu_type)
        return -1;
    if (LARGE_CONTE_SIZE < resul->resu_leng) {
        ClitPrintErro("Result leng more than LARGE_CONTE_SIZE!", -1);
        return -1;
    }
    //
    char resp_data[LARGE_CONTE_SIZE];
    memcpy(resp_data, resul->resu_data, resul->resu_leng);
    quote_decode(pamvp[0x00]);
    // chk_resdat_type
    pretty_variable_echo(resul, pamvp[0x00], resp_data, resul->resu_leng);
    //
    return 0x00;
}

