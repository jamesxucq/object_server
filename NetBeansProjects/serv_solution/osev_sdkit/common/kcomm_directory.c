#include <string.h>

#include "commo_header.h"
#include "kcomm_directory.h"

//
char _commo_directory_[MAX_PATH * 3];

//

char *commo_directory_init(char *directory) {
    strcpy(_commo_directory_, directory);
    fprintf(stdout, "Set data directory:%s\n", directory);
    return _commo_directory_;
}

