
/* 
 * File:   LevThInvoke.h
 * Author: James Xu
 *
 * Created on 2023.11.16., PM 3:33
 */

#ifndef LEVTH_INVOKE_H
#define LEVTH_INVOKE_H

// checked

template <class T> int BASELevTh::Invoke(T &ivkRObje, const string &invokStri) {
    // CLIEPF("[FUNC]:BASELevTh::Invoke\n");
    if ("" == invokStri) return -1;
    //
    const char *parms[0x02] = {(char *) invokStri.c_str(), NULL};
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t const_resp;
    int invo_valu = lev3_const_invok(&const_resp, mpOSEVClie, &moLevThOBID, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKV(ivkRObje, &const_resp);
    //
    return 0x00;
}
// checked

template <class T> int BASELevTh::Invoke(T &ivkRObje, const string &invokStri, const string &prediStri) {
    // CLIEPF("[FUNC]:BASELevTh::Invoke\n");
    if ("" == invokStri || "" == prediStri)
        return -1;
    //
    const char *parms[0x03] = {(char *) invokStri.c_str(), (char *) prediStri.c_str(), NULL};
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t const_resp;
    int invo_valu = lev3_const_invok(&const_resp, mpOSEVClie, &moLevThOBID, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKV(ivkRObje, &const_resp);
    //
    return 0x00;
}
// checked

template <class T> int BASELevTh::Invoke(T &ivkRObje, const string &invokStri, const osv_oid_t &condiOBID) {
    // CLIEPF("[FUNC]:BASELevTh::Invoke\n");
    if ("" == invokStri) return -1;
    //
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {(char *) invokStri.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t const_resp;
    int invo_valu = lev3_const_invok(&const_resp, mpOSEVClie, &moLevThOBID, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKV(ivkRObje, &const_resp);
    //
    return 0x00;
}

// checked

template <class T> int BASELevTh::Invoke(vector <T *> &ivkRVecto, const string &invokStri) {
    // CLIEPF("[FUNC]:BASELevTh::Invoke\n");
    if ("" == invokStri) return -1;
    //
    const char *parms[0x02] = {(char *) invokStri.c_str(), NULL};
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t const_resp;
    int invo_valu = lev3_const_invok(&const_resp, mpOSEVClie, &moLevThOBID, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKVVect(ivkRVecto, &const_resp);
    //
    return 0x00;
}

// checked

template <class T> int BASELevTh::Invoke(vector <T *> &ivkRVecto, const string &invokStri, const string &prediStri) {
    // CLIEPF("[FUNC]:BASELevTh::Invoke\n");
    if ("" == invokStri || "" == prediStri)
        return -1;
    //
    const char *parms[0x03] = {(char *) invokStri.c_str(), (char *) prediStri.c_str(), NULL};
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t const_resp;
    int invo_valu = lev3_const_invok(&const_resp, mpOSEVClie, &moLevThOBID, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKVVect(ivkRVecto, &const_resp);
    //
    return 0x00;
}

// checked

template <class T> int BASELevTh::Invoke(vector <T *> &ivkRVecto, const string &invokStri, const osv_oid_t &condiOBID) {
    // CLIEPF("[FUNC]:BASELevTh::Invoke\n");
    if ("" == invokStri) return -1;
    //
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {(char *) invokStri.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t const_resp;
    int invo_valu = lev3_const_invok(&const_resp, mpOSEVClie, &moLevThOBID, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKVVect(ivkRVecto, &const_resp);
    //
    return 0x00;
}

#endif /* LEVTH_INVOKE_H */

