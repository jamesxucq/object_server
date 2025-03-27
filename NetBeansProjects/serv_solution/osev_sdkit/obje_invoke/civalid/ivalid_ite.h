
/* 
 * File:   ivalid_ite.h
 * Author: James Xu
 *
 * Created on 2024.10.14, PM 2:58
 */

#ifndef IVALID_ITE_H
#define IVALID_ITE_H

#ifdef __cplusplus
extern "C" {
#endif

    //

    inline int valid_postm_insrep_lv2pn(char *reque_lv2pn, char *space) {
        char param_lv2pn[LVTN_LENGTH];
        char *toksp;
        PASS_TBLANK(toksp, space)
                char *tokep = strchr(toksp + 0x01, ':');
        if (!tokep) return -1;
        strzcpy(param_lv2pn, toksp, tokep - toksp);
        //
        if (strcmp(reque_lv2pn, param_lv2pn))
            return -1;
        return 0x00;
    }

    //
    int valid_statm_list_ite(char *basen, char *lv2pn, lev1_meta *lev1m);
    int valid_statm_stati_ite(char *basen, char *lv2pn);
    int valid_cream_ite(char *basen, char *lv2pn, lev1_meta *lev1m);
    // int valid_relom_ite(char *lv2pn, lev1_meta *lev1m);    

    inline int valid_relom_ite(char *lv2pn, lev1_meta *lev1m) {
        if (!(HAVE_CLASN & lev1m->layout))
            return -1;
        if (strcmp(lv2pn, lev1m->lv2pn))
            return -1;
        OSEVPF("PASSED, valid_relom_ite\n");
        return 0x00;
    }

    int valid_replm_ite(char *basen, char *lv2pn, lev1_meta *lev1m, uint32 *forced);
    int valid_dropm_ite(respo_ctrl *resctl, char *basen, char *lv2pn, lev1_meta *lev1m);
    int valid_intem_ite(char *basen, char *lv2pn, lev1_meta *lev1m);

    // valid reload method
    int valid_rlmde_ite(char *basen, lev1_meta *lev1m);
    int valid_rlmme_ite(char *basen, lev1_meta *lev1m);
    int valid_rlmcl_ite(char *basen, lev1_meta *lev1m);

    //
    int check_iextem_ite(char *iexte_lv2pn, char *basen, char *space);

    //

#ifdef __cplusplus
}
#endif

#endif /* IVALID_ITE_H */

