
#ifndef OSCO_SOCKS_H
#define OSCO_SOCKS_H

//

#ifdef __cplusplus
extern "C" {
#endif


    //
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

//
#include "clie_macro.h"
#include "clie_struct.h"
#include "reque_conne.h"

    //
    int osco_connect(serv_addr *saddr);
    // void OSCO_CLOSE(int conne_sock);
#define OSCO_CLOSE(CONNE_SOCK) close(CONNE_SOCK)

    //
    long long send_receive(char *recv_buffer, char *send_buffer, long long slen, int conne_sock);
    long long osco_send(char *send_buffer, long long slen, int conne_sock);
    long long receive(char *recv_buffer, int conne_sock);

#ifdef __cplusplus
}
#endif

#endif /* OSCO_SOCKS_H */

