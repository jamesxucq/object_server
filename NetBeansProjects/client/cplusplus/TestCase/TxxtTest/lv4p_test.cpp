
#include <cstdlib>

using namespace std;

#include <vector>
using std::vector;

//
#include "txxt.h"

#include "lv4p_test.h"

/*
// Server
// #define QECHO_CONT_OBJID    0x00
// #define QECHO_CONT_NAME     0x01
// #define QECHO_LVFP_ATTRIB   0x02
// #define QECHO_LVFP_STATIS   0x03

static const struct parm_node quer_echo_tab[] = {
    {"ECHO", "0I"}, // ECHO
    {"ATTRIB", "1I"}, // ATTRIB
    {"STATIS", "2I"}, // STATIS
    {NULL, "INVA"}
};
 */

int LevFPEcho(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPEcho\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    // int Echo(string &echoValu, const string &echoType);
    // int Echo(string &echoValu, const string &echoType, const string &contName);
    // int Echo(string &echoValu, const string &echoType, const osv_oid_t *conta_oid);
    string echoValu;
    int echo_valu = earthLevFP.Echo(echoValu);
    if (echo_valu) {
        printf("earthLevFP Echo error. echo_valu:%x\n", echo_valu);
        return -1;
    }
    printf("echoValu:|%s|\n", echoValu.c_str());
    //
    printf("LevFPEcho OK!\n");
    return 0;
}

int LevFPCreate(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPCreate\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    // int Create(const string &contName, const string &lv2pName, string &storaType);
    int creat_valu = earthLevFP.Create("txxt_temp_con", "witi", "txxt");
    if (creat_valu) {
        printf("earthLevFP Create error. creat_valu:%x\n", creat_valu);
        return -1;
    }
    //
    printf("LevFPCreate OK!\n");
    return 0;
}

int LevFPDrop(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPDrop\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    // int Drop(const string &contName);
    int drop_valu = earthLevFP.Drop("txxt_temp_con");
    if (drop_valu) {
        printf("earthLevFP Drop error. drop_valu:%x\n", drop_valu);
        return -1;
    }
    //
    printf("LevFPDrop OK!\n");
    return 0;
}

int LevFPUpdate(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPUpdate\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    // template <class T> int Update(const string &contName, vector <T *> &updatVecto);
    vector <earth::lev2p::txxt *> updatVecto;
    int updat_valu = earthLevFP.Update("txxt_temp_con", updatVecto);
    if (updat_valu) {
        printf("earthLevFP Update error. updat_valu:%x\n", updat_valu);
        return -1;
    }
    //
    printf("LevFPUpdate OK!\n");
    return 0;
}

int LevFPInsert(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPInsert\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    // template <class T> int Insert(const string &contName, vector <T *> &inserVecto);
    vector <earth::lev2p::txxt *> inserVecto;
    int inser_valu = earthLevFP.Insert("txxt_temp_con", inserVecto);
    if (inser_valu) {
        printf("earthLevFP Insert error. inser_valu:%x\n", inser_valu);
        return -1;
    }
    //
    printf("LevFPInsert OK!\n");
    return 0;
}

int LevFPSearch(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPSearch\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    // template <class T> int Search(vector <T *> &searVecto, const string &contName);
    // template <class T> int Search(vector <T *> &searVecto, const string &contName, const string &prediStri);
    vector <earth::lev2p::txxt *> searVecto;
    int searc_valu = earthLevFP.Search(searVecto, "txxt_temp_con");
    if (searc_valu) {
        printf("earthLevFP Search error. searc_valu:%x\n", searc_valu);
        return -1;
    }
    //
    printf("LevFPSearch OK!\n");
    return 0;
}

int LevFPInvoke(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPInvoke\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    // template <class T> int Invoke(T &invoObje, const string &contName, string &invokStri);
    // template <class T> int Invoke(vector <T *> &invoVecto, const string &contName, string &invokStri);
    // template <class T> int Invoke(vector <T *> &invoVecto, const string &contName, string &invokStri, const string &prediStri);
    vector <IRKeyVal::RTypInt32 *> ivkRVecto;
    int invok_valu = earthLevFP.Invoke(ivkRVecto, "txxt_temp_con", "txxx(11, 22, 33)");
    if (invok_valu) {
        printf("earthLevFP Invoke error. invok_valu:%x\n", invok_valu);
        return -1;
    }
    //
    printf("LevFPInvoke OK!\n");
    return 0;
}

int LevFPFactory(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevFPFactory\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    // template <class T> int Factory(vector <T *> &factoVecto, const string &contName);
    // template <class T> int Factory(vector <T *> &factoVecto, const string &contName, const string &prediStri);
    vector <earth::lev2p::txxt *> factoVecto;
    int factory_valu = earthLevFP.Factory(factoVecto, "txxt_temp_con");
    if (factory_valu) {
        printf("earthLevFP Factory error. factory_valu:%x\n", factory_valu);
        return -1;
    }
    //
    printf("LevFPFactory OK!\n");
    return 0;
}