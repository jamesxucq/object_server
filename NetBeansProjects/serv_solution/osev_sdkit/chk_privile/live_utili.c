
#include "commo_header.h"
#include "kcomm_header.h"
#include "basev_bzl.h"
#include "rive_bzl.h"
#include "query_bzl.h"

#include "live_utili.h"
#include "loop_memo.h"

//

priv_cont _priv_data_[] = {
    {AUTH_ROLES_CONT, DEFA_ROLE_LVTP},
    {AUTH_OUSER_CONT, DEFA_USER_LVTP},
    {AUTH_BUSER_CONT, DEFA_USER_LVTP},
    {NULL, NULL}
};

// check privileges data exists

int chk_privi_data(cont_lsmp *conda_stm, lv2pm_hmap *lv2pm_stm, priv_cont *priv_data) {
    OSEVPF("[FUNC]:chk_privi_data\n");
    contain *contp;
    lv2pme *lv2me;
    priv_cont *prico = priv_data;
    for (; prico->cont_name && prico->lv2pn_type; ++prico) {
        contp = (contain *) cache_value(prico->cont_name, conda_stm->lev3n_hm);
        if (!contp) return -1;
        lv2me = (lv2pme *) cache_value(&contp->lv2p_type, lv2pm_stm->lv2pmo_hm);
        if (!lv2me) return -1;
        if (strcmp(lv2me->lv2pn, prico->lv2pn_type))
            return -1;
    }
    //
    return 0x00;
}

//

#define OSEV_LIVE_INITIA(BASVAL, CONTA_NAME) \
    contain *contp = (contain *) cache_value(CONTA_NAME, BASVAL->conda_stm.lev3n_hm); \
    if (!contp) return -1; \
    rive_ha *stora_ha = contp->stora_ha; \
    riv_curso_t *curso; \
    stor_seio *sto_seio = ACTIV_SESSION_BZL(BASVAL->rivcon, stora_ha); \
    if (!sto_seio) return -1; \
    if (stora_ha->open_curso_cont(&curso, sto_seio->seion, CONTA_NAME, "raw")) { \
        QUIET_SESSION_BZL(BASVAL->rivcon, stora_ha, sto_seio); \
        return -1; \
    }

#define OSEV_LIVE_FINAL(CURSO, SLIST, STORA_HA, RVCON) \
    stora_ha->close_curso(CURSO); \
    QUIET_SESSION_BZL(RVCON, STORA_HA, SLIST);

//

int live_recu_load(liv_list **llsth, base_valu *admbv, char *contn) {
    OSEVPF("[FUNC]:live_recu_load ----------------------- \n");
    OSEV_LIVE_INITIA(admbv, contn);
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, admbv->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) {
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    // OSEVPF("load contn:|%s| data_size:%d\n", contn, dylid->data_size);
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv2me)) {
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(curso)) {
        // OSEVPF("1 -------------------\n");
        stora_ha->get_key(curso, &key);
        stora_ha->get_value(curso, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv2me)) {
            free_valu(&obje_memo);
            OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
            return -1;
        }
        if (!appe_live_list(llsth, obje_memo.data, obje_memo.data_size)) {
            free_valu(&obje_memo);
            OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
            return -1;
        }
        // log_binary_file(obje_memo, dylid->data_size, "./binary_code.bin_f");
    }
    //
    free_valu(&obje_memo);
    OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
    return 0x00;
}

// for debug
#ifdef _DEBUG
#pragma pack(1)

struct user {
    osv_oid_i obje_obid;
    char user_name[32];
    char password[32];
    char salt[16];
    char role_obid[96];
};
#pragma pack() 

int user_recu_prin(base_valu *admbv, char *contn) {
    OSEVPF("[FUNC]:user_recu_prin +++++++++++++++ \n");
    OSEV_LIVE_INITIA(admbv, contn);
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, admbv->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) {
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    // OSEVPF("load contn:|%s| data_size:%d\n", contn, dylid->data_size);
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv2me)) {
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(curso)) {
        OSEVPF("1 -------------------\n");
        stora_ha->get_key(curso, &key);
        stora_ha->get_value(curso, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv2me)) {
            free_valu(&obje_memo);
            OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
            return -1;
        }
        struct user *usrp = obje_memo.data;
        char obid_stri[OBJE_IDENTI_ZLEN];
        printf("obje_obid:|%s|\n", oidstr(obid_stri, (osv_oid_t *) & usrp->obje_obid));
        printf("user_name:|%s|\n", usrp->user_name);
        // printf("password:|%s|\n", usrp->password);
        // log_binary_file(obje_memo, dylid->data_size, "./binary_code.bin_f");
    }
    //
    free_valu(&obje_memo);
    OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
    return 0x00;
}
#endif
//

