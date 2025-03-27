
/* 
 * File:   serv_utili.h
 * Author: James Xu
 *
 * Created on 2023.12.22, AM 10:19
 */

#ifndef SERV_UTILI_H
#define SERV_UTILI_H

#include "process/initialize.h"
#include "process/hand_binary.h"
#include "process/finalize.h"
#include "process/exceptio.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

#define EVENT_DELET(EPO_FD, EPO_LIST, EVD) { \
    /* OSEVPF("event del, close:%d\n", EVD->sockfd); */ \
    event_dele(EPO_FD, EVD); \
    close(EVD->sockfd); \
    if (!set_levd_list(EPO_LIST, EVD)) { _LOG_WARN("levd_list del fail."); } \
}

    // accept new connections from clients
#define ACCEPT_CONNECT(EPO_FD, EPO_LIST, LISTEN_FD) { \
    struct sockaddr_in sin; \
    socklen_t len = sizeof (struct sockaddr_in); \
    int aifd; \
    levd_list *levd_list; \
\
/*_LOG_WARN("accept connect!");*/ \
    for (;;) { /* accept */ \
        if ((aifd = accept(LISTEN_FD, (struct sockaddr*) &sin, &len)) == -1) { \
            if ((EAGAIN != errno) && (EINTR != errno)) { \
                _LOG_WARN("%s: bad accept", __func__); \
            } \
            break; \
        } \
/* OSEVPF("accept:%d\n", aifd); */ \
        do { \
            levd_list = get_levd_list(EPO_LIST); \
            if (!levd_list) { \
                _LOG_WARN("%s:max connection limit[%d].", __func__, max_events); \
                break; \
            } \
            /* memset(levd_list->evd, '\0', sizeof(event_data)); */ \
            /* if (levd_list->evd->bev) INITIAL_EVENT(levd_list->evd->bev); */ \
            /* set nonblocking */ \
            if (fcntl(aifd, F_SETFL, fcntl(aifd, F_GETFL) | O_NONBLOCK) < 0x00) \
                break; \
            /* add a read event for receive data */ \
            event_set(levd_list->evd, aifd); \
            event_add(EPO_FD, EPOLLIN | EPOLLET, levd_list->evd); \
_LOG_INFO("new connection[%s:%d][time:%d][fd:%d]", inet_ntoa(sin.sin_addr), ntohs(sin.sin_port), levd_list->evd->last_active, aifd); \
        } while(0x00); \
    } \
}

#define CONTRO_SIGNAL(SIFD) { \
    struct signalfd_siginfo fdsi; \
    ssize_t realen; \
    for(;;) { \
        realen = read(SIFD, &fdsi, sizeof(struct signalfd_siginfo)); \
        if (sizeof(struct signalfd_siginfo) == realen) { \
            if (SIGINT == fdsi.ssi_signo) { _LOG_WARN("GOT SIGINT!"); } \
            else if (SIGPIPE == fdsi.ssi_signo) { _LOG_WARN("GOT SIGPIPE!"); } \
            else { _LOG_WARN("read unexpected signal!"); } \
        } else { \
            if((EAGAIN != errno) && (EINTR != errno)) \
                { _LOG_WARN("signal fd read error! sifd:%d", SIFD); } \
            break; \
        } \
    } \
}

    // alarm catch function
#define CHECK_TIMEOUT(EPO_FD, EPO_LIST, CHECK_TATOL, TIME_OUT, NOW_TIME) { \
    levd_list *levd_head = NULL; \
    levd_list *levd_list, *next_elist; \
    /* a simple timeout check here, every time 100, better to use a mini-heap, and add timer event */ \
    unsigned int inde = 0x00; \
    for (levd_list = EPO_LIST->chkpos; levd_list && inde<CHECK_TATOL; ++inde, levd_list = (levd_head==next_elist?0L:next_elist)) { /* doesn't check listen fd */ \
        next_elist = levd_list->next == levd_list ? 0L: levd_list->next; \
        if ((NOW_TIME - levd_list->evd->last_active) >= TIME_OUT) { /* 60s timeout */ \
            /* decrease auth cache refere */ \
            _LOG_WARN("[fd:%d] timeout[%d--%d].", levd_list->evd->sockfd, levd_list->evd->last_active, NOW_TIME); \
            levd_list->evd->bev->rvse_excepti_hand(levd_list->evd->bev->seion); \
            EVENT_DELET(EPO_FD, EPO_LIST, levd_list->evd) \
        } else if (!levd_head) levd_head = levd_list; \
    } \
}

    // sockets connect timeout check here
