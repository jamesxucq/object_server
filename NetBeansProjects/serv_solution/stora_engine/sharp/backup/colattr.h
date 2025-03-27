
/* 
 * File:   colattr.h
 * Author: Administrator
 *
 * Created on 2018.3.11, AM 8:27
 */

#ifndef COLATTR_H
#define COLATTR_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct colla_list {
        char conta_name[CONTA_LENGTH];
        uint32 isize;
        struct colla *next;
    };

    //
    int creat_colla(char *osdb);
    int addi_colla(char *conta_name, uint32 stora_type, char *data_type, char *osdb);
    int dele_colla(char *conta_name, char *osdb);
    int find_colla(osv_oid_t *oid, char *data_type, char *conta_name, char *osdb);
    int sear_colla(char *resu, char *osdb, char *conta_name, char *data_type);

    //
    struct conta_list *load_colla(char *osdb);

#ifdef __cplusplus
}
#endif

#endif /* COLATTR_H */

