
#include "third_party.h"
#include "osev_common/commo_header.h"

#include "proto_conne/conve_utili.h"
#include "parser/parsing.h"
#include "function/funct_header.h"

#include "ClieMacro.h"
#include "ErcodClie.h"
#include "proto_conne/proto_conne.h"
#include "ChkLvtpAtti.h"
#include "ClieTokit/EntitKits.h"
#include "InvoRType.h"
#include "ClieTokit/InserKits.h"

#include "BASELevTh.h"
#include "debug_funct_cpp.h"
#include "proto_conne/conatt.h"

BASELevTh::BASELevTh() {
}

BASELevTh::~BASELevTh() {
}

//

int BASELevTh::Build(const string &levThName, const osv_oid_t &levThOBID, const osev_clie *pOSEVClie) {
    moLevThName = levThName;
    OBID_BINARY_COPY(&moLevThOBID, &levThOBID)
    mpOSEVClie = pOSEVClie;
    return 0x00;
}

//

int BASELevTh::Echo(string &echoValu) {
    CLIEPF("[FUNC]:BASELevTh::Echo\n");
    const char *parms[0x01] = {NULL};
    resp_data_t const_resp;
    int echo_valu = lev3_const_statu(&const_resp, mpOSEVClie, &moLevThOBID, ESTAT_ECHO, parms);
    if (!echo_valu) {
        const_resp.resp_memo[const_resp.content_length] = '\0';
        echoValu.assign(const_resp.resp_memo);
    }
    //
    return echo_valu;
}

// checked
// [txxt_con]lev3> txxt_con:create(66,100,222);
// parmStri = "66, 100, 222"
// parmStri = "(66, 100, 222)"

int BASELevTh::Create(const string &parmStri) { // checked
    CLIEPF("[FUNC]:BASELevTh::Create\n");
    if ("" == parmStri) return -1;
    //
    const char *creat_pamvp[PARAM_COUNT];
    char _cline_[LARGE_CONTE_SIZE];
    if (split_instru_pamvs(creat_pamvp, _cline_, (char *) parmStri.c_str()))
        return -1;
    if (pretr_functi_pamvs(creat_pamvp))
        return -1;
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t const_resp;
    return lev3_const_creat(&const_resp, mpOSEVClie, &moLevThOBID, creat_pamvp);
}

// checked

int BASELevTh::Drop(const string & prediStri) {
    CLIEPF("[FUNC]:BASELevTh::Drop\n");
    if ("" == prediStri) return -1;
    //
    const char *parms[0x02] = {(char *) prediStri.c_str(), NULL};
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t const_resp;
    return lev3_const_drop(&const_resp, mpOSEVClie, &moLevThOBID, parms);
}

// checked

int BASELevTh::Drop(const osv_oid_t &dropOBID) {
    CLIEPF("[FUNC]:BASELevTh::Drop\n");
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x02] = {cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &dropOBID);
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t const_resp;
    return lev3_const_drop(&const_resp, mpOSEVClie, &moLevThOBID, parms);
}

// checked
// objeStri = "Func:Stroid("bb7ddcfb10c0ff6401000000"), 7.6, "cccddd"S, 100.44d, 222" 
// objeStri = "(Func:Stroid("bb7ddcfb10c0ff6401000000"), 7.6, "cccddd"S, 100.44d, 222)"

