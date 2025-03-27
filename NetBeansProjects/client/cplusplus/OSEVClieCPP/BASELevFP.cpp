
#include "third_party.h"
#include "osev_common/commo_header.h"

#include "ClieMacro.h"
#include "ErcodClie.h"
#include "proto_conne/proto_conne.h"
#include "ChkLvtpAtti.h"
#include "ClieTokit/EntitKits.h"
#include "InvoRType.h"
#include "ClieTokit/InserKits.h"
#include "BASELevTh.h"
#include "parser/parse_respo.h"
#include "proto_conne/conve_utili.h"

#include "BASELevFP.h"
#include "debug_funct_cpp.h"

//

BASELevFP::BASELevFP() {
    // pthread_mutex_init(&m_ContainObj_Mutex, NULL);
    moContainObjHM = creat_actio(dele_cont, CONTA_BACKET_SIZE);
}

//

BASELevFP::~BASELevFP() {
    CLIEPF("[FUNC]:BASELevFP::~BASELevFP => done_clie_destroy\n");
    resp_head dest_resp;
    done_clie_destroy(&dest_resp, &moOSEVClie);
    if (moContainObjHM)
        action_destroy(moContainObjHM);
    // pthread_mutex_destroy(&m_ContainObj_Mutex);
}

//

cont_valu_t *BASELevFP::FindContain(const char *contName) {
    CLIEPF("[FUNC]:BASELevFP::FindContain\n");
    if (!moContainObjHM) {
        moContainObjHM = creat_actio(dele_cont, CONTA_BACKET_SIZE);
        if (!moContainObjHM)
            return NULL;
    }
    // CLIEPF("find_conta_bzl, start. contName:%s\n", contName);
    cont_valu_t *cvalu;
    cvalu = (cont_valu_t *) action_value(contName, moContainObjHM);
    if (cvalu) return cvalu;
    //
    const char *parms[0x02] = {contName, NULL};
    resp_data_t quer_resp;
    if (!lv4p_query_statu(&quer_resp, &moOSEVClie, QSTAT_ECHO, parms)) {
        CLIEPF("resp_memo:|%s|\n", quer_resp.resp_memo);
        cvalu = (cont_valu_t*) malloc(sizeof (cont_valu_t));
        // memcpy(&cvalu->contOBID, quer_resp.resp_memo, sizeof (osv_oid_t));
        if (parse_query_obid(&cvalu->contOBID, &quer_resp))
            return NULL;
        strcpy(cvalu->contName, contName);
        action_insert(cvalu->contName, cvalu, moContainObjHM);
    }
    //
#ifdef _DEBUG
    CLIEPF("status_code:|%x|\n", quer_resp.status_code);
    CLIEPF("contName:|%s|\n", contName);
    if (cvalu) {
        char oidStri[OBJE_IDENTI_ZLEN];
        CLIEPF("obid:|%s|\n", oidstr(oidStri, &cvalu->contOBID));
    }
#endif
    return cvalu;
}

//

void BASELevFP::ResetContain() {
    CLIEPF("[FUNC]:BASELevFP::ResetContain\n");
    if (moContainObjHM)
        action_clear(moContainObjHM);
}
//

void BASELevFP::EraseContain(const char *contName) {
    CLIEPF("[FUNC]:BASELevFP::EraseContain\n");
    CLIEPF("EraseContain, contName:|%s|\n", contName);
    if (moContainObjHM)
        action_remove(contName, moContainObjHM);
}

//

int BASELevFP::GetLevTh(Contain &contObje, const string &contName) {
    CLIEPF("[FUNC]:BASELevFP::GetLevTh\n");
    cont_valu_t *cvalu = FindContain((char *) contName.c_str());
    if (!cvalu) {
        CLIEPF("not find the contName:|%s|\n", (char *) contName.c_str());
        return -1;
    }
    // contObje.Create(contName, m_ConneSocket);
    contObje.Build(contName, cvalu->contOBID, &moOSEVClie);
    //
    return 0x00;
}

//

int BASELevFP::GetContain(Contain &contObje, const string &contName) {
    CLIEPF("[FUNC]:BASELevFP::GetContain\n");
    cont_valu_t *cvalu = FindContain((char *) contName.c_str());
    if (!cvalu) {
        CLIEPF("not find the contName:|%s|\n", (char *) contName.c_str());
        return -1;
    }
    // contObje.Create(contName, m_ConneSocket);
    contObje.Build(contName, cvalu->contOBID, &moOSEVClie);
    //
    return 0x00;
}

