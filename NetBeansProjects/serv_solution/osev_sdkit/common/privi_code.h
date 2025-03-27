
/* 
 * File:   privi_code.h
 * Author: James Xu
 *
 * Created on 2023.4.11, AM 11:21
 */

#ifndef PRIVI_CODE_H
#define PRIVI_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

    // admin
#define INVA_PRIVI      0x00000000

    // general scope
#define SCOP_OSEV       0x01000000 // osev
#define SCOP_BASE       0x02000000 // base level
#define SCOP_CONT       0x04000000 // container
    // #define SCOP_ENTI       0x08000000 // entity
    // #define SCOP_CLAS       0x10000000 // lv2p
#define PRIVI_SCOPE(PRIV_CODE)    (0xFF000000 & PRIV_CODE) // PRIVI_SCOPE_MASK
#define PRIVI_SCOPE_CODE          0xFF000000
    //
    // general privile
#define PRIVI_VALUE(PRIV_CODE)    (0x00FFFFFF & PRIV_CODE) // PRIVI_VALUE_MASK
    // SCOP_OSEV privile
#define OVBP_POST       0x00000001 // post osev base
#define OVBP_STATU      0x00000002 // manage osev base
#define OVBP_COMND      0x00000003 // osev base
#define OVBP_PRIVI      0x00000004 // role / user
#define OVBP_CLUST      0x00000010 // clust
#define OBJE_SERV_PALL  (OVBP_POST | OVBP_STATU | OVBP_COMND | OVBP_PRIVI | OVBP_CLUST)
#define CLEAR_OVDBP(PRIV_CODE)    (0xFF000000 & PRIV_CODE) // CLEAR_OVDBP_MASK
    // SCOP_BASE LEVEL privile
#define BLVO_EXECU      0x00000001
#define BLVO_WRITE      0x00000002
#define BLVO_READ       0x00000004
#define BLVT_EXECU      0x00000010
#define BLVT_WRITE      0x00000020
#define BLVT_READ       0x00000040
#define BLVH_EXECU      0x00000100
#define BLVH_WRITE      0x00000200
#define BLVH_READ       0x00000400
#define BLVF_EXECU      0x00001000
#define BLVF_WRITE      0x00002000
#define BLVF_READ       0x00004000
#define BASE_LEVE_PALL  0x00007777
#define CLEAR_BLEVP(PRIV_CODE)    (0xFF000000 & PRIV_CODE) // CLEAR_BLEVP_MASK
    // SCOP_CONT privile
    // level three 
#define ENTP_POST       0x00000001
#define ENTP_STATU      0x00000002
#define ENTP_CREAT      0x00000004
#define ENTP_DROP       0x00000008
#define ENTP_UPDAT      0x00000010
#define ENTP_INSER      0x00000020
#define ENTP_SEARO      0x00000040
#define ENTP_INVOK      0x00000080
#define ENTI_METH_PALL   (ENTP_POST | ENTP_STATU | ENTP_CREAT | ENTP_DROP | ENTP_UPDAT | ENTP_INSER | ENTP_SEARO | ENTP_INVOK)
    // level foup
#define QUEP_POST       0x00001000
#define QUEP_STATU      0x00002000
#define QUEP_CREAT      0x00004000
#define QUEP_DROP       0x00008000
#define QUEP_UPDAT      0x00010000
#define QUEP_INSER      0x00020000
#define QUEP_SEARQ      0x00040000
#define QUEP_INVOK      0x00080000
#define QUEP_FACTO      0x00100000
#define QUER_METH_PALL   (QUEP_POST | QUEP_STATU | QUEP_CREAT | QUEP_DROP | QUEP_UPDAT | QUEP_INSER | QUEP_SEARQ | QUEP_INVOK | QUEP_FACTO)
#define QUEN_METH_PALL   (QUER_METH_PALL | ENTI_METH_PALL)
#define CLEAR_QUENP(PRIV_CODE)    (0xFF000000 & PRIV_CODE) // CLEAR_QUENP_MASK

    //

    struct _coqu_pvmk_ {
        unsigned int blv_pmk; // base level privileage mask
        unsigned int met_pmk; // method privileage mask
    };

    typedef struct _coqu_pvmk_ coqu_pvmk;

    // constr
    extern coqu_pvmk epost_privi; // post
    extern coqu_pvmk eecho_privi; // echo
    extern coqu_pvmk ecrea_privi; // creat
    extern coqu_pvmk edrop_privi; // drop
    extern coqu_pvmk eupda_privi; // updat
    extern coqu_pvmk einse_privi; // inser
    extern coqu_pvmk esear_privi; // search
    extern coqu_pvmk einvo_privi; // invok

    // query
    extern coqu_pvmk qpost_privi; // post
    extern coqu_pvmk qecho_privi; // echo
    extern coqu_pvmk qcrea_privi; // creat
    extern coqu_pvmk qdrop_privi; // drop
    extern coqu_pvmk qupda_privi; // updat
    extern coqu_pvmk qinse_privi; // inser
    extern coqu_pvmk qsear_privi; // search
    extern coqu_pvmk qinvo_privi; // invok
    extern coqu_pvmk qfact_privi; // facto

    // invoke
#define IPOST_PRIVI     BLVO_WRITE // post
#define IECHO_PRIVI     BLVO_READ // list
#define ICREAT_PRIVI    BLVO_WRITE // creat
#define IREPLA_PRIVI    BLVO_WRITE // repla
#define IDROP_PRIVI     BLVO_WRITE // drop
#define IINTEGRA_PRIVI  BLVO_EXECU // integra
#define IRELOAD_PRIVI   BLVO_EXECU // reload

    // colle
#define CPOST_PRIVI     BLVT_WRITE // post
#define CLIST_PRIVI     BLVT_READ // list
#define CCREAT_PRIVI    BLVT_WRITE // creat
#define CREPLA_PRIVI    BLVT_WRITE // repla
#define CDROP_PRIVI     BLVT_WRITE // drop
#define CINTEGRA_PRIVI  BLVT_EXECU // integra
#define CRELOAD_PRIVI   BLVT_EXECU // reload

#ifdef __cplusplus
}
#endif

#endif /* PRIVI_CODE_H */

