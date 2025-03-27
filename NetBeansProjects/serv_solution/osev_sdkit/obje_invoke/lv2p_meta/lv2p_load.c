#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "trans/trans_utili.h"
#include "filli_clang.h"

#include "lv2p_load.h"
#include "debug_funct_oi.h"
#include "lev1_decla.h"

//
/*
<?xml version="1.0" encoding="UTF-8"?>
<lv2p_metada>
    <stora_id>fe739b30f77c335900000000</stora_id>
    <lv2p_name>test</lv2p_name>
    <lv2p_atti>
        <version>1</version>
        <external>FALSE</external>
        <integrality>
            <lev1 range="0x01" lv2pn="this">method name</lev1>
            <lev1 range="0x01" lv2pn="teet">method name</lev1>
        </integrality>
    </lv2p_atti>
</lv2p_metada>
<inherit range="0x01" lev1n="lev1_name>lv2p_name</inherit>
<inherit range="0x02" lev1n="lev1_name">lv2p_name</inherit>
<inherit range="0x03" lev1n="">lv2p_name</inherit>
 */

//
static osv_str_t START_STORID_LABEL = osv_stri("<stora_id>");
static osv_str_t END_STORID_LABEL = osv_stri("</stora_id>");
static osv_str_t START_VERSION_LABEL = osv_stri("<version>");
static osv_str_t END_VERSION_LABEL = osv_stri("</version>");
static osv_str_t START_EXTERNAL_LABEL = osv_stri("<external>");
static osv_str_t END_EXTERNAL_LABEL = osv_stri("</external>");
static osv_str_t START_INTEGRALITY_LABEL = osv_stri("<integrality>");
static osv_str_t END_INTEGRALITY_LABEL = osv_stri("</integrality>");
static osv_str_t START_LEVO_LABEL = osv_stri("<lev1");
static osv_str_t LEVO_RANGE_LABEL = osv_stri("range");
static osv_str_t LEVO_LVTPN_LABEL = osv_stri("lv2pn");
static osv_str_t END_LEVO_LABEL = osv_stri("</lev1>");
static osv_str_t END_METADA_LABEL = osv_stri("</lv2p_metada>");
//
static osv_str_t START_INHERIT_LABEL = osv_stri("<inherit");
static osv_str_t INHER_RANGE_LABEL = osv_stri("range");
static osv_str_t INHER_LEVON_LABEL = osv_stri("lev1n");
static osv_str_t END_INHERIT_LABEL = osv_stri("</inherit>");

//

char *parse_integra(integra **olsth, char *inte_data) {
    // OSEVPF("[FUNC]:parse_integra\n");
    char atval1[ATTRIB_LENGTH], atval2[ATTRIB_LENGTH];
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    integra *onnod;
    // OSEVPF("inte_data:|%s|\n", inte_data);
    olsth[0x00] = NULL;
    pase_tok = inte_data;
    GET_TATTRIB_ELEMENT_VALUE(atval1, atval2, elem_valu, pase_tok, START_LEVO_LABEL, LEVO_RANGE_LABEL, LEVO_LVTPN_LABEL, END_LEVO_LABEL)
    while (pase_tok) {
        onnod = new_integ_list(olsth);
        if (!onnod) return NULL;
        onnod->rang_type = atoi(atval1);
        strcpy(onnod->lv2pn, atval2);
        strcpy(onnod->lev1n, elem_valu);
        // OSEVPF("onnod->lev1_name:|%s| pase_tok:%08X\n", onnod->lev1n, pase_tok);
        GET_TATTRIB_ELEMENT_VALUE(atval1, atval2, elem_valu, pase_tok, START_LEVO_LABEL, LEVO_RANGE_LABEL, LEVO_LVTPN_LABEL, END_LEVO_LABEL)
    }
    //
    return inte_data;
}

char *parse_attrib_lv2p(lv2p_attri *lv2ai, char *lv2p_cont) {
    // OSEVPF("[FUNC]:parse_attrib_lv2p\n");
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    pase_tok = lv2p_cont;
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_STORID_LABEL, END_STORID_LABEL);
    if (!pase_tok) return NULL;
    strsid_obid(&lv2ai->lv2p_obid, elem_valu);
    //
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_VERSION_LABEL, END_VERSION_LABEL);
    if (!pase_tok) return NULL;
    lv2ai->versio = atol(elem_valu);
    //
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_EXTERNAL_LABEL, END_EXTERNAL_LABEL);
    if (!pase_tok) return NULL;
    STRI_BOOL_VALU(lv2ai->iexter, elem_valu)
    //
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_INTEGRALITY_LABEL, END_INTEGRALITY_LABEL);
    if (!pase_tok) return NULL;
    if (!parse_integra(&lv2ai->integ_list, elem_valu))
        return NULL;
    //
    return lv2p_cont;
}