//

int BASELevFP::EchoOBID(osv_oid_t &contOBID, const string &echoConta) {
    CLIEPF("[FUNC]:BASELevFP::EchoOBID\n");
    const char *parms[0x02] = {(char *) echoConta.c_str(), NULL};
    resp_data_t query_resp;
    int echo_valu = lv4p_query_statu(&query_resp, &moOSEVClie, QSTAT_ECHO, parms);
    if (!echo_valu) {
        query_resp.resp_memo[query_resp.content_length] = '\0';
        // echoValu.assign(query_resp.resp_memo);
        OBID_BINARY_COPY(&contOBID, (osv_oid_t *) query_resp.resp_memo)
    }
    //
    return echo_valu;
}

int BASELevFP::EchoName(string &echoConta, const osv_oid_t &contOBID) {
    CLIEPF("[FUNC]:BASELevFP::EchoName\n");
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x02] = {cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &contOBID);
    //
    resp_data_t query_resp;
    int echo_valu = lv4p_query_statu(&query_resp, &moOSEVClie, QSTAT_ECHO, parms);
    if (!echo_valu) {
        query_resp.resp_memo[query_resp.content_length] = '\0';
        echoConta.assign(query_resp.resp_memo);
    }
    //
    return echo_valu;
}

int BASELevFP::Echo(string &echoValu) {
    CLIEPF("[FUNC]:BASELevFP::Echo\n");
    const char *parms[0x01] = {NULL};
    resp_data_t query_resp;
    int echo_valu = lv4p_query_statu(&query_resp, &moOSEVClie, QSTAT_ECHO, parms);
    if (!echo_valu) {
        query_resp.resp_memo[query_resp.content_length] = '\0';
        echoValu.assign(query_resp.resp_memo);
    }
    //
    return echo_valu;
}

int BASELevFP::Echo(string &echoValu, const string &echoConta) {
    CLIEPF("[FUNC]:BASELevFP::Echo\n");
    const char *parms[0x02] = {(char *) echoConta.c_str(), NULL};
    resp_data_t query_resp;
    int echo_valu = lv4p_query_statu(&query_resp, &moOSEVClie, QSTAT_ECHO, parms);
    if (!echo_valu) {
        query_resp.resp_memo[query_resp.content_length] = '\0';
        echoValu.assign(query_resp.resp_memo);
    }
    //
    return echo_valu;
}

int BASELevFP::Echo(string &echoValu, const osv_oid_t &contOBID) {
    CLIEPF("[FUNC]:BASELevFP::Echo\n");
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x02] = {cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &contOBID);
    //
    resp_data_t query_resp;
    int echo_valu = lv4p_query_statu(&query_resp, &moOSEVClie, QSTAT_ECHO, parms);
    if (!echo_valu) {
        query_resp.resp_memo[query_resp.content_length] = '\0';
        echoValu.assign(query_resp.resp_memo);
    }
    //
    return echo_valu;
}

// odb-lv4p> :create("txxt_iii_con", "witi", "txxt");

