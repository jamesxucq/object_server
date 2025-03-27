
/* 
 * File:   costr_utili.h
 * Author: James Xu
 *
 * Created on 2022.11.15, AM 10:13
 */

#ifndef COSTR_UTILI_H
#define COSTR_UTILI_H

#include "kcomm_types.h"
#include "lv2p_decla.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    inline char *conve_types(char *types, char *data, char *slen) {
        if ((!strcmp("char", data) || !strcmp("byte", data)) && slen[0x00])
            types = lscpy(types, slen);
        KV_STCH_EQUA(types[0x00], ostyp_fmtst_dict, data);
        (++types)[0x00] = '\0';
        return types;
    }
    
    // trans-serve

    inline char *ostyp_format_char(char *fmtst, char *ostyp) {
        if (strchr(ostyp, '&'))
            fmtst = lccpy(fmtst, 'R');
        KV_STCH_LCPY(fmtst, ostyp_fmtst_dict, ostyp);
        return fmtst;
    }
    
    //
    int split_data_styl(char *type, char *valu, char *size, char *data);

    //
    char *split_lv2pn(char *lv2pn, char *lv2_dec);

    //
    int comp_stri_array(char **lv2pnp1, char **lv2pnp2);

    // -1:error 0x00:constructor 0x01:normal

    inline int gener_const_type(char *lv2pn, char *lev1n) {
        return strcmp(lv2pn, lev1n);
    }

    char *check_extend(char *lv2pn, char *file_name, char *name_extend);
    
#ifdef __cplusplus
}
#endif

#endif /* COSTR_UTILI_H */

