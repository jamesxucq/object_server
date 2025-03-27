
/* 
 * File:   cli_struct.h
 * Author: James Xu
 *
 * Created on 2017.1.17, PM 3:19
 */

#ifndef CLI_STRUCT_H
#define CLI_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "osev_clie_clang.h"
#include "cstri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _clie_stat_t_ {
        uint32 cli_mode;
        uint32 run_level;
    };

    typedef struct _clie_stat_t_ clie_stat_t;

    //

    struct _clie_resu_ {
        int resu_type; // 0x00:memory 0x01:stream
        uint64 resu_leng;
        FILE *resu_stram;
        char resu_data[RESP_DATA_SIZE];
    };

    typedef struct _clie_resu_ clie_resu;

    //

    int resul_initial(clie_resu *resul);
    void reset_result(clie_resu *resul);
    void final_result(clie_resu *resul);

    //

#pragma pack(1)

    struct _cli_oid_t_ {
        unsigned int osev_unique;
        unsigned int time_stamp;
        unsigned int counter;
    };
#pragma pack()

    typedef struct _cli_oid_t_ cli_oid_t;

    //

#pragma pack(1)

    struct _cli_sid_t_ {
        unsigned int time_stamp;
        unsigned int counter;
    };
#pragma pack()

    typedef struct _cli_sid_t_ cli_sid_t;

    // modify method

    enum OSEV_LEVE_METH {
        OSEV_INVAL = 0x00,
        OSEV_COMAND,
        OSEV_STATU,
        OSEV_PRIVI
    };

    enum BASE_LEVE_METH {
        BASE_INVAL = 0x00,
        BASE_COMAND,
        BASE_STATU,
        BASE_PRIVI
    };
    //
    //#define     BCOMD_OPEN      0x00 // start Create
    //#define     BCOMD_CLOSE     0x01 // shutdown

    enum OSVB_COMAND_INVK {
        CMDI_INVAL = 0x00,
        CMDI_OPEN, // start create
        CMDI_CLOSE // shutdown
    };
    extern int osev_comand_tab[];
    extern int base_comand_tab[];

    // modify method
    //#define     BSTAT_ECHO      0x00
    //#define     BSTAT_STATUS    0x01
    //#define     BSTAT_STATIS    0x02

    enum OSVB_STATU_INVK {
        STAI_INVAL = 0x00,
        STAI_ECHO,
        STAI_STATUS,
        STAI_STATIS
    };
    extern int osev_status_tab[];
    extern int base_status_tab[];

    // modify method
    //#define     BPRIV_LIST       0x00
    //#define     BPRIV_ROLE       0x01
    //#define     BPRIV_USER       0x02

    enum OSVB_PRIVI_INVK {
        PRII_INVAL = 0x00,
        PRII_LIST,
        PRII_ROLE,
        PRII_USER
    };
    extern int osev_privi_tab[];
    extern int base_privi_tab[];

    // modify method

    enum LEVE_INVOK_METH {
        LEVO_INVAL = 0x00,
        LEVO_POST,
        LEVO_LIST,
        LEVO_CREAT,
        LEVO_DROP,
        LEVO_REPLA,
        LEVO_INTEGRA,
        LEVO_RELOAD
    };

    // modify method

    enum LEVE_COLLE_METH {
        LVTP_INVAL = 0x00,
        LVTP_POST,
        LVTP_LIST,
        LVTP_CREAT,
        LVTP_DROP,
        LVTP_REPLA,
        LVTP_INTEGRA,
        LVTP_RELOAD
    };

    // modify method

    // #define ENTI_ECHO   0x10
    // #define     EECHO_OBJID    0x00
    // #define     EECHO_NAME     0x01
    // #define     EECHO_ATTRIB   0x02
    // #define     EECHO_STATIS   0x03

    enum ENTI_ECHO_INVK {
        EEHI_INVAL = 0x00,
        EEHI_OBJID,
        EEHI_NAME,
        EEHI_ATTRIB,
        EEHI_STATIS
    };
    extern int const_echo_tab[];

    enum LEVE_CONST_METH {
        LEVT_INVAL = 0x00,
        LEVT_POST,
        LEVT_ECHO,
        LEVT_CREAT,
        LEVT_DROP,
        LEVT_UPDAT,
        LEVT_INSER,
        LEVT_SEARO,
        LEVT_INVOK
    };

    // modify method

    // #define QUER_ECHO   0x10
    // #define     QECHO_OBJID    0x00
    // #define     QECHO_NAME     0x01
    // #define     QECHO_ATTRIB   0x02
    // #define     QECHO_STATIS   0x03

    enum QUER_ECHO_INVK {
        QEHI_INVAL = 0x00,
        QEHI_OBJID,
        QEHI_NAME,
        QEHI_ATTRIB,
        QEHI_STATIS
    };
    extern int query_echo_tab[];

    enum LEVE_QUERY_METH {
        LVFP_INVAL = 0x00,
        LVFP_POST,
        LVFP_ECHO,
        LVFP_CREAT,
        LVFP_DROP,
        LVFP_UPDAT,
        LVFP_INSER,
        LVFP_SEARQ,
        LVFP_FACTO,
        LVFP_INVOK
    };

    //

    struct _obje_valu_ {
        osv_oid_t obje_obid;
        char obje_iden[OBJN_LENGTH];
        int changed; // 0x00: not change, 0x01: changed 
    };

    typedef struct _obje_valu_ obje_valu;

#ifdef __cplusplus
}
#endif

#endif /* CLI_STRUCT_H */

