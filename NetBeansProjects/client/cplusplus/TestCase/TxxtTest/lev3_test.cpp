
#include <cstdlib>

using namespace std;

#include <vector>
using std::vector;

//
#include "txxt.h"

#include "lev3_test.h"

int LevThSearVecto(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThSearVecto\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    //
    BASELevTh txxtContain;
    printf("earthLevFP.GetLevTh\n");
    if (earthLevFP.GetLevTh(txxtContain, "txxt_con")) {
        printf("BASELevFP GetLevTh error.\n");
        return -1;
    }
    //
    printf("BASELevTh Search start.\n");
    vector <earth::lev2p::txxt *> searVector;
    string PrediStri = "*";
    printf("txxtContain.Search\n");
    if (txxtContain.Search(searVector, PrediStri)) {
        printf("BASELevTh Search error.\n");
        return -1;
    }
    //
    char temp[33];
    printf("BASELevTh Search ok.\n");
    vector <earth::lev2p::txxt *>::iterator iter;
    for (iter = searVector.begin(); iter != searVector.end(); ++iter) {
        printf("|%s|%d|%d|%d|\n", oidstr(temp, &(*iter)->obje_oid), (*iter)->xx, (*iter)->ax, (*iter)->cx);
    }
    EntryUtili::ClearVecto(searVector);
    //
    printf("LevThSearVecto OK!\n");
    return 0;

}


// vector test

int LevThObjeInserUpdat(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThObjeInserUpdat\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    //
    BASELevTh txxtContain;
    printf("earthLevFP.GetLevTh\n");
    if (earthLevFP.GetLevTh(txxtContain, "txxt_con")) {
        printf("BASELevFP GetLevTh error.\n");
        return -1;
    }
    //
    char temp[33];
    earth::lev2p::txxt txxtObje;
    // txxtObje.Create(12, 34);
    txxtObje.obje_oid.osev_unique = earthLevFP.moOSEVClie.clie_oid.osev_unique;
    txxtObje.obje_oid.time_stamp = 2;
    txxtObje.obje_oid.counter = 2;
    txxtObje.xx = 33;
    txxtObje.ax = 99;
    txxtObje.cx = 22;
    printf("|%s|%d|%d|%d|\n", oidstr(temp, &txxtObje.obje_oid), txxtObje.xx, txxtObje.ax, txxtObje.cx);
    printf("txxtContain.Insert\n");
    if (txxtContain.Insert(txxtObje)) {
        printf("BASELevTh Insert error.\n");
        return -1;
    }
    //
    txxtObje.ax = 199;
    txxtObje.cx = 122;
    printf("|%s|%d|%d|%d|\n", oidstr(temp, &txxtObje.obje_oid), txxtObje.xx, txxtObje.ax, txxtObje.cx);
    printf("txxtContain.Update\n");
    if (txxtContain.Update(txxtObje)) {
        printf("BASELevTh Update error.\n");
        return -1;
    }
    //
    printf("LevThObjeInserUpdat OK!\n");
    return 0;

}

/*
const struct parm_node cons_echo_tab[] = {
    {"ECHO", "0I"}, // ECHO
    {"ATTRIB", "1I"}, // ATTRIB
    {"STATIS", "2I"}, // STATIS
    {NULL, "INVA"}
};
 */

int LevThEcho(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThEcho\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    //
    BASELevTh txxtContain;
    printf("earthLevFP.GetLevTh\n");
    if (earthLevFP.GetLevTh(txxtContain, "txxt_con")) {
        printf("BASELevFP GetLevTh error.\n");
        return -1;
    }
    // int Echo(string &echoValu, const string &echoType);
    string echoValu;
    int echo_valu = txxtContain.Echo(echoValu);
    if (echo_valu) {
        printf("BASELevTh Echo error. echo_valu:%x\n", echo_valu);
        return -1;
    }
    printf("echoValu:|%s|\n", echoValu.c_str());
    //
    printf("LevThEcho OK!\n");
    return 0;
}

int LevThCreate(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThCreate\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    //
    BASELevTh txxtContain;
    printf("earthLevFP.GetLevTh\n");
    if (earthLevFP.GetLevTh(txxtContain, "txxt_con")) {
        printf("BASELevFP GetLevTh error.\n");
        return -1;
    }
    // int Create(const string &lv2pName, const string &params);
    // earth::lev2p::txxt deopObje;
    int creat_valu = txxtContain.Create("(11, 22, 33)");
    if (creat_valu) {
        printf("BASELevTh Create error. creat_valu:%x\n", creat_valu);
        return -1;
    }
    //
    printf("LevThCreate OK!\n");
    return 0;
}

