
/* 
 * File:   fstoid.h
 * Author: james
 *
 * Created on 2022.11.11, PM 2:22
 */

#ifndef FSTOID_H
#define FSTOID_H

#ifdef __cplusplus
extern "C" {
#endif

#define STROID_TOK  "stroid"
#define STROID_SLEN  0x06

    // return oid count
    int func_stroid(osv_oid_t *bina_oid, char *obje_iden);



#ifdef __cplusplus
}
#endif

#endif /* FSTOID_H */

