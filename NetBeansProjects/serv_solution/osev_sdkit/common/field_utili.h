
/* 
 * File:   field_utili.h
 * Author: James Xu
 *
 * Created on 2022.10.8, AM 9:34
 */

#ifndef FIELD_UTILI_H
#define FIELD_UTILI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int field_lv2me_ensi(char *field_str, lv2pme **lv2mep);
    int field_lv2me_resi(char *field_str, lv2pme *lv2me);
    int field_lv2me_reco(char *field_str, lv2pme *lv2me);

    //
    int fires_lv2pn_type_enco(field_resul_co *fieres, lv2pme **lv2mep);
    int fires_lv2pn_item_enco(field_resul_co *fieres, lv2pme **lv2mep);

    //
    int find_lv2pn_meta(lv2pme **lv2mep, lv2pm_hmap *lv2pm_stm, char *desl2n, contain **sconp);
    int find_lv2po_meta(lv2pme **lv2mep, lv2pm_hmap *lv2pm_stm, osv_oid_t *desl2o, contain **sconp);
    int find_lv2pm_meta(lv2pme **lv2mep, lv2pm_hmap *lv2pm_stm, lv2pme *lv2dme, contain **sconp);

#ifdef __cplusplus
}
#endif

#endif /* FIELD_UTILI_H */

