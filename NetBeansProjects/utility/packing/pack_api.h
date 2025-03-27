
/* 
 * File:   pack_api.h
 * Author: james
 *
 * Created on 2022.9.27, PM 4:07
 */

#ifndef PACK_API_H
#define PACK_API_H

#include "packing.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

#define PK_ERROR (-31802)
#define PK_NOTFOUND (-31803)

    // The configuration information returned by the WiredTiger configuration
    // parsing functions in the PK_EXTENSION_API and the public API.

    struct __pk_config_item {
        /* The value of a configuration string.
         * Regardless of the type of the configuration string (boolean, int,
         * list or string), the \c str field will reference the value of the
         * configuration string.
         * The bytes referenced by \c str are <b>not</b> nul-terminated,
         * use the \c len field instead of a terminating nul byte. */
        const char *str;

        // The number of bytes in the value referenced by \c str.
        size_t len;

        /* The numeric value of a configuration boolean or integer.
         * If the configuration string's value is "true" or "false", the
         * \c val field will be set to 1 (true), or 0 (false).
         * If the configuration string can be legally interpreted as an integer,
         * using the strtoll function rules as specified in ISO/IEC 9899:1990
         * ("ISO C90"), that integer will be stored in the \c val field. */
        int64_t val;

        // Permitted values of the \c type field.

        enum {
            // A string value with quotes stripped.
            PK_CONFIG_ITEM_STRING,
            // A boolean literal ("true" or "false").
            PK_CONFIG_ITEM_BOOL,
            // An unquoted identifier: a string value without quotes.
            PK_CONFIG_ITEM_ID,
            // A numeric value.
            PK_CONFIG_ITEM_NUM,
            // A nested structure or list, including brackets.
            PK_CONFIG_ITEM_STRUCT
        }
        /* The type of value determined by the parser.  In all cases,
         * the \c str and \c len fields are set. */
        type;
    };

    typedef struct __pk_config_item PK_CONFIG_ITEM;

#ifdef __cplusplus
}
#endif

#endif /* PACK_API_H */

