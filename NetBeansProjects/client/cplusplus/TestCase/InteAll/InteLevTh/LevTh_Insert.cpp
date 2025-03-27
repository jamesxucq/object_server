
#include "../earth_lv2p/EarthLvtpHeader.h"

#include "LevTh_Insert.h"

// int Insert(osv_oid_t *pNewOBID, const string &objeStri); // checked

static int LevThInsertStri(Contain &inteContain) {
    printf("[FUNC]:LevThInsertStri\n");
    osv_oid_t newOBID;
    char obid_stri[OBJE_IDENTI_ZLEN];
    printf("old OBID:|%s|\n", oidstr(obid_stri, &newOBID));
    int inser_valu = inteContain.Insert(newOBID, "Func:Stroid(INVAL), 3333333, 22, 11");
    if (inser_valu) {
        printf("Contain Insert ERROR! inser_valu:%08X\n", inser_valu);
        return -1;
    }
    printf("new OBID:|%s|\n", oidstr(obid_stri, &newOBID));
    //
    printf("LevThInsertStri PASSED!\n");
    return 0;
}

// template <class T> int Insert(T &inserObje); // checked

static int LevThInsertObje(Contain &inteContain) {
    printf("[FUNC]:LevThInsertObje\n");
    earth::lev2p::txxt inserObje(1, 1, 1);
    int inser_valu = inteContain.Insert(inserObje);
    if (inser_valu) {
        printf("Contain Insert ERROR! inser_valu:%08X\n", inser_valu);
        return -1;
    }
    //
    printf("LevThInsertObje PASSED!\n");
    return 0;
}

// template <class T> int Insert(vector <T *> &inserVecto); // checked

static int LevThInsertVecto(Contain &inteContain) {
    printf("[FUNC]:LevThInsertVecto\n");
    vector <earth::lev2p::txxt *> inserVecto;
    earth::lev2p::txxt inserObje(33621, 33667, 33645);
    inserVecto.push_back(&inserObje);
    //
    int inser_valu = inteContain.Insert(inserVecto);
    if (inser_valu) {
        printf("Contain Insert ERROR! inser_valu:%08X\n", inser_valu);
        return -1;
    }
    //
    printf("LevThInsertVecto PASSED!\n");
    return 0;
}

//

int LevThInsert(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThInsert\n");
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
    //        if (LevThInsertStri(txxtContain))
    //            printf("LevThInsertStri ERROR!\n");
    printf("--------------------------\n");
    if (LevThInsertObje(txxtContain))
        printf("LevThInsertObje ERROR!\n");
    /*
        printf("--------------------------\n");
        if (LevThInsertVecto(txxtContain))
            printf("LevThInsertVecto ERROR!\n");
     */
    //
    return 0x00;
}

