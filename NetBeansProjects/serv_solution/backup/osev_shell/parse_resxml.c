#include "commo_header.h"

#include "osev_clie_clang.h"
#include"cli_struct.h"

#include "parse_resxml.h"
#include "debug_funct_sh.h"

/*
<?xml version="1.0" encoding="UTF-8"?>
    <lv2p>
        <name>roles</name>
        <obid>dd6d7f0ec35d116401000000</obid>
    </lv2p>
 */

static osv_str_t START_COCON_LABEL = osv_stri("<name>");
static osv_str_t END_COCON_LABEL = osv_stri("</name>");
static osv_str_t START_COCOO_LABEL = osv_stri("<obid>");
static osv_str_t END_COCOO_LABEL = osv_stri("</obid>");

int parse_colle_ovalu(obje_valu *ovalu, resp_data_t *xml_colle) {
    CLIEPF("[FUNC]:parse_colle_ovalu\n");
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    xml_colle->resp_memo[xml_colle->content_length] = '\0';
    CLIEPF("xml_colle->resp_memo:|%s|\n", xml_colle->resp_memo);
    pase_tok = xml_colle->resp_memo;
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_COCON_LABEL, END_COCON_LABEL);
    if (!pase_tok) return -1;
    strcpy(ovalu->obje_iden, elem_valu);
    //
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_COCOO_LABEL, END_COCOO_LABEL);
    if (!pase_tok) return -1;
    stroid(&ovalu->obje_obid, elem_valu);
    //
    return 0x00;
}

//

/*
<?xml version="1.0" encoding="UTF-8"?>
    <contain>
        <name>roles_con</name>
        <obid>dd6d7f0ec35d116401000000</obid>
    </contain>
 */

int parse_query_ovalu(obje_valu *ovalu, resp_data_t *xml_query) {
    CLIEPF("[FUNC]:parse_query_ovalu\n");
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    xml_query->resp_memo[xml_query->content_length] = '\0';
    CLIEPF("xml_query->resp_memo:|%s|\n", xml_query->resp_memo);
    pase_tok = xml_query->resp_memo;
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_COCON_LABEL, END_COCON_LABEL);
    if (!pase_tok) return -1;
    strcpy(ovalu->obje_iden, elem_valu);
    //
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_COCOO_LABEL, END_COCOO_LABEL);
    if (!pase_tok) return -1;
    stroid(&ovalu->obje_obid, elem_valu);
    //
    return 0x00;
}

//

/*
 <?xml version="1.0" encoding="UTF-8"?>
<base_status name="earth">
    <base_obid>bfff1d8bcdb7546403000000</base_obid>
    <authen status="ON"/>
    <running="yes"/>
    <running_level>00007777</running_level>
</base_status>
 */
static osv_str_t START_BSTAT_LABEL = osv_stri("<base_status");
static osv_str_t BSTAT_BNAME_LABEL = osv_stri("name");

static osv_str_t START_BOBIDE_LABEL = osv_stri("<base_obid>");
static osv_str_t END_BOBIDE_LABEL = osv_stri("</base_obid>");

int parse_osev_ovalu(obje_valu *ovalu, resp_data_t *xml_osev) {
    CLIEPF("[FUNC]:parse_osev_ovalu\n");
    char atval[ATTRIB_LENGTH];
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    xml_osev->resp_memo[xml_osev->content_length] = '\0';
    CLIEPF("xml_osev->resp_memo:|%s|\n", xml_osev->resp_memo);
    pase_tok = xml_osev->resp_memo;
    GET_ATTRIB_VALUE(atval, pase_tok, START_BSTAT_LABEL, BSTAT_BNAME_LABEL);
    if (!pase_tok) return -1;
    strcpy(ovalu->obje_iden, atval);
    //
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_BOBIDE_LABEL, END_BOBIDE_LABEL);
    if (!pase_tok) return -1;
    stroid(&ovalu->obje_obid, elem_valu);
    //
    return 0x00;
}