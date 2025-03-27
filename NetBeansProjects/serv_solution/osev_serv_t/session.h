#ifndef SESSION_H_
#define SESSION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "server_macro.h"
#include "seion_utili.h"
// #include "third_party.h"

//
#define OPEN_AUTHEN_SE(REV_ERRNO) { \
    OSEVPF("[FUNC]:OPEN_AUTHEN_SE\n"); \
}
#define CLOSE_AUTHEN_SE(RVSCTL) { \
    OSEVPF("[FUNC]:CLOSE_AUTHEN_SE\n"); \
    /* */ \
    (RVSCTL)->status_code = OK; \
}

//
#define OPEN_POST_SE(REV_ERRNO) { \
    OSEVPF("[FUNC]:OPEN_POST_SE\n"); \
}
#define CLOSE_POST_SE(RVSCTL) { \
    OSEVPF("[FUNC]:CLOSE_POST_SE\n"); \
    /* */ \
    (RVSCTL)->status_code = OK; \
}

//
#define OPEN_STATUS_SE(REV_ERRNO) { \
    OSEVPF("[FUNC]:OPEN_STATUS_SE\n"); \
}
#define CLOSE_STATUS_SE(RVSCTL) { \
    OSEVPF("[FUNC]:CLOSE_STATUS_SE\n"); \
    /* */ \
    (RVSCTL)->status_code = OK; \
}

//
#define OPEN_COMAND_SE(REV_ERRNO) { \
    OSEVPF("[FUNC]:OPEN_COMAND_SE\n"); \
}
#define CLOSE_COMAND_SE(RVSCTL) { \
    OSEVPF("[FUNC]:CLOSE_COMAND_SE\n"); \
    /* */ \
    (RVSCTL)->status_code = OK; \
}

// OPEN_PRIVILE_SE
#define OPEN_PRIVILE_SE(REV_ERRNO) { \
    OSEVPF("[FUNC]:OPEN_PRIVILE_SE\n"); \
}
#define CLOSE_PRIVILE_SE(RVSCTL) { \
    OSEVPF("[FUNC]:CLOSE_PRIVILE_SE\n"); \
    /* */ \
    (RVSCTL)->status_code = OK; \
}

//
#define OPEN_KALIVE_SE(REV_ERRNO) { \
    OSEVPF("[FUNC]:OPEN_KALIVE_SE\n"); \
}
#define CLOSE_KALIVE_SE(RVSCTL) { \
    OSEVPF("[FUNC]:CLOSE_KALIVE_SE\n"); \
    /* */ \
    (RVSCTL)->status_code = OK; \
}

// OPEN_INVOKE_SE
#define OPEN_INVOKE_SE(REV_ERRNO) { \
    OSEVPF("[FUNC]:OPEN_INVOKE_SE\n"); \
}
#define CLOSE_INVOKE_SE(RVSCTL) { \
    OSEVPF("[FUNC]:CLOSE_INVOKE_SE\n"); \
    /* */ \
    (RVSCTL)->status_code = OK; \
}

// OPEN_COLLE_SE
#define OPEN_COLLE_SE(REV_ERRNO) { \
    OSEVPF("[FUNC]:OPEN_COLLE_SE\n"); \
}
#define CLOSE_COLLE_SE(RVSCTL) { \
    OSEVPF("[FUNC]:CLOSE_COLLE_SE\n"); \
    /* */ \
    (RVSCTL)->status_code = OK; \
}

// OPEN_CONST_SE
#define OPEN_CONST_SE(RVSCTL, REV_ERRNO) { \
    OSEVPF("[FUNC]:OPEN_CONST_SE\n"); \
    /* */ \
    (RVSCTL)->posi_requ = (char *) (RVSCTL)->requ_memo; \
}
#define CLOSE_CONST_STACO_SE(RVSCTL) \
    (RVSCTL)->status_code = OK;

#define CLOSE_CONST_RESPO_SE(RVSCTL) { \
    (RVSCTL)->status_code = OK; \
    rewind((RVSCTL)->resp_stram); \
}

// OPEN_QUERY_SE
#define OPEN_QUERY_MEMO_SE(RVSCTL, REV_ERRNO) { \
    OSEVPF("[FUNC]:OPEN_QUERY_MEMO_SE\n"); \
    /* */ \
    (RVSCTL)->posi_requ = (char *) (RVSCTL)->requ_memo; \
}
#define OPEN_QUERY_FILE_SE(REV_ERRNO) { \
    OSEVPF("[FUNC]:OPEN_QUERY_FILE_SE\n"); \
}

// CLOSE_CONST_SE // CLOSE_QUERY_SE
#define CLOSE_QUERY_STACO_SE(RVSCTL) \
    (RVSCTL)->status_code = OK;

#define CLOSE_QUERY_REQUE_SE(RVSCTL) { \
    (RVSCTL)->status_code = OK; \
    rewind((RVSCTL)->requ_stram); \
}
#define CLOSE_QUERY_RESPO_SE(RVSCTL) { \
    (RVSCTL)->status_code = OK; \
    rewind((RVSCTL)->resp_stram); \
}
#define CLOSE_QUERY_QUESP_SE(RVSCTL) { \
    (RVSCTL)->status_code = OK; \
    rewind((RVSCTL)->requ_stram); \
    rewind((RVSCTL)->resp_stram); \
}

//
#define OPEN_DONE_SE(REV_ERRNO) { \
    OSEVPF("[FUNC]:OPEN_DONE_SE\n"); \
}
#define CLOSE_DONE_SE(RVSCTL) { \
    OSEVPF("[FUNC]:CLOSE_DONE_SE\n"); \
    /* */ \
    (RVSCTL)->status_code = OK; \
}

#endif /* SESSION_H_ */
