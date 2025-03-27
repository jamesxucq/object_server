
#include "../earth_lv2p/EarthLvtpHeader.h"

#include "LevFP_Factory.h"

static int LevFPFactoryObje(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPFactoryObje\n");
    // template <class T> int Factory(vector <T *> &factoVecto, const string &contName);
    // template <class T> int Factory(vector <T *> &factoVecto, const string &contName, const string &prediStri);
    vector <earth::lev2p::txxt *> factoVecto;
    int factory_valu = earthLevFP.Factory(factoVecto, "txxt_con");
    if (factory_valu) {
        printf("earthLevFP Factory ERROR! factory_valu:%08X\n", factory_valu);
        return -1;
    }
    //
    printf("LevFPFactoryObje PASSED!\n");
    return 0;
}

static int LevFPFactoryRaw(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPFactoryRaw\n");
    // template <class T> int Factory(vector <T *> &factoVecto, const string &contName);
    // template <class T> int Factory(vector <T *> &factoVecto, const string &contName, const string &prediStri);
    resp_data_t query_resp;
    int factory_valu = earthLevFP.Factory(&query_resp, "<[xx int, ax int]>", "txxt_con");
    if (factory_valu) {
        printf("earthLevFP Factory ERROR! factory_valu:%08X\n", factory_valu);
        return -1;
    }
    //
    osv_oid_t obje_obid;
    int xx, ax;
    int deseValu;
    char obid_stri[OBJE_IDENTI_ZLEN];
    //
    PK_PACK_STREAM *pkps;
    EUTI_PKPS_OPEN(pkps, &query_resp, "oii");
    do {
        deseValu = UserKits::LoopDeseri(pkps, (char *) "oii", &obje_obid, &xx, &ax);
        if (!deseValu) {
            printf("|%s|%d|%d|\n", oidstr(obid_stri, &obje_obid), xx, ax);
        } else if (0x00 > deseValu) {
            printf("UserKits::LoopDeseri ERROR!\n");
            EUTI_PKPS_CLOSE(pkps);
            return -1;
        }
    } while (!deseValu);
    EUTI_PKPS_CLOSE(pkps);
    //
    printf("LevFPFactoryObje PASSED!\n");
    return 0;
}

// 

static int LevFPFactoryObjRaw(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPFactoryObjRaw\n");
    // template <class T> int Factory(vector <T *> &factoVecto, const string &contName);
    // template <class T> int Factory(vector <T *> &factoVecto, const string &contName, const string &prediStri);
    resp_data_t query_resp;
    int factory_valu = earthLevFP.Factory(&query_resp, "<[xx int, ax int]>", "txxt_con");
    if (factory_valu) {
        printf("earthLevFP Factory ERROR! factory_valu:%08X\n", factory_valu);
        return -1;
    }
    //
    osv_oid_t obje_obid;
    int xx, ax;
    int deseValu;
    char obid_stri[OBJE_IDENTI_ZLEN];
    //
    DeseRespo *xxp = new DeseRespo(&query_resp, "oii");
    //
    do {
        deseValu = xxp->LoopDeseri(&obje_obid, &xx, &ax);
        if (!deseValu) {
            printf("|%s|%d|%d|\n", oidstr(obid_stri, &obje_obid), xx, ax);
        } else if (0x00 > deseValu) {
            printf("DeseRespo::LoopDeseri ERROR!\n");
            delete xxp;
            return -1;
        }
    } while (!deseValu);
    //
//    printf("xxxxxxxxxxxxx!\n");
//    xxp->Reset();
//    do {
//        deseValu = xxp->LoopDeseri(&obje_obid, &xx, &ax);
//        if (!deseValu) {
//            printf("|%s|%d|%d|\n", oidstr(obid_stri, &obje_obid), xx, ax);
//        } else if (0x00 > deseValu) {
//            printf("DeseRespo::LoopDeseri ERROR!\n");
//            delete xxp;
//            return -1;
//        }
//    } while (!deseValu);
    //
    delete xxp;
    //
    printf("LevFPFactoryObje PASSED!\n");
    return 0;
}

//

int LevFPFactory(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPFactory\n");
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    // 得到数据库第４层空间对象
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP ERROR!\n");
        return -1;
    }
    //
    //    if (LevFPFactoryObje(earthLevFP))
    //        printf("LevFPFactoryObje ERROR!\n");
    // printf("--------------------------\n");
    //    if (LevFPFactoryRaw(earthLevFP))
    //        printf("LevFPFactoryObje ERROR!\n");
    // printf("--------------------------\n");
    if (LevFPFactoryObjRaw(earthLevFP))
        printf("LevFPFactoryObje ERROR!\n");
    // printf("--------------------------\n")
    //
    return 0x00;
}
