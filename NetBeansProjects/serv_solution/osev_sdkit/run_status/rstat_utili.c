#include "commo_header.h"
#include "third_party.h"
#include "kcomm_header.h"

#include "rstat_utili.h"

//

int load_base_rstat(base_rstat *rstat, char *basen) {
    OSEVPF("[FUNC]:load_base_rstat\n");
    char running_stat[MAX_PATH * 3];
    CREAT_TEMPORA_FILE(running_stat, basen, BASE_RUNNING_STAT);
    if (FILE_EXIST(running_stat)) return 0x01;
    //
    int rstat_fd;
    if ((rstat_fd = open64(running_stat, O_RDONLY, 0666)) == -1) {
        close(rstat_fd);
        _LOG_WARN("can not open file %s", running_stat);
        return -1;
    }
    //
    if (sizeof (base_rstat) != read(rstat_fd, rstat, sizeof (base_rstat))) {
        close(rstat_fd);
        _LOG_WARN("read running stat error!");
        return -1;
    }
    //
    close(rstat_fd);
    return 0x00;
}

int open_base_rlev(char *basen, uint32 run_level) {
    OSEVPF("[FUNC]:open_base_rlev\n");
    char running_stat[MAX_PATH * 3];
    CREAT_TEMPORA_FILE(running_stat, basen, BASE_RUNNING_STAT);
    if (!FILE_EXIST(running_stat)) return 0x01;
    //
    int rstat_fd;
    if ((rstat_fd = open64(running_stat, O_WRONLY | O_CREAT, 0666)) == -1) {
        close(rstat_fd);
        _LOG_WARN("can not open file %s", running_stat);
        return -1;
    }
    //
    base_rstat rstatu;
    rstatu.running_level = run_level;
    OSEVPF("run_level:|%08X|\n", run_level);
    if (sizeof (base_rstat) != write(rstat_fd, &rstatu, sizeof (base_rstat))) {
        close(rstat_fd);
        _LOG_WARN("write running stat error!");
        return -1;
    }
    //
    close(rstat_fd);
    return 0x00;
}

int reset_base_rlev(char *basen, uint32 run_level) {
    OSEVPF("[FUNC]:reset_base_rlev\n");
    char running_stat[MAX_PATH * 3];
    CREAT_TEMPORA_FILE(running_stat, basen, BASE_RUNNING_STAT);
    if (FILE_EXIST(running_stat)) return 0x01;
    //
    int rstat_fd;
    if ((rstat_fd = open64(running_stat, O_WRONLY | O_CREAT, 0666)) == -1) {
        close(rstat_fd);
        _LOG_WARN("can not open file %s", running_stat);
        return -1;
    }
    //
    base_rstat rstatu;
    rstatu.running_level = run_level;
    OSEVPF("run_level:|%08X|\n", run_level);
    if (sizeof (base_rstat) != write(rstat_fd, &rstatu, sizeof (base_rstat))) {
        close(rstat_fd);
        _LOG_WARN("write running stat error!");
        return -1;
    }
    //
    close(rstat_fd);
    return 0x00;
}

//
// 0x00: exists 0x01:opened 0x02: not exists

int check_base_exist(char *basen) {
    OSEVPF("[FUNC]:check_base_exist\n");
    char base_path[MAX_PATH * 3];
    CREAT_BASE_DIRECTORY(base_path, basen);
    if (FILE_EXIST(base_path)) return 0x02;
    //
    CREAT_TEMPORA_FILE(base_path, basen, BASE_RUNNING_STAT);
    if (!FILE_EXIST(base_path)) return 0x01;
    //
    return 0x00;
}

int close_base_rlev(char *basen) {
    OSEVPF("[FUNC]:close_base_rlev\n");
    char running_stat[MAX_PATH * 3];
    CREAT_TEMPORA_FILE(running_stat, basen, BASE_RUNNING_STAT);
    if (FILE_EXIST(running_stat)) return 0x01;
    //
    if (unlink(running_stat)) {
        _LOG_WARN("unlink file error! errno:%d path:%s", errno, running_stat);
        return -1;
    }
    //
    return 0x00;
}

//

int valid_base_opened(char *basen) {
    OSEVPF("[FUNC]:valid_base_opened\n");
    char running_stat[MAX_PATH * 3];
    CREAT_TEMPORA_FILE(running_stat, basen, BASE_RUNNING_STAT);
    if (FILE_EXIST(running_stat)) return -1;
    //
    return 0x00;
}

//

int enab_authen_flag() {
    OSEVPF("[FUNC]:enab_authen_flag\n");
    char authen_stat[MAX_PATH * 3];
    CREAT_TEMPORA_FILE(authen_stat, OSEV_DATA_PATH, OSEV_AUTHEN_STAT);
    if (!FILE_EXIST(authen_stat)) return 0x01;
    //
    int astat_fd;
    if ((astat_fd = open64(authen_stat, O_WRONLY | O_CREAT, 0666)) == -1) {
        close(astat_fd);
        _LOG_WARN("can not open file %s", authen_stat);
        return -1;
    }
    close(astat_fd);
    //
    return 0x00;
}

// 0x00: normal 0x01:opened 0x02: not exists

int disab_authen_flag() {
    OSEVPF("[FUNC]:disab_authen_flag\n");
    char authen_stat[MAX_PATH * 3];
    CREAT_TEMPORA_FILE(authen_stat, OSEV_DATA_PATH, OSEV_AUTHEN_STAT);
    if (FILE_EXIST(authen_stat)) return 0x01;
    //
    if (unlink(authen_stat)) {
        _LOG_WARN("unlink file error! errno:%d path:%s", errno, authen_stat);
        return -1;
    }
    //
    return 0x00;
}

int valid_authen_enab() {
    OSEVPF("[FUNC]:valid_authen_enab\n");
    char authen_stat[MAX_PATH * 3];
    CREAT_TEMPORA_FILE(authen_stat, OSEV_DATA_PATH, OSEV_AUTHEN_STAT);
    if (FILE_EXIST(authen_stat)) return -1;
    //
    return 0x00;
}
