
/* 
 * File:   cur_json.h
 * Author: james
 *
 * Created on 2022.9.28, PM 3:20
 */

#ifndef CUR_JSON_H
#define CUR_JSON_H

#include "misc.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    ssize_t __pk_json_strlen(const char *src, size_t srclen);
    int __pk_json_strncpy(char **pdst, size_t dstlen, const char *src, size_t srclen);


#ifdef __cplusplus
}
#endif

#endif /* CUR_JSON_H */

