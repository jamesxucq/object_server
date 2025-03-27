
/* 
 * File:   data_compa_rssi.h
 * Author: James Xu
 *
 * Created on 2024.6.20, PM 2:21
 */

#ifndef DATA_COMPA_RSSI_H
#define DATA_COMPA_RSSI_H

#include <stdio.h>
#include "commo_header.h"
#include "rive_struct.h"
#include "../conte_resou.h"

#ifdef __cplusplus
extern "C" {
#endif

    // rssi
    // not equal   
    int data_text_noteq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_noteq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_noteq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_noteq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);
    
    // equal   
    int data_text_equal_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_equal_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_equal_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_equal_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);
    int data_rid_equal_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *rid_valu);

    // great
    int data_text_great_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_great_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_great_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_great_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);

    //
    int data_text_leseq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_leseq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_leseq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_leseq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);

    //
    int data_text_less_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_less_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_less_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_less_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);

    //
    int data_text_greeq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu);
    int data_lolo_greeq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu);
    int data_ullo_greeq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu);
    int data_doub_greeq_rssi(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu);
    
#ifdef __cplusplus
}
#endif

#endif /* DATA_COMPA_RSSI_H */

