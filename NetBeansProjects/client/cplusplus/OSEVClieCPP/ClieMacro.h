
/* 
 * File:   ClieMacro.h
 * Author: James Xu
 *
 * Created on 2024.5.17, AM 9:26
 */

#ifndef CLIEMACRO_H
#define CLIEMACRO_H

#ifdef __cplusplus
extern "C" {
#endif

    // check attribute: version, external

    // #define _CHECK_VERSION_EVERYTIME
    // #define _CHECK_VERSION_INTERVAL // interval
    // #define _CHECK_ATTRIBU_EVERYTIME
#define _CHECK_ATTRIBU_INTERVAL // interval
    // #define _DONOT_CHECK_ATTRIBU

    //
#define CHECK_ATTRIBU_FREQUENCY   (1024-1) // 2^10-1


#ifdef __cplusplus
}
#endif

#endif /* CLIEMACRO_H */

