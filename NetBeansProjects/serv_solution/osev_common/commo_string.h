
/* 
 * File:   commo_string.h
 * Author: James Xu
 *
 * Created on 2022.11.10, AM 9:23
 */

#ifndef COMMO_STRING_H
#define COMMO_STRING_H

#include "logger.h"
#include "commo_macro.h"
#include "osev_datyp.h"
#include "osev_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#define PREDI_TYPE_EXCEP -1
#define PREDI_TYPE_OBJID 0x00
#define PREDI_TYPE_CONDI 0x01
#define PREDI_TYPE_TRAVE 0x02

    int check_condi_type(char *pamcon);
    int check_predi_type(char *pamcon);

    //
    unsigned int query_source_count(char *source);
    unsigned int query_source_conta(char (*qconta)[CONTA_LENGTH], char *source);



#ifdef __cplusplus
}
#endif

#endif /* COMMO_STRING_H */

