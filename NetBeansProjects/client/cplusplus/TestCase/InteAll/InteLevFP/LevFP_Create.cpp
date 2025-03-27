
#include "../earth_lv2p/EarthLvtpHeader.h"

#include "LevFP_Create.h"

static int LevFPCreateObje(BASELevFP &earthLevFP) {
    // int Create(const string &contName, const string &lv2pName, string &storaType);
    int creat_valu = earthLevFP.Create("txxt_temp_con", "witi", "txxt");
    if (creat_valu) {
        printf("earthLevFP Create ERROR! creat_valu:%08X\n", creat_valu);
        return -1;
    }
    //
    printf("LevFPCreateObje PASSED!\n");
    return 0;
}

int LevFPCreate(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPCreate\n");
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    // 得到数据库第４层空间对象
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP ERROR!\n");
        return -1;
    }
    //
    if (LevFPCreateObje(earthLevFP))
        printf("LevFPCreateObje ERROR!\n");
    // printf("--------------------------\n");
    return 0x00;
}