#ifndef _EVD_LIST_H_
#define _EVD_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "commo_header.h"

    //

    struct _event_data_ {
        int sockfd;
        int evctrl; // 0:data 1:ctrl
        BYTE *buffer; // recv data buffer
        long long rsleng;
        //
        int evloop;
        unsigned long long last_active; // last active time
        //
        int evstatu;
        _event *bev;
        long long sleng;
    };

    typedef struct _event_data_ event_data;

    //

    struct _levd_list_ {
        struct _levd_list_ *prev, *next;
        //
        event_data *evd;
    };

    typedef struct _levd_list_ levd_list;

    //

    struct _evd_list_ {
        levd_list *active;
        levd_list *sleep;
        levd_list *chkpos;
    };

    typedef struct _evd_list_ evd_list;

    //
    //
#include "epoll_serv.h"
    int init_evd_list(evd_list *elist, event_data *evds, int events_tatol);
    void dele_evd_list(evd_list *elist);

    levd_list *get_levd_list(evd_list *elist);
    levd_list *set_levd_list(evd_list *elist, event_data *evd);

#ifdef __cplusplus
}
#endif

#endif /* _EVD_LIST_H_ */


