
/* 
 * File:   lv2p_list.h
 * Author: James Xu
 *
 * Created on 2016.12.18, AM 10:18
 */

#ifndef LVTP_LIST_H
#define LVTP_LIST_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    lv2p_attri *creat_lv2p_atti(lv2pm_hmap *lv2pm_stm, osv_oid_t *lv2p_obid, char *lv2pn);
    int destr_lv2p_atti(lv2pm_hmap *lv2pm_stm, osv_oid_t *lv2p_obid);
    int delet_lv2p_atti(lv2pm_hmap *lv2pm_stm, char *lv2pn);

    //

    integra *appe_integ_list(integra **olsth, int range_type, char *lv2pn, char *lev1n);
    integra *dele_integ_iden(integra **olsth, char *lv2pn, char *lev1n);
    integra *dele_integ_lv2p(integra **olsth, char *lv2pn);
    integra *find_integ_iden(integra *olist, char *lv2pn, char *lev1n);

    //
    inherit *addi_imeth(inherit **ilsth, int rang_type, char *lv2pn, char *lev1n);
    inherit *addi_inhe_meth(inherit **ilsth, char *lv2pn, char *lev1n);
    inherit *addi_inhe_lev1(inherit **ilsth, char *lv2pn, char *lev1n);
    inherit *addi_inhe_lv2p(inherit **ilsth, char *lv2pn);
    inherit *addi_inhe_clas(inherit **ilsth, char *lv2pn);

    //
    inherit *dele_imeth(inherit **ilsth, int rang_type, char *lv2pn, char *lev1n);
    inherit *dele_inhe_meth(inherit **ilsth, char *lv2pn, char *lev1n);
    inherit *dele_inhe_lev1(inherit **ilsth, char *lv2pn, char *lev1n);
    inherit *dele_inhe_lv2p(inherit **ilsth, char *lv2pn);
    inherit *dele_inhe_clas(inherit **ilsth, char *lv2pn);

    //
    inherit *find_inher_iden(inherit *ilist, char *lv2pn, char *lev1n);
    inherit *find_inher_levo(inherit *ilist, int rang_type, char *lv2pn, char *lev1n);
    inherit *find_inher_lvtp(inherit *ilist, int rang_type, char *lv2pn);
#define IMETH_DELET(ILIST) free(ILIST)

    //
    lv1_cont *modi_l1cnod_conte(lv1_cont *l1lsnd, char *lev1n, char *fmtsop, char *lev1_cont);

    //

    lv1_cont *find_l1cnod_name(lv1_cont *l1lsnd, char *lev1n);
    lv1_cont *find_l1cnod_decl(lv1_cont *l1lsnd, char *lev1n, char *decla);
    lv1_cont *find_l1cnod_iden(lv1_cont *l1lsnd, char *lev1n, char *fmtsop);
    lv1_cont *dele_l1cnod_iden(lv1_cont **l1clsth, char *lev1n, char *fmtsop);
    lv1_cont *dele_l1cnod_decl(lv1_cont **l1clsth, char *lev1n, char *decla);

    //

#define CLAM_STRU_DELE(LVTDI) \
    l1clst_dele(LVTDI.l1con_list);

#define RETU_DELM(LVTDI, RET_VAL) { \
        l1clst_dele(LVTDI.l1con_list); \
        return RET_VAL; \
    }

#define RETU_DELMP(LVTDIP, RET_VAL) { \
        l1clst_dele((LVTDIP)->l1con_list); \
        return RET_VAL; \
    }

#ifdef __cplusplus
}
#endif

#endif /* LVTP_LIST_H */

