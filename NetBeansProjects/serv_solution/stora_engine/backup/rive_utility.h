/* 
 * File:   rive_utility.h
 * Author: Administrator
 */

#ifndef RIVE_UTILITY_H
#define RIVE_UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>

//

#include "riv_common.h"

//
#ifdef __cplusplus
extern "C" {
#endif

    //
    uint32 fill_idle_iden(FILE *fpiden, int32 line_size);
    //
    uint64 find_idle_iden(FILE *fpiden);
    uint32 add_idle_iden(FILE *fpiden, uint64 ainde);
//    uint64 iden_read(struct file_id *pattb, FILE *fpiden, uint64 ainde);
//    uint64 iden_write(FILE *fpiden, struct file_id *pattb, uint64 ainde);
    uint64 iden_sibli_modify(FILE *fpiden, uint64 ainde, uint64 sibling);
    uint64 iden_file_modify(FILE *fpiden, uint64 ainde, char *new_name);
    //
//    uint64 find_sibli_chks(FILE *fpchks, uint64 cinde);
//    uint64 find_idle_chks(FILE *fpchks);
//    uint32 add_idle_chks(FILE *fpchks, uint64 chks_hind);
//    uint64 chks_read(struct ckchks *pcks, FILE *fpchks, uint64 cinde);
//    uint64 chks_write(FILE *fpchks, struct ckchks *pcks, uint64 cinde);
//    uint64 chks_sibli_modify(FILE *fpchks, uint64 cinde, uint64 sibling);
//    uint64 chks_stamp_modify(FILE *fpchks, time_t stamp, uint64 cinde);
//    //
//    void chunk_chks(unsigned char *pchks, FILE *fpchks, uint64 file_size, uint64 cinde);

    
    //
#ifdef __cplusplus
}
#endif

#endif /* RIVE_UTILITY_H */

