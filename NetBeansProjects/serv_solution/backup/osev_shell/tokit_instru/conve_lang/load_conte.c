#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "parse_lv2p_atti.h"
#include "load_conte.h"
//

char *load_conte_plain(char *conte, int max_size, clie_resu *resul) {
    if (resul->resu_type) {
        if (max_size < resul->resu_leng)
            return NULL;
        rewind(resul->resu_stram);
        ssize_t realen = fread(conte, 0x01, resul->resu_leng, resul->resu_stram);
        if (resul->resu_leng != realen)
            return NULL;
    } else memcpy(conte, resul->resu_data, resul->resu_leng);
    conte[resul->resu_leng] = '\0';
            //
    return conte;
}

