
/* 
 * File:   ercod_cli.h
 * Author: james
 *
 * Created on 2024.5.16, PM 3:23
 */

#ifndef ERCOD_CLI_H
#define ERCOD_CLI_H

#ifdef __cplusplus
extern "C" {
#endif

#define ERR_SUCCESS     0x00
#define ERR_FAULT       -1
#define ERR_EXCEP       0x01

    /* View Error Code Define */
#define  CLI_BASE      0x03000000
    // #define  ERR_CONFIG     CLI_BASE | 0x0001
    // #define  ERR_LOAD       CLI_BASE | 0x0003

    /* Ctrl Error Code Define */
#define  BZLG_BASE      0x06000000
// #define  ERR_COLLE_ATTRI        BZLG_BASE | 0x0001
// #define  ERR_COMPA_ATTRI        BZLG_BASE | 0x0003
    
    /* Mode Error Code Define */
#define  OBJE_BASE      0x09000000
    // #define  ERR_CONFIG     OBJE_BASE | 0x0001
    // #define  ERR_LOAD       OBJE_BASE | 0x0003


#ifdef __cplusplus
}
#endif

#endif /* ERCOD_CLI_H */

