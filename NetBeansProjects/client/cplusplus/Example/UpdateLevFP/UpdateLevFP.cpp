
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

static int LevFPUpdateVecto(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPUpdateVecto\n");
    osv_oid_t obje_obid;
    stroid(&obje_obid, (char *) "fbff3655efaff76501000000");
    earth::lev2p::txxt updatObje(obje_obid, 23, 22, 21);
    //
    // template <class T> int Update(const string &contName, vector <T *> &updatVecto);
    vector <earth::lev2p::txxt *> updatVecto;
    updatVecto.push_back(&updatObje);
    // 更新updatVecto的对象数据
    int updat_valu = earthLevFP.Update("txxt_con", updatVecto);
    if (updat_valu) {
        printf("earthLevFP Update ERROR! updat_valu:%08X\n", updat_valu);
        return -1;
    }
    // EntitKits::ClearVecto(updatVecto);
    printf("LevFPUpdateObje PASSED!\n");
    return 0;
}

static int LevFPUpdateObje(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPUpdateObje\n");
    // template <class T> int Update(const string &contName, vector <T *> &updatVecto);
    osv_oid_t obje_obid;
    stroid(&obje_obid, (char *) "fbff3655efaff76501000000");
    earth::lev2p::txxt updatObje(obje_obid, 3, 2, 1);
    //
    // 更新OBID为"fbff3655efaff76501000000"的对象数据
    int updat_valu = earthLevFP.Update("txxt_con", updatObje);
    if (updat_valu) {
        printf("earthLevFP Update ERROR! updat_valu:%08X\n", updat_valu);
        return -1;
    }
    //
    printf("LevFPUpdateObje PASSED!\n");
    return 0;
}

//

int LevFPUpdate(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPUpdate\n");
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    // 得到数据库第４层空间对象
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP ERROR!\n");
        return -1;
    }
    //
    printf("-------------------------- LevFPUpdateObje\n");
    if (LevFPUpdateObje(earthLevFP))
        printf("LevFPUpdateObje ERROR!\n");
    printf("-------------------------- LevFPUpdateVecto\n");
    if (LevFPUpdateVecto(earthLevFP))
        printf("LevFPUpdateVecto ERROR!\n");
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
    printf("********************************* [FUNC]:LevFPUpdate\n");
    LevFPUpdate(vmwaConne);
    printf("********************************* END\n");
    //
    return 0;
}


