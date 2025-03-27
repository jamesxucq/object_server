
/* 
 * File:   LevFPFactory.h
 * Author: James Xu
 *
 * Created on 2023.11.16, PM 3:32
 */

#ifndef LEVFP_FACTORY_H
#define LEVFP_FACTORY_H

////////////////////////////////////////////////////////////////////////////////
// const string &srcConta
////////////////////////////////////////////////////////////////////////////////

// checked

template <class T> int BASELevFP::Factory(T &factoObje, const string &srcConta, const string &prediStri) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == srcConta || "" == prediStri)
        return -1;
    //
    const char *parms[0x04] = {T::spLevTPName, (char *) srcConta.c_str(), (char *) prediStri.c_str(), NULL};
    resp_data_t query_resp;
    int facto_valu = lv4p_query_facto(&query_resp, &moOSEVClie, parms);
    if (facto_valu) {
        // CLIEPF("resp_code:%d\n", facto_valu);
        return facto_valu;
    }
    if (EntitKits::DeseObje(factoObje, &query_resp)) {
        // CLIEPF("deseri factory ERROR!\n");
        return -1;
    }
    //
    return 0x00;
}

// checked

template <class T> int BASELevFP::Factory(T &factoObje, const string &srcConta, const osv_oid_t &condiOBID) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == srcConta)
        return -1;
    //
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {T::spLevTPName, (char *) srcConta.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    int facto_valu = lv4p_query_facto(&query_resp, &moOSEVClie, parms);
    if (facto_valu) {
        // CLIEPF("resp_code:%d\n", facto_valu);
        return facto_valu;
    }
    if (EntitKits::DeseObje(factoObje, &query_resp)) {
        // CLIEPF("deseri factory ERROR!\n");
        return -1;
    }
    //
    return 0x00;
}

// checked

template <class T> int BASELevFP::Factory(vector <T *> &factoVecto, const string &srcConta) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == srcConta) return -1;
    //
    const char *parms[0x03] = {T::spLevTPName, (char *) srcConta.c_str(), NULL};
    resp_data_t query_resp;
    int facto_valu = lv4p_query_facto(&query_resp, &moOSEVClie, parms);
    if (facto_valu) {
        // CLIEPF("resp_code:%d\n", facto_valu);
        return facto_valu;
    }
    if (EntitKits::DeseObjeVect(factoVecto, &query_resp)) {
        // CLIEPF("deseri factory ERROR!\n");
        return -1;
    }
    //
    return 0x00;
}

// checked

template <class T> int BASELevFP::Factory(vector <T *> &factoVecto, const string &srcConta, const string &prediStri) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == srcConta || "" == prediStri)
        return -1;
    //
    const char *parms[0x04] = {T::spLevTPName, (char *) srcConta.c_str(), (char *) prediStri.c_str(), NULL};
    resp_data_t query_resp;
    int facto_valu = lv4p_query_facto(&query_resp, &moOSEVClie, parms);
    if (facto_valu) {
        // CLIEPF("resp_code:%d\n", facto_valu);
        return facto_valu;
    }
    if (EntitKits::DeseObjeVect(factoVecto, &query_resp)) {
        // CLIEPF("deseri factory ERROR!\n");
        return -1;
    }
    //
    return 0x00;
}

// checked

template <class T> int BASELevFP::Factory(vector <T *> &factoVecto, const string &srcConta, const osv_oid_t &condiOBID) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == srcConta)
        return -1;
    //
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {T::spLevTPName, (char *) srcConta.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    int facto_valu = lv4p_query_facto(&query_resp, &moOSEVClie, parms);
    if (facto_valu) {
        // CLIEPF("resp_code:%d\n", facto_valu);
        return facto_valu;
    }
    if (EntitKits::DeseObjeVect(factoVecto, &query_resp)) {
        // CLIEPF("deseri factory ERROR!\n");
        return -1;
    }
    //
    return 0x00;
}

////////////////////////////////////////////////////////////////////////////////
// Contain &srcConta
////////////////////////////////////////////////////////////////////////////////

// checked

template <class T> int BASELevFP::Factory(T &factoObje, Contain &srcConta, const string &prediStri) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == prediStri) return -1;
    //
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {T::spLevTPName, srcOBID, (char *) prediStri.c_str(), NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    //
    resp_data_t query_resp;
    int facto_valu = lv4p_query_facto(&query_resp, &moOSEVClie, parms);
    if (facto_valu) {
        // CLIEPF("resp_code:%d\n", facto_valu);
        return facto_valu;
    }
    if (EntitKits::DeseObje(factoObje, &query_resp)) {
        // CLIEPF("deseri factory ERROR!\n");
        return -1;
    }
    //
    return 0x00;
}

// checked

template <class T> int BASELevFP::Factory(T &factoObje, Contain &srcConta, const osv_oid_t &condiOBID) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevFP::Factory\n");
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {T::spLevTPName, srcOBID, cpmoOBID, NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    int facto_valu = lv4p_query_facto(&query_resp, &moOSEVClie, parms);
    if (facto_valu) {
        // CLIEPF("resp_code:%d\n", facto_valu);
        return facto_valu;
    }
    if (EntitKits::DeseObje(factoObje, &query_resp)) {
        // CLIEPF("deseri factory ERROR!\n");
        return -1;
    }
    //
    return 0x00;
}

// checked

