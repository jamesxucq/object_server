
/* 
 * File:   fstoid.h
 * Author: James Xu
 *
 * Created on 2022.11.11, PM 2:22
 */

#ifndef FSTOID_H
#define FSTOID_H

#ifdef __cplusplus
extern "C" {
#endif

#define STROBID_TOK  "Stroid"
#define STROBID_SLEN  0x06

    // Stroid("fdeac7ec9a385a6304000000", "fdeac7ec9a385a6304000000")
    // Stroid("bb7ddcfb10c0ff6401000000")
    // return obid count

    inline char *valid_stroid_type(char *stri) {
        PASS_BLANK(stri)
        if (strncmp(STROBID_TOK, stri, STROBID_SLEN))
            return NULL;
        stri += STROBID_SLEN;
        //
        return stri;
    }

    // Stroid("fdeac7ec9a385a6304000000", "fdeac7ec9a385a6304000000")
    // Stroid("bb7ddcfb10c0ff6401000000")
    // return obid count, -1 is error. 

    inline int func_stroid_sing(osv_oid_t *binary_obid, char *plain_obid) {
        plain_obid = valid_stroid_type(plain_obid);
        if (!plain_obid) return -1;
#ifdef _DEBUG
        printf("[FUNC]:func_stroid_sing => plain_obid:|%s|\n", plain_obid);
#endif // _DEBUG
        return param_stroid_sing(binary_obid, plain_obid);
    }

    inline int func_stroid_mult(osv_oid_t *binary_obid, char *plain_obid) {
        plain_obid = valid_stroid_type(plain_obid);
        if (!plain_obid) return -1;
#ifdef _DEBUG
        printf("[FUNC]:func_stroid_mult => plain_obid:|%s|\n", plain_obid);
#endif // _DEBUG
        return param_stroid_mult(binary_obid, plain_obid);
    }



#ifdef __cplusplus
}
#endif

#endif /* FSTOID_H */

