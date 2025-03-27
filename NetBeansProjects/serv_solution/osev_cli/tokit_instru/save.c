#include "commo_header.h"

#include "save.h"
#include "../debug_funct_sh.h"

//
#define BUFF_SIZE                        0x2000

static int save_stre(char *file_name, FILE *strem, unsigned int mode) {
    static char *mode_flag[0x02] = {"wb+", "ab+"};
    unsigned char buffer[BUFF_SIZE];
    int realen, wrilen;
    //
    FILE *desti = fopen64(file_name, mode_flag[mode]);
    if (!desti) {
        CLIT_PF("open file error! %s\n", file_name);
        return -1;
    }
    //
    rewind(strem);
    do {
        if (0x00 >= (realen = fread(buffer, 0x01, BUFF_SIZE, strem)))
            break;
        if (0x00 >= (wrilen = fwrite(buffer, 0x01, realen, desti)))
            break;
        if (wrilen != realen) {
            CLIT_PF("write file error! %s\n", file_name);
            fclose(desti);
            return -1;
        }
    } while (0 < realen && 0 < wrilen);
    //        
    fclose(desti);
    return 0x00;
}

static int save_memo(char *file_name, char *memo, uint64 slen, unsigned int mode) {
    static char *mode_flag[0x02] = {"wb+", "ab+"};
    int wrilen, tatol = 0x00;
    //
    FILE *desti = fopen64(file_name, mode_flag[mode]);
    if (!desti) {
        CLIT_PF("open file error! %s\n", file_name);
        return -1;
    }
    //
    do {
        if (!(wrilen = fwrite(memo + tatol, 0x01, slen - tatol, desti))) {
            CLIT_PF("write file error! %s\n", file_name);
            fclose(desti);
            return -1;
        }
        tatol += wrilen;
    } while (slen > tatol);
    //        
    fclose(desti);
    return 0x00;
}

//
// kits:save(filename, TRUNCA);
// kits:save(filename, APPEND);
// kits:save(filename); // append

#define SAVE_TRUNCA_FILE "TRUNCA"
#define SAVE_APPEND_FILE "APPEND"

// trans-serve
#define TRUNCA_FILE 0x00
#define FILE_APPEND 0x01

// 0x00:OK -1:error

int kits_save(char **pamvp, clit_resu *resul) {
    CLIT_PF("[FUNC]:kits_save.\n");
    unsigned int mode = FILE_APPEND;
    // pamvu = 1 = 2
    if (!pamvp[0x00] || (pamvp[0x01] && pamvp[0x02]))
        return -1;
    //
    if (pamvp[0x01]) {
        quote_decode(pamvp[0x01]);
        if (strcmp(SAVE_TRUNCA_FILE, pamvp[0x01])) {
            mode = TRUNCA_FILE;
        } else if (strcmp(SAVE_APPEND_FILE, pamvp[0x01]))
            mode = FILE_APPEND;
    }
    //
    quote_decode(pamvp[0x00]);
    if (resul->resu_type) {
        if (save_stre(pamvp[0x00], resul->resu_stram, mode)) {
            CLIT_PF("save file %s error!\n", pamvp[0x00]);
        }
    } else {
        if (save_memo(pamvp[0x00], resul->resu_data, resul->resu_leng, mode)) {
            CLIT_PF("save file %s error!\n", pamvp[0x00]);
        }
    }
    //
    return 0x00;
}