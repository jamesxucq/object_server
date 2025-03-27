
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

static int LevFPInsertAttri(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPInsertAttri\n");
    // template <class T> int Insert(const string &contName, vector <T *> &inserVecto);
    // vector <earth::lev2p::txxt *> inserVecto;
    const string contName = "txxt_con";
    string attri = "xxxx";
    string value = "xxxx";
    // 给contain对象插入一个新属性.
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
    // 给contain对象插入一个新的本地对象，修改本地对象的obid，使其关联数据库里的对象
    int inser_valu = earthLevFP.Insert(contName, inserObje);
    if (inser_valu) {
        printf("earthLevFP Insert ERROR! inser_valu:%08X\n", inser_valu);
        return -1;
    }
    //
    printf("--------------\n");
    printf("obid_stri:|%s|\n", oidstr(obid_stri, &inserObje.obje_obid));
    printf("inserObje.xx:%d\n", inserObje.xx);
    printf("inserObje.ax:%d\n", inserObje.ax);
    printf("inserObje.cx:%d\n", inserObje.cx);
    printf("--------------\n");
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
    printf("-------------------------- LevFPInsertAttri\n");
    if (LevFPInsertAttri(earthLevFP))
        printf("LevFPInsertAttri ERROR!\n");
    //
    printf("-------------------------- LevFPInsertObje\n");
    if (LevFPInsertObje(earthLevFP))
        printf("LevFPInsertObje ERROR!\n");
    printf("--------------------------\n");
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
    printf("********************************* [FUNC]:LevFPInsert\n");
    LevFPInsert(vmwaConne);
    printf("********************************* END\n");
    //
    return 0;
}


