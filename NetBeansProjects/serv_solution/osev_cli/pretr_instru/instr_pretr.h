
/* 
 * File:   instr_pretr.h
 * Author: James Xu
 *
 * Created on 2023.4.14, PM 2:03
 */

#ifndef INSTR_PRETR_H
#define INSTR_PRETR_H

#ifdef __cplusplus
extern "C" {
#endif

    // pretr_instruct_comd
    int pretr_clie_use(char **pamvp);
    int pretr_osev_inte(const char *objide, unsigned int levivk, unsigned int invok, char **pamvp, char *_sline_);
    int pretr_base_inte(const char *objide, unsigned int levivk, unsigned int invok, char **pamvp, char *_sline_);
    //
    int pretr_conte_levon(uint32 run_level, unsigned int levivk, char **pamvp, char *_sline_);
    int pretr_conte_levtp(unsigned int levivk, unsigned int invok, char **pamvp, char *_sline_);
    int pretr_conte_levth(uint32 run_level, unsigned int levivk, char **pamvp, char *_sline_);
    int pretr_conte_levfp(unsigned int levivk, unsigned int invok, char **pamvp, char *_sline_);

#ifdef __cplusplus
}
#endif

#endif /* INSTR_PRETR_H */

