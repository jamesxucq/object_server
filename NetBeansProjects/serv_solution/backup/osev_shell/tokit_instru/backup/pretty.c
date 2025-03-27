#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "pretty.h"

//

struct vint_node {
    const char chak;
    int intv;
};

#define TVALU_INTE(VALUE, TABLE, CHAK) { \
    struct vint_node *item = (struct vint_node *) TABLE; \
    for(; '\0' != item->chak; ++item) \
        if(item->chak == CHAK) break; \
    VALUE = item->intv; \
}

enum DATA_TYPE {
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
    STRI_TYP,
    NONE_TYP
};

static const struct vint_node types_value_tab[] = {
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
    {'f', FLOA_TYP}, // float
    {'d', DOUB_TYP}, // double
    {'R', RECO_TYP}, // record number
    {'o', OBID_TYP}, // object_id
    {'O', OBID_TYP}, // object_id
    {'s', CHAR_TYP}, // byte/char
    {'S', STRI_TYP}, // string
    {'\0', NONE_TYP} //
};

static char *print_type(uint32 *lv2datyp, uint32 *slenp, char *fmts) {
    char *endsize;
    if (isdigit(fmts[0x00])) {
        slenp[0x00] = strtoul(fmts, &endsize, 10);
        fmts = endsize;
    }
    TVALU_INTE((*lv2datyp), types_value_tab, fmts[0x00]);
    //
    return ++fmts;
}

//

static char *prin_char(char *resul_str, char *char_valu) {
    // CLIEPF("prin_char char_valu:|%d|\n", (int) char_valu);
    return lsprif(resul_str, "|%c", ((char *) char_valu)[0x00]);
}

static char *prin_uchar(char *resul_str, char *ucha_valu) {
    // CLIEPF("prin_uchar ucha_valu:|%u|\n", (unsigned int) ucha_valu);
    return lsprif(resul_str, "|%u", ((unsigned char *) ucha_valu)[0x00]);
}

static char *prin_short(char *resul_str, char *shor_valu) {
    // CLIEPF("prin_short shor_valu:|%hd|\n", shor_valu)[0x00]);
    return lsprif(resul_str, "|%hd", ((short *) shor_valu)[0x00]);
}

static char *prin_ushor(char *resul_str, char *usho_valu) {
    // CLIEPF("prin_ushor usho_valu:|%hu|\n", usho_valu)[0x00]);
    return lsprif(resul_str, "|%hu", ((unsigned short *) usho_valu)[0x00]);
}

static char *prin_int(char *resul_str, char *int_valu) {
    // CLIEPF("prin_int int_valu:|%d|\n", int_valu)[0x00]);
    return lsprif(resul_str, "|%d", ((int *) int_valu)[0x00]);
}

static char *prin_uint(char *resul_str, char *uint_valu) {
    // CLIEPF("prin_uint uint_valu:|%u|\n", uint_valu)[0x00]);
    return lsprif(resul_str, "|%u", ((unsigned int *) uint_valu)[0x00]);
}

static char *prin_llong(char *resul_str, char *llon_valu) {
    // CLIEPF("prin_llong llon_valu:|%lld|\n", llon_valu)[0x00]);
    return lsprif(resul_str, "|%lld", ((long long *) llon_valu)[0x00]);
}

static char *prin_ullon(char *resul_str, char *ullo_valu) {
    // CLIEPF("prin_ullon ullo_valu:|%llu|\n", ullo_valu)[0x00]);
    return lsprif(resul_str, "|%llu", ((unsigned long long *) ullo_valu)[0x00]);
}

static char *prin_float(char *resul_str, char *floa_valu) {
    // CLIEPF("prin_ullon ullo_valu:|%llu|\n", ullo_valu)[0x00]);
    return lsprif(resul_str, "|%f", ((float *) floa_valu)[0x00]);
}

static char *prin_double(char *resul_str, char *doub_valu) {
    // CLIEPF("prin_ullon ullo_valu:|%llu|\n", ullo_valu)[0x00]);
    return lsprif(resul_str, "|%lf", ((double *) doub_valu)[0x00]);
}

static char *oidstr_se(char *oid_stri, she_oid_t *obje_oid) {
    char *toksp = oid_stri;
    unsigned char *tokst = ((unsigned char *) obje_oid);
    unsigned int inde = 0x00;
    for (; inde < OID_BINARY_LEN; ++inde, ++tokst) {
        sprintf(toksp, "%02x", *tokst);
        ++toksp;
        ++toksp;
    }
    // oid_stri[24] = '\0';
    return oid_stri;
}

static char *prin_objid(char *resul_str, char *oid_valu) {
    char oid_stri[OID_LINE_LEN];
    oidstr_se(oid_stri, (she_oid_t *) oid_valu);
    // CLIEPF("prin_objid oid_stri:|%s|\n", oid_stri);
    return lsprif(resul_str, "|%s", oid_stri);
}

static char *sidstr_se(char *sid_stri, she_sid_t *obje_sid) {
    char *toksp = sid_stri;
    unsigned char *tokst = ((unsigned char *) obje_sid);
    unsigned int inde = 0x00;
    for (; inde < SID_BINARY_LEN; ++inde, ++tokst) {
        sprintf(toksp, "%02x", *tokst);
        ++toksp;
        ++toksp;
    }
    // sid_stri[16] = '\0';
    return sid_stri;
}

static char *prin_record(char *resul_str, char *rcod_valu) {
    char sid_stri[SID_LINE_LEN];
    sidstr_se(sid_stri, (she_sid_t *) rcod_valu);
    // CLIEPF("prin_record sid_stri:|%s|\n", sid_stri);
    return lsprif(resul_str, "|%s", sid_stri);
}

