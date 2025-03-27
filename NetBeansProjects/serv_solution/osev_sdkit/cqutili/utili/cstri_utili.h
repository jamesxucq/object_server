
/* 
 * File:   cstri_utili.h
 * Author: James Xu
 *
 * Created on 2021.4.26, PM1:51
 */

#ifndef CSTRI_UTILI_H
#define CSTRI_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _pams_invk_ {
        char *pamvp[PARAM_COUNT];
        char _sline_[LARGE_CONTE_SIZE];
    };

    typedef struct _pams_invk_ pams_invk;

    //
    char *qinvo_parms(pams_invk *pamivk, char *pamcon);
    char *split_qinvo(char *objide, char *meth_str, char *pamcon, char *meth_line);

    //
    int decode_invok_parms(char *lv2pn, char *lev1n, pams_invk *pamivk, char *invop_str);
    char *filli_binary_handn(char *handn, char *lv2pn, char *lev1n, char **pamvp);

    //
    int split_invok(char *iclan, char *imetn, char *invop, char *lv2pn);


#ifdef __cplusplus
}
#endif

#endif /* CSTRI_UTILI_H */