#define CONTRO_TIMEOUT(EPO_FD, EPO_LIST, CHECK_TATOL, TIME_OUT, TIFD) { \
/*OSEVPF("check timeout!\n");*/ \
    uint64_t exp; \
    ssize_t realen = read(TIFD, &exp, sizeof(uint64_t)); \
    if (sizeof (uint64_t) == realen) { \
/*OSEVPF("check timeout! exp:%llu time(NULL):%lu\n", exp, time(NULL));*/ \
        CHECK_TIMEOUT(EPO_FD, EPO_LIST, CHECK_TATOL, TIME_OUT, time(NULL)); \
    } else { _LOG_WARN("timer read error! tifd:%d", TIFD); } \
}

#define ACCEPT_CONTRO(EPO_FD, EPO_LIST, COLFD, EVD, CHECK_TATOL, TIME_OUT) { \
/*_LOG_WARN("accept contro!");*/ \
    if(COLFD[0x00] == EVD->sockfd) \
        ACCEPT_CONNECT(EPO_FD, EPO_LIST, COLFD[0x00]) \
    else if(COLFD[0x01] == EVD->sockfd) \
        CONTRO_TIMEOUT(EPO_FD, EPO_LIST, CHECK_TATOL, TIME_OUT, COLFD[0x01])\
    else if(COLFD[0x02] == EVD->sockfd) CONTRO_SIGNAL(COLFD[0x02]) \
}

    // set event last_active
#define EVENT_ACTIVE(EVD) EVD->last_active = time(NULL);

#define INITIAL_EVENT_HANDLE(BEV) { \
    BEV->recv_initial_hand = requ_initialize_tab[BEV->levtyp][BEV->levivk]; \
    BEV->recv_binary_hand = requ_handler_tab[BEV->levtyp][BEV->levivk]; \
    BEV->recv_finaliz_hand = requ_finalize_tab[BEV->levtyp][BEV->levivk]; \
    BEV->send_initial_hand = resp_initialize_tab[BEV->levtyp][BEV->levivk]; \
    BEV->send_binary_hand = resp_handler_tab[BEV->levtyp][BEV->levivk]; \
    BEV->send_finaliz_hand = resp_finalize_tab[BEV->levtyp][BEV->levivk]; \
    BEV->rvse_excepti_hand = rvse_exceptio_tab[BEV->levtyp][BEV->levivk]; \
}

    //

#define INITIAL_RECV_EVENT(EVD, EVDAT) { \
/*OSEVPF("---- EVD->sockfd:%d EVD->evstatu:%d\n", EVD->sockfd, EVD->evstatu);*/ \
    REQU_EVDAT_HDBD(EVDAT, EVD); \
    PROTO_REQHAD(EVD->bev, (EVDAT)->head_ptr) \
/*OSEVPF("---- levtyp:%d\n", EVD->bev->levtyp);*/ \
    INITIAL_EVENT_HANDLE(EVD->bev) \
/*OSEVPF("---- EVD->bev->recv_initial_hand:%X\n", EVD->bev->recv_initial_hand);*/ \
    if((EVD->evstatu = EVD->bev->recv_initial_hand(EVD->bev->seion, &EVD->bev->evdat))) { \
        if(!(EVD->evstatu = EVD->bev->recv_binary_hand(&EVD->bev->seion->rvsctl, &EVD->bev->evdat))) \
            EVD->bev->recv_finaliz_hand(EVD->bev->seion); \
    } else EVD->bev->recv_finaliz_hand(EVD->bev->seion); \
/*OSEVPF("---- EVD->evstatu:%d\n", EVD->evstatu);*/ \
}

#define HANDLER_RECV_EVENT(EVD, EVDAT) { \
    REQU_EVDAT_BODY(EVDAT, EVD); \
    if(!(EVD->evstatu = EVD->bev->recv_binary_hand(&EVD->bev->seion->rvsctl, &EVD->bev->evdat))) \
        EVD->bev->recv_finaliz_hand(EVD->bev->seion); \
}

    // receive data
