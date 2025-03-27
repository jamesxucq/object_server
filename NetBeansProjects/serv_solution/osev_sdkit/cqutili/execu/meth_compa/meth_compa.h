
/* 
 * File:   meth_compa.h
 * Author: James Xu
 *
 * Created on 2021.7.8, PM 2:51
 */

#ifndef METH_COMPA_H
#define METH_COMPA_H

#include <stdio.h>
#include "commo_header.h"
#include "rive_struct.h"
#include "../conte_resou.h"

#ifdef __cplusplus
extern "C" {
#endif

    // not equal   
    int meth_text_noteq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_noteq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_noteq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_noteq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);

    // equal   
    int meth_text_equal(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_equal(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_equal(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_equal(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);
    int meth_rid_equal(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *rid_valu);

    // great
    int meth_text_great(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_great(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_great(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_great(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);

    //
    int meth_text_leseq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_leseq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_leseq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_leseq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);

    //
    int meth_text_less(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_less(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_less(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_less(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);

    //
    int meth_text_greeq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu);
    int meth_lolo_greeq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu);
    int meth_ullo_greeq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu);
    int meth_doub_greeq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu);

#ifdef __cplusplus
}
#endif

#endif /* METH_COMPA_H */

