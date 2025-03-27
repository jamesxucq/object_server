#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "commo_header.h"

#include "kcomm_macro.h"
#include "kcomm_directory.h"

#include "oattri.h"

//
/*
 <?xml version="1.0" encoding="UTF-8"?>
<base_metada>
    <stora_id>13646121<stora_id>
    <base_name>test<base_name>
</base_metada>
 
<?xml version="1.0" encoding="UTF-8"?>
<base_metada>
    <stora_id>a63b5e6801000000</stora_id>
    <base_name>earth</base_name>
</base_metada>
 
 */

//
static osv_str_t START_STORID_LABEL = osv_stri("<stora_id>");
static osv_str_t END_STORID_LABEL = osv_stri("</stora_id>");
static osv_str_t START_BASEN_LABEL = osv_stri("<base_name>");
static osv_str_t END_BASEN_LABEL = osv_stri("</base_name>");

//

static char *parse_attrib_base(osv_oid_t *base_obid, char *basen, char *oacont) {
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    pase_tok = oacont;
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_STORID_LABEL, END_STORID_LABEL);
    if (!pase_tok) return NULL;
    strsid_obid(base_obid, elem_valu);
    printf("elem_valu:|%s|\n", elem_valu);
    //
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_BASEN_LABEL, END_BASEN_LABEL);
    if (!pase_tok) return NULL;
    strcpy(basen, elem_valu);
    printf("elem_valu:|%s|\n", elem_valu);
    //
    return oacont;
}

//

static int save_attrib_base(char *oatti_path, osv_oid_t *base_obid, char *basen) {
    char attrib_cont[LARGE_TEXT_SIZE];
    MK_ZERO(attrib_cont);
    char *last_str = attrib_cont;
    //
    last_str = lscpy(last_str, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    char stoid_stri[STOR_IDENTI_ZLEN];
    last_str = lsprif(last_str, "<base_metada><stora_id>%s</stora_id>", oid_sidstr(stoid_stri, base_obid));
    last_str = lsprif(last_str, "<base_name>%s</base_name></base_metada>\n", basen);
    OSEVPF("[FUNC]:save_base_attrib attrib_cont:\n|%s|\n", attrib_cont);
    if (save_data(oatti_path, attrib_cont, 0x00))
        return -1;
    //
    return 0x00;
}

//

int creat_base_attri(char *basen) {
    char oatti_path[MAX_PATH * 3];
    CREAT_BASE_SUBDIRE(oatti_path, basen, BASE_CONTE_DATA)
    //
    osv_oid_t base_obid;
    creat_base_obid(&base_obid);
    if (save_attrib_base(oatti_path, &base_obid, basen))
        return -1;
    return 0x00;
}

//

int parse_base_attri(osv_oid_t *base_obid, char *basen) {
    char oatti_path[MAX_PATH * 3];
    char oatti_cont[LARGE_TEXT_SIZE];
    CREAT_BASE_SUBDIRE(oatti_path, basen, BASE_CONTE_DATA)
    if (!load_data(oatti_cont, LARGE_TEXT_SIZE, oatti_path))
        return -1;
    OSEVPF("load_data:|%s|\n", oatti_cont);
    //
    char _basen_[BASE_LENGTH];
    if (!parse_attrib_base(base_obid, _basen_, oatti_cont))
        return -1;
    printf("basen:|%s| _basen_:|%s|\n", basen, _basen_);
    if (strcmp(basen, _basen_)) return -1;
    //
    return 0x00;
}

//
/*
 <?xml version="1.0" encoding="UTF-8"?>
<osev_metada>
    <osev_unique>13646121<osev_unique>
    <osev_name>test<osev_name>
</osev_metada>
 */

//
static osv_str_t START_UNIQUE_LABEL = osv_stri("<osev_unique>");
static osv_str_t END_UNIQUE_LABEL = osv_stri("</osev_unique>");
static osv_str_t START_OSEVN_LABEL = osv_stri("<osev_name>");
static osv_str_t END_OSEVN_LABEL = osv_stri("</osev_name>");

//

static char *parse_attrib_osev(osv_oid_t *base_obid, char *osevn, char *oacont) {
    char elem_valu[ELEMEN_LENGTH];
    char *pase_tok;
    //
    pase_tok = oacont;
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_UNIQUE_LABEL, END_UNIQUE_LABEL);
    if (!pase_tok) return NULL;
    struniq_obid(base_obid, elem_valu);
    //
    GET_ELEMENT_VALUE(elem_valu, pase_tok, START_OSEVN_LABEL, END_OSEVN_LABEL);
    if (!pase_tok) return NULL;
    strcpy(osevn, elem_valu);
    //
    return oacont;
}

//

static int save_attrib_osev(char *oatti_path, osv_oid_t *base_obid, char *osevn) {
    char attrib_cont[LARGE_TEXT_SIZE];
    MK_ZERO(attrib_cont);
    char *last_str = attrib_cont;
    //
    last_str = lscpy(last_str, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    char uniq_stri[UNIQ_OBIDEN_ZLEN];
    last_str = lsprif(last_str, "<osev_metada><osev_unique>%s</osev_unique>", oid_uniqstr(uniq_stri, base_obid));
    last_str = lsprif(last_str, "<osev_name>%s</osev_name></osev_metada>\n", osevn);
    OSEVPF("[FUNC]:save_osev_attrib attrib_cont:\n|%s|\n", attrib_cont);
    if (save_data(oatti_path, attrib_cont, 0x00))
        return -1;
    //
    return 0x00;
}

//

int creat_osev_attri(char *osevn, osv_oid_t *osev_obid, char *data_directory) {
    fprintf(stdout, "Creat the osev_attri.met!\n");
    char oatti_path[MAX_PATH * 3];
    CREAT_OSEV_FILE(oatti_path, data_directory, OSEV_CONTE_DATA)
    creat_osev_obid(osev_obid);
    creat_osev_name(osevn);
    if (save_attrib_osev(oatti_path, osev_obid, osevn))
        return -1;
    return 0x00;
}

//

int parse_osev_attri(char *osevn, osv_oid_t *osev_obid, char *data_directory) {
    fprintf(stdout, "Parse the osev_attri.met!\n");
    char oatti_path[MAX_PATH * 3];
    char oatti_cont[LARGE_TEXT_SIZE];
    CREAT_OSEV_FILE(oatti_path, data_directory, OSEV_CONTE_DATA)
    if (!load_data(oatti_cont, LARGE_TEXT_SIZE, oatti_path))
        return -1;
    OSEVPF("load_data:|%s|\n", oatti_cont);
    if (!parse_attrib_osev(osev_obid, osevn, oatti_cont))
        return -1;
    //
    return 0x00;
}

