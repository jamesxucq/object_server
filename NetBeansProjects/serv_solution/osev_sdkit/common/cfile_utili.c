#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"

#include "kcomm_macro.h"
#include "kcomm_directory.h"
#include "cfile_utili.h"

//

int delet_libra_file(char *basen, char *librn) {
    OSEVPF("[FUNC]:delet_libra_file\n");
    char libr_path[MAX_PATH * 3];
    LIBRARY_SUFFIX_FILE(libr_path, basen, librn, LIBRA_SUFFIX);
    OSEVPF("libr_path:|%s|\n", libr_path);
    unlink(libr_path);
    return 0x00;
}

int bakup_libra_file(char *basen, char *librn) {
    OSEVPF("[FUNC]:bakup_libra_file\n");
    char libr_path[MAX_PATH * 3];
    char libr_baku[MAX_PATH * 3];
    LIBRARY_SUFFIX_FILE(libr_path, basen, librn, LIBRA_SUFFIX);
    LIBRARY_SUFFIX_FILE(libr_baku, basen, librn, BAKUP_SUFFIX);
    OSEVPF("libr_path:|%s|\n", libr_path);
    OSEVPF("libr_baku:|%s|\n", libr_baku);
    if (rename(libr_path, libr_baku))
        return -1;
    //
    return 0x00;
}

int recov_libra_file(char *basen, char *librn) {
    OSEVPF("[FUNC]:recov_libra_file\n");
    char libr_path[MAX_PATH * 3];
    char libr_baku[MAX_PATH * 3];
    LIBRARY_SUFFIX_FILE(libr_path, basen, librn, LIBRA_SUFFIX);
    LIBRARY_SUFFIX_FILE(libr_baku, basen, librn, BAKUP_SUFFIX);
    OSEVPF("libr_path:|%s|\n", libr_path);
    OSEVPF("libr_baku:|%s|\n", libr_baku);
    if (rename(libr_baku, libr_path))
        return -1;
    //
    return 0x00;
}


