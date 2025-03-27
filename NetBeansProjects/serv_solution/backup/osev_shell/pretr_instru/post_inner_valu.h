
/* 
 * File:   post_inner_valu.h
 * Author: james
 *
 * Created on 2024.5.14, PM 2:53
 */

#ifndef POST_INNER_VALU_H
#define POST_INNER_VALU_H

#ifdef __cplusplus
extern "C" {
#endif

    // default, lv2p

    inline int ipti_inner_inst(char **pamvp) {
        //
        return 0x00;
    }

    // default, lv2p
    int cpti_inner_inst(char **pamvp);

    // default, lv2p

    inline int epti_inner_inst(char **pamvp) {
        //
        return 0x00;
    }

    // default, lv2p

    inline int qpti_inner_inst(char **pamvp) {
        //
        return 0x00;
    }

    //

#ifdef __cplusplus
}
#endif

#endif /* POST_INNER_VALU_H */

