
/* 
 * File:   clit_struct.h
 * Author: James Xu
 *
 * Created on 2017.1.17, PM 3:19
 */

#ifndef CLIT_STRUCT_H
#define CLIT_STRUCT_H

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

    struct _clit_stat_t_ {
        uint32 cli_mode;
        uint32 run_level;
    };

    typedef struct _clit_stat_t_ clit_stat_t;

    //

    struct _clit_resu_ {
        int resu_type; // 0x00:memory 0x01:stream
        uint64 resu_leng;
        FILE *resu_stram;
        char resu_data[RESP_DATA_SIZE];
    };

    typedef struct _clit_resu_ clit_resu;

    //

    int resul_initial(clit_resu *resul);
    void reset_result(clit_resu *resul);
    void final_result(clit_resu *resul);

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

    enum OSEV_LEVEL_METH {
        OSEV_INVALID = 0x00,
        OSEV_POST,
        OSEV_STATUS,
        OSEV_COMAND,
        OSEV_PRIVILE
    };

    enum BASE_LEVEL_METH {
        BASE_INVALID = 0x00,
        BASE_POST,
        BASE_STATUS,
        BASE_COMAND,
        BASE_PRIVILE
    };
    //
    // modify method
    // #define     BSTAT_ECHO      0x00
    // #define     BSTAT_STATUS    0x01
    // #define     BSTAT_STATIS    0x02

    enum OSVB_STATUS_INVK {
        STAIU_INVALID = 0x00,
        STAIU_ECHO,
        STAIU_STATIS
    };
    extern int osev_status_tab[];
    extern int base_status_tab[];

    // #define     BCOMD_OPEN      0x00 // start Create
    // #define     BCOMD_CLOSE     0x01 // shutdown

    enum OSVB_COMAND_INVK {
        COMDI_INVALID = 0x00,
        COMDI_OPEN, // start create
        COMDI_CLOSE // shutdown
    };
    extern int osev_comand_tab[];
    extern int base_comand_tab[];

    // modify method
    // #define     BPRIV_LIST       0x00
    // #define     BPRIV_ROLE       0x01
    // #define     BPRIV_USER       0x02

    enum OSVB_PRIVILE_INVK {
        PRIVI_INVALID = 0x00,
        PRIVI_LIST,
        PRIVI_ROLE,
        PRIVI_USER
    };
    extern int osev_privile_tab[];
    extern int base_privile_tab[];

    // modify method
    // #define INVO_STATU       0x10
    // #define     ISTAT_LIST    0x00
    // #define     ISTAT_STATIS  0x01

    enum INVO_STATUS_INVK {
        ISTATU_INVALID = 0x00,
        ISTATU_LIST,
        ISTATU_STATIS
    };

    extern int invok_status_tab[];

    enum LEVE_INVOKE_METH {
        LEVO_INVALID = 0x00,
        LEVO_POST,
        LEVO_STATUS,
        LEVO_CREATE,
        LEVO_DROP,
        LEVO_REPLACE,
        LEVO_INTEGRA,
        LEVO_RELOAD
    };

    // modify method

    // #define COLE_STATU       0x10
    // #define     CSTAT_LIST    0x00
    // #define     CSTAT_STATIS  0x01

    enum COLE_STATUS_INVK {
        CSTATU_INVALID = 0x00,
        CSTATU_LIST,
        CSTATU_STATIS
    };

    extern int colle_status_tab[];

    enum LEVE_COLLECT_METH {
        LVTP_INVALID = 0x00,
        LVTP_POST,
        LVTP_STATUS,
        LVTP_CREATE,
        LVTP_DROP,
        LVTP_REPLACE,
        LVTP_INTEGRA,
        LVTP_RELOAD
    };

    // modify method

    // #define ENTI_STATU  0x10
    // #define     ESTAT_ECHO     0x00
    // #define     ESTAT_ATTRIB   0x01
    // #define     ESTAT_STATIS   0x02

    enum ENTI_STATUS_INVK {
        ESTATU_INVALID = 0x00,
        ESTATU_ECHO,
        ESTATU_ATTRIB,
        ESTATU_STATIS
    };

    extern int const_status_tab[];

    enum LEVE_CONSTRUCT_METH {
        LEVT_INVALID = 0x00,
        LEVT_POST,
        LEVT_STATUS,
        LEVT_CREATE,
        LEVT_DROP,
        LEVT_UPDATE,
        LEVT_INSERT,
        LEVT_SEARCH,
        LEVT_INVOKE
    };

    // modify method

    // #define QUER_STATU   0x10
    // #define     QSTAT_ECHO     0x00
    // #define     QSTAT_ATTRIB   0x01
    // #define     QSTAT_STATIS   0x02

    enum QUER_STATUS_INVK {
        QSTATU_INVALID = 0x00,
        QSTATU_ECHO,
        QSTATU_ATTRIB,
        QSTATU_STATIS
    };
    extern int query_status_tab[];

    enum LEVE_QUERY_METH {
        LVFP_INVALID = 0x00,
        LVFP_POST,
        LVFP_STATUS,
        LVFP_CREATE,
        LVFP_DROP,
        LVFP_UPDATE,
        LVFP_INSERT,
        LVFP_SEARCH,
        LVFP_FACTORY,
        LVFP_INVOKE
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

#endif /* CLIT_STRUCT_H */

