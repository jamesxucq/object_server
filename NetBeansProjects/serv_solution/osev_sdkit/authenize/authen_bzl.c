/* authen_bzl.c
 * Created on: 2010-3-10
 * Author: Divad
 */

#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "filli_privi.h"
#include "privile_bzl.h"
#include "cache_utili.h"
#include "authe_valid.h"
#include "authen_obje.h"
#include "seion_struct.h"
#include "astri_utili.h"
#include "authen_bzl.h"

#include "debug_funct_au.h"
#include "liv_list.h"

//

int authbzl_create() {
    fprintf(stdout, "[FUNC]:authbzl create start!\n");
    //
#ifdef NOAUTH
    _authe_statu_ = AUTHEN_OFF;
#else
    _authe_statu_ = AUTHEN_ON;
#endif // NOAUTH
    //
    fprintf(stdout, "[FUNC]:authbzl create end!\n");
    return ERR_SUCCESS; //succ
}

int authbzl_destroy() {
    fprintf(stdout, "[FUNC]:authbzl destroy start!\n");
    //
    fprintf(stdout, "[FUNC]:authbzl destroy end!\n");
    return ERR_SUCCESS; //succ
}

//

priv_auth *osev_apval_bzl(char *user_name) {
    // OSEVPF("[FUNC]:osev_apval_bzl\n");
    // OSEVPF("user_name:|%s|\n", user_name);
    user_privi *uepriv;
    priv_auth *apval;
    char action_key[ACTION_KEY_LENGTH];
    //
    creat_action_key(action_key, user_name, OSEV_DEFAULT_VALUE);
    if ((apval = (priv_auth *) action_value(action_key, _priv_auth_hm_))) apval->_refer_inde_++;
    else {
        if (!(uepriv = (user_privi *) cache_value(user_name, _user_priv_lm_.osev_user_hm)))
            return NULL;
        if (!(apval = mallo_apval()))
            return NULL;
        //
        apval->use_privi = uepriv;
        if (filli_authe_valid(apval->auth_valid, apval->use_privi)) {
            DELETE_APVAL(apval);
            return NULL;
        }
        _LOG_DEBUG("Enable OSEV authen.");
        strcpy(apval->osev_base, OSEV_DEFAULT_VALUE);
        // ruturn obid text
        // gener_osev_poid(&apval->prau_obid, apval->obid_stri);
        gener_osev_obid(&apval->prau_obid);
        strcpy(apval->_action_key_, action_key);
        apval->_refer_inde_ = 0x01;
        action_insert(apval->_action_key_, apval, _priv_auth_hm_);
    }
    // OSEVPF("increase auth cache refer inde:%d\n", apval->_refer_inde_);
    return apval;
}

//

priv_auth *base_apval_bzl(char *user_name, osv_oid_t *base_obid, char *basen) {
    OSEVPF("[FUNC]:base_apval_bzl\n");
    user_privi *uepriv;
    priv_auth *apval;
    char action_key[ACTION_KEY_LENGTH];
    //
    creat_action_key(action_key, user_name, basen);
    if ((apval = (priv_auth *) action_value(action_key, _priv_auth_hm_))) apval->_refer_inde_++;
    else {
        if (!(uepriv = (user_privi *) cache_value(user_name, _user_priv_lm_.base_user_hm)))
            return NULL;
        if (!(apval = mallo_apval()))
            return NULL;
        //
        apval->use_privi = uepriv;
        if (filli_authe_valid(apval->auth_valid, apval->use_privi)) {
            DELETE_APVAL(apval);
            return NULL;
        }
        _LOG_DEBUG("Enable BASE authen.");
        strcpy(apval->osev_base, basen);
        // ruturn obid text
        // PLAIN_BINARY_CPYOID(&apval->prau_obid, apval->obid_stri, base_obid)
        OBID_BINARY_COPY(&apval->prau_obid, base_obid)
        strcpy(apval->_action_key_, action_key);
        apval->_refer_inde_ = 0x01;
        action_insert(apval->_action_key_, apval, _priv_auth_hm_);
    }
    // OSEVPF("increase auth cache refer inde:%d\n", apval->_refer_inde_);
    return apval;
}

