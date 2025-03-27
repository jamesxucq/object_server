
/* 
 * File:   lv2p_conte.h
 * Author: James Xu
 *
 * Created on 2017.2.13, AM 9:05
 */

#ifndef LVTP_CONTE_H
#define LVTP_CONTE_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int creat_lv2p_conte(char *basen);
    int appen_conte_lv2p(char *lv2pn, osv_oid_t *lv2p_obid, char *lv2p_fmtsd, uint64 data_size, char *basen);
    int updat_conte_lv2p(osv_oid_t *lv2p_obid, char *lv2p_fmtsd, uint64 data_size, char *basen);
    int delet_conte_lv2p(char *lv2pn, char *basen);

    //

    struct _lv2p_cont_i_ {
        osv_sid_i lv2p_stoid;
        char lv2pn[LVTN_LENGTH];
        char lv2p_fmtsd[FMTST_COUNT_ZTAI];
        uint64 data_size;

        union {
            unsigned int sibling;
            unsigned int recycle;
        };
    };

    typedef struct _lv2p_cont_i_ lv2p_cont_i;

    //

    struct _lv2p_cont_t_ {
        FILE *contp;
        lv2p_cont_i l2nod;
    };

    typedef struct _lv2p_cont_t_ lv2p_cont_t;

    //

    unsigned int open_conte_lv2p(lv2p_cont_t *dcont, char *basen);
    void close_conte_lv2p(lv2p_cont_t *dcont);
    unsigned int read_conte_lv2p(lv2p_cont_t *dcont, unsigned int reind);


#ifdef __cplusplus
}
#endif

#endif /* LVTP_CONTE_H */

