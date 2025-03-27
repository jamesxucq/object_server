
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "osev_common/commo_header.h"

#include "osco_socks.h"

//
#define CONNE_SOCKS_DATSIZ               0x2000  // 8K

//

int osco_connect(serv_addr *saddr) {
    int conne_sock;
    if ((conne_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        // OSEVPF("OSCO socket create ERROR!\n");
        return -1;
    }
    //
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(saddr->sin_port);
    sin.sin_addr.s_addr = inet_addr(saddr->sin_addr);
    bzero(&(sin.sin_zero), 8);
    if (connect(conne_sock, (struct sockaddr *) &sin, sizeof (struct sockaddr)) == -1) {
        // OSEVPF("OSCO socket connect ERROR!\n");
        // OSEVPF("sin_addr:%s sin_port:%d\n", saddr->sin_addr, saddr->sin_port);
        return -1;
    }
    // OSEVPF("sin_addr:%s sin_port:%d\n", saddr->sin_addr, saddr->sin_port);
    // OSEVPF("OSCO socket connect OK!\n");
    //
    return conne_sock;
}

//

long long send_receive(char *recv_buffer, char *send_buffer, long long slen, int conne_sock) {
    long long bytes_sent, bytes_recv;
    //
    bytes_sent = send(conne_sock, send_buffer, slen, 0);
    if (bytes_sent != slen) { // reconnect to server
        // OSEVPF("OSCO send failed!\n");
        return -1;
    }
    //    
    bytes_recv = recv(conne_sock, recv_buffer, CONNE_SOCKS_DATSIZ, 0);
    if (0 >= bytes_recv) { // bytes_recv = 0; bytes_recv < 0;
        // OSEVPF("OSCO recv failed!\n");
        return -1;
    }
    //
    return bytes_recv;
}

//

long long osco_send(char *send_buffer, long long slen, int conne_sock) {
    long long bytes_sent;
    //
    bytes_sent = send(conne_sock, send_buffer, slen, 0);
    if (bytes_sent != slen) { // reconnect to server
        // OSEVPF("OSCO send failed!\n");
        return -1;
    }
    //
    return bytes_sent;
}

//

long long receive(char *recv_buffer, int conne_sock) {
    long long bytes_recv;
    //    
    bytes_recv = recv(conne_sock, recv_buffer, CONNE_SOCKS_DATSIZ, 0);
    if (0 >= bytes_recv) { // bytes_recv = 0; bytes_recv < 0;
        // OSEVPF("OSCO recv failed!\n");
        return -1;
    }
    //
    return bytes_recv;
}