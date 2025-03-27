#ifndef FILE_UTILI_H_
#define FILE_UTILI_H_

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
#include <utime.h>
#include <dirent.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/times.h>

#include "utility/last_stri.h"
#include "commo_macro.h"
#include "osev_datyp.h"
#include "logger.h"
#include "osev_macro.h"
#include "stri_utili.h"

    //

#define FILE_SIZE(SIZE, PATH) { \
    struct stat64 statbuf; \
    if (stat64(PATH, &statbuf) < 0x00) \
        _LOG_WARN("stat errno:%d", errno); \
    SIZE = statbuf.st_size; \
}

    // off_t file_size_descrip(int fildes);
#define FILE_SIZE_DESCRIP(SIZE, FILDES) { \
    struct stat64 statbuf; \
    if (fstat64(FILDES, &statbuf) < 0x00) \
        _LOG_WARN("fstat errno:%d", errno); \
    SIZE = statbuf.st_size; \
}
    //off_t file_size_stre(FILE *strem);
#define FILE_SIZE_STREAM(SIZE, STREAM) { \
    if (fseeko64(STREAM, 0x00, SEEK_END)) \
        _LOG_WARN("fseeko64 errno:%d", errno); \
    SIZE = ftello64(STREAM); \
}
    // rewind(STREAM);
#define FILE_SIZE_STREAM_EXT(SIZE, CHKS, STREAM) { \
    if (fseeko64(STREAM, 0x00, SEEK_END)) \
        _LOG_WARN("fseeko64 errno:%d", errno); \
    SIZE = ftello64(STREAM); \
    chks_text_stre(CHKS, STREAM, SIZE); \
}

    /*Get file_name from file_path*/
    // char *file_get_name(const char *file_path);
#define FILE_GET_NAME(FILE_NAME, FILE_PATH) { \
    char path[PATH_MAX]; \
    strcpy(path, FILE_PATH); \
    strcpy(FILE_NAME, basename(path)); \
}
    /* Get directory suffix from file_path */
    // char *file_get_dir(char *filedir, const char *file_path);
#define FILE_GET_DIRE(FILE_DIRE, FILE_PATH) { \
    char path[PATH_MAX]; \
    strcpy(path, FILE_PATH); \
    strcpy(FILE_DIRE, dirname(path)); \
}

    //
    // int file_time(time_t *last_write, char *name);
#define FILE_TIME(LAST_WRITE, NAME) { \
    struct stat64 statbuf; \
    if (stat64(NAME, &statbuf) < 0x00) \
        _LOG_WARN("stat errno:%d", errno); \
    LAST_WRITE = statbuf.st_mtime; \
}
    // int file_time_stre(time_t *last_write, FILE *strem);
#define FILE_TIME_STREAM(LAST_WRITE, STREAM) { \
    int fildes; \
    struct stat64 statbuf; \
    if ((fildes = fileno(STREAM)) == -1) \
        _LOG_WARN("fileno errno:%d", errno); \
    if (fstat64(fildes, &statbuf) < 0x00) \
        _LOG_WARN("fstat errno:%d", errno); \
    LAST_WRITE = statbuf.st_mtime; \
}
    // int file_size_time(size_t *file_size, time_t *last_write, char *name);
#define FILE_SIZE_TIME(FILE_SIZE, LAST_WRITE, NAME) { \
    struct stat64 statbuf; \
    if (stat64(NAME, &statbuf) < 0x00) \
        _LOG_WARN("stat errno:%d", errno); \
    FILE_SIZE = statbuf.st_size; \
    LAST_WRITE = statbuf.st_mtime; \
}
    // int file_size_time_stre(size_t *file_size, time_t *last_write, FILE *strem);
#define FILE_SIZE_TIME_STREAM(FILE_SIZE, LAST_WRITE, STREAM) { \
    int fildes; \
    struct stat64 statbuf; \
    if ((fildes = fileno(STREAM)) == -1) \
        _LOG_WARN("fileno errno:%d", errno); \
    if (fstat64(fildes, &statbuf) < 0x00) \
        _LOG_WARN("fstat errno:%d", errno); \
    FILE_SIZE = statbuf.st_size; \
    LAST_WRITE = statbuf.st_mtime; \
}
    //
    /* Determine if two time_t values are equivalent*/
    FILE *creat_bakup_file(FILE *local_stre, uint64 offset);
    FILE *creat_bakup_chunk(FILE *local_stre, uint64 offset);

    //
