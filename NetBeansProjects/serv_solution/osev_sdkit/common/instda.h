
/* 
 * File:   instda.h
 * Author: James Xu
 *
 * Created on 2024.4.1, PM 2:37
 */

#ifndef INSTDA_H
#define INSTDA_H

#ifdef __cplusplus
extern "C" {
#endif

    struct _inher_versi_ {
        osv_oid_t lv2p_obid; // lv2p object id
        unsigned long long versio; // 0x00:disable >0x00:is version
    };

    typedef struct _inher_versi_ inher_versi;

#define SET_INVER_ZERO(INVEP) (INVEP)->lv2p_obid.osev_unique = 0x00;
#define IS_INVER_ZERO(INVEP) (!(INVEP)->lv2p_obid.osev_unique)
#define NOT_INVER_ZERO(INVEP) ((INVEP)->lv2p_obid.osev_unique)

    // attrib

    struct _instda_ {
        char *lv2p_decl;
        // class instant, check version
        unsigned long long versio; // 0x00:disable >0x00:is version
        inher_versi inhver[CINHE_COUNT_ZTAI];
        //
    };

    typedef struct _instda_ instda;

    //

    inline instda *mallo_instda(char *lv2_dec) {
        instda *insai = (instda *) malloc(sizeof (instda));
        insai->lv2p_decl = strdup(lv2_dec);
        return insai;
    }

    //

    void dele_instda(void *insai);


#ifdef __cplusplus
}
#endif

#endif /* INSTDA_H */

