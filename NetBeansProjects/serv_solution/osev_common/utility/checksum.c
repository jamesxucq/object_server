#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <sys/mman.h>

//
#include "third_party.h"
#include "utility/md5.h"
#include "checksum.h"

//static int sumresidue;
MD5_CTX gmd;

//

int file_chks(unsigned char *sum, char *file_name, unsigned long long offset) {
    memset(sum, '\0', MD5_DIGEST_LEN);
    int fildes = open64(file_name, O_RDONLY);
    if (fildes == -1) {
        // _LOG_ERROR("not open file:%s", file_name);
        return -1;
    }
    struct stat64 statbuf;
    if (fstat64(fildes, &statbuf) < 0)
        return -1;
    //
    dmmap64 *mmap = (dmmap64 *) dmmap_file64(fildes, statbuf.st_size, MAX_MAP_SIZE, CHKS_CHUNK);
    MD5_CTX md;
    // remainder
    unsigned long long remain = statbuf.st_size - offset;
    unsigned long long posi = offset;
    MD5Init(&md);
    if (CHKS_CHUNK < remain) {
        remain = statbuf.st_size - CHKS_CHUNK;
        for (; remain >= posi; posi += CHKS_CHUNK)
            MD5Update(&md, dmmap_ptr64(mmap, posi, CHKS_CHUNK), CHKS_CHUNK);
        remain = statbuf.st_size - posi;
    }
    if (remain > 0x00)
        MD5Update(&md, dmmap_ptr64(mmap, posi, remain), remain);
    MD5Final(&md);
    memcpy(sum, md.digest, MD5_DIGEST_LEN);
    //
    undmmap_file64(mmap);
    close(fildes);
    return 0x00;
}

int file_chks_text(char *chks_str, char *file_name, unsigned long long offset) {
    int fildes = open64(file_name, O_RDONLY);
    if (fildes == -1) {
        // _LOG_ERROR("not open file:%s", file_name);
        return -1;
    }
    struct stat64 statbuf;
    if (fstat64(fildes, &statbuf) < 0)
        return -1;
    //
    dmmap64 *mmap = (dmmap64 *) dmmap_file64(fildes, statbuf.st_size, MAX_MAP_SIZE, CHKS_CHUNK);
    MD5_CTX md;
    // remainder
    unsigned long long remain = statbuf.st_size - offset;
    unsigned long long posi = offset;
    MD5Init(&md);
    if (CHKS_CHUNK < remain) {
        remain = statbuf.st_size - CHKS_CHUNK;
        for (; remain >= posi; posi += CHKS_CHUNK)
            MD5Update(&md, dmmap_ptr64(mmap, posi, CHKS_CHUNK), CHKS_CHUNK);
        remain = statbuf.st_size - posi;
    }
    if (remain > 0x00)
        MD5Update(&md, dmmap_ptr64(mmap, posi, remain), remain);
    MD5Final(&md);
    undmmap_file64(mmap);
    close(fildes);
    //
    unsigned char *digest = md.digest;
    for (posi = 0x00; posi < MD5_DIGEST_LEN; ++posi, ++digest) {
        sprintf(chks_str, "%02x", *digest);
        ++chks_str;
        ++chks_str;
    }
    // chks_str[0x00] = '\0';
    return 0x00;
}

int file_chks64(unsigned char *chks, char *file_name, unsigned long long offset) {
    memset(chks, '\0', MD5_DIGEST_LEN);
    int fildes = open64(file_name, O_RDONLY);
    if (fildes == -1) {
        // _LOG_ERROR("not open file:%s", file_name);
        return -1;
    }
    struct stat64 statbuf;
    if (fstat64(fildes, &statbuf) < 0)
        return -1;
    //
    dmmap64 *mmap = (dmmap64 *) dmmap_file64(fildes, statbuf.st_size, MAX_MAP_SIZE, CHKS_CHUNK);
    MD5_CTX md;
    // remainder
    unsigned long long remain = statbuf.st_size - offset;
    unsigned long long posi = offset;
    MD5Init(&md);
    if (CHKS_CHUNK < remain) {
        remain = statbuf.st_size - CHKS_CHUNK;
        for (; remain >= posi; posi += CHKS_CHUNK)
            MD5Update(&md, dmmap_ptr64(mmap, posi, CHKS_CHUNK), CHKS_CHUNK);
        remain = statbuf.st_size - posi;
    }
    if (remain > 0x00)
        MD5Update(&md, dmmap_ptr64(mmap, posi, remain), remain);
    MD5Final(&md);
    memcpy(chks, md.digest, MD5_DIGEST_LEN);
    //
    undmmap_file64(mmap);
    close(fildes);
    return 0x00;
}




