/* osev_obje.c
 * Created on: 2010-3-10
 * Author: Divad
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "server_macro.h"
#include "third_party.h" // test

#include "finalize.h"
#include "osev_obje.h"
#include "comdi_bzl.h"

//

static int hand_cons_memo_recv(_event *bev) {
    OSEVPF("[FUNC]:hand_cons_memo_recv\n");
    resp_ctrl *reqctl = &bev->seion->rvsctl;
    evdata *evdat = &bev->evdat;
    //
    if (!reqctl->content_length) return HAND_FINISH;
    // OSEVPF("content_length:%d rsend_count:%d\n", reqctl->content_length, reqctl->rsend_count);
    // OSEVPF("blen:%d body_buffer:%d requ_data:%d\n", evdat->blen, evdat->body_buffer, reqctl->requ_stem);
    memcpy(reqctl->resp_memo, evdat->value_ptr, evdat->blen);
    //
    reqctl->requ_inde += evdat->blen;
    if (reqctl->content_length != reqctl->requ_inde)
        return HAND_UNDONE;
    return HAND_FINISH;
}

/* // delete by james 20231213
static int hand_cons_data_recv(_event *bev) {
    OSEVPF("[FUNC]:hand_cons_data_recv\n");
    resp_ctrl *reqctl = &bev->seion->rvsctl;
    evdata *evdat = &bev->evdat;
    //
    if (!reqctl->content_length) return HAND_FINISH;
    // OSEVPF("content_length:%d rsend_count:%d\n", reqctl->content_length, reqctl->rsend_count);
    // OSEVPF("blen:%d body_buffer:%d requ_data:%d\n", evdat->blen, evdat->body_buffer, reqctl->requ_stem);
    evdat->blen = fwrite(evdat->value_ptr, 0x01, evdat->blen, reqctl->requ_stem);
    //
    reqctl->requ_inde += evdat->blen;
    if (reqctl->content_length != reqctl->requ_inde)
        return HAND_UNDONE;
    return HAND_FINISH;
}
 */

// modify method
static int(*recv_const_tab[])(_event*) = {
    hand_cons_memo_recv, // echo
    hand_cons_memo_recv, // create
    hand_cons_memo_recv, // drop
    hand_cons_memo_recv, // update
    hand_cons_memo_recv, // insert
    hand_cons_memo_recv, // search
    hand_cons_memo_recv // invoke
};

int hand_const_recv(_event *bev) {
    inte_value *inval = &bev->seion->inval;
    resp_ctrl *reqctl = &bev->seion->rvsctl;
    //
    int haval = recv_const_tab[inval->lvivk_type](bev);
    if (!haval) FINAL_CONST_RECV(inval, reqctl, bev->seion->baval);
    return haval;
}

//

static int hand_quer_memo_recv(_event *bev) {
    OSEVPF("[FUNC]:hand_quer_memo_recv\n");
    resp_ctrl *reqctl = &bev->seion->rvsctl;
    evdata *evdat = &bev->evdat;
    //
    if (!reqctl->content_length) return HAND_FINISH;
    // OSEVPF("content_length:%d rsend_count:%d\n", reqctl->content_length, reqctl->rsend_count);
    // OSEVPF("blen:%d body_buffer:%d requ_data:%d\n", evdat->blen, evdat->body_buffer, reqctl->requ_stem);
    memcpy(reqctl->resp_memo, evdat->value_ptr, evdat->blen);
    //
    reqctl->requ_inde += evdat->blen;
    if (reqctl->content_length != reqctl->requ_inde)
        return HAND_UNDONE;
    return HAND_FINISH;
}

static int hand_quer_data_recv(_event *bev) {
    OSEVPF("[FUNC]:hand_quer_data_recv\n");
    resp_ctrl *reqctl = &bev->seion->rvsctl;
    evdata *evdat = &bev->evdat;
    //
    if (!reqctl->content_length) return HAND_FINISH;
    // OSEVPF("content_length:%d rsend_count:%d\n", reqctl->content_length, reqctl->rsend_count);
    // OSEVPF("blen:%d body_buffer:%d requ_data:%d\n", evdat->blen, evdat->body_buffer, reqctl->requ_stem);
    evdat->blen = fwrite(evdat->value_ptr, 0x01, evdat->blen, reqctl->requ_stem);
    //
    reqctl->requ_inde += evdat->blen;
    if (reqctl->content_length != reqctl->requ_inde)
        return HAND_UNDONE;
    return HAND_FINISH;
}

// modify method
static int(*recv_query_tab[])(_event*) = {
    hand_quer_memo_recv, // echo
    hand_quer_memo_recv, // create
    hand_quer_memo_recv, // drop
    hand_quer_data_recv, // update
    hand_quer_data_recv, // insert
    hand_quer_memo_recv, // search
    hand_quer_memo_recv, // invoke
    hand_quer_memo_recv // factory
};

//

int hand_query_recv(_event *bev) {
    inte_value *inval = &bev->seion->inval;
    resp_ctrl *reqctl = &bev->seion->rvsctl;
    //
    int haval = recv_query_tab[inval->lvivk_type](bev);
    if (!haval) FINAL_QUERY_RECV(inval, reqctl, bev->seion->baval);
    return haval;
}

//
int(*recv_handler_tab[])(_event*) = {
    NULL, NULL, NULL, NULL,
    hand_const_recv,
    hand_query_recv
};

//

