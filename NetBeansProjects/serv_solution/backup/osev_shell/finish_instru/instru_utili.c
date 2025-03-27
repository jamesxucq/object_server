#include "commo_header.h"

#include "../cinstru.h"
#include "../cli_struct.h"
#include "print_strea.h"

#include "instru_utili.h"
#include "../debug_funct_sh.h"

//

#define CLIEN_TABLE "    "

void clien_finis(clie_resu *resul, char *instru) {
    if (!strcasecmp(instru, "clie:help")) {
        fprintf(stdout, CLIEN_TABLE"help ...\n");
    } else if (!strcasecmp(instru, "clie:version")) {
        fprintf(stdout, CLIEN_TABLE"version ...\n");
    } else if (!strcasecmp(instru, "clie:about")) {
        fprintf(stdout, CLIEN_TABLE"about ...\n");
    } else {
        if (resul->resu_type) {
            fprintf(stdout, "CLIENT STRAM RESPON:\n");
            print_stream(resul->resu_stram, resul->resu_leng);
            fprintf(stdout, "\n");
        } else {
            resul->resu_data[resul->resu_leng] = '\0';
            fprintf(stdout, "CLIENT MEMOR RESPON:\n%s\n", resul->resu_data);
        }
    }
}

void osev_finis(clie_resu *resul, unsigned int levivk) {
    switch (levivk) {
        case STAI_ECHO:
            fprintf(stdout, "OSEV ECHO RESPON:\n%s\n", resul->resu_data);
            break;
        default:
            if (resul->resu_type) {
                fprintf(stdout, "OSEV STRAM RESPON:\n");
                print_stream(resul->resu_stram, resul->resu_leng);
                fprintf(stdout, "\n");
            } else {
                resul->resu_data[resul->resu_leng] = '\0';
                fprintf(stdout, "OSEV MEMOR RESPON:\n%s\n", resul->resu_data);
            }
            break;
    }
}

void base_finis(clie_resu *resul, unsigned int levivk) {
    switch (levivk) {
        case STAI_ECHO:
            fprintf(stdout, "BASE ECHO RESPON:\n%s\n", resul->resu_data);
            break;
        default:
            if (resul->resu_type) {
                fprintf(stdout, "BASE STRAM RESPON:\n");
                print_stream(resul->resu_stram, resul->resu_leng);
                fprintf(stdout, "\n");
            } else {
                resul->resu_data[resul->resu_leng] = '\0';
                fprintf(stdout, "BASE MEMOR RESPON:\n%s\n", resul->resu_data);
            }
    }
}

void level_finis(clie_resu *resul) {
    if (resul->resu_type) {
        fprintf(stdout, "LEVEL STRAM RESPON:\n");
        print_stream(resul->resu_stram, resul->resu_leng);
        fprintf(stdout, "\n");
    } else {
        resul->resu_data[resul->resu_leng] = '\0';
        fprintf(stdout, "LEVEL MEMOR RESPON:\n%s\n", resul->resu_data);
    }
}

