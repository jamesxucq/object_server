
/* 
 * File:   rstat_utili.h
 * Author: James Xu
 *
 * Created on 2017.1.8, AM 10:14
 */

#ifndef RSTAT_UTILI_H
#define RSTAT_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#define BASE_RUNNING_STAT   "base_running.sta"

#define OSEV_DATA_PATH  "osev"
#define OSEV_AUTHEN_STAT   "osev_authen.sta"

    //

    struct _base_rstat_ {
        uint32 running_level;
    };

    typedef struct _base_rstat_ base_rstat;

    int load_base_rstat(base_rstat *rstatu, char *basen);

    //
    int open_base_rlev(char *basen, uint32 run_level);
    int reset_base_rlev(char *basen, uint32 run_level);
    int close_base_rlev(char *basen);

    //
    // 0x00: exists 0x01:opened 0x02: not exists
#define BASE_EXISTS 0x00
#define BASE_OPENED 0x01
#define BASE_NOEXIS 0x02
    int check_base_exist(char *basen);

    //
    int valid_base_opened(char *basen);

    //
    int enab_authen_flag();
    int disab_authen_flag();
    int valid_authen_enab();

    //

#ifdef __cplusplus
}
#endif

#endif /* RSTAT_UTILI_H */

