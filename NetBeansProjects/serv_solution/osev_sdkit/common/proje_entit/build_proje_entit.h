
/* 
 * File:   build_proje_entit.h
 * Author: James Xu
 *
 * Created on 2022.12.20, PM 1:56
 */

#ifndef BUILD_PROJE_ENTIT_H
#define BUILD_PROJE_ENTIT_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int build_objec_strea_ensi(FILE *proj_data, osv_oid_t *key_obid, PK_ITEM *svalu);
    int build_objec_strea_enob(FILE *proj_data, osv_oid_t *key_obid, PK_ITEM *svalu);

    // normal
    int build_proje_strea_enco(FILE *proj_data, PK_ITEM *objnod, PK_ITEM *svalu1, PK_ITEM *svalu2, field_resul_co *fieres);
    int build_proje_objec_enco(paki_memo_t *objnod, PK_ITEM *svalu1, PK_ITEM *svalu2, field_resul_co *fieres);


#ifdef __cplusplus
}
#endif

#endif /* BUILD_PROJE_ENTIT_H */

