#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/file.h>
#include <unistd.h>

//
#include "shap_utility.h"
#include "creat_sharp.h"

uint32 build_sharp_enviro(char *file_name, int32 isize) {
    FILE *fpiden = fopen(file_name, "wb+");
    if (!fpiden) return 0x01;
    // root
    if (fill_head_iden(fpiden, isize)) {
        fclose(fpiden);
        return 0x01;
    }
    if (fill_idle_iden(fpiden, isize)) {
        fclose(fpiden);
        return 0x01;
    }
    fclose(fpiden);
    //
    printf("build_sharp_enviro:%s\n", file_name);
    return 0x00;
}

//

uint32 destroy_sharp_enviro(char *file_name) {
    unlink(file_name);
    printf("destroy_sharp_enviro:%s\n", file_name);
    return 0x00;
}


