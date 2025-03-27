
/* 
 * File:   LevThSearch.h
 * Author: James Xu
 *
 * Created on 2023.11.16, PM 3:33
 */

#ifndef LEVTH_SEARCH_H
#define LEVTH_SEARCH_H

// checked

template <class T> int BASELevTh::Search(T &searObje) {
    CHECK_LVTP_ATTRIBU(T::clVersion, mpOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevTh::Search\n");
    const char *parms[0x01] = {NULL};
    // CLIEPF("parms[0x00]:|%s|, parms[0x01]:|%s|\n", parms[0x00], parms[0x01]);
    resp_data_t const_resp;
    int searo_valu = lev3_const_searo(&const_resp, mpOSEVClie, &moLevThOBID, parms);
    if (searo_valu) {
        // CLIEPF("resp_code:%u\n", searo_valu);
        return searo_valu;
    }
    EntitKits::DeseObje(searObje, &const_resp);
    //
    return 0x00;
}

// checked

template <class T> int BASELevTh::Search(T &searObje, const string &prediStri) {
    CHECK_LVTP_ATTRIBU(T::clVersion, mpOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevTh::Search\n");
    if ("" == prediStri) return -1;
    //
    const char *parms[0x02] = {(char *) prediStri.c_str(), NULL};
    // CLIEPF("parms[0x00]:|%s|, parms[0x01]:|%s|\n", parms[0x00], parms[0x01]);
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    //
    resp_data_t const_resp;
    int searo_valu = lev3_const_searo(&const_resp, mpOSEVClie, &moLevThOBID, parms);
    if (searo_valu) {
        // CLIEPF("resp_code:%u\n", searo_valu);
        return searo_valu;
    }
    EntitKits::DeseObje(searObje, &const_resp);
    //
    return 0x00;
}

// checked

template <class T> int BASELevTh::Search(T &searObje, const osv_oid_t &condiOBID) {
    CHECK_LVTP_ATTRIBU(T::clVersion, mpOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevTh::Search\n");
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x02] = {cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    // CLIEPF("parms[0x00]:|%s|, parms[0x01]:|%s|\n", parms[0x00], parms[0x01]);
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    //
    resp_data_t const_resp;
    int searo_valu = lev3_const_searo(&const_resp, mpOSEVClie, &moLevThOBID, parms);
    if (searo_valu) {
        // CLIEPF("resp_code:%u\n", searo_valu);
        return searo_valu;
    }
    EntitKits::DeseObje(searObje, &const_resp);
    //
    return 0x00;
}

// checked

template <class T> int BASELevTh::Search(vector <T *> &searVecto) {
    CHECK_LVTP_ATTRIBU(T::clVersion, mpOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevTh::Search\n");
    const char *parms[0x01] = {NULL};
    // CLIEPF("parms[0x00]:|%s|, parms[0x01]:|%s|\n", parms[0x00], parms[0x01]);
    //
    resp_data_t const_resp;
    int searo_valu = lev3_const_searo(&const_resp, mpOSEVClie, &moLevThOBID, parms);
    if (searo_valu) {
        // CLIEPF("resp_code:%u\n", searo_valu);
        return searo_valu;
    }
    if (EntitKits::DeseObjeVect(searVecto, &const_resp))
        return -1;
    //
    return 0x00;
}

// checked

template <class T> int BASELevTh::Search(vector <T *> &searVecto, const string &prediStri) {
    CHECK_LVTP_ATTRIBU(T::clVersion, mpOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevTh::Search\n");
    if ("" == prediStri) return -1;
    //
    const char *parms[0x02] = {(char *) prediStri.c_str(), NULL};
    // CLIEPF("parms[0x00]:|%s|, parms[0x01]:|%s|\n", parms[0x00], parms[0x01]);
    //
    resp_data_t const_resp;
    int searo_valu = lev3_const_searo(&const_resp, mpOSEVClie, &moLevThOBID, parms);
    if (searo_valu) {
        // CLIEPF("resp_code:%u\n", searo_valu);
        return searo_valu;
    }
    if (EntitKits::DeseObjeVect(searVecto, &const_resp))
        return -1;
    //
    return 0x00;
}

// checked

template <class T> int BASELevTh::Search(vector <T *> &searVecto, const osv_oid_t &condiOBID) {
    CHECK_LVTP_ATTRIBU(T::clVersion, mpOSEVClie, T::spLevTPName, T::suChkAttribCount)
    // CLIEPF("[FUNC]:BASELevTh::Search\n");
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x02] = {cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    // CLIEPF("parms[0x00]:|%s|, parms[0x01]:|%s|\n", parms[0x00], parms[0x01]);
    //
    resp_data_t const_resp;
    int searo_valu = lev3_const_searo(&const_resp, mpOSEVClie, &moLevThOBID, parms);
    if (searo_valu) {
        // CLIEPF("resp_code:%u\n", searo_valu);
        return searo_valu;
    }
    if (EntitKits::DeseObjeVect(searVecto, &const_resp))
        return -1;
    //
    return 0x00;
}

#endif /* LEVTH_SEARCH_H */

