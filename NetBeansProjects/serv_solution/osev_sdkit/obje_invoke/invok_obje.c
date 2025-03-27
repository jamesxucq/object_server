
#include "commo_header.h"
#include "kcomm_header.h"
#include "ostri_utili.h"

#include "lv2p_meta/lv2me_ite.h"
#include "invok_obje.h"

// xfs not have, ext4 have it.
// #define  HAVE_DIRENT_DTYPE    0x01
// #ifdef HAVE_DIRENT_DTYPE

/*
static int clas_scaner(char **carrp, char *_cline_, char *dirpath) {
    // OSEVPF("[FUNC]:clat_scaner, dirpath:|%s|\n", dirpath);
    DIR *dires;
    struct dirent *entry;
    char *last_str = _cline_;
    char lv2pn[LVTN_LENGTH];
    //
    if (!(dires = opendir(dirpath)))  {
        _LOG_WARN("can not open dir %s", dirpath);
        return -1;
    }
    while (NULL != (entry = readdir(dires))) {
        // OSEVPF("--- clat_scaner d_name:|%s|\n", entry->d_name);
        if (DT_DIR == entry->d_type) {
            if (!strcmp(".", entry->d_name) || !strcmp("..", entry->d_name))
                continue;
        } else if (DT_UNKNOWN == entry->d_type || DT_REG == entry->d_type) {
            if (check_extend(lv2pn, entry->d_name, CLASS_EXTEND_NAME)) {
                // OSEVPF("clat_scaner lv2pn:|%s|\n", lv2pn);
                LSCPY_O(carrp[0x00], lv2pn, last_str);
                ++carrp;
            }
        }
    }
    closedir(dires);
    //
    return 0x00;
}
 */

static int clas_scaner(char **carrp, char *_cline_, char *dirpath) {
    // OSEVPF("[FUNC]:clat_scaner, dirpath:|%s|\n", dirpath);
    DIR *dires;
    struct dirent *entry;
    struct stat64 statbuf;
    char *last_str = _cline_;
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
        // OSEVPF("--- clat_scaner d_name:|%s|\n", entry->d_name);
        if (S_ISLNK(statbuf.st_mode) || S_ISREG(statbuf.st_mode)) {
            if (check_extend(lv2pn, entry->d_name, CLASS_EXTEND_NAME)) {
                // OSEVPF("clat_scaner lv2pn:|%s|\n", lv2pn);
                LSCPY_O(carrp[0x00], lv2pn, last_str);
                ++carrp;
            }
        }
    }
    closedir(dires);
    //
    return 0x00;
}

int list_clas(char **clas_arrp, char *_cline_, char *data_path) {
    memset(clas_arrp, '\0', sizeof (char *) * LVTP_COUNT);
    clas_scaner(clas_arrp, _cline_, data_path);
    return 0x00;
}

//

int updat_lv2p_extern(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, uint32 value) {
    OSEVPF("[FUNC]:updat_lv2p_extern\n");
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    if (value) {
        lv2ai->iexter = TRUE_OSV;
    } else lv2ai->iexter = FALSE_OSV;
    //
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2pn);
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

