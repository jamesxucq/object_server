#include "commo_header.h"

#include "../cinstru.h"
#include "../clit_struct.h"
#include "print_strea.h"

#include "instru_utili.h"
#include "../debug_funct_sh.h"

//

#define CLIEN_TABLE "    "

void clien_finis(clit_resu *resul, char *instru) {
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

#define OSEV_DEFAULT_FINISH(RESUL) { \
    if (RESUL->resu_type) { \
        fprintf(stdout, "OSEV STRAM RESPON:\n"); \
        print_stream(RESUL->resu_stram, RESUL->resu_leng); \
        fprintf(stdout, "\n"); \
    } else { \
        RESUL->resu_data[RESUL->resu_leng] = '\0'; \
        fprintf(stdout, "OSEV MEMOR RESPON:\n%s\n", RESUL->resu_data); \
    } \
}

void osev_finis(clit_resu *resul, unsigned int levivk, unsigned int invok) {
    switch (levivk) {
        case OSEV_POST:
            fprintf(stdout, "OSEV POST RESPON:\n%s\n", resul->resu_data);
            break;
        case OSEV_STATUS:
        {
            switch (invok) {
                case STAIU_ECHO:
                    fprintf(stdout, "OSEV STATU:ECHO RESPON:\n%s\n", resul->resu_data);
                    break;
                case STAIU_STATIS:
                    fprintf(stdout, "OSEV STATU:STATIS RESPON:\n%s\n", resul->resu_data);
                    break;
                default:
                    break;
            }
        }
            break;
        case OSEV_COMAND:
        {
            switch (invok) {
                case COMDI_OPEN:
                case COMDI_CLOSE:
                    OSEV_DEFAULT_FINISH(resul)
                    break;
                default:
                    break;
            }
        }
            break;
        case OSEV_PRIVILE:
        {
            switch (invok) {
                case PRIVI_LIST:
                    fprintf(stdout, "OSEV PRIVI:LIST RESPON:\n%s\n", resul->resu_data);
                    break;
                case PRIVI_ROLE:
                case PRIVI_USER:
                    OSEV_DEFAULT_FINISH(resul)
                    break;
                default:
                    break;
            }
        }
            break;
        default:
            break;
    }
}

#define BASE_DEFAULT_FINISH(RESUL) { \
    if (RESUL->resu_type) { \
        fprintf(stdout, "BASE STRAM RESPON:\n"); \
        print_stream(RESUL->resu_stram, RESUL->resu_leng); \
        fprintf(stdout, "\n"); \
    } else { \
        RESUL->resu_data[RESUL->resu_leng] = '\0'; \
        fprintf(stdout, "BASE MEMOR RESPON:\n%s\n", RESUL->resu_data); \
    } \
}

void base_finis(clit_resu *resul, unsigned int levivk, unsigned int invok) {
    switch (levivk) {
        case BASE_POST:
            BASE_DEFAULT_FINISH(resul)
            break;
        case BASE_STATUS:
        {
            switch (invok) {
                case STAIU_ECHO:
                    fprintf(stdout, "BASE STATU:ECHO RESPON:\n%s\n", resul->resu_data);
                    break;
                case STAIU_STATIS:
                    fprintf(stdout, "BASE STATU:STATIS RESPON:\n%s\n", resul->resu_data);
                    break;
                default:
                    break;
            }
        }
            break;
        case BASE_COMAND:
        {
            switch (invok) {
                case COMDI_OPEN:
                case COMDI_CLOSE:
                    BASE_DEFAULT_FINISH(resul)
                    break;
                default:
                    break;
            }
        }
            break;
        case BASE_PRIVILE:
        {
            switch (invok) {
                case PRIVI_LIST:
                    fprintf(stdout, "BASE PRIVI:LIST RESPON:\n%s\n", resul->resu_data);
                    break;
                case PRIVI_ROLE:
                case PRIVI_USER:
                    BASE_DEFAULT_FINISH(resul)
                    break;
                default:
                    break;
            }
        }
            break;
        default:
            break;
    }
}

void level_finis(clit_resu *resul) {
    if (resul->resu_type) {
        fprintf(stdout, "LEVEL STRAM RESPON:\n");
        print_stream(resul->resu_stram, resul->resu_leng);
        fprintf(stdout, "\n");
    } else {
        resul->resu_data[resul->resu_leng] = '\0';
        fprintf(stdout, "LEVEL MEMOR RESPON:\n%s\n", resul->resu_data);
    }
}

