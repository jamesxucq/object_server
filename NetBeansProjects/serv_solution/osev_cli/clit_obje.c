
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "commo_header.h"
#include "clit_macro.h"
#include "osev_clie_clang.h"
#include"clit_struct.h"
#include "cstri_utili.h"
#include"connect.h"
#include "parse_resxml.h"

#include "clit_obje.h"
#include "debug_funct_sh.h"


//
actionmap *_colle_cache_hm_;
pthread_mutex_t _colle_cache_mutex_ = PTHREAD_MUTEX_INITIALIZER;

actionmap *_conta_cache_hm_;
pthread_mutex_t _conta_cache_mutex_ = PTHREAD_MUTEX_INITIALIZER;

actionmap *_base_cache_hm_;
pthread_mutex_t _base_cache_mutex_ = PTHREAD_MUTEX_INITIALIZER;

//
osev_clie _ocli_clie_;
int _conne_type_ = NULL_CONNE;
osvp_auth _ocli_auth_;

//
obje_valu _leve_defa_obje_;
clit_stat_t _last_cli_stat_;
int _blank_prompt_;

// 0x00: connected -1: not connected

int chk_clien_conne() {
    resp_head kaliv_resp;
    if (kaliv_clie_continue(&kaliv_resp, &_ocli_clie_)) {
        OSEVPrintErro("Connect to osev exception!", kaliv_resp.status_code);
        return -1;
    }
    return 0x00;
}

//

static void dele_cache(void *data) {
    if (data) free(data);
}

// 0x00:ok -1:error

int conne_base_noau(osev_clie *oclie, const char *basen) {
    osvp_auth clus_auth;
    if (!strcmp(oclie->clie_name, basen))
        return 0x00;
    //
    memcpy(&clus_auth, &_ocli_auth_, sizeof (osvp_auth));
    strcpy(clus_auth.osev_base, basen);
    CLIT_PF("[FUNC]:------ noauth connect to %s.\n", basen);
    // CLIT_PF("connect to %s ...\n", conne_str);
    if (reconne_base(oclie, &clus_auth))
        return -1;
    INIT_OSEV_OBID(&oclie->clie_obid);
    return 0x00;
}

// 0x00:ok -1:error

int conne_base_auth(osev_clie *oclie, const char *basen, const char *name, const char *paswd) {
    osvp_auth clus_auth;
    if (!strcmp(oclie->clie_name, basen))
        return 0x00;
    //
    memcpy(&clus_auth.saddr, &_ocli_auth_.saddr, sizeof (serv_addr));
    strcpy(clus_auth.osev_base, basen);
    strcpy(clus_auth.authe.user_name, name);
    strcpy(clus_auth.authe.pass_word, paswd);
    CLIT_PF("------ auth connect to %s.\n", basen);
    // CLIT_PF("connect to %s ...\n", conne_str);
    if (reconne_base(oclie, &clus_auth))
        return -1;
    INIT_OSEV_OBID(&oclie->clie_obid);
    return 0x00;
}

//

osv_oid_t *find_conta_obid(const char *contn, osev_clie *oclie) {
    CLIT_PF("[FUNC]:find_conta_obid, start. contn:|%s|\n", contn);
    obje_valu *ovalu;
    pthread_mutex_lock(&_conta_cache_mutex_);
    ovalu = (obje_valu *) action_value((void *) contn, _conta_cache_hm_);
    pthread_mutex_unlock(&_conta_cache_mutex_);
    if (ovalu) return &ovalu->obje_obid;
    // 
    CLIT_PF("1 xxxxxxxxxxxxx\n");
    const char *parms[0x02] = {contn, NULL};
    resp_data_t quer_resp;
    if (lv4p_query_statu(&quer_resp, oclie, QSTAT_ECHO, parms)) {
        OSEVPrintErro("query echo error!", quer_resp.status_code);
        outpu_excep_code(&quer_resp);
        return NULL;
    }
    //
    CLIT_PF("2 xxxxxxxxxxxxx\n");
    ovalu = (obje_valu*) malloc(sizeof (obje_valu));
    if (!ovalu) return NULL;
    if (parse_query_ovalu(ovalu, &quer_resp)) {
        CLIT_PF("parse_query_ovalu error!");
        dele_cache(ovalu);
        return NULL;
    }
    CLIT_PF("3 xxxxxxxxxxxxx\n");
    pthread_mutex_lock(&_conta_cache_mutex_);
    action_insert(ovalu->obje_iden, ovalu, _conta_cache_hm_);
    pthread_mutex_unlock(&_conta_cache_mutex_);
    //
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    CLIT_PF("end find_conta_obid, echo %s obid:|%s|\n", contn, oidstr(obid_stri, &ovalu->obje_obid));
#endif
    return &ovalu->obje_obid;
}

void erase_conta(const char *contn, unsigned int quer_valu) {
    if (LVFP_DROP == quer_valu) {
        // quote_decode(contn);
        CLIT_PF("erase_conta, contn:|%s|\n", contn);
        pthread_mutex_lock(&_conta_cache_mutex_);
        action_remove((void *) contn, _conta_cache_hm_);
        pthread_mutex_unlock(&_conta_cache_mutex_);
    }
}

//

