#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <wait.h>
#include<grp.h>
#include <pwd.h>

#include "commo_header.h"
#include "sconfig.h"
#include "epoll_serv.h"

#include "process_cycle.h"

//

void worker_process_init(serv_config *config) {
    /*
        if (osev_set_environment(cycle, NULL) == NULL) {
            exit(2);
        }
        if (worker >= 0 && ccf->priority != 0) {
            if (setpriority(PRIO_PROCESS, 0, ccf->priority) == -1) {
                _LOG_ERROR("setpriority(%d) failed", ccf->priority);
            }
        }
        if (ccf->rlimit_nofile != CONF_UNSET) {
            rlmt.rlim_cur = (rlim_t) ccf->rlimit_nofile;
            rlmt.rlim_max = (rlim_t) ccf->rlimit_nofile;
            if (setrlimit(RLIMIT_NOFILE, &rlmt) == -1) {
                _LOG_ERROR("setrlimit(RLIMIT_NOFILE, %i) failed", ccf->rlimit_nofile);
            }
        }
        if (ccf->rlimit_core != CONF_UNSET) {
            rlmt.rlim_cur = (rlim_t) ccf->rlimit_core;
            rlmt.rlim_max = (rlim_t) ccf->rlimit_core;
            if (setrlimit(RLIMIT_CORE, &rlmt) == -1) {
                _LOG_ERROR("setrlimit(RLIMIT_CORE, %O) failed", ccf->rlimit_core);
            }
        }
     */
    //
    if (0x00 == geteuid()) {
        if (0 == config->_group_id_) {
            _LOG_WARN("I will not set gid to 0");
            return;
        }
        //
        if (setgid(config->_group_id_) == -1) {
            _LOG_FATAL("setgid(%d) failed", config->_group_id_);
            exit(2); /* fatal */
        }
        //
        if (initgroups(config->user_name, config->_group_id_) == -1) {
            _LOG_FATAL("initgroups(%s, %d) failed", config->user_name, config->_group_id_);
        }
        if (setuid(config->_user_id_) == -1) {
            _LOG_FATAL("setuid(%d) failed", config->_user_id_);
            exit(2); /* fatal */
        }
    }
}

//
#define RETRY_SERVER_TIMES       32
#define RETRY_SERVER_DELAY       16 // 16s

pid_t start_worker_process(serv_config *config) {
    int retry_times = 0x00;
    //
    pid_t child = fork();
    switch (child) {
        case -1:
            _LOG_WARN("fork worker failed!");
        case 0: // child
            worker_process_init(config);
            while (RETRY_SERVER_TIMES > ++retry_times) {
                if (ERR_FAULT != epoll_server(config)) {
                    _LOG_WARN("epoll server start failed!");
                    break;
                }
                _LOG_WARN("epoll server start retry time: %d!", retry_times);
                sleep(RETRY_SERVER_DELAY);
            }
            break;
        default: // parent
            break;
    }
    //
    return child;
}

//
#define INVA_CHILD_PID  -1
#define RETRY_PROCESS_TIMES       16
#define RETRY_PROCESS_DELAY       32 // 32s

int master_process_cycle(serv_config *config) {
    struct timeval tv = {RETRY_PROCESS_DELAY, 0x00};
    pid_t child;
    //
    _LOG_WARN("osev: start worker process!");
    child = start_worker_process(config);
    select(0x00, NULL, NULL, NULL, &tv);
    _LOG_WARN("osev: child spawned successfully: PID: %d", child);
    //
    int restart_times = 0x00;
    int status;
    for (; (INVA_CHILD_PID == child) & (RETRY_PROCESS_TIMES > restart_times); ++restart_times) {
        switch (wait(&status)) {
            case -1:
                _LOG_ERROR("osev: master process wait error! exited.");
                return ERR_FAULT;
                break;
            default:
                if (WIFEXITED(status)) {
                    _LOG_WARN("osev: child exited with: %d", WEXITSTATUS(status));
                } else if (WIFSIGNALED(status)) {
                    _LOG_WARN("osev: child signaled: %d", WTERMSIG(status));
                } else {
                    _LOG_WARN("osev: child died somehow: exit status = %d", status);
                }
                break;
        }
        //
        _LOG_WARN("osev: restart worker process! times: %d", restart_times);
        child = start_worker_process(config);
        select(0x00, NULL, NULL, NULL, &tv);
        _LOG_WARN("osev: child spawned successfully: PID: %d", child);
    }
    //
    return ERR_SUCCESS;
}

int single_process_cycle(serv_config *config) {
    if (ERR_FAULT == epoll_server(config)) {
        _LOG_WARN("epoll server start failed!");
        return ERR_FAULT;
    }
    //
    return ERR_SUCCESS;
}




