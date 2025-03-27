
#include "../earth_lv2p/EarthLvtpHeader.h"

#include "LevTh_Create.h"

static int LevThCreateObje(Contain &inteContain) {
    printf("[FUNC]:LevThCreateObje\n");
    // int Create(const string &lv2pName, const string &params);
    // earth::lev2p::txxt deopObje;
    int creat_valu = inteContain.Create("(11, 22, 33)");
    if (creat_valu) {
        printf("Contain Create ERROR! creat_valu:%08X\n", creat_valu);
        return -1;
    }
    //
    earth::lev2p::txxt creatObje;
    creat_valu = inteContain.Create(creatObje, "(11, 22, 33)");
    if (creat_valu) {
        printf("Contain Create ERROR! creat_valu:%08X\n", creat_valu);
        return -1;
    }
    //
    printf("LevThCreateObje PASSED!\n");
    return 0;
}

//

int LevThCreate(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThCreate\n");
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
    if (LevThCreateObje(txxtContain))
        printf("LevThCreateObje ERROR!\n");
    // printf("--------------------------\n");
    return 0x00;
}