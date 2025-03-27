
/* 
 * File:   BASELevFP.h / OSEVBase.h
 * Author: James Xu
 *
 * Created on 2017.9.6
 */

#ifndef BASE_LEVFP_H
#define BASE_LEVFP_H

//

using namespace std;

#include <string>
using std::string;

#include <vector>
using std::vector;

//

struct _cont_valu_ {
    osv_oid_t contOBID;
    char contName[OBJN_LENGTH];
};

typedef struct _cont_valu_ cont_valu_t;

//

class BASELevFP {
public:
    // m_BaseName, osv_oid_t m_OID base OID, m_ConneSocket
    osev_clie moOSEVClie;
private:
    // storage contain obid
    actionmap *moContainObjHM;
public:
    BASELevFP();
    virtual ~BASELevFP();
public:
    cont_valu_t *FindContain(const char *contName);
    void ResetContain();
    void EraseContain(const char *contName);
public:
    int GetLevTh(Contain &contObje, const string &contName);
    int GetContain(Contain &contObje, const string &contName);
public:
    // echo ECHO ATTRIB STATIS
    int EchoOBID(osv_oid_t &contOBID, const string &echoConta);
    int EchoName(string &echoConta, const osv_oid_t &contOBID);
    int Echo(string &echoValu);
    int Echo(string &echoValu, const string &echoConta);
    int Echo(string &echoValu, const osv_oid_t &contOBID);
    // create
    int Create(const string &contName, const string &storaType, const string &lv2pName); // checked
    int Create(Contain &contObje, const string &contName, const string &storaType, const string &lv2pName); // checked
    // drop
    int Drop(const string &dropConta); // checked
    int Drop(const osv_oid_t &dropOBID); // checked
    int Drop(Contain &dropObje); // checked
    // update, large data, if contain not exists, return error.
    int Update(const string &updatConta, const string &attri, const string &value); // todo:
    int Update(Contain &updatConta); // todo:
    template <class T> int Update(const string &updatConta, T &updatObje); // checked
    template <class T> int Update(const string &updatConta, vector <T *> &updatVecto); // checked
    template <class T> int Update(Contain &updatConta, T &updatObje); // checked
    template <class T> int Update(Contain &updatConta, vector <T *> &updatVecto); // checked
    // insert, large data; if contain not exists, create it
    int Insert(const string &inserConta, const string &attri, const string &value); // todo:
    int Insert(Contain &inserConta); // todo:
    template <class T> int Insert(const string &inserConta, T &inserObje); // checked
    template <class T> int Insert(const string &inserConta, vector <T *> &inserVecto); // checked
    template <class T> int Insert(Contain &inserConta, T &inserObje); // checked
    template <class T> int Insert(Contain &inserConta, vector <T *> &inserVecto); // checked
    // search
    // const string &srcConta
    template <class T> int Search(T &searObje, const string &srcConta, const string &prediStri); // checked
    template <class T> int Search(T &searObje, const string &srcConta, const osv_oid_t &condiOBID); // checked
    template <class T> int Search(vector <T *> &searVecto, const string &srcConta); // checked
    template <class T> int Search(vector <T *> &searVecto, const string &srcConta, const string &prediStri); // checked
    template <class T> int Search(vector <T *> &searVecto, const string &srcConta, const osv_oid_t &condiOBID); // checked
    int Search(resp_data_t *query_resp, const string &lv2pDefin, const string &srcConta); // checked
    int Search(resp_data_t *query_resp, const string &lv2pDefin, const string &srcConta, const string &prediStri); // checked
    int Search(resp_data_t *query_resp, const string &lv2pDefin, const string &srcConta, const osv_oid_t &condiOBID); // checked
    int Search(const string &destConta, const string &srcConta); // checked
    int Search(const string &destConta, const string &srcConta, const string &prediStri); // checked
    int Search(const string &destConta, const string &srcConta, const osv_oid_t &condiOBID); // checked
    int Search(Contain &destConta, const string &srcConta); // checked
    int Search(Contain &destConta, const string &srcConta, const string &prediStri); // checked
    int Search(Contain &destConta, const string &srcConta, const osv_oid_t &condiOBID); // checked
    // Contain &srcConta
    template <class T> int Search(T &searObje, Contain &srcConta, const string &prediStri); // checked
    template <class T> int Search(T &searObje, Contain &srcConta, const osv_oid_t &condiOBID); // checked
    template <class T> int Search(vector <T *> &searVecto, Contain &srcConta); // checked
    template <class T> int Search(vector <T *> &searVecto, Contain &srcConta, const string &prediStri); // checked
    template <class T> int Search(vector <T *> &searVecto, Contain &srcConta, const osv_oid_t &condiOBID); // checked
    int Search(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcConta); // checked
    int Search(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcConta, const string &prediStri); // checked
    int Search(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcConta, const osv_oid_t &condiOBID); // checked
    int Search(const string &destConta, Contain &srcConta); // checked
    int Search(const string &destConta, Contain &srcConta, const string &prediStri); // checked
    int Search(const string &destConta, Contain &srcConta, const osv_oid_t &condiOBID); // checked
    int Search(Contain &destConta, Contain &srcConta); // checked
    int Search(Contain &destConta, Contain &srcConta, const string &prediStri); // checked
    int Search(Contain &destConta, Contain &srcConta, const osv_oid_t &condiOBID); // checked
    // Contain &srcContaI, Contain &srcContaII
    template <class T> int Search(T &searObje, Contain &srcContaI, Contain &srcContaII, const string &prediStri); // checked
    template <class T> int Search(T &searObje, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II); // checked
    template <class T> int Search(vector <T *> &searVecto, Contain &srcContaI, Contain &srcContaII); // checked
    template <class T> int Search(vector <T *> &searVecto, Contain &srcContaI, Contain &srcContaII, const string &prediStri); // checked
    template <class T> int Search(vector <T *> &searVecto, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II); // checked
    int Search(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcContaI, Contain &srcContaII); // checked
    int Search(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcContaI, Contain &srcContaII, const string &prediStri); // checked
    int Search(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II); // checked
    int Search(const string &destConta, Contain &srcContaI, Contain &srcContaII); // checked
    int Search(const string &destConta, Contain &srcContaI, Contain &srcContaII, const string &prediStri); // checked
    int Search(const string &destConta, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II); // checked
    int Search(Contain &destConta, Contain &srcContaI, Contain &srcContaII); // checked
    int Search(Contain &destConta, Contain &srcContaI, Contain &srcContaII, const string &prediStri); // checked
    int Search(Contain &destConta, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II); // checked
    // invoke
    int Invoke(const string &invoConta, const string &invokStri); // checked
    int Invoke(const string &invoConta, const string &invokStri, const string &prediStri); // checked
    int Invoke(const string &invoConta, const string &invokStri, const osv_oid_t &condiOBID); // checked
    template <class T> int Invoke(T &ivkRObje, const string &invoConta, const string &invokStri); // checked
    template <class T> int Invoke(T &ivkRObje, const string &invoConta, const string &invokStri, const string &prediStri); // checked
    template <class T> int Invoke(T &ivkRObje, const string &invoConta, const string &invokStri, const osv_oid_t &condiOBID); // checked
    template <class T> int Invoke(vector <T *> &ivkRVecto, const string &invoConta, const string &invokStri); // checked
    template <class T> int Invoke(vector <T *> &ivkRVecto, const string &invoConta, const string &invokStri, const string &prediStri); // checked
    template <class T> int Invoke(vector <T *> &ivkRVecto, const string &invoConta, const string &invokStri, const osv_oid_t &condiOBID); // checked
    int Invoke(resp_data_t *query_resp, const string &invoConta, const string &invokStri); // checked
    int Invoke(resp_data_t *query_resp, const string &invoConta, const string &invokStri, const string &prediStri); // checked
    int Invoke(resp_data_t *query_resp, const string &invoConta, const string &invokStri, const osv_oid_t &condiOBID); // checked
    int Invoke(Contain &invoConta, const string &invokStri); // checked
    int Invoke(Contain &invoConta, const string &invokStri, const string &prediStri); // checked
    int Invoke(Contain &invoConta, const string &invokStri, const osv_oid_t &condiOBID); // checked
    template <class T> int Invoke(T &ivkRObje, Contain &invoConta, const string &invokStri); // checked
    template <class T> int Invoke(T &ivkRObje, Contain &invoConta, const string &invokStri, const string &prediStri); // checked
    template <class T> int Invoke(T &ivkRObje, Contain &invoConta, const string &invokStri, const osv_oid_t &condiOBID); // checked
    template <class T> int Invoke(vector <T *> &ivkRVecto, Contain &invoConta, const string &invokStri); // checked
    template <class T> int Invoke(vector <T *> &ivkRVecto, Contain &invoConta, const string &invokStri, const string &prediStri); // checked
    template <class T> int Invoke(vector <T *> &ivkRVecto, Contain &invoConta, const string &invokStri, const osv_oid_t &condiOBID); // checked
    int Invoke(resp_data_t *query_resp, Contain &invoConta, const string &invokStri); // checked
    int Invoke(resp_data_t *query_resp, Contain &invoConta, const string &invokStri, const string &prediStri); // checked
    int Invoke(resp_data_t *query_resp, Contain &invoConta, const string &invokStri, const osv_oid_t &condiOBID); // checked
    // factory
    // const string &srcConta
    template <class T> int Factory(T &factoObje, const string &srcConta, const string &prediStri); // checked
    template <class T> int Factory(T &factoObje, const string &srcConta, const osv_oid_t &condiOBID); // checked
    template <class T> int Factory(vector <T *> &factoVecto, const string &srcConta); // checked
    template <class T> int Factory(vector <T *> &factoVecto, const string &srcConta, const string &prediStri); // checked
    template <class T> int Factory(vector <T *> &factoVecto, const string &srcConta, const osv_oid_t &condiOBID); // checked
    int Factory(resp_data_t *query_resp, const string &lv2pDefin, const string &srcConta); // checked
    int Factory(resp_data_t *query_resp, const string &lv2pDefin, const string &srcConta, const string &prediStri); // checked
    int Factory(resp_data_t *query_resp, const string &lv2pDefin, const string &srcConta, const osv_oid_t &condiOBID); // checked
    int Factory(const string &destConta, const string &srcConta); // checked
    int Factory(const string &destConta, const string &srcConta, const string &prediStri); // checked
    int Factory(const string &destConta, const string &srcConta, const osv_oid_t &condiOBID); // checked
    int Factory(Contain &destConta, const string &srcConta); // checked
    int Factory(Contain &destConta, const string &srcConta, const string &prediStri); // checked
    int Factory(Contain &destConta, const string &srcConta, const osv_oid_t &condiOBID); // checked
    // Contain &srcConta
    template <class T> int Factory(T &factoObje, Contain &srcConta, const string &prediStri); // checked
    template <class T> int Factory(T &factoObje, Contain &srcConta, const osv_oid_t &condiOBID); // checked
    template <class T> int Factory(vector <T *> &factoVecto, Contain &srcConta); // checked
    template <class T> int Factory(vector <T *> &factoVecto, Contain &srcConta, const string &prediStri); // checked
    template <class T> int Factory(vector <T *> &factoVecto, Contain &srcConta, const osv_oid_t &condiOBID); // checked
    int Factory(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcConta); // checked
    int Factory(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcConta, const string &prediStri); // checked
    int Factory(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcConta, const osv_oid_t &condiOBID); // checked
    int Factory(const string &destConta, Contain &srcConta); // checked
    int Factory(const string &destConta, Contain &srcConta, const string &prediStri); // checked
    int Factory(const string &destConta, Contain &srcConta, const osv_oid_t &condiOBID); // checked
    int Factory(Contain &destConta, Contain &srcConta); // checked
    int Factory(Contain &destConta, Contain &srcConta, const string &prediStri); // checked
    int Factory(Contain &destConta, Contain &srcConta, const osv_oid_t &condiOBID); // checked
    // Contain &srcContaI, Contain &srcContaII
    template <class T> int Factory(T &factoObje, Contain &srcContaI, Contain &srcContaII, const string &prediStri); // checked
    template <class T> int Factory(T &factoObje, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II); // checked
    template <class T> int Factory(vector <T *> &factoVecto, Contain &srcContaI, Contain &srcContaII); // checked
    template <class T> int Factory(vector <T *> &factoVecto, Contain &srcContaI, Contain &srcContaII, const string &prediStri); // checked
    template <class T> int Factory(vector <T *> &factoVecto, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II); // checked
    int Factory(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcContaI, Contain &srcContaII); // checked
    int Factory(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcContaI, Contain &srcContaII, const string &prediStri); // checked
    int Factory(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II); // checked
    int Factory(const string &destConta, Contain &srcContaI, Contain &srcContaII); // checked
    int Factory(const string &destConta, Contain &srcContaI, Contain &srcContaII, const string &prediStri); // checked
    int Factory(const string &destConta, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II); // checked
    int Factory(Contain &destConta, Contain &srcContaI, Contain &srcContaII); // checked
    int Factory(Contain &destConta, Contain &srcContaI, Contain &srcContaII, const string &prediStri); // checked
    int Factory(Contain &destConta, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II); // checked
};

