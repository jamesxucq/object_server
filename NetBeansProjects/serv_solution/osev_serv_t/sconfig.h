
/* 
 * File:   sconfig.h
 * Author: James Xu
 *
 * Created on 2016.12.28, AM 10:41
 */

#ifndef SCONFIG_H
#define SCONFIG_H

#include "commo_macro.h"
#include "osev_datyp.h"

#ifdef __cplusplus
extern "C" {
#endif

    struct _log_config_ {
        char logfile[MAX_PATH * 3];
        LOG_LVL_T debug_level;
    };

    typedef struct _log_config_ log_config;

    //

    struct _serv_config_ {
        // system info
        char user_name[_USERN_LENGTH_];
        char group_name[GROUPN_LENGTH];
        uid_t _user_id_;
        gid_t _group_id_;
        int worker_threads;
        char lock_file[MAX_PATH * 3];
        char pid_file[MAX_PATH * 3];
        // server info
        char data_directory[MAX_PATH * 3];
        // network info
        char serv_address[SERVN_LENGTH];
        short bind_port;
        int max_connecting;
        int seion_timeout;
        // log config
        log_config runtime_log;
        log_config access_log;
    };

    typedef struct _serv_config_ serv_config;

#ifdef __cplusplus
}
#endif

#endif /* SCONFIG_H */

