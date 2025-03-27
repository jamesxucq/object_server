
/* 
 * File:   post_inner_valu.h
 * Author: James Xu
 *
 * Created on 2024.5.14, PM 2:53
 */

#ifndef POST_INNER_VALU_H
#define POST_INNER_VALU_H

#ifdef __cplusplus
extern "C" {
#endif

    // default, lv2p
    int ipot_inner_inst(char **pamvp);

    // default, lv2p
    int cpot_inner_inst(char **pamvp);

    // default, lv2p

    inline int epot_inner_inst(char **pamvp) {
        //
        return 0x00;
    }

    // default, lv2p

    inline int qpot_inner_inst(char **pamvp) {
        //
        return 0x00;
    }

    //

#ifdef __cplusplus
}
#endif

#endif /* POST_INNER_VALU_H */

