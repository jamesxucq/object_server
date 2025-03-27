
#include "../earth_lv2p/EarthLvtpHeader.h"

#include "LevTh_Invoke.h"

static int LevThInvokeObje(Contain &inteContain) {
    printf("[FUNC]:LevThInvokeObje\n");
    // template <class T> int Invoke(T &invoObje, const string &invokStri);
    // template <class T> int Invoke(vector <T *> &invoVecto, const string &invokStri);
    // template <class T> int Invoke(vector <T *> &invoVecto, const string &invokStri, const string &prediStri);
    // string prediStri = "ECHO";
    osv_oid_t invokOBID;
    stroid(&invokOBID, (char *) "fbff3655c2b5e66501000000");
    IRKeyVal::RTypInt32 ivkRObje;
    int invo_valu = inteContain.Invoke(ivkRObje, "tpp(1111111, 22)", invokOBID);
    if (invo_valu) {
        printf("Contain Invoke ERROR! invo_valu:%d\n", invo_valu);
        return -1;
    }
    //
    printf("LevThInvokeObje PASSED!\n");
    return 0;
}

//

int LevThInvoke(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThInvoke\n");
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
    if (LevThInvokeObje(txxtContain))
        printf("LevThInvokeObje ERROR!\n");
    // printf("--------------------------\n");
    return 0x00;
}