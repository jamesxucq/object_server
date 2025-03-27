
/* 
 * File:   klist_ite.h
 * Author: James Xu
 *
 * Created on 2024.5.15, PM 3:44
 */

#ifndef KLIST_ITE_H
#define KLIST_ITE_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int requ_lev1_iden(char *lev1_cont, osv_oid_t *coll_obid, char *lev1n, osev_clie *oclie);
    int requ_lv2p_atti(char *lv2p_cont, const char *lv2pn, osev_clie *oclie);
    // extern integrality
    int requ_lv2p_extint(bool_osv *lv2p_extern, bool_osv *lv2p_integr, char *lv2p_cont, const char *lv2pn, const osev_clie *oclie);
    int requ_lv2p_expand(char *lv2p_cont, const char *lv2pn, osev_clie *oclie);
    int requ_lv2p_conte(char *lv2p_cont, const char *lv2pn, osev_clie *oclie);
    int split_lv2p_lev1(char *lv2p_decla, char *lev1np[LEVO_COUNT], char *_mline_, char *lv2p_cont);



#ifdef __cplusplus
}
#endif

#endif /* KLIST_ITE_H */

