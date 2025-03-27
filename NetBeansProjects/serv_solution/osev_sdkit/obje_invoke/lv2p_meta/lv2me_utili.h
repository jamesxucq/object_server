
/* 
 * File:   lv2me_utili.h
 * Author: James Xu
 *
 * Created on 2022.11.25, PM 4:08
 */

#ifndef LV2ME_UTILI_H
#define LV2ME_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    lv2pme *open_lv2p_meta(lv2pm_hmap *lv2pm_stm, osv_oid_t *lv2p_obid, char *lv2pn, lv2p_expa_t *lv2expt);
    // 0x00:hand refer zero. >0x00:refer number <0x00:error
    int close_lv2p_meta(lv2pm_hmap *lv2pm_stm, osv_oid_t *lv2p_obid);
    int delet_lv2p_meta(lv2pm_hmap *lv2pm_stm, char *lv2pn);

    //
    lv2pme *creat_lv2p_meta(inst_hmap *insda_stm, instda *lv2in, lv2p_expa_t *lv2expt, osv_oid_t *lv2p_obid);
    // 0x00:hand refer zero. >0x00:refer number <0x00:error
    int destr_lv2p_meta(inst_hmap *insda_stm, char *lv2_dec);

#ifdef __cplusplus
}
#endif

#endif /* LV2ME_UTILI_H */

