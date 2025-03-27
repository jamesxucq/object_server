
#include "../earth_lv2p/EarthLvtpHeader.h"

#include "LevTh_Drop.h"

static int LevThDropObje(Contain &inteContain) {
    printf("[FUNC]:LevThDropObje\n");
    // template <class T> int Drop(T &dropObje); // passed
    // template <class T> int Drop(vector <T *> &dropVecto);
    // int Drop(const string &prediStri);
    earth::lev2p::txxt deopObje;
    int drop_valu = inteContain.Drop(deopObje);
    if (drop_valu) {
        printf("Contain Drop ERROR! drop_valu:%08X\n", drop_valu);
        return -1;
    }
    //
    printf("LevThDropObje PASSED!\n");
    return 0;
}

//

int LevThDrop(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThDrop\n");
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
    if (LevThDropObje(txxtContain))
        printf("LevThDropObje ERROR!\n");
    // printf("--------------------------\n");
    return 0x00;
}