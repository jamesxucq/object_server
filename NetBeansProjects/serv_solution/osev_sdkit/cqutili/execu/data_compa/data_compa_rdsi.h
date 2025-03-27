
/* 
 * File:   data_compa_rdsi.h
 * Author: James Xu
 *
 * Created on 2024.6.21, AM 9:15
 */

#ifndef DATA_COMPA_RDSI_H
#define DATA_COMPA_RDSI_H

#include <stdio.h>
#include "commo_header.h"
#include "rive_struct.h"
#include "../conte_resou.h"

#ifdef __cplusplus
extern "C" {
#endif

    // rdsi
    // not equal   
    int data_text_noteq_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_noteq_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_noteq_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_noteq_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);

    // equal   
    int data_text_equal_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_equal_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_equal_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_equal_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);
    int data_rid_equal_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *rid_valu);

    // great
    int data_text_great_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_great_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_great_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_great_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);

    //
    int data_text_leseq_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_leseq_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_leseq_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_leseq_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);

    //
    int data_text_less_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_less_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_less_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_less_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);

    //
    int data_text_greeq_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_greeq_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_greeq_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_greeq_rdsi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);


#ifdef __cplusplus
}
#endif

#endif /* DATA_COMPA_RDSI_H */

