
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

static int LevThCreateObje(Contain &inteContain) {
    printf("[FUNC]:LevThCreateObje\n");
    // int Create(const string &lv2pName, const string &params);
    // earth::lev2p::txxt deopObje;
    // 在inteContain这个容器里，用这些"(11, 22, 33)"创建一个对象
    int creat_valu = inteContain.Create("(11, 22, 33)");
    if (creat_valu) {
        printf("Contain Create ERROR! creat_valu:%08X\n", creat_valu);
        return -1;
    }
    //
    earth::lev2p::txxt creatObje;
    //　在inteContain这个容器里，用这些"(111, 122, 133)"创建一个对象，
    // 并把对象值返回给creatObje这个本地对象
    creat_valu = inteContain.Create(creatObje, "(111, 122, 133)");
    if (creat_valu) {
        printf("Contain Create ERROR! creat_valu:%08X\n", creat_valu);
        return -1;
    }
    //
    printf("LevThCreateObje PASSED!\n");
    return 0;
}

//

int LevThCreate(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThCreate\n");
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
    if (LevThCreateObje(txxtContain))
        printf("LevThCreateObje ERROR!\n");
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
    printf("********************************* [FUNC]:LevThCreate\n");
    LevThCreate(vmwaConne);
    printf("********************************* END\n");
    //
    return 0;
}

