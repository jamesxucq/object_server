
/* 
 * File:   chk_utili.h
 * Author: James Xu
 *
 * Created on 2023.4.12, PM 2:44
 */

#ifndef CHK_UTILI_H
#define CHK_UTILI_H

#include "query_bzl.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#define UINT64_LENGTH   sizeof(unsigned long long) // 0x0008

    //

    struct _valid_cobid_ {
        osv_oid_t chk_obid[DCONT_SCONT_COUNT]; // base / contain obid

        union {
            unsigned char vali_code[UINT64_LENGTH];
            uint64 vali_numb;
        };
    };

    typedef struct _valid_cobid_ valid_cobid;

    // 0x00:ok -1:error 
    int qecho_contn_valid(valid_cobid *vaoid, cont_lsmp *conda_stm, char *echo_cont);

    inline int qecho_conto_valid(valid_cobid *vaoid, osv_oid_t *cont_obid) {
        OSEVPF("[FUNC]:qecho_conto_valid\n");
        OBID_BINARY_COPY(&vaoid->chk_obid[0x00], cont_obid);
        vaoid->vali_numb = 0xFF;
        return 0x00;
    }

    inline int base_default_valid(valid_cobid *vaoid, osv_oid_t *base_obid) {
        OSEVPF("[FUNC]:base_default_valid\n");
        OBID_BINARY_COPY(&vaoid->chk_obid[0x00], base_obid);
        vaoid->vali_numb = 0xFF;
        return 0x00;
    }

    // it is very important, attention!!!
#define QPAM_ECHO_ROPRIV    0x02

    inline void qecho_multi_data(valid_cobid *vaoid, char **pamvp, void *uepriv) {
        pamvp[QPAM_ECHO_ROPRIV] = uepriv;
        vaoid->vali_numb = 0x00;
    }


    // 0x00:ok -1:error 
    int single_conta_valid(valid_cobid *vaoid, cont_lsmp *conda_stm, char *sing_cont);
    int creat_conta_valid(valid_cobid *vaoid, osv_oid_t *base_obid);
    int multip_conta_valid(valid_cobid *vaoid, cont_lsmp *conda_stm, char *mult_cont);
    int searc_conta_valid(valid_cobid *vaoid, cont_lsmp *conda_stm, char *dest_cont, char *sour_cont);
    int facto_conta_valid(valid_cobid *vaoid, cont_lsmp *conda_stm, char *dest_cont, char *sour_cont);


#ifdef __cplusplus
}
#endif

#endif /* CHK_UTILI_H */

