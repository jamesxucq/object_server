
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

static int LevFPInvokeObje(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPInvokeObje\n");
    // template <class T> int Invoke(T &invoObje, const string &contName, string &invokStri);
    // template <class T> int Invoke(vector <T *> &invoVecto, const string &contName, string &invokStri);
    // template <class T> int Invoke(vector <T *> &invoVecto, const string &contName, string &invokStri, const string &prediStri);
    osv_oid_t invokOBID;
    stroid(&invokOBID, (char *) "fbff3655c2b5e66501000000");
    vector <IRKeyVal::RTypInt32 *> ivkRVecto;
    // 调用"txxt_con"这个容器里符合条件的对象的"tpp(11111111, 222)"方法,
    // 返回i值放ivkRVecto里
    int invo_valu = earthLevFP.Invoke(ivkRVecto, "txxt_con", "tpp(11111111, 222)");
    if (invo_valu) {
        printf("earthLevFP Invoke ERROR! invo_valu:%08X\n", invo_valu);
        return -1;
    }
    EntitKits::ClearVecto(ivkRVecto);
    //
    printf("LevFPInvokeObje PASSED!\n");
    return 0;
}

int LevFPInvoke(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPInvoke\n");
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    // 得到数据库第４层空间对象
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP ERROR!\n");
        return -1;
    }
    //
    printf("-------------------------- LevFPInvokeObje\n");
    if (LevFPInvokeObje(earthLevFP))
        printf("LevFPInvokeObje ERROR!\n");
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
    printf("********************************* [FUNC]:LevFPInvoke\n");
    LevFPInvoke(vmwaConne);
    printf("********************************* END\n");
    //
    return 0;
}

