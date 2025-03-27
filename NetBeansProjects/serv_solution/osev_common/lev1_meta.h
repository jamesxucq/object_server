
/* 
 * File:   lev1_meta.h
 * Author: James Xu
 *
 * Created on 2017.1.10, PM 2:12
 */

#ifndef LEVO_LIST_H
#define LEVO_LIST_H

#include "third_party.h"
#include "utility/action_hmap.h"
#include "utility/cache_hmap.h"
#include "commo_macro.h"
#include "osev_datyp.h"
#include "osev_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _dyli_hand_ {
        char lev1_librn[LVON_LENGTH];
        void *handle;
        int refer_inde;
        //
        struct _dyli_hand_ *next;
    };

    typedef struct _dyli_hand_ dyli_hand;

    //

    inline dyli_hand *mallo_dyhand() {
        dyli_hand *dyhand = (dyli_hand *) malloc(sizeof (dyli_hand));
        if (!dyhand) return NULL;
        memset(dyhand, '\0', sizeof (dyli_hand));
        return dyhand;
    }

#define FREE_DYHAND(DYHAND) {if (DYHAND) free(DYHAND);}

    //
    dyli_hand *open_dyhand(dyli_hand **dylsth, char *libr_path, char *lev1_librn);

    // 0x00:hand refer zero. >0x00:refer count <0x00:error
    int close_dyhand(OUT char *lev1_librn, dyli_hand **dylsth, void *libr_hand);
    void dele_dyhand(dyli_hand *dyhand);

    //

    union _METHO_USER_ {
        void (*constr)(void *, void *);
        void (*invoke)(void *, void *, void *);
    };

    typedef union _METHO_USER_ METHO_USER;
    //

    enum _CALLER_TYPE_ {
        RTYP_VOID = 0x00,
        RTYP_CHAR,
        RTYP_UCHA,
        RTYP_SHOR,
        RTYP_USHO,
        RTYP_INT,
        RTYP_UINT,
        RTYP_LONG,
        RTYP_ULON,
        RTYP_LLON,
        RTYP_ULLO,
        RTYP_OBID,
        RTYP_FLOA,
        RTYP_DOUB,
        RTYP_CHAP,
        RTYP_STRZ
    };
    // trans-serve
    typedef enum _CALLER_TYPE_ CALLER_TYPE;

    // lv2pme
#include "parms_style.h"
#include "../osev_sdkit/common/lv2p_meta.h"

    //

    struct _lev1me_ {
        // lev1me name
        char handn[HANDN_LENGTH];
        int norma_const; // -1:error 0x00:constructor 0x01:normal
        // .so handler
        void *libr_hand;
        METHO_USER method;
        // lv2p meta
        lv2pme *lv2me;
        // lev1 meta
        char lev1n[LVON_LENGTH];
        CALLER_TYPE oivk_retyp_oe; // oivk return type 
        //
        char oivk_fmtsp_oe[FMTST_COUNT_ZTAI]; // out invoke params format string
        // unsigned char fixed_float_oe; // 0x00:fixed 0x01:float
        int oivk_size_oe; // oivk struct length
    };

    typedef struct _lev1me_ lev1me;
    //

    inline lev1me * mallo_lev1me() {
        lev1me *lv1me = (lev1me *) malloc(sizeof (lev1me));
        if (!lv1me) return NULL;
        memset(lv1me, '\0', sizeof (lev1me));
        return lv1me;
    }

    inline void dele_lev1me(void *lv1me) {
        if (lv1me) free(lv1me);
    }

    //

    struct _hand_hashmap_ {
        dyli_hand *dyha_list;
        actionmap *lev1n_hm; // lev1 name map
    };

    typedef struct _hand_hashmap_ hand_hmap;

    // lev1
#define HANDO_CACHE_INITI(HANDO, DELE_FUNC, BACKET_SIZE) { \
    HANDO.dyha_list = NULL; \
    HANDO.lev1n_hm = creat_actio(DELE_FUNC, BACKET_SIZE); \
}

#define FINAL_HANDO_CACHE(HANDO) { \
    action_destroy(HANDO.lev1n_hm); \
    dele_dyhand(HANDO.dyha_list); \
}

#ifdef __cplusplus
}
#endif

#endif /* LEVO_LIST_H */

