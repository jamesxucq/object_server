
/* 
 * File:   parse_respo.h
 * Author: James Xu
 *
 * Created on 2023.11.4, PM 1:56
 */

#ifndef PARSE_RESPO_H
#define PARSE_RESPO_H

#ifdef __cplusplus
extern "C" {
#endif

    //

    int parse_query_obid(osv_oid_t *obje_obid, resp_data_t *xml_query);

    // trans-serve
    char *parse_colle_versi(unsigned long long *lv2p_versi, resp_data_t *xml_colle);
    
    //
    char *parse_colle_attrib(unsigned long long *lv2p_versi, unsigned int *lv2p_extern, resp_data_t *xml_colle);

    // trans-serve
    // lev3
    cont_atti *parse_const_conat(cont_atti *conat, resp_data_t *xml_const);

#ifdef __cplusplus
}
#endif

#endif /* PARSE_RESPO_H */

