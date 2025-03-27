
/* 
 * File:   funct_header.h
 * Author: James Xu
 *
 * Created on 2022.11.11, PM 2:35
 */

#ifndef FUNCT_HEADER_H
#define FUNCT_HEADER_H


#ifdef __cplusplus
extern "C" {
#endif

    //
#define FUNCTION_TOK        "Func"
#define FUNCTION_SLEN        0x04
#define SPACE_DELIM_TOK     ':'  
    //
#include "fstoid.h"

    //

    inline char *valid_functi_type(char *stri) {
        PASS_BLANK(stri)
        if (strncmp(FUNCTION_TOK, stri, FUNCTION_SLEN))
            return NULL;
        stri += FUNCTION_SLEN;
        PASS_BLANK(stri)
        if (SPACE_DELIM_TOK != stri[0x00])
            return NULL;
        ++stri;
        PASS_BLANK(stri)
                //
        return stri;
    }

    //

    inline int pretr_functi_pamvs(const char **pamvp) {
#ifdef _DEBUG
        printf("[FUNC]:pretr_functi_pamvs\n");
#endif // _DEBUG
        char *func_invk;
        osv_oid_t binary_obid;
        //
        for (; pamvp[0x00]; ++pamvp) {
#ifdef _DEBUG
            printf("pamvp[0x00]:|%s|\n", pamvp[0x00]);
#endif // _DEBUG
            func_invk = valid_functi_type((char *) pamvp[0x00]);
            if (!func_invk) continue;
#ifdef _DEBUG
            printf("func_invk:|%s|\n", func_invk);
#endif // _DEBUG
            if (0x01 == func_stroid_sing(&binary_obid, func_invk))
                ESMCPY_OBID(((char *) pamvp[0x00]), &binary_obid);
#ifdef _DEBUG
            char obid_stri[OBJE_IDENTI_ZLEN];
            printf("binary_obid:|%s|\n", oidstr(obid_stri, &binary_obid));
#endif // _DEBUG
        }
        //
        return 0x00;
    }

    inline int pretr_source_obid(osv_oid_t *binary_obid, char *plain_obid) {
        plain_obid = valid_functi_type(plain_obid);
        if (!plain_obid) return -1;
        return func_stroid_mult(binary_obid, plain_obid);
    }

#ifdef __cplusplus
}
#endif

#endif /* FUNCT_HEADER_H */

