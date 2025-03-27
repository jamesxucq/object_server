#include "commo_header.h"

#include "rive_obje.h"

#include "rive_bzl.h"

//

int rivebzl_create(char *data_directory) {
    fprintf(stdout, "[FUNC]:rivebzl_create start!\n");
    // strcpy(_conta_directory_, data_directory);
    fprintf(stdout, "[FUNC]:rivebzl_create end!\n");
    return ERR_SUCCESS; //succ
}
//

int rivebzl_destroy() {
    fprintf(stdout, "[FUNC]:rivebzl_destroy start!\n");
    fprintf(stdout, "[FUNC]:rivebzl_destroy end!\n");
    return ERR_SUCCESS; //succ
}

//

int open_rive_bzl(rive_conne *rivcon, char *basen) {
    OSEVPF("[FUNC]:open_rive_bzl open:|%s|\n", basen);
    rive_ha **stora_ha = _stora_hande_tab_;
    unsigned int inde = 0x00;
    for (; STORA_ENGINE_COUNT > inde; ++inde, ++stora_ha) {
        if ((stora_ha[0x00])->open_conne(&(rivcon[inde].conne), basen, 0x01)) {
            _LOG_WARN("open rive %s error!", (stora_ha[0x00])->storage_name);
            return -1;
        }
        rivcon[inde].selist = NULL;
    }
    //
    return 0x00;
}

//

int close_rive_bzl(rive_conne *rivcon) {
    OSEVPF("[FUNC]:close_rive_bzl\n");
    rive_ha **stora_ha = _stora_hande_tab_;
    unsigned int inde = 0x00;
    for (; STORA_ENGINE_COUNT > inde; ++inde, ++stora_ha) {
        if ((stora_ha[0x00])->close_conne(rivcon[inde].conne)) {
            _LOG_WARN("close rive %s error!", (stora_ha[0x00])->storage_name);
            return -1;
        }
        destroy_seion(rivcon[inde].selist, (stora_ha[0x00]));
    }
    //
    return 0x00;
}