#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"

#include "lev1_meta.h"
#include "lev1_decla.h"
#include "lv2p_decla.h"

#include "lv2p_expand.h"

//

lv2p_expa_t *mallo_lv2exp(int lv2o_coun, int lv1d_coun) {
    lv2p_expa_t *lv2expt = (lv2p_expa_t *) malloc(sizeof (lv2p_expa_t));
    if (!lv2expt) return NULL;
    //
    lv2expt->lv2o_coun = 0x00;
    lv2expt->lv2nod = (lv2p_prop *) malloc(sizeof (lv2p_prop) * lv2o_coun);
    if (!lv2expt->lv2nod) {
        free(lv2expt);
        return NULL;
    }
    //
    lv2expt->lv1d_coun = 0x00;
    lv2expt->lv1dat = (lev1_decl_t *) malloc(sizeof (lev1_decl_t) * lv1d_coun);
    if (!lv2expt->lv1dat) {
        free(lv2expt->lv2nod);
        free(lv2expt);
        return NULL;
    }
    //
    return lv2expt;
}

//

static void crea_lev1_inne(OUT lev1_inne_t *tnnep, lev1_inne_i *innep) {
    // OSEVPF("[FUNC]:crea_lev1_inne\n");
    tnnep->inne_count = innep->inne_count;
    strcpy(tnnep->inne_fmtsp, innep->inne_fmtsp);
    //
    char *last_str = tnnep->_iline_;
    char **tparp = tnnep->inne_pams;
    char (*iparp)[PARAM_LENGTH] = innep->inne_pams;
    for (; (*iparp)[0x00]; ++tparp, ++iparp)
        LSCPY_O(tparp[0x00], iparp[0x00], last_str);
    tparp[0x00] = NULL;
}

static void crea_lev1_decl(OUT lev1_decl_t *tlv1d, lev1_decl_i *ilv1d) {
    // OSEVPF("[FUNC]:crea_lev1_decl\n");
    char **tinhp;
    char (*iinhp)[PARAM_LENGTH];
    //
    for (; LVTP_TYPE_NONE != ilv1d->levtyp; ++tlv1d, ++ilv1d) {
        tlv1d->levtyp = ilv1d->levtyp;
        strcpy(tlv1d->lv2pn, ilv1d->lv2pn);
        strcpy(tlv1d->ident, ilv1d->ident);
        //
        char *last_str = tlv1d->_cline_;
        tinhp = tlv1d->inhe_lv2n;
        iinhp = ilv1d->inhe_lv2n;
        for (; (*iinhp)[0x00]; ++tinhp, ++iinhp)
            LSCPY_O(tinhp[0x00], iinhp[0x00], last_str);
        tinhp[0x00] = NULL;
        //
        crea_lev1_inne(&tlv1d->innep, &ilv1d->innep);
    }
    tlv1d->levtyp = LVTP_TYPE_NONE;
}

//

lv2p_expa_t *creat_lv2exp(lv2p_expa_i *lv2expi) {
    // OSEVPF("[FUNC]:creat_lv2exp\n");
    lv2p_expa_t *lv2expt = (lv2p_expa_t *) malloc(sizeof (lv2p_expa_t));
    if (!lv2expt) return NULL;
    //
    lv2expt->lv2o_coun = lv2expi->lv2o_coun;
    lv2expt->lv2nod = (lv2p_prop *) MALLOC_NTAI(sizeof (lv2p_prop), lv2expi->lv2o_coun);
    if (!lv2expt->lv2nod) {
        free(lv2expt);
        return NULL;
    }
    MEMCPY_NTAI(lv2expt->lv2nod, lv2expi->lv2nod, sizeof (lv2p_prop), lv2expi->lv2o_coun);
    lv2expt->lv1d_coun = lv2expi->lv1d_coun;
    lv2expt->lv1dat = (lev1_decl_t *) MALLOC_NTAI(sizeof (lev1_decl_t), lv2expi->lv1d_coun);
    if (!lv2expt->lv1dat) {
        free(lv2expt->lv2nod);
        free(lv2expt);
        return NULL;
    }
    crea_lev1_decl(lv2expt->lv1dat, lv2expi->lv1dat);
    //
    return lv2expt;
}

//

