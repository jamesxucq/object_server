
/* 
 * File:   stati_scont.h
 * Author: James Xu
 *
 * Created on 2024.5.31, PM 3:07
 */

#ifndef STATI_SCONT_H
#define STATI_SCONT_H

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _stati_scont_ {
        contain *contp;
        char *cont_name;
        osv_oid_t *lv2p_type;
        unsigned int sinde; // reference contain index
        unsigned int append; // 0x00:exists, not append 0x01:append
    };

    typedef struct _stati_scont_ stati_scont;

    //
#define CHK_ZERO_SSCON(SSCON) ((SSCON)->contp)
#define MAKE_SSCON_ZERO(SSCON) (SSCON)->contp = NULL;


#ifdef __cplusplus
}
#endif

#endif /* STATI_SCONT_H */