// checked

template <class T> int BASELevFP::BASELevFP::Update(const string &updatConta, T &updatObje) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
            // CLIEPF("[FUNC]: Contain::Update\n");
    if ("" == updatConta) return -1;
    // object parm style stream
    char objePsts[ESCA_ENTICON_PART + OBJE_CONTE_LEN];
    const char *parms[0x03] = {updatConta.c_str(), objePsts, NULL};
    unsigned long long seriLeng = OBJE_CONTE_LEN;
    if (EntitKits::SeriObje(ESCA_ECONTE_POSI(objePsts), &seriLeng, updatObje))
        return -1;
    MAKE_ESCHEAD_BINA(objePsts, seriLeng)
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t query_resp;
    return lv4p_query_updat(&query_resp, &moOSEVClie, parms);
}

// checked

template <class T> int BASELevFP::Update(const string &updatConta, vector <T *> &updatVecto) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
            // CLIEPF("[FUNC]: Contain::Update\n");
    if ("" == updatConta) return -1;
    //
    char binaPsts[ESCA_ENTICON_PART + BINA_ARRAY_LEN];
    const char *parms[0x03] = {updatConta.c_str(), binaPsts, NULL};
    unsigned long long seriLeng = BINA_ARRAY_LEN;
    if (EntitKits::SeriObjeVect(ESCA_ECONTE_POSI(binaPsts), &seriLeng, updatVecto))
        return -1;
    MAKE_ESCHEAD_BINA(binaPsts, seriLeng)
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t query_resp;
    return lv4p_query_updat(&query_resp, &moOSEVClie, parms);
}

