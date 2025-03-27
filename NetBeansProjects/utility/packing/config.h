
/* 
 * File:   config.h
 * Author: james
 *
 * Created on 2022.9.28, PM 2:55
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "pk_internal.h"
#include "misc.h"
#include "pack_api.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct __pk_config {
        const char *orig;
        const char *end;
        const char *cur;

        int depth, top;
        const int8_t *go;
    };

    //
    void __pk_config_initn(PK_CONFIG *conf, const char *str, size_t len);

#define __pk_config_subinit(conf, item) __pk_config_initn(conf, item->str, item->len)

    //
    int __pk_config_next(PK_CONFIG *conf, PK_CONFIG_ITEM *key, PK_CONFIG_ITEM *value);

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_H */