static char *prin_char_arra(char *resul_str, char *stri_valu, size_t len) {
    stri_valu[len] = '\0';
    // CLIEPF("prin_char_arra stri_valu:|%s|\n", stri_valu);
    return lsprif(resul_str, "|%s", stri_valu);
}

static char *prin_string(char *resul_str, uint64 *data_size, char *stri_valu, char *obje_tail) {
    char *posi_str = obje_tail + data_size[0x00];
    data_size[0x00] += *(uint64 *) stri_valu;
    // CLIEPF("prin_char_arra stri_valu:|%s|\n", stri_valu);
    return lsprif(resul_str, "|%s", posi_str);
}

//

static char *(*prin_tab[])(char *, char *) = {
    prin_char,
    prin_uchar,
    prin_short,
    prin_ushor,
    prin_int,
    prin_uint,
    prin_llong,
    prin_ullon,
    prin_float,
    prin_double,
    prin_record,
    prin_objid
};

static const int len_vtype_tab[] = {
    0x01,
    0x01,
    0x02,
    0x02,
    0x04,
    0x04,
    0x08,
    0x08,
    0x04,
    0x08,
    0x08,
    0x0c,
    0x00
};

// 0x00:OK -1:error

static int utili_pretty_fixed(shel_resu *resul, char *numtok, char *query_data) {
    char *posi_str = query_data;
    char *last_str = resul->resu_data;
    char *style_str;
    //
    int inde = 0x00;
    for (; resul->resu_leng > (posi_str - query_data); ++inde) {
        style_str = numtok;
        uint32 vtype, sleng;
        while ('\0' != style_str[0x00]) {
            style_str = print_type(&vtype, &sleng, style_str);
            // CLIEPF("vtype:%d sleng:%d style_str:|%s|\n", vtype, sleng, style_str);
            if (CHAR_TYP == vtype) {
                last_str = prin_char_arra(last_str, posi_str, sleng);
                posi_str += sleng;
            } else {
                last_str = prin_tab[vtype](last_str, posi_str);
                posi_str += len_vtype_tab[vtype];
            }
        }
        last_str = lscpy(last_str, "|\n");
    }
    last_str = lsprif(last_str, "found %d objectes.\n", inde);
    resul->resu_leng = last_str - resul->resu_data;
    //
    return 0x00;
}

//

static uint64 count_data_leng(char *numtok) {
    OSEVPF("count_data_leng\n");
    uint64 data_leng = 0x00;
    //
    uint32 vtype, sleng;
    char *style_str = numtok;
    while ('\0' != style_str[0x00]) {
        style_str = print_type(&vtype, &sleng, style_str);
        // CLIEPF("vtype:%d sleng:%d style_str:|%s|\n", vtype, sleng, style_str);
        switch (vtype) {
            case CHAR_TYP:
                data_leng += sleng;
                break;
            case STRI_TYP:
                data_leng += 0x08;
                break;
            default:
                data_leng += len_vtype_tab[vtype];
                break;
        }
    }
    //
    return data_leng;
}

// 0x00:OK -1:error

static int utili_pretty_varia(shel_resu *resul, char *numtok, char *query_data) {
    uint64 obje_leng = count_data_leng(numtok);
    char *posi_str = query_data;
    char *last_str = resul->resu_data;
    char *style_str;
    //
    uint64 data_size;
    char *obje_tail;
    int inde = 0x00;
    for (; resul->resu_leng > (posi_str - query_data); ++inde) {
        obje_tail = posi_str + obje_leng;
        style_str = numtok;
        data_size = 0x00;
        uint32 vtype, sleng;
        while ('\0' != style_str[0x00]) {
            style_str = print_type(&vtype, &sleng, style_str);
            // CLIEPF("vtype:%d sleng:%d style_str:|%s|\n", vtype, sleng, style_str);
            switch (vtype) {
                case CHAR_TYP:
                    last_str = prin_char_arra(last_str, posi_str, sleng);
                    posi_str += sleng;
                    break;
                case STRI_TYP:
                    last_str = prin_string(last_str, &data_size, posi_str, obje_tail);
                    posi_str += 0x08;
                    break;
                default:
                    last_str = prin_tab[vtype](last_str, posi_str);
                    posi_str += len_vtype_tab[vtype];
                    break;
            }
        }
        last_str = lscpy(last_str, "|\n");
        posi_str = obje_tail + data_size;
    }
    last_str = lsprif(last_str, "found %d objectes.\n", inde);
    resul->resu_leng = last_str - resul->resu_data;
    //
    return 0x00;
}

// 0x00:OK -1:error

int utili_pretty(char **paraep, shel_resu *resul) {
    if (resul->resu_type) return -1;
    if (LARGE_TEXT_SIZE < resul->resu_leng) {
        CliePrintErro("Result leng more than LARGE_TEXT_SIZE !", -1);
        return -1;
    }
    //
    char query_data[LARGE_TEXT_SIZE];
    memcpy(query_data, resul->resu_data, resul->resu_leng);
    quote_decode(paraep[0x00]);
    // chk_resdat_type
    char *style_str = paraep[0x00];
    for (; style_str[0x00]; ++style_str) {
        if ('S' == style_str[0x00]) {
            utili_pretty_varia(resul, paraep[0x00], query_data);
            return 0x00;
        }
    }
    //
    utili_pretty_fixed(resul, paraep[0x00], query_data);
    return 0x00;
}