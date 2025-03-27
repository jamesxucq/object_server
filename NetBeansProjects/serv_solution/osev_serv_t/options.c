/*
 * options.c
 *
 *  Created on: 2010-3-17
 *      Author: Divad
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>             /* for getopt() */
#include <getopt.h>

#include "commo_macro.h"
#include "osev_datyp.h"
#include "logger.h"
#include "server_macro.h"
#include "commo_header.h"

#include "options.h"

/*! Show the version information of the program.*/
void display_version(void) {
    const char* version = VERSION;
    const char* copyright = COPYRIGHT;
    const char* disclaimer = DISCLAIMER;

    fprintf(stderr, "Version %s\n", version);
    fprintf(stderr, "%s\n", copyright);
    fprintf(stderr, "%s\n", disclaimer);
} /* display_version() */

/*! Show the usage of the program.*/
void display_usage(const char* program_name) {
    const char* function = FUNCTION;

    fprintf(stderr, "Function: %s\n", function);
    printf(USAGE, program_name);
} /* void display_usage() */

int parse_args(char *xml_config, int argc, char *argv[]) {
    /* These variables will be used in command-line option parsing */
    /* -- 1 begin --------------------------------------------------------- */
    // const int NUM_ARGS = 1; /* Used in checking the number of non-option arguments */
    int option; /* The return value of getopt() */
    /* -- 1 end ----------------------------------------------------------- */

    /* These variables are ready to get values from option arguments */
    char file_name[PATH_MAX];
    MK_ZERO(file_name);

    /* Other variable definitions */
    unsigned int inde;

    static const char *sopt = "f:vh";
    static const struct option lopt[] = {
        {"file", required_argument, NULL, 'f'},
        {"version", no_argument, NULL, 'v'},
        {"help", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}
    };
    /* Parse command-line options */
    /* -- 2 begin -------------------------------------------------------- */
    /* Setting opterr to 0 will disable the "invalid option" error message */
    /* opterr = 0; */
    while ((option = getopt_long(argc, argv, sopt, lopt, NULL)) != -1) {
        switch (option) {
            case 'f': /* The option has 1 argument */
                strcpy(file_name, optarg);
                break;
            case 'v': /* The option has no argument */
                display_version();
                return EXIT_FAILURE;
                break;
            case 'h': /* help */
            case ':': /* invalid option */
            case '?': /* invalid option */
            default:
                display_usage(argv[0x00]);
                return EXIT_FAILURE;
                break;
        }
    }
    /* -- 2 end ----------------------------------------------------------- */
    /* Output for verifying user input */
    if (file_name[0x00]) {
        if (VALID_FILE_PATH(file_name)) {
            fprintf(stderr, "the file name is error! %s\n", file_name);
            return EXIT_FAILURE;
        }
    } else {
        CREAT_CONF_PATH(file_name, OBJE_SERV_DEFAULT)
    }

    /* -- 3 begin (Optional) ---------------------------------------------- */
    /* After the command-line parsing,
       (argc - optind) is the number of non-option arguments and
       argv[optind] points to the first of them.

       Print all the non-option arguments.
     */
    fprintf(stderr, "Number of non-option arguments = %d:\n", argc - optind);
    for (inde = optind; inde < argc; ++inde) {
        fprintf(stderr, "\t%s\n", argv[inde]);
    }
    /* Show the parsed results */
    /* -- 3 end (Optional) ------------------------------------------------ */

    /* Check the number of the required non-option arguments if necessary.
       You can choose between the strict and loose check,
       or disable both of them without the number check. */
    /* -- 4 begin (Optional) ---------------------------------------------- */

    /* -- 4 end (Optional) ----------------------------------------------- */

    /* ... */
    strcpy(xml_config, file_name);
    //fprintf(stderr, "Program terminated normally.\n" );

    return EXIT_SUCCESS;
} /* int main() */
