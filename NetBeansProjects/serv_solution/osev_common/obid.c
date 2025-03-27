
#include "commo_macro.h"
#include "osev_datyp.h"
#include "osev_macro.h"
#include "linux_os.h"
#include "osev_atomic.h"
#include "encoding.h"
#include "osev_macro.h"
#include "stri_utili.h"

#include "obid.h"
#include "debug_funct_osv.h"

//
osv_oid_t INVA_OBID_VALU = {
    INVA_UINT_VALU, INVA_UINT_VALU, INVA_UINT_VALU
};

//
// seed ^= hash_value(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);

static size_t hash_combine(char *combi) {
    size_t seed = 0x9e3779b9;
    int slen = strlen(combi);
    unsigned int valu;
    unsigned int inde = 0x00;
    for (; slen > inde; inde += sizeof (unsigned int)) {
        memcpy(&valu, combi, sizeof (unsigned int));
        seed ^= valu + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        combi += sizeof (unsigned int);
    }
    //
    return seed;
}

//

osv_oid_t *creat_osev_obid(osv_oid_t *osev_obid) {
    char netw_info[SERVN_LENGTH];
    MK_ZERO(netw_info);
    if (network_info(netw_info)) random_salt((unsigned char *) netw_info);
    size_t machine_piece = hash_combine(netw_info);
    //
    pid_t process_piece = getpid();
    unsigned int gen_machine = machine_piece | process_piece;
    if (!gen_machine) gen_machine = 0x9e3779b9;
    //
    osev_obid->osev_unique = gen_machine;
    ((osv_oid_i *) osev_obid)->stoid = 0x00;
    return osev_obid;
}

char *creat_osev_name(char *osevn) {
    char netw_info[SERVN_LENGTH];
    MK_ZERO(netw_info);
    if (network_info(netw_info))
        random_salt((unsigned char *) netw_info);
    strcpy(osevn, netw_info);
    //
    return osevn;
}

// "fdeac7ec9a385a6304000000, fdeac7ec9a385a6304000000"

int split_oidst_enco(char *line_oid1, char *line_oid2, char *plain_obid) {
    char *toksp, *tokep;
    //
    toksp = plain_obid;
    for (; ' ' == toksp[0x00]; ++toksp);
    if ('\0' == toksp[0x00]) return -1;
    tokep = 0x01 + toksp;
    for (; ' ' != tokep[0x00] && ',' != tokep[0x00] && '\0' != tokep[0x00]; ++tokep);
    strzcpy(line_oid1, toksp, tokep - toksp);
    //
    toksp = tokep;
    for (; ' ' == toksp[0x00] || ',' == toksp[0x00]; ++toksp);
    if ('\0' == toksp[0x00]) return -1;
    tokep = 0x01 + toksp;
    for (; ' ' != tokep[0x00] && ',' != tokep[0x00] && '\0' != tokep[0x00]; ++tokep);
    strzcpy(line_oid2, toksp, tokep - toksp);
    //
    return 0x00;
}

// "fdeac7ec9a385a6304000000, fdeac7ec9a385a6304000000, fdeac7ec9a385a6304000000"
// return obid count

int comma_stroid(osv_oid_t *binary_obid, char *plain_obid) {
    char obid_stri[OBJE_IDENTI_ZLEN * MAX_SCONT_COUNT];
    char *toksp, *tokep;
    //
    tokep = plain_obid;
    unsigned int inde = 0x00;
    for (; MAX_SCONT_COUNT > inde; ++inde, ++binary_obid) {
        toksp = tokep;
        for (; ' ' == toksp[0x00] || ',' == toksp[0x00]; ++toksp);
        if ('\0' == toksp[0x00]) break;
        tokep = 0x01 + toksp;
        for (; ' ' != tokep[0x00] && ',' != tokep[0x00] && '\0' != tokep[0x00]; ++tokep);
        strzcpy(obid_stri, toksp, tokep - toksp);
        stroid(binary_obid, obid_stri);
    }
    //
    return inde;
}

// ("fdeac7ec9a385a6304000000")
// ("INVAL")
// ("ZERO")
// return obid count
#define OBID_VALUE_INVAL    "INVAL"
#define OBID_VALUE_ZERO     "ZERO"

int param_stroid_sing(osv_oid_t *binary_obid, char *plain_obid) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    char *toksp, *tokep;
    //
    toksp = plain_obid;
    for (; ' ' == toksp[0x00] || ',' == toksp[0x00] || '(' == toksp[0x00] \
                || ')' == toksp[0x00] || '"' == toksp[0x00] || ';' == toksp[0x00]; ++toksp);
    if ('\0' == toksp[0x00])
        return 0x00;
    tokep = 0x01 + toksp;
    for (; ' ' != tokep[0x00] && ',' != tokep[0x00] && '(' != tokep[0x00] \
                && ')' != tokep[0x00] && '"' != tokep[0x00] && '\0' != tokep[0x00]; ++tokep);
    strzcpy(obid_stri, toksp, tokep - toksp);
#ifdef _DEBUG
    printf("[FUNC]:param_stroid_sing => obid_stri:|%s|\n", obid_stri);
#endif // _DEBUG
    if (!strcmp(OBID_VALUE_INVAL, obid_stri))
        MAKE_INVAL_OBID(binary_obid)
    else if (!strcmp(OBID_VALUE_ZERO, obid_stri))
        MAKE_ZERO_OBID(binary_obid)
    else stroid(binary_obid, obid_stri);
    //
    return 0x01;
}

// ("fdeac7ec9a385a6304000000", "fdeac7ec9a385a6304000000")
// ("INVAL", "ZERO", "ZERO")
// return obid count

int param_stroid_mult(osv_oid_t *binary_obid, char *plain_obid) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    char *toksp, *tokep;
    //
    tokep = plain_obid;
    unsigned int inde = 0x00;
    for (; MAX_SCONT_COUNT > inde; ++inde, ++binary_obid) {
        toksp = tokep;
        for (; ' ' == toksp[0x00] || ',' == toksp[0x00] || '(' == toksp[0x00] \
                || ')' == toksp[0x00] || '"' == toksp[0x00] || ';' == toksp[0x00]; ++toksp);
        if ('\0' == toksp[0x00]) break;
        tokep = 0x01 + toksp;
        for (; ' ' != tokep[0x00] && ',' != tokep[0x00] && '(' != tokep[0x00] \
                && ')' != tokep[0x00] && '"' != tokep[0x00] && '\0' != tokep[0x00]; ++tokep);
        strzcpy(obid_stri, toksp, tokep - toksp);
        if (!strcmp(OBID_VALUE_INVAL, obid_stri))
            MAKE_INVAL_OBID(binary_obid)
        else if (!strcmp(OBID_VALUE_ZERO, obid_stri))
            MAKE_ZERO_OBID(binary_obid)
        else stroid(binary_obid, obid_stri);
    }
    //
    return inde;
}

