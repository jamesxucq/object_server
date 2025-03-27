
/* 
 * File:   LevFPInvoke.h
 * Author: James Xu
 *
 * Created on 2023.11.16, PM 3:32
 */

#ifndef LEVFP_INVOKE_H
#define LEVFP_INVOKE_H

// checked

template <class T> int BASELevFP::Invoke(T &ivkRObje, const string &invoConta, const string &invokStri) {
    // CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invoConta || "" == invokStri)
        return -1;
    //
    const char *parms[0x03] = {(char *) invoConta.c_str(), (char *) invokStri.c_str(), NULL};
    resp_data_t query_resp;
    int invo_valu = lv4p_query_invok(&query_resp, &moOSEVClie, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKV(ivkRObje, &query_resp);
    //
    return 0x00;
}
// checked

template <class T> int BASELevFP::Invoke(T &ivkRObje, const string &invoConta, const string &invokStri, const string &prediStri) {
    // CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invoConta || "" == invokStri || "" == prediStri)
        return -1;
    //
    const char *parms[0x04] = {(char *) invoConta.c_str(), (char *) invokStri.c_str(), (char *) prediStri.c_str(), NULL};
    resp_data_t query_resp;
    int invo_valu = lv4p_query_invok(&query_resp, &moOSEVClie, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKV(ivkRObje, &query_resp);
    //
    return 0x00;
}
// checked

template <class T> int BASELevFP::Invoke(T &ivkRObje, const string &invoConta, const string &invokStri, const osv_oid_t &condiOBID) {
    // CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invoConta || "" == invokStri)
        return -1;
    //
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {(char *) invoConta.c_str(), (char *) invokStri.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    int invo_valu = lv4p_query_invok(&query_resp, &moOSEVClie, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKV(ivkRObje, &query_resp);
    //
    return 0x00;
}
// checked

template <class T> int BASELevFP::Invoke(vector <T *> &ivkRVecto, const string &invoConta, const string &invokStri) {
    // CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invoConta || "" == invokStri)
        return -1;
    //
    const char *parms[0x03] = {(char *) invoConta.c_str(), (char *) invokStri.c_str(), NULL};
    resp_data_t query_resp;
    int invo_valu = lv4p_query_invok(&query_resp, &moOSEVClie, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKVVect(ivkRVecto, &query_resp);
    //
    return 0x00;
}
// checked

template <class T> int BASELevFP::Invoke(vector <T *> &ivkRVecto, const string &invoConta, const string &invokStri, const string &prediStri) {
    // CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invoConta || "" == invokStri || "" == prediStri)
        return -1;
    //
    const char *parms[0x04] = {(char *) invoConta.c_str(), (char *) invokStri.c_str(), (char *) prediStri.c_str(), NULL};
    resp_data_t query_resp;
    int invo_valu = lv4p_query_invok(&query_resp, &moOSEVClie, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKVVect(ivkRVecto, &query_resp);
    //
    return 0x00;
}
// checked

template <class T> int BASELevFP::Invoke(vector <T *> &ivkRVecto, const string &invoConta, const string &invokStri, const osv_oid_t &condiOBID) {
    // CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invoConta || "" == invokStri)
        return -1;
    //
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {(char *) invoConta.c_str(), (char *) invokStri.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    int invo_valu = lv4p_query_invok(&query_resp, &moOSEVClie, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKVVect(ivkRVecto, &query_resp);
    //
    return 0x00;
}

////////////////////////////////////////////////////////////////////////////////

// checked

template <class T> int BASELevFP::Invoke(T &ivkRObje, Contain &invoConta, const string &invokStri) {
    // CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invokStri) return -1;
    //
    char invoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {invoOBID, (char *) invokStri.c_str(), NULL};
    ESMCPY_OBID(invoOBID, &invoConta.moLevThOBID);
    //
    resp_data_t query_resp;
    int invo_valu = lv4p_query_invok(&query_resp, &moOSEVClie, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKV(ivkRObje, &query_resp);
    //
    return 0x00;
}
// checked

template <class T> int BASELevFP::Invoke(T &ivkRObje, Contain &invoConta, const string &invokStri, const string &prediStri) {
    // CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invokStri || "" == prediStri)
        return -1;
    //
    char invoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {invoOBID, (char *) invokStri.c_str(), (char *) prediStri.c_str(), NULL};
    ESMCPY_OBID(invoOBID, &invoConta.moLevThOBID);
    //
    resp_data_t query_resp;
    int invo_valu = lv4p_query_invok(&query_resp, &moOSEVClie, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKV(ivkRObje, &query_resp);
    //
    return 0x00;
}
// checked

template <class T> int BASELevFP::Invoke(T &ivkRObje, Contain &invoConta, const string &invokStri, const osv_oid_t &condiOBID) {
    // CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invokStri) return -1;
    //
    char invoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {invoOBID, (char *) invokStri.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(invoOBID, &invoConta.moLevThOBID);
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    int invo_valu = lv4p_query_invok(&query_resp, &moOSEVClie, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKV(ivkRObje, &query_resp);
    //
    return 0x00;
}
// checked

template <class T> int BASELevFP::Invoke(vector <T *> &ivkRVecto, Contain &invoConta, const string &invokStri) {
    // CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invokStri) return -1;
    //
    char invoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {invoOBID, (char *) invokStri.c_str(), NULL};
    ESMCPY_OBID(invoOBID, &invoConta.moLevThOBID);
    //
    resp_data_t query_resp;
    int invo_valu = lv4p_query_invok(&query_resp, &moOSEVClie, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKVVect(ivkRVecto, &query_resp);
    //
    return 0x00;
}
// checked

template <class T> int BASELevFP::Invoke(vector <T *> &ivkRVecto, Contain &invoConta, const string &invokStri, const string &prediStri) {
    // CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invokStri || "" == prediStri)
        return -1;
    //
    char invoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {invoOBID, (char *) invokStri.c_str(), (char *) prediStri.c_str(), NULL};
    ESMCPY_OBID(invoOBID, &invoConta.moLevThOBID);
    //
    resp_data_t query_resp;
    int invo_valu = lv4p_query_invok(&query_resp, &moOSEVClie, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKVVect(ivkRVecto, &query_resp);
    //
    return 0x00;
}
// checked

template <class T> int BASELevFP::Invoke(vector <T *> &ivkRVecto, Contain &invoConta, const string &invokStri, const osv_oid_t &condiOBID) {
    // CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invokStri) return -1;
    //
    char invoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {invoOBID, (char *) invokStri.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(invoOBID, &invoConta.moLevThOBID);
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    int invo_valu = lv4p_query_invok(&query_resp, &moOSEVClie, parms);
    if (invo_valu) {
        // CLIEPF("resp_code:%u\n", invo_valu);
        return invo_valu;
    }
    EntitKits::DeseRKVVect(ivkRVecto, &query_resp);
    //
    return 0x00;
}

#endif /* LEVFP_INVOKE_H */

