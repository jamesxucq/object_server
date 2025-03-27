
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

/*
static const struct stst_node quer_echo_dict[] = {
    {"ECHO", "0I"}, // ECHO
    {"ATTRIB", "1I"}, // ATTRIB
    {"STATIS", "2I"}, // STATIS
    {NULL, "INVA"}
};
 */

static int LevFPEchoObje(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPEchoObje\n");
    // int Echo(string &echoValu, const string &echoType);
    // int Echo(string &echoValu, const string &echoType, const string &contName);
    // int Echo(string &echoValu, const string &echoType, const osv_oid_t *conta_obid);
    string echoValu;
    //
    // 得到数据库的对象ID
    int echo_valu = earthLevFP.Echo(echoValu);
    if (echo_valu) {
        printf("earthLevFP Echo ERROR! echo_valu:%08X\n", echo_valu);
        return -1;
    }
    printf("echoValu:|%s|\n", echoValu.c_str());
    //
    printf("LevFPEchoObje PASSED!\n");
    return 0;
}

int LevFPEcho(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPEcho\n");
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    // 得到数据库第４层空间对象
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP ERROR!\n");
        return -1;
    }
    //
    if (LevFPEchoObje(earthLevFP))
        printf("LevFPEchoObje ERROR!\n");
    // printf("--------------------------\n");
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
    printf("********************************* [FUNC]:LevFPEcho\n");
    LevFPEcho(vmwaConne);
    printf("********************************* END\n");
    //
    return 0;
}
