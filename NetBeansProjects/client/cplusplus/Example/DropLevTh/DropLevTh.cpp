
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

void print_tobje_colum(earth::lev2p::txxt &prinObje) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    printf("--------------------------- [FUNC]:print_txxt_obje\n");
    printf("obje:obje_obid %s\n", oidstr(obid_stri, &prinObje.obje_obid));
    printf("obje:xx %d\n", prinObje.xx);
    printf("obje:ax %d\n", prinObje.ax);
    printf("obje:cx %d\n", prinObje.cx);
}

static int LevThDropObje(Contain &inteContain) {
    printf("[FUNC]:LevThDropObje\n");
    //
    earth::lev2p::txxt dropObje;
    print_tobje_colum(dropObje);
    //　在inteContain这个容器里，用这些"(111, 122, 133)"创建一个对象，
    // 并把对象值返回给creatObje这个本地对象
    int creat_valu = inteContain.Create(dropObje, "(111, 122, 133)");
    if (creat_valu) {
        printf("Contain Create ERROR! creat_valu:%08X\n", creat_valu);
        return -1;
    }
    print_tobje_colum(dropObje);
    // template <class T> int Drop(T &dropObje); // passed
    // template <class T> int Drop(vector <T *> &dropVecto);
    // int Drop(const string &prediStri);
    // 把在inteContain这个容器里，创建的对象删除，
    int drop_valu = inteContain.Drop(dropObje);
    if (drop_valu) {
        printf("Contain Drop ERROR! drop_valu:%08X\n", drop_valu);
        return -1;
    }
    //
    printf("LevThDropObje PASSED!\n");
    return 0;
}

//

int LevThDrop(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThDrop\n");
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
    if (LevThDropObje(txxtContain))
        printf("LevThDropObje ERROR!\n");
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
    printf("********************************* [FUNC]:LevThDrop\n");
    LevThDrop(vmwaConne);
    printf("********************************* END\n");
    //
    return 0;
}

