
#include "commo_header.h"
#include "kcomm_header.h"
#include "stat_respo.h"

//

void list_lv2p_attri(respo_ctrl *resctl, lv2p_attri *lv2ai) {
    char *last_str = lscpy(resctl->posi_resp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
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
    PDAT_LASTPOS_PCAT(resctl, last_str)
}

//

static char *lev1_decla(char *decla, char *meth_data) {
    char *detok = strchr(meth_data, '<');
    if (!detok) return NULL;
    detok = strchr(detok + 0x01, '>');
    if (!detok) return NULL;
    decla = lszcpy(decla, meth_data, detok - meth_data + 0x01);
    decla = lscpy(decla, ";\n");
    // OSEVPF("decla:|%s|\n", decla);
    return decla;
}

void list_lv2p_meta(respo_ctrl *resctl, lv2p_decl_i *lv2di) {
    char *last_str = lscpy(resctl->posi_resp, lv2di->lv2p_decl);
    last_str = lccpy(last_str, '\n');
    //
    lv1_cont *l1lsnd = lv2di->l1con_list;
    while (l1lsnd) {
        last_str = lev1_decla(last_str, l1lsnd->conte);
        l1lsnd = l1lsnd->next;
    }
    //
    PDAT_LASTPOS_PCAT(resctl, last_str)
}

//

/*
<?xml version="1.0" encoding="UTF-8"?>
<lv2p_expand>
    <lv2p_conte lv2o_coun=3>
        <lv2p_prop attri=1 type="int" size=0 decla="xx int" >xx</lv2p_prop>
        <lv2p_prop attri=1 type="int" size=0 decla="ax int" >ax</lv2p_prop>
        <lv2p_prop attri=1 type="int" size=0 decla="cx int" >cx</lv2p_prop>
    </lv2p_conte>
    <lev1_decla lv1d_coun=1>
        <lev1_meth levtyp=1 lv2pn="txxt" ident="">
            <inhe_lv2n>
                <lv2n>cx</lv2n>
                <lv2n>ax</lv2n>
            </inhe_lv2n>
            <lev1_inne inne_fmtsp="iii" inne_coun=3>
                <parm>cx</parm>
                <parm>ax</parm>
                <parm>xx</parm>
            </lev1_inne>
        </lev1_meth>
    </lev1_decla>
</lv2p_expand>
 */

static char *lev1_declare(char *lev1_decl, lev1_decl_t *lev1d) {
    lev1_decl = lsprif(lev1_decl, "<lev1_meth levtyp=%d lv2pn=\"%s\" ident=\"%s\">"
            , lev1d->levtyp, lev1d->lv2pn, lev1d->inhe_lv2n, lev1d->ident);
    char **ilv2np = lev1d->inhe_lv2n;
    if (ilv2np[0x00]) {
        lev1_decl = lscpy(lev1_decl, "<inhe_lv2n>");
        for (; ilv2np[0x00]; ++ilv2np)
            lev1_decl = lsprif(lev1_decl, "<ilv2n>%s</ilv2n>", ilv2np[0x00]);
        lev1_decl = lscpy(lev1_decl, "</inhe_lv2n>");
    }
    lev1_decl = lsprif(lev1_decl, "<lev1_inne inne_fmtsp=\"%s\" inne_coun=%d>"
            , lev1d->innep.inne_fmtsp, lev1d->innep.inne_count);
    char **innep = lev1d->innep.inne_pams;
    for (; innep[0x00]; ++innep)
        lev1_decl = lsprif(lev1_decl, "<parm>%s</parm>", innep[0x00]);
    lev1_decl = lscpy(lev1_decl, "</lev1_inne></lev1_meth>");
    //
    return lev1_decl;
}

void list_lv2p_expand(respo_ctrl *resctl, lv2p_expa_t *lv2expt) {
    OSEVPF("[FUNC]:list_lv2p_expand\n");
    // printf("lv2expt->lv2o_coun:|%d|\n", lv2expt->lv2o_coun);
    char *last_str = lscpy(resctl->posi_resp, LIST_XML_HEAD);
    last_str = lscpy(last_str, "<lv2p_expand>");
    if (lv2expt->lv2o_coun) {
        last_str = lsprif(last_str, "<lv2p_conte lv2o_coun=%d>", lv2expt->lv2o_coun);
        lv2p_prop *lv2nod = lv2expt->lv2nod;
        for (; ACCE_COTRL_INVAL != lv2nod->access; ++lv2nod) {
            last_str = lsprif(last_str, "<lv2p_prop attri=%u type=\"%s\" size=%u decla=\"%s\" >%s</lv2p_prop>"
                    , lv2nod->access, potyp_ostyp_tab[lv2nod->potyp], lv2nod->size, lv2nod->decla, lv2nod->name);
        }
        last_str = lscpy(last_str, "</lv2p_conte>");
    }
    if (lv2expt->lv1d_coun) {
        last_str = lsprif(last_str, "<lev1_decla lv1d_coun=%d>", lv2expt->lv1d_coun);
        // printf("lv2expt->lv1d_coun:|%d|\n", lv2expt->lv1d_coun);
        lev1_decl_t *lv1d = lv2expt->lv1dat;
        for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
            last_str = lev1_declare(last_str, lv1d);
        }
        last_str = lscpy(last_str, "</lev1_decla>");
    }
    last_str = lscpy(last_str, "</lv2p_expand>");
    //
    PDAT_LASTPOS_PCAT(resctl, last_str)
}

