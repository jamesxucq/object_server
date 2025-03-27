
/* 
 * File:   lv1_cont.h
 * Author: James Xu
 *
 * Created on 2017.2.13, AM 9:05
 */

#ifndef LEVO_CONTE_H
#define LEVO_CONTE_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int creat_lev1_conte(char *basen);

    //
    int appen_conte_lv1me(char *basen, char *lv2pn, lev1me *lv1me, char *lev1_librn);
    int updat_conte_lv1me(char *basen, char *lv2pn, lev1me *lv1me, char *lev1_librn);
    int delet_conte_lv1id(char *basen, lev1id *lev1i);
    int delet_conte_lev1m(char *basen, lev1_meta *lev1m);

    //

    struct _lev1_cont_i_ {
        char lv2pn[LVTN_LENGTH];
        char lev1n[LVON_LENGTH];
        CALLER_TYPE oivk_retyp; // oivk return type 
        char oivk_fmtsp[FMTST_COUNT_ZTAI]; // out invoke params format string
        int oivk_size; // oivk struct length
        //
        char lev1_librn[LVON_LENGTH];

        union {
            unsigned int sibling;
            unsigned int recycle;
        };
    };

    typedef struct _lev1_cont_i_ lev1_cont_i;

    //

    struct _lev1_cont_t_ {
        FILE *contp;
        lev1_cont_i l1i_nod;
    };

    typedef struct _lev1_cont_t_ lev1_cont_t;

    //

    unsigned int open_conte_lev1(lev1_cont_t *ocont, char *basen);
    void close_conte_lev1(lev1_cont_t *ocont);
    unsigned int read_conte_lev1(lev1_cont_t *ocont, unsigned int reind);


#ifdef __cplusplus
}
#endif

#endif /* LEVO_CONTE_H */