#define RECEIVE_DATA(EVD, EPO_FD, EPO_LIST) { \
/*_LOG_WARN("EPOLLE RECEIVE!");*/ \
    for (;;) { /* receive data */ \
/*struct timeval t_start,t_end; gettimeofday(&t_start, NULL);*/\
        EVD->rsleng = recv(EVD->sockfd, EVD->buffer, BUFF_SOCKET_SIZE, 0x00); \
/*gettimeofday(&t_end, NULL); fprintf(stderr, "%ld\n", t_end.tv_usec - t_start.tv_usec);*/\
        if (0x00 < EVD->rsleng) { \
            INITIAL_RECV_EVENT(EVD, &EVD->bev->evdat) \
            if (!EVD->evstatu) { /* change to send event */ \
/*_LOG_WARN("[fd:%d] recv over, modify to send.", EVD->sockfd);*/ \
                event_set(EVD, FD_CONTINUE); \
                event_mod(EPO_FD, EPOLLOUT | EPOLLET, EVD); \
                break; \
            } else { \
                if(!POW2N_MOD(EVD->evloop++, CONNECT_ACTIVE)) EVENT_ACTIVE(EVD) \
                for (;;) { /* receive data */ \
/*struct timeval t_start,t_end; gettimeofday(&t_start, NULL);*/\
                    EVD->rsleng = recv(EVD->sockfd, EVD->buffer, BUFF_SOCKET_SIZE, 0x00); \
/*gettimeofday(&t_end, NULL); fprintf(stderr, "%ld\n", t_end.tv_usec - t_start.tv_usec);*/\
                    if (0x00 < EVD->rsleng) { \
                        HANDLER_RECV_EVENT(EVD, &EVD->bev->evdat) \
                        if (!EVD->evstatu) { /* change to send event */ \
/*_LOG_WARN("[fd:%d] recv over, modify to send.", EVD->sockfd);*/ \
                            event_set(EVD, FD_CONTINUE); \
                            event_mod(EPO_FD, EPOLLOUT | EPOLLET, EVD); \
                            break; \
                        } else if(!POW2N_MOD(EVD->evloop++, CONNECT_ACTIVE)) EVENT_ACTIVE(EVD) \
                    } else if (!EVD->rsleng) { \
/*_LOG_WARN("[fd:%d] recv closed gracefully.", EVD->sockfd);*/ \
                        EVENT_DELET(EPO_FD, EPO_LIST, EVD) \
                        break; \
                    } else { \
                        if ((EAGAIN != errno) && (EINTR != errno)) { \
/*_LOG_WARN("recv[fd:%d] error[%d]:%s", EVD->sockfd, errno, strerror(errno));*/ \
                            EVD->bev->rvse_excepti_hand(EVD->bev->seion); \
                            EVENT_DELET(EPO_FD, EPO_LIST, EVD) \
                        } \
                        break; \
                    } \
                } \
                break; \
            } \
        } else if (!EVD->rsleng) { \
/*_LOG_WARN("[fd:%d] recv closed gracefully.", EVD->sockfd);*/ \
            EVENT_DELET(EPO_FD, EPO_LIST, EVD) \
            break; \
        } else { \
            if ((EAGAIN != errno) && (EINTR != errno)) { \
/*_LOG_WARN("recv[fd:%d] error[%d]:%s", EVD->sockfd, errno, strerror(errno));*/ \
                EVD->bev->rvse_excepti_hand(EVD->bev->seion); \
                EVENT_DELET(EPO_FD, EPO_LIST, EVD) \
            } \
            break; \
        } \
    } \
}

    //
#define INITIAL_SEND_EVENT(EVD, EVDAT) { \
    RESP_EVDAT_HINI(EVDAT, EVD) \
    if((EVD->evstatu = EVD->bev->send_initial_hand(EVD->bev->seion, &EVD->bev->evdat))) { \
        if(!(EVD->evstatu = EVD->bev->send_binary_hand(&EVD->bev->seion->rvsctl, &EVD->bev->evdat))) \
            EVD->bev->send_finaliz_hand(EVD->bev->seion); \
    } else EVD->bev->send_finaliz_hand(EVD->bev->seion); \
    RESP_EVDAT_HEND(EVDAT, EVD) \
}

