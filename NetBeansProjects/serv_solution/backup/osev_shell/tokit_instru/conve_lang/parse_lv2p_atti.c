#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "../kstri_utili.h"
#include "cstri_utili.h"

#include "parse_lv2p_atti.h"
#include "../../debug_funct_sh.h"

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
<inherit lev1="levi_name">lv2p_name</inherit>
<inherit lev1="levi_name">lv2p_name</inherit>
 */

//
static osv_str_t START_STORID_LABEL = osv_stri("<stora_id>");
static osv_str_t END_STORID_LABEL = osv_stri("</stora_id>");
static osv_str_t START_CLASN_LABEL = osv_stri("<lv2p_name>");
static osv_str_t END_CLASN_LABEL = osv_stri("</lv2p_name>");
static osv_str_t START_VERSION_LABEL = osv_stri("<version>");
static osv_str_t END_VERSION_LABEL = osv_stri("</version>");
static osv_str_t START_EXTERNAL_LABEL = osv_stri("<external>");
static osv_str_t END_EXTERNAL_LABEL = osv_stri("</external>");
static osv_str_t START_INTEGRALITY_LABEL = osv_stri("<integrality>");
static osv_str_t END_INTEGRALITY_LABEL = osv_stri("</integrality>");
static osv_str_t START_lEVEONE_LABEL = osv_stri("<lev1>");
static osv_str_t END_LEVEONE_LABEL = osv_stri("</lev1>");
static osv_str_t START_METADA_LABEL = osv_stri("<lv2p_metada>");
static osv_str_t END_METADA_LABEL = osv_stri("</lv2p_metada>");

//

static char *parse_integra(levon **olsth, char *inte_data) {
    // CLIEPF("[FUNC]:parse_integra\n");
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    levon *slist;
    // CLIEPF("inte_data:|%s|\n", inte_data);
    olsth[0x00] = NULL;
    pase_tok = inte_data;
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_lEVEONE_LABEL, END_LEVEONE_LABEL);
    while (pase_tok) {
        slist = appe_slist_new(olsth);
        if (!slist) return NULL;
        strcpy(slist->lev1n, elem_valu);
        // CLIEPF("slist->lev1_name:|%s| pase_tok:%08X\n", slist->lev1_name, pase_tok);
        GET_ELEMENT_VALUE(elem_valu, pase_tok, START_lEVEONE_LABEL, END_LEVEONE_LABEL);
    }
    //
    return inte_data;
}

char *parse_lv2p_atti(class_meta *clsmt, char *lv2p_cont) {
    // CLIEPF("[FUNC]:parse_lv2p_atti\n");
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    pase_tok = lv2p_cont;
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_STORID_LABEL, END_STORID_LABEL);
    if (!pase_tok) return NULL;
    strsid_obid(&clsmt->lv2p_obid, elem_valu);
    //
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_CLASN_LABEL, END_CLASN_LABEL);
    if (!pase_tok) return NULL;
    strcpy(clsmt->lv2pn, elem_valu);
    //
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_VERSION_LABEL, END_VERSION_LABEL);
    if (!pase_tok) return NULL;
    clsmt->versio = atol(elem_valu);
    //
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_EXTERNAL_LABEL, END_EXTERNAL_LABEL);
    if (!pase_tok) return NULL;
    STRI_BOOL_VALU(clsmt->iextern, elem_valu)
    //
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_INTEGRALITY_LABEL, END_INTEGRALITY_LABEL);
    if (!pase_tok) return NULL;
    if (!parse_integra(&clsmt->levo_list, elem_valu))
        return NULL;
    //
    return lv2p_cont;
}

//

char *split_lv2p_atti(char *acont, char *lv2p_cont) {
    char *tokep = strstr(lv2p_cont, END_METADA_LABEL.data);
    if (!tokep) return NULL;
    tokep += END_METADA_LABEL.slen;
    if (acont) strzcpy(acont, lv2p_cont, tokep - lv2p_cont);
    return tokep;
}

// check the start_metada_label, the content is attribute/

char *find_lv2p_atti(char *lv2p_cont) {
    char *tokep = strstr(lv2p_cont, START_METADA_LABEL.data);
    if (!tokep) return NULL;
    tokep += END_METADA_LABEL.slen;
    //
    tokep = strstr(tokep, END_METADA_LABEL.data);
    if (!tokep) return NULL;
    tokep += END_METADA_LABEL.slen;
    return tokep;
}

//

static osv_str_t START_EXPAND_LABEL = osv_stri("<lv2p_expand>");
static osv_str_t END_EXPAND_LABEL = osv_stri("</lv2p_expand>");

char *find_l2exp_bzl(char *lv2p_cont) {
    char *tokep = strstr(lv2p_cont, START_EXPAND_LABEL.data);
    if (!tokep) return NULL;
    tokep += START_EXPAND_LABEL.slen;
    //
    tokep = strstr(tokep, END_EXPAND_LABEL.data);
    if (!tokep) return NULL;
    tokep += END_EXPAND_LABEL.slen;
    return tokep;
}

//

unsigned int split_conte_type(char *lv2e_cont, char *lv2p_cont, char *lev1_cont, char *leve_data) {
    CLIEPF("[FUNC]:split_conte_type ----------------------\n");
    int is_defin = 0x00;
    int contype = 0x00;
    char *last_lv2p = lv2p_cont;
    char *last_lev1 = lev1_cont;
    //
    char *cotok = find_lv2p_atti(leve_data);
    if (cotok) {
        last_lv2p = lszcpy(last_lv2p, leve_data, cotok - leve_data);
        last_lev1 = lszcpy(last_lev1, leve_data, cotok - leve_data);
        contype |= KLST_LVTP_ATTRIB;
        CLIEPF("KLST_LVTP_ATTRIB\n");
    } else cotok = leve_data;
    //
    char *last_str = find_l2exp_bzl(cotok);
    if (last_str) {
        lszcpy(lv2e_cont, cotok, last_str - cotok);
        contype |= KLST_LVTP_EXPAND;
        CLIEPF("KLST_LVTP_EXPAND\n");
    } else last_str = cotok;
    //
    char line_cont[LARGE_TEXT_SIZE];
    unsigned int line_type;
    while ((last_str = next_conte_type(line_cont, &line_type, last_str))) {
        switch (line_type) {
            case TYPE_LVTP_DEFINE:
                CLIEPF("TYPE_LVTP_DEFINE, |%s|\n", line_cont);
                if (!is_defin) {
                    last_lv2p = lscpy(last_lv2p, line_cont);
                    last_lev1 = lscpy(last_lev1, line_cont);
                    ++is_defin;
                }
                break;
            case TYPE_LEVO_CONTE:
                CLIEPF("TYPE_LEVO_CONTE, |%s|\n", line_cont);
                last_lev1 = lscpy(last_lev1, line_cont);
                contype |= KLST_LEVO_CONTE;
                break;
            case TYPE_LVTP_CONTE:
                CLIEPF("TYPE_LVTP_CONTE, |%s|\n", line_cont);
                last_lv2p = lscpy(last_lv2p, line_cont);
                contype |= KLST_LVTP_CONTE;
                break;
            default:
                return 0x00;
                break;
        }
    }
    //
    CLIEPF("end, split_conte_type ----------------------\n");
    return is_defin ? contype : 0x00;
}
