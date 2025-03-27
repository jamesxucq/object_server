
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "osev_macro.h"
#include "reque_conne.h"
#include "respo_conne.h"
#include "osco_socks.h"
#include "clie_macro.h"
#include "hand_method.h"
#include "clie_obje.h"
#include "osev_clie_clang.h"

// 0x00:success -1:error

int hand_reques(resp_head *res_had, int conne_sock, requ_data_t *req_dat) {
    OSEVPF("[FUNC]:hand_reques\n");
    if (-1 == send_receive((char *) res_had, (char*) req_dat->requ_memo, req_dat->requ_leng, conne_sock)) {
        OSEVPF("Handle send recv execep!\n");
        return -1;
    }
    OSEVPF("Handle res_had->status_code:%d\n", res_had->status_code);
    return 0x00;
}

// 0x00:success -1:error

int hand_respon(resp_data_t *res_dat, int conne_sock, requ_data_t *req_dat) {
    OSEVPF("[FUNC]:hand_respon\n");
    char revbuf[CONNE_DATA_SIZE];
    //
    long long recvlen = send_receive(revbuf, (char*) req_dat->requ_memo, req_dat->requ_leng, conne_sock);
    if (-1 == recvlen) {
        OSEVPF("Method send recv execep!\n");
        return -1;
    }
    // OSEVPF("Recvlen:%d\n", recvlen);
    res_dat->status_code = ((resp_head *) revbuf)->status_code;
    res_dat->content_length = ((resp_head *) revbuf)->content_length;
    memcpy(res_dat->resp_memo, revbuf + RESP_HEAD_BLEN, recvlen - RESP_HEAD_BLEN);
    OSEVPF("content_length:%llu\n", ((resp_head *) revbuf)->content_length);
    int recv_total = recvlen - RESP_HEAD_BLEN;
    // OSEVPF("recv_total:%d\n", recv_total);
    while (res_dat->content_length != recv_total) {
        recvlen = receive(revbuf, conne_sock);
        // OSEVPF("Recvlen:%d\n", recvlen);
        if (-1 == recvlen) {
            OSEVPF("Method send recv execep!\n");
            return -1;
        }
        memcpy(res_dat->resp_memo + recv_total, revbuf, recvlen);
        recv_total += recvlen;
    }
    OSEVPF("Respon status_code:0x%04x\n", ((resp_head *) revbuf)->status_code);
    return 0x00;
}