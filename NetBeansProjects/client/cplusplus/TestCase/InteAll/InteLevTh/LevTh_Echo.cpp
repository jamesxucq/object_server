
#include "../earth_lv2p/EarthLvtpHeader.h"

#include "LevTh_Echo.h"

 //

static int LevThEchoObje(Contain &inteContain) {
    printf("[FUNC]:LevThEchoObje\n");
    // int Echo(string &echoValu, const string &echoType);
    string echoValu;
    int echo_valu = inteContain.Echo(echoValu);
    if (echo_valu) {
        printf("Contain Echo ERROR! echo_valu:%08X\n", echo_valu);
        return -1;
    }
    printf("echoValu:|%s|\n", echoValu.c_str());
    //
    printf("LevThEchoObje PASSED!\n");
    return 0;
}

//

int LevThEcho(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThEcho\n");
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    // 得到数据库第４层空间对象
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP ERROR!\n");
        return -1;
    }
    //
    Contain txxtContain;
    printf("earthLevFP.GetContain\n");
    if (earthLevFP.GetContain(txxtContain, "txxt_con")) {
        printf("BASELevFP GetContain ERROR!\n");
        return -1;
    }
    //
    if (LevThEchoObje(txxtContain))
        printf("LevThEchoObje ERROR!\n");
    // printf("--------------------------\n");
    return 0x00;
}