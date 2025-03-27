#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"

#include "parse_respo.h"

/*
<?xml version="1.0" encoding="UTF-8"?>
    <lv2p_metada>
        <stora_id>54a2026500000000</stora_id>
        <lv2p_name>tsst</lv2p_name>
        <lv2p_atti>
            <version>2</version>
            <external>FALSE</external>
            <integrality></integrality>
        </lv2p_atti>
    </lv2p_metada>
 */

//
static osv_str_t START_VERSION_LABEL = osv_stri("<version>");
static osv_str_t END_VERSION_LABEL = osv_stri("</version>");
static osv_str_t START_EXTERNAL_LABEL = osv_stri("<external>");
static osv_str_t END_EXTERNAL_LABEL = osv_stri("</external>");
static osv_str_t START_LEVO_LABEL = osv_stri("<lev1");
static osv_str_t END_LEVO_LABEL = osv_stri("</lev1>");

// trans-serve

char *parse_colle_versi(unsigned long long *lv2p_versi, resp_data_t *xml_colle) {
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    xml_colle->resp_memo[xml_colle->content_length] = '\0';
    OSEVPF("xml_colle->resp_memo:|%s|\n", xml_colle->resp_memo);
    pase_tok = xml_colle->resp_memo;
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_VERSION_LABEL, END_VERSION_LABEL);
    if (!pase_tok) return NULL;
    *lv2p_versi = strtoul(elem_valu, NULL, 10);
    //
    return pase_tok;
}

char *parse_colle_extern(bool_osv *lv2p_extern, resp_data_t *xml_colle) {
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    xml_colle->resp_memo[xml_colle->content_length] = '\0';
    OSEVPF("xml_colle->resp_memo:|%s|\n", xml_colle->resp_memo);
    pase_tok = xml_colle->resp_memo;
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_EXTERNAL_LABEL, END_EXTERNAL_LABEL);
    if (!pase_tok) return NULL;
    STRI_BOOL_VALU(lv2p_extern[0x00], elem_valu)
            //
    return pase_tok;
}

// extern integrality

char *parse_colle_extint(bool_osv *lv2p_extern, bool_osv *lv2p_integr, resp_data_t *xml_colle) {
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    xml_colle->resp_memo[xml_colle->content_length] = '\0';
    OSEVPF("xml_colle->resp_memo:|%s|\n", xml_colle->resp_memo);
    pase_tok = xml_colle->resp_memo;
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_EXTERNAL_LABEL, END_EXTERNAL_LABEL);
    if (!pase_tok) return NULL;
    STRI_BOOL_VALU(lv2p_extern[0x00], elem_valu);
    //
    char *chktok = pase_tok;
    CHK_ELEMENT_VALUE(chktok, START_LEVO_LABEL, END_LEVO_LABEL);
    if (chktok)
        lv2p_integr[0x00] = FALSE_OSV;
    else lv2p_integr[0x00] = TRUE_OSV;
    //
    return pase_tok;
}

//

char *parse_colle_conte(char *lv2p_conte, resp_data_t *xml_colle) {
    return lv2p_conte;
}

//

char *parse_invok_conte(char *lev1_conte, resp_data_t *xml_invok) {
    return lev1_conte;
}

//
//
/*
<?xml version="1.0" encoding="UTF-8"?>
<conatt>
    <name>txxt_con</name>
    <obid>ff7f5d14a6ba306602000000</obid>
    <attrib>
        <lv2p_type fmtst="iii" dasiz="24">txxt</lv2p_type>
        <referen type="dynamic">
            <refe_cont count="2">
                <contain>contname1</contain>
                <contain>contname2</contain>
            </refe_cont>
            <condit>xx>2 AND yy < 3</condit>
        </referen>
        <stora_engine>wiredtiger</stora_engine>
    </attrib>
</conatt>
 */

static osv_str_t START_LTPTYP_LABEL = osv_stri("<lv2p_type");
static osv_str_t LTPTYP_FMTST_LABEL = osv_stri("fmtst");
static osv_str_t LTPTYP_DASIZ_LABEL = osv_stri("dasiz");

cont_atti *parse_const_conat(cont_atti *conat, resp_data_t *xml_const) {
#ifdef _DEBUG
    printf("[FUNC]:parse_const_conat\n");
#endif // _DEBUG
    // char elem_valu[ELEMEN_LENGTH];
    char atval1[ATTRIB_LENGTH], atval2[ATTRIB_LENGTH];
    char *pase_tok;
    //
    xml_const->resp_memo[xml_const->content_length] = '\0';
#ifdef _DEBUG
    printf("xml_const->resp_memo:|%s|\n", xml_const->resp_memo);
#endif // _DEBUG
    pase_tok = xml_const->resp_memo;
    GET_TATTRIB_VALUE(atval1, atval2, pase_tok, START_LTPTYP_LABEL, LTPTYP_FMTST_LABEL, LTPTYP_DASIZ_LABEL)
    if (!pase_tok) return NULL;
    strcpy(conat->fmtst, atval1);
    conat->data_size = strtoul(atval2, NULL, 10);
    //
    return conat;
}

cont_atti *parse_query_conat(cont_atti *conat, resp_data_t *xml_query) {
    return conat;
}