
#include "../earth_lv2p/EarthLvtpHeader.h"

#include "LevFP_Invoke.h"

static int LevFPInvokeObje(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPInvokeObje\n");
    // template <class T> int Invoke(T &invoObje, const string &contName, string &invokStri);
    // template <class T> int Invoke(vector <T *> &invoVecto, const string &contName, string &invokStri);
    // template <class T> int Invoke(vector <T *> &invoVecto, const string &contName, string &invokStri, const string &prediStri);
    osv_oid_t invokOBID;
    stroid(&invokOBID, (char *) "fbff3655c2b5e66501000000");
    vector <IRKeyVal::RTypInt32 *> ivkRVecto;
    int invo_valu = earthLevFP.Invoke(ivkRVecto, "txxt_con", "tpp(11111111, 222)");
    if (invo_valu) {
        printf("earthLevFP Invoke ERROR! invo_valu:%08X\n", invo_valu);
        return -1;
    }
    //
    printf("LevFPInvokeObje PASSED!\n");
    return 0;
}

int LevFPInvoke(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPInvoke\n");
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    // 得到数据库第４层空间对象
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP ERROR!\n");
        return -1;
    }
    //
    if (LevFPInvokeObje(earthLevFP))
        printf("LevFPInvokeObje ERROR!\n");
    // printf("--------------------------\n");
    return 0x00;
}

