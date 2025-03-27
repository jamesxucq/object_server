
#include "../earth_lv2p/EarthLvtpHeader.h"

#include "LevFP_Echo.h"

/*
static const struct stst_node quer_echo_dict[] = {
    {"ECHO", "0I"}, // ECHO
    {"ATTRIB", "1I"}, // ATTRIB
    {"STATIS", "2I"}, // STATIS
    {NULL, "INVA"}
};
 */

static int LevFPEchoObje(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPEchoObje\n");
    // int Echo(string &echoValu, const string &echoType);
    // int Echo(string &echoValu, const string &echoType, const string &contName);
    // int Echo(string &echoValu, const string &echoType, const osv_oid_t *conta_obid);
    string echoValu;
    int echo_valu = earthLevFP.Echo(echoValu);
    if (echo_valu) {
        printf("earthLevFP Echo ERROR! echo_valu:%08X\n", echo_valu);
        return -1;
    }
    printf("echoValu:|%s|\n", echoValu.c_str());
    //
    printf("LevFPEchoObje PASSED!\n");
    return 0;
}

int LevFPEcho(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPEcho\n");
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    // 得到数据库第４层空间对象
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP ERROR!\n");
        return -1;
    }
    //
    if (LevFPEchoObje(earthLevFP))
        printf("LevFPEchoObje ERROR!\n");
    // printf("--------------------------\n");
    return 0x00;
}
