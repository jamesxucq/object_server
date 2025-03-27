#include "commo_header.h"

#include "../cinstru.h"
#include "../cli_struct.h"
#include "print_strea.h"

#include "tokit_utili.h"
#include "../debug_funct_sh.h"

//

void list_finis(clie_resu *resul) {
    fprintf(stdout, "resu_type:%d resu_leng:%llu\n", resul->resu_type, resul->resu_leng);
    if (resul->resu_type) {
        fprintf(stdout, "LIST STRAM RESPON:\n");
        print_stream(resul->resu_stram, resul->resu_leng);
        fprintf(stdout, "\n");
    } else {
        resul->resu_data[resul->resu_leng] = '\0';
        fprintf(stdout, "LIST MEMOR RESPON:\n%s\n", resul->resu_data);
    }
}

void load_finis(clie_resu *resul) {
    fprintf(stdout, "resu_type:%d resu_leng:%llu\n", resul->resu_type, resul->resu_leng);
    if (resul->resu_type) {
        fprintf(stdout, "LOAD STRAM RESPON:\n");
        print_stream(resul->resu_stram, resul->resu_leng);
        fprintf(stdout, "\n");
    } else {
        resul->resu_data[resul->resu_leng] = '\0';
        fprintf(stdout, "LOAD MEMOR RESPON:\n%s\n", resul->resu_data);
    }
}

void save_finis(clie_resu *resul) {
    fprintf(stdout, "resu_type:%d resu_leng:%llu\n", resul->resu_type, resul->resu_leng);
    if (resul->resu_type) {
        fprintf(stdout, "SAVE STRAM RESPON:\n");
        print_stream(resul->resu_stram, resul->resu_leng);
        fprintf(stdout, "\n");
    } else {
        resul->resu_data[resul->resu_leng] = '\0';
        fprintf(stdout, "SAVE MEMOR RESPON:\n%s\n", resul->resu_data);
    }
}

void conv_finis(clie_resu *resul) {
    fprintf(stdout, "resu_type:%d resu_leng:%llu\n", resul->resu_type, resul->resu_leng);
    if (resul->resu_type) {
        fprintf(stdout, "CONVER STRAM RESPON:\n");
        print_stream(resul->resu_stram, resul->resu_leng);
        fprintf(stdout, "\n");
    } else {
        resul->resu_data[resul->resu_leng] = '\0';
        fprintf(stdout, "CONVER MEMOR RESPON:\n%s\n", resul->resu_data);
    }
}

void prtyp_finis(clie_resu *resul) {
    fprintf(stdout, "resu_type:%d resu_leng:%llu\n", resul->resu_type, resul->resu_leng);
    if (resul->resu_type) {
        fprintf(stdout, "PRETTY STRAM RESPON:\n");
        print_stream(resul->resu_stram, resul->resu_leng);
        fprintf(stdout, "\n");
    } else {
        resul->resu_data[resul->resu_leng] = '\0';
        fprintf(stdout, "PRETTY MEMOR RESPON:\n%s\n", resul->resu_data);
    }
}

void keyval_finis(clie_resu *resul) {
    fprintf(stdout, "resu_type:%d resu_leng:%llu\n", resul->resu_type, resul->resu_leng);
    if (resul->resu_type) {
        fprintf(stdout, "KEY_VALUE STRAM RESPON:\n");
        print_stream(resul->resu_stram, resul->resu_leng);
        fprintf(stdout, "\n");
    } else {
        resul->resu_data[resul->resu_leng] = '\0';
        fprintf(stdout, "KEY_VALUE MEMOR RESPON:\n%s\n", resul->resu_data);
    }
}

void formp_finis(clie_resu *resul) {
    fprintf(stdout, "resu_type:%d resu_leng:%llu\n", resul->resu_type, resul->resu_leng);
    if (resul->resu_type) {
        fprintf(stdout, "FORMAT STRAM RESPON:\n");
        print_stream(resul->resu_stram, resul->resu_leng);
        fprintf(stdout, "\n");
    } else {
        resul->resu_data[resul->resu_leng] = '\0';
        fprintf(stdout, "FORMAT MEMOR RESPON:\n%s\n", resul->resu_data);
    }
}

void expand_finis(clie_resu *resul) {
    fprintf(stdout, "resu_type:%d resu_leng:%llu\n", resul->resu_type, resul->resu_leng);
    if (resul->resu_type) {
        fprintf(stdout, "EXPAND STRAM RESPON:\n");
        print_stream(resul->resu_stram, resul->resu_leng);
        fprintf(stdout, "\n");
    } else {
        resul->resu_data[resul->resu_leng] = '\0';
        fprintf(stdout, "EXPAND MEMOR RESPON:\n%s\n", resul->resu_data);
    }
}



