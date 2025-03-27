
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
#include "access_log.h"

//

#define POW2N_MOD(nua, nub)  (nua & (nub - 0x01)) // x=2^n a=b%x-->a=b&(x-1)
#define BUFFER_SIZE          0x1000  // 4K
#define MAX_LOG_FILE_SIZ         0x80000000  // 128M
#define CHECK_LOGSIZ_FREQUENCY   0x1000  // 4K

static char _log_file_[PATH_MAX];
static int _log_fd_ = -1;

//

void access_initial(char *logfile) {
    struct stat64 statbuf;
    //
    if (logfile) {
        strcpy(_log_file_, logfile);
        //_log_fd_ = open64(_log_file_, O_WRONLY|O_APPEND|O_CREAT|O_TRUNC, 0666);
        _log_fd_ = open64(_log_file_, O_WRONLY | O_APPEND | O_CREAT, 0666);
        if (-1 == _log_fd_) {
            fprintf(stderr, "access_logs open64 errno:%d", errno);
            return;
        }
        if (stat64(_log_file_, &statbuf) < 0x00)
            fprintf(stderr, "access_logs stat errno:%d", errno);
        if (MAX_LOG_FILE_SIZ < statbuf.st_size) {
            if (ftruncate64(_log_fd_, 0x00))
                fprintf(stderr, "access_logs ftruncate errno:%d", errno);
        }
    }
}

//

void access_final() {
    if (-1 != _log_fd_) close(_log_fd_);
}

//

#ifndef _DEBUG

static void chk_log_siz(unsigned long long length) {
    struct stat64 statbuf;
    //  
    if (stat64(_log_file_, &statbuf) < 0x00)
        fprintf(stderr, "access_logs stat errno:%d", errno);
    if (length < statbuf.st_size) {
        if (ftruncate64(_log_fd_, 0x00))
            fprintf(stderr, "access_logs ftruncate errno:%d", errno);
    }
}

#endif

void access_printf(const char *fmt, ...) {
#ifndef _DEBUG
    if (-1 == _log_fd_) return;
    static int check_times;
    if (!POW2N_MOD(++check_times, CHECK_LOGSIZ_FREQUENCY))
        chk_log_siz(MAX_LOG_FILE_SIZ);
#endif
    //
    char buffer[BUFFER_SIZE];
    time_t current_time = time(NULL);
    struct tm current_tm;
    int time_len = 0;
    memset(&current_tm, '\0', sizeof (struct tm));
    time_len = strftime(buffer, BUFFER_SIZE - 1,
            "[%Y-%m-%d %H:%M:%S]", localtime_r(&current_time, &current_tm));
    //
    va_list ap;
    va_start(ap, fmt);
#ifdef _DEBUG
    vsnprintf(buffer + time_len, BUFFER_SIZE - time_len - 1, fmt, ap);
#else
    int size = vsnprintf(buffer + time_len, BUFFER_SIZE - time_len - 1, fmt, ap) + time_len;
#endif
    va_end(ap);
    //
#ifdef _DEBUG
    fprintf(stdout, "%s", buffer);
#else
    int wrilen = write(_log_fd_, buffer, size);
    if (wrilen != size) fprintf(stderr, "can not write to log file!\n%s", buffer);
#endif
}
