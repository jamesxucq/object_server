#ifndef _CLI_MACRO_H_
#define _CLI_MACRO_H_

#ifdef __cplusplus
extern "C" {
#endif

    //
#define CLI_TYPE_EXIT   0xFFFFFFFF

    // CLI_TYPE
#define CITP_CLIE   0x00000000 // cli level
#define CITP_OSVB   0x00000001 // OSEV / BASE
#define CITP_CLEV   0x00000002 // contain level

    // LEVEL_TYPE
#define LVTP_ONE    0x00000000
#define LVTP_TWOP   0x00000001
#define LVTP_THRE   0x00000002
#define LVTP_FOUP   0x00000003

#define LEVEL_EXTEND_SPACE      0x000F0000
#define SET_EXTEND_SPACE(LEVE_CODE)     (LEVE_CODE |= 0x000F0000)
#define UNSET_EXTEND_SPACE(LEVE_CODE)   (LEVE_CODE &= 0xFFF0FFFF)
#define ONLY_LEVEL_VALUE(LEVE_CODE)     (0x0000FFFF & LEVE_CODE)
    
    //
#define DEFAULT_HOST_PORT 8888
#define DEFAULT_CONTENT_LENGTH (100 * 1024) /* bytes */
#define DEFAULT_KEEP_ALIVE 5 /* seconds */
#define DEFAULT_MAX_CONNECTION_AGE 300 /* seconds */

#define VERSION 	"1.0"
#define COPYRIGHT 	"Copyright (C) 2012 Pu Shan"
#define DISCLAIMER      "This is not free software.  "
#define FUNCTION	"osev cli" 
#define USAGE		"Usage: %s [options] <input>\n"
#define PROGRAM_NAME	"osev-cli"
#define BUG_REPORT_EMAIL "james.xucq@gmail.com"
    
    //
#define OSEV_DEFAULT_VALUE  "osev"
#define BASE_DEFAULT_VALUE  "odb"
#define CLIE_DEFAULT_VALUE  "clie"
    
    //
#define OSEV_PRIVILE_VALUE  "osev:privile"
#define BASE_PRIVILE_VALUE  "odb:privile"

#ifdef __cplusplus
}
#endif

#endif /* _CLI_MACRO_H_ */

