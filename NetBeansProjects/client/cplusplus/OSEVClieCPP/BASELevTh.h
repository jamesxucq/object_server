
/* 
 * File:   BASELevTh.h / OSEVContain.h
 * Author: James Xu
 *
 * Created on 2017.9.6
 */

#ifndef BASE_LVTPH_H
#define BASE_LVTPH_H

//
using namespace std;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "parser/parsing.h"
#include "function/funct_header.h"

//

class BASELevTh {
public:
    osv_oid_t moLevThOBID; // contain OBID
    string moLevThName;
    // string moClassName; // todo:20231129
private:
    const osev_clie *mpOSEVClie;
public:
    BASELevTh();
    virtual ~BASELevTh();
public:
    int Build(const string &levThName, const osv_oid_t &levThOBID, const osev_clie *pOSEVClie);
public:
    //  echo ECHO ATTRIB STATIS
    int Echo(string &echoValu);
    // create    
    int Create(const string &parmStri); // checked
    template <class T> int Create(T &creatObje, const string &parmStri); // checked
    // drop
    template <class T> int Drop(T &dropObje); // checked
    template <class T> int Drop(vector <T *> &dropVecto); // checked
    int Drop(const string &prediStri); // checked
    int Drop(const osv_oid_t &dropOBID); // checked
    // update, small data;
    int Update(const char *objeStri); // checked
    int Update(string &objeStri); // checked
    template <class T> int Update(T &updatObje); // checked
    template <class T> int Update(vector <T *> &updatVecto); // checked
    // insert, small data;
    int Insert(osv_oid_t &newOBID, const string &objeStri); // checked
    template <class T> int Insert(T &inserObje); // checked
    template <class T> int Insert(vector <T *> &inserVecto); // checked
    // search
    template <class T> int Search(T &searObje); // checked
    template <class T> int Search(T &searObje, const string &prediStri); // checked
    template <class T> int Search(T &searObje, const osv_oid_t &condiOBID); // checked
    template <class T> int Search(vector <T *> &searVecto); // checked
    template <class T> int Search(vector <T *> &searVecto, const string &prediStri); // checked
    template <class T> int Search(vector <T *> &searVecto, const osv_oid_t &condiOBID); // checked
    int Search(resp_data_t *const_resp); // checked
    int Search(resp_data_t *const_resp, const string &prediStri); // checked
    int Search(resp_data_t *const_resp, const osv_oid_t &condiOBID); // checked
    // invoke
    int Invoke(const string &invokStri); // checked
    int Invoke(const string &invokStri, const string &prediStri); // checked
    int Invoke(const string &invokStri, const osv_oid_t &condiOBID); // checked
    template <class T> int Invoke(T &ivkRObje, const string &invokStri); // checked
    template <class T> int Invoke(T &ivkRObje, const string &invokStri, const string &prediStri); // checked
    template <class T> int Invoke(T &ivkRObje, const string &invokStri, const osv_oid_t &condiOBID); // checked
    template <class T> int Invoke(vector <T *> &ivkRVecto, const string &invokStri); // checked
    template <class T> int Invoke(vector <T *> &ivkRVecto, const string &invokStri, const string &prediStri); // checked
    template <class T> int Invoke(vector <T *> &ivkRVecto, const string &invokStri, const osv_oid_t &condiOBID); // checked
    int Invoke(resp_data_t *const_resp, const string &invokStri); // checked
    int Invoke(resp_data_t *const_resp, const string &invokStri, const string &prediStri); // checked
    int Invoke(resp_data_t *const_resp, const string &invokStri, const osv_oid_t &condiOBID); // checked
};

typedef class BASELevTh Contain;

// checked

template <class T> int BASELevTh::Create(T &creatObje, const string &parmStri) {
    CHECK_LVTP_ATTRIBU(T::clVersion, mpOSEVClie, T::spLevTPName, T::suChkAttribCount)
            // CLIEPF("[FUNC]:BASELevTh::Create\n");
    if ("" == parmStri) return -1;
    // Create
    const char *creat_pamvp[PARAM_COUNT];
    char _cline_[LARGE_CONTE_SIZE];
    if (split_instru_pamvs(creat_pamvp, _cline_, (char *) parmStri.c_str()))
        return -1;
    if (pretr_functi_pamvs(creat_pamvp))
        return -1;
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t const_resp;
    int creat_searo = lev3_const_creat(&const_resp, mpOSEVClie, &moLevThOBID, creat_pamvp);
    if (creat_searo) {
        // CLIEPF("const create ERROR!\n");
        return creat_searo;
    }
    osv_oid_t condiOBID;
    EntitKits::DeseOBID(condiOBID, &const_resp);
    if (IS_INVAL_OBID(&condiOBID)) return -1;
    // Search
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x02] = {cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    creat_searo = lev3_const_searo(&const_resp, mpOSEVClie, &moLevThOBID, parms);
    if (creat_searo) {
        // CLIEPF("resp_code:%u\n", creat_searo);
        return creat_searo;
    }
    EntitKits::DeseObje(creatObje, &const_resp);
    //
    return 0x00;
}


// checked

template <class T> int BASELevTh::Drop(T &dropObje) {
    CHECK_LVTP_ATTRIBU(T::clVersion, mpOSEVClie, T::spLevTPName, T::suChkAttribCount)
            // CLIEPF("[FUNC]:BASELevTh::Drop\n");
            char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x02] = {cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &dropObje.obje_obid);
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t const_resp;
    return lev3_const_drop(&const_resp, mpOSEVClie, &moLevThOBID, parms);
}

// checked

