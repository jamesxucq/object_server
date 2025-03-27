
/* 
 * File:   filli_clang.h
 * Author: James Xu
 *
 * Created on 2023.10.7, PM 3:34
 */

#ifndef FILLI_CLANG_H
#define FILLI_CLANG_H

#include "commo_header.h"

#include "lv2p_list.h"
#include "../../clit_struct.h"
#include "filli_inline.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int filli_lv2p_conte(clit_resu *resul, char *clang_str, char *lv2pn, char *basen);
    int filli_lev1_conte(clit_resu *resul, char *clang_str, char *lv2pn, char *basen);

    //
    int filli_ointe_comple(char *line_oivk, char (*oivk_data)[PARAM_LENGTH]);
    char *filli_lcon_defin(char *clang_str, char *lv2pn, lv2p_prop *lv2nod);

    //
    char *filli_meta_seria(char *clang_str, char *lv2pn, lv2p_prop *lv2nod);
    char *filli_meta_deseri(char *clang_str, char *lv2pn, lv2p_prop *lv2nod);

    //
#define FILLI_ELVTP_HEAD(CLANG_STR, LVTPN) \
    lsprif(CLANG_STR, "class %s { \n", LVTPN);

#define FILLI_ELVTP_TAIL(CLANG_STR) \
    lscpy(CLANG_STR, "}; \n");

    //
    char *filli_lv2p_based(char *clang_str, class_meta *clsmt, lv2p_expa_t *lv2expt);

    //

    char *filli_stati_const(char *clang_str, class_meta *clsmt, lv2p_prop *lv2nod);

    //

    char *filli_lcon_decla(char *clang_str, char *lv2pn, lv2p_prop *lv2nod);
    char *filli_elv2p_decla(char *clang_str, lv2p_prop *lv2nod);
    // char *filli_meta_decla(char *clang_str, char *lv2pn);

#define FILLI_METHO_SECTI(CLANG_STR) lscpy(CLANG_STR, "public: \n");

    // trans-serve

    struct _parse_metho_ {
        char lv2pn[LVTN_LENGTH];
        char lev1n[LVON_LENGTH];
        char oivk_retyp_pm[PAMTYP_LENGTH];
        int retyp_valu;
        char line_oivk[LVON_LENGTH];
        char oivk_fmtsp_pm[FMTST_COUNT_ZTAI]; // out invoke params format string
        char ibind[LVON_LENGTH];
        char lev1_body[LARGE_TEXT_SIZE];
    };

    typedef struct _parse_metho_ parse_metho;

    // trans-serve
    /*
    #define INCL_OSVOID_DEFI    "#pragma pack(1) \n \
    typedef struct { \n \
    unsigned int osev_unique; \n \
    unsigned long long stoid; \n \
    } osv_oid_i; \n \
    #pragma pack() \n"
    #define INCL_PACKING_HEAD "#include \"packing.h\"\n"
     */
#define INCL_SYSTEM_HEAD "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <stdint.h>\n"
#define INCL_OSVOBID_HEAD "#include <osev_obid.h>\n"
#define INCL_STRZUTI_HEAD "#include <strz_utili.h>\n"
#define INCL_OREVAL_HEAD "#include <osev_reval.h>\n"

    // trans-serve

    inline char *filli_ohead_text(char *clang_str) {
        clang_str = lscpy(clang_str, INCL_SYSTEM_HEAD);
        clang_str = lscpy(clang_str, INCL_OSVOBID_HEAD);
        clang_str = lscpy(clang_str, INCL_STRZUTI_HEAD);
        clang_str = lscpy(clang_str, INCL_OREVAL_HEAD);
        return clang_str;
    }

    // trans-serve
    char *filli_class_text(char *clang_str, char *lv2pn, char (*lv2p_prop)[PARAM_LENGTH]);

    // trans-serve

    inline void filli_ointe_simple(char *line_oivk, char *lv2pn) {
        line_oivk = lscpy(line_oivk, "(struct ");
        line_oivk = lscpy(line_oivk, lv2pn);
        line_oivk = lscpy(line_oivk, " *this)");
    }
    //
    char *filli_const_defin(char *clang_str, parse_metho *metho);
    char *filli_metho_defin(char *clang_str, parse_metho *metho);

    //
    char *filli_const_decla(char *clang_str, parse_metho *metho);
    char *filli_metho_decla(char *clang_str, parse_metho *metho);


#ifdef __cplusplus
}
#endif

#endif /* FILLI_CLANG_H */