static int hand_cons_memo_send(_event *bev) {
    OSEVPF("[FUNC]:hand_cons_memo_send\n");
    int send_valu = HAND_UNDONE;
    resp_ctrl *resctl = &bev->seion->rvsctl;
    evdata *evdat = &bev->evdat;
    //
    if (!resctl->content_length) {
        evdat->blen = 0x00;
        return HAND_FINISH;
    }
    if (resctl->content_length <= (resctl->resp_inde + evdat->blen)) {
        evdat->blen = resctl->content_length - resctl->resp_inde;
        send_valu = HAND_FINISH;
    }
    // OSEVPF("send_valu:%d\n", send_valu);
    // OSEVPF("content_length:%d rsend_count:%d\n", resctl->content_length, resctl->rsend_count);
    // OSEVPF("blen:%d body_buffer:%d resp_buffe:%d\n", evdat->blen, evdat->body_buffer, resctl->resp_memo);
    memcpy(evdat->value_ptr, resctl->resp_memo + resctl->resp_inde, evdat->blen);
    //
    resctl->resp_inde += evdat->blen;
    return send_valu;
}

static int hand_cons_data_send(_event *bev) {
    OSEVPF("[FUNC]:hand_cons_data_send\n");
    int send_valu = HAND_UNDONE;
    resp_ctrl *resctl = &bev->seion->rvsctl;
    evdata *evdat = &bev->evdat;
    //
    if (!resctl->content_length) {
        evdat->blen = 0x00;
        return HAND_FINISH;
    }
    if (resctl->content_length <= (resctl->resp_inde + evdat->blen)) {
        evdat->blen = resctl->content_length - resctl->resp_inde;
        send_valu = HAND_FINISH;
    }
    evdat->blen = fread(evdat->value_ptr, 0x01, evdat->blen, resctl->resp_stem);
    if (!evdat->blen) {
        _LOG_WARN("cons file error!");
    }
    // OSEVPF("evdat->blen:%llu\n", evdat->blen);
    // log_binary_file(evdat->value_ptr, evdat->blen, "./binary_code.bin_s");
    resctl->resp_inde += evdat->blen;
    return send_valu;
}

// modify method
static int(*send_const_tab[])(_event*) = {
    hand_cons_memo_send, // echo
    hand_cons_memo_send, // create
    hand_cons_memo_send, // drop
    hand_cons_memo_send, // update
    hand_cons_memo_send, // insert
    hand_cons_data_send, // search
    hand_cons_data_send // invoke
};

int hand_const_send(_event *bev) {
    int haval = send_const_tab[bev->seion->inval.lvivk_type](bev);
    if (!haval) FINAL_CONST_SEND(&bev->seion->rvsctl);
    return haval;
}

//

static int hand_quer_memo_send(_event *bev) {
    OSEVPF("[FUNC]:hand_quer_memo_send\n");
    int send_valu = HAND_UNDONE;
    resp_ctrl *resctl = &bev->seion->rvsctl;
    evdata *evdat = &bev->evdat;
    //
    if (!resctl->content_length) {
        evdat->blen = 0x00;
        return HAND_FINISH;
    }
    // OSEVPF("evdat->blen:%d\n", evdat->blen);
    if (resctl->content_length <= (resctl->resp_inde + evdat->blen)) {
        evdat->blen = resctl->content_length - resctl->resp_inde;
        send_valu = HAND_FINISH;
    }
    // OSEVPF("send_valu:%d\n", send_valu);
    // OSEVPF("content_length:%d rsend_count:%d\n", resctl->content_length, resctl->rsend_count);
    // OSEVPF("blen:%d body_buffer:%d resp_buffe:%d\n", evdat->blen, evdat->value_ptr, resctl->resp_memo);
    memcpy(evdat->value_ptr, resctl->resp_memo + resctl->resp_inde, evdat->blen);
    //
    resctl->resp_inde += evdat->blen;
    return send_valu;
}

static int hand_quer_data_send(_event *bev) {
    OSEVPF("[FUNC]:hand_quer_data_send\n");
    int send_valu = HAND_UNDONE;
    resp_ctrl *resctl = &bev->seion->rvsctl;
    evdata *evdat = &bev->evdat;
    //
    if (!resctl->content_length) {
        evdat->blen = 0x00;
        return HAND_FINISH;
    }
    if (resctl->content_length <= (resctl->resp_inde + evdat->blen)) {
        evdat->blen = resctl->content_length - resctl->resp_inde;
        send_valu = HAND_FINISH;
    }
    evdat->blen = fread(evdat->value_ptr, 0x01, evdat->blen, resctl->resp_stem);
    if (!evdat->blen) {
        _LOG_WARN("quer file error!");
    }
    // OSEVPF("evdat->blen:%llu\n", evdat->blen);
    // log_binary_file(evdat->value_ptr, evdat->blen, "./binary_code.bin_s");
    resctl->resp_inde += evdat->blen;
    return send_valu;
}

// modify method
static int(*send_query_tab[])(_event*) = {
    hand_quer_memo_send, // echo
    hand_quer_memo_send, // create
    hand_quer_memo_send, // drop
    hand_quer_memo_send, // update rf
    hand_quer_data_send, // insert rf
    hand_quer_data_send, // search
    hand_quer_data_send, // invoke
    hand_quer_data_send // factory
};

int hand_query_send(_event *bev) {
    int haval = send_query_tab[bev->seion->inval.lvivk_type](bev);
    if (!haval) FINAL_QUERY_SEND(&bev->seion->rvsctl);
    return haval;
}

//
int (*send_handler_tab[])(_event*) = {
    NULL, NULL, NULL, NULL,
    hand_const_send,
    hand_query_send,
};

//
