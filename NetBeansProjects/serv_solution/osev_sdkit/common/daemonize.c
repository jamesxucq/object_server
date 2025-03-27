#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <signal.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

//

int daemonize(const char *command) {
    int fd;
    struct sigaction sa;
    /* Clear file creation mask. */
    umask(0);
    switch (fork()) {
        case -1:
            fprintf(stderr, "fork() failed, %s.\n", command);
            return -1;
        case 0:
            break;
        default:
            exit(0);
    }
    //
    if (setsid() == -1) {
        fprintf(stderr, "setsid() failed");
        return -1;
    }
    /* Ensure future opens won't allocate controlling TTYs. */
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0) fprintf(stderr, "can't ignore SIGHUP\n");
    /* Change the current working directory to the root so
     * we won't prevent file systems from being unmounted. */
    if (chdir("/") < 0) fprintf(stderr, "can't change directory to /\n");
    /* Attach file descriptors 0, 1, and 2 to /dev/null. */
    fd = open("/dev/null", O_RDWR);
    if (fd == -1) {
        syslog(LOG_ERR, "open(\"/dev/null\") failed");
        return -1;
    }
    if (dup2(fd, STDIN_FILENO) == -1) {
        syslog(LOG_ERR, "dup2(STDIN) failed");
        return -1;
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        syslog(LOG_ERR, "dup2(STDOUT) failed");
        return -1;
    }
    if (dup2(fd, STDERR_FILENO) == -1) {
        syslog(LOG_ERR, "dup2(STDERR) failed");
        return -1;
    }
    if (fd > STDERR_FILENO) {
        if (close(fd) == -1) {
            syslog(LOG_ERR, "close() failed");
            return -1;
        }
    }
    //
    syslog(LOG_DEBUG, "Daemon OK!");
    return 0x00;
}

/*
 short daemonize(const char *cmd, short bind_port[], unsigned int port_tatol) {
    int inde, fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;
    short alloc_port;
 * Clear file creation mask. *
    umask(0);
 * Get maximum number of file descriptors. *
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) fprintf(stderr, "%s: can't get file limit\n", cmd);
 * Become a session leader to lose controlling TTY. *
    if ((pid = fork()) < 0) fprintf(stderr, "%s: can't fork\n", cmd);
    else if (0 != pid) exit(0); * parent *

    setsid();

 * Ensure future opens won't allocate controlling TTYs. *
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0) fprintf(stderr, "can't ignore SIGHUP\n");

    inde = 0x00;
    for (;; ++inde) {
        if ((pid = fork()) < 0) fprintf(stderr, "%s: can't fork\n", cmd);
        else if (0 != pid) {* parent *
            if ((port_tatol - 1) == inde) exit(0);
        } else { * child *
            alloc_port = bind_port[inde];
            fprintf(stderr, "alloc port:%d inde:%d\n", alloc_port, inde);
            break;
        }
    }

 * Change the current working directory to the root so
 * we won't prevent file systems from being unmounted. *
    if (chdir("/") < 0) fprintf(stderr, "can't change directory to /\n");

 * Close all open file descriptors. *
    if (rl.rlim_max == RLIM_INFINITY) rl.rlim_max = 1024;
    inde = 0x00;
    for (; inde < rl.rlim_max; ++inde) close(inde);

 * Attach file descriptors 0, 1, and 2 to /dev/null. *
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

 * Initialize the log file. *
    // openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (0 != fd0 || 1 != fd1 || 2 != fd2) {
        syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
        exit(1);
    }
    syslog(LOG_DEBUG, "daem ok");
    //
    return alloc_port;
}
 */