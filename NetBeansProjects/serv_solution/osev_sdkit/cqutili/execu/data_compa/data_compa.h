
/* 
 * File:   data_compa.h
 * Author: James Xu
 *
 * Created on 2021.4.1, PM2:51
 */

#ifndef DATA_COMPA_H
#define DATA_COMPA_H

#include <stdio.h>
#include "commo_header.h"
#include "rive_struct.h"
#include "../conte_resou.h"

#ifdef __cplusplus
extern "C" {
#endif

    // not equal   
    int data_text_noteq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_noteq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_noteq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_noteq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);

    // equal   
    int data_text_equal(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_equal(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_equal(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_equal(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);
    int data_rid_equal(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *rid_valu);

    // great
    int data_text_great(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_great(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_great(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_great(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);

    //
    int data_text_leseq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_leseq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_leseq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_leseq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);

    //
    int data_text_less(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_less(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_less(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_less(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);

    //
    int data_text_greeq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_greeq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_greeq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_greeq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);

#ifdef __cplusplus
}
#endif

#endif /* DATA_COMPA_H */

