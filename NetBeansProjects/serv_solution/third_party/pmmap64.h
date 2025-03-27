/* 
 * File:   pmmap64.h
 * Author: James Xu
 */

#ifndef POIN_MAP64_H
#define POIN_MAP64_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>

    struct _pmmap64_ {
        unsigned long long mmap_size; /* File size (from stat) */
        unsigned long long p_offset; /* Window start */
        unsigned long long p_fd_offset; /* offset of cursor in fd ala lseek */
        unsigned char *conptr; /* Window pointer */
        unsigned int p_size; /* Largest wind size we allocated */
        unsigned int p_len; /* Latest (rounded) wind size */
        unsigned int def_wind_size; /* Default wind size */
        FILE *filptr; /* File Descriptor */
        int status; /* first errno from read errors	*/
    };

    typedef struct _pmmap64_ pmmap64;

    //  
    pmmap64 *pmmap_file64(FILE *filptr, unsigned long long mmap_size, unsigned int read_size, unsigned int blk_size);
    unsigned char *pmmap_ptr64(pmmap64 *mmap, unsigned long long offset, unsigned int msize);
    int unpmmap_file64(pmmap64 *mmap);

#define MAX_MAP_SIZE    0x80000 // 512K

#ifdef __cplusplus
}
#endif

#endif /* POIN_MAP64_H */

