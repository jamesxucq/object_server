
#include "file_utili.h"
#include "debug_funct_osv.h"

int recu_mkdir(const char *dirpath, mode_t mode) {
    char parent[PATH_MAX];
    if (!mkdir(dirpath, mode))
        return 0x00;
    if (ENOENT == errno) {
        FILE_GET_DIRE(parent, dirpath)
        if (recu_mkdir(parent, mode) || mkdir(dirpath, mode))
            return -1;
    }
    return 0x00;
}

//
#define BUFF_SIZE                        0x2000
#define BAKUP_CHUNK_SIZE  ((int)1 << 22) // 4M

FILE *creat_bakup_file(FILE *local_stre, uint64 offset) {
    unsigned char buffer[BUFF_SIZE];
    FILE *bakup_stram = NULL;
    int realen, wrilen;
    //
    if (!(bakup_stram = tmpfile64()))
        return NULL;
    if (fseeko64(local_stre, offset, SEEK_SET))
        return NULL;
    rewind(bakup_stram);
    //
    do {
        realen = fread(buffer, 0x01, BUFF_SIZE, local_stre);
        if (0 >= realen) continue;
        //
        if (0 >= (wrilen = fwrite(buffer, 0x01, realen, bakup_stram))) continue;
        if (wrilen != realen) return NULL;
    } while (0 < realen && 0 < wrilen);
    //
    return bakup_stram;
}

FILE *creat_bakup_chunk(FILE *local_stre, uint64 offset) {
    unsigned char buffer[BUFF_SIZE];
    FILE *bakup_stram = NULL;
    int realen, wrilen;
    //
    if (!(bakup_stram = tmpfile64()))
        return NULL;
    if (fseeko64(local_stre, offset, SEEK_SET))
        return NULL;
    rewind(bakup_stram);
    //
    size_t bakup_tatol = 0;
    do {
        realen = fread(buffer, 0x01, BUFF_SIZE, local_stre);
        if (0 >= realen) continue;
        //
        if (0 >= (wrilen = fwrite(buffer, 0x01, realen, bakup_stram))) continue;
        if (wrilen != realen) return NULL;
        bakup_tatol += wrilen;
        if (BAKUP_CHUNK_SIZE == bakup_tatol) break;
    } while (0 < realen && 0 < wrilen);
    //
    return bakup_stram;
}

// xfs not have, ext4 have it.
// #define  HAVE_DIRENT_DTYPE    0x01
// #ifdef HAVE_DIRENT_DTYPE

/*
int recu_rmdir(char *dirpath) {
    DIR *dires;
    struct dirent *entry;
    char full_path[MAX_PATH * 3];
    //
    if (!(dires = opendir(dirpath)))  {
        _LOG_WARN("can not open dir %s", dirpath);
        return -1;
    }
    sprintf(full_path, "%s/", dirpath);
    char *last_path = (char *) strend(full_path);
    while (NULL != (entry = readdir(dires))) {
        if (DT_UNKNOWN == entry->d_type || DT_REG == entry->d_type) {
            strcpy((char *) last_path, entry->d_name);
            OSEVPF("unlink file:|%s|\n", full_path);
            if (unlink(full_path)) {
                closedir(dires);
                return -1;
            }
        } else if (DT_DIR == entry->d_type) {
            if (!strcmp(".", entry->d_name) || !strcmp("..", entry->d_name))
                continue;
            strcpy((char *) last_path, entry->d_name);
            if (recu_rmdir(full_path)) {
                closedir(dires);
                return -1;
            }
        }
    }
    closedir(dires);
    if (rmdir(dirpath) < 0) return -1;
    OSEVPF("rmdir dire:|%s|\n", dirpath);
    //
    return 0x00;
}
 */

int recu_rmdir(char *dirpath) {
    DIR *dires;
    struct dirent *entry;
    struct stat64 statbuf;
    char full_path[MAX_PATH * 3];
    //
    if (!(dires = opendir(dirpath))) {
        _LOG_WARN("can not open dir %s", dirpath);
        return -1;
    }
    sprintf(full_path, "%s/", dirpath);
    char *last_path = (char *) strend(full_path);
    while (NULL != (entry = readdir(dires))) {
        strcpy(last_path, entry->d_name);
        if (stat64(full_path, &statbuf) < 0) {
            closedir(dires);
            _LOG_WARN("stat errno:%d", errno);
            return -1;
        }
        if (S_ISLNK(statbuf.st_mode) || S_ISREG(statbuf.st_mode)) {
            if (unlink(full_path)) {
                closedir(dires);
                return -1;
            }
        } else if (S_ISDIR(statbuf.st_mode)) {
            if (!strcmp(".", entry->d_name) || !strcmp("..", entry->d_name))
                continue;
            if (recu_rmdir(full_path)) {
                closedir(dires);
                return -1;
            }
        }
    }
    closedir(dires);
    if (rmdir(dirpath) < 0) return -1;
    //
    return 0x00;
}

