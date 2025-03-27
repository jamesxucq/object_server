
/* 
 * File:   oattri.h
 * Author: James Xu
 *
 * Created on 2017.5.25, PM1:56
 */

#ifndef OATTRI_H
#define OATTRI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int creat_base_attri(char *basen);
    int parse_base_attri(osv_oid_t *base_obid, char *basen);

    //
    int creat_osev_attri(char *osevn, osv_oid_t *osev_obid, char *data_directory);
    int parse_osev_attri(char *osevn, osv_oid_t *osev_obid, char *data_directory);


#ifdef __cplusplus
}
#endif

#endif /* OATTRI_H */