int live_insert(base_valu *admbv, char *contn, void *inse_data) {
    // OSEVPF("[FUNC]:live_insert\n");
    OSEV_LIVE_INITIA(admbv, contn);
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, admbv->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) {
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    //
    loop_memo_t liv_dat;
    if (!loop_malloc(&liv_dat, lv2me)) {
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    memcpy(liv_dat.data, inse_data, lv2me->data_size);
    // log_binary_file(data, dylid->data_size, "./binary_code.bin_bound");
    PK_ITEM key, valu;
    if (solve_objec_loop(&key, &valu, &liv_dat, lv2me)) {
        free_loop(&liv_dat);
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    stora_ha->set_key(curso, &key);
    stora_ha->set_value(curso, &valu);
    if (0x00 != stora_ha->inser_curso(curso)) {
        _LOG_INFO("inser_curso error!");
        free_loop(&liv_dat);
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    //
    free_loop(&liv_dat);
    OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
    return 0x00;
}

//

int live_load(valu_memo_t *load_data, base_valu *admbv, char *contn, osv_oid_t *roue_obid) {
    OSEVPF("[FUNC]:live_load ----------------------- \n");
    OSEV_LIVE_INITIA(admbv, contn);
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, admbv->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) {
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    //
    PK_ITEM key, valu;
    stora_ha->set_sid_key(curso, &((osv_oid_i *) roue_obid)->stoid);
    if (0x00 != stora_ha->search_curso(curso)) {
        _LOG_INFO("search_curso error!");
        // OSEVPF("ret:%d\n", ret);
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    stora_ha->get_key(curso, &key);
    stora_ha->get_value(curso, &valu);
    FILL_UNIQUE_OBID((osv_oid_t *) load_data->data);
    if (bound_objec_data(load_data, (uint64 *) key.data, &valu, lv2me)) {
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    // log_binary_file(data, dylid->data_size, "./binary_code.bin_solve");
    OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
    return 0x00;
}

//

int loop_load(loop_memo_t *load_data, base_valu *admbv, char *contn, osv_oid_t *roue_obid) {
    OSEVPF("[FUNC]:loop_load ----------------------- \n");
    OSEV_LIVE_INITIA(admbv, contn);
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, admbv->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) {
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    //
    PK_ITEM key, valu;
    stora_ha->set_sid_key(curso, &((osv_oid_i *) roue_obid)->stoid);
    if (0x00 != stora_ha->search_curso(curso)) {
        _LOG_INFO("search_curso error!");
        // OSEVPF("ret:%d\n", ret);
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    stora_ha->get_key(curso, &key);
    stora_ha->get_value(curso, &valu);
    FILL_UNIQUE_OBID((osv_oid_t *) load_data->data);
    if (bound_objec_loop(load_data, (uint64 *) key.data, &valu, lv2me)) {
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    // log_binary_file(data, dylid->data_size, "./binary_code.bin_solve");
    OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
    return 0x00;
}

int loop_save(base_valu *admbv, char *contn, loop_memo_t *save_data, osv_oid_t *roue_obid) {
    // OSEVPF("[FUNC]:loop_save\n");
    OSEV_LIVE_INITIA(admbv, contn);
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, admbv->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) {
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
#ifdef _DEBUG
    OSEVPF("objeid_qconta_cla\n");
    char obid_stri[OBJE_IDENTI_ZLEN];
    OSEVPF("|%s|\n", oidstr(obid_stri, roue_obid));
#endif
    //
    PK_ITEM key, valu;
    if (solve_objec_loop(&key, &valu, save_data, lv2me)) {
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    stora_ha->set_sid_key(curso, &((osv_oid_i *) roue_obid)->stoid);
    stora_ha->set_value(curso, &valu);
    if (0x00 != stora_ha->update_curso(curso)) {
        _LOG_INFO("update_curso error!");
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    //
    OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
    return 0x00;
}

int live_remove(base_valu *admbv, char *contn, osv_oid_t *roue_obid) {
    // OSEVPF("[FUNC]:live_remove\n");
    OSEV_LIVE_INITIA(admbv, contn);
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    OSEVPF("objeid_qconta_cla:|%s|\n", oidstr(obid_stri, roue_obid));
#endif
    //
    stora_ha->set_sid_key(curso, &((osv_oid_i *) roue_obid)->stoid);
    if (0x00 != stora_ha->remove_curso(curso)) {
        _LOG_INFO("remove_curso error!");
        OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
        return -1;
    }
    //
    OSEV_LIVE_FINAL(curso, sto_seio, stora_ha, admbv->rivcon)
    return 0x00;
}