// creat the new to file

int file_copy_create(char *from, char *to) {
    int fd1, fd2;
    struct stat64 statbuf;
    if (stat64(from, &statbuf) == -1) {
        _LOG_WARN("can not get info of %s", from);
        return -1;
    }
    if ((fd1 = open64(from, O_RDONLY)) == -1) {
        _LOG_WARN("can not open file %s", from);
        return -1;
    }
    if ((fd2 = creat64(to, statbuf.st_mode)) == -1) {
        _LOG_WARN("can not open file %s", to);
        return -1;
    }
    //
    int size;
    unsigned char buffer[0x1000] = ""; //4K
    while (0 != (size = read(fd1, buffer, 0x1000))) {
        if (write(fd2, buffer, size) != size)
            _LOG_WARN("write error!");
    }
    //
    close(fd1);
    close(fd2);
    return 0x00;
}

#define MAX_COPY_SIZ  0x20000 // 1GB
// #define MAX_COPY_SIZ  1024 // 8MB
// append

int file_copy_append(char *from, char *to) { // 0:ok 1:processing -1:error
    struct stat64 statbuf1, statbuf2;
    if (stat64(from, &statbuf1) == -1) {
        _LOG_WARN("can not get info of %s", from);
        return -1;
    }
    if (stat64(to, &statbuf2) == -1)
        statbuf2.st_size = 0;
    //
    int fd1, fd2;
    if ((fd1 = open64(from, O_RDONLY)) == -1) {
        _LOG_WARN("can not open file %s", from);
        return -1;
    }
    if ((fd2 = open64(to, O_WRONLY | O_CREAT | O_APPEND, statbuf1.st_mode)) == -1) {
        close(fd1);
        _LOG_WARN("can not open file %s", to);
        return -1;
    }
    //
    lseek64(fd2, 0x00, SEEK_END);
    int size;
    unsigned char buffer[0x2000] = ""; //8K
    while (0 != (size = read(fd1, buffer, 0x2000))) {
        if (write(fd2, buffer, size) != size)
            _LOG_WARN("write error!");
    }
    //
    close(fd1);
    close(fd2);
    return 0x00;
}

int file_copy_trunca(char *from, char *to) { // 0:ok 1:processing -1:error
    struct stat64 statbuf1, statbuf2;
    if (stat64(from, &statbuf1) == -1) {
        _LOG_WARN("can not get info of %s", from);
        return -1;
    }
    if (stat64(to, &statbuf2) == -1)
        statbuf2.st_size = 0;
    //
    int fd1, fd2;
    if ((fd1 = open64(from, O_RDONLY)) == -1) {
        _LOG_WARN("can not open file %s", from);
        return -1;
    }
    if ((fd2 = open64(to, O_WRONLY | O_CREAT | O_TRUNC, statbuf1.st_mode)) == -1) {
        close(fd1);
        _LOG_WARN("can not open file %s", to);
        return -1;
    }
    //
    int size;
    unsigned char buffer[0x2000] = ""; //8K
    while (0 != (size = read(fd1, buffer, 0x2000))) {
        if (write(fd2, buffer, size) != size)
            _LOG_WARN("write error!");
    }
    //
    close(fd1);
    close(fd2);
    return 0x00;
}

static void copy_regular_file(char from[], char to[]) {
    struct stat64 statbuf;
    if (stat64(from, &statbuf) == -1) {
        _LOG_WARN("can not get info of %s", from);
        return;
    }
    int fd1, fd2;
    if ((fd1 = open64(from, O_RDONLY)) == -1) {
        _LOG_WARN("can not open file %s", from);
        return;
    }
    if ((fd2 = creat64(to, statbuf.st_mode)) == -1) {
        _LOG_WARN("can not open file %s", to);
        return;
    }
    //
    unsigned char buffer[0x1000] = "";
    int size;
    while (0 != (size = read(fd1, buffer, 0x1000))) {
        if (write(fd2, buffer, size) != size) {
            _LOG_WARN("write error!");
        }
    }
    close(fd1);
    close(fd2);
}

int recu_dires_copy(char *dire_from, char *dire_to) {
    char path1[MAX_PATH * 3] = "";
    char path2[MAX_PATH * 3] = "";
    DIR *dires = NULL;
    struct dirent *entry;
    struct stat64 statbuf;
    //
    if (stat64(dire_from, &statbuf) != -1) {
        if (S_ISDIR(statbuf.st_mode)) {
            if (mkdir(dire_to, 0777) == -1) {
                _LOG_WARN("can not creat dir %s", dire_to);
                return -1;
            }
            if (!(dires = opendir(dire_from))) {
                _LOG_WARN("can not open dir %s", dire_from);
                return -1;
            }
            while (NULL != (entry = readdir(dires))) {
                if (0 == strcmp(entry->d_name, ".") || 0 == strcmp(entry->d_name, ".."))
                    continue;
                sprintf(path1, "%s/%s", dire_from, entry->d_name);
                sprintf(path2, "%s/%s", dire_to, entry->d_name);
                recu_dires_copy(path1, path2); //
            }
        } else copy_regular_file(dire_from, dire_to);
    }
    closedir(dires);
    //
    return 0x00;
}

