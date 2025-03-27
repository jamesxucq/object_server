
/* 
 * File:   parse_expan.h
 * Author: James Xu
 *
 * Created on 2023.10.17, PM 4:16
 */

#ifndef PARSE_EXPAN_H
#define PARSE_EXPAN_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    char *parse_lv2expt_count(lv2p_expa_t *lv2expt, char *lv2e_cont);
    char *parse_lv2expt_content(lv2p_expa_t *lv2expt, char *lv2e_cont);


#ifdef __cplusplus
}
#endif

#endif /* PARSE_EXPAN_H */

