/* aserv_bzl.c
 * Created on: 2010-3-10
 * Author: Divad
 */

#include "osev_bzl.h"
#include "sconfig.h"

//

static serv_config *load_serv_config(const char *config_path);

//

serv_config *servbzl_create(char *xml_config) {
    fprintf(stdout, "[FUNC]:servbzl create start!\n");
    serv_config *config = load_serv_config(xml_config);
    if (config) fprintf(stderr, "Load config OK!\n");
    else fprintf(stderr, "Load config failed!\n");
    // chdir(config->data_directory);
    fprintf(stdout, "[FUNC]:servbzl create end!\n");
    return config; //succ
}

int servbzl_destroy() {
    fprintf(stdout, "[FUNC]:servbzl destroy start!\n");
    fprintf(stdout, "[FUNC]:servbzl destroy end!\n");
    return ERR_SUCCESS; //succ
}

//

static serv_config *load_serv_config(const char *config_path) {
    if (!config_path) return NULL;
    //
    if (serv_config_from_xml(&_serv_conf_, config_path))
        return NULL;
    find_user_group(_serv_conf_.user_name, _serv_conf_.group_name, &_serv_conf_._user_id_, &_serv_conf_._group_id_);
    //
    return &_serv_conf_;
}

serv_config *get_serv_config() {
    return &_serv_conf_;
}

//
