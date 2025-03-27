
#include "commo_header.h"

#include "../common/ccomm_types.h"
#include "parse_expand.h"
#include "../../debug_funct_sh.h"

//
static osv_str_t START_LVTPCONT_LABEL = osv_stri("<lv2p_conte");
static osv_str_t LVTPD_COUNT_LABEL = osv_stri("lv2o_coun");
static osv_str_t END_LVTPCONT_LABEL = osv_stri("</lv2p_conte>");

static osv_str_t START_LVTPPROP_LABEL = osv_stri("<lv2p_prop");
static osv_str_t LVTPN_ATTRI_LABEL = osv_stri("attri");
static osv_str_t LVTPN_TYPE_LABEL = osv_stri("type");
static osv_str_t LVTPN_SIZE_LABEL = osv_stri("size");
static osv_str_t LVTPN_DECLA_LABEL = osv_stri("decla");
static osv_str_t END_LVTPNODE_LABEL = osv_stri("</lv2p_prop>");

//
static osv_str_t START_LEVODECL_LABEL = osv_stri("<lev1_decla");
static osv_str_t LEVOD_COUNT_LABEL = osv_stri("lv1d_coun");
static osv_str_t END_LEVODECL_LABEL = osv_stri("</lev1_decla>");

static osv_str_t START_LEVOMETH_LABEL = osv_stri("<lev1_meth");
static osv_str_t LVTPN_LVTPYP_LABEL = osv_stri("levtyp");
static osv_str_t LVTPN_LVTPN_LABEL = osv_stri("lv2pn");
static osv_str_t LVTPN_IDENT_LABEL = osv_stri("ident");
static osv_str_t END_LEVONODE_LABEL = osv_stri("</lev1_meth>");

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

char *parse_lv2expt_count(lv2p_expa_t *lv2expt, char *lv2e_cont) {
    // CLIEPF("[FUNC]:parse_lv2expt_count\n");
    char atval[ATTRIB_LENGTH];
    char *pase_tok;
    //
    pase_tok = lv2e_cont;
    GET_ATTRIB_VALUE(atval, pase_tok, START_LVTPCONT_LABEL, LVTPD_COUNT_LABEL)
    if (!pase_tok) return NULL;
    lv2expt->lv2o_coun = atoi(atval);
    // 
    GET_ATTRIB_VALUE(atval, pase_tok, START_LEVODECL_LABEL, LEVOD_COUNT_LABEL)
    if (!pase_tok) return NULL;
    lv2expt->lv1d_coun = atoi(atval);
    //
    return lv2e_cont;
}

//

/*
        <lv2p_prop attri=1 type="int" size=0 decla="xx int" >xx</lv2p_prop>
        <lv2p_prop attri=1 type="int" size=0 decla="ax int" >ax</lv2p_prop>
        <lv2p_prop attri=1 type="int" size=0 decla="cx int" >cx</lv2p_prop>
 */

static char *parse_lv2p_conte(lv2p_prop *lv2nod, char *lv2p_conte) {
    // CLIEPF [FUNC]:parse_lv2p_conte\n");
    // CLIEPF("lv2p_conte:|%s|\n", lv2p_conte);
    char atval1[ATTRIB_LENGTH], atval2[ATTRIB_LENGTH], atval3[ATTRIB_LENGTH], atval4[ATTRIB_LENGTH];
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    // OSEVPF("inte_data:|%s|\n", inte_data);
    pase_tok = lv2p_conte;
    GET_FATTRIB_ELEMENT_VALUE(atval1, atval2, atval3, atval4, elem_valu, pase_tok, START_LVTPPROP_LABEL, LVTPN_ATTRI_LABEL, LVTPN_TYPE_LABEL, LVTPN_SIZE_LABEL, LVTPN_DECLA_LABEL, END_LVTPNODE_LABEL)
    while (pase_tok) {
        lv2nod->access = atoi(atval1);
        // strcpy(lv2nod->type, atval2);
        KV_STIN_EQUA(lv2nod->potyp, ostyp_potyp_dict, atval2)
        lv2nod->size = atoi(atval3);
        strcpy(lv2nod->decla, atval4);
        strcpy(lv2nod->name, elem_valu);
        // OSEVPF("onnod->lev1_name:|%s| pase_tok:%08X\n", onnod->lev1n, pase_tok);
        GET_FATTRIB_ELEMENT_VALUE(atval1, atval2, atval3, atval4, elem_valu, pase_tok, START_LVTPPROP_LABEL, LVTPN_ATTRI_LABEL, LVTPN_TYPE_LABEL, LVTPN_SIZE_LABEL, LVTPN_DECLA_LABEL, END_LVTPNODE_LABEL)
                ++lv2nod;
    }
    lv2nod->access = ACCE_COTRL_INVAL;
    //
    return lv2p_conte;
}

//

static osv_str_t START_LVTPN_LABEL = osv_stri("<lv2n>");
static osv_str_t END_LVTPN_LABEL = osv_stri("</lv2n>");
static osv_str_t START_PARAM_LABEL = osv_stri("<parm>");
static osv_str_t END_PARAM_LABEL = osv_stri("</parm>");

/*
                <lv2n>cx</lv2n>
                <lv2n>ax</lv2n>
 */

static char *parse_lev1_inhe(char **inhe_lv2n, char *_cline_, char *lev1_inhe) {
    // CLIEPF("[FUNC]:parse_lev1_inhe\n");
    // CLIEPF("lev1_inhe:|%s|\n", lev1_inhe);
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    char **ilv2n = inhe_lv2n;
    pase_tok = lev1_inhe;
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_LVTPN_LABEL, END_LVTPN_LABEL)
    while (pase_tok) {
        LSCPY_O(ilv2n[0x00], elem_valu, _cline_);
        GET_ELEMENT_VALUE(elem_valu, pase_tok, START_LVTPN_LABEL, END_LVTPN_LABEL)
                ++ilv2n;
    }
    ilv2n[0x00] = NULL;
    //
    return lev1_inhe;
}

