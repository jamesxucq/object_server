
/* 
 * File:   pretty_ite.h
 * Author: James Xu
 *
 * Created on 2024.5.15, PM 3:59
 */

#ifndef PRETTY_ITE_H
#define PRETTY_ITE_H

#ifdef __cplusplus
extern "C" {
#endif

    // build fmtstr e->s 

    inline void build_packi_fmtst(char *fmtstr, char *prestr) {
        for (; prestr[0x00]; ++prestr, ++fmtstr) {
            if ('x' == prestr[0x00])
                fmtstr[0x00] = 's';
            else fmtstr[0x00] = prestr[0x00];
        }
        fmtstr[0x00] = '\0';
    }

    // 0x00:OK -1:error

    int pretty_variable_echo(clit_resu *resul, char *fmtstr, char *prestr, char *resp_data, uint64 quer_leng);

#ifdef __cplusplus
}
#endif

#endif /* PRETTY_ITE_H */

