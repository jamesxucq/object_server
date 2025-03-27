
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <signal.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "third_party.h"
#include "server_macro.h"

#include "basev_bzl.h"
#include "authen_bzl.h"
#include "privile_bzl.h"
#include "invok_bzl.h"
#include "chk_privi_bzl.h"
#include "reqin_ite.h"
#include "conte_bzl.h"
#include "rstatu_bzl.h"
#include "rive_bzl.h"
// #include "plugin.h"

#include "epoll_serv.h"
#include "process_cycle.h"
#include "parse_conf.h"
#include "osev_bzl.h"
#include "osev_serv.h"
#include "sconfig.h"

//

static void status_logger() {
#ifdef _DEBUG
    fprintf(stderr, "Debug %s.\n", PROGRAM_NAME);
#else
    fprintf(stderr, "Release %s.\n", PROGRAM_NAME);
#endif
    //
#ifdef NOAUTH
    fprintf(stderr, "OSEV disable authen.\n");
#else
    fprintf(stderr, "OSEV enable authen.\n");
#endif // NOAUTH
    // 
}

//

int initialize_serv(char *xml_config) {
    serv_config *config = NULL;
    // init serv tui module
    config = servbzl_create(xml_config);
    if (!config) return ERR_FAULT;
    fprintf(stdout, "Configuration file name:%s\n", xml_config);
    //
    if (rstabzl_create(config->data_directory)) {
        fprintf(stderr, "basebzl_create ERROR!\n");
        return ERR_FAULT;
    }
    if (basebzl_create()) {
        fprintf(stderr, "basebzl_create ERROR!\n");
        return ERR_FAULT;
    }
    //
    if (privbzl_create(config->max_connecting)) {
        fprintf(stderr, "authbzl_create ERROR!\n");
        return ERR_FAULT;
    }
    // 
    if (authbzl_create()) {
        fprintf(stderr, "authbzl_create ERROR!\n");
        return ERR_FAULT;
    }
    // init riverfs module
    if (rivebzl_create(config->data_directory)) {
        fprintf(stderr, "rivebzl_create ERROR!\n");
        return ERR_FAULT;
    }
    //
    return ERR_SUCCESS;
}

int finalize_serv() {
    // init riverfs module
    rivebzl_destroy();
    // stop the dir watcher thread
    authbzl_destroy();
    //
    privbzl_destroy();
    //
    basebzl_destroy();
    //
    rstabzl_destroy();
    // uninit client gui module
    servbzl_destroy();
    //
    return ERR_SUCCESS;
}

//

int main(int argc, char *argv[]) {
    char xml_config[MAX_PATH * 3];
    status_logger();
    //
    if (parse_args(xml_config, argc, argv))
        return ERR_FAULT;
    if (FILE_EXIST(xml_config)) {
        fprintf(stderr, "%s configuration file not exist.\n", xml_config);
        return EXIT_FAILURE;
    }
    //    
    struct sigaction sa;
    sa.sa_handler = SIG_IGN; // SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; // 0;
    if (sigaction(SIGABRT, &sa, NULL) < 0) fprintf(stderr, "Can't ignore SIGABRT\n");
    //
    if (initialize_serv(xml_config)) {
        fprintf(stderr, "Initialize OSEV failed!\n");
        return ERR_FAULT;
    }
    fprintf(stderr, "Initialize OSEV OK!\n");
    serv_config *config = get_serv_config();
#ifndef _DEBUG
    if (daemonize(PROGRAM_NAME)) return ERR_FAULT;
#endif
    // init log module
    log_initial(config->runtime_log.logfile, config->runtime_log.debug_level);
    access_initial(config->access_log.logfile);
    //
#ifndef _DEBUG
    master_process_cycle(config);
#else
    _LOG_WARN("Debug single mode!");
    single_process_cycle(config);
#endif
    log_final();
    access_final();
    //
    if (finalize_serv()) {
        _LOG_WARN("Finalize OSEV failed!");
        return ERR_FAULT;
    }
    _LOG_INFO("Finalize OSEV OK!");
    //
    return ERR_SUCCESS;
}

