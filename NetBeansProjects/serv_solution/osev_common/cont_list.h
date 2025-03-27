
/* 
 * File:   cont_list.h
 * Author: James Xu
 *
 * Created on 2017.1.16, PM 2:35
 */

#ifndef CONT_LIST_H
#define CONT_LIST_H

#include "third_party.h"
#include "utility/utlist.h"
#include "osev_macro.h"
#include "hash_table_ex.h"
#include "rive_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

    // contype
#define ENTIT_CONTA_NORMAL   0x00
#define REFER_CONTA_STATIC   0x01
#define REFER_CONTA_DYNAMI   0x02

    // conditype
#define CONDI_TYPE_TRAVE   0x00
#define CONDI_TYPE_OBJID   0x01
#define CONDI_TYPE_PREDI   0x02

    //
#define CONTA_INITI_VERSIO   0x00
#define CONTA_INVAL_VERSIO   ((unsigned long long)-1)

    struct _cont_versi_ {
        osv_oid_t lv4p_obid; // lv4p object id
        unsigned long long versio; // 0x00:disable >0x00:is version  // virtual
    };

    typedef struct _cont_versi_ cont_versi;

    //

#define CHK_ZERO_COVE(PCOVE) \
    (((osv_oid_i *)(&(PCOVE)->lv4p_obid))->stoid)

#define MAKE_ZERO_COVE(PCOVE) \
    ((osv_oid_i *)(&(PCOVE)->lv4p_obid))->stoid = 0x00;

    //

    struct _contain_ {
        osv_oid_t cont_obid;
        char cont_name[CONTA_LENGTH];
        int contype; // 0x00:normal conta, 0x01:static referen , 0x02:dynamic referen
        char base_name[BASE_LENGTH];
        osv_oid_t lv2p_type;
        //
        int refe_coun; // 0: is normal !=0: is referen contain, max is 4 referen
        unsigned long long versio; // 0x00:disable >0x00:is version // virtual
        cont_versi refe_cove[RCONT_CONUT_ZTAI];
        unsigned int conditype; // 0x00:traver 0x01:objid 0x02:predica
        char condition[CONDIT_LENGTH];
        //
        rive_ha *stora_ha;
    };

    typedef struct _contain_ contain;

    //

    struct _cont_list_ {
        contain *contp;
        //
        struct _cont_list_ *next;
    };

    typedef struct _cont_list_ cont_list;

    //
    cont_list *appe_cont_list(cont_list **clsth);
    contain *appe_clist_cont(cont_list **clsth);

    //

    inline void dele_cont_list(cont_list *clist) {
        cont_list *clsnd;
        while (clist) {
            clsnd = clist;
            clist = clist->next;
            free(clsnd->contp);
            free(clsnd);
        }
    }

    inline void dele_clist(cont_list **clsth, cont_list *clist) {
        LL_DELETE(*clsth, clist)
        free(clist->contp);
        free(clist);
    }

    inline void dele_clist_cont(cont_list **clsth, contain *contp) {
        // printf("dele_clist_cont\n");
        cont_list *clsnd = clsth[0x00];
        for (; clsnd; clsnd = clsnd->next) {
            if (contp == clsnd->contp) {
                // printf("contp->cont_name:|%s|, clsnd->contp->cont_name:|%s|\n", contp->cont_name, clsnd->contp->cont_name);
                LL_DELETE(*clsth, clsnd)
                free(clsnd->contp);
                free(clsnd);
                break;
            }
        }
    }

    // CONVE_CATTR_CONTA

#define CONVE_CATTR_CONTA(CONTP, CANOD, BASEN) { \
    OBID_STOID_BUILD(&CONTP->cont_obid, &CANOD.cont_stoid) \
    strcpy(CONTP->cont_name, CANOD.cont_name); \
    CONTP->contype = CANOD.contype; \
    strcpy(CONTP->base_name, BASEN); \
    OBID_STOID_BUILD(&CONTP->lv2p_type, &CANOD.lv2p_type); \
    cont_versi *des_ref; \
    osv_sid_i *src_ref; \
    unsigned int inde; \
    switch (CANOD.contype) { \
        case REFER_CONTA_STATIC: \
            CONTP->refe_coun = CANOD.refe_coun; \
            des_ref = CONTP->refe_cove; \
            src_ref = CANOD.refe_cont; \
            for (inde = 0x00; (MAX_RSCON_COUNT > inde) && NOT_ZERO_STOID(src_ref); ++inde, ++des_ref, ++src_ref) \
                OBID_STOID_BUILD(&(des_ref->lv4p_obid), src_ref); \
            MAKE_ZERO_COVE(des_ref) \
            break; \
        case REFER_CONTA_DYNAMI: \
            CONTP->refe_coun = CANOD.refe_coun; \
            CONTP->versio = CONTA_INITI_VERSIO; \
            cont_versi *des_ref = CONTP->refe_cove; \
            src_ref = CANOD.refe_cont; \
            for (inde = 0x00; CANOD.refe_coun > inde; ++inde, ++des_ref, ++src_ref) { \
                OBID_STOID_BUILD(&(des_ref->lv4p_obid), src_ref); \
                des_ref->versio = CONTA_INVAL_VERSIO; \
            } \
            CONTP->conditype = CANOD.conditype; \
            if (CONDI_TYPE_OBJID == CANOD.conditype) { \
                osv_oid_t *enti_obid = (osv_oid_t *) CONTP->condition; \
                src_ref = (osv_sid_i *) CANOD.condition; \
                for (inde = 0x00; CANOD.refe_coun > inde; ++inde, ++enti_obid, ++src_ref) { \
                    OBID_STOID_BUILD(enti_obid, src_ref); \
                } \
            } else strcpy(CONTP->condition, CANOD.condition); \
            break; \
        default: \
            break; \
    } \
    CONTP->stora_ha = GET_STORAHA_BZL(CANOD.stora_type); \
}

    //

#ifdef __cplusplus
}
#endif

#endif /* CONT_LIST_H */

