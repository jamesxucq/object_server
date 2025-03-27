
/* 
 * File:   valid_logic.h
 * Author: james
 *
 * Created on 2024.5.17, PM 4:05
 */

#ifndef VALID_LOGIC_H
#define VALID_LOGIC_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int valid_levon_exten(unsigned int levivk, char **pamvp);
    int valid_levon_pamvs(unsigned int levivk, char **pamvp);
    
    //
    int valid_levtp_pamvs(unsigned int levivk, char **pamvp);

#ifdef __cplusplus
}
#endif

#endif /* VALID_LOGIC_H */

