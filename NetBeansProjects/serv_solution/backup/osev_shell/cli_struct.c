#include <fcntl.h>
#include <unistd.h>

#include "cli_struct.h"
#include "debug_funct_sh.h"

//
int osev_comand_tab[] = {-1, OCOMD_OPEN, OCOMD_CLOSE};
int base_comand_tab[] = {-1, BCOMD_OPEN, BCOMD_CLOSE};
int osev_status_tab[] = {-1, OSTAT_ECHO, OSTAT_STATUS, OSTAT_STATIS};
int base_status_tab[] = {-1, BSTAT_ECHO, BSTAT_STATUS, BSTAT_STATIS};
int osev_privi_tab[] = {-1, OPRIV_LIST, OPRIV_ROLE, OPRIV_USER};
int base_privi_tab[] = {-1, BPRIV_LIST, BPRIV_ROLE, BPRIV_USER};

int const_echo_tab[] = {-1, EECHO_OBJID, EECHO_NAME, EECHO_ATTRIB, EECHO_STATIS};
int query_echo_tab[] = {-1, QECHO_OBJID, QECHO_NAME, QECHO_ATTRIB, QECHO_STATIS};

// mkstemp

int resul_initial(clie_resu *resul) {
    resul->resu_type = 0x00;
    resul->resu_leng = 0x00;
    //
    char resul_name[MAX_PATH] = {"/tmp/resul_set.XXXXXX"};
    if (!mkstemp(resul_name))
        return -1;
    resul->resu_stram = fopen64(resul_name, "wb+");
    if (!resul->resu_stram)
        return -1;
    unlink(resul_name);
    rewind(resul->resu_stram);
    CLIEPF("resul_name:%s\n", resul_name);
    //
    return 0x00;
}

//

void reset_result(clie_resu *resul) {
    if (resul->resu_type)
        rewind(resul->resu_stram);
    resul->resu_type = 0x00;
    resul->resu_leng = 0x00;
}

//

void final_result(clie_resu *resul) {
    if (resul->resu_stram)
        fclose(resul->resu_stram);
}