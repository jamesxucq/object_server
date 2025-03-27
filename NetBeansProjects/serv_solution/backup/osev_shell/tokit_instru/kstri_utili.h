
/* 
 * File:   kstri_utili.h
 * Author: James Xu
 *
 * Created on 2017.623, PM 1:53
 */

#ifndef KSTRI_UTILI_H
#define KSTRI_UTILI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    char *find_metho_decla(char *l1nsps, char *lv2p_cont);
    char *find_metho_defin(char *l1nsps, char *lv2p_cont);

    // trans-serve
    char *split_class_conte(char *lv2_dec, char *lv2p_cont);

    //
#define TYPE_LVTP_DEFINE    0x01
#define TYPE_LEVO_CONTE     0x02
#define TYPE_LVTP_CONTE     0x03
    char *next_conte_type(char *line_cont, unsigned int *line_type, char *lv2p_cont);

#define KLST_LVTP_ATTRIB   0x0001
#define KLST_LVTP_EXPAND   0x0002
#define KLST_LEVO_CONTE    0x0004
#define KLST_LVTP_CONTE    0x0008
    unsigned int build_klist_type(char *list_type);


#ifdef __cplusplus
}
#endif

#endif /* KSTRI_UTILI_H */