// checked

template <class T> int BASELevFP::Update(Contain &updatConta, T &updatObje) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
            // CLIEPF("[FUNC]: Contain::Update\n");
            //
            char distOID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char objePsts[ESCA_ENTICON_PART + OBJE_CONTE_LEN];
    const char *parms[0x03] = {distOID, objePsts, NULL};
    ESMCPY_OBID(distOID, &updatConta.moLevThOBID);
    unsigned long long seriLeng = OBJE_CONTE_LEN;
    if (EntitKits::SeriObje(ESCA_ECONTE_POSI(objePsts), &seriLeng, updatObje))
        return -1;
    MAKE_ESCHEAD_BINA(objePsts, seriLeng)
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t query_resp;
    return lv4p_query_updat(&query_resp, &moOSEVClie, parms);
}

// checked

template <class T> int BASELevFP::Update(Contain &updatConta, vector <T *> &updatVecto) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
            // CLIEPF("[FUNC]: Contain::Update\n");
            //
            char distOID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char binaPsts[ESCA_ENTICON_PART + BINA_ARRAY_LEN];
    const char *parms[0x03] = {distOID, binaPsts, NULL};
    ESMCPY_OBID(distOID, &updatConta.moLevThOBID);
    unsigned long long seriLeng = BINA_ARRAY_LEN;
    if (EntitKits::SeriObjeVect(ESCA_ECONTE_POSI(binaPsts), &seriLeng, updatVecto))
        return -1;
    MAKE_ESCHEAD_BINA(binaPsts, seriLeng)
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t query_resp;
    return lv4p_query_updat(&query_resp, &moOSEVClie, parms);
}

