
/* 
 * File:   query_utili.h
 * Author: James Xu
 *
 * Created on 2017.3.2, PM 2:21
 */

#ifndef QUERY_UTILI_H
#define QUERY_UTILI_H

#include "commo_header.h"
#include "kcomm_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int inser_conta_list(cont_lsmp *conda_stm, cont_list *clist);

    // cont_type
#define INVAL_CONTA_TYPE   0x0000
#define ENTIT_CONTA_TYPE   0x0001
#define REFER_CONTA_TYPE   0x0002
#define ENTIT_REFER_TYPE   0x0003
    unsigned int parse_source_contn(contain **sconp, unsigned int *cont_type, cont_lsmp *conda_stm, char *src_name);
    unsigned int parse_source_conto(contain **sconp, unsigned int *cont_type, cont_lsmp *conda_stm, osv_oid_t *src_obid, unsigned long long src_len);

    //
    int parse_refere_conta(contain **rconp, cont_lsmp *conda_stm, cont_versi *rcove, int rcoun);

    //
    int check_refer_obid(unsigned char pamtyp, char *param);

    // 0x00:is empty 0x01:not empty

    inline int check_rcont_empty(int rcoun, cont_versi *rcove) {
        unsigned int inde = 0x00;
        for (; rcoun > inde; ++inde, ++rcove) {
            if (CHK_ZERO_OBID((&rcove->lv4p_obid)))
                return 0x01;
        }
        return 0x00;
    }

    //

    inline unsigned int build_condit_type(char *condition, unsigned char creat_conditype) {
        switch (creat_conditype) {
            case DATY_OBID: // 
                return CONDI_TYPE_OBJID;
                break;
            case DATY_STRI: // 
                if ((DYNAMIC_PREDICATE_DEFAULT == condition[0x00]) || IS_ZERO(condition))
                    return CONDI_TYPE_TRAVE;
                else return CONDI_TYPE_PREDI;
                break;
            default:
                return INVA_UINT_VALU;
                break;
        }
        return INVA_UINT_VALU;
    }


#ifdef __cplusplus
}
#endif

#endif /* QUERY_UTILI_H */

