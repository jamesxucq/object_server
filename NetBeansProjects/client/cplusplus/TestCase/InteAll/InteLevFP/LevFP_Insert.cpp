
#include "../earth_lv2p/EarthLvtpHeader.h"

#include "LevFP_Insert.h"

static int LevFPInsertAttri(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPInsertAttri\n");
    // template <class T> int Insert(const string &contName, vector <T *> &inserVecto);
    // vector <earth::lev2p::txxt *> inserVecto;
    const string contName = "txxt_con";
    string attri = "xxxx";
    string value = "xxxx";
    int inser_valu = earthLevFP.Insert(contName, attri, value);
    if (inser_valu) {
        printf("earthLevFP Insert ERROR! inser_valu:%08X\n", inser_valu);
        return -1;
    }
    //
    printf("LevFPInsertObje PASSED!\n");
    return 0;
}

static int LevFPInsertObje(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPInsertObje\n");
    // template <class T> int Insert(const string &contName, vector <T *> &inserVecto);
    // vector <earth::lev2p::txxt *> inserVecto;
    const string contName = "txxt_con";
    earth::lev2p::txxt inserObje(4, 2, 3);
    printf("--------------\n");
    char obid_stri[33];
    printf("obid_stri:|%s|\n", oidstr(obid_stri, &inserObje.obje_obid));
    printf("inserObje.xx:%d\n", inserObje.xx);
    printf("inserObje.ax:%d\n", inserObje.ax);
    printf("inserObje.cx:%d\n", inserObje.cx);
    printf("--------------\n");
    printf("xxxxxxxxxxx\n");
    int inser_valu = earthLevFP.Insert(contName, inserObje);
    if (inser_valu) {
        printf("earthLevFP Insert ERROR! inser_valu:%08X\n", inser_valu);
        return -1;
    }
    //
    printf("LevFPInsertObje PASSED!\n");
    return 0;
}

int LevFPInsert(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPInsert\n");
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    // 得到数据库第４层空间对象
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP ERROR!\n");
        return -1;
    }
    //
    // if (LevFPInsertAttri(earthLevFP))
    // printf("LevFPInsertAttri ERROR!\n");
    // printf("--------------------------\n");
    //
    if (LevFPInsertObje(earthLevFP))
        printf("LevFPInsertObje ERROR!\n");
    // printf("--------------------------\n");
    return 0x00;
}