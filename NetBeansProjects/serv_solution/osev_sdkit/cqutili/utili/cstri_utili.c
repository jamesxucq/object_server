#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "commo_header.h"
#include "cstri_utili.h"

//

char *qinvo_parms(pams_invk *pamivk, char *pamcon) {
    char *last_str = pamivk->_sline_;
    char *tokep, *toksp = strpar(pamcon);
    //
    OSEVPF("pamcon:|%s|\n", pamcon);
    char *pamvu = pamivk->pamvp[0x00];
    // unsigned int inde;
    for (; toksp; ++pamvu) {
        tokep = strpbrk(toksp + 0x01, " ,");
        if (tokep) {
            LSZCPY_O(pamvu, toksp, tokep - toksp, last_str)
            toksp = strpar(tokep + 0x01);
            OSEVPF("pamvu:|%s|\n", pamvu);
        } else {
            LSCPY_O(pamvu, toksp, last_str)
            toksp = NULL;
            OSEVPF("pamvu:|%s|\n", pamvu);
        }
    }
    pamvu = NULL;
    //
    return pamivk->_sline_;
}

//

char *split_qinvo(char *objide, char *meth_str, char *pamcon, char *meth_line) {
    char *toksp;
    PASS_TBLANK(toksp, meth_line)
            char *toknp = strchr(toksp, ':');
    if (!toknp) return NULL;
    char *tokep = strpbrk(toknp, " (");
    if (!tokep) return NULL;
    //
    strzcpy(objide, toksp, toknp - toksp);
    toknp++;
    strzcpy(meth_str, toknp, tokep - toknp);
    MK_ZERO(pamcon);
    if ('(' != tokep[0x00]) {
        tokep = strchr(tokep, '(');
        if (!tokep) return NULL;
    }
    ++tokep;
    toksp = qstrch(tokep, ')');
    if (!toksp) return NULL;
    strzcpy(pamcon, tokep, toksp - tokep);
    //
    return objide;
}

//

static int decode_invop(pams_invk *pamivk, char *invop_str) {
    // OSEVPF("[FUNC]:decode_invop\n");
    unsigned long long req_len;
    invop_str = unpak_conte_leng(&req_len, invop_str);
    if (!invop_str) {
        pamivk->pamvp[0x00] = NULL;
        return -1;
    }
    // OSEVPF("req_len:|%llu|\n", req_len);
    if (!decod_binary_loop(pamivk->pamvp, pamivk->_sline_, invop_str, req_len)) {
        pamivk->pamvp[0x00] = NULL;
        return -1;
    }
    //
    return 0x00;
}

int decode_invok_parms(char *lv2pn, char *lev1n, pams_invk *pamivk, char *invop_str) {
    // OSEVPF("[FUNC]:decode_invok_parms\n");
    char *pase_tok = unpak_binary_conte(invop_str);
    if (!pase_tok) return -1;
    //
    char pamcon[PARAM_LENGTH];
    pase_tok = pamstyl_stri(pamcon, pase_tok);
    if (!pase_tok) return -1;
    if (IS_ZERO(pamcon)) MK_ZERO(lv2pn);
    else strcpy(lv2pn, pamcon);
    // OSEVPF("lv2pn:|%s|\n", lv2pn);
    pase_tok = pamstyl_stri(pamcon, pase_tok);
    if (!pase_tok) return -1;
    strcpy(lev1n, pamcon);
    // OSEVPF("lev1n:|%s|\n", lev1n);
    if (decode_invop(pamivk, pase_tok))
        return -1;
    // OSEVPF("pamvp[0x00]:|%d| pamvp[0x01]:|%d|\n", ((int_entit *) pamivk->pamvp[0x00])->data, ((int_entit *) pamivk->pamvp[0x01])->data);
    return 0x00;
}

//
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

/*
static const char *vari_type_tab[] = {
    "int",
    "short",
    "long",
    "char",
    "float",
    "double",
    NULL
};
 */

char *filli_binary_handn(char *handn, char *lv2pn, char *lev1n, char **pamvp) {
    handn = lscpy(handn, lv2pn);
    handn = lccpy(handn, '_');
    handn = lscpy(handn, lev1n);
    handn = lccpy(handn, '_');
    //
    for (; NULL != pamvp[0x00]; ++pamvp) {
        OSEVPF("filli_binary_handn valu:|%d|\n", (int) ((unsigned char *) pamvp[0x00])[0x00]);
        switch (((unsigned char *) pamvp[0x00])[0x00]) {
            case DATY_INVAL:
                _LOG_WARN("case: DATY_INVAL");
                return NULL;
                break;
            case DATY_BYTE:
                handn = lccpy(handn, 'b');
                break;
            case DATY_UBYTE:
                handn = lccpy(handn, 'B');
                break;
            case DATY_SHORT:
                handn = lccpy(handn, 'h');
                break;
            case DATY_USHORT:
                handn = lccpy(handn, 'H');
                break;
            case DATY_INT:
                handn = lccpy(handn, 'i');
                break;
            case DATY_UINT:
                handn = lccpy(handn, 'I');
                break;
            case DATY_LLONG:
                handn = lccpy(handn, 'q');
                break;
            case DATY_ULLONG:
                handn = lccpy(handn, 'Q');
                break;
            case DATY_OBID:
                handn = lccpy(handn, 'o');
                break;
            case DATY_FLOAT:
                handn = lccpy(handn, 'f');
                break;
            case DATY_DOUBLE:
                handn = lccpy(handn, 'd');
                break;
            case DATY_STRI:
                handn = lccpy(handn, 's');
                break;
            case DATY_STRZ:
                handn = lccpy(handn, 'S');
                break;
            case DATY_BINARY:
                handn = lccpy(handn, 'e');
                break;
            default:
                _LOG_WARN("default: valu[0x00]");
                return NULL;

                break;
        }
    }
    //
    return handn;
}

//

int split_invok(char *iclan, char *imetn, char *invop, char *lv2pn) {
    char *toksp;
    PASS_TBLANK(toksp, invop)
            char *tokep = strchr(toksp, ':');
    if (tokep == toksp) {
        strcpy(iclan, lv2pn);
        strcpy(imetn, pass_blank(++tokep));
    } else if (tokep) {
        strzcpy(iclan, toksp, tokep - toksp);
        strcpy(imetn, pass_blank(++tokep));
    } else {
        strcpy(iclan, lv2pn);
        strcpy(imetn, toksp);
    }
    return 0x00;
}

//
