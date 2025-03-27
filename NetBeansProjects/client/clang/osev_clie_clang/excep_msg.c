
#include "commo_header.h"

#include "clie_macro.h"
#include "reque_respo.h"
#include "excep_messa.h"

#include "excep_msg.h"

//

static const char *excep_stri(char *excstr, int exce_code) {
    char *excep_msg;
    EXCEP_DICTI_VALUE(excep_msg, exception_dict, exce_code)
    if (!excep_msg) {
        sprintf(excstr, "%08X: Unknown exception", exce_code);
        return excstr;
    }
    return excep_msg;
}

static const char *statu_stri(char *stastr, int stat_code) {
    char *statu_msg;
    EXCEP_DICTI_VALUE(statu_msg, status_dict, stat_code)
    if (!statu_msg) {
        sprintf(stastr, "%08X: Unknown status_code", stat_code);
        return stastr;
    }
    return statu_msg;
}

//

void outpu_excep_code(resp_data_t *res_dat) {
    char excstr[STACKBUF_ZLEN];
    printf("    STATUS_CODE: (%04X) %s\n", res_dat->status_code, statu_stri(excstr, res_dat->status_code));
    //
    if (EXCEP_LENG == res_dat->content_length)
        printf("    EXCEPTION: (%08X) %s\n", ((unsigned int*) res_dat->resp_memo)[0x00], excep_stri(excstr, ((unsigned int*) res_dat->resp_memo)[0x00]));
    else if (OSEV_ATTACH_OKAY == ((unsigned int*) res_dat->resp_memo)[0x00]) {
        res_dat->resp_memo[res_dat->content_length] = '\0';
        printf("    EXCEPTION: OSEV_ATTACH_OKAY(%08X)\n", ((unsigned int*) res_dat->resp_memo)[0x00]);
        printf("%s\n", res_dat->resp_memo + EXCEP_LENG);
    } else if (res_dat->content_length) printf("    EXCEPTION: Unknown exception!\n");
}

//

void outpu_respo_code(uint32 status_code) {
    char stastr[STACKBUF_ZLEN];
    printf("    STATUS_CODE: (%04X) %s\n", status_code, statu_stri(stastr, status_code));
}