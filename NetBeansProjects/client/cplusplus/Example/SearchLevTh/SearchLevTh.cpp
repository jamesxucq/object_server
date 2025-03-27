
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

static int LevThSearchObje(Contain &inteContain) {
    printf("[FUNC]:LevThSearchObje\n");
    // template <class T> int Search(T &searObje); // passed
    // template <class T> int Search(T &searObje, const string &prediStri); // passed
    // template <class T> int Search(vector <T *> &searVecto); // passed
    // template <class T> int Search(vector <T *> &searVecto, const string &prediStri); // passed
    // string prediStri = "ECHO";
    earth::lev2p::txxt searObje;
    // 查询容器里"txxt_con"符合条件的对象，并返回
    int searc_valu = inteContain.Search(searObje);
    if (searc_valu) {
        printf("Contain Search ERROR! searc_valu:%08X\n", searc_valu);
        return -1;
    }
    //
    printf("LevThSearchObje PASSED!\n");
    return 0;
}

static int LevThSearVecto(Contain &inteContain) {
    printf("[FUNC]:LevThSearVecto\n");
    printf("Contain Search start.\n");
    vector <earth::lev2p::txxt *> searVector;
    string PrediStri = "*";
    printf("inteContain.Search\n");
    //　查询容器里"txxt_con"符合条件的对象，并返回
    if (inteContain.Search(searVector, PrediStri)) {
        printf("Contain Search ERROR!\n");
        return -1;
    }
    //
    char temp[33];
    printf("Contain Search ok.\n");
    vector <earth::lev2p::txxt *>::iterator iter;
    for (iter = searVector.begin(); iter != searVector.end(); ++iter) {
        printf("|%s|%d|%d|%d|\n", oidstr(temp, &(*iter)->obje_obid), (*iter)->xx, (*iter)->ax, (*iter)->cx);
    }
    EntitKits::ClearVecto(searVector);
    //
    printf("LevThSearVecto PASSED!\n");
    return 0;
}

//

int LevThSearch(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThSearch\n");
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
    printf("-------------------------- LevThSearchObje\n");
    if (LevThSearchObje(txxtContain))
        printf("LevThSearchObje ERROR!\n");
    printf("-------------------------- LevThSearVecto\n");
    if (LevThSearVecto(txxtContain))
        printf("LevThSearVecto ERROR!\n");
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
    printf("********************************* [FUNC]:LevThSearch\n");
    LevThSearch(vmwaConne);
    printf("********************************* END\n");
    //
    return 0;
}

