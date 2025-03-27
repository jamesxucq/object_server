#include "commo_header.h"

// #include "kcomm_directory.h"
#include "lev1_decla.h"
#include "lv2p_decla.h"
#include "kcstr_utili.h"
// #include "leve_list.h"
// #include "debug_funct_co.h"

//

lev1_decl_t *find_lev1d(lev1_decl_t *lev1d, lev1_decl_t *lv1d) {
    for (; LVTP_TYPE_NONE != lev1d->levtyp; ++lev1d) {
        if (!comp_stri_array(lev1d->inhe_lv2n, lv1d->inhe_lv2n)
                && !strcmp(lev1d->ident, lv1d->ident)
                && !strcmp(lev1d->innep.inne_fmtsp, lv1d->innep.inne_fmtsp))
            return lev1d;
    }
    return NULL;
}

//

lev1_decl_t *find_lev1d_iden(lev1_decl_t *lv1d, char *lv2pn, char *lev1n) {
    // OSEVPF("find_lev1d_iden lv2pn:|%s| lev1n:|%s|\n", lv2pn, lev1n);
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        // PRIN_lev1d_debug(lv1d);
        if (!strcmp(lv1d->lv2pn, lv2pn)
                && !lv1d->inhe_lv2n[0x00]
                && !strcmp(lv1d->ident, lev1n))
            return lv1d;
    }
    return NULL;
}

//

lev1_decl_t *find_lev1d_lv1n(lev1_decl_t *lv1d, char *lev1n) {
    // OSEVPF("find_lev1d_iden lv2pn:|%s| lev1n:|%s|\n", lv2pn, lev1n);
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        // PRIN_lev1d_debug(lv1d);
        if (!strcmp(lv1d->ident, lev1n))
            return lv1d;
    }
    return NULL;
}

//

int gener_acces_cotrl(char *acce_cont) {
    // !acce_cont[0x00]: default ACCE_COTRL_AUTO
    if (!acce_cont[0x00] || !strcasecmp("AUTO", acce_cont))
        return ACCE_COTRL_AUTO;
    else if (!strcasecmp("INVISI", acce_cont))
        return ACCE_COTRL_INVISI;
    else if (!strcasecmp("HIDE", acce_cont))
        return ACCE_COTRL_HIDE;
    //
    return ACCE_COTRL_INVAL;
}

//

static void dupl_lev1_inne(OUT lev1_inne_t *dinnep, lev1_inne_t *sinnep) {
    OSEVPF("[FUNC]:dupl_lev1_inne\n");
    dinnep->inne_count = sinnep->inne_count;
    strcpy(dinnep->inne_fmtsp, sinnep->inne_fmtsp);
    //
    char *last_str = dinnep->_iline_;
    char **dparp = dinnep->inne_pams;
    char **sparp = sinnep->inne_pams;
    for (; sparp[0x00]; ++dparp, ++sparp)
        LSCPY_O(dparp[0x00], sparp[0x00], last_str);
    dparp[0x00] = NULL;
}

void dupl_lev1_decl(OUT lev1_decl_t *des_lv1d, lev1_decl_t *src_lv1d) {
    OSEVPF("[FUNC]:dupl_lev1_decl\n");
    char **dinhp;
    char **sinhp;
    //
    for (; LVTP_TYPE_NONE != src_lv1d->levtyp; ++des_lv1d, ++src_lv1d) {
        des_lv1d->levtyp = src_lv1d->levtyp;
        strcpy(des_lv1d->lv2pn, src_lv1d->lv2pn);
        strcpy(des_lv1d->ident, src_lv1d->ident);
        //
        char *last_str = des_lv1d->_cline_;
        dinhp = des_lv1d->inhe_lv2n;
        sinhp = src_lv1d->inhe_lv2n;
        for (; sinhp[0x00]; ++dinhp, ++sinhp)
            LSCPY_O(dinhp[0x00], sinhp[0x00], last_str);
        dinhp[0x00] = NULL;
        //
        dupl_lev1_inne(&des_lv1d->innep, &src_lv1d->innep);
    }
    des_lv1d->levtyp = LVTP_TYPE_NONE;
}

//

lev1_decl_t *appe_lev1_decl(OUT lev1_decl_t *lev1d, lev1_decl_t *lv1d) {
    OSEVPF("[FUNC]:appe_lev1_decl\n");
    // memcpy(lev1d, lv1d, sizeof (lev1_decl_t));
    dupl_lev1_decl(lev1d, lv1d);
    (++lev1d)->levtyp = LVTP_TYPE_NONE;
    return lev1d;
}

