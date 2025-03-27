
#include "commo_header.h"
#include "kcomm_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"
#include "plan/plan_node_ensi.h"
#include "plan/plan_node_enco.h"

#include "utili/cstri_utili.h"
#include "ustri_utili.h"

char *filli_origi_handn(char *handn, char *lv2pn, char *lev1n, leaf_list *leli) {
    handn = lscpy(handn, lv2pn);
    handn = lccpy(handn, '_');
    handn = lscpy(handn, lev1n);
    handn = lccpy(handn, '_');
    //
    for (; leli; leli = leli->next) {
        switch (check_pamvu_nodtyp(leli->leno->stri_valu)) {
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
                _LOG_WARN("default: stri_valu");
                return NULL;
                break;
        }
    }
    //
    return handn;
}

//

int creat_binary_parms(pams_invk *pamivk, leaf_list *leli) {
    char *last_str = pamivk->_sline_;
    char **pamvp = pamivk->pamvp;
    //
    char pscon[LINE_LENGTH];
    unsigned long long colen;
    for (; leli; leli = leli->next, ++pamvp) {
        colen = encod_list_once(pscon, leli->leno->stri_valu);
        OSEVPF("creat_binary_parms\n");
        if (INVA_ULOLO_VALU == colen)
            return -1;
        LAMCPY_BIN(pamvp[0x00], pscon, colen, last_str);
    }
    pamvp[0x00] = NULL;
    //
    return 0x00;
}

