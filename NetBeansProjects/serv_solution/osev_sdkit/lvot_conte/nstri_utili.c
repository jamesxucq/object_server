#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "invok_bzl.h"

#include "nstri_utili.h"

//

char *filli_relom_objen(char **obje_namp, char *_ofile_, char *basen, lev1_list *l1lst) {
    char handn[HANDN_LENGTH];
    char lev1_obje[MAX_PATH * 3];
    for (; l1lst; ++obje_namp, l1lst = l1lst->next) {
        BUILD_HANDN_BZL(handn, &l1lst->lev1m);
        TEMPORA_SUFFIX_FILE(lev1_obje, basen, handn, OBJEC_SUFFIX);
        LSCPY_O(obje_namp[0x00], lev1_obje, _ofile_);
    }
    obje_namp[0x00] = NULL;
    OSEVPF("[FUNC]:filli_relom_objen, _ofile_:|%s|\n", _ofile_);
    return _ofile_;
}

///

char *filli_reloc_objen(char **obje_namp, char *_ofile_, char *basen, lv2p_list *l2lst) {
    char lv2p_obje[MAX_PATH * 3];
    for (; l2lst; ++obje_namp, l2lst = l2lst->next) {
        TEMPORA_SUFFIX_FILE(lv2p_obje, basen, l2lst->lv2dt.lv2pn, OBJEC_SUFFIX);
        LSCPY_O(obje_namp[0x00], lv2p_obje, _ofile_);
    }
    obje_namp[0x00] = NULL;
    OSEVPF("[FUNC]:filli_reloc_objen, _ofile_:|%s|\n", _ofile_);
    return _ofile_;
}

//

void ulink_relom_objec(char *basen, lev1_list *l1lst) {
    char handn[HANDN_LENGTH];
    char lev1_obje[MAX_PATH * 3];
    for (; l1lst; l1lst = l1lst->next) {
        BUILD_HANDN_BZL(handn, &l1lst->lev1m);
        TEMPORA_SUFFIX_FILE(lev1_obje, basen, handn, OBJEC_SUFFIX);
        unlink(lev1_obje);
        OSEVPF("[FUNC]:ulink_relom_objec, lev1_obje:|%s|\n", lev1_obje);
    }
}

//

void ulink_reloc_objec(char *basen, lv2p_list *l2lst) {
    char lv2p_obje[MAX_PATH * 3];
    for (; l2lst; l2lst = l2lst->next) {
        TEMPORA_SUFFIX_FILE(lv2p_obje, basen, l2lst->lv2dt.lv2pn, OBJEC_SUFFIX);
        unlink(lv2p_obje);
        OSEVPF("[FUNC]:ulink_reloc_objec, lv2p_obje:|%s|\n", lv2p_obje);
    }
}

//

char *filli_osbsc_name(OUT char *osize, OUT char *bindn, OUT char *solvn, char *lv2pn) {
    osize = lccpy(osize, '_');
    osize = lscpy(osize, lv2pn);
    lscpy(osize, "_size_");
    //
    osize = lscpy(bindn, "_bind_");
    osize = lscpy(osize, lv2pn);
    lccpy(osize, '_');
    //
    osize = lscpy(solvn, "_solve_");
    osize = lscpy(osize, lv2pn);
    lccpy(osize, '_');
    //
    return osize;
}