
/* 
 * File:   main.cpp
 * Author: james
 *
 * Created on 2025.2.17, PM 2:23
 */

#include <cstdlib>
using namespace std;

#include "../earth_lv2p/EarthLvtpHeader.h"

//
#define USER_NAME "dev1"
#define PASSWORD "123abc"
#define IP_ADDRESS "127.0.0.1"
#define PORT 8848
#define BASE_NAME "earth"

//
// int Insert(osv_oid_t *pNewOBID, const string &objeStri); // checked

static int LevThInsertStri(Contain &inteContain) {
    printf("[FUNC]:LevThInsertStri\n");
    osv_oid_t newOBID;
    char obid_stri[OBJE_IDENTI_ZLEN];
    printf("old OBID:|%s|\n", oidstr(obid_stri, &newOBID));
    // 以文本方式在数据库的"txxt_con"容器里插入一个对象，并返回obid
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
    char obid_stri[OBJE_IDENTI_ZLEN];
    printf("old OBID:|%s|\n", oidstr(obid_stri, &inserObje.obje_obid));
    //
    // 本地构造一个对象，在数据库的"txxt_con"容器里插入这个对象，
    // 并修改本地对象的obid，使其关联数据库里的对象
    int inser_valu = inteContain.Insert(inserObje);
    if (inser_valu) {
        printf("Contain Insert ERROR! inser_valu:%08X\n", inser_valu);
        return -1;
    }
    printf("new OBID:|%s|\n", oidstr(obid_stri, &inserObje.obje_obid));
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
    // 本地构造一个对象的vector，在数据库的"txxt_con"容器里插入这个vector，
    // 并修改本地vector里对象的obid，使其关联数据库里的对象
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
    // 得到一个３层容器对象
    if (earthLevFP.GetContain(txxtContain, "txxt_con")) {
        printf("BASELevFP GetContain ERROR!\n");
        return -1;
    }
    //
    printf("-------------------------- LevThInsertStri\n");
    if (LevThInsertStri(txxtContain))
        printf("LevThInsertStri ERROR!\n");
    printf("-------------------------- LevThInsertObje\n");
    if (LevThInsertObje(txxtContain))
        printf("LevThInsertObje ERROR!\n");
    printf("-------------------------- LevThInsertVecto\n");
    if (LevThInsertVecto(txxtContain))
        printf("LevThInsertVecto ERROR!\n");
    printf("--------------------------\n");
    //
    return 0x00;
}

/*
 * 
 */
int main(int argc, char** argv) {
    printf("********************************* [FUNC]:main\n");
    // txxt类的版本号
    printf("clVersion:|%llu|\n", earth::lev2p::txxt::clVersion);
    // 本地检测服务器txxt类的属性变化计数
    printf("suChkAttribCount:|%u|\n", earth::lev2p::txxt::suChkAttribCount);
    // 构建一个服务器连接
    OSEVConne vmwaConne(USER_NAME, PASSWORD, IP_ADDRESS, PORT, BASE_NAME);
    printf("OSEVConne USER_NAME:  %s\n", USER_NAME);
    printf("          PASSWORD:   %s\n", PASSWORD);
    printf("          IP_ADDRESS: %s:%d\n", IP_ADDRESS, PORT);
    printf("          BASE_NAME:  %s\n", BASE_NAME);
    printf("********************************* [FUNC]:LevThInsert\n");
    LevThInsert(vmwaConne);
    printf("********************************* END\n");
    //
    return 0;
}

