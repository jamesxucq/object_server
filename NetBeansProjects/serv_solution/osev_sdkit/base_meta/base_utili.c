#include "commo_header.h"
// #include "third_party.h"
#include "kcomm_header.h"

#include "base_utili.h"

//

struct _subpath_ {
    char *path;
    const struct _subpath_ *subp;
};

typedef struct _subpath_ subpath;

// container path
#define CONT_SHARP_HOME "sharp"
#define CONT_IMEMO_HOME "imemo"
#define CONT_LEAP_HOME "leap"
#define CONT_WTIGER_HOME "wiredtiger" // wiredtiger

static const subpath cont_meta_tab[] = {
    {CONT_SHARP_HOME, NULL}, // sharp
    {CONT_IMEMO_HOME, NULL}, // imemo
    {CONT_LEAP_HOME, NULL}, // leap
    {CONT_WTIGER_HOME, NULL}, // wiredtiger
    {NULL, NULL}
};

// meta data root
#define DATA_CONTAIN_DEFAULT    "contain"
#define DATA_CLASS_DEFAULT      "class"
#define DATA_OBJECT_DEFAULT     "object"
#define DATA_CACHE_DEFAULT      "cache"
#define DATA_INSTANT_DEFAULT    "instant"
#define DATA_TEMP_DEFAULT       "temp"

static const subpath meta_subpath_tab[] = {
    {DATA_CONTAIN_DEFAULT, cont_meta_tab},
    {DATA_CLASS_DEFAULT, NULL},
    {DATA_OBJECT_DEFAULT, NULL},
    {DATA_CACHE_DEFAULT, NULL},
    {DATA_INSTANT_DEFAULT, NULL},
    {DATA_TEMP_DEFAULT, NULL},
    {NULL, NULL}
};

//

int creat_base_conte(char *basen) {
    char meta_path[MAX_PATH * 3];
    CREAT_BASE_DIRECTORY(meta_path, basen)
    if (mkdir(meta_path, 0755)) {
        _LOG_WARN("mkdir:%s error[%d]:%s", meta_path, errno, strerror(errno));
        return -1;
    }
    //
    if (creat_base_attri(basen)) {
        _LOG_WARN("create basen attrib file error!");
        return -1;
    }
    //
    char *sub_dire;
    subpath *sub_path = (subpath *) meta_subpath_tab;
    for (; sub_path->path; ++sub_path) {
        CREAT_BASE_SUBDIRE_LAST(sub_dire, meta_path, basen, sub_path->path)
        if (mkdir(meta_path, 0755)) {
            _LOG_WARN("mkdir:%s error[%d]:%s", meta_path, errno, strerror(errno));
            return -1;
        }
        // second level
        if (sub_path->subp) {
            subpath *sel_path = (subpath *) sub_path->subp;
            for (; sel_path->path; ++sel_path) {
                char *last_str = lccpy(sub_dire, '/');
                last_str = lscpy(last_str, sel_path->path);
                if (mkdir(meta_path, 0755)) {
                    _LOG_WARN("mkdir:%s error[%d]:%s", meta_path, errno, strerror(errno));
                    return -1;
                }
            }
        }
    }
    //
    return 0x00;
}

//

int drop_base_conte(char *basen) {
    OSEVPF("[FUNC]:drop_base_conte:|%s|\n", basen);
    char meta_path[MAX_PATH * 3];
    CREAT_BASE_DIRECTORY(meta_path, basen)
    if (recu_rmdir(meta_path)) {
        _LOG_WARN("recu rmdir error, path:%s", meta_path);
        return -1;
    }
    //
    return 0x00;
}

// xfs not have, ext4 have it.
// #define  HAVE_DIRENT_DTYPE    0x01
// #ifdef HAVE_DIRENT_DTYPE

/*
int empty_directory(char *dirpath) {
    DIR *dires;
    struct dirent *entry;
    //
    if (!(dires = opendir(dirpath)))  {
        _LOG_WARN("can not open dir %s", dirpath);
        return -1;
    }
    while (NULL != (entry = readdir(dires))) {
        if (DT_UNKNOWN == entry->d_type || DT_REG == entry->d_type) {
            closedir(dires);
            return -1;
        } else if (DT_DIR == entry->d_type) {
            if (!strcmp(".", entry->d_name) || !strcmp("..", entry->d_name))
                continue;
            closedir(dires);
            return -1;
        }
    }
    closedir(dires);
    //
    return 0x00;
}
 */

int empty_directory(char *dirpath) {
    DIR *dires;
    struct dirent *entry;
    struct stat64 statbuf;
    char full_path[MAX_PATH * 3];
    //
    if (!(dires = opendir(dirpath))) {
        _LOG_WARN("can not open dir %s", dirpath);
        return -1;
    }
    while (NULL != (entry = readdir(dires))) {
        snprintf(full_path, sizeof (full_path), "%s/%s", dirpath, entry->d_name);
        if (stat64(full_path, &statbuf) < 0) {
            closedir(dires);
            _LOG_WARN("stat errno:%d", errno);
            return -1;
        }
        if (S_ISLNK(statbuf.st_mode) || S_ISREG(statbuf.st_mode)) {
            closedir(dires);
            return -1;
        } else if (S_ISDIR(statbuf.st_mode)) {
            if (!strcmp(".", entry->d_name) || !strcmp("..", entry->d_name))
                continue;
            closedir(dires);
            return -1;
        }
    }
    closedir(dires);
    //
    return 0x00;
}

// 0x00:empty -1:not empty

int valid_base_clean(char *basen) {
    OSEVPF("[FUNC]:valid_base_clean:|%s|\n", basen);
    char meta_path[MAX_PATH * 3];
    CREAT_BASE_SUBDIRE(meta_path, basen, DATA_CLASS_DEFAULT)
    if (empty_directory(meta_path))
        return -1;
    //
    return 0x00;
}