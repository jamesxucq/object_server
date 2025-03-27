
/* 
 * File:   lv2p_attri.h
 * Author: James Xu
 *
 * Created on 2024.4.10, AM 9:38
 */

#ifndef LVTP_ATTRI_H
#define LVTP_ATTRI_H

// #include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 0x02:meth 0x04:lev1 0x08:lv2p 0x10:clas
#define INHE_TYPE_METH     LVTP_INHE_METH // 0x02 // lv2pn:methn( , , ) // inherit method, bind current data
#define INHE_TYPE_LEVO     LVTP_INHE_LEVO // 0x04 // lv2pn:methn // inherit method and data
#define INHE_TYPE_LVTP     LVTP_INHE_LVTP // 0x08 // lv2pn:sub_clasn // inherit sub class   
#define INHE_TYPE_CLAS     LVTP_INHE_CLAS // 0x10 // lv2pn // inherit whole class   

    struct _inherit_ {
        int rang_type; // 0x02:meth 0x04:lev1 0x08:lv2p 0x10:clas
        char lv2pn[LVTN_LENGTH];
        char lev1n[LVON_LENGTH];
        //
        struct _inherit_ *next;
    };

    typedef struct _inherit_ inherit;

    //
#define INTE_NORM_METH     LVTP_NORM_METH // lev1n( , , )
#define INTE_INHE_METH     LVTP_INHE_METH // lv2pn:lev1n( , , )
#define INTE_INHE_LEVO     LVTP_INHE_LEVO // lv2pn:lev1n
#define INTE_INHE_LVTP     LVTP_INHE_LVTP // lv2pn:sub_clasn
#define INTE_INHE_CLAS     LVTP_INHE_CLAS // lv2pn

    struct _integra_ {
        // 0x01:norm meth 0x02:inhe meth 0x04:inhe lev1 0x08:inhe lv2p 0x10:inhe clas
        int rang_type;
        char lv2pn[LVTN_LENGTH];
        char lev1n[LVON_LENGTH];
        //
        struct _integra_ *next;
    }; // integrality

    typedef struct _integra_ integra;

    //

    struct _lv2p_attri_ {
        osv_oid_t lv2p_obid;
        char lv2pn[LVTN_LENGTH];
        unsigned long long versio; // 0x00:disable >0x00:is version
        bool_osv iexter; // 0x00: internal 0x01: external
        integra *integ_list;
        inherit *inher_list;
    };

    typedef struct _lv2p_attri_ lv2p_attri;

    //
#define INITI_INTEG_INHER(LVTPAI) { \
    LVTPAI->integ_list = NULL; \
    LVTPAI->inher_list = NULL; \
}

    //    
    integra *new_integ_list(integra **olsth);

    inline void olist_dele(integra *olist) {
        integra *olsnd;
        while ((olsnd = olist)) {
            olist = olist->next;
            free(olsnd);
        }
    }
#define LEVONE_DELET(OLIST) free(OLIST);

    //
    inherit *appe_ilist_new(inherit **ilsth);

    inline void ilist_dele(inherit *ilist) {
        inherit *ilsnd;
        while ((ilsnd = ilist)) {
            ilist = ilist->next;
            free(ilsnd);
        }
    }

    //

    inline lv2p_attri *mallo_lv2pai() {
        lv2p_attri *lv2ai = (lv2p_attri *) malloc(sizeof (lv2p_attri));
        return lv2ai;
    }

    void dele_lv2pai(void *lv2ai);

#ifdef __cplusplus
}
#endif

#endif /* LVTP_ATTRI_H */

