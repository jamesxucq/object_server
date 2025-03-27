
/* 
 * File:   parse_levivk.h
 * Author: James Xu
 *
 * Created on 2017.5.21, PM3:43
 */

#ifndef PARSE_LEVIVK_H
#define PARSE_LEVIVK_H

#ifdef __cplusplus
extern "C" {
#endif

// 0:success 0x01:exception -1:error
    int parse_iinstru_levivk(cli_inst *cinst, uint32 cli_mode, uint32 run_level);
    
    //
    int parse_kinstru_levivk(cli_inst *cinst, uint32 cli_mode, uint32 run_level);



#ifdef __cplusplus
}
#endif

#endif /* PARSE_LEVIVK_H */

