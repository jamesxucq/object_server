#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <wait.h>

#include "commo_header.h"
#include "compi_clang.h"
#include "lv2p_decla.h"
#include "debug_funct_co.h"

//
#define GCC_COMPI_TOK   "gcc"
#define GCC_COMPI_LABLE     "gcc compiling"

// #define LIBPACKING_TOK    "-lpacking"

#define FILLI_CLANG_LIBRA_PARAM(LINE_TXT, COMPI_TOK, LIBR_FILE, CLAN_FILE) \
    LINE_TXT[0x00] = COMPI_TOK; LINE_TXT[0x01] = "-Wall"; \
    LINE_TXT[0x02] = "-fPIC"; LINE_TXT[0x03] = "-O2"; \
    LINE_TXT[0x04] = "-shared"; LINE_TXT[0x05] = "-o"; \
    LINE_TXT[0x06] = LIBR_FILE; LINE_TXT[0x07] = CLAN_FILE; \
    LINE_TXT[0x08] = NULL;
// LINE_TXT[0x08] = LIBPACKING_TOK; LINE_TXT[0x09] = NULL;
//

#define RBUF_LENG      0x1000  // 4K

static int clang_libra_compile(char *libr_path, char *clan_file, char *comp_mesg) {
    OSEVPF("[FUNC]:clang_libra_compile. clan_file:|%s|\n", clan_file);
    char *parm_line[MAX_PARAM_CNT];
    int errfd[0x02];
    if (pipe(errfd)) return -1;
    //
    pid_t pid = vfork();
    if (0x00 > pid) {
        close(errfd[0x00]);
        close(errfd[0x01]);
        OSEVPF("fork gcc ERROR!\n");
        return -1;
    } else if (!pid) {
        close(errfd[0x00]);
        if (-1 == dup2(errfd[0x01], STDERR_FILENO))
            return -1;
        close(errfd[0x01]);
        //
        FILLI_CLANG_LIBRA_PARAM(parm_line, GCC_COMPI_TOK, libr_path, clan_file)
#ifdef _DEBUG
                PRIN_parms_label(GCC_COMPI_LABLE, parm_line);
#endif
        execvp(parm_line[0x00], parm_line);
        OSEVPF("gcc compile error.\n");
        exit(-1);
    }
    //
    int realen;
    char rbuf[RBUF_LENG];
    close(errfd[0x01]);
    while (0x00 < (realen = read(errfd[0x00], rbuf, RBUF_LENG))) {
        memcpy(comp_mesg, rbuf, realen);
        comp_mesg += realen;
        // OSEVPF("loop realen:%d\n", realen);
    }
    // OSEVPF("finish realen:%d\n", realen);
    comp_mesg[0x00] = '\0';
    close(errfd[0x00]);
    //
    wait(NULL);
    return 0x00;
}

int compi_clang_libra(char *libr_path, char *clan_path, char *comp_mesg) {
    // OSEVPF("[FUNC]:----- compi_clang_libra.\n");
    // OSEVPF("clan_path:|%s|\n", clan_path);
    if (clang_libra_compile(libr_path, clan_path, comp_mesg))
        return -1;
    OSEVPF("comp_mesg:|%s|\n", comp_mesg);
    if (FILE_EXIST(libr_path))
        return -1;
    OSEVPF("libr_path:|%s|\n", libr_path);
    OSEVPF("Creat library file OK!\n");
    return 0x00;
}

//
#define FILLI_CLANG_OBJEC_PARAM(LINE_TXT, COMPI_TOK, OBJE_FILE, CLAN_FILE) \
    LINE_TXT[0x00] = COMPI_TOK; LINE_TXT[0x01] = "-Wall"; \
    LINE_TXT[0x02] = "-fPIC"; LINE_TXT[0x03] = "-O2"; \
    LINE_TXT[0x04] = "-c"; LINE_TXT[0x05] = "-o"; \
    LINE_TXT[0x06] = OBJE_FILE; LINE_TXT[0x07] = CLAN_FILE; \
    LINE_TXT[0x08] = NULL;

//

