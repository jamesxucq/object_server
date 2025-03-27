
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
// fbff3655688ce66502000000
// fbff3655688ce66502000000

static int LevThUpdateStri(Contain &inteContain) {
    printf("[FUNC]:LevThUpdateStri\n");
    // template <class T> int Update(T &updatObje); // passed
    // template <class T> int Update(vector <T *> &updatVecto);
    // 更新OBID为"fbff3655c2b5e66501000000"的对象数据
    int updat_valu = inteContain.Update("Func:Stroid(\"fbff3655c2b5e66501000000\"), 2111111, 212, 212");
    if (updat_valu) {
        printf("Contain Update ERROR! updat_valu:%08X\n", updat_valu);
        return -1;
    }
    // 更新OBID为"fbff3655c2b5e66501000001的对象数据
    string updat_osl = "Func:Stroid(\"fbff3655c2b5e66501000001\"), 12111, 212, 212";
    updat_valu = inteContain.Update(updat_osl);
    if (updat_valu) {
        printf("Contain Update ERROR! updat_valu:%08X\n", updat_valu);
        return -1;
    }
    //
    printf("LevThUpdateObje PASSED!\n");
    return 0;
}

static int LevThUpdateObje(Contain &inteContain) {
    printf("[FUNC]:LevThUpdateObje\n");
    char temp[33];
    earth::lev2p::txxt updatObje;
    // template <class T> int Update(T &updatObje); // passed
    // template <class T> int Update(vector <T *> &updatVecto);
    // 构造OBID为fbff3655c2b5e66501000001的对象
    stroid(&updatObje.obje_obid, (char *) "fbff3655c2b5e66501000000");
    updatObje.xx = 2111111;
    updatObje.ax = 212;
    updatObje.cx = 213;
    printf("|%s|%d|%d|%d|\n", oidstr(temp, &updatObje.obje_obid), updatObje.xx, updatObje.ax, updatObje.cx);
    printf("inteContain.Update\n");
    // 更新updatObje对象数据
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
    // 构造一个earth::lev2p::txxt测试对象
    // updatObje.Create(12, 34);
    // updatObje.obje_obid.osev_unique = earthLevFP.moOSEVClie.clie_obid.osev_unique;
    updatObje.obje_obid.time_stamp = 2;
    updatObje.obje_obid.counter = 2;
    updatObje.xx = 4;
    updatObje.ax = 5;
    updatObje.cx = 6;
    printf("|%s|%d|%d|%d|\n", oidstr(temp, &updatObje.obje_obid), updatObje.xx, updatObje.ax, updatObje.cx);
    printf("inteContain.Insert\n");
    //　把这个测试对象插入inteContain
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
    // 更新updatVecto里的对象数据
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
    txxtObje.ax = 199;
    txxtObje.cx = 122;
    printf("|%s|%d|%d|%d|\n", oidstr(temp, &txxtObje.obje_obid), txxtObje.xx, txxtObje.ax, txxtObje.cx);
    printf("inteContain.Update\n");
    if (inteContain.Update(txxtObje)) {
        printf("Contain Update ERROR!\n");
        return -1;
    }
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
    // 得到一个３层容器对象
    if (earthLevFP.GetContain(txxtContain, "txxt_con")) {
        printf("BASELevFP GetContain ERROR!\n");
        return -1;
    }
    //
    // LevThObjeInserUpdat
    printf("-------------------------- LevThObjeInserUpdat\n");
    if (LevThObjeInserUpdat(txxtContain))
        printf("LevThObjeInserUpdat ERROR!\n");
    // LevThUpdateObje
    printf("-------------------------- LevThUpdateStri\n");
    if (LevThUpdateStri(txxtContain))
        printf("LevThUpdateStri ERROR!\n");
    printf("-------------------------- LevThUpdateObje\n");
    if (LevThUpdateObje(txxtContain))
        printf("LevThUpdateObje ERROR!\n");
    printf("-------------------------- LevThUpdateVecto\n");
    if (LevThUpdateVecto(txxtContain))
        printf("LevThUpdateVecto ERROR!\n");
    //
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
    printf("********************************* [FUNC]:LevThUpdate\n");
    LevThUpdate(vmwaConne);
    printf("********************************* END\n");
    //
    return 0;
}
