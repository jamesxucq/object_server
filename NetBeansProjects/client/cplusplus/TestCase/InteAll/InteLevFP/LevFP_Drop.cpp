
#include "../earth_lv2p/EarthLvtpHeader.h"

#include "LevFP_Drop.h"

static int LevFPDropObje(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPDropObje\n");
    // int Drop(const string &contName);
    int drop_valu = earthLevFP.Drop("txxt_temp_con");
    if (drop_valu) {
        printf("earthLevFP Drop ERROR! drop_valu:%08X\n", drop_valu);
        return -1;
    }
    //
    printf("LevFPDropObje PASSED!\n");
    return 0;
}

int LevFPDrop(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPDrop\n");
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    // 得到数据库第４层空间对象
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP ERROR!\n");
        return -1;
    }
    //
    if (LevFPDropObje(earthLevFP))
        printf("LevFPDropObje ERROR!\n");
    // printf("--------------------------\n");
    return 0x00;
}