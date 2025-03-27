/* epoll_serv.c
 * Created on: 2010-3-19
 * Author: Divad
#include "sserv_bzl.h"
 */
#include <sys/timerfd.h>  
#include <sys/signalfd.h>
#include <sys/time.h> // for test
#include <signal.h>  
#include <unistd.h> 

#include "third_party.h"
#include "commo_header.h"
#include "sconfig.h"
#include "event.h"
#include "session.h"
#include "osev_utili.h"

#include "epoll_serv.h"

// #define EPOLL_SERV_PORT 8090 // default port
#define LISTENQ 20

// check timeout
#define CONNECT_ACTIVE 256
#define TIMEOUT_CHECK_COUNT 3

// int max_events = 512;
#define MAX_EVENTS 512
#define FD_CONTINUE   0x00

// set event

void event_set(event_data *evd, int sockfd) {
    if (sockfd) evd->sockfd = sockfd;
    evd->evloop = 0x00;
    evd->last_active = time(NULL);
    evd->evstatu = LOOP_QUSP;
    // _LOG_WARN("event Set ok[fd:%d]", evd->sockfd); // disable by james 20120410
}

// add an event to epoll

void event_add(int epofd, int events, event_data *evd) {
    struct epoll_event ev = {0x00,
        {0x00}};
    ev.data.ptr = evd;
    ev.events = events;
    //
    if (epoll_ctl(epofd, EPOLL_CTL_ADD, evd->sockfd, &ev))
        _LOG_WARN("event add failed[fd:%d] error[%d]:%s", evd->sockfd, errno, strerror(errno));
}

// add/mod an event to epoll

void event_mod(int epofd, int events, event_data *evd) {
    struct epoll_event ev = {0x00,
        {0x00}};
    ev.data.ptr = evd;
    ev.events = events;
    //
    if (epoll_ctl(epofd, EPOLL_CTL_MOD, evd->sockfd, &ev))
        _LOG_WARN("event mod failed[fd:%d] error[%d]:%s", evd->sockfd, errno, strerror(errno));
}

// delete an event from epoll

void event_dele(int epofd, event_data *evd) {
    struct epoll_event ev = {0x00,
        {0x00}};
    ev.data.ptr = evd;
    if (epoll_ctl(epofd, EPOLL_CTL_DEL, evd->sockfd, &ev)) {
        _LOG_WARN("event del fail[fd:%d] error[%d]:%s", evd->sockfd, errno, strerror(errno));
    }
}

//

int init_listen_socket(int *colfd, int epofd, event_data *list_evd, short port) {
    int lisfd = socket(AF_INET, SOCK_STREAM, 0x00);
    if (lisfd == -1) {
        _LOG_WARN("CREAT SOCKET FD ERROR!");
        return ERR_FAULT;
    }
    //
    fcntl(lisfd, F_SETFL, fcntl(lisfd, F_GETFL) | O_NONBLOCK); // set non-blocking
    _LOG_INFO("server listen fd:%d", lisfd);
    //
    memset(list_evd, '\0', sizeof (event_data));
    list_evd->evctrl = 0x01;
    event_set(list_evd, lisfd);
    event_add(epofd, EPOLLIN | EPOLLET, list_evd);
    //
    // bind & listen
    struct sockaddr_in sin;
    bzero(&sin, sizeof (sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);
    if (bind(lisfd, (const struct sockaddr*) &sin, sizeof (struct sockaddr)) == -1) {
        _LOG_WARN("BIND ERROR!");
        return ERR_FAULT;
    }
    if (listen(lisfd, LISTENQ) == -1) {
        _LOG_WARN("LISTEN ERROR!");
        return ERR_FAULT;
    }
    // EVD->rsleng:
    colfd[0x00] = lisfd;
    return ERR_SUCCESS;
}

int init_contro_event(int *colfd, int epofd, event_data *sig_evd, event_data *ala_evd, int time_out) {
    // alarm fd
    struct itimerspec neval;
    neval.it_value.tv_sec = 0x03;
    neval.it_value.tv_nsec = 0x00;
    neval.it_interval.tv_sec = time_out;
    neval.it_interval.tv_nsec = 0x00;
    //
    int tifd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK);
    if (tifd == -1) {
        _LOG_WARN("timerfd create error!");
        return ERR_FAULT;
    }
    if (-1 == timerfd_settime(tifd, 0x00, &neval, NULL)) {
        _LOG_WARN("settime error!");
        return ERR_FAULT;
    }
    //
    memset(ala_evd, '\0', sizeof (event_data));
    ala_evd->evctrl = 0x01;
    event_set(ala_evd, tifd);
    event_add(epofd, EPOLLIN | EPOLLET, ala_evd);
    colfd[0x01] = tifd;
    // signal fd
    sigset_t mask;
    sigemptyset(&mask);
    //    sigaddset(&mask, SIGINT); // disable for test
    sigaddset(&mask, SIGPIPE);
    //
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
        _LOG_WARN("sigprocmask");
    //
    int sifd = signalfd(-1, &mask, SFD_NONBLOCK);
    if (-1 == sifd) {
        _LOG_WARN("signalfd create error!");
        return ERR_FAULT;
    }
    //
    memset(sig_evd, '\0', sizeof (event_data));
    sig_evd->evctrl = 0x01;
    event_set(sig_evd, sifd);
    event_add(epofd, EPOLLIN | EPOLLET, sig_evd);
    colfd[0x02] = sifd;
    //
    return ERR_SUCCESS;
}