// checked

template <class T> int BASELevFP::Insert(const string &inserConta, T &inserObje) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
    printf("[FUNC]:BASELevFP::Insert\n");
    if ("" == inserConta) return -1;
    //
    char objePsts[ESCA_ENTICON_PART + OBJE_CONTE_LEN];
    const char *parms[0x03] = {inserConta.c_str(), objePsts, NULL};
    unsigned long long seriLeng = OBJE_CONTE_LEN;
    if (EntitKits::SeriObje(ESCA_ECONTE_POSI(objePsts), &seriLeng, inserObje))
        return -1;
    MAKE_ESCHEAD_BINA(objePsts, seriLeng)
    printf("seriLeng:|%llu|\n", seriLeng);
    printf("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t query_resp;
    int inser_valu = lv4p_query_inser(&query_resp, &moOSEVClie, parms);
    if (inser_valu) {
        printf("query insert ERROR!\n");
        return inser_valu;
    }
    IRKeyVal::RTypObid kvObid;
    EntitKits::DeseRKV(kvObid, &query_resp);
    if (IS_INVAL_OBID(&kvObid.obje_obid)) return -1;
    OBID_BINARY_COPY(&inserObje.obje_obid, &kvObid.obje_obid)
            // printf("BASELevFP::Insert end\n");
    return 0x00;
}

