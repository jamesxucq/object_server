
/* 
 * File:   inte_const.h
 * Author: James Xu
 *
 * Created on 2017.6.17., PM1:43
 */

#ifndef INTE_CONST_H
#define INTE_CONST_H

// the third level

#ifdef __cplusplus
extern "C" {
#endif

    //
    void const_post_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void const_statu_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void const_creat_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void const_drop_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void const_updat_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void const_inser_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void const_searc_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void const_invok_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);


#ifdef __cplusplus
}
#endif

#endif /* INTE_CONST_H */

