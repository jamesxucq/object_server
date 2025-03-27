
/* 
 * File:   parse_respo.h
 * Author: James Xu
 *
 * Created on 2023.9.25, AM 10:24
 */

#ifndef PARSE_RESPO_H
#define PARSE_RESPO_H

#include "reque_respo.h"
#include "conatt.h"

#ifdef __cplusplus
extern "C" {
#endif

    // trans-serve
    char *parse_colle_versi(unsigned long long *lv2p_versi, resp_data_t *xml_colle);
    char *parse_colle_extern(bool_osv *lv2p_extern, resp_data_t *xml_colle);
    // extern integrality
    char *parse_colle_extint(bool_osv *lv2p_extern, bool_osv *lv2p_integr, resp_data_t *xml_colle);

    // trans-serve
    // lev1 lv2p
    char *parse_colle_conte(char *lv2p_versi, resp_data_t *xml_colle);
    char *parse_invok_conte(char *lv2p_versi, resp_data_t *xml_invok);

    // trans-serve
    // lev3 lv4p
    cont_atti *parse_const_conat(cont_atti *conat, resp_data_t *xml_const);
    cont_atti *parse_query_conat(cont_atti *conat, resp_data_t *xml_query);


#ifdef __cplusplus
}
#endif

#endif /* PARSE_RESPO_H */