// checked

template <class T> int BASELevFP::Insert(const string &inserConta, vector <T *> &inserVecto) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
            // CLIEPF("[FUNC]:BASELevFP::Insert\n");
    if ("" == inserConta) return -1;
    //
    char binaPsts[ESCA_ENTICON_PART + BINA_ARRAY_LEN];
    const char *parms[0x03] = {inserConta.c_str(), binaPsts, NULL};
    unsigned long long seriLeng = BINA_ARRAY_LEN;
    if (EntitKits::SeriObjeVect(ESCA_ECONTE_POSI(binaPsts), &seriLeng, inserVecto))
        return -1;
    MAKE_ESCHEAD_BINA(binaPsts, seriLeng)
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t query_resp;
    int inser_valu = lv4p_query_inser(&query_resp, &moOSEVClie, parms);
    if (inser_valu) {
        // CLIEPF("query insert ERROR!\n");
        return inser_valu;
    }
    //
    vector <IRKeyVal::RTypObid *> kvObidVec;
    EntitKits::DeseRKVVect(kvObidVec, &query_resp);
    if (InseKits::ChkInvalOBID(kvObidVec)) {
        EntitKits::ClearVecto(kvObidVec);
        return -1;
    }
    if (InseKits::RefreshOBID(inserVecto, kvObidVec)) {
        EntitKits::ClearVecto(kvObidVec);
        return -1;
    }
    EntitKits::ClearVecto(kvObidVec);
    //
    return 0x00;
}

// checked

template <class T> int BASELevFP::Insert(Contain &inserConta, T &inserObje) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
            // CLIEPF("[FUNC]:BASELevFP::Insert\n");
            //
            char distOID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char objePsts[ESCA_ENTICON_PART + OBJE_CONTE_LEN];
    const char *parms[0x03] = {distOID, objePsts, NULL};
    ESMCPY_OBID(distOID, &inserConta.moLevThOBID);
    unsigned long long seriLeng = OBJE_CONTE_LEN;
    if (EntitKits::SeriObje(ESCA_ECONTE_POSI(objePsts), &seriLeng, inserObje))
        return -1;
    MAKE_ESCHEAD_BINA(objePsts, seriLeng)
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t query_resp;
    int inser_valu = lv4p_query_inser(&query_resp, &moOSEVClie, parms);
    if (inser_valu) {
        // CLIEPF("query insert ERROR!\n");
        return inser_valu;
    }
    IRKeyVal::RTypObid kvObid;
    EntitKits::DeseRKV(kvObid, &query_resp);
    if (IS_INVAL_OBID(&kvObid.obje_obid)) return -1;
    OBID_BINARY_COPY(&inserObje.obje_obid, &kvObid.obje_obid)
            //
    return 0x00;
}

// checked

template <class T> int BASELevFP::Insert(Contain &inserConta, vector <T *> &inserVecto) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
            // CLIEPF("[FUNC]:BASELevFP::Insert\n");
            //
            char distOID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char binaPsts[ESCA_ENTICON_PART + BINA_ARRAY_LEN];
    const char *parms[0x03] = {distOID, binaPsts, NULL};
    ESMCPY_OBID(distOID, &inserConta.moLevThOBID);
    unsigned long long seriLeng = BINA_ARRAY_LEN;
    if (EntitKits::SeriObjeVect(ESCA_ECONTE_POSI(binaPsts), &seriLeng, inserVecto))
        return -1;
    MAKE_ESCHEAD_BINA(binaPsts, seriLeng)
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t query_resp;
    int inser_valu = lv4p_query_inser(&query_resp, &moOSEVClie, parms);
    if (inser_valu) {
        // CLIEPF("query insert ERROR!\n");
        return inser_valu;
    }
    //
    vector <IRKeyVal::RTypObid *> kvObidVec;
    EntitKits::DeseRKVVect(kvObidVec, &query_resp);
    if (InseKits::ChkInvalOBID(kvObidVec)) {
        EntitKits::ClearVecto(kvObidVec);
        return -1;
    }
    if (InseKits::RefreshOBID(inserVecto, kvObidVec)) {
        EntitKits::ClearVecto(kvObidVec);
        return -1;
    }
    EntitKits::ClearVecto(kvObidVec);
    //
    return 0x00;
}

//

#include "InlineLev/LevFPSearch.h"
#include "InlineLev/LevFPInvoke.h"
#include "InlineLev/LevFPFactory.h"

#endif /* BASE_LEVFP_H */

