#include <fcntl.h>
#include <unistd.h>

#include "clit_struct.h"
#include "debug_funct_sh.h"

//
int osev_comand_tab[] = {-1, OCOMD_OPEN, OCOMD_CLOSE};
int base_comand_tab[] = {-1, BCOMD_OPEN, BCOMD_CLOSE};
int osev_status_tab[] = {-1, OSTAT_ECHO, OSTAT_STATIS};
int base_status_tab[] = {-1, BSTAT_ECHO, BSTAT_STATIS};
int osev_privile_tab[] = {-1, OPRIV_LIST, OPRIV_ROLE, OPRIV_USER};
int base_privile_tab[] = {-1, BPRIV_LIST, BPRIV_ROLE, BPRIV_USER};

int invok_status_tab[] = {-1, ISTAT_LIST, ISTAT_STATIS};
int colle_status_tab[] = {-1, CSTAT_LIST, CSTAT_STATIS};
int const_status_tab[] = {-1, ESTAT_ECHO, ESTAT_ATTRIB, ESTAT_STATIS};
int query_status_tab[] = {-1, QSTAT_ECHO, QSTAT_ATTRIB, QSTAT_STATIS};

// mkstemp

int resul_initial(clit_resu *resul) {
    resul->resu_type = 0x00;
    resul->resu_leng = 0x00;
    //
    char resul_name[MAX_PATH * 3] = {"/tmp/resul_set.XXXXXX"};
    if (!mkstemp(resul_name))
        return -1;
    resul->resu_stram = fopen64(resul_name, "wb+");
    if (!resul->resu_stram)
        return -1;
    unlink(resul_name);
    rewind(resul->resu_stram);
    CLIT_PF("resul_name:%s\n", resul_name);
    //
    return 0x00;
}

//

void reset_result(clit_resu *resul) {
    if (resul->resu_type)
        rewind(resul->resu_stram);
    resul->resu_type = 0x00;
    resul->resu_leng = 0x00;
}

//

void final_result(clit_resu *resul) {
    if (resul->resu_stram)
        fclose(resul->resu_stram);
}