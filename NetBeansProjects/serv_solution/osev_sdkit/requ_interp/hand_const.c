#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "const_bzl.h"

#include "hand_const.h"

//
#define EPAM_POST_TYPE    0x00
// [txxt_con]lev3> :post(INSTRU); // instru
// [txxt_con]lev3> :post(lv2pn, ATTRIB, VALUE); // set lv2p value;

int const_post_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:const_post_hand\n");
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
#define EPAM_ECHO_TYPE   0x00
// #define EPAM_ECHO_NAME    0x01
// #define EPAM_ECHO_OBID    0x01

// const
// [txxt_con]lev3> :echo() | kits:format(BINARY_OBID);  // default: objid
// [txxt_con]lev3> :echo:objid();

int const_statu_echo_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:const_statu_echo_hand\n");
    // pamvu = 0
    if (pamvu->pamcon[0x00]) {
        PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    contain *contp = (contain *) cache_value(cont_obid, ((base_valu *) baval)->conda_stm.lev3o_hm);
    if (contp) {
#ifdef _DEBUG
        char obid_stri[OBJE_IDENTI_ZLEN];
        OSEVPF("Contain:|%s|\n", oidstr(obid_stri, cont_obid));
#endif
        enti_statu_echo_bzl(resctl, contp);
    } else {
#ifdef _DEBUG
        char obid_stri[OBJE_IDENTI_ZLEN];
        OSEVPF("Not found:|%s|\n", oidstr(obid_stri, cont_obid));
#endif
        PDAT_EXCEPTIM_TAIL(resctl, NOT_FOUND_CONTA)
        return -1;
    }
    //
    return 0x00;
}

// [txxt_con]lev3> :echo:attrib();
// [txxt_con]lev3> :echo:attrib() | kits:format(XML);

int const_statu_attri_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:const_statu_attri_hand\n");
    // pamvu = 0
    if (pamvu->pamcon[0x00]) {
        PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    contain *contp = (contain *) cache_value(cont_obid, ((base_valu *) baval)->conda_stm.lev3o_hm);
    if (contp) {
#ifdef _DEBUG
        char obid_stri[OBJE_IDENTI_ZLEN];
        OSEVPF("Contain:|%s|\n", oidstr(obid_stri, cont_obid));
#endif
        enti_statu_attri_bzl(resctl, contp, baval);
    } else {
#ifdef _DEBUG
        char obid_stri[OBJE_IDENTI_ZLEN];
        OSEVPF("Not found:|%s|\n", oidstr(obid_stri, cont_obid));
#endif
        PDAT_EXCEPTIM_TAIL(resctl, NOT_FOUND_CONTA)
        return -1;
    }
    //
    return 0x00;
}

// [txxt_con]lev3> :echo:statis();

int const_statu_stati_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:const_statu_stati_hand\n");
    // pamvu = 0
    if (pamvu->pamcon[0x00]) {
        PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    contain *contp = (contain *) cache_value(cont_obid, ((base_valu *) baval)->conda_stm.lev3o_hm);
    if (contp) {
#ifdef _DEBUG
        char obid_stri[OBJE_IDENTI_ZLEN];
        OSEVPF("Contain:|%s|\n", oidstr(obid_stri, cont_obid));
#endif
        enti_statu_stati_bzl(resctl, contp, baval);
    } else {
#ifdef _DEBUG
        char obid_stri[OBJE_IDENTI_ZLEN];
        OSEVPF("Not found:|%s|\n", oidstr(obid_stri, cont_obid));
#endif
        PDAT_EXCEPTIM_TAIL(resctl, NOT_FOUND_CONTA)
        return -1;
    }
    //
    return 0x00;
}

//
// [txxt_con]lev3> txxt_con:create(66,100,222);
// [txxt_con]lev3> role:role(0B, "admin", "");
// [txxt_con]lev3> taat:taat(33,44,5555);

int const_creat_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:const_creat_hand\n");
    contain *contp = (contain *) cache_value(cont_obid, ((base_valu *) baval)->conda_stm.lev3o_hm);
    if (!contp) {
#ifdef _DEBUG
        char obid_stri[OBJE_IDENTI_ZLEN];
        OSEVPF("Not find contain:|%s|\n", oidstr(obid_stri, cont_obid));
#endif
        PDAT_EXCEPTIM_TAIL(resctl, NOT_FOUND_CONTA)
        return -1;
    }
    // OSEVPF("enti_creat_bzl\n");
    int creat_valu = enti_creat_bzl(resctl, contp, baval, pamvu->pamcon);
    if (creat_valu) {
        OSEVPF("Create object execep!\n");
        PDAT_EXCEPTIM_TAIL(resctl, CREAT_ENTIT_EXPT)
        return -1;
    }
    //
    REFRESH_CONTAIN_VERSION(contp)
    return 0x00;
}

// [txxt_con]lev3> obje:drop();
// [txxt_con]lev3> obje:drop(obje_obid);
// [txxt_con]lev3> obje:drop("xx()>0x00");

