
#ifndef CLI_OBJE_H
#define CLI_OBJE_H

#include <pthread.h>

#include "osev_clie_clang.h"
#include "cstri_utili.h"
#include "osvp_utili.h"
#include"cli_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    extern osev_clie _ocli_clie_;
    extern int _conne_type_;
    extern osvp_auth _ocli_auth_;

    //
    extern obje_valu _leve_defa_obje_;
    extern clie_stat_t _last_cli_stat_;
    extern int _blank_prompt_;

    // 0x00: connected -1: not connected
    int chk_clien_conne();

    // 0x00:ok -1:error
    int conne_cont_noau(osev_clie *oclie, const char *basen);
    // 0x00:ok -1:error
    int conne_cont_auth(osev_clie *oclie, const char *basen, const char *name, const char *paswd);

    // 
    extern actionmap *_conta_cache_hm_;
    extern pthread_mutex_t _conta_cache_mutex_;

    int creat_conta_cache();
    void destr_conta_cache();
    osv_oid_t *find_conta_obid(const char *contn, osev_clie *oclie);
    void erase_conta(const char *contn, unsigned int quer_valu);

    inline void reset_conta_cache() {
        // CLIEPF("------ clear conta cache.\n");
        pthread_mutex_lock(&_conta_cache_mutex_);
        action_clear(_conta_cache_hm_);
        pthread_mutex_unlock(&_conta_cache_mutex_);
    }

    //
    extern actionmap *_base_cache_hm_;
    extern pthread_mutex_t _base_cache_mutex_;

    int creat_base_cache();
    void destr_base_cache();
    osv_oid_t *find_base_obid(char *basen, osev_clie *oclie);
    void erase_base(const char *basen, const char *objide, unsigned int inst_valu);

    inline void reset_base_cache() {
        // CLIEPF("------ clear base cache.\n");
        pthread_mutex_lock(&_base_cache_mutex_);
        action_clear(_base_cache_hm_);
        pthread_mutex_unlock(&_base_cache_mutex_);
    }

    //
    extern actionmap *_colle_cache_hm_;
    extern pthread_mutex_t _colle_cache_mutex_;

    int creat_colle_cache();
    void destr_colle_cache();
    osv_oid_t *find_colle_obid(const char *colle, osev_clie *oclie);
    void erase_colle(const char *colle, unsigned int coll_valu);

    inline void reset_colle_cache() {
        pthread_mutex_lock(&_colle_cache_mutex_);
        action_clear(_colle_cache_hm_);
        pthread_mutex_unlock(&_colle_cache_mutex_);
    }


#ifdef __cplusplus
}
#endif

#endif /* CLI_OBJE_H */