int LevThDrop(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThDrop\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    //
    BASELevTh txxtContain;
    printf("earthLevFP.GetLevTh\n");
    if (earthLevFP.GetLevTh(txxtContain, "txxt_con")) {
        printf("BASELevFP GetLevTh error.\n");
        return -1;
    }
    // template <class T> int Drop(T &dropObje); // passed
    // template <class T> int Drop(vector <T *> &dropVecto);
    // int Drop(const string &prediStri);
    earth::lev2p::txxt deopObje;
    int drop_valu = txxtContain.Drop(deopObje);
    if (drop_valu) {
        printf("BASELevTh Drop error. drop_valu:%x\n", drop_valu);
        return -1;
    }
    //
    printf("LevThDrop OK!\n");
    return 0;
}

int LevThUpdate(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThUpdate\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    //
    BASELevTh txxtContain;
    printf("earthLevFP.GetLevTh\n");
    if (earthLevFP.GetLevTh(txxtContain, "txxt_con")) {
        printf("BASELevFP GetLevTh error.\n");
        return -1;
    }
    // template <class T> int Update(T &updatObje); // passed
    // template <class T> int Update(vector <T *> &updatVecto);
    earth::lev2p::txxt updatObje;
    int updat_valu = txxtContain.Update(updatObje);
    if (updat_valu) {
        printf("BASELevTh Update error. updat_valu:%x\n", updat_valu);
        return -1;
    }
    //
    printf("LevThUpdate OK!\n");
    return 0;
}

int LevThInsert(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThInsert\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    //
    BASELevTh txxtContain;
    printf("earthLevFP.GetLevTh\n");
    if (earthLevFP.GetLevTh(txxtContain, "txxt_con")) {
        printf("BASELevFP GetLevTh error.\n");
        return -1;
    }
    // int Insert(osv_oid_t *pNewOID, const string &objeStri); // checked
    // template <class T> int Insert(T &inserObje); // checked
    // template <class T> int Insert(vector <T *> &inserVecto); // checked
    earth::lev2p::txxt inserObje;
    int inser_valu = txxtContain.Insert(inserObje);
    if (inser_valu) {
        printf("BASELevTh Insert error. inser_valu:%x\n", inser_valu);
        return -1;
    }
    //
    vector <earth::lev2p::txxt *> inserVecto;
    inser_valu = txxtContain.Insert(inserVecto);
    if (inser_valu) {
        printf("BASELevTh Insert error. inser_valu:%x\n", inser_valu);
        return -1;
    }
    //
    printf("LevThInsert OK!\n");
    return 0;
}

int LevThSearch(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThSearch\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    //
    BASELevTh txxtContain;
    printf("earthLevFP.GetLevTh\n");
    if (earthLevFP.GetLevTh(txxtContain, "txxt_con")) {
        printf("BASELevFP GetLevTh error.\n");
        return -1;
    }
    // template <class T> int Search(T &searObje); // passed
    // template <class T> int Search(T &searObje, const string &prediStri); // passed
    // template <class T> int Search(vector <T *> &searVecto); // passed
    // template <class T> int Search(vector <T *> &searVecto, const string &prediStri); // passed
    // string prediStri = "ECHO";
    earth::lev2p::txxt searObje;
    int searc_valu = txxtContain.Search(searObje);
    if (searc_valu) {
        printf("BASELevTh Search error. searc_valu:%x\n", searc_valu);
        return -1;
    }
    //
    printf("LevThSearch OK!\n");
    return 0;
}

int LevThInvoke(OSEVConne &vmwaConne) {
    printf("[FUNC]:LevThInvoke\n");
    OSEVConne vmwaConne(userName, password, address, port, "earth");
    //
    BASELevFP earthLevFP;
    printf("vmwaConne.GetBASELevFP\n");
    if (vmwaConne.GetBASELevFP(earthLevFP)) {
        printf("OSEVConne GetBASELevFP error.\n");
        return -1;
    }
    //
    BASELevTh txxtContain;
    printf("earthLevFP.GetLevTh\n");
    if (earthLevFP.GetLevTh(txxtContain, "txxt_con")) {
        printf("BASELevFP GetLevTh error.\n");
        return -1;
    }
    // template <class T> int Invoke(T &invoObje, const string &invokStri);
    // template <class T> int Invoke(vector <T *> &invoVecto, const string &invokStri);
    // template <class T> int Invoke(vector <T *> &invoVecto, const string &invokStri, const string &prediStri);
    // string prediStri = "ECHO";
    IRKeyVal::RTypInt32 ivkRObje;
    int invok_valu = txxtContain.Invoke(ivkRObje, "txxt(11, 22, 33)");
    if (invok_valu) {
        printf("BASELevTh Invoke error. invok_valu:%x\n", invok_valu);
        return -1;
    }
    //
    printf("LevThInvoke OK!\n");
    return 0;
}