//

char *get_executable_path(char* epath) {
    char exec_path[PATH_MAX];
    int len = readlink("/proc/self/exe", exec_path, PATH_MAX);
    if (0 > len) return NULL;
    exec_path[len] = '\0';
    //
    strcpy(epath, exec_path);
    return epath;
}

char *get_appli_path() {
    static char appli_path[1024];
    if ('\0' == appli_path[0x00]) {
        if (!get_executable_path(appli_path))
            return NULL;
        char *tokep = strrchr(appli_path, '/');
        if (!tokep) return NULL;
        tokep[0x00] = '\0';
        tokep = strrchr(appli_path, '/');
        if (!tokep) return NULL;
        (tokep)[0x00] = '\0';
    }
    return appli_path;
}

//

char *load_data(char *data_cont, int cont_size, char *file_name) {
    struct stat64 statbuf;
    if (stat64(file_name, &statbuf) < 0) {
        OSEVPF("file_name:|%s|\n", file_name);
        _LOG_WARN("stat errno:%d", errno);
        return NULL;
    }
    if (cont_size < (statbuf.st_size + 0x01))
        return NULL;
    //
    FILE *data_fp = fopen64(file_name, "rb+");
    if (!data_fp) {
        _LOG_ERROR("open file error! %s", file_name);
        return NULL;
    }
    if (fseeko64(data_fp, 0x00, SEEK_SET)) {
        fclose(data_fp);
        _LOG_ERROR("seek file error! %s", file_name);
        return NULL;
    }
    if (0x00 >= fread(data_cont, 0x01, statbuf.st_size, data_fp)) {
        fclose(data_fp);
        _LOG_ERROR("read file error! %s", file_name);
        return NULL;
    }
    data_cont[statbuf.st_size] = '\0';
    fclose(data_fp);
    //
    return data_cont;
}

char *bina_load_data(char *data_cont, int cont_size, char *file_name, uint64 posit) {
    struct stat64 statbuf;
    if (stat64(file_name, &statbuf) < 0) {
        OSEVPF("file_name:|%s|\n", file_name);
        _LOG_WARN("stat errno:%d", errno);
        return NULL;
    }
    if (cont_size > statbuf.st_size)
        return NULL;
    //
    FILE *data_fp = fopen64(file_name, "rb+");
    if (!data_fp) {
        _LOG_ERROR("open file error! %s", file_name);
        return NULL;
    }
    if (fseeko64(data_fp, posit, SEEK_SET)) {
        fclose(data_fp);
        _LOG_ERROR("seek file error! %s", file_name);
        return NULL;
    }
    if (0x00 >= fread(data_cont, 0x01, cont_size, data_fp)) {
        fclose(data_fp);
        _LOG_ERROR("read file error! %s", file_name);
        return NULL;
    }
    fclose(data_fp);
    //
    return data_cont;
}

//

int save_data(char *file_name, char *data_cont, int mode) {
    static char *mode_flag[0x02] = {"wb+", "ab+"};
    int cont_size = strlen(data_cont);
    if (!cont_size) return 0x00;
    //
    FILE *data_fp = fopen64(file_name, mode_flag[mode]);
    if (!data_fp) {
        _LOG_ERROR("open file error! errno:%d %s", errno, file_name);
        return -1;
    }
    if (0 >= fwrite(data_cont, cont_size, 0x01, data_fp)) {
        fclose(data_fp);
        _LOG_ERROR("fwrite file error! errno:%d %s", errno, file_name);
        return -1;
    }
    fclose(data_fp);
    //
    return 0x00;
}

int bina_save_data(char *file_name, char *data_cont, int cont_size, int mode) {
    static char *mode_flag[0x02] = {"wb+", "ab+"};
    if (!cont_size) return 0x00;
    //
    FILE *data_fp = fopen64(file_name, mode_flag[mode]);
    if (!data_fp) {
        _LOG_ERROR("open file error! errno:%d %s", errno, file_name);
        return -1;
    }
    if (0 >= fwrite(data_cont, cont_size, 0x01, data_fp)) {
        fclose(data_fp);
        _LOG_ERROR("fwrite file error! errno:%d %s", errno, file_name);
        return -1;
    }
    fclose(data_fp);
    //
    return 0x00;
}

