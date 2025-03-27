
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

static int LevFPCreateObje(BASELevFP &earthLevFP) {
    // int Create(const string &contName, const string &lv2pName, string &storaType);
    // 在数据库第４层空间里，创造一个存储名为"txxt_temp_con"的容器对象，
    // 用来存储"txxt"这种类型的对象，用"witi"这种存储引擎
    int creat_valu = earthLevFP.Create("txxt_temp_con", "witi", "txxt");
    if (creat_valu) {
        printf("earthLevFP Create ERROR! creat_valu:%08X\n", creat_valu);
        return -1;
    }
    //
    printf("LevFPCreateObje PASSED!\n");
    return 0;
}

int LevFPCreate(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPCreate\n");
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    // 得到数据库第４层空间对象
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP ERROR!\n");
        return -1;
    }
    //
    if (LevFPCreateObje(earthLevFP))
        printf("LevFPCreateObje ERROR!\n");
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
    printf("********************************* [FUNC]:LevFPCreate\n");
    LevFPCreate(vmwaConne);
    printf("********************************* END\n");
    //
    return 0;
}


