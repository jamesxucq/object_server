
/* 
 * File:   parse_resxml.h
 * Author: james
 *
 * Created on 2023.5.9, PM 1:49
 */

#ifndef PARSE_RESXML_H
#define PARSE_RESXML_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int parse_colle_ovalu(obje_valu *ovalu, resp_data_t *xml_colle);
    int parse_query_ovalu(obje_valu *ovalu, resp_data_t *xml_query);
    int parse_osev_ovalu(obje_valu *ovalu, resp_data_t *xml_osev);

#ifdef __cplusplus
}
#endif

#endif /* PARSE_RESXML_H */

