
#include "../earth_lv2p/EarthLvtpHeader.h"

#include "LevFP_Update.h"

static int LevFPUpdateVecto(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPUpdateVecto\n");
    // template <class T> int Update(const string &contName, vector <T *> &updatVecto);
    vector <earth::lev2p::txxt *> updatVecto;
    int updat_valu = earthLevFP.Update("txxt_con", updatVecto);
    if (updat_valu) {
        printf("earthLevFP Update ERROR! updat_valu:%08X\n", updat_valu);
        return -1;
    }
    //
    printf("LevFPUpdateObje PASSED!\n");
    return 0;
}

static int LevFPUpdateObje(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPUpdateObje\n");
    // template <class T> int Update(const string &contName, vector <T *> &updatVecto);
    osv_oid_t obje_obid;
    stroid(&obje_obid, (char *) "fbff3655efaff76501000000");
    earth::lev2p::txxt updatObje(obje_obid, 3, 2, 1);
    //
    int updat_valu = earthLevFP.Update("txxt_con", updatObje);
    if (updat_valu) {
        printf("earthLevFP Update ERROR! updat_valu:%08X\n", updat_valu);
        return -1;
    }
    //
    printf("LevFPUpdateObje PASSED!\n");
    return 0;
}

//

int LevFPUpdate(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPUpdate\n");
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    // 得到数据库第４层空间对象
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP ERROR!\n");
        return -1;
    }
    //
    printf("--------------------------\n");
    if (LevFPUpdateObje(earthLevFP))
        printf("LevFPUpdateObje ERROR!\n");
    printf("--------------------------\n");
    //    if (LevFPUpdateVecto(earthLevFP))
    //        printf("LevFPUpdateVecto ERROR!\n");
    //    printf("--------------------------\n");
    //
    return 0x00;
}
