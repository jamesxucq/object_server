#ifndef OSTPPROTO_H
#define OSTPPROTO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    // server ostp method
    // OSEV_METHOD
#define OSVP_OSEV       0x00 // set or get osev base run status // osev, low-leve
#define OSVP_BASE       0x01
#define OSVP_KALIVE     0x02 // keep alive 
#define OSVP_INVOKE     0x03 // addi dele modi meth // leve-1
#define OSVP_COLLE      0x04 // addi dele modi class // leve-2p
#define OSVP_CONST      0x05 // leve-3
#define OSVP_QUERY      0x06 // select object from container // leve-4p invok object method
#define OSVP_DONE       0x07 // end

    //
    // STATUS_CODE
    // #define INVALID                 0x0000 // 0000 Invalid
    // Informational
#define CONTINUE                0x0010 // 100 Continue 
#define SWITCHINT_PROTOCOLS     0x0011 // 101 Switching Protocols
#define PROCESSING              0x0012 // * 102 Processing // WebDAV
    // Successful
#define OK                      0x0020 // 200 OK
#define CREATED                 0x0021 // 201 Created
#define ACCEPTED                0x0022 // 202 Accepted
    // Redirection
#define MULTIPLE_CHOICES        0x0030 // 300 Multiple Choices
#define MOVED_PERMANENTLY       0x0031 // 301 Moved Permanently
    // Client Error
#define BAD_REQUEST             0x0040 // 400 Bad Request
#define UNAUTHORIZED            0x0041 // 401 Unauthenized
#define FORBIDDEN               0x0043 // 403 Forbidden
    // Server Error
#define INTERNAL_SERVER_ERROR   0x0050 // 500 Internal Server Error
#define NOT_IMPLEMENTED         0x0051 // 501 Not Implemented
#define BAD_GATEWAY             0x0052 // 502 Bad Gateway
#define SERVICE_UNAVAILABLE     0x0053 // 503 Service Unavailable

    //

#define REQU_EVDAT_HDBD(EVDAT, EVD) { \
    (EVDAT)->head_ptr = (EVD)->buffer; \
    (EVDAT)->body_ptr = (EVD)->buffer + REQU_HEAD_BLEN; \
    (EVDAT)->blen = (EVD)->rsleng - REQU_HEAD_BLEN; \
}

#define REQU_EVDAT_BODY(EVDAT, EVD) { \
    (EVDAT)->body_ptr = (EVD)->buffer; \
    (EVDAT)->blen = (EVD)->rsleng; \
}

    //
#define RESP_EVDAT_HINI(EVDAT, EVD) { \
    (EVDAT)->head_ptr = (EVD)->buffer; \
    (EVDAT)->body_ptr = (EVD)->buffer + RESP_HEAD_BLEN; \
    (EVDAT)->blen = BUFF_SOCKET_SIZE - RESP_HEAD_BLEN; \
}

#define RESP_EVDAT_HEND(EVDAT, EVD) { \
    (EVD)->sleng = 0x00; \
    (EVD)->rsleng = RESP_HEAD_BLEN + (EVDAT)->blen; \
}

#define RESP_EVDAT_BINI(EVDAT, EVD) { \
    (EVDAT)->body_ptr = (EVD)->buffer; \
    (EVDAT)->blen = BUFF_SOCKET_SIZE; \
}

#define RESP_EVDAT_BEND(EVDAT, EVD) { \
    (EVD)->sleng = 0x00; \
    (EVD)->rsleng = (EVDAT)->blen; \
}

    //

#define PROTO_REQHAD(BEV, HEADER) { \
    (BEV)->levtyp = ((requ_head *)HEADER)->levtyp; \
    (BEV)->levivk = ((requ_head *)HEADER)->levivk; \
    OBID_BINARY_COPY(&(BEV)->seion->inval.inte_obid, &((requ_head *)HEADER)->requ_obid); \
    (BEV)->seion->rvsctl.content_length = ((requ_head *)HEADER)->content_length; \
    OSEVPF("\n(BEV)->levtyp:%u, (BEV)->levivk:%04X, content_length:%llu\n", (BEV)->levtyp, (BEV)->levivk, (BEV)->seion->rvsctl.content_length); \
}

#ifdef __cplusplus
}
#endif

#endif /* OSTPPROTO_H */

