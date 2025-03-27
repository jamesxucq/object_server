
/* 
 * File:   conattr.h
 * Author: James Xu
 *
 * Created on 2017.2.11, AM 8:27
 */

#ifndef CONATTR_H
#define CONATTR_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    // refe_coun
#define ENTITY_CONTAI_COUNT     0x00

    //

    struct _cont_atti_i_ {
        osv_sid_i cont_stoid;
        char cont_name[CONTA_LENGTH];
        int contype; // 0x00:normal conta, 0x01:static referen , 0x02:dynamic referen
        osv_sid_i lv2p_type;
        //
        int refe_coun; // 0: is normal !=0: is referen contain, max is 4 referen
        osv_sid_i refe_cont[RCONT_CONUT_ZTAI];
        unsigned int conditype; // 0x00:traver 0x01:objid 0x02:predica
        char condition[CONDIT_LENGTH];
        //
        unsigned int stora_type;

        union {
            unsigned int sibling;
            unsigned int recycle;
        };
    };

    typedef struct _cont_atti_i_ cont_atti_i;

    //
    int creat_cont_atti(char *basen); // passed
    int addi_cont_atti(char *contn, osv_oid_t *lv2p_type, uint32 stora_type, char *basen); // passed
    int addi_rscont_atti(char *contn, osv_oid_t *lv2p_type, uint32 refe_coun, uint32 stora_type, char *basen); // passed
    int addi_rdcont_atti(char *contn, osv_oid_t *lv2p_type, uint32 refe_coun, osv_oid_t *refe_cont, uint32 conditype, char *condition, uint32 stora_type, char *basen); // passed
    int dele_cont_atti(osv_oid_t *cont_obid, char *basen); // passed
    int find_cont_atti(cont_atti_i *conap, char *contn, char *basen); // passed
    int updat_rscont_atti(contain *contp, char *basen); // passed

    //
    int searc_conta_attri(char *resul, char *basen, char *contn, osv_oid_t *lv2p_type); // passed
    // 0x00:found 0x01:not found -1:error
    int check_catti_lv2p(char *basen, osv_oid_t *lv2p_type); // passed

    //
    cont_list *load_catti_base(char *basen); // passed

#ifdef __cplusplus
}
#endif

#endif /* CONATTR_H */

