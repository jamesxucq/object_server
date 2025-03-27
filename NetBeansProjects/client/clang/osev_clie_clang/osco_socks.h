
#ifndef OSCO_SOCKS_H
#define OSCO_SOCKS_H
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#include "commo_header.h"
#include "clie_macro.h"

#ifdef __cplusplus
extern "C" {
#endif



    // trans-serve
    int osco_connect(serv_addr *saddr);

    // void OSCO_CLOSE(int conne_sock);
#define OSCO_CLOSE(CONNE_SOCK) { \
    OSEVPF("[FUNC]:OSCO_CLOSE\n"); \
    close(CONNE_SOCK); \
}

    //
    long long send_receive(char *recv_buffer, char *send_buffer, long long slen, int conne_sock);
    long long osco_send(char *send_buffer, long long slen, int conne_sock);
    long long receive(char *recv_buffer, int conne_sock);

#ifdef __cplusplus
}
#endif

#endif /* OSCO_SOCKS_H */

