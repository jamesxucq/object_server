#include "commo_header.h"
#include "kcomm_header.h"

#include "stora_engine.h"
#include "third_party.h"
#include "sess_list.h"
#include "rive_bzl.h"
#include "stora_utili.h"

#include "plugin_wt.h"

//

// #define	CONNE_CONFIG "create,cache_size=128MB,log=(archive=false,enabled=true)"
// #define	CONNE_CONFIG "create"
#define CONNE_CONFIG "create\
                    ,cache_size=1G\
                    ,session_max=2000\
                    ,eviction=(threads_max=4)\
                    ,log=(enabled=true,archive=true,path=journal)\
                    ,checkpoint=(wait=60,log_size=2G)\
                    ,statistics=(fast)"

#define JOURNAL_PATH "journal"
#define DISABLE_LOG ",log=(enabled=false)"

int wt_open_conne(riv_conne_t **connp, char *basen, int durab) {
    char journal_path[MAX_PATH * 3];
    char contain_home[MAX_PATH * 3];
    CONTAIN_ENGINE_FILE(journal_path, basen, WTIGER_ENAME, JOURNAL_PATH);
    CREAT_CONTAIN_DIRECTORY(contain_home, basen, WTIGER_ENAME);
    char config_str[CONF_LENGTH];
    strcpy(config_str, CONNE_CONFIG);
    //
    OSEVPF("[FUNC]:wt_open_conne creat, base:|%s|\n", basen);
    OSEVPF("contain_home:|%s|\n", contain_home);
    if (durab) { // create journal path
        DIRECTORY_EXISTS(journal_path)
        if (!S_ISDIR(statbuf.st_mode)) {
            if (mkdir(journal_path, 0755))
                _LOG_WARN("mkdir errno:%d", errno);
            _LOG_WARN("mkdir:%s", journal_path);
        }
    } else { // open disable log
        DIRECTORY_EXISTS(journal_path)
        if (S_ISDIR(statbuf.st_mode)) {
            int ret = wiredtiger_open(contain_home, NULL, config_str, (WT_CONNECTION **) connp);
            if (ret == EINVAL) {
                _LOG_WARN("wiredtiger_open result EINVAL.");
            } else if (ret != 0) {
                _LOG_WARN("wiredtiger_open result error.");
            }
            ((WT_CONNECTION *) connp[0x00])->close((connp[0x00]), NULL);
        }
        strcat(config_str, DISABLE_LOG);
    }
    //
    return wiredtiger_open(contain_home, NULL, config_str, (WT_CONNECTION **) connp);
}

int wt_close_conne(riv_conne_t *conne) {
    return ((WT_CONNECTION *) conne)->close(conne, NULL);
}

//

int wt_open_sess(rive_conne *conne, riv_sessi_t **sessp) {
    // ((WT_CONNECTION *) conne)->open_session((WT_CONNECTION *) conne, NULL, NULL, (WT_SESSION**) sessp);
    // ((WT_CONNECTION *) conne)->open_session((WT_CONNECTION *) conne, NULL, "isolation=snapshot", (WT_SESSION**) sessp);
    return ((WT_CONNECTION *) conne)->open_session((WT_CONNECTION *) conne, NULL, "isolation=snapshot", (WT_SESSION**) sessp);
}

int wt_close_sess(riv_sessi_t *sessi) {
    return ((WT_SESSION *) sessi)->close(sessi, NULL);
}

int wt_log_flush(riv_sessi_t *sessi) {
    return ((WT_SESSION *) sessi)->log_flush(sessi, "sync=on");
}

int wt_begin_transa_sess(riv_sessi_t *sessi) {
    return ((WT_SESSION *) sessi)->begin_transaction(sessi, NULL);
}

int wt_commit_transa_sess(riv_sessi_t *sessi) {
    return ((WT_SESSION *) sessi)->commit_transaction(sessi, NULL);
}

int wt_reset_sess(riv_sessi_t *sessi) {
    // ((WT_SESSION *) sessi)->commit_transaction(sessi, NULL);
    return ((WT_SESSION *) sessi)->reset(sessi);
}

//

int wt_open_curso(riv_curso_t **cursp, riv_sessi_t *sessi, char *uri, char *config) {
    return ((WT_SESSION *) sessi)->open_cursor(sessi, uri, NULL, config, (WT_CURSOR **) cursp);
}

int wt_open_curso_cont(riv_curso_t **cursp, riv_sessi_t *sessi, char *contai, char *config) {
    char open_uri[MAX_PATH * 3];
    lscpy(lscpy(open_uri, "table:"), contai);
    OSEVPF("[FUNC]:wt_open_table, open_uri:|%s|\n", open_uri);
    return ((WT_SESSION *) sessi)->open_cursor(sessi, open_uri, NULL, config, (WT_CURSOR **) cursp);
}