int init_event_data(event_data *evds, int max_events) {
    if (!evds) return ERR_FAULT;
    memset(evds, '\0', sizeof (event_data) *(max_events + 0x03));
    unsigned int inde = 0x00;
    for (; inde < max_events; ++inde) {
        memset(&evds[inde], '\0', sizeof (event_data));
        CREATE_SRECVBUF(evds[inde].buffer)
        CREATE_EVENT(evds[inde].bev)
    }
    return ERR_SUCCESS;
}

void final_event_data(event_data *evds, int max_events) {
    unsigned int inde;
    if (evds) {
        inde = 0x00;
        for (; inde < max_events; ++inde) {
            DESTROY_EVENT(evds[inde].bev)
            DESTROY_SRECVBUF(evds[inde].buffer)
        }
    }
}

//

int epoll_server(serv_config *config) {
    int epofd = -1, colfd[3] = {-1, -1, -1};
    // init the env
    short port = config->bind_port; // EPOLL_SERV_PORT; // default port
    int max_events = config->max_connecting;
    int time_out = config->seion_timeout;
    int check_tatol = config->max_connecting >> TIMEOUT_CHECK_COUNT;
    _LOG_INFO("MAX_EVENTS:%d TIME_OUT:%d", max_events, time_out);
    _LOG_INFO("SERVER RUNNING:PORT[%d]", port);
    // init event_data
    event_data *evds = (event_data *) malloc(sizeof (event_data) *(max_events + 0x03)); // g_evds[max_events] is used by listen fd
    if (!evds) {
        _LOG_WARN("malloc event_data error!");
        return ERR_FAULT;
    }
    memset(evds, '\0', sizeof (event_data) *(max_events + 0x03));
    if (init_event_data(evds, max_events)) {
        _LOG_WARN("init event_data error!");
        DELETE_EVDATS(evds);
        return ERR_FAULT;
    }
    // init evnets
    struct epoll_event *events = (struct epoll_event *) malloc(sizeof (struct epoll_event) *(max_events + 0x03));
    if (!events) {
        _LOG_WARN("malloc epoll event error!");
        final_event_data(evds, max_events);
        DELETE_EVDATS(evds);
        return ERR_FAULT;
    }
    memset(events, '\0', sizeof (struct epoll_event) *(max_events + 0x03));
    // init event data list
    evd_list *elist = (evd_list *) malloc(sizeof (evd_list));
    if (!elist) {
        _LOG_WARN("malloc event list error!");
        DELETE_EVENTS(events);
        final_event_data(evds, max_events);
        DELETE_EVDATS(evds);
        return ERR_FAULT;
    }
    memset(elist, '\0', sizeof (evd_list));
    if (init_evd_list(elist, evds, max_events)) {
        _LOG_WARN("init event list error!");
        DELETE_EVENTS(events);
        final_event_data(evds, max_events);
        DELETE_EVDATS(evds);
        return ERR_FAULT;
    }
    // create epoll
    epofd = epoll_create(max_events + 0x03);
    if (-1 == epofd) {
        _LOG_WARN("create epoll failed:%d, erron:%d", epofd, errno);
        dele_evd_list(elist);
        DELETE_EVENTS(events);
        final_event_data(evds, max_events);
        DELETE_EVDATS(evds);
        return ERR_FAULT;
    }
    // create & bind listen socket, and add to epoll, set non-blocking
    if (init_listen_socket(colfd, epofd, &evds[max_events], port)) {
        dele_evd_list(elist);
        DELETE_EVENTS(events);
        final_event_data(evds, max_events);
        DELETE_EVDATS(evds);
        return ERR_FAULT;
    }
    // create ctrl fd
    if (init_contro_event(colfd, epofd, &evds[max_events + 0x01], &evds[max_events + 0x02], time_out)) {
        dele_evd_list(elist);
        DELETE_EVENTS(events);
        final_event_data(evds, max_events);
        DELETE_EVDATS(evds);
        return ERR_FAULT;
    }
    // event loop
    for (;;) { // wait for events to happen
        int ready = epoll_wait(epofd, events, max_events, -1);
        if (ready < 0x00) {
            if ((EAGAIN == errno) || (EINTR == errno))
                continue;
            _LOG_WARN("epoll_wait error, exit. erron: %d", errno);
            break;
        }
        // OSEVPF("epoll_wait ready: %d\n", ready);
        unsigned int inde = 0x00;
        for (; inde < ready; ++inde) {
            event_data *evd = (event_data*) events[inde].data.ptr;
            // OSEVPF("events[inde].events:%x evd->sockfd:%d\n", events[inde].events, evd->sockfd);
            if (evd->evctrl) ACCEPT_CONTRO(epofd, elist, colfd, evd, check_tatol, time_out) // accept ctrl
            else if (events[inde].events & (EPOLLERR | EPOLLHUP | EPOLLRDHUP))
                CLOSE_EXCEPTIO(evd, epofd, elist, events[inde]) // exception event
            else if (events[inde].events & EPOLLIN) RECEIVE_DATA(evd, epofd, elist) // read event
            else if (events[inde].events & EPOLLOUT) SEND_MESSAGE(evd, epofd, elist) // write event
            } // handle epoll
        // OSEVPF("loop continue!\n");
    } // main loop An established connection was aborted by the software in your host machine.
    //
    _LOG_WARN("QUIT EVENT LOOP, ERROR!");
    // free resource
    close(epofd);
    dele_evd_list(elist);
    DELETE_EVENTS(events);
    final_event_data(evds, max_events);
    DELETE_EVDATS(evds);
    //
    _LOG_WARN("EXIT OBJSERV ERROR!");
    return ERR_SUCCESS;
}

