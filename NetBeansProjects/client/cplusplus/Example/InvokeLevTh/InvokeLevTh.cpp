
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

static int LevThInvokeObje(Contain &inteContain) {
    printf("[FUNC]:LevThInvokeObje\n");
    // template <class T> int Invoke(T &invoObje, const string &invokStri);
    // template <class T> int Invoke(vector <T *> &invoVecto, const string &invokStri);
    // template <class T> int Invoke(vector <T *> &invoVecto, const string &invokStri, const string &prediStri);
    // string prediStri = "ECHO";
    osv_oid_t invokOBID;
    stroid(&invokOBID, (char *) "fbff3655c2b5e66501000000");
    IRKeyVal::RTypInt32 ivkRObje;
    // 调用inteContain这个容器里OBID为i"fbff3655c2b5e66501000000"的对象的"tpp(11111111, 222)"方法,
    // 返回值放ivkRObje里
    int invo_valu = inteContain.Invoke(ivkRObje, "tpp(1111111, 22)", invokOBID);
    if (invo_valu) {
        printf("Contain Invoke ERROR! invo_valu:%d\n", invo_valu);
        return -1;
    }
    //
    printf("LevThInvokeObje PASSED!\n");
    return 0;
}

//

int LevThInvoke(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThInvoke\n");
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
    printf("-------------------------- LevThInvokeObje\n");
    if (LevThInvokeObje(txxtContain))
        printf("LevThInvokeObje ERROR!\n");
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
    printf("********************************* [FUNC]:LevThInvoke\n");
    LevThInvoke(vmwaConne);
    printf("********************************* END\n");
    //
    return 0;
}