priv_auth *nodb_apval_bzl(char *user_name, osv_oid_t *base_obid, char *basen) {
    priv_auth *apval;
    char action_key[ACTION_KEY_LENGTH];
    //
    creat_action_key(action_key, user_name, basen);
    if ((apval = (priv_auth *) action_value(action_key, _priv_auth_hm_))) apval->_refer_inde_++;
    else {
        _LOG_DEBUG("Disable BASE authen.");
        if (!(apval = mallo_apval()))
            return NULL;
        //
        strcpy(apval->osev_base, basen);
        // ruturn obid text
        // PLAIN_BINARY_CPYOID(&apval->prau_obid, apval->obid_stri, base_obid)
        OBID_BINARY_COPY(&apval->prau_obid, base_obid)
        strcpy(apval->_action_key_, action_key);
        apval->_refer_inde_ = 0x01;
        action_insert(apval->_action_key_, apval, _priv_auth_hm_);
    }
    // OSEVPF("increase auth cache refer inde:%d\n", apval->_refer_inde_);
    return apval;
}

//

priv_auth *nosv_apval_bzl(char *user_name) {
    priv_auth *apval;
    char action_key[ACTION_KEY_LENGTH];
    //
    creat_action_key(action_key, user_name, OSEV_DEFAULT_VALUE);
    if ((apval = (priv_auth *) action_value(action_key, _priv_auth_hm_))) apval->_refer_inde_++;
    else {
        _LOG_DEBUG("Disable OSEV authen.");
        if (!(apval = mallo_apval()))
            return NULL;
        //
        strcpy(apval->osev_base, OSEV_DEFAULT_VALUE);
        // ruturn obid text
        // gener_osev_poid(&apval->prau_obid, apval->obid_stri);
        gener_osev_obid(&apval->prau_obid);
        strcpy(apval->_action_key_, action_key);
        apval->_refer_inde_ = 0x01;
        action_insert(apval->_action_key_, apval, _priv_auth_hm_);
    }
    // OSEVPF("increase auth cache refer inde:%d\n", apval->_refer_inde_);
    return apval;
}

//

void authe_epoll_exceptio(char *action_key) {
    priv_auth *apval;
    if ((apval = (priv_auth *) action_value(action_key, _priv_auth_hm_))) {
        apval->_refer_inde_--;
        if (!apval->_refer_inde_) {
            OSEVPF("exception delete apval refere inde:%d\n", apval->_refer_inde_);
            action_remove(action_key, _priv_auth_hm_);
        }
    }
    // disable by james 20120410
    // OSEVPF("decrease auth cache refere inde:%d\n", apval->_refer_inde_);
}

int erase_auth_cache_end(char *action_key) {
    OSEVPF("[FUNC]:erase_auth_cache_end\n");
    priv_auth *apval;
    if ((apval = (priv_auth *) action_value(action_key, _priv_auth_hm_))) {
        apval->_refer_inde_--;
        if (!apval->_refer_inde_) {
            OSEVPF("done delete apval refere inde:%d\n", apval->_refer_inde_);
            action_remove(action_key, _priv_auth_hm_);
        }
    }
    // disable by james 20120410
    // OSEVPF("decrease auth cache refere inde:%d\n", apval->_refer_inde_);
    return ERR_SUCCESS;
}

//

int chk_reque_bzl(unsigned char *req_valid, unsigned char *plai_valid, char *req_salt) {
    // OSEVPF("[FUNC]:chk_reque_bzl\n");
    if (IS_ZERO(plai_valid)) return ERR_SUCCESS; // no authen
    //
    unsigned char hash_valid[VALID_LENGTH];
    salt_auth_chks(hash_valid, plai_valid, req_salt);
    //
#ifdef _DEBUG
    OSEVPF("-----------------\n");
    OSEVPF("plai_valid:|%s|\n", plai_valid);
    char temp[SALT_LENGTH + 0x01];
    strzcpy(temp, req_salt, SALT_LENGTH);
    OSEVPF("req_salt:|%s|\n", temp);
    OSEVPF("req_valid:");
    PRIN_md5sum(req_valid);
    OSEVPF("hash_valid:");
    PRIN_md5sum(hash_valid);
#endif
    //
    return memcmp(hash_valid, req_valid, VALID_LENGTH);
}

//

int auth_status_bzl() {
    return _authe_statu_;
}