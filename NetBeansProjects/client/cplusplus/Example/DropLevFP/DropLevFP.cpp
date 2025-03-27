
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

static int LevFPDropObje(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPDropObje\n");
    // int Drop(const string &contName);
    //　在数据库第４层空间里，销毁名为"txxt_temp_con"的容器对象
    int drop_valu = earthLevFP.Drop("txxt_temp_con");
    if (drop_valu) {
        printf("earthLevFP Drop ERROR! drop_valu:%08X\n", drop_valu);
        return -1;
    }
    //
    printf("LevFPDropObje PASSED!\n");
    return 0;
}

int LevFPDrop(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPDrop\n");
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    // 得到数据库第４层空间对象
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP ERROR!\n");
        return -1;
    }
    //
    if (LevFPDropObje(earthLevFP))
        printf("LevFPDropObje ERROR!\n");
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
    printf("********************************* [FUNC]:LevFPDrop\n");
    LevFPDrop(vmwaConne);
    printf("********************************* END\n");
    //
    return 0;
}

