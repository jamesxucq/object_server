
#include "../earth_lv2p/EarthLvtpHeader.h"

#include "LevTh_Search.h"

static int LevThSearchObje(Contain &inteContain) {
    printf("[FUNC]:LevThSearchObje\n");
    // template <class T> int Search(T &searObje); // passed
    // template <class T> int Search(T &searObje, const string &prediStri); // passed
    // template <class T> int Search(vector <T *> &searVecto); // passed
    // template <class T> int Search(vector <T *> &searVecto, const string &prediStri); // passed
    // string prediStri = "ECHO";
    earth::lev2p::txxt searObje;
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
    if (earthLevFP.GetContain(txxtContain, "txxt_con")) {
        printf("BASELevFP GetContain ERROR!\n");
        return -1;
    }
    //
    if (LevThSearchObje(txxtContain))
        printf("LevThSearchObje ERROR!\n");
    //
    unsigned int inde = 0x00;
    for (; inde < 0x01; ++inde) {
        printf("-------------------------- inde:%d\n", inde);
        if (LevThSearVecto(txxtContain))
            printf("LevThSearVecto ERROR!\n");
    }
    //
    return 0x00;
}