
#include "../earth_lv2p/EarthLvtpHeader.h"

#include "LevTh_Update.h"

// fbff3655688ce66502000000
// fbff3655688ce66502000000

static int LevThUpdateStri(Contain &inteContain) {
    printf("[FUNC]:LevThUpdateStri\n");
    // template <class T> int Update(T &updatObje); // passed
    // template <class T> int Update(vector <T *> &updatVecto);
    int updat_valu = inteContain.Update("Func:Stroid(\"fbff3655c2b5e66501000000\"), 2111111, 212, 212");
    if (updat_valu) {
        printf("Contain Update ERROR! updat_valu:%08X\n", updat_valu);
        return -1;
    }
    //
    /*
        string updat_osl = "Func:Stroid(\"fbff3655c2b5e66501000000\"), 2111111, 212, 212";
        int updat_valu = inteContain.Update(updat_osl);
        if (updat_valu) {
            printf("Contain Update ERROR! updat_valu:%08X\n", updat_valu);
            return -1;
        }
     */
    //
    printf("LevThUpdateObje PASSED!\n");
    return 0;
}

static int LevThUpdateObje(Contain &inteContain) {
    printf("[FUNC]:LevThUpdateObje\n");
    char temp[33];
    earth::lev2p::txxt updatObje;
    // updatObje.Create(12, 34);
    // updatObje.obje_obid.osev_unique = earthLevFP.moOSEVClie.clie_obid.osev_unique;
    /*
        updatObje.obje_obid.time_stamp = 2;
        updatObje.obje_obid.counter = 2;
        updatObje.xx = 211;
        updatObje.ax = 212;
        updatObje.cx = 213;
        printf("|%s|%d|%d|%d|\n", oidstr(temp, &updatObje.obje_obid), updatObje.xx, updatObje.ax, updatObje.cx);
        printf("inteContain.Insert\n");
        if (inteContain.Insert(updatObje)) {
            printf("Contain Insert ERROR!\n");
            return -1;
        }
        printf("updatObje.obje_obid:|%s|\n", oidstr(temp, &updatObje.obje_obid));
     */
    //
    // template <class T> int Update(T &updatObje); // passed
    // template <class T> int Update(vector <T *> &updatVecto);
    stroid(&updatObje.obje_obid, (char *) "fbff3655c2b5e66501000000");
    updatObje.xx = 2111111;
    updatObje.ax = 212;
    updatObje.cx = 213;
    printf("|%s|%d|%d|%d|\n", oidstr(temp, &updatObje.obje_obid), updatObje.xx, updatObje.ax, updatObje.cx);
    printf("inteContain.Update\n");
    int updat_valu = inteContain.Update(updatObje);
    if (updat_valu) {
        printf("Contain Update ERROR! updat_valu:%08X\n", updat_valu);
        return -1;
    }
    //
    printf("LevThUpdateObje PASSED!\n");
    return 0;
}

static int LevThUpdateVecto(Contain &inteContain) {
    printf("[FUNC]:LevThUpdateVecto\n");
    char temp[33];
    earth::lev2p::txxt updatObje;
    // updatObje.Create(12, 34);
    // updatObje.obje_obid.osev_unique = earthLevFP.moOSEVClie.clie_obid.osev_unique;
    updatObje.obje_obid.time_stamp = 2;
    updatObje.obje_obid.counter = 2;
    updatObje.xx = 4;
    updatObje.ax = 5;
    updatObje.cx = 6;
    printf("|%s|%d|%d|%d|\n", oidstr(temp, &updatObje.obje_obid), updatObje.xx, updatObje.ax, updatObje.cx);
    printf("inteContain.Insert\n");
    if (inteContain.Insert(updatObje)) {
        printf("Contain Insert ERROR!\n");
        return -1;
    }
    //
    // template <class T> int Update(T &updatObje); // passed
    // template <class T> int Update(vector <T *> &updatVecto);
    updatObje.ax = 15;
    updatObje.cx = 16;
    printf("|%s|%d|%d|%d|\n", oidstr(temp, &updatObje.obje_obid), updatObje.xx, updatObje.ax, updatObje.cx);
    printf("inteContain.Update\n");
    vector <earth::lev2p::txxt *> updatVecto;
    updatVecto.push_back(&updatObje);
    int updat_valu = inteContain.Update(updatVecto);
    if (updat_valu) {
        printf("Contain Update ERROR! updat_valu:%08X\n", updat_valu);
        return -1;
    }
    //
    printf("LevThUpdateObje PASSED!\n");
    return 0;
}

// vector test

static int LevThObjeInserUpdat(Contain &inteContain) {
    printf("[FUNC]:LevThObjeInserUpdat\n");
    char temp[33];
    earth::lev2p::txxt txxtObje;
    // txxtObje.Create(12, 34);
    // txxtObje.obje_obid.osev_unique = earthLevFP.moOSEVClie.clie_obid.osev_unique;
    txxtObje.obje_obid.time_stamp = 2;
    txxtObje.obje_obid.counter = 2;
    txxtObje.xx = 133;
    txxtObje.ax = 199;
    txxtObje.cx = 122;
    printf("|%s|%d|%d|%d|\n", oidstr(temp, &txxtObje.obje_obid), txxtObje.xx, txxtObje.ax, txxtObje.cx);
    printf("inteContain.Insert\n");
    if (inteContain.Insert(txxtObje)) {
        printf("Contain Insert ERROR!\n");
        return -1;
    }
    printf("updatObje.obje_obid:|%s|\n", oidstr(temp, &txxtObje.obje_obid));
    //
    /*
        txxtObje.ax = 199;
        txxtObje.cx = 122;
        printf("|%s|%d|%d|%d|\n", oidstr(temp, &txxtObje.obje_obid), txxtObje.xx, txxtObje.ax, txxtObje.cx);
        printf("inteContain.Update\n");
        if (inteContain.Update(txxtObje)) {
            printf("Contain Update ERROR!\n");
            return -1;
        }
     */
    //
    printf("LevThObjeInserUpdat PASSED!\n");
    return 0;
}

int LevThUpdate(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThUpdate\n");
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
    // LevThObjeInserUpdat
    /*
        printf("--------------------------\n");
        if (LevThObjeInserUpdat(txxtContain))
            printf("LevThObjeInserUpdat ERROR!\n");
     */
    // LevThUpdateObje
    printf("--------------------------\n");
    if (LevThUpdateStri(txxtContain))
        printf("LevThUpdateStri ERROR!\n");

    /*
        printf("--------------------------\n");
        if (LevThUpdateObje(txxtContain))
            printf("LevThUpdateObje ERROR!\n");
     */
    /*
        printf("--------------------------\n");
        if (LevThUpdateVecto(txxtContain))
            printf("LevThUpdateVecto ERROR!\n");
     */
    //
    return 0x00;
}