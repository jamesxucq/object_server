
/* 
 * File:   meth_compa_rssi.h
 * Author: James Xu
 *
 * Created on 2024.6.20, PM 2:23
 */

#ifndef METH_COMPA_RSSI_H
#define METH_COMPA_RSSI_H

#include <stdio.h>
#include "commo_header.h"
#include "rive_struct.h"
#include "../conte_resou.h"

#ifdef __cplusplus
extern "C" {
#endif

    // rssi
    // not equal   
    int meth_text_noteq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_noteq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_noteq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_noteq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);

    // equal   
    int meth_text_equal_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_equal_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_equal_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_equal_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);
    int meth_rid_equal_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *rid_valu);

    // great
    int meth_text_great_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_great_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_great_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_great_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);

    //
    int meth_text_leseq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_leseq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_leseq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_leseq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);

    //
    int meth_text_less_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_less_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_less_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_less_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);

    //
    int meth_text_greeq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_greeq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_greeq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_greeq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);

    // rdsi
    // not equal   
    int meth_text_noteq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_noteq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_noteq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_noteq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);

    // equal   
    int meth_text_equal_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_equal_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_equal_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_equal_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);
    int meth_rid_equal_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *rid_valu);

    // great
    int meth_text_great_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_great_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_great_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_great_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);

    //
    int meth_text_leseq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_leseq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_leseq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_leseq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);

    //
    int meth_text_less_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_less_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_less_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_less_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);

    //
    int meth_text_greeq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_greeq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_greeq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_greeq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);


#ifdef __cplusplus
}
#endif

#endif /* METH_COMPA_RSSI_H */

