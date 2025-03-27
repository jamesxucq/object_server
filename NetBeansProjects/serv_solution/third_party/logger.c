#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <time.h>
#include <libgen.h>
#include <errno.h>
//
#include "logger.h"

//
#define POW2N_MOD(nua, nub)  (nua & (nub - 0x01)) // x=2^n a=b%x-->a=b&(x-1)
#define BUFFER_SIZE          0x1000  // 4K
#define MAX_LOG_FILE_SIZ         0x80000000  // 128M
#define CHECK_LOGSIZ_FREQUENCY   0x1000  // 4K

static LOG_LVL_T _log_lvl_;
static char _log_file_[PATH_MAX];
static int _log_fd_ = -1;

//

void log_initial(char *logfile, LOG_LVL_T log_lvl) {
    struct stat64 statbuf;
    //
    if (logfile && (log_lvl <= LOG_LVL_MAX)) {
        strcpy(_log_file_, logfile);
        _log_lvl_ = log_lvl;
        //_log_fd_ = open64(_log_file_, O_WRONLY|O_APPEND|O_CREAT|O_TRUNC, 0666);
        _log_fd_ = open64(_log_file_, O_WRONLY | O_APPEND | O_CREAT, 0666);
        if (-1 == _log_fd_) {
            fprintf(stderr, "logger open64 errno:%d", errno);
            return;
        }
        if (stat64(_log_file_, &statbuf) < 0x00)
            fprintf(stderr, "logger stat errno:%d", errno);
        if (MAX_LOG_FILE_SIZ < statbuf.st_size) {
            if (ftruncate64(_log_fd_, 0x00))
                fprintf(stderr, "logger ftruncate errno:%d", errno);
        }
    }
}

//

void log_final() {
    if (-1 != _log_fd_) close(_log_fd_);
}

//
#ifndef _DEBUG

static void chk_log_siz(unsigned long long length) {
    struct stat64 statbuf;
    //  
    if (stat64(_log_file_, &statbuf) < 0x00)
        fprintf(stderr, "logger stat errno:%d", errno);
    if (length < statbuf.st_size) {
        if (ftruncate64(_log_fd_, 0x00))
            fprintf(stderr, "logger ftruncate errno:%d", errno);
    }
}

#endif

static char *LEVEL_TIPS[] = {"[FATAL]", "[ERROR]", "[WARN]", "[INFO]", "[DEBUG]", "[TRACE]", "[MAX]"};
static int TIPS_LEN[] = {0x07, 0x07, 0x06, 0x06, 0x07, 0x07, 0x05};

void log_printf_c(LOG_LVL_T log_lvl, const char *fmt, ...) {
#ifndef _DEBUG
    if (log_lvl > _log_lvl_ || -1 == _log_fd_) return;
    static int check_times;
    if (!POW2N_MOD(++check_times, CHECK_LOGSIZ_FREQUENCY))
        chk_log_siz(MAX_LOG_FILE_SIZ);
#endif
    //
    char buffer[BUFFER_SIZE];
    time_t current_time = time(NULL);
    struct tm current_tm;
    memset(&current_tm, '\0', sizeof (struct tm));
    int prev_len = strftime(buffer, BUFFER_SIZE - 1,
            "[%Y-%m-%d %H:%M:%S]", localtime_r(&current_time, &current_tm));
    strcpy(buffer + prev_len, LEVEL_TIPS[log_lvl]);
    prev_len += TIPS_LEN[log_lvl];
    //
    va_list ap;
    va_start(ap, fmt);
#ifdef _DEBUG
    vsnprintf(buffer + prev_len, BUFFER_SIZE - prev_len - 1, fmt, ap);
#else
    int size = vsnprintf(buffer + prev_len, BUFFER_SIZE - prev_len - 1, fmt, ap) + prev_len;
#endif
    va_end(ap);
    //
#ifdef _DEBUG
    fprintf(stdout, "%s", buffer);
#else

    if (size != write(_log_fd_, buffer, size))
        fprintf(stderr, "can not write to log file!\n%s", buffer);
#endif
}

//

static inline char *lccpy(char * dest_last, const char src) {
    dest_last[0x00] = src;
    (++dest_last)[0x00] = '\0';
    //
    return dest_last;
}

#define LAST_CAT(DEST_LAST, SRC_STR) { \
    char *last_dest = DEST_LAST; \
    last_dest[0x00] = SRC_STR; \
    (++last_dest)[0x00] = '\0'; \
}

void log_printf_cpp(LOG_LVL_T log_lvl, const char *fmt, ...) {
#ifndef _DEBUG
    if (log_lvl > _log_lvl_ || -1 == _log_fd_) return;
    static int check_times;
    if (!POW2N_MOD(++check_times, CHECK_LOGSIZ_FREQUENCY))
        chk_log_siz(MAX_LOG_FILE_SIZ);
#endif
    //
    char buffer[BUFFER_SIZE];
    time_t current_time = time(NULL);
    struct tm current_tm;
    memset(&current_tm, '\0', sizeof (struct tm));
    int prev_len = strftime(buffer, BUFFER_SIZE - 1,
            "[%Y-%m-%d %H:%M:%S]", localtime_r(&current_time, &current_tm));
    strcpy(buffer + prev_len, LEVEL_TIPS[log_lvl]);
    prev_len += TIPS_LEN[log_lvl];
    //
    va_list ap;
    va_start(ap, fmt);
    int size = vsnprintf(buffer + prev_len, BUFFER_SIZE - prev_len - 1, fmt, ap) + prev_len;
    va_end(ap);
    LAST_CAT((buffer + size), '\n');
    //
#ifdef _DEBUG
    fprintf(stdout, "%s", buffer);
#else
    if (size != write(_log_fd_, buffer, size))
        fprintf(stderr, "can not write to log file!\n%s", buffer);
#endif
}