/*
<?xml version="1.0" encoding="UTF-8"?>
    <integrality>
        <lev1 range="1" lv2pn="taat">tpp</lev1>
    </integrality>
 */

void list_lv2p_lolst(respo_ctrl *resctl, integra *olist) {
    char *last_str = lscpy(resctl->posi_resp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    last_str = lscpy(last_str, "<integrality>");
    for (; olist; olist = olist->next)
        last_str = lsprif(last_str, "<lev1 range=\"%d\" lv2pn=\"%s\">%s</lev1>", olist->rang_type, olist->lv2pn, olist->lev1n);
    resctl->posi_resp = lscpy(last_str, "</integrality>");
}

/*
void list_lv2p_lolst(respo_ctrl *resctl, integra *olist) {
    for (; olist; olist = olist->next) {
        // OSEVPF("olist->lev1_name:|%s|\n", olist->lev1_name);
        resctl->posi_resp = lsprif(resctl->posi_resp, "%04X ", olist->rang_type);
        resctl->posi_resp = lscpy(resctl->posi_resp, olist->lv2pn);
        resctl->posi_resp = lccpy(resctl->posi_resp, ':');
        resctl->posi_resp = lscpy(resctl->posi_resp, olist->lev1n);
        resctl->posi_resp = lccpy(resctl->posi_resp, '(');
        resctl->posi_resp = lscpy(resctl->posi_resp, ")\n");
    }
}
 */

//

void list_lev1_lv2p(respo_ctrl *resctl, lv1_cont *l1lsnd) {
    char *last_str = (char *) resctl->resp_memo;
    for (; l1lsnd; l1lsnd = l1lsnd->next) {
        OSEVPF("22 conte:|%s|\n", l1lsnd->conte);
        last_str = lscpy(last_str, l1lsnd->conte);
        last_str = lccpy(last_str, '\n');
    }
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

void list_lev1_iden(respo_ctrl *resctl, char *lev1n, lv1_cont *l1lsnd) {
    char *last_str = (char *) resctl->resp_memo;
    OSEVPF("21\n");
    l1lsnd = find_l1cnod_name(l1lsnd, lev1n);
    for (; l1lsnd; l1lsnd = find_l1cnod_name(l1lsnd->next, lev1n)) {
        OSEVPF("22 conte:|%s|\n", l1lsnd->conte);
        last_str = lscpy(last_str, l1lsnd->conte);
        last_str = lccpy(last_str, '\n');
    }
    OSEVPF("23\n");
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

void list_lev1_fmtsp(respo_ctrl *resctl, char *lev1n, char *fmtsop, lv1_cont *l1lsnd) {
    char *last_str = (char *) resctl->resp_memo;
    for (; (l1lsnd = find_l1cnod_iden(l1lsnd, lev1n, fmtsop)); l1lsnd = l1lsnd->next) {
        last_str = lscpy(last_str, l1lsnd->conte);
        last_str = lccpy(last_str, '\n');
    }
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

