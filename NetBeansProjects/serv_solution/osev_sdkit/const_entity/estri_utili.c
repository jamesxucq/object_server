
#include "commo_header.h"
#include "estri_utili.h"

//

char *filli_const_handn(char *handn, char *lv2pn, char **pamvp) {
    handn = lscpy(handn, lv2pn);
    handn = lccpy(handn, '_');
    handn = lscpy(handn, lv2pn);
    handn = lccpy(handn, '_');
    //
    for (; NULL != pamvp[0x00]; ++pamvp) {
        OSEVPF("[FUNC]:filli_const_handn valu:|%d|\n", (int) ((unsigned char *) pamvp[0x00])[0x00]);
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
                _LOG_WARN("default: DATY_INVAL");
                return NULL;
                break;
        }
    }
    //
    return handn;
}

//

int is_lv2p_decl(char *lv2p_cont) {
    char *matok = strchr(lv2p_cont, '<');
    if (!matok) return -1;
    matok = strchr(++matok, '>');
    if (!matok) return -1;
    //
    return 0x00;
}