int parse_extern_lv2p(bool_osv *iexter, char *lv2p_cont) {
    // OSEVPF("[FUNC]:parse_attrib_lv2p\n");
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    pase_tok = lv2p_cont;
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_EXTERNAL_LABEL, END_EXTERNAL_LABEL);
    if (!pase_tok) return -1;
    STRI_BOOL_VALU(iexter[0x00], elem_valu)
            //
    return 0x00;
}

int parse_inherit(inherit **inhe_list, char *lv2p_inhe) {
    // OSEVPF("[FUNC]:parse_inherit\n");
    char atval1[ATTRIB_LENGTH], atval2[ATTRIB_LENGTH];
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    inherit *ilist;
    pase_tok = lv2p_inhe;
    GET_TATTRIB_ELEMENT_VALUE(atval1, atval2, elem_valu, pase_tok, START_INHERIT_LABEL, INHER_RANGE_LABEL, INHER_LEVON_LABEL, END_INHERIT_LABEL)
    while (pase_tok) {
        ilist = appe_ilist_new(inhe_list);
        if (!ilist) return -1;
        ilist->rang_type = atoi(atval1);
        strcpy(ilist->lev1n, atval2);
        strcpy(ilist->lv2pn, elem_valu);
        GET_TATTRIB_ELEMENT_VALUE(atval1, atval2, elem_valu, pase_tok, START_INHERIT_LABEL, INHER_RANGE_LABEL, INHER_LEVON_LABEL, END_INHERIT_LABEL)
    }
    //
    return 0x00;
}

//

char *split_lv2p_stoid(char *sid_data, char *lv2p_cont) {
    char *toksp = strstr(lv2p_cont, START_STORID_LABEL.data);
    if (!toksp) return NULL;
    toksp += START_STORID_LABEL.slen;
    char *tokep = strstr(toksp, END_STORID_LABEL.data);
    if (!tokep) return NULL;
    //
    if (sid_data) strzcpy(sid_data, toksp, tokep - toksp);
    return tokep + END_STORID_LABEL.slen;
}
//

char *split_lv2p_atti(char *acont, char *lv2p_cont) {
    char *tokep = strstr(lv2p_cont, END_METADA_LABEL.data);
    if (!tokep) return NULL;
    tokep += END_METADA_LABEL.slen;
    if (acont) strzcpy(acont, lv2p_cont, tokep - lv2p_cont);
    return tokep;
}

//

char *split_lv2p_integ(char *inte_data, char *lv2p_cont) {
    char *toksp = strstr(lv2p_cont, START_INTEGRALITY_LABEL.data);
    if (!toksp) return NULL;
    char *tokep = strstr(lv2p_cont, END_INTEGRALITY_LABEL.data);
    if (!tokep) return NULL;
    tokep += END_INTEGRALITY_LABEL.slen;
    if (inte_data) strzcpy(inte_data, toksp, tokep - toksp);
    return tokep;
}

char *pass_lv2p_atti(char *lv2p_cont) {
    char *tokep = strstr(lv2p_cont, END_METADA_LABEL.data);
    if (!tokep) return NULL;
    tokep += END_METADA_LABEL.slen;
    return tokep;
}

//

int parse_lev1_meta(lv1_cont **l1clsth, char *meth_decl) {
    OSEVPF("[FUNC]:parse_lev1_meta meth_decl:|%s|\n", meth_decl);
    char *tokep, *toksp;
    lv1_cont *l1c_nod;
    char lvnsps[LVON_LENGTH];
    char lev1_invk[LVON_LENGTH];
    // 
    char *lev1n;
    if (!(toksp = kill_inval(meth_decl)))
        return 0x00;
    tokep = find_defin_decla_ext(lvnsps, lev1_invk, toksp);
    while (tokep) {
        if ((lev1n = l1nsps_delim(lvnsps))) {
            l1c_nod = appe_l1clst_new(l1clsth);
            if (!l1c_nod) return -1;
            strcpy(l1c_nod->lev1n, lev1n);
            if (0x00 > (l1c_nod->oivk_retyp_oc = conv_oinvk_retyp(lev1_invk)))
                return -1;
            if (conv_oinvk_decla(l1c_nod->oivk_fmtsp_oc, lev1_invk))
                return -1;
            l1c_nod->oivk_size_oc = count_pamik_size(l1c_nod->oivk_fmtsp_oc);
            strzcpy(l1c_nod->conte, toksp, tokep - toksp);
            PRIN_lev1_conte(l1c_nod);
        }
        if (!(toksp = kill_inval(tokep))) break;
        tokep = find_defin_decla_ext(lvnsps, lev1_invk, toksp);
    }
    //
    return 0x00;
}

//

int load_lv2p_expand(lv2p_expa_i *lv2expi, char *basen, char *lv2pn) {
    // OSEVPF("[FUNC]:load_lv2p_expand\n");
    char lv2e_path[MAX_PATH * 3];
    LVTP_EXPAN_FILE(lv2e_path, basen, lv2pn);
    if (!bina_load_data((char *) lv2expi, sizeof (lv2p_expa_i), lv2e_path, 0x00))
        return -1;
    // PRIN_lv2p_expa_i(lv2expi);
    return 0x00;
}