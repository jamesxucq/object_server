#ifndef EPOLL_SERV_H_
#define EPOLL_SERV_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "commo_header.h"

#include "parse_conf.h"
#include "event.h"
#include "evd_list.h"

    //
#define CREATE_SRECVBUF(SRE_BUFF) { \
    SRE_BUFF = (BYTE *) malloc(BUFF_SOCKET_SIZE); \
    if(!SRE_BUFF) return ERR_FAULT; \
    memset(SRE_BUFF, '\0', BUFF_SOCKET_SIZE); \
}

#define DESTROY_SRECVBUF(SRE_BUFF) { \
    if(SRE_BUFF) return free(SRE_BUFF); \
    SRE_BUFF = NULL; \
}

    //
    int epoll_server(serv_config *config);
    int init_event_data(event_data *evds, int max_events);

#ifdef __cplusplus
}
#endif

#endif /* EPOLL_SERV_H_ */
