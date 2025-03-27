
/* 
 * File:   insda_utili.h
 * Author: James Xu
 *
 * Created on 2024.4.1, AM 8:57
 */

#ifndef INSDA_UTILI_H
#define INSDA_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    lv2pme *creat_lv2pm_insda(inst_hmap *insda_stm, base_valu *baval, lv2p_decl_t *lv2dt, char *lv2_dec);
    lv2p_expa_t *creat_lv2pe_insda(base_valu *baval, lv2p_decl_t *lv2dt);

#ifdef __cplusplus
}
#endif

#endif /* INSDA_UTILI_H */