#define SET_FILE_MODTIME(FILE_NAME, MODTIME) { \
    struct utimbuf utb; \
    memset(&utb, '\0', sizeof (struct utimbuf)); \
    utb.modtime = MODTIME; \
    if (utime(FILE_NAME, &utb)) \
        _LOG_WARN("utime errno:%d", errno); \
/* OSEVPF("path:|%s| mtim:|%s|\n", FILE_NAME, utc_time_text(MODTIME)); */ \
}

    //
    // int directory_exist(char *dirpath);
#define DIRECTORY_EXISTS(DIRPATH) \
    struct stat64 statbuf; \
    statbuf.st_mode = 0x00; \
    lstat64(DIRPATH, &statbuf); \
    // S_ISDIR(statbuf.st_mode);

    // 0x00:ok -1:error
#define FILE_EXIST(PATH_NAME)   access(PATH_NAME, F_OK)
#define CLASS_EXIST(PATH_NAME)  access(PATH_NAME, F_OK)
#define OBJECT_EXIST(PATH_NAME) access(PATH_NAME, F_OK)

    //int is_directory(char *path);
#define IS_DIRECTORY(PATH) \
    struct stat64 statbuf; \
    if (lstat64(PATH, &statbuf) < 0x00) \
        _LOG_WARN("lstat errno:%d", errno); \
    // S_ISDIR(statbuf.st_mode);

    //
#define CREAT_BAKUP_DIRPATH(BAKUP_PATH, MODE) { \
    char filedir[PATH_MAX]; \
    FILE_GET_DIRE(filedir, BAKUP_PATH) \
    if (mkdir(filedir, MODE)) \
        _LOG_WARN("mkdir errno:%d", errno); \
    _LOG_WARN("mkdir bakup path:|%s|", filedir); \
}

    //
#define CREAT_FILE_DIRPATH(LOCATION, FILE_NAME, MODE) { \
    char filedir[PATH_MAX]; \
    FILE_GET_DIRE(filedir, FILE_NAME) \
    char *dirpath = next_dirpath(LOCATION, filedir); \
    while (dirpath) { \
        DIRECTORY_EXISTS(dirpath) \
        if (TRUE != S_ISDIR(statbuf.st_mode)) { \
            if (mkdir(dirpath, MODE)) \
                _LOG_WARN("mkdir errno:%d", errno); \
            _LOG_WARN("mkdir:|%s|", dirpath); \
        } \
        dirpath = next_dirpath(LOCATION, NULL); \
    } \
}
    /*Attempts to create a directory recursively.*/
    int recu_mkdir(const char *dirpath, mode_t mode);

    //
    int recu_rmdir(char *dirpath);
    // creat the new to file
    int file_copy_create(char *from, char *to);
#define file_copy(from, to) file_copy_create(from, to)
    // append
    int file_copy_append(char *from, char *to);
    // truncate
    int file_copy_trunca(char *from, char *to);
    // 
    int recu_dires_copy(char *dire_from, char *dire_to);

    //
    char *get_appli_path();
#define CREAT_CONF_PATH(PATH_NAME, FILE_NAME) \
    sprintf(PATH_NAME, "%s/conf/%s", get_appli_path(), FILE_NAME);
#define CREAT_LOGS_PATH(PATH_NAME, FILE_NAME) \
    sprintf(PATH_NAME, "%s/logs/%s", get_appli_path(), FILE_NAME);
#define CREAT_DATA_PATH(PATH_NAME) \
    sprintf(PATH_NAME, "%s/data", get_appli_path());

    //
    char *load_data(char *data_cont, int cont_size, char *file_name);
    char *bina_load_data(char *data_cont, int cont_size, char *file_name, uint64 posit);

    // trans-serve
#define TRUNCA_FILE 0x00
#define FILE_APPEND 0x01
    int save_data(char *file_name, char *data_cont, int mode);
    int bina_save_data(char *file_name, char *data_cont, int cont_size, int mode);

    //
#define GetTickCount time(NULL);

    //
#define APPEND_DATAD(DATFD, DATA, SIZE) write(DATFD, DATA, SIZE)
#define APPEND_DATAS(RSFIL, DATA, SIZE) fwrite(DATA, SIZE, 0x01, RSFIL)


#ifdef __cplusplus
}
#endif

#endif /* FILE_UTILI_H_ */
