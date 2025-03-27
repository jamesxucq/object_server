
/* 
 * File:   creaq_utili.h
 * Author: James Xu
 *
 * Created on 2024.5.28, AM 10:59
 */

#ifndef CREAQ_UTILI_H
#define CREAQ_UTILI_H

#include "../contain.h"
#include "../query_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    inline contain *creat_qcont_meta(base_valu *baval, char *contn) {
        cont_list *clist = appe_cont_list(&baval->conda_stm.clist);
        if (!clist) return NULL;
        if (!build_conta_meta(clist->contp, baval->base_name, contn)) {
            dele_clist(&baval->conda_stm.clist, clist);
            OSEVPF("Create contain execep!\n");
            return NULL;
        }
        conta_cache_insert(&baval->conda_stm, clist->contp);
        //
        return clist->contp;
    }

    // reference parse_source_contn

    inline unsigned int parse_refere_contn(osv_oid_t *rcont, unsigned int *cont_type, cont_lsmp *conda_stm, char *ref_name) {
        // OSEVPF("[FUNC]:parse_refere_contn, ref_name:|%s|\n", ref_name);
        cont_type[0x00] = INVAL_CONTA_TYPE;
        char qconta[SCONT_CONUT_ZTAI][CONTA_LENGTH];
        unsigned int cont_coun = query_source_conta(qconta, ref_name);
        if (MAX_RDCON_COUNT < cont_coun)
            return 0x00;
        //
        contain *contp;
        char (*qcont)[CONTA_LENGTH] = qconta;
        unsigned int inde = 0x00;
        for (; (cont_coun > inde) && (*qcont)[0x00]; ++inde, ++rcont, ++qcont) {
            contp = (contain *) cache_value(qcont[0x00], conda_stm->lev3n_hm);
            if (!contp) return 0x00;
            // OSEVPF("contp->cont_name:|%s|\n", contp->cont_name);
            PRIN_osv_oid_t_stri(&(contp->cont_obid));
            OBID_BINARY_COPY(rcont, &(contp->cont_obid))
            if (contp->contype) {
                cont_type[0x00] |= REFER_CONTA_TYPE;
            } else cont_type[0x00] |= ENTIT_CONTA_TYPE;
        }
        // rcont[0x00]->refe_coun
        // OSEVPF("parse_refere_contn end.....\n");
        return cont_coun;
    }


#ifdef __cplusplus
}
#endif

#endif /* CREAQ_UTILI_H */

