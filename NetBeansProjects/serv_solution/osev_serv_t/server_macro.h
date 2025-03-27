#ifndef _SERVER_MACRO_H_
#define	_SERVER_MACRO_H_

#ifdef	__cplusplus
extern "C" {
#endif
//

//
#define DEFAULT_HOST_PORT 8888
#define DEFAULT_CONTENT_LENGTH (100 * 1024) /* bytes */
#define DEFAULT_KEEP_ALIVE 5 /* seconds */
#define DEFAULT_MAX_CONNECTION_AGE 300 /* seconds */
    // #define BUG_REPORT_EMAIL "james.xucq@gmail.com"
#define BUG_REPORT_EMAIL "xujiecq@163.com"

#define OBJE_SERV_DEFAULT "object_server.xml"
#define OSEV_LOCK_DEFAULT "object_server.lock"
#define OSEV_PID_DEFAULT "object_server.pid"
#define OSEV_LOG_DEFAULT "object_server.log"
#define OSEV_ACCESS_DEFAULT "osev_access.log"
#define OSEV_USER_DEFAULT "nobody"
#define OSEV_GROUP_DEFAULT "nobody"

#define VERSION 	"0.6.1.0"
#define COPYRIGHT 	"Copyright (C) 2025 Basic Data"
#define DISCLAIMER      "This is not free software.  "
#define FUNCTION	"Object Server" 
#define USAGE		"Usage: %s [options] <input>\n"
#define PROGRAM_NAME	"osev_serv_t"

//
#define LOOP_QUSP                       0x00000000 // initial
#define REQU_STOP                       0x00000000 // stop
#define REQU_CONTINUE                   0x00000001 // continue
#define RESP_STOP                       REQU_STOP // stop
#define RESP_CONTINUE                   REQU_CONTINUE // continue

//
#define SEND_NEXTHAND                   0x00000000
#define SEND_CONTINUE                   0x00000001
//
    
#ifdef	__cplusplus
}
#endif
    
#endif	/* _SERVER_MACRO_H_ */