int BASELevTh::Update(const char *objeStri) {
    CLIEPF("[FUNC]:BASELevTh::Update\n");
    if (!objeStri || '\0' == objeStri[0x00]) return -1;
    //
    const char *updat_pamvp[PARAM_COUNT];
    char _cline_[LARGE_CONTE_SIZE];
    if (split_instru_pamvs(updat_pamvp, _cline_, (char *) objeStri))
        return -1;
    if (pretr_functi_pamvs(updat_pamvp))
        return -1;
    //
    char objePsts[ESCA_ENTICON_PART + OBJE_CONTE_LEN];
    const char *parms[0x02] = {objePsts, NULL};
    cont_atti conat;
    if (lev3_const_conat(&conat, mpOSEVClie, &moLevThOBID, FMTST_TIMEOUT_SECON))
        return -1;
    unsigned long long seriLeng = pack_list_loop(ESCA_ECONTE_POSI(objePsts), OBJE_CONTE_LEN, updat_pamvp, conat.fmtst);
    if (INVA_ULOLO_VALU == seriLeng)
        return -1;
    MAKE_ESCHEAD_BINA(objePsts, seriLeng)
    //
    resp_data_t const_resp;
    return lev3_const_updat(&const_resp, mpOSEVClie, &moLevThOBID, parms);
}

// checked
// objeStri = "Func:Stroid("bb7ddcfb10c0ff6401000000"), 7.6, "cccddd"S, 100.44d, 222" 
// objeStri = "(Func:Stroid("bb7ddcfb10c0ff6401000000"), 7.6, "cccddd"S, 100.44d, 222)"

int BASELevTh::Update(string & objeStri) {
    CLIEPF("[FUNC]:BASELevTh::Update\n");
    if ("" == objeStri) return -1;
    //
    const char *updat_pamvp[PARAM_COUNT];
    char _cline_[LARGE_CONTE_SIZE];
    if (split_instru_pamvs(updat_pamvp, _cline_, (char *) objeStri.c_str()))
        return -1;
    if (pretr_functi_pamvs(updat_pamvp))
        return -1;
    //
    char objePsts[ESCA_ENTICON_PART + OBJE_CONTE_LEN];
    const char *parms[0x02] = {objePsts, NULL};
    cont_atti conat;
    if (lev3_const_conat(&conat, mpOSEVClie, &moLevThOBID, FMTST_TIMEOUT_SECON))
        return -1;
    unsigned long long seriLeng = pack_list_loop(ESCA_ECONTE_POSI(objePsts), OBJE_CONTE_LEN, updat_pamvp, conat.fmtst);
    if (INVA_ULOLO_VALU == seriLeng)
        return -1;
    MAKE_ESCHEAD_BINA(objePsts, seriLeng)
    //
    resp_data_t const_resp;
    return lev3_const_updat(&const_resp, mpOSEVClie, &moLevThOBID, parms);
}

// checked
// objeStri = "Func:Stroid("bb7ddcfb10c0ff6401000000"), 7.6, "cccddd"S, 100.44d, 222" 
// objeStri = "(Func:Stroid("bb7ddcfb10c0ff6401000000"), 7.6, "cccddd"S, 100.44d, 222)"

int BASELevTh::Insert(osv_oid_t &newOBID, const string & objeStri) { // checked
    CLIEPF("[FUNC]:BASELevTh::Insert\n");
    if ("" == objeStri) return -1;
    //
    const char *inser_pamvp[PARAM_COUNT];
    char _cline_[LARGE_CONTE_SIZE];
    if (split_instru_pamvs(inser_pamvp, _cline_, (char *) objeStri.c_str()))
        return -1;
    if (pretr_functi_pamvs(inser_pamvp))
        return -1;
    //
    char objePsts[ESCA_ENTICON_PART + OBJE_CONTE_LEN];
    const char *parms[0x02] = {objePsts, NULL};
    cont_atti conat;
    if (lev3_const_conat(&conat, mpOSEVClie, &moLevThOBID, FMTST_TIMEOUT_SECON))
        return -1;
    CLIEPF("conat.fmtst:|%s|\n", conat.fmtst);
    unsigned long long seriLeng = pack_list_loop(ESCA_ECONTE_POSI(objePsts), OBJE_CONTE_LEN, inser_pamvp, conat.fmtst);
    if (INVA_ULOLO_VALU == seriLeng)
        return -1;
    MAKE_ESCHEAD_BINA(objePsts, seriLeng)
    //
    resp_data_t const_resp;
    CLIEPF("[FUNC]:lev3_const_inser\n");
    int inser_valu = lev3_const_inser(&const_resp, mpOSEVClie, &moLevThOBID, parms);
    if (inser_valu) {
        CLIEPF("const insert ERROR!\n");
        return inser_valu;
    }
    IRKeyVal::RTypObid kvObid;
    EntitKits::DeseRKV(kvObid, &const_resp);
    if (IS_INVAL_OBID(&kvObid.obje_obid)) return -1;
    OBID_BINARY_COPY(&newOBID, &kvObid.obje_obid)
            //
    return 0x00;
}

