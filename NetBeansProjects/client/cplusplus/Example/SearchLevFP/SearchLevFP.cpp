
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

void print_tobje_line(earth::lev2p::txxt &prinObje) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    printf("|%s|%d|%d|%d|\n", oidstr(obid_stri, &prinObje.obje_obid), prinObje.xx, prinObje.ax, prinObje.cx);
}

static int LevFPSearchObje(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPSearchObje\n");
    // template <class T> int Search(vector <T *> &searVecto, const string &contName);
    // template <class T> int Search(vector <T *> &searVecto, const string &contName, const string &prediStri);
    vector <earth::lev2p::txxt *> searVecto;
    // 查询容器里"txxt_con"符合条件的对象，并返回
    int searc_valu = earthLevFP.Search(searVecto, "txxt_con");
    if (searc_valu) {
        printf("earthLevFP Search ERROR! searc_valu:%08X\n", searc_valu);
        return -1;
    }
    //
    vector <earth::lev2p::txxt *>::iterator iter;
    for (iter = searVecto.begin(); iter != searVecto.end(); ++iter) {
        // delete (*iter);
        print_tobje_line(**iter);
    }
    // 销毁返回的本地对象
    EntitKits::ClearVecto(searVecto);
    //
    printf("LevFPSearchObje PASSED!\n");
    return 0;
}

int LevFPSearch(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPSearch\n");
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    // 得到数据库第４层空间对象
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP ERROR!\n");
        return -1;
    }
    //
    printf("-------------------------- LevFPSearchObje\n");
    if (LevFPSearchObje(earthLevFP))
        printf("LevFPSearchObje ERROR!\n");
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
    printf("********************************* [FUNC]:LevFPSearch\n");
    LevFPSearch(vmwaConne);
    printf("********************************* END\n");
    //
    return 0;
}


