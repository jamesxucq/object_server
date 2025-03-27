
#include "../earth_lv2p/EarthLvtpHeader.h"

#include "LevFP_Search.h"

static int LevFPSearchObje(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPSearchObje\n");
    // template <class T> int Search(vector <T *> &searVecto, const string &contName);
    // template <class T> int Search(vector <T *> &searVecto, const string &contName, const string &prediStri);
    vector <earth::lev2p::txxt *> searVecto;
    int searc_valu = earthLevFP.Search(searVecto, "txxt_con");
    if (searc_valu) {
        printf("earthLevFP Search ERROR! searc_valu:%08X\n", searc_valu);
        return -1;
    }
    //
    printf("LevFPSearchObje PASSED!\n");
    return 0;
}

int LevFPSearch(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPSearch\n");
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    // 得到数据库第４层空间对象
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP ERROR!\n");
        return -1;
    }
    //
    if (LevFPSearchObje(earthLevFP))
        printf("LevFPSearchObje ERROR!\n");
    // printf("--------------------------\n");
    return 0x00;
}
