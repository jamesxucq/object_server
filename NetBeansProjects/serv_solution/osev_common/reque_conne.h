
#ifndef REQUE_CONNE
#define REQUE_CONNE

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    //
#include "osev_macro.h"
#include "obid.h"
#include "ostproto.h"

    //

#define ZERO_LEVEL_INVK     0x00
#define ONLY_HEADER_SECTION     0x00

#pragma pack(1)

    struct _requ_head_ {
        unsigned char levtyp; // OSEV_METHOD
        unsigned char levivk; // POST_OPEN, COLE_DROP, QUER_FACTO
        osv_oid_t requ_obid;
        unsigned long long content_length;
    };
#pragma pack()

    typedef struct _requ_head_ requ_head;

    //
#define REQUEST_HEAD \
        unsigned char levtyp; \
        unsigned char levivk; \
        osv_oid_t requ_obid; \
        unsigned long long content_length;

    // request
#define REQU_HEAD_BLEN  sizeof(requ_head)

#define CAT_REQHAD_PTR(HEAD, LEVTYP, LEVIVK, REQU_OBID, LENGTH) { \
    ((requ_head*) HEAD)->levtyp = LEVTYP; \
    ((requ_head*) HEAD)->levivk = LEVIVK; \
    OBID_BINARY_COPY(&((requ_head*) HEAD)->requ_obid, REQU_OBID) \
    ((requ_head*) HEAD)->content_length = LENGTH; \
}
    // printf("\n(REH)->levtyp:%u, (BEV)->levivk:%04X, content_length:%llu\n", LEVTYP, LEVIVK, (unsigned long long) LENGTH);

    // LEVEL OSEV 

#pragma pack(1)

    struct _osev_requ_ {
        REQUEST_HEAD
        unsigned char requ_binary[0x00]; // param
    };
#pragma pack()

    typedef struct _osev_requ_ osev_requ;

    // #define OSVP_OSEV       0x00 // set or get osev base run status // osev, low-leve
    // OSEV osev_type // modify method
#define OAUTHEN      0x00
#define OPOST        0x10
#define OSTATUS      0x20
#define     OSTAT_ECHO       0x00
#define     OSTAT_STATIS     0x01
#define OCOMAND      0x30
#define     OCOMD_OPEN       0x00 // start Create
#define     OCOMD_CLOSE      0x01 // shutdown
#define OPRIVI       0x40    
#define     OPRIV_LIST       0x00
#define     OPRIV_ROLE       0x01
#define     OPRIV_USER       0x02

    // LEVEL BASE

#pragma pack(1)

    struct _base_requ_ {
        REQUEST_HEAD
        unsigned char requ_binary[0x00]; // param
    };
#pragma pack()

    typedef struct _base_requ_ base_requ;

    // #define OSVP_BASE       0x01
    // BASE base_type // modify method
#define BAUTHEN      0x00
#define BPOST        0x10
#define BSTATUS      0x20
#define     BSTAT_ECHO      0x00
#define     BSTAT_STATIS    0x01
#define BCOMAND      0x30
#define     BCOMD_OPEN      0x00 // start Create
#define     BCOMD_CLOSE     0x01 // shutdown
#define BPRIVI       0x40    
#define     BPRIV_LIST       0x00
#define     BPRIV_ROLE       0x01
#define     BPRIV_USER       0x02

    // LEVEL KALIVE

#pragma pack(1)

    struct _kaliv_requ_ {
        REQUEST_HEAD
    };
#pragma pack()

    typedef struct _kaliv_requ_ kaliv_requ;
    // #define OSVP_KALIVE     0x02 // keep alive 

    // LEVEL INVOKE

#pragma pack(1)

    struct _invok_requ_ {
        REQUEST_HEAD
        unsigned char requ_binary[0x00]; // param
    };
#pragma pack()

    typedef struct _invok_requ_ invok_requ;

    // #define OSVP_INVOKE     0x03 // addi dele modi meth // leve-1
    // INVOK METHOD invok_type // modify method
#define INVO_POST       0x00
#define INVO_STATU      0x10
#define     ISTAT_LIST     0x00
#define     ISTAT_STATIS   0x01
#define INVO_CREAT      0x20
#define INVO_REPLA      0x30
#define INVO_DROP       0x40
#define INVO_INTEGRA    0x50
#define INVO_RELOAD     0x60

    // LEVEL COLLE

#pragma pack(1)

    struct _colle_requ_ {
        REQUEST_HEAD
        unsigned char requ_binary[0x00]; // param
    };
#pragma pack()

    typedef struct _colle_requ_ colle_requ;

    // #define OSVP_COLLE      0x04 // addi dele modi class // leve-2p
    // COLLE METHOD colle_type // modify method
#define COLE_POST       0x00
#define COLE_STATU      0x10
#define     CSTAT_LIST     0x00
#define     CSTAT_STATIS   0x01
#define COLE_CREAT      0x20
#define COLE_REPLA      0x30
#define COLE_DROP       0x40
#define COLE_INTEGRA    0x50
#define COLE_RELOAD     0x60

    // LEVEL CONSTR
#pragma pack(1)

    struct _const_requ_ {
        REQUEST_HEAD
        unsigned char requ_binary[0x00]; // param
    };

#pragma pack()

    typedef struct _const_requ_ const_requ;

    // #define OSVP_CONST      0x05 // leve-3
    // CONST METHOD const_type // modify method
#define ENTI_POST   0x00
#define ENTI_STATU  0x10
#define     ESTAT_ECHO     0x00
#define     ESTAT_ATTRIB   0x01
#define     ESTAT_STATIS   0x02
#define ENTI_CREAT  0x20
#define ENTI_DROP   0x30
#define ENTI_UPDAT  0x40
#define ENTI_INSER  0x50
#define ENTI_SEARO  0x60
#define ENTI_INVOK  0x70

    // LEVEL QUERY

#pragma pack(1)

    struct _query_requ_ {
        REQUEST_HEAD
        unsigned char requ_binary[0x00]; // param
    };

#pragma pack()

    typedef struct _query_requ_ query_requ;

    // #define OSVP_QUERY      0x06 // select object from container // leve-4p invok object method
    // QUERY METHOD query_type // modify method
#define QUER_POST   0x00
#define QUER_STATU   0x10
#define     QSTAT_ECHO     0x00
#define     QSTAT_ATTRIB   0x01
#define     QSTAT_STATIS   0x02
#define QUER_CREAT  0x20
#define QUER_DROP   0x30
#define QUER_UPDAT  0x40
#define QUER_INSER  0x50
#define QUER_SEARQ  0x60
#define QUER_INVOK  0x70
#define QUER_FACTO  0x80

    // LEVEL DONE

#pragma pack(1)

    struct _done_requ_ {
        REQUEST_HEAD
    };
#pragma pack()

    typedef struct _done_requ_ done_requ;

    // #define OSVP_DONE       0x07 // end
    //

#ifdef __cplusplus
}
#endif

#endif /* REQUE_CONNE */

