
#include "commo_header.h"

#include "kcomm_macro.h"
#include "kcstr_utili.h"

#include "recurs_data.h"

// xfs not have, ext4 have
// #ifdef _DIRENT_HAVE_D_TYPE

/*
static int recur_scaner(char **carrp, char *_cdecl_, char *dirpath) {
    DIR *dires;
    struct dirent *entry;
    char *last_str = _cdecl_;
    char full_path[MAX_PATH * 3];
    char lv2pn[LVTN_LENGTH];
    //
    if (!(dires = opendir(dirpath)))  {
        _LOG_WARN("can not open dir %s", dirpath);
        return -1;
    }
    while (NULL != (entry = readdir(dires))) {
        if (DT_UNKNOWN == entry->d_type || DT_REG == entry->d_type) {
            if (check_extend(lv2pn, entry->d_name, CLASS_EXTEND_NAME)) {
                // OSEVPF("clat_scaner lv2pn:|%s|\n", lv2pn);
                LSCPY_O(carrp[0x00], lv2pn, last_str);
                ++carrp;
            }
        } else if (DT_DIR == entry->d_type) {
            if (!strcmp(".", entry->d_name) || !strcmp("..", entry->d_name))
                continue;
            if (recur_scaner(carrp, last_str, full_path)) {
                closedir(dires);
                return -1;
            }
        }
    }
    closedir(dires);
    //
    return 0x00;
}
 */

static int recur_scaner(char **carrp, char *_cdecl_, char *dirpath) {
    DIR *dires;
    struct dirent *entry;
    struct stat64 statbuf;
    char *last_str = _cdecl_;
    char full_path[MAX_PATH * 3];
    char lv2pn[LVTN_LENGTH];
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
            if (check_extend(lv2pn, entry->d_name, CLASS_EXTEND_NAME)) {
                // OSEVPF("clat_scaner lv2pn:|%s|\n", lv2pn);
                LSCPY_O(carrp[0x00], lv2pn, last_str);
                ++carrp;
            }
        } else if (S_ISDIR(statbuf.st_mode)) {
            if (!strcmp(".", entry->d_name) || !strcmp("..", entry->d_name))
                continue;
            if (recur_scaner(carrp, last_str, full_path)) {
                closedir(dires);
                return -1;
            }
        }
    }
    closedir(dires);
    //
    return 0x00;
}

int list_clasn(char **lv2pnp, char *_cdecl_, char *lv2p_path) {
    memset(lv2pnp, '\0', sizeof (char *) * MAX_BASE_COUNT);
    recur_scaner(lv2pnp, _cdecl_, lv2p_path);
    return 0x00;
}

// #ifdef _DIRENT_HAVE_D_TYPE

/*
static int list_scaner(char **basnp, char *_cdecl_, char *dirpath) {
    DIR *dires;
    struct dirent *entry;
    char *last_str = _cdecl_;
    //
    if (!(dires = opendir(dirpath)))  {
        _LOG_WARN("can not open dir %s", dirpath);
        return -1;
    }
    while (NULL != (entry = readdir(dires))) {
        // OSEVPF("h entry->d_name:|%s| entry->d_type:%d\n", entry->d_name, entry->d_type);
        if (DT_DIR == entry->d_type) {
            if (!strcmp(".", entry->d_name) || !strcmp("..", entry->d_name))
                continue;
            LSCPY_O(basnp[0x00], entry->d_name, last_str);
            ++basnp;
        }
    }
    closedir(dires);
    //
    return 0x00;
}
 */

static int list_scaner(char **basnp, char *_oline_, char *dirpath) {
    DIR *dires;
    struct dirent *entry;
    struct stat64 statbuf;
    char full_path[MAX_PATH * 3];
    char *last_str = _oline_;
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
        if (S_ISDIR(statbuf.st_mode)) {
            if (!strcmp(".", entry->d_name) || !strcmp("..", entry->d_name))
                continue;
            LSCPY_O(basnp[0x00], entry->d_name, last_str);
            ++basnp;
        }
    }
    closedir(dires);
    //
    return 0x00;
}

int list_base(char **basnp, char *_oline_, char *data_path) {
    memset(basnp, '\0', sizeof (char *) * MAX_BASE_COUNT);
    list_scaner(basnp, _oline_, data_path);
    return 0x00;
}