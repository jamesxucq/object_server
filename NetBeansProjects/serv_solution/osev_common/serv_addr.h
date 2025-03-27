
/* 
 * File:   serv_addr.h
 * Author: James Xu
 *
 * Created on 2024.1.4, PM 2:34
 */

#ifndef SERV_ADDR_H
#define SERV_ADDR_H

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _serv_addr_ {
        char sin_addr[SERVN_LENGTH];
        int sin_port;
    };

    typedef struct _serv_addr_ serv_addr;


#ifdef __cplusplus
}
#endif

#endif /* SERV_ADDR_H */