template <class T> int BASELevFP::Factory(vector <T *> &factoVecto, Contain &srcConta) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevFP::Factory\n");
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {T::spLevTPName, srcOBID, NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    //
    resp_data_t query_resp;
    int facto_valu = lv4p_query_facto(&query_resp, &moOSEVClie, parms);
    if (facto_valu) {
        // CLIEPF("resp_code:%d\n", facto_valu);
        return facto_valu;
    }
    if (EntitKits::DeseObjeVect(factoVecto, &query_resp)) {
        // CLIEPF("deseri factory ERROR!\n");
        return -1;
    }
    //
    return 0x00;
}

// checked

template <class T> int BASELevFP::Factory(vector <T *> &factoVecto, Contain &srcConta, const string &prediStri) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == prediStri) return -1;
    //
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {T::spLevTPName, srcOBID, (char *) prediStri.c_str(), NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    //
    resp_data_t query_resp;
    int facto_valu = lv4p_query_facto(&query_resp, &moOSEVClie, parms);
    if (facto_valu) {
        // CLIEPF("resp_code:%d\n", facto_valu);
        return facto_valu;
    }
    if (EntitKits::DeseObjeVect(factoVecto, &query_resp)) {
        // CLIEPF("deseri factory ERROR!\n");
        return -1;
    }
    //
    return 0x00;
}

// checked

template <class T> int BASELevFP::Factory(vector <T *> &factoVecto, Contain &srcConta, const osv_oid_t &condiOBID) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevFP::Factory\n");
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {T::spLevTPName, srcOBID, cpmoOBID, NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    int facto_valu = lv4p_query_facto(&query_resp, &moOSEVClie, parms);
    if (facto_valu) {
        // CLIEPF("resp_code:%d\n", facto_valu);
        return facto_valu;
    }
    if (EntitKits::DeseObjeVect(factoVecto, &query_resp)) {
        // CLIEPF("deseri factory ERROR!\n");
        return -1;
    }
    //
    return 0x00;
}

////////////////////////////////////////////////////////////////////////////////
// Contain &srcContaI, Contain &srcContaII
////////////////////////////////////////////////////////////////////////////////

// checked

template <class T> int BASELevFP::Factory(T &factoObje, Contain &srcContaI, Contain &srcContaII, const string &prediStri) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == prediStri) return -1;
    //
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x04] = {T::spLevTPName, srcOBID, (char *) prediStri.c_str(), NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    int facto_valu = lv4p_query_facto(&query_resp, &moOSEVClie, parms);
    if (facto_valu) {
        // CLIEPF("resp_code:%d\n", facto_valu);
        return facto_valu;
    }
    if (EntitKits::DeseObje(factoObje, &query_resp)) {
        // CLIEPF("deseri factory ERROR!\n");
        return -1;
    }
    //
    return 0x00;
}

// checked

template <class T> int BASELevFP::Factory(T &factoObje, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevFP::Factory\n");
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    char cpmoOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x04] = {T::spLevTPName, srcOBID, cpmoOBID, NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    ESMCPY_BINARY_II(cpmoOBID, &condiOBID_I, &condiOBID_II, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    int facto_valu = lv4p_query_facto(&query_resp, &moOSEVClie, parms);
    if (facto_valu) {
        // CLIEPF("resp_code:%d\n", facto_valu);
        return facto_valu;
    }
    if (EntitKits::DeseObje(factoObje, &query_resp)) {
        // CLIEPF("deseri factory ERROR!\n");
        return -1;
    }
    //
    return 0x00;
}

// checked

template <class T> int BASELevFP::Factory(vector <T *> &factoVecto, Contain &srcContaI, Contain &srcContaII) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevFP::Factory\n");
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x03] = {T::spLevTPName, srcOBID, NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    int facto_valu = lv4p_query_facto(&query_resp, &moOSEVClie, parms);
    if (facto_valu) {
        // CLIEPF("resp_code:%d\n", facto_valu);
        return facto_valu;
    }
    if (EntitKits::DeseObjeVect(factoVecto, &query_resp)) {
        // CLIEPF("deseri factory ERROR!\n");
        return -1;
    }
    //
    return 0x00;
}

// checked

template <class T> int BASELevFP::Factory(vector <T *> &factoVecto, Contain &srcContaI, Contain &srcContaII, const string &prediStri) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == prediStri) return -1;
    //
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x04] = {T::spLevTPName, srcOBID, (char *) prediStri.c_str(), NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    int facto_valu = lv4p_query_facto(&query_resp, &moOSEVClie, parms);
    if (facto_valu) {
        // CLIEPF("resp_code:%d\n", facto_valu);
        return facto_valu;
    }
    if (EntitKits::DeseObjeVect(factoVecto, &query_resp)) {
        // CLIEPF("deseri factory ERROR!\n");
        return -1;
    }
    //
    return 0x00;
}

// checked

template <class T> int BASELevFP::Factory(vector <T *> &factoVecto, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II) {
    CHECK_LVTP_ATTRIBU(T::clVersion, &moOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevFP::Factory\n");
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    char cpmoOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x04] = {T::spLevTPName, srcOBID, cpmoOBID, NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    ESMCPY_BINARY_II(cpmoOBID, &condiOBID_I, &condiOBID_II, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    int facto_valu = lv4p_query_facto(&query_resp, &moOSEVClie, parms);
    if (facto_valu) {
        // CLIEPF("resp_code:%d\n", facto_valu);
        return facto_valu;
    }
    if (EntitKits::DeseObjeVect(factoVecto, &query_resp)) {
        // CLIEPF("deseri factory ERROR!\n");
        return -1;
    }
    //
    return 0x00;
}

#endif /* LEVFP_FACTORY_H */

