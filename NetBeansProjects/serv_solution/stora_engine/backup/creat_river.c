#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/file.h>
#include <unistd.h>

#include "riv_common.h"
#include "rive_utility.h"
#include "creat_river.h"

//

/*
uint32 create_river_enviro(char *location) {
    char file_name[MAX_PATH * 3];
    int irval = 0x00;
    RIVER_PATH(file_name, location, RIV_INDE_DEFAULT);
    // create the database object
    TreeDB rivdb;
    // open the database
    if (!rivdb.open(file_name, TreeDB::OWRITER | TreeDB::OCREATE)) {
        cerr << "open error: " << rivdb.error().name() << endl;
        irval = 0x01;
    }
    // close the database
    if (!rivdb.close()) {
        cerr << "close error: " << rivdb.error().name() << endl;
    }
    //
    RIVER_PATH(file_name, location, RIV_IDEN_DEFAULT);
    FILE *fpiden = fopen64(file_name, "wb+");
    if (!fpiden) irval = 0x01;
    //
    RIVER_PATH(file_name, location, RIV_CHKS_DEFAULT);
    FILE *fpchks = fopen64(file_name, "wb+");
    if (!fpchks) irval = 0x01;
    if (!irval) fill_idle_entry(fpchks, fpiden);
    //
    if (fpchks) fclose(fpchks);
    if (fpiden) fclose(fpiden);
    //
    return irval;
}
 */

uint32 build_river_enviro(char *file_name, int32 line_size) {
    int irval = 0x00;
    //
    FILE *fpiden = fopen64(file_name, "wb+");
    if (!fpiden) irval = 0x01;
    if (!irval) fill_idle_iden(fpiden, line_size);
    //
    return irval;
}

//

uint32 destroy_river_enviro(char *file_name) {
    printf("destroy_river_enviro:%s\n", file_name);
    unlink(file_name);
    return 0x00;
}