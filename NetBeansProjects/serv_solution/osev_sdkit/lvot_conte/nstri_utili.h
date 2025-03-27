
/* 
 * File:   nstri_utili.h
 * Author: James Xu
 *
 * Created on 2017.1.8, PM 2:59
 */

#ifndef NSTRI_UTILI_H
#define NSTRI_UTILI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#define FILLI_HANDLE_NAME(HANDN, LVTPN, LEVON, OIVKFMT) { \
    char *last_str = lscpy(HANDN, LVTPN); \
    last_str = lccpy(last_str, '_'); \
    last_str = lscpy(last_str, LEVON); \
    last_str = lccpy(last_str, '_'); \
    lscpy(last_str, OIVKFMT); }

#define FILLI_LIBRARY_NAME(LIBR_NAME, FILE_NAME, SUFFIX) { \
    char *last_str = lscpy(LIBR_NAME, FILE_NAME); \
    lscpy(last_str, SUFFIX); }

    //
    char *filli_relom_objen(char **obje_namp, char *_ofile_, char *basen, lev1_list *l1lst);
    char *filli_reloc_objen(char **obje_namp, char *_ofile_, char *basen, lv2p_list *l2lst);

    //
    void ulink_relom_objec(char *basen, lev1_list *l1lst);
    void ulink_reloc_objec(char *basen, lv2p_list *l2lst);

    //
    char *filli_osbsc_name(OUT char *osize, OUT char *bindn, OUT char *solvn, char *lv2pn);

#ifdef __cplusplus
}
#endif

#endif /* NSTRI_UTILI_H */

