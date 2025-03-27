#ifndef TINY_MMAP_H_
#define TINY_MMAP_H_

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

    struct _tiny_mmap_ {
        off_t mmap_size; /* File size (from stat) */
        off_t p_offset; /* Window start */
        off_t p_fd_offset; /* offset of cursor in fildes ala lseek */
        unsigned char *conptr; /* Window pointer */
        unsigned int p_size; /* Largest wind size we allocated */
        unsigned int p_len; /* Latest (rounded) wind size */
        unsigned int def_wind_size; /* Default wind size */
        int fildes; /* File Descriptor */
        int status; /* first errno from read errors	*/
    };

    typedef struct _tiny_mmap_ tiny_mmap;

    //
    tiny_mmap *mmap_file(int fildes, off_t mmap_size, unsigned int read_size, unsigned int blk_size);
    unsigned char *mmap_ptr(tiny_mmap *mmap, off_t offset, unsigned int msize);
    int unmmap_file(tiny_mmap *mmap);

#define MAX_MAP_SIZE    0x80000 // 512K

#ifdef __cplusplus
}
#endif

#endif /* TINY_MMAP_H_ */