int const_drop_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:const_drop_hand\n");
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
#endif
    // pamvu = 0 = 1
    if (pamvu->pamtyp[0x00] && pamvu->pamtyp[0x01]) {
        PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    contain *contp = (contain *) cache_value(cont_obid, ((base_valu *) baval)->conda_stm.lev3o_hm);
    if (!contp) {
#ifdef _DEBUG
        OSEVPF("Not found:|%s|\n", oidstr(obid_stri, cont_obid));
#endif
        PDAT_EXCEPTIM_TAIL(resctl, NOT_FOUND_CONTA)
        return -1;
    }
    //
#ifdef _DEBUG
    OSEVPF("contain:|%s|\n", oidstr(obid_stri, cont_obid));
#endif
    int drop_valu = enti_drop_bzl(contp, baval, pamvu);
    if (drop_valu) {
        OSEVPF("Drop object execep!\n");
        PDAT_EXCEPTIM_TAIL(resctl, DROP_ENTIT_EXPT)
        return -1;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    REFRESH_CONTAIN_VERSION(contp)
    return 0x00;
}

// [txxt_con]lev3> :updat(object);
// [txxt_con]lev3> :update(func:stroid("bb7ddcfb10c0ff6401000000"), 7.6, "cccddd"S, 100.44d, 222);

int const_updat_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:const_updat_hand\n");
    // pamvu = 1
    if (!pamvu->pamcon[0x00] || pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    contain *contp = (contain *) cache_value(cont_obid, ((base_valu *) baval)->conda_stm.lev3o_hm);
    if (!contp) {
        OSEVPF("Not find contain !\n");
        PDAT_EXCEPTIM_TAIL(resctl, NOT_FOUND_CONTA)
        return -1;
    }
    //
    int updat_valu = enti_updat_bzl(contp, baval, pamvu);
    if (updat_valu) {
        OSEVPF("Update object execep!\n");
        PDAT_EXCEPTIM_TAIL(resctl, UPDAT_ENTIT_EXPT)
        return -1;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    REFRESH_CONTAIN_VERSION(contp)
    return 0x00;
}

// [txxt_con]lev3> :insert(object);
// [txxt_con]lev3> :insert(func:stroid("bb7ddcfb10c0ff6401000000"), 7.6, "cccddd"S, 100.44d, 222);

int const_inser_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:const_inser_hand\n");
    // pamvu = 1
    if (!pamvu->pamcon[0x00] || pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    contain *contp = (contain *) cache_value(cont_obid, ((base_valu *) baval)->conda_stm.lev3o_hm);
    if (!contp) {
#ifdef _DEBUG
        char obid_stri[OBJE_IDENTI_ZLEN];
        OSEVPF("Not find contain:|%s|\n", oidstr(obid_stri, cont_obid));
#endif
        PDAT_EXCEPTIM_TAIL(resctl, NOT_FOUND_CONTA)
        return -1;
    }
    // OSEVPF("enti_inser_bzl\n");
    int inser_valu = enti_inser_bzl(resctl, contp, baval, pamvu);
    if (inser_valu) {
        OSEVPF("Insert object execep!\n");
        PDAT_EXCEPTIM_TAIL(resctl, INSER_ENTIT_EXPT)
        return -1;
    }
    //
    REFRESH_CONTAIN_VERSION(contp)
    return 0x00;
}

// [txxt_con]lev3> obje:search();
// [txxt_con]lev3> obje:search("xx()>0x00");
// [txxt_con]lev3> :search("xx=3") | kits:pretty("oiii");

int const_searc_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu) {
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    OSEVPF("[FUNC]:const_searc_hand, find contain:|%s|\n", oidstr(obid_stri, cont_obid));
#endif
    // pamvu = 0 = 1
    if (pamvu->pamtyp[0x00] && pamvu->pamtyp[0x01]) {
        FDAT_EXCEPTI_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    contain *contp = (contain *) cache_value(cont_obid, ((base_valu *) baval)->conda_stm.lev3o_hm);
    if (!contp) {
        OSEVPF("Not find contain!\n");
        FDAT_EXCEPTI_TAIL(resctl, NOT_FOUND_CONTA)
        return -1;
    }
    //
    int searo_valu = enti_searo_bzl(resctl, contp, (base_valu *) baval, pamvu);
    if (searo_valu) {
        OSEVPF("Search object execep!\n");
        FDAT_EXCEPTI_TAIL(resctl, SEARC_ENTIT_EXPT)
        return -1;
    }
    //
    return 0x00;
}

// [txxt_con]lev3> obje:invoke("metho(122)");
// [txxt_con]lev3> obje:invoke("metho(122)", obje:is_class("test"));
// [txxt_con]lev3> obje:invoke("metho(122)", "obje:numb() > 0x00");
// [txxt_con]lev3> :invoke("tpp(777, 555)", func:stroid("bb7ddcfbb8a2026503000000"));

int const_invok_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:const_invok_hand\n");
    // pamvu = 1 = 2
    if (!pamvu->pamtyp[0x00] || (pamvu->pamtyp[0x01] && pamvu->pamtyp[0x02])) {
        FDAT_EXCEPTI_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    contain *contp = (contain *) cache_value(cont_obid, ((base_valu *) baval)->conda_stm.lev3o_hm);
    if (!contp) {
#ifdef _DEBUG
        char obid_stri[OBJE_IDENTI_ZLEN];
        OSEVPF("Not find contain:|%s|\n", oidstr(obid_stri, cont_obid));
#endif
        FDAT_EXCEPTI_TAIL(resctl, NOT_FOUND_CONTA)
        return -1;
    }
    //
    int invok_valu = enti_invok_bzl(resctl, contp, baval, pamvu);
    if (invok_valu) {
        OSEVPF("Invoke object execep!\n");
        FDAT_EXCEPTI_TAIL(resctl, INVOK_ENTIT_EXPT)
        return -1;
    }
    //
    REFRESH_CONTAIN_VERSION(contp)
    return 0x00;
}