/*
                <parm>cx</parm>
                <parm>ax</parm>
                <parm>xx</parm>
 */

static char *parse_lev1_inne(lev1_inne_t *innep, char *lev1_inne) {
    // CLIEPF("[FUNC]:parse_lev1_inne\n");
    // CLIEPF("lev1_inne:|%s|\n", lev1_inne);
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    char **iparms = innep->inne_pams;
    char *last_str = innep->_iline_;
    pase_tok = lev1_inne;
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_PARAM_LABEL, END_PARAM_LABEL)
    while (pase_tok) {
        LSCPY_O(iparms[0x00], elem_valu, last_str);
        GET_ELEMENT_VALUE(elem_valu, pase_tok, START_PARAM_LABEL, END_PARAM_LABEL)
                ++iparms;
    }
    iparms[0x00] = NULL;
    //
    return lev1_inne;
}

//
static osv_str_t START_INHELVTN_LABEL = osv_stri("<inhe_lv2n>");
static osv_str_t END_INHELVTN_LABEL = osv_stri("</inhe_lv2n>");

static osv_str_t START_LEVOINNE_LABEL = osv_stri("<lev1_inne");
static osv_str_t LVTPN_INNEFMTSP_LABEL = osv_stri("inne_fmtsp");
static osv_str_t LVTPN_INNECOUN_LABEL = osv_stri("inne_coun");
static osv_str_t END_LEVOINNE_LABEL = osv_stri("</lev1_inne>");

/*
            <inhe_lv2n>
                <lv2n>cx</lv2n>
                <lv2n>ax</lv2n>
            </inhe_lv2n>
            <lev1_inne inne_fmtsp="iii" inne_coun=3>
                <parm>cx</parm>
                <parm>ax</parm>
                <parm>xx</parm>
            </lev1_inne>
 */

static char *parse_lev1_node(lev1_decl_t *lv1dat, char *lev1_meth) {
    // CLIEPF("[FUNC]:parse_lev1_node\n");
    // CLIEPF("lev1_meth:|%s|\n", lev1_meth);
    char atval1[ATTRIB_LENGTH], atval2[ATTRIB_LENGTH];
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    pase_tok = lev1_meth;
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_INHELVTN_LABEL, END_INHELVTN_LABEL)
    if (pase_tok) {
        if (!parse_lev1_inhe(lv1dat->inhe_lv2n, lv1dat->_cline_, elem_valu))
            return NULL;
    } else pase_tok = lev1_meth;
    //
    GET_TATTRIB_ELEMENT_VALUE(atval1, atval2, elem_valu, pase_tok, START_LEVOINNE_LABEL, LVTPN_INNEFMTSP_LABEL, LVTPN_INNECOUN_LABEL, END_LEVOINNE_LABEL)
    if (pase_tok) {
        strcpy(lv1dat->innep.inne_fmtsp, atval1);
        lv1dat->innep.inne_count = atoi(atval2);
        if (!parse_lev1_inne(&lv1dat->innep, elem_valu))
            return NULL;
    }
    //
    return lev1_meth;
}

/*
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
 */

static char *parse_lev1_decla(lev1_decl_t *lv1dat, char *lev1_decl) {
    // CLIEPF("[FUNC]:parse_lev1_decla\n");
    // CLIEPF("lev1_decl:|%s|\n", lev1_decl);
    char atval1[ATTRIB_LENGTH], atval2[ATTRIB_LENGTH], atval3[ATTRIB_LENGTH];
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    pase_tok = lev1_decl;
    GET_HATTRIB_ELEMENT_VALUE(atval1, atval2, atval3, elem_valu, pase_tok, START_LEVOMETH_LABEL, LVTPN_LVTPYP_LABEL, LVTPN_LVTPN_LABEL, LVTPN_IDENT_LABEL, END_LEVONODE_LABEL)
    while (pase_tok) {
        lv1dat->levtyp = atoi(atval1);
        strcpy(lv1dat->lv2pn, atval2);
        strcpy(lv1dat->ident, atval3);
        if (!parse_lev1_node(lv1dat, elem_valu))
            return NULL;
        GET_HATTRIB_ELEMENT_VALUE(atval1, atval2, atval3, elem_valu, pase_tok, START_LEVOMETH_LABEL, LVTPN_LVTPYP_LABEL, LVTPN_LVTPN_LABEL, LVTPN_IDENT_LABEL, END_LEVONODE_LABEL)
                ++lv1dat;
    }
    lv1dat->levtyp = LVTP_TYPE_NONE;
    //
    return lev1_decl;
}

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

char *parse_lv2expt_content(lv2p_expa_t *lv2expt, char *lv2e_cont) {
    // CLIEPF("[FUNC]:parse_lv2expt_content\n");
    // CLIEPF("lv2e_cont:|%s|\n", lv2e_cont);
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    pase_tok = lv2e_cont;
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_LVTPCONT_LABEL, END_LVTPCONT_LABEL)
    if (!pase_tok) return NULL;
    if (!parse_lv2p_conte(lv2expt->lv2nod, elem_valu))
        return NULL;
    //
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_LEVODECL_LABEL, END_LEVODECL_LABEL)
    if (!pase_tok) return NULL;
    if (!parse_lev1_decla(lv2expt->lv1dat, elem_valu))
        return NULL;
    //
    return lv2e_cont;
}








