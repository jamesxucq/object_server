#include "commo_header.h"
#include "kcomm_header.h"

// #include "rstatu_bzl.h"
#include "query_bzl.h"
#include "basev_bzl.h"

#include "chk_reque_param.h"
#include "hand_query.h"

//
#define QPAM_POST_TYPE    0x00
// odb-lv4p> :post(INSTRU); // instru
// odb-lv4p> :post(lv2pn, ATTRIB, VALUE); // set lv2p value;

int query_post_hand(respo_ctrl *resctl, void *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:query_post_hand\n");
    // pamvu = 1 // instru
    if (!pamvu->pamtyp[0x00] || pamvu->pamtyp[0x01]) {
        PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    // pamvu = 3 // set lv2p value;
    if (!pamvu->pamtyp[0x00] || !pamvu->pamtyp[0x01] || !pamvu->pamtyp[0x02] || pamvu->pamtyp[0x03]) {
        PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
            //
    return 0x00;
}

//

#define QPAM_ECHO_TYPE   0x00
#define QPAM_ECHO_NAME   0x00
#define QPAM_ECHO_OBID   0x00
// it is very important, attention!!!
#define QPAM_ECHO_ROPRIV    0x02

// query
// odb-lv4p> :echo("taat_con") | kits:format(BINARY_OBID); // default: objid
// odb-lv4p> :echo:objid();
// odb-lv4p> :echo:objid(conta_name);

int query_statu_echo_hand(respo_ctrl *resctl, void *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:query_statu_echo_hand\n");
    OSEVPF("pamvu->pamcon[0x00]:|%s|\n", pamvu->pamcon[0x00]);
    OSEVPF("pamvu->pamcon[0x01]:|%s|\n", pamvu->pamcon[0x01]);
    OSEVPF("pamvu->pamcon[0x02]:|%p|\n", pamvu->pamcon[0x02]);
    // pamvu = 0 = 1
    if (pamvu->pamtyp[0x00] && pamvu->pamtyp[0x01]) {
        PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("z PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    switch (pamvu->pamtyp[QPAM_ECHO_TYPE]) {
        case DATY_INVAL: // all
#ifndef NOAUTH
            // QPAM_ECHO_ROPRIV must have valu 
            CHECK_SINGLE_PARAM(resctl, INVA_PARAM_EXPT, pamvu->pamcon[QPAM_ECHO_ROPRIV])
#endif // NOAUTH
                    if (quer_statu_whole_bzl(resctl, (base_valu *) baval, (user_privi *) pamvu->pamcon[QPAM_ECHO_ROPRIV])) {
                PDAT_EXCEPTIM_TAIL(resctl, ECHO_QUERY_EXPT)
                return -1;
            }
            break;
        case DATY_OBID: // objid
            if (quer_statu_name_bzl(resctl, (base_valu *) baval, (osv_oid_t *) pamvu->pamcon[QPAM_ECHO_OBID])) {
                OSEVPF("not found:|%s|\n", pamvu->pamcon[0x00]);
                PDAT_EXCEPTIM_TAIL(resctl, ECHO_QUERY_EXPT)
                return -1;
            }
            break;
        case DATY_STRI: // name
            if (quer_statu_objid_bzl(resctl, (base_valu *) baval, pamvu->pamcon[QPAM_ECHO_NAME])) {
                OSEVPF("not found:|%s|\n", pamvu->pamcon[QPAM_ECHO_NAME]);
                PDAT_EXCEPTIM_TAIL(resctl, ECHO_QUERY_EXPT)
                return -1;
            }
            break;
        default:
            _LOG_WARN("default: QPAM_ECHO_TYPE");
            PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
            break;
    }
    //
#ifdef _DEBUG
    if (pamvu->pamcon[0x00])
        OSEVPF("contain:|%s|\n", pamvu->pamcon[0x00]);
#endif
    //
    return 0x00;
}

// odb-lv4p> :echo:attrib();
// odb-lv4p> :echo:attrib("txxt_con") | kits:format(XML);
// odb-lv4p> :echo:attrib(conta_obid) | kits:format(XML);
// odb-lv4p> :echo:attrib("txxt_con") | kits:format(XML);

#define QPAM_ATTI_TYPE   0x00
#define QPAM_ATTI_NAME   0x00
#define QPAM_ATTI_OBID   0x00

int query_statu_attri_hand(respo_ctrl *resctl, void *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:query_statu_attri_hand\n");
    OSEVPF("pamvu->pamcon[0x01]:|%s|\n", pamvu->pamcon[0x01]);
    OSEVPF("pamvu->pamcon[0x02]:|%p|\n", pamvu->pamcon[0x02]);
    // pamvu = 1
    if (!pamvu->pamtyp[0x00] || pamvu->pamtyp[0x01]) {
        PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    if (quer_statu_attri_bzl(resctl, (base_valu *) baval, pamvu)) {
        PDAT_EXCEPTIM_TAIL(resctl, ECHO_QUERY_EXPT)
        return -1;
    }
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    OSEVPF("Contain:|%s|\n", oidstr(obid_stri, (osv_oid_t *) pamvu->pamcon[QPAM_ECHO_OBID]));
#endif
    //
    return 0x00;
}

// odb-lv4p> :echo:statis("earth");
// odb-lv4p> :echo:statis(ODB);
// odb-lv4p> :echo:statis(CONTAIN);
// odb-lv4p> :echo:statis(); // CONTAIN | ODB

#define QPAM_STAI_TYPE   0x00
#define QPAM_USTAI_TYPE  0x00
#define QPAM_STAI_OBID  0x00
#define QPAM_STAI_NAME  0x00

int query_statu_stati_hand(respo_ctrl *resctl, void *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:query_statu_stati_hand\n");
    // OSEVPF("pamvu->pamcon[0x00]:|%d|\n", *((uint32 *) pamvu->pamcon[0x00]));
    OSEVPF("pamvu->pamcon[0x00]:|%s|\n", pamvu->pamcon[0x00]);
    OSEVPF("pamvu->pamcon[0x01]:|%s|\n", pamvu->pamcon[0x01]);
    // pamvu = 1
    if (!pamvu->pamtyp[0x00] || pamvu->pamtyp[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    switch (pamvu->pamtyp[QPAM_STAI_TYPE]) {
        case DATY_INVAL:
            _LOG_WARN("case: DATY_INVAL");
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
            break;
        case DATY_UINT:
            if (quer_statu_ustai_bzl(resctl, (base_valu *) baval, *((uint32 *) pamvu->pamcon[QPAM_USTAI_TYPE]))) {
                PDAT_EXCEPTIM_TAIL(resctl, ECHO_QUERY_EXPT)
                return -1;
            }
            break;
        case DATY_OBID:
            if (quer_statu_ostai_bzl(resctl, (base_valu *) baval, (osv_oid_t *) pamvu->pamcon[QPAM_STAI_OBID])) {
                PDAT_EXCEPTIM_TAIL(resctl, ECHO_QUERY_EXPT)
                return -1;
            }
            break;
        case DATY_STRI:
            if (quer_statu_nstai_bzl(resctl, (base_valu *) baval, pamvu->pamcon[QPAM_STAI_NAME])) {
                PDAT_EXCEPTIM_TAIL(resctl, ECHO_QUERY_EXPT)
                return -1;
            }
            break;
        default:
            _LOG_WARN("default: QPAM_STAI_TYPE");
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
            break;
    }
    //
    return 0x00;
}

// odb-lv4p> :create("mycon", "rive", "test");
// odb-lv4p> :create("mycon", "rive", "test", "scon1, scon2", "xxx=0x00");
// odb-lv4p> :create("mycon", "rive", "test", "scon1", "xxx=0x00");
// odb-lv4p> witi:witi("tppt_con", "taat");
// odb-lv4p> witi:witi("tppt_con", "taat", "scon1, scon2", "xxx=0x00");

// odb-lv4p> witi:witi("base_user_con", "user"); // admin
// odb-lv4p> witi:witi("osev_user_con", "user"); // admin
// odb-lv4p> witi:witi("roles_con", "role"); // admin

#define QPAM_CREA_CONTN     0x00
#define QPAM_CREA_CONTYP    0x03
#define QPAM_CREA_STATIC    0x04
#define QPAM_CREA_CONDIT    0x04
#define QPAM_CREA_DYNAMI    0x05

int query_creat_hand(respo_ctrl *resctl, void *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:query_creat_hand\n");
#ifdef _DEBUG
    OSEVPF("pamvu->pamcon[0x00]:|%s|\n", pamvu->pamcon[0x00]);
    OSEVPF("*((uint32 *) pamvu->pamcon[0x01]):|%u|\n", *((uint32 *) pamvu->pamcon[0x01]));
    OSEVPF("pamvu->pamcon[0x02]:|%s|\n", pamvu->pamcon[0x02]);
    if (pamvu->pamcon[0x03]) OSEVPF("*((uint32 *) pamvu->pamcon[0x03]):|%u|\n", *((uint32 *) pamvu->pamcon[0x03]));
#endif
    // pamvu >= 3
    if (!pamvu->pamtyp[0x00] || !pamvu->pamtyp[0x01] || !pamvu->pamtyp[0x02]) {
        PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    if (CONTA_LENGTH <= pamvu->req_len[QPAM_CREA_CONTN]) {
        PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_LENG)
        return -1;
    }
    contain *contp = (contain *) cache_value(pamvu->pamcon[QPAM_CREA_CONTN], ((base_valu *) baval)->conda_stm.lev3n_hm);
    if (contp) {
        PDAT_EXCEPTIM_TAIL(resctl, CONTA_EXIST_EXPT)
        return -1;
    }
    switch (pamvu->pamtyp[QPAM_CREA_CONTYP]) {
        case DATY_INVAL: // ENTIT_CONTA_NORMAL
            _LOG_WARN("case: DATY_INVAL");
            break;
        case DATY_UINT: // REFER_CONTA_STATIC
            if (pamvu->pamtyp[QPAM_CREA_STATIC]) {
                PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
                return -1;
            }
            break;
        case DATY_STRI: // REFER_CONTA_DYNAMI
            if ((DATY_STRI != pamvu->pamtyp[QPAM_CREA_CONDIT]) || pamvu->pamtyp[QPAM_CREA_DYNAMI]) {
                PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
                return -1;
            }
            if ((CONDIT_LENGTH <= pamvu->req_len[QPAM_CREA_CONDIT])) {
                PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_LENG)
                return -1;
            }
            break;
        default:
            _LOG_WARN("default: QPAM_CREA_CONTYP");
            PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
            break;
    }
    //
    if (quer_creat_bzl(resctl, (base_valu *) baval, pamvu)) {
        OSEVPF("Create query execep!\n");
        PDAT_EXCEPTIM_TAIL(resctl, CREAT_QUERY_EXPT)
        return -1;
    }
    // PDAT_PRODUCEN_TAIL(resctl)
    return 0x00;
}

// odb-lv4p> :drop("tsst_con");

int query_drop_hand(respo_ctrl *resctl, void *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:query_drop_hand\n");
    // pamvu = 1
    if (!pamvu->pamtyp[0x00] || pamvu->pamtyp[0x01]) {
        PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    if (quer_drop_bzl((base_valu *) baval, pamvu)) {
        OSEVPF("Drop query execep!\n");
        PDAT_EXCEPTIM_TAIL(resctl, DROP_QUERY_EXPT)
        return -1;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return 0x00;
}

int query_updat_hand(respo_ctrl *resctl, void *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:query_updat_hand\n");
    // pamvu = 2
    if (!pamvu->pamtyp[0x00] || !pamvu->pamtyp[0x01] || pamvu->pamtyp[0x02]) {
        PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    if (quer_updat_bzl((base_valu *) baval, pamvu)) {
        OSEVPF("Update query execep!\n");
        PDAT_EXCEPTIM_TAIL(resctl, UPDAT_QUERY_EXPT)
        return -1;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return 0x00;
}

int query_inser_hand(respo_ctrl *resctl, void *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:query_inser_hand\n");
    // pamvu = 2
    if (!pamvu->pamtyp[0x00] || !pamvu->pamtyp[0x01] || pamvu->pamtyp[0x02]) {
        FDAT_EXCEPTI_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    if (quer_inser_bzl(resctl, (base_valu *) baval, pamvu)) {
        OSEVPF("Insert query execep!\n");
        FDAT_EXCEPTI_TAIL(resctl, INSER_QUERY_EXPT)
        return -1;
    }
    //
    return 0x00;
}

// 创建对象引用,写/排它锁
// odb-lv4p> :search("lv2pn", "conobje", "obje:numb() > 0x00");
// odb-lv4p> :search("cobje", conobje", "obje:numb() > 0x00");
// odb-lv4p> :search("cobje", "conobje1, conobje2", "conobje1:obje:numb() > 0x00 AND conobje2:obje:numb() > 0x00");
// odb-lv4p> :search("cobje", "conobje1, conobje2", "conobje1::numb() > 0x00 AND conobje2::numb() > 0x00");
// odb-lv4p> :search("cobje", "conobje");
// odb-lv4p> :search("tsst", "tsst_con") | kits:pretty("oiii");
// odb-lv4p> :search("tsst", "tsst_con", "xx=3") | kits:pretty("oiii");
// odb-lv4p> :search("<[xx int32, ax int32, cx int32]>", "tsst_con", "xx=3") | kits:pretty("oiii");
// odb-lv4p> :search("<[xx int32, ax int32]>", "txxt_con") | kits:pretty("oii");

int query_searc_hand(respo_ctrl *resctl, void *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:query_searc_hand\n");
    // pamvu >= 2
    if (!pamvu->pamtyp[0x00] || !pamvu->pamtyp[0x01]) {
        FDAT_EXCEPTI_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    if (quer_searq_bzl(resctl, (base_valu *) baval, pamvu)) {
        OSEVPF("Search query execep!\n");
        FDAT_EXCEPTI_TAIL(resctl, SEARC_QUERY_EXPT)
        return -1;
    }
    //
    return 0x00;
}

// odb-lv4p> :invoke("lv2n:meth(conta1:obje, conta2:obje, 55)", "conta1,conta2");
// odb-lv4p> :invoke("lv2n:meth(conta1:obje, 55)", "conta1");
// odb-lv4p> :invoke("lv2n:meth(conta1:obje, 55)", "conta1", "conta1:obje:tst(xxx) > 0x00");
// odb-lv4p> :invoke("lv2n:meth(conta1:obje, 55)", "conta1", "conta1::tst(xxx) > 0x00");
// odb-lv4p> :invoke("tpp(777, 555)", "tsst_con", func:stroid("bb7ddcfbb8a2026503000000"));
// odb-lv4p> :invoke("tsst_con:tpp(777, 555)", "tsst_con", func:stroid("bb7ddcfbb8a2026503000000"));

int query_invok_hand(respo_ctrl *resctl, void *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:query_invok_hand\n");
    // pamvu >= 2
    if (!pamvu->pamtyp[0x00] || !pamvu->pamtyp[0x01]) {
        FDAT_EXCEPTI_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    if (quer_invok_bzl(resctl, (base_valu *) baval, pamvu)) {
        OSEVPF("Invok query execep!\n");
        FDAT_EXCEPTI_TAIL(resctl, INVOK_QUERY_EXPT)
        return -1;
    }
    //
    return 0x00;
}

// 创建对象实体,读/共享锁
// odb-lv4p> :factory("lv2pn", "conobje", "obje:numb() > 0x00");
// odb-lv4p> :factory("lv2pn", conobje", "obje:numb() > 0x00");
// odb-lv4p> :factory("lv2pn", "conobje1, conobje2", "conobje1:obje:numb() > 0x00 AND conobje2:obje:numb() > 0x00");
// odb-lv4p> :factory("lv2pn", "conobje1, conobje2", "conobje1::numb() > 0x00 AND conobje2::numb() > 0x00");
// odb-lv4p> :factory("lv2pn", "conobje");
// odb-lv4p> :factory("<[xx int32, ax int32, cx int32]>", "conobje");

int query_facto_hand(respo_ctrl *resctl, void *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:query_facto_hand\n");
    // pamvu >= 2
    if (!pamvu->pamtyp[0x00] || !pamvu->pamtyp[0x01]) {
        FDAT_EXCEPTI_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    if (quer_facto_bzl(resctl, (base_valu *) baval, pamvu)) {
        OSEVPF("Facto query execep!\n");
        FDAT_EXCEPTI_TAIL(resctl, FACTO_QUERY_EXPT)
        return -1;
    }
    //
    return 0x00;
}