int wt_open_curso_prop(riv_curso_t **cursp, riv_sessi_t *sessi, char *contai, char *field, char *config) {
    char open_uri[MAX_PATH * 3];
    char *last_str = lscpy(open_uri, "table:");
    last_str = lscpy(last_str, contai);
    last_str = lccpy(last_str, '(');
    last_str = lscpy(last_str, field);
    lccpy(last_str, ')');
    OSEVPF("[FUNC]:wt_open_table, open_uri:|%s|\n", open_uri);
    return ((WT_SESSION *) sessi)->open_cursor(sessi, open_uri, NULL, config, (WT_CURSOR **) cursp);
}

int wt_open_curso_grou(riv_curso_t **cursp, riv_sessi_t *sessi, char *group, char *config) {
    char grouri[MAX_PATH * 3];
    lscpy(lscpy(grouri, "colgroup:"), group);
    OSEVPF("[FUNC]:wt_open_curso_grou, grouri:|%s|\n", grouri);
    return ((WT_SESSION *) sessi)->open_cursor(sessi, grouri, NULL, config, (WT_CURSOR **) cursp);
}

int wt_open_curso_inde(riv_curso_t **cursp, riv_sessi_t *sessi, char *index, char *config) {
    char induri[MAX_PATH * 3];
    lscpy(lscpy(induri, "index:"), index);
    OSEVPF("[FUNC]:wt_open_curso_inde, induri:|%s|\n", induri);
    return ((WT_SESSION *) sessi)->open_cursor(sessi, induri, NULL, config, (WT_CURSOR **) cursp);
}

int wt_close_curso(riv_curso_t *curso) {
    return ((WT_CURSOR *) curso)->close(curso);
}

int wt_inser_curso(riv_curso_t *curso) {
    return ((WT_CURSOR *) curso)->insert(curso);
}

int wt_reset_curso(riv_curso_t *curso) {
    return ((WT_CURSOR *) curso)->reset(curso);
}

int wt_next_curso(riv_curso_t *curso) {
    return ((WT_CURSOR *) curso)->next(curso);
}

int wt_prev_curso(riv_curso_t *curso) {
    return ((WT_CURSOR *) curso)->prev(curso);
}

int wt_search_curso(riv_curso_t *curso) {
    return ((WT_CURSOR *) curso)->search(curso);
}

int wt_searn_curso(riv_curso_t *curso, int *exactp) {
    return ((WT_CURSOR *) curso)->search_near(curso, exactp);
}

int wt_update_curso(riv_curso_t *curso) {
    return ((WT_CURSOR *) curso)->update(curso);
}

int wt_remove_curso(riv_curso_t *curso) {
    return ((WT_CURSOR *) curso)->remove(curso);
}

int wt_reconf_curso(riv_curso_t *curso, char *config) {
    return ((WT_CURSOR *) curso)->reconfigure(curso, config);
}

void set_key_wt(riv_curso_t *curso, PK_ITEM *key) {
    ((WT_CURSOR *) curso)->set_key(curso, key);
}

void set_sid_key_wt(riv_curso_t *curso, unsigned long long *key) {
    WT_ITEM key_item;
    key_item.data = key;
    key_item.size = sizeof (unsigned long long);
    ((WT_CURSOR *) curso)->set_key(curso, &key_item);
}

void set_value_wt(riv_curso_t *curso, PK_ITEM *value) {
    ((WT_CURSOR *) curso)->set_value(curso, value);
}

int get_key_wt(riv_curso_t *curso, PK_ITEM *value) {
    return ((WT_CURSOR *) curso)->get_key(curso, value);
}

int get_value_wt(riv_curso_t *curso, PK_ITEM *value) {
    return ((WT_CURSOR *) curso)->get_value(curso, value);
}

//

int wt_creat_contai(riv_sessi_t *sessi, char *contai, char *forma) {
    char crea_uri[MAX_PATH * 3];
    char *last_str = lscpy(crea_uri, "table:");
    lscpy(last_str, contai);
    conve_forma_style(forma);
    return ((WT_SESSION *) sessi)->create(sessi, crea_uri, forma);
}

//

int wt_dorp_contai(riv_sessi_t *sessi, char *contai) {
    char deop_uri[MAX_PATH * 3];
    char *last_str = lscpy(deop_uri, "table:");
    lscpy(last_str, contai);
    return ((WT_SESSION *) sessi)->drop(sessi, deop_uri, NULL);
}

//