#define HANDLER_SEND_EVENT(EVD, EVDAT) { \
    RESP_EVDAT_BINI(EVDAT, EVD) \
    if(!(EVD->evstatu = EVD->bev->send_binary_hand(&EVD->bev->seion->rvsctl, &EVD->bev->evdat))) \
        EVD->bev->send_finaliz_hand(EVD->bev->seion); \
    RESP_EVDAT_BEND(EVDAT, EVD) \
}

    // send data
#define SEND_MESSAGE(EVD, EPO_FD, EPO_LIST) { \
/*_LOG_WARN("EPOLL SEND!");*/ \
    unsigned int send_continue = SEND_CONTINUE; \
    int cleng; \
    for (;;) { /* send data */ \
        INITIAL_SEND_EVENT(EVD, &EVD->bev->evdat) \
/* struct timeval t_start,t_end; gettimeofday(&t_start, NULL);*/\
        cleng = send(EVD->sockfd, EVD->buffer + EVD->sleng, EVD->rsleng - EVD->sleng, 0x00); \
/* gettimeofday(&t_end, NULL); fprintf(stderr, "%ld\n", t_end.tv_usec - t_start.tv_usec);*/\
/*_LOG_WARN("cleng:%d EVD->rsleng:%d EVD->sleng:%d", cleng, EVD->rsleng, EVD->sleng);*/ \
/* log_binary_code(EVD->buffer + EVD->sleng, EVD->rsleng - EVD->sleng); */ \
        if (0x00 < cleng) { \
            EVD->sleng += cleng; \
            if (EVD->sleng != EVD->rsleng) { \
                send_continue = SEND_CONTINUE; \
                for (;;) { /* send data */ \
                    if (SEND_CONTINUE != send_continue) \
                        HANDLER_SEND_EVENT(EVD, &EVD->bev->evdat) \
/* struct timeval t_start,t_end; gettimeofday(&t_start, NULL);*/\
                    cleng = send(EVD->sockfd, EVD->buffer + EVD->sleng, EVD->rsleng - EVD->sleng, 0x00); \
/* gettimeofday(&t_end, NULL); fprintf(stderr, "%ld\n", t_end.tv_usec - t_start.tv_usec);*/\
/*_LOG_WARN("cleng:%d EVD->rsleng:%d EVD->sleng:%d", cleng, EVD->rsleng, EVD->sleng);*/ \
/* log_binary_code(EVD->buffer + EVD->sleng, EVD->rsleng - EVD->sleng); */ \
                    if (0x00 < cleng) { \
                        EVD->sleng += cleng; \
                        if (EVD->sleng != EVD->rsleng) { \
                            send_continue = SEND_CONTINUE; \
                        } else { \
                            if (!EVD->evstatu) { /* change to receive event */ \
                                if(OSVP_DONE != EVD->bev->levtyp) { \
/*_LOG_WARN("[fd:%d] send over, modify to recv. levtyp:%d", EVD->sockfd, EVD->bev->levtyp);*/ \
                                    event_set(EVD, FD_CONTINUE); \
                                    event_mod(EPO_FD, EPOLLIN | EPOLLET, EVD); \
                                } else { \
/*_LOG_WARN("[fd:%d] send over, delete.", EVD->sockfd);*/ \
                                    EVENT_DELET(EPO_FD, EPO_LIST, EVD) \
                                } \
                                break; \
                            } \
                            if(!POW2N_MOD(EVD->evloop++, CONNECT_ACTIVE)) EVENT_ACTIVE(EVD) \
                            send_continue = SEND_NEXTHAND; \
                        } \
                    } else { \
                        if ((EAGAIN != errno) && (EINTR != errno)) { \
/*_LOG_WARN("[fd:%d] send exception.", EVD->sockfd);*/ \
/*_LOG_WARN("send[fd:%d] error[%d]:%s", EVD->sockfd, errno, strerror(errno));*/ \
                            EVD->bev->rvse_excepti_hand(EVD->bev->seion); \
                            EVENT_DELET(EPO_FD, EPO_LIST, EVD) \
                        } \
                        break; \
                    } \
                } \
                break; \
            } else { \
                if (!EVD->evstatu) { /* change to receive event */ \
                    if(OSVP_DONE != EVD->bev->levtyp) { \
/*_LOG_WARN("[fd:%d] send over, modify to recv. levtyp:%d", EVD->sockfd, EVD->bev->levtyp);*/ \
                        event_set(EVD, FD_CONTINUE); \
                        event_mod(EPO_FD, EPOLLIN | EPOLLET, EVD); \
                    } else { \
/*_LOG_WARN("[fd:%d] send over, delete.", EVD->sockfd);*/ \
                        EVENT_DELET(EPO_FD, EPO_LIST, EVD) \
                    } \
                    break; \
                } else { \
                    if(!POW2N_MOD(EVD->evloop++, CONNECT_ACTIVE)) EVENT_ACTIVE(EVD) \
                    send_continue = SEND_NEXTHAND; \
                    for (;;) { /* send data */ \
                        if (SEND_CONTINUE != send_continue) \
                            HANDLER_SEND_EVENT(EVD, &EVD->bev->evdat) \
/* struct timeval t_start,t_end; gettimeofday(&t_start, NULL);*/\
                        cleng = send(EVD->sockfd, EVD->buffer + EVD->sleng, EVD->rsleng - EVD->sleng, 0x00); \
/* gettimeofday(&t_end, NULL); fprintf(stderr, "%ld\n", t_end.tv_usec - t_start.tv_usec);*/\
/*_LOG_WARN("cleng:%d EVD->rsleng:%d EVD->sleng:%d", cleng, EVD->rsleng, EVD->sleng);*/ \
/* log_binary_code(EVD->buffer + EVD->sleng, EVD->rsleng - EVD->sleng); */ \
                        if (0x00 < cleng) { \
                            EVD->sleng += cleng; \
                            if (EVD->sleng != EVD->rsleng) { \
                                send_continue = SEND_CONTINUE; \
                            } else { \
                                if (!EVD->evstatu) { /* change to receive event */ \
                                    if(OSVP_DONE != EVD->bev->levtyp) { \
/*_LOG_WARN("[fd:%d] send over, modify to recv. levtyp:%d", EVD->sockfd, EVD->bev->levtyp);*/ \
                                        event_set(EVD, FD_CONTINUE); \
                                        event_mod(EPO_FD, EPOLLIN | EPOLLET, EVD); \
                                    } else { \
/*_LOG_WARN("[fd:%d] send over, delete.", EVD->sockfd);*/ \
                                        EVENT_DELET(EPO_FD, EPO_LIST, EVD) \
                                    } \
                                    break; \
                                } \
                                if(!POW2N_MOD(EVD->evloop++, CONNECT_ACTIVE)) EVENT_ACTIVE(EVD) \
                                send_continue = SEND_NEXTHAND; \
                            } \
                        } else { \
                            if ((EAGAIN != errno) && (EINTR != errno)) { \
/*_LOG_WARN("[fd:%d] send exception.", EVD->sockfd);*/ \
/*_LOG_WARN("send[fd:%d] error[%d]:%s", EVD->sockfd, errno, strerror(errno));*/ \
                                EVD->bev->rvse_excepti_hand(EVD->bev->seion); \
                                EVENT_DELET(EPO_FD, EPO_LIST, EVD) \
                            } \
                            break; \
                        } \
                    } \
                    break; \
                } \
            } \
        } else { \
            if ((EAGAIN != errno) && (EINTR != errno)) { \
/*_LOG_WARN("[fd:%d] send exception.", EVD->sockfd);*/ \
/*_LOG_WARN("send[fd:%d] error[%d]:%s", EVD->sockfd, errno, strerror(errno));*/ \
                EVD->bev->rvse_excepti_hand(EVD->bev->seion); \
                EVENT_DELET(EPO_FD, EPO_LIST, EVD) \
            } \
            break; \
        } \
    } \
}

    // exception
#define CLOSE_EXCEPTIO(EVD, EPO_FD, EPO_LIST, EVENTS) { \
_LOG_WARN("[fd:%d] epoll hup or err, everts:%x, loop closed.", EVD->sockfd, EVENTS.events); \
    if(EVENTS.events & (EPOLLERR | EPOLLHUP)) \
        EVD->bev->rvse_excepti_hand(EVD->bev->seion); \
    EVENT_DELET(EPO_FD, EPO_LIST, EVD) \
}

    //

#define DELETE_EVENTS(EVENTS) free(EVENTS)
#define DELETE_EVDATS(EVDATS) free(EVDATS)

#ifdef __cplusplus
}
#endif

#endif /* SERV_UTILI_H */