template <class T> int BASELevTh::Drop(vector <T *> &dropVecto) {
    CHECK_LVTP_ATTRIBU(T::clVersion, mpOSEVClie, T::spLevTPName, T::suChkAttribCount)
            // CLIEPF("[FUNC]:BASELevTh::Drop\n");
            char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x02] = {cpmoOBID, NULL};
    //
    class vector <T *>::iterator iter;
    for (iter = dropVecto.begin(); iter != dropVecto.end(); ++iter) {
        ESMCPY_OBID(cpmoOBID, &(*iter)->obje_obid);
        // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
        resp_data_t const_resp;
        int drop_valu = lev3_const_drop(&const_resp, mpOSEVClie, &moLevThOBID, parms);
        if (drop_valu) {
            // CLIEPF("const drop ERROR!\n");
            return drop_valu;
        }
    }
    //
    return 0x00;
}

// checked

template <class T> int BASELevTh::Update(T &updatObje) {
    CHECK_LVTP_ATTRIBU(T::clVersion, mpOSEVClie, T::spLevTPName, T::suChkAttribCount)
            // CLIEPF("[FUNC]: BASELevTh::Update\n");
            char objePsts[ESCA_ENTICON_PART + OBJE_CONTE_LEN];
    const char *parms[0x02] = {objePsts, NULL};
    unsigned long long seriLeng = OBJE_CONTE_LEN;
    //
    if (EntitKits::SeriObje(ESCA_ECONTE_POSI(objePsts), &seriLeng, updatObje))
        return -1;
    MAKE_ESCHEAD_BINA(objePsts, seriLeng)
    //
    resp_data_t const_resp;
    return lev3_const_updat(&const_resp, mpOSEVClie, &moLevThOBID, parms);
}

// checked

template <class T> int BASELevTh::Update(vector <T *> &updatVecto) {
    CHECK_LVTP_ATTRIBU(T::clVersion, mpOSEVClie, T::spLevTPName, T::suChkAttribCount)
            // CLIEPF("[FUNC]: BASELevTh::Update\n");
            char objePsts[ESCA_ENTICON_PART + OBJE_CONTE_LEN];
    const char *parms[0x02] = {objePsts, NULL};
    unsigned long long seriLeng = OBJE_CONTE_LEN;
    //
    class vector <T *>::iterator iter;
    for (iter = updatVecto.begin(); iter != updatVecto.end(); ++iter) {
        if (EntitKits::SeriObje(ESCA_ECONTE_POSI(objePsts), &seriLeng, *(*iter)))
            return -1;
        MAKE_ESCHEAD_BINA(objePsts, seriLeng)
        // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
        resp_data_t const_resp;
        int updat_valu = lev3_const_updat(&const_resp, mpOSEVClie, &moLevThOBID, parms);
        if (updat_valu) {
            // CLIEPF("const update ERROR!\n");
            return updat_valu;
        }
    }
    //
    return 0x00;
}

// checked

template <class T> int BASELevTh::Insert(T &inserObje) {
    CHECK_LVTP_ATTRIBU(T::clVersion, mpOSEVClie, T::spLevTPName, T::suChkAttribCount)
            // CLIEPF("[FUNC]:BASELevTh::Insert\n");
            char objePsts[ESCA_ENTICON_PART + OBJE_CONTE_LEN];
    const char *parms[0x02] = {objePsts, NULL};
    unsigned long long seriLeng = OBJE_CONTE_LEN;
    if (EntitKits::SeriObje(ESCA_ECONTE_POSI(objePsts), &seriLeng, inserObje))
        return -1;
    MAKE_ESCHEAD_BINA(objePsts, seriLeng)
    // CLIEPF("seriLeng:|%llu|\n", seriLeng);
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    //
    resp_data_t const_resp;
    int inser_valu = lev3_const_inser(&const_resp, mpOSEVClie, &moLevThOBID, parms);
    if (inser_valu) {
        // CLIEPF("const insert ERROR!\n");
        return inser_valu;
    }
    IRKeyVal::RTypObid kvObid;
    EntitKits::DeseRKV(kvObid, &const_resp);
    if (IS_INVAL_OBID(&kvObid.obje_obid)) return -1;
    OBID_BINARY_COPY(&inserObje.obje_obid, &kvObid.obje_obid)
            //
    return 0x00;
}

// checked

template <class T> int BASELevTh::Insert(vector <T *> &inserVecto) {
    CHECK_LVTP_ATTRIBU(T::clVersion, mpOSEVClie, T::spLevTPName, T::suChkAttribCount)
            // CLIEPF("[FUNC]:BASELevTh::Insert\n");
            char objePsts[ESCA_ENTICON_PART + OBJE_CONTE_LEN];
    const char *parms[0x02] = {objePsts, NULL};
    unsigned long long seriLeng = OBJE_CONTE_LEN;
    //
    class vector <T *>::iterator iter;
    for (iter = inserVecto.begin(); iter != inserVecto.end(); ++iter) {
        if (EntitKits::SeriObje(ESCA_ECONTE_POSI(objePsts), &seriLeng, *(*iter)))
            return -1;
        MAKE_ESCHEAD_BINA(objePsts, seriLeng)
        // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
        resp_data_t const_resp;
        int inser_valu = lev3_const_inser(&const_resp, mpOSEVClie, &moLevThOBID, parms);
        if (inser_valu) {
            // CLIEPF("const insert ERROR!\n");
            return inser_valu;
        }
        IRKeyVal::RTypObid kvObid;
        EntitKits::DeseRKV(kvObid, &const_resp);
        if (IS_INVAL_OBID(&kvObid.obje_obid)) return -1;
        OBID_BINARY_COPY(&((*iter))->obje_obid, &kvObid.obje_obid)
    }
    //
    return 0x00;
}

//
#include "InlineLev/LevThSearch.h"
#include "InlineLev/LevThInvoke.h"

#endif /* BASE_LVTPH_H */

