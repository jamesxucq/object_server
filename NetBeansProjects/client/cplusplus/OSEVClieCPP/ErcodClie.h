
/* 
 * File:   ErcodClie.h
 * Author: James Xu
 *
 * Created on 2023.11.8, PM 3:02
 */

#ifndef ERCOD_CLIE_H
#define ERCOD_CLIE_H

#ifdef __cplusplus
extern "C" {
#endif

#define ERR_SUCCESS     0x00
#define ERR_FAULT       -1
#define ERR_EXCEP       0x01

    /* View Error Code Define */
#define  CLIE_BASE      0x02000000
    // #define  ERR_CONFIG     CLIE_BASE | 0x0001
    // #define  ERR_LOAD       CLIE_BASE | 0x0003

    /* Ctrl Error Code Define */
#define  INTE_BASE      0x05000000
#define  ERR_COLLE_VERSIO       INTE_BASE | 0x0001
#define  ERR_COMPA_VERSIO       INTE_BASE | 0x0003
#define  ERR_COLLE_ATTRI        INTE_BASE | 0x0005
#define  ERR_COMPA_ATTRI        INTE_BASE | 0x0007

    /* Mode Error Code Define */
#define  DATA_BASE      0x08000000
    // #define  ERR_CONFIG     DATA_BASE | 0x0001
    // #define  ERR_LOAD       DATA_BASE | 0x0003


#ifdef __cplusplus
}
#endif

#endif /* ERCOD_CLIE_H */