// checked

int BASELevTh::Search(resp_data_t * const_resp) {
    CLIEPF("[FUNC]:BASELevTh::Search\n");
    const char *parms[0x01] = {NULL};
    return lev3_const_searo(const_resp, mpOSEVClie, &moLevThOBID, parms);
}

// checked

int BASELevTh::Search(resp_data_t *const_resp, const string & prediStri) {
    CLIEPF("[FUNC]:BASELevTh::Search\n");
    if ("" == prediStri) return -1;
    //
    const char *parms[0x02] = {(char *) prediStri.c_str(), NULL};
    return lev3_const_searo(const_resp, mpOSEVClie, &moLevThOBID, parms);
}

// checked

int BASELevTh::Search(resp_data_t *const_resp, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevTh::Search\n");
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x02] = {cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    return lev3_const_searo(const_resp, mpOSEVClie, &moLevThOBID, parms);
}

// checked

int BASELevTh::Invoke(const string & invokStri) {
    CLIEPF("[FUNC]:BASELevTh::Invoke\n");
    if ("" == invokStri) return -1;
    //
    const char *parms[0x02] = {(char *) invokStri.c_str(), NULL};
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t const_resp;
    return lev3_const_invok(&const_resp, mpOSEVClie, &moLevThOBID, parms);
}

// checked

int BASELevTh::Invoke(const string &invokStri, const string & prediStri) {
    CLIEPF("[FUNC]:BASELevTh::Invoke\n");
    if ("" == invokStri || "" == prediStri)
        return -1;
    //
    const char *parms[0x03] = {(char *) invokStri.c_str(), (char *) prediStri.c_str(), NULL};
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    resp_data_t const_resp;
    return lev3_const_invok(&const_resp, mpOSEVClie, &moLevThOBID, parms);
}

// checked

int BASELevTh::Invoke(const string &invokStri, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevTh::Invoke\n");
    if ("" == invokStri) return -1;
    //
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {(char *) invokStri.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t const_resp;
    return lev3_const_invok(&const_resp, mpOSEVClie, &moLevThOBID, parms);
}

//

int BASELevTh::Invoke(resp_data_t *const_resp, const string &invokStri) {
    CLIEPF("[FUNC]:BASELevTh::Invoke\n");
    if ("" == invokStri) return -1;
    //
    const char *parms[0x02] = {(char *) invokStri.c_str(), NULL};
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    return lev3_const_invok(const_resp, mpOSEVClie, &moLevThOBID, parms);
}

int BASELevTh::Invoke(resp_data_t *const_resp, const string &invokStri, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevTh::Invoke\n");
    if ("" == invokStri || "" == prediStri)
        return -1;
    //
    const char *parms[0x03] = {(char *) invokStri.c_str(), (char *) prediStri.c_str(), NULL};
    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    return lev3_const_invok(const_resp, mpOSEVClie, &moLevThOBID, parms);
}

int BASELevTh::Invoke(resp_data_t *const_resp, const string &invokStri, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevTh::Invoke\n");
    if ("" == invokStri) return -1;
    //
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {(char *) invokStri.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    return lev3_const_invok(const_resp, mpOSEVClie, &moLevThOBID, parms);
}


