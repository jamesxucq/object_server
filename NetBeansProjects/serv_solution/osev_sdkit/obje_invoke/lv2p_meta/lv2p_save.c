#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "ostri_utili.h"
#include "lv2p_save.h"
#include "lv2p_expand.h"
#include "lev1_decla.h"

#include "trans/trans_utili.h"
#include "filli_clang.h"
#include "debug_funct_oi.h"

//
/*
<?xml version="1.0" encoding="UTF-8"?>
<lv2p_metada>
    <stora_id>b568e96500000000</stora_id>
    <lv2p_name>taat</lv2p_name>
    <lv2p_atti>
        <version>2</version>    
        <external>FALSE</external>
        <integrality></integrality>
    </lv2p_atti>
</lv2p_metada>
 */

/*
    <lev1 range="0x01" lv2pn="this">method name</lev1>
    <lev1 range="0x01" lv2pn="teet">method name</lev1>
 */

int crea_lv2p_attrib(char *lv2t_path, char *lv2pn, osv_oid_t *lv2p_obid) {
    OSEVPF("[FUNC]:crea_lv2p_attrib\n");
    char attrib_cont[LARGE_TEXT_SIZE];
    MK_ZERO(attrib_cont);
    char *last_str = lscpy(attrib_cont, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    char stoid_stri[STOR_IDENTI_ZLEN];
    last_str = lsprif(last_str, "<lv2p_metada><stora_id>%s</stora_id>", oid_sidstr(stoid_stri, lv2p_obid));
    last_str = lsprif(last_str, "<lv2p_name>%s</lv2p_name>", lv2pn);
    last_str = lscpy(last_str, "<lv2p_atti>");
    last_str = lsprif(last_str, "<version>%lu</version>", CLASS_INIT_VERSION);
    last_str = lsprif(last_str, "<external>%s</external>", BOOL_STRI_TAB[CLASS_INIT_INTERNAL]);
    last_str = lscpy(last_str, "<integrality>");
    last_str = lscpy(last_str, "</integrality>");
    last_str = lscpy(last_str, "</lv2p_atti></lv2p_metada>\n");
    if (save_data(lv2t_path, attrib_cont, TRUNCA_FILE))
        return -1;
    OSEVPF("[FUNC]:crea_lv2p_attrib attrib_cont:\n|%s|\n", attrib_cont);
    return 0x00;
}

int save_lv2p_attrib(char *lv2t_path, lv2p_attri *lv2ai) {
    char attrib_cont[LARGE_TEXT_SIZE];
    MK_ZERO(attrib_cont);
    char *last_str = lscpy(attrib_cont, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    char stoid_stri[STOR_IDENTI_ZLEN];
    last_str = lsprif(last_str, "<lv2p_metada><stora_id>%s</stora_id>", oid_sidstr(stoid_stri, &lv2ai->lv2p_obid));
    OSEVPF("oid_sidstr(stoid_stri, lv2p_obid):|%s|\n", stoid_stri);
    last_str = lsprif(last_str, "<lv2p_name>%s</lv2p_name>", lv2ai->lv2pn);
    last_str = lscpy(last_str, "<lv2p_atti>");
    last_str = lsprif(last_str, "<version>%lu</version>", lv2ai->versio);
    last_str = lsprif(last_str, "<external>%s</external>", BOOL_STRI_TAB[lv2ai->iexter]);
    last_str = lscpy(last_str, "<integrality>");
    integra *olist = lv2ai->integ_list;
    for (; olist; olist = olist->next)
        last_str = lsprif(last_str, "<lev1 range=\"%d\" lv2pn=\"%s\">%s</lev1>", olist->rang_type, olist->lv2pn, olist->lev1n);
    last_str = lscpy(last_str, "</integrality>");
    last_str = lscpy(last_str, "</lv2p_atti></lv2p_metada>\n");
    if (save_data(lv2t_path, attrib_cont, TRUNCA_FILE))
        return -1;
    OSEVPF("[FUNC]:save_lv2p_attrib attrib_cont:\n|%s|\n", attrib_cont);
    return 0x00;
}

// <inherit type="0x01" lev1="lev1_name" fmtsp="iii">lv2p_name</inherit>

int save_lv2p_inher(char *lv2t_path, inherit *inhe_list) {
    char attrib_cont[LARGE_TEXT_SIZE];
    MK_ZERO(attrib_cont);
    char *last_str = attrib_cont;
    inherit *ilist = inhe_list;
    for (; ilist; ilist = ilist->next) {
        last_str = lsprif(last_str, "<inherit range=\"%d\" lev1n=\"%s\">%s</inherit>", ilist->rang_type, ilist->lev1n, ilist->lv2pn);
    }
    if (save_data(lv2t_path, attrib_cont, FILE_APPEND))
        return -1;
    OSEVPF("[FUNC]:save_lv2p_inher attrib_cont:\n|%s|\n", attrib_cont);
    return 0x00;
}

int save_lv2p_decla(char *lv2d_path, char *lv2_dec) {
    char class_cont[LARGE_TEXT_SIZE];
    char *last_str = lscpy(class_cont, lv2_dec);
    lccpy(last_str, '\n');
    if (save_data(lv2d_path, class_cont, TRUNCA_FILE))
        return -1;
    return 0x00;
}

int save_lv2p_metho(char *lv2d_path, lv1_cont *l1lsnd) {
    char lev1_cont[LARGE_TEXT_SIZE];
    MK_ZERO(lev1_cont);
    char *last_str = lev1_cont;
    for (; l1lsnd; l1lsnd = l1lsnd->next) {
        last_str = lscpy(last_str, l1lsnd->conte);
        last_str = lccpy(last_str, '\n');
    }
    if (save_data(lv2d_path, lev1_cont, FILE_APPEND))
        return -1;
    return 0x00;
}

//

static void crea_lev1_inne(OUT lev1_inne_i *innep, lev1_inne_t *tnnep) {
    // OSEVPF("[FUNC]:crea_lev1_inne\n");
    innep->inne_count = tnnep->inne_count;
    strcpy(innep->inne_fmtsp, tnnep->inne_fmtsp);
    //
    char (*iparp)[PARAM_LENGTH] = innep->inne_pams;
    char **tparp = tnnep->inne_pams;
    for (; tparp[0x00]; ++iparp, ++tparp) strcpy(iparp[0x00], tparp[0x00]);
    MK_ZERO(iparp[0x00]);
}

static void crea_lev1_decl(OUT lev1_decl_i *ilv1d, lev1_decl_t *tlv1d) {
    // OSEVPF("[FUNC]:lev1_decl_dupl\n");
    char (*iinhp)[PARAM_LENGTH];
    char **tinhp;
    //
    for (; LVTP_TYPE_NONE != tlv1d->levtyp; ++ilv1d, ++tlv1d) {
        ilv1d->levtyp = tlv1d->levtyp;
        strcpy(ilv1d->lv2pn, tlv1d->lv2pn);
        strcpy(ilv1d->ident, tlv1d->ident);
        //
        iinhp = ilv1d->inhe_lv2n;
        tinhp = tlv1d->inhe_lv2n;
        for (; tinhp[0x00]; ++iinhp, ++tinhp) strcpy(iinhp[0x00], tinhp[0x00]);
        MK_ZERO(iinhp[0x00]);
        //
        crea_lev1_inne(&ilv1d->innep, &tlv1d->innep);
    }
    ilv1d->levtyp = LVTP_TYPE_NONE;
}

int save_lv2p_expand(char *lv2e_path, lv2p_expa_t *lv2expt) {
    OSEVPF("[FUNC]:save_lv2p_expand\n");
    lv2p_expa_i *lv2expi = (lv2p_expa_i *) malloc(sizeof (lv2p_expa_i));
    if (!lv2expi) return -1;
    //
    lv2expi->lv2o_coun = lv2expt->lv2o_coun;
    MEMCPY_NTAI(lv2expi->lv2nod, lv2expt->lv2nod, sizeof (lv2p_prop), lv2expt->lv2o_coun);
    lv2expi->lv1d_coun = lv2expt->lv1d_coun;
    crea_lev1_decl(lv2expi->lv1dat, lv2expt->lv1dat);
    // PRIN_lv2p_expa_i(lv2expi);
    if (bina_save_data(lv2e_path, (char *) lv2expi, sizeof (lv2p_expa_i), TRUNCA_FILE)) {
        free(lv2expi);
        return -1;
    }
    //
    free(lv2expi);
    return 0x00;
}
