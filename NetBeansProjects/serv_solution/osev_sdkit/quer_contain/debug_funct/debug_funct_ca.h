
/* 
 * File:   debug_funct_ca.h
 * Author: James Xu
 *
 * Created on 2024.6.5, AM 9:03
 */

#ifndef DEBUG_FUNCT_CA_H
#define DEBUG_FUNCT_CA_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    /*
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
     */

    //

    void p_cont_atti_i(cont_atti_i *canod) {
        char stoid_stri[STOR_IDENTI_ZLEN];
        printf("-------------------- p_cont_atti_i\n");
        printf("canod->cont_stoid:|%s|\n", sidstr(stoid_stri, (osv_sid_t *) & canod->cont_stoid));
        printf("canod->cont_name:|%s|\n", canod->cont_name);
        printf("canod->contype:|%d|\n", canod->contype);
        printf("canod->refe_coun:|%d|\n", canod->refe_coun);
        //
        printf("canod->refe_cont[0x00]:|%llu|\n", canod->refe_cont[0x00]);
        printf("canod->refe_cont[0x01]:|%llu|\n", canod->refe_cont[0x01]);
        printf("canod->refe_cont[0x02]:|%llu|\n", canod->refe_cont[0x02]);
        printf("canod->refe_cont[0x03]:|%llu|\n", canod->refe_cont[0x03]);
        //
        printf("canod->conditype:|%u|\n", canod->conditype);
        printf("canod->condition:|%s|\n", canod->condition);
        printf("canod->stora_type:|%u|\n", canod->stora_type);
        printf("--------------------\n");
    }



#ifdef __cplusplus
}
#endif

#endif /* DEBUG_FUNCT_CA_H */

