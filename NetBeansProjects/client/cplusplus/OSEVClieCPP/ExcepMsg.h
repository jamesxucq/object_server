
/* 
 * File:   ExcepMsg.h
 * Author: James Xu
 *
 * Created on 2017.9.21
 */

#ifndef EXCEP_MSG_H
#define EXCEP_MSG_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    const char *excep_stri(int exce_code);
    void excep_echo(char *exce_data, int exce_len);



#ifdef __cplusplus
}
#endif

#endif /* EXCEP_MSG_H */

