#include "commo_header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <bits/fcntl-linux.h>
#include "load.h"
#include "../debug_funct_sh.h"

//
#define BUFF_SIZE                        0x2000

static int load_strea(FILE *strem, char *file_name) {
    unsigned char buffer[BUFF_SIZE];
    int realen;
    // CLIEPF("load strem\n");
    rewind(strem);
    FILE *from = fopen64(file_name, "rb+");
    if (!from) {
        CLIEPF("open file error! %s\n", file_name);
        return -1;
    }
    rewind(from);
    //
    while (0x00 != (realen = fread(buffer, 0x01, BUFF_SIZE, from))) {
        if (realen != fwrite(buffer, 0x01, realen, strem)) {
            CLIEPF("write ERROR!\n");
            fclose(from);
            return -1;
        }
    }
    //        
    fclose(from);
    return 0x00;
}

static int load_memo(char *memo, char *file_name) {
    // CLIEPF("load memo\n");
    FILE *from = fopen64(file_name, "rb+");
    if (!from) {
        CLIEPF("open file error! %s\n", file_name);
        return -1;
    }
    //
    if (0x00 >= fread(memo, 0x01, RESP_DATA_SIZE, from)) {
        CLIEPF("read file error! %s\n", file_name);
        fclose(from);
        return -1;
    }
    //        
    fclose(from);
    return 0x00;
}

// load_type

static int check_load_type(uint64 *file_len, char *file_name, int bulen) {
    struct stat64 statb;
    if (stat64(file_name, &statb) == -1) {
        CLIEPF("can not get info of %s", file_name);
        return -1;
    }
    *file_len = statb.st_size;
    if (bulen < statb.st_size) return 0x01;
    return 0x00;
}

// kits:load(filename);

// 0x00:OK -1:error

int kits_load(char **pamvp, clie_resu *resul) {
    CLIEPF("[FUNC]:kits_load.\n");
    int load_valu = 0x00;
    // pamvu = 1
    if (!pamvp[0x00] || pamvp[0x01])
        return -1;
    //
    uint64 file_len;
    quote_decode(pamvp[0x00]);
    switch (check_load_type(&file_len, pamvp[0x00], RESP_DATA_SIZE)) {
        case 0x00:
            load_valu = load_memo(resul->resu_data, pamvp[0x00]);
            resul->resu_leng = file_len;
            resul->resu_type = 0x00;
            break;
        case 0x01:
            rewind(resul->resu_stram);
            load_valu = load_strea(resul->resu_stram, pamvp[0x00]);
            resul->resu_leng = file_len;
            resul->resu_type = 0x01;
            break;
        case -1:
            load_valu = -1;
            break;
    }
    //
    return load_valu;
}