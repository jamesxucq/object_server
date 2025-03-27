
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

#define STROBID_TOK  "stroid"
#define STROBID_SLEN  0x06

    // func:stroid("fdeac7ec9a385a6304000000", "fdeac7ec9a385a6304000000")
    // func:stroid("bb7ddcfb10c0ff6401000000")
    // return obid count

    inline char *valid_stroid_type(char *stri) {
        PASS_BLANK(stri)
        if (strncmp(STROBID_TOK, stri, STROBID_SLEN))
            return NULL;
        stri += STROBID_SLEN;
        //
        return stri;
    }

    // func:stroid("fdeac7ec9a385a6304000000", "fdeac7ec9a385a6304000000")
    // func:stroid("bb7ddcfb10c0ff6401000000")
    // return obid count, -1 is error. 

    inline int func_stroid_sing(osv_oid_t *binary_obid, char *plain_obid) {
        plain_obid = valid_stroid_type(plain_obid);
        if (!plain_obid) return -1;
        // CLIEPF("valid_fstroid_type:|%s|\n", last_str);
        return param_stroid_sing(binary_obid, plain_obid);
    }

    inline int func_stroid_mult(osv_oid_t *binary_obid, char *plain_obid) {
        plain_obid = valid_stroid_type(plain_obid);
        if (!plain_obid) return -1;
        // CLIEPF("valid_fstroid_type:|%s|\n", last_str);
        return param_stroid_mult(binary_obid, plain_obid);
    }

    // ESMCPY_OBID(DEST, SORC)
    // ESMCPY_BINARY(DEST, SORC, SIZE)
#define PACK_COMPLEX_OBID(DEST, SORC, COUNT) { \
    if(0x01 == COUNT) \
        ESMCPY_OBID(DEST, SORC) \
    else ESMCPY_BINARY(DEST, SORC, sizeof (osv_oid_t) * COUNT) \
}


#ifdef __cplusplus
}
#endif

#endif /* FSTOID_H */

