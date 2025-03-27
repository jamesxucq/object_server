
#include "memory_utility.h"
// #include "jemalloc/jemalloc.h"
#include "tiny_mmap.h"

/* This provides functionality somewhat similar to mmap() but using read().
 * It gives sliding wind access to a file.  mmap() is not used because of
 * the possibility of another program (such as a mailer) truncating the
 * file thus giving us a SIGBUS. */
tiny_mmap *mmap_file(int fildes, off_t mmap_size, unsigned int read_size, unsigned int blk_size) {
    tiny_mmap *mmap;
    //
    if (!(mmap = malloc(sizeof (tiny_mmap)))) {
        fprintf(stderr, "mmap file malloc error");
        return NULL;
    }
    memset(mmap, '\0', sizeof (tiny_mmap));
    //
    if (blk_size && (read_size % blk_size))
        read_size += blk_size - (read_size % blk_size);
    //
    mmap->fildes = fildes;
    mmap->mmap_size = mmap_size;
    mmap->def_wind_size = read_size;
    //
    return mmap;
}

/* slide the read wind in the file */
unsigned char *mmap_ptr(tiny_mmap *mmap, off_t offset, unsigned int msize) {
    unsigned int realen;
    off_t wind_start, read_start;
    unsigned int wind_size, read_size, read_offset;
    //
    if (msize <= 0) {
        fprintf(stderr, "invalid msize passed to mmap_ptr: %ld", (long) msize);
        return NULL;
    }
    //
    /* in most cases the region will already be available */
    if (offset >= mmap->p_offset && offset + msize <= mmap->p_offset + mmap->p_len)
        return mmap->conptr + (offset - mmap->p_offset);
    //
    /* nope, we are going to have to do a read. Work out our desired wind */
    wind_start = offset;
    wind_size = mmap->def_wind_size;
    if (wind_start + wind_size > mmap->mmap_size)
        wind_size = (unsigned int) (mmap->mmap_size - wind_start);
    if (msize > wind_size) wind_size = msize;
    //
    /* make sure we have allocated enough memory for the wind */
    if (wind_size > mmap->p_size) {
        mmap->conptr = realloc_array(mmap->conptr, sizeof (char), wind_size);
        if (!mmap->conptr) {
            fprintf(stderr, "mmap_ptr newc error");
        }
        mmap->p_size = wind_size;
    }
    //
    /* Now try to avoid re-reading any bytes by reusing any bytes
     * from the previous buffer. */
    if (wind_start >= mmap->p_offset &&
            wind_start < mmap->p_offset + mmap->p_len &&
            wind_start + wind_size >= mmap->p_offset + mmap->p_len) {
        read_start = mmap->p_offset + mmap->p_len;
        read_offset = (unsigned int) (read_start - wind_start);
        read_size = wind_size - read_offset;
        memmove(mmap->conptr, mmap->conptr + (mmap->p_len - read_offset), read_offset);
    } else {
        read_start = wind_start;
        read_size = wind_size;
        read_offset = 0;
    }
    //
    if (read_size <= 0) {
        fprintf(stderr, "invalid read_size of %ld in mmap_ptr", (long) read_size);
        return NULL;
    }
    //
    if (mmap->p_fd_offset != read_start) {
        if (-1 == lseek64(mmap->fildes, read_start, SEEK_SET)) {
            fprintf(stderr, "lseek returned error!");
            return NULL;
        }
        mmap->p_fd_offset = read_start;
    }
    mmap->p_offset = wind_start;
    mmap->p_len = wind_size;
    //
    while (read_size > 0) {
        realen = read(mmap->fildes, mmap->conptr + read_offset, read_size);
        if (realen <= 0) {
            if (!mmap->status) mmap->status = realen ? errno : ENODATA;
            /* The best we can do is zero the buffer -- the file has changed mid transfer! */
            memset(mmap->conptr + read_offset, '\0', read_size);
            break;
        }
        mmap->p_fd_offset += realen;
        read_offset += realen;
        read_size -= realen;
    }
    //
    return mmap->conptr;
}

int unmmap_file(tiny_mmap *mmap) {
    if (mmap->conptr) free(mmap->conptr);
    int retvu = mmap->status;
    free(mmap);
    return retvu;
}