osv_oid_t *seek_base_obid(char *basen, osev_clie *oclie) {
    CLIT_PF("[FUNC]:seek_base_obid, start. basen:|%s|\n", basen);
    obje_valu *ovalu;
    pthread_mutex_lock(&_base_cache_mutex_);
    ovalu = (obje_valu *) action_value(basen, _base_cache_hm_);
    pthread_mutex_unlock(&_base_cache_mutex_);
    if (ovalu) return &ovalu->obje_obid;
    //
    const char *parms[0x02] = {basen, NULL};
    resp_data_t stat_resp;
    if (osev_leve_inte(&stat_resp, OSEV_STATUS, STAIU_ECHO, oclie, &oclie->clie_obid, parms)) {
        OSEVPrintErro("status:echo error!", stat_resp.status_code);
        outpu_excep_code(&stat_resp);
        return NULL;
    }
    //
    ovalu = (obje_valu*) malloc(sizeof (obje_valu));
    if (!ovalu) return NULL;
    if (parse_osev_ovalu(ovalu, &stat_resp)) {
        dele_cache(ovalu);
        return NULL;
    }
    pthread_mutex_lock(&_base_cache_mutex_);
    action_insert(ovalu->obje_iden, ovalu, _base_cache_hm_);
    pthread_mutex_unlock(&_base_cache_mutex_);
    //
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    CLIT_PF("end server seek_base_obid, echo %s obid:|%s|\n", basen, oidstr(obid_stri, &ovalu->obje_obid));
#endif
    return &ovalu->obje_obid;
}
//

void erase_base(const char *basen, const char *objide, unsigned int inst_valu) {
    char base_iden[OBJN_LENGTH];
    if ((COMDI_CLOSE == inst_valu) && !strcmp(OSEV_DEFAULT_VALUE, objide)) {
        strcpy(base_iden, basen);
        // quote_decode(base_iden);
        CLIT_PF("erase_conta, base %s objide:|%s|\n", basen, base_iden);
        pthread_mutex_lock(&_base_cache_mutex_);
        action_remove(base_iden, _base_cache_hm_);
        pthread_mutex_unlock(&_base_cache_mutex_);
    }
}

// #define LIST_LVTP_OBJID     0x0001
#define INVO_LIST_OBJID "OBJID"

osv_oid_t *find_colle_obid(const char *colle, osev_clie *oclie) {
    CLIT_PF("[FUNC]:find_colle_obid, start. colle:|%s|\n", colle);
    obje_valu * ovalu;
    pthread_mutex_lock(&_colle_cache_mutex_);
    ovalu = (obje_valu *) action_value((char *) colle, _colle_cache_hm_);
    pthread_mutex_unlock(&_colle_cache_mutex_);
    if (ovalu) return &ovalu->obje_obid;
    //
    const char *parms[0x03] = {colle, INVO_LIST_OBJID, NULL};
    resp_data_t invok_resp;
    if (lv2p_colle_statu(&invok_resp, oclie, CSTAT_LIST, parms)) {
        OSEVPrintErro("collo list error!", invok_resp.status_code);
        outpu_excep_code(&invok_resp);
        return NULL;
    }
    //
    ovalu = (obje_valu*) malloc(sizeof (obje_valu));
    if (!ovalu) return NULL;
    if (parse_colle_ovalu(ovalu, &invok_resp)) {
        dele_cache(ovalu);
        return NULL;
    }
    pthread_mutex_lock(&_colle_cache_mutex_);
    action_insert(ovalu->obje_iden, ovalu, _colle_cache_hm_);
    pthread_mutex_unlock(&_colle_cache_mutex_);
    //
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    CLIT_PF("end find_colle_obid, echo %s obid:|%s|\n", colle, oidstr(obid_stri, &ovalu->obje_obid));
#endif
    return &ovalu->obje_obid;
}

void erase_colle(const char *colle, unsigned int coll_valu) {
    if (LVTP_DROP == coll_valu) {
        // quote_decode(colle);
        CLIT_PF("erase_cinvo, invok:|%s|\n", colle);
        pthread_mutex_lock(&_colle_cache_mutex_);
        action_remove((char *) colle, _colle_cache_hm_);
        pthread_mutex_unlock(&_colle_cache_mutex_);
    }
}

//

int creat_conta_cache() {
    pthread_mutex_lock(&_conta_cache_mutex_);
    _conta_cache_hm_ = creat_actio(dele_cache, CONTA_BACKET_SIZE);
    pthread_mutex_unlock(&_conta_cache_mutex_);
    if (!_conta_cache_hm_) return -1;
    return 0x00;
}

void destr_conta_cache() {
    pthread_mutex_lock(&_conta_cache_mutex_);
    if (_conta_cache_hm_) {
        action_destroy(_conta_cache_hm_);
        _conta_cache_hm_ = NULL;
    }
    pthread_mutex_unlock(&_conta_cache_mutex_);
}

int creat_base_cache() {
    pthread_mutex_lock(&_base_cache_mutex_);
    _base_cache_hm_ = creat_actio(dele_cache, BASE_BACKET_SIZE);
    pthread_mutex_unlock(&_base_cache_mutex_);
    if (!_base_cache_hm_) return -1;
    return 0x00;
}

void destr_base_cache() {
    pthread_mutex_lock(&_base_cache_mutex_);
    if (_base_cache_hm_) {
        action_destroy(_base_cache_hm_);
        _base_cache_hm_ = NULL;
    }
    pthread_mutex_unlock(&_base_cache_mutex_);
}

int creat_colle_cache() {
    pthread_mutex_lock(&_colle_cache_mutex_);
    _colle_cache_hm_ = creat_actio(dele_cache, COLLE_BACKET_SIZE);
    pthread_mutex_unlock(&_colle_cache_mutex_);
    if (!_colle_cache_hm_) return -1;
    return 0x00;
}

void destr_colle_cache() {
    pthread_mutex_lock(&_colle_cache_mutex_);
    if (_colle_cache_hm_) {
        action_destroy(_colle_cache_hm_);
        _colle_cache_hm_ = NULL;
    }
    pthread_mutex_unlock(&_colle_cache_mutex_);
}
