
/* 
 * File:   parse_l12con.h
 * Author: James Xu
 *
 * Created on 2017.6.22, PM 3:20
 */

#ifndef PARSE_LOTCON_H
#define PARSE_LOTCON_H

#ifdef __cplusplus
extern "C" {
#endif

    class_meta *parse_lev1_cont(class_meta *clsmt, char *lev1_cont);
    class_meta *parse_lv2p_cont(class_meta *clsmt, char *lv2p_cont);

#ifdef __cplusplus
}
#endif

#endif /* PARSE_LOTCON_H */

