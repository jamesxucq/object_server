
/* 
 * File:   main.cpp
 * Author: james
 *
 * Created on 2025.2.17, PM 2:23
 */

#include <cstdlib>
using namespace std;

#include <vector>
using std::vector;

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

static int LevFPFactoryObje(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPFactoryObje\n");
    // template <class T> int Factory(vector <T *> &factoVecto, const string &contName);
    // template <class T> int Factory(vector <T *> &factoVecto, const string &contName, const string &prediStri);
    // 用容器"txxt_con"里符合条件的对象，构造新的对象并返回ｉ
    vector <earth::lev2p::txxt *> factoVecto;
    int factory_valu = earthLevFP.Factory(factoVecto, "txxt_con");
    if (factory_valu) {
        printf("earthLevFP Factory ERROR! factory_valu:%08X\n", factory_valu);
        return -1;
    }
    //
    vector <earth::lev2p::txxt *>::iterator iter;
    for (iter = factoVecto.begin(); iter != factoVecto.end(); ++iter) {
        // delete (*iter);
        print_tobje_line(**iter);
    }
    // 销毁返回的本地对象
    EntitKits::ClearVecto(factoVecto);
    //
    printf("LevFPFactoryObje PASSED!\n");
    return 0;
}

static int LevFPFactoryRaw(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPFactoryRaw\n");
    // template <class T> int Factory(vector <T *> &factoVecto, const string &contName);
    // template <class T> int Factory(vector <T *> &factoVecto, const string &contName, const string &prediStri);
    resp_data_t query_resp;
    // 用容器"txxt_con"里符合条件的对象，以"<[xx int, ax int]>"类型，构造新的对象并返回ｉ
    int factory_valu = earthLevFP.Factory(&query_resp, "<[xx int, ax int]>", "txxt_con");
    if (factory_valu) {
        printf("earthLevFP Factory ERROR! factory_valu:%08X\n", factory_valu);
        return -1;
    }
    //
    osv_oid_t obje_obid;
    int xx, ax;
    int deseValu;
    char obid_stri[OBJE_IDENTI_ZLEN];
    //
    PK_PACK_STREAM *pkps;
    EUTI_PKPS_OPEN(pkps, &query_resp, "oii");
    do {
        // 由于本地没"<[xx int, ax int]>"类型的对象，解析返回的数据流
        deseValu = UserKits::LoopDeseri(pkps, (char *) "oii", &obje_obid, &xx, &ax);
        if (!deseValu) {
            printf("|%s|%d|%d|\n", oidstr(obid_stri, &obje_obid), xx, ax);
        } else if (0x00 > deseValu) {
            printf("UserKits::LoopDeseri ERROR!\n");
            EUTI_PKPS_CLOSE(pkps);
            return -1;
        }
    } while (!deseValu);
    EUTI_PKPS_CLOSE(pkps);
    //
    printf("LevFPFactoryObje PASSED!\n");
    return 0;
}

// 

static int LevFPFactoryObjRaw(BASELevFP &earthLevFP) {
    printf("[FUNC]:LevFPFactoryObjRaw\n");
    // template <class T> int Factory(vector <T *> &factoVecto, const string &contName);
    // template <class T> int Factory(vector <T *> &factoVecto, const string &contName, const string &prediStri);
    resp_data_t query_resp;
    // 用容器"txxt_con"里符合条件的对象，以"<[xx int, ax int]>"类型，构造新的对象并返回ｉ
    int factory_valu = earthLevFP.Factory(&query_resp, "<[xx int, ax int]>", "txxt_con");
    if (factory_valu) {
        printf("earthLevFP Factory ERROR! factory_valu:%08X\n", factory_valu);
        return -1;
    }
    //
    osv_oid_t obje_obid;
    int xx, ax;
    int deseValu;
    char obid_stri[OBJE_IDENTI_ZLEN];
    //　构造解析对象
    DeseRespo *deresp = new DeseRespo(&query_resp, "oii");
    //
    do {
        // 由于本地没"<[xx int, ax int]>"类型的对象，解析返回的数据流
        deseValu = deresp->LoopDeseri(&obje_obid, &xx, &ax);
        if (!deseValu) {
            printf("|%s|%d|%d|\n", oidstr(obid_stri, &obje_obid), xx, ax);
        } else if (0x00 > deseValu) {
            printf("DeseRespo::LoopDeseri ERROR!\n");
            delete deresp;
            return -1;
        }
    } while (!deseValu);
    //
    printf("xxxxxxxxxxxxx!\n");
    //重置解析对象
    deresp->Reset();
    do {
        // 由于本地没"<[xx int, ax int]>"类型的对象，解析返回的数据流
        deseValu = deresp->LoopDeseri(&obje_obid, &xx, &ax);
        if (!deseValu) {
            printf("|%s|%d|%d|\n", oidstr(obid_stri, &obje_obid), xx, ax);
        } else if (0x00 > deseValu) {
            printf("DeseRespo::LoopDeseri ERROR!\n");
            delete deresp;
            return -1;
        }
    } while (!deseValu);
    //
    delete deresp;
    //
    printf("LevFPFactoryObje PASSED!\n");
    return 0;
}

//

int LevFPFactory(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPFactory\n");
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    // 得到数据库第４层空间对象
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP ERROR!\n");
        return -1;
    }
    //
    printf("-------------------------- LevFPFactoryObje\n");
    if (LevFPFactoryObje(earthLevFP))
        printf("LevFPFactoryObje ERROR!\n");
    printf("-------------------------- LevFPFactoryRaw\n");
    if (LevFPFactoryRaw(earthLevFP))
        printf("LevFPFactoryObje ERROR!\n");
    printf("-------------------------- LevFPFactoryObjRaw\n");
    if (LevFPFactoryObjRaw(earthLevFP))
        printf("LevFPFactoryObje ERROR!\n");
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
    printf("********************************* [FUNC]:LevFPFactory\n");
    LevFPFactory(vmwaConne);
    printf("********************************* END\n");
    //
    return 0;
}