static int clang_objec_compile(char *obje_path, char *clan_file, char *comp_mesg) {
    char *parm_line[MAX_PARAM_CNT];
    int errfd[0x02];
    if (pipe(errfd)) return -1;
    //
    pid_t pid = vfork();
    if (0x00 > pid) {
        close(errfd[0x00]);
        close(errfd[0x01]);
        OSEVPF("fork gcc ERROR!\n");
        return -1;
    } else if (!pid) {
        close(errfd[0x00]);
        if (-1 == dup2(errfd[0x01], STDERR_FILENO))
            return -1;
        close(errfd[0x01]);
        //
        FILLI_CLANG_OBJEC_PARAM(parm_line, GCC_COMPI_TOK, obje_path, clan_file)
#ifdef _DEBUG
                PRIN_parms_label(GCC_COMPI_LABLE, parm_line);
#endif
        execvp(parm_line[0x00], parm_line);
        OSEVPF("gcc compile error.\n");
        exit(-1);
    }
    //
    int realen;
    char rbuf[RBUF_LENG];
    close(errfd[0x01]);
    while (0x00 < (realen = read(errfd[0x00], rbuf, RBUF_LENG))) {
        memcpy(comp_mesg, rbuf, realen);
        comp_mesg += realen;
        // OSEVPF("loop realen:%d\n", realen);
    }
    // OSEVPF("finish realen:%d\n", realen);
    comp_mesg[0x00] = '\0';
    close(errfd[0x00]);
    //
    wait(NULL);
    return 0x00;
}

int compi_clang_objec(char *obje_path, char *clan_path, char *comp_mesg) {
    // OSEVPF("[FUNC]:----- compi_clang_objec.\n");
    // OSEVPF("clan_path:|%s|\n", clan_path);
    if (clang_objec_compile(obje_path, clan_path, comp_mesg))
        return -1; // fixme: 20170116
    // OSEVPF("comp_mesg:|%s|\n", comp_mesg);
    if (FILE_EXIST(obje_path)) return -1;
    OSEVPF("obje_path:|%s|\n", obje_path);
    OSEVPF("Creat object file OK!\n");
    return 0x00;
}

//
#define ECHO_OBJE_FILE(LINE, INDE, OFILE) { \
    unsigned int inde = INDE; \
    for(; OFILE[0x00]; ++inde, ++OFILE) { \
        LINE[inde] = OFILE[0x00]; \
    } \
    LINE[inde] = NULL; \
}

#define FILLI_OBJEC_LIBRA_PARAM(LINE_TXT, COMPI_TOK, LIBR_FILE, OBJE_NAMP) \
    LINE_TXT[0x00] = COMPI_TOK; LINE_TXT[0x01] = "-Wall"; \
    LINE_TXT[0x02] = "-fPIC"; LINE_TXT[0x03] = "-shared"; \
    LINE_TXT[0x04] = "-o"; LINE_TXT[0x05] = LIBR_FILE; \
    ECHO_OBJE_FILE(LINE_TXT, 0x06, OBJE_NAMP)
// LINE_TXT[0x06] = LIBPACKING_TOK; ECHO_OBJE_FILE(LINE_TXT, 0x07, OBJE_NAMP)
//

static int objec_libra_compile(char *libr_path, char **obje_namp, char *comp_mesg) {
    char *parm_line[MAX_PARAM_CNT];
    int errfd[0x02];
    if (pipe(errfd)) return -1;
    //
    pid_t pid = vfork();
    if (0x00 > pid) {
        close(errfd[0x00]);
        close(errfd[0x01]);
        OSEVPF("fork gcc ERROR!\n");
        return -1;
    } else if (!pid) {
        close(errfd[0x00]);
        if (-1 == dup2(errfd[0x01], STDERR_FILENO))
            return -1;
        close(errfd[0x01]);
        //
        FILLI_OBJEC_LIBRA_PARAM(parm_line, GCC_COMPI_TOK, libr_path, obje_namp)
#ifdef _DEBUG
                PRIN_parms_label(GCC_COMPI_LABLE, parm_line);
#endif
        execvp(parm_line[0x00], parm_line);
        OSEVPF("gcc compile error.\n");
        exit(-1);
    }
    //
    int realen;
    char rbuf[RBUF_LENG];
    close(errfd[0x01]);
    while (0x00 < (realen = read(errfd[0x00], rbuf, RBUF_LENG))) {
        memcpy(comp_mesg, rbuf, realen);
        comp_mesg += realen;
        // OSEVPF("loop realen:%d\n", realen);
    }
    // OSEVPF("finish realen:%d\n", realen);
    comp_mesg[0x00] = '\0';
    close(errfd[0x00]);
    //
    wait(NULL);
    return 0x00;
}

int compi_objec_libra(char *libr_path, char **obje_namp, char *comp_mesg) {
    // OSEVPF("[FUNC]:----- compi_clang_libra.\n");
    // OSEVPF("obje_path:|%s|\n", obje_path);
    if (objec_libra_compile(libr_path, obje_namp, comp_mesg))
        return -1; // fixme: 20170116
    // OSEVPF("comp_mesg:|%s|\n", comp_mesg);
    if (FILE_EXIST(libr_path)) return -1;
    OSEVPF("libr_path:|%s|\n", libr_path);
    OSEVPF("Creat library file OK!\n");
    return 0x00;
}