int BASELevFP::Create(const string &contName, const string &storaType, const string &lv2pName) {
    CLIEPF("[FUNC]:BASELevFP::Create\n");
    if ("" == contName || "" == lv2pName)
        return -1;
    PAMVS_CVALU(storaType, stora_engine_dict);
    if (!strcmp("INVA", (char *) storaType.c_str()))
        return -1;
    //
    const char *parms[0x04] = {(char *) contName.c_str(), (char *) storaType.c_str(), (char *) lv2pName.c_str(), NULL};
    resp_data_t query_resp;
    return lv4p_query_creat(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Create(Contain &contObje, const string &contName, const string &storaType, const string &lv2pName) {
    CLIEPF("[FUNC]:BASELevFP::Create\n");
    if ("" == contName || "" == lv2pName)
        return -1;
    PAMVS_CVALU(storaType, stora_engine_dict);
    if (!strcmp("INVA", (char *) storaType.c_str()))
        return -1;
    //
    const char *parms[0x04] = {(char *) contName.c_str(), (char *) storaType.c_str(), (char *) lv2pName.c_str(), NULL};
    resp_data_t query_resp;
    int creat_valu = lv4p_query_creat(&query_resp, &moOSEVClie, parms);
    if (creat_valu) {
        // CLIEPF("query insert ERROR!\n");
        return creat_valu;
    }
    //
    osv_oid_t contOBID;
    EntitKits::DeseOBID(contOBID, &query_resp);
    if (IS_INVAL_OBID(&contOBID)) return -1;
    contObje.Build(contName, contOBID, &moOSEVClie);
    //
    return 0x00;
}

// checked

int BASELevFP::Drop(const string &dropConta) {
    CLIEPF("[FUNC]:BASELevFP::Drop\n");
    if ("" == dropConta) return -1;
    //
    const char *parms[0x02] = {(char *) dropConta.c_str(), NULL};
    resp_data_t query_resp;
    return lv4p_query_drop(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Drop(const osv_oid_t &dropOBID) {
    CLIEPF("[FUNC]:BASELevFP::Drop\n");
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x02] = {cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &dropOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_drop(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Drop(Contain &dropObje) {
    CLIEPF("[FUNC]:BASELevFP::Drop\n");
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x02] = {cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &dropObje.moLevThOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_drop(&query_resp, &moOSEVClie, parms);
}


// todo

int BASELevFP::BASELevFP::Update(const string &updatConta, const string &attri, const string &value) {
    // CLIEPF("[FUNC]: Contain::Update\n");
    if ("" == value || "" == attri || "" == updatConta)
        return -1;
    //    // object parm style stream
    //    char objePsts[ESCA_ENTICON_PART + OBJE_CONTE_LEN];
    //    const char *parms[0x03] = {updatConta.c_str(), objePsts, NULL};
    //    unsigned long long seriLeng = OBJE_CONTE_LEN;
    //    EntitKits::SeriObje(ESCA_ECONTE_POSI(objePsts), &seriLeng, updatObje);
    //    MAKE_ESCHEAD_BINA(objePsts, seriLeng)
    //    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    //    resp_data_t query_resp;
    //    return lv4p_query_updat(&query_resp, &moOSEVClie, parms);
    return 0x00;
}

// todo

int BASELevFP::Update(Contain &updatConta) {
    // CLIEPF("[FUNC]: Contain::Update\n");
    //            char distOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    //    char objePsts[ESCA_ENTICON_PART + OBJE_CONTE_LEN];
    //    const char *parms[0x03] = {distOBID, objePsts, NULL};
    //    ESMCPY_OBID(distOBID, &updatConta.moLevThOBID);
    //    unsigned long long seriLeng = OBJE_CONTE_LEN;
    //    EntitKits::SeriObje(ESCA_ECONTE_POSI(objePsts), &seriLeng, updatObje);
    //    MAKE_ESCHEAD_BINA(objePsts, seriLeng)
    //    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    //    resp_data_t query_resp;
    //    return lv4p_query_updat(&query_resp, &moOSEVClie, parms);
    return 0x00;
}

// todo

int BASELevFP::Insert(const string &inserConta, const string &attri, const string &value) {
    // CLIEPF("[FUNC]:BASELevFP::Insert\n");
    if ("" == value || "" == attri || "" == inserConta)
        return -1;
    //
    //    char objePsts[ESCA_ENTICON_PART + OBJE_CONTE_LEN];
    //    const char *parms[0x03] = {inserConta.c_str(), objePsts, NULL};
    //    unsigned long long seriLeng = OBJE_CONTE_LEN;
    //    EntitKits::SeriObje(ESCA_ECONTE_POSI(objePsts), &seriLeng, inserObje);
    //    MAKE_ESCHEAD_BINA(objePsts, seriLeng)
    //    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    //    resp_data_t query_resp;
    //    int inser_valu = lv4p_query_inser(&query_resp, &moOSEVClie, parms);
    //    if (inser_valu) {
    //        // CLIEPF("query insert ERROR!\n");
    //        return inser_valu;
    //    }
    //    IRKeyVal::RTypObid kvObid;
    //    EntitKits::DeseRKV(kvObid, &query_resp);
    //    if (IS_INVAL_OBID(&kvObid.obje_obid)) return -1;
    //    OBID_BINARY_COPY(&inserObje.obje_obid, &kvObid.obje_obid)
    //
    return 0x00;
}

// todo

int BASELevFP::Insert(Contain &inserConta) {
    // CLIEPF("[FUNC]:BASELevFP::Insert\n");
    //
    //            char distOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    //    char objePsts[ESCA_ENTICON_PART + OBJE_CONTE_LEN];
    //    const char *parms[0x03] = {distOBID, objePsts, NULL};
    //    ESMCPY_OBID(distOBID, &inserConta.moLevThOBID);
    //    unsigned long long seriLeng = OBJE_CONTE_LEN;
    //    EntitKits::SeriObje(ESCA_ECONTE_POSI(objePsts), &seriLeng, inserObje);
    //    MAKE_ESCHEAD_BINA(objePsts, seriLeng)
    //    // CLIEPF("parms[0x00]:|%s|\n", parms[0x00]);
    //    resp_data_t query_resp;
    //    int inser_valu = lv4p_query_inser(&query_resp, &moOSEVClie, parms);
    //    if (inser_valu) {
    //        // CLIEPF("query insert ERROR!\n");
    //        return inser_valu;
    //    }
    //    IRKeyVal::RTypObid kvObid;
    //    EntitKits::DeseRKV(kvObid, &query_resp);
    //    if (IS_INVAL_OBID(&kvObid.obje_obid)) return -1;
    //    OBID_BINARY_COPY(&inserObje.obje_obid, &kvObid.obje_obid)
    //
    return 0x00;
}

// checked

int BASELevFP::Search(resp_data_t *query_resp, const string &lv2pDefin, const string &srcConta) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == srcConta) return -1;
    //
    const char *parms[0x03] = {lv2pDefin.c_str(), (char *) srcConta.c_str(), NULL};
    return lv4p_query_searq(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(resp_data_t *query_resp, const string &lv2pDefin, const string &srcConta, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == srcConta || "" == prediStri)
        return -1;
    //
    const char *parms[0x04] = {lv2pDefin.c_str(), (char *) srcConta.c_str(), (char *) prediStri.c_str(), NULL};
    return lv4p_query_searq(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(resp_data_t *query_resp, const string &lv2pDefin, const string &srcConta, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == srcConta) return -1;
    //
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {lv2pDefin.c_str(), (char *) srcConta.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    return lv4p_query_searq(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(const string &destConta, const string &srcConta) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == destConta || "" == srcConta)
        return -1;
    //
    const char *parms[0x03] = {(char *) destConta.c_str(), (char *) srcConta.c_str(), NULL};
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(const string &destConta, const string &srcConta, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == destConta || "" == srcConta || "" == prediStri)
        return -1;
    //
    const char *parms[0x04] = {(char *) destConta.c_str(), (char *) srcConta.c_str(), (char *) prediStri.c_str(), NULL};
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(const string &destConta, const string &srcConta, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == destConta || "" == srcConta)
        return -1;
    //
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {(char *) destConta.c_str(), (char *) srcConta.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(Contain &destConta, const string &srcConta) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == srcConta) return -1;
    //
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {destOBID, (char *) srcConta.c_str(), NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(Contain &destConta, const string &srcConta, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == srcConta || "" == prediStri)
        return -1;
    //
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {destOBID, (char *) srcConta.c_str(), (char *) prediStri.c_str(), NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(Contain &destConta, const string &srcConta, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == srcConta) return -1;
    //
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {destOBID, (char *) srcConta.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcConta) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {lv2pDefin.c_str(), srcOBID, NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    return lv4p_query_searq(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcConta, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == prediStri) return -1;
    //
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {lv2pDefin.c_str(), srcOBID, (char *) prediStri.c_str(), NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    return lv4p_query_searq(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcConta, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {lv2pDefin.c_str(), srcOBID, cpmoOBID, NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    return lv4p_query_searq(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(const string &destConta, Contain &srcConta) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == destConta) return -1;
    //
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {(char *) destConta.c_str(), srcOBID, NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(const string &destConta, Contain &srcConta, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == destConta || "" == prediStri)
        return -1;
    //
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {(char *) destConta.c_str(), srcOBID, (char *) prediStri.c_str(), NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(const string &destConta, Contain &srcConta, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == destConta) return -1;
    //
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {(char *) destConta.c_str(), srcOBID, cpmoOBID, NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(Contain &destConta, Contain &srcConta) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    //
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {destOBID, srcOBID, NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(Contain &destConta, Contain &srcConta, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == prediStri) return -1;
    //
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {destOBID, srcOBID, prediStri.c_str(), NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(Contain &destConta, Contain &srcConta, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {destOBID, srcOBID, cpmoOBID, NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcContaI, Contain &srcContaII) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x03] = {lv2pDefin.c_str(), srcOBID, NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    return lv4p_query_searq(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcContaI, Contain &srcContaII, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == prediStri) return -1;
    //
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x04] = {lv2pDefin.c_str(), srcOBID, (char *) prediStri.c_str(), NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    return lv4p_query_searq(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    char cpmoOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x04] = {lv2pDefin.c_str(), srcOBID, cpmoOBID, NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    ESMCPY_BINARY_II(cpmoOBID, &condiOBID_I, &condiOBID_II, sizeof (osv_oid_t));
    return lv4p_query_searq(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(const string &destConta, Contain &srcContaI, Contain &srcContaII) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == destConta) return -1;
    //
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x03] = {destConta.c_str(), srcOBID, NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(const string &destConta, Contain &srcContaI, Contain &srcContaII, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == destConta || "" == prediStri)
        return -1;
    //
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x04] = {destConta.c_str(), srcOBID, prediStri.c_str(), NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(const string &destConta, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == destConta) return -1;
    //
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    char cpmoOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x04] = {destConta.c_str(), srcOBID, cpmoOBID, NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    ESMCPY_BINARY_II(cpmoOBID, &condiOBID_I, &condiOBID_II, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(Contain &destConta, Contain &srcContaI, Contain &srcContaII) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    //
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x03] = {destOBID, srcOBID, NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(Contain &destConta, Contain &srcContaI, Contain &srcContaII, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    if ("" == prediStri) return -1;
    //
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x04] = {destOBID, srcOBID, prediStri.c_str(), NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Search(Contain &destConta, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II) {
    CLIEPF("[FUNC]:BASELevFP::Search\n");
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    char cpmoOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x04] = {destOBID, srcOBID, cpmoOBID, NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    ESMCPY_BINARY_II(cpmoOBID, &condiOBID_I, &condiOBID_II, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Invoke(const string &invoConta, const string &invokStri) {
    CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invoConta || "" == invokStri)
        return -1;
    //
    const char *parms[0x03] = {(char *) invoConta.c_str(), (char *) invokStri.c_str(), NULL};
    resp_data_t query_resp;
    return lv4p_query_invok(&query_resp, &moOSEVClie, parms);
}
// checked

int BASELevFP::Invoke(const string &invoConta, const string &invokStri, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invoConta || "" == invokStri || "" == prediStri)
        return -1;
    //
    const char *parms[0x04] = {(char *) invoConta.c_str(), (char *) invokStri.c_str(), (char *) prediStri.c_str(), NULL};
    resp_data_t query_resp;
    return lv4p_query_invok(&query_resp, &moOSEVClie, parms);
}
// checked

int BASELevFP::Invoke(const string &invoConta, const string &invokStri, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invoConta || "" == invokStri) return -1;
    //
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {(char *) invoConta.c_str(), (char *) invokStri.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_invok(&query_resp, &moOSEVClie, parms);
}

//

int BASELevFP::Invoke(resp_data_t *query_resp, const string &invoConta, const string &invokStri) {
    CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invokStri) return -1;
    //
    const char *parms[0x03] = {(char *) invoConta.c_str(), (char *) invokStri.c_str(), NULL};
    return lv4p_query_invok(query_resp, &moOSEVClie, parms);
}
// checked

int BASELevFP::Invoke(resp_data_t *query_resp, const string &invoConta, const string &invokStri, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invokStri || "" == prediStri)
        return -1;
    //
    const char *parms[0x04] = {(char *) invoConta.c_str(), (char *) invokStri.c_str(), (char *) prediStri.c_str(), NULL};
    return lv4p_query_invok(query_resp, &moOSEVClie, parms);
}
// checked

int BASELevFP::Invoke(resp_data_t *query_resp, const string &invoConta, const string &invokStri, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invokStri) return -1;
    //
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {(char *) invoConta.c_str(), (char *) invokStri.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    return lv4p_query_invok(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Invoke(Contain &invoConta, const string &invokStri) {
    CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invokStri) return -1;
    //
    char invoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {invoOBID, (char *) invokStri.c_str(), NULL};
    ESMCPY_OBID(invoOBID, &invoConta.moLevThOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_invok(&query_resp, &moOSEVClie, parms);
}
// checked

int BASELevFP::Invoke(Contain &invoConta, const string &invokStri, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invokStri || "" == prediStri)
        return -1;
    //
    char invoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {invoOBID, (char *) invokStri.c_str(), (char *) prediStri.c_str(), NULL};
    ESMCPY_OBID(invoOBID, &invoConta.moLevThOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_invok(&query_resp, &moOSEVClie, parms);
}
// checked

int BASELevFP::Invoke(Contain &invoConta, const string &invokStri, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invokStri) return -1;
    //
    char invoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {invoOBID, (char *) invokStri.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(invoOBID, &invoConta.moLevThOBID);
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_invok(&query_resp, &moOSEVClie, parms);
}

int BASELevFP::Invoke(resp_data_t *query_resp, Contain &invoConta, const string &invokStri) {
    CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invokStri) return -1;
    //
    char invoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {invoOBID, (char *) invokStri.c_str(), NULL};
    ESMCPY_OBID(invoOBID, &invoConta.moLevThOBID);
    //
    return lv4p_query_invok(query_resp, &moOSEVClie, parms);
}
// checked

int BASELevFP::Invoke(resp_data_t *query_resp, Contain &invoConta, const string &invokStri, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invokStri || "" == prediStri)
        return -1;
    //
    char invoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {invoOBID, (char *) invokStri.c_str(), (char *) prediStri.c_str(), NULL};
    ESMCPY_OBID(invoOBID, &invoConta.moLevThOBID);
    //
    return lv4p_query_invok(query_resp, &moOSEVClie, parms);
}
// checked

int BASELevFP::Invoke(resp_data_t *query_resp, Contain &invoConta, const string &invokStri, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevFP::Invoke\n");
    if ("" == invokStri) return -1;
    //
    char invoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {invoOBID, (char *) invokStri.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(invoOBID, &invoConta.moLevThOBID);
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    return lv4p_query_invok(query_resp, &moOSEVClie, parms);
}
// checked

// checked

int BASELevFP::Factory(resp_data_t *query_resp, const string &lv2pDefin, const string &srcConta) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == srcConta) return -1;
    //
    const char *parms[0x03] = {(char *) lv2pDefin.c_str(), (char *) srcConta.c_str(), NULL};
    return lv4p_query_facto(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(resp_data_t *query_resp, const string &lv2pDefin, const string &srcConta, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == srcConta || "" == prediStri)
        return -1;
    //
    const char *parms[0x04] = {(char *) lv2pDefin.c_str(), (char *) srcConta.c_str(), (char *) prediStri.c_str(), NULL};
    return lv4p_query_facto(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(resp_data_t *query_resp, const string &lv2pDefin, const string &srcConta, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == srcConta) return -1;
    //
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {(char *) lv2pDefin.c_str(), (char *) srcConta.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    return lv4p_query_facto(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(const string &destConta, const string &srcConta) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == destConta || "" == srcConta)
        return -1;
    //
    const char *parms[0x03] = {(char *) destConta.c_str(), (char *) srcConta.c_str(), NULL};
    //
    resp_data_t query_resp;
    return lv4p_query_facto(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(const string &destConta, const string &srcConta, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == destConta || "" == srcConta || "" == prediStri)
        return -1;
    //
    const char *parms[0x04] = {(char *) destConta.c_str(), (char *) srcConta.c_str(), (char *) prediStri.c_str(), NULL};
    resp_data_t query_resp;
    return lv4p_query_facto(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(const string &destConta, const string &srcConta, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == destConta || "" == srcConta)
        return -1;
    //
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {(char *) destConta.c_str(), (char *) srcConta.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_facto(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(Contain &destConta, const string &srcConta) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == srcConta) return -1;
    //
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {destOBID, srcConta.c_str(), NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(Contain &destConta, const string &srcConta, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == srcConta || "" == prediStri)
        return -1;
    //
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {destOBID, srcConta.c_str(), prediStri.c_str(), NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(Contain &destConta, const string &srcConta, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == srcConta) return -1;
    //
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {destOBID, srcConta.c_str(), cpmoOBID, NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcConta) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {lv2pDefin.c_str(), srcOBID, NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    return lv4p_query_facto(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcConta, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == prediStri) return -1;
    //
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {lv2pDefin.c_str(), srcOBID, (char *) prediStri.c_str(), NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    return lv4p_query_facto(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcConta, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {lv2pDefin.c_str(), srcOBID, cpmoOBID, NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    return lv4p_query_facto(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(const string &destConta, Contain &srcConta) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == destConta) return -1;
    //
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {destConta.c_str(), srcOBID, NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(const string &destConta, Contain &srcConta, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == destConta || "" == prediStri)
        return -1;
    //
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {destConta.c_str(), srcOBID, prediStri.c_str(), NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(const string &destConta, Contain &srcConta, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == destConta) return -1;
    //
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {destConta.c_str(), srcOBID, cpmoOBID, NULL};
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(Contain &destConta, Contain &srcConta) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    //
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x03] = {destOBID, srcOBID, NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(Contain &destConta, Contain &srcConta, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == prediStri) return -1;
    //
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {destOBID, srcOBID, prediStri.c_str(), NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(Contain &destConta, Contain &srcConta, const osv_oid_t &condiOBID) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char srcOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char cpmoOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    const char *parms[0x04] = {destOBID, srcOBID, cpmoOBID, NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    ESMCPY_OBID(srcOBID, &srcConta.moLevThOBID);
    ESMCPY_OBID(cpmoOBID, &condiOBID);
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcContaI, Contain &srcContaII) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x03] = {lv2pDefin.c_str(), srcOBID, NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    return lv4p_query_facto(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcContaI, Contain &srcContaII, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == prediStri) return -1;
    //
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x04] = {lv2pDefin.c_str(), srcOBID, (char *) prediStri.c_str(), NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    return lv4p_query_facto(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(resp_data_t *query_resp, const string &lv2pDefin, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    char cpmoOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x04] = {lv2pDefin.c_str(), srcOBID, cpmoOBID, NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    ESMCPY_BINARY_II(cpmoOBID, &condiOBID_I, &condiOBID_II, sizeof (osv_oid_t));
    return lv4p_query_facto(query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(const string &destConta, Contain &srcContaI, Contain &srcContaII) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == destConta) return -1;
    //
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x03] = {destConta.c_str(), srcOBID, NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(const string &destConta, Contain &srcContaI, Contain &srcContaII, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == destConta || "" == prediStri)
        return -1;
    //
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x04] = {destConta.c_str(), srcOBID, prediStri.c_str(), NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(const string &destConta, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == destConta) return -1;
    //
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    char cpmoOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x04] = {destConta.c_str(), srcOBID, cpmoOBID, NULL};
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    ESMCPY_BINARY_II(cpmoOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(Contain &destConta, Contain &srcContaI, Contain &srcContaII) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    //
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x03] = {destOBID, srcOBID, NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(Contain &destConta, Contain &srcContaI, Contain &srcContaII, const string &prediStri) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    if ("" == prediStri) return -1;
    //
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x04] = {destOBID, srcOBID, prediStri.c_str(), NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}

// checked

int BASELevFP::Factory(Contain &destConta, Contain &srcContaI, Contain &srcContaII, const osv_oid_t &condiOBID_I, const osv_oid_t &condiOBID_II) {
    CLIEPF("[FUNC]:BASELevFP::Factory\n");
    char destOBID[ESCA_OBIDCON_PART + OBJE_IDENTI_BLEN];
    char srcOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    char cpmoOBID[ESCA_ENTICON_PART + OBJE_IDENTI_BLEN * MAX_SCONT_COUNT];
    const char *parms[0x04] = {destOBID, srcOBID, cpmoOBID, NULL};
    ESMCPY_OBID(destOBID, &destConta.moLevThOBID);
    ESMCPY_BINARY_II(srcOBID, &srcContaI.moLevThOBID, &srcContaII.moLevThOBID, sizeof (osv_oid_t));
    ESMCPY_BINARY_II(cpmoOBID, &condiOBID_I, &condiOBID_II, sizeof (osv_oid_t));
    //
    resp_data_t query_resp;
    return lv4p_query_searq(&query_resp, &moOSEVClie, parms);
}


