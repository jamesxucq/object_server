
#include "commo_header.h"
#include "kcomm_header.h"
#include "post_respo.h"

// trans-serve
#define POST_XML_HEAD "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"

//

/*
<?xml version="1.0" encoding="UTF-8"?>
<lv2p_explain>
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
</lv2p_explain>
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

//

void post_lv2p_explain(respo_ctrl *resctl, lv2p_expa_t *lv2expt) {
    OSEVPF("[FUNC]:post_lv2p_explain\n");
    // printf("lv2expt->lv2o_coun:|%d|\n", lv2expt->lv2o_coun);
    char *last_str = lscpy((char *) resctl->resp_memo, POST_XML_HEAD);
    last_str = lscpy(last_str, "<lv2p_explain>");
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
    last_str = lscpy(last_str, "</lv2p_explain>");
    // PDAT_LASTPOS_PCAT(resctl, last_str)
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

//

/*
<?xml version="1.0" encoding="UTF-8"?>
<inher_exter>
    <lv2pn>txxt</lv2pn>
</inher_exter>
 */

void post_lv2p_iexter(respo_ctrl *resctl, char *iexte_lv2pn) {
    OSEVPF("[FUNC]:post_lv2p_iexter\n");
    char *last_str = lscpy((char *) resctl->resp_memo, POST_XML_HEAD);
    last_str = lscpy(last_str, "<inher_exter>");
    if (iexte_lv2pn[0x00])
        last_str = lsprif(last_str, "<lv2pn>%s</lv2pn>", iexte_lv2pn);
    last_str = lscpy(last_str, "</inher_exter>");
    // PDAT_LASTPOS_PCAT(resctl, last_str)
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}
