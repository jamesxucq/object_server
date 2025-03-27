
/* 
 * File:   pre_instru_ite.h
 * Author: James Xu
 *
 * Created on 2023.4.14, PM 3:12
 */

#ifndef PRE_INSTRU_ITE_H
#define PRE_INSTRU_ITE_H

#include "instru.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    inline int instru_prepare_ite(clit_inst *cinst, clit_stat_t *clit_stat) {
        if (ATTRI_INSTRUC & cinst->inst_attrib) {
            return pretr_instruct_comd(cinst, clit_stat->run_level);
        } else if (ATTRI_TOOLKIT & cinst->inst_attrib) {
            return 0x00;
        } else return -1;
        return 0x00;
    }

#ifdef __cplusplus
}
#endif

#endif /* PRE_INSTRU_ITE_H */

