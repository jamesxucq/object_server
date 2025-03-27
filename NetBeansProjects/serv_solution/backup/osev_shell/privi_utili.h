
/* 
 * File:   privi_utili.h
 * Author: james
 *
 * Created on 2023.4.6, PM 1:50
 */

#ifndef PRIVI_UTILI_H
#define PRIVI_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    // admin
#define INVA_PRIVI       0x00000000
    //
    // general scope
#define SCOP_OSEV       0x01000000 //
#define SCOP_BASE       0x02000000 // base level
#define SCOP_CONT       0x04000000 // entity / container
    //
    // general privile
    // SCOP_OSEV privile
#define OVBP_COMND      0x00000001 // osev base
#define OVBP_STATU      0x00000002 // manage osev base
#define OVBP_PRIVI      0x00000004 // role / user
#define OVBP_CLUST      0x00000008 // clust
#define OBJE_SERV_PALL  (OVBP_COMND | OVBP_STATU | OVBP_PRIVI | OVBP_CLUST)
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
    // SCOP_CONT privile
    // LEVEL three
#define ENTP_POST       0x00000001
#define ENTP_ECHO       0x00000002
#define ENTP_CREAT      0x00000004
#define ENTP_DROP       0x00000008
#define ENTP_UPDAT      0x00000010
#define ENTP_INSER      0x00000020
#define ENTP_SEARO      0x00000040
#define ENTP_INVOK      0x00000080
#define ENTI_METH_PALL   (ENTP_POST | ENTP_ECHO | ENTP_CREAT | ENTP_DROP | ENTP_UPDAT | ENTP_INSER | ENTP_SEARO | ENTP_INVOK)
    // level foup
#define QUEP_POST       0x00001000
#define QUEP_ECHO       0x00002000
#define QUEP_CREAT      0x00004000
#define QUEP_DROP       0x00008000
#define QUEP_UPDAT      0x00010000
#define QUEP_INSER      0x00020000
#define QUEP_SEARQ      0x00040000
#define QUEP_INVOK      0x00080000
#define QUEP_FACTO      0x00100000
#define QUER_METH_PALL   (QUEP_POST | QUEP_ECHO | QUEP_CREAT | QUEP_DROP | QUEP_UPDAT | QUEP_INSER | QUEP_SEARQ | QUEP_INVOK | QUEP_FACTO)
#define QUEN_METH_PALL   (QUER_METH_PALL | ENTI_METH_PALL)

    // client extend scope
#define INVA_SBLV   0x00000000
#define SBLV_ONE    0x00000001
#define SBLV_TWOP   0x00000002
#define SBLV_THRE   0x00000004
#define SBLV_FOUP   0x00000008
    // "12p34p" "12+34+"
    // "1 2p 3 4p" "1 2+ 3 4+"
    // "1,2p,3,4p" "1,2+,3,4+"
    uint32 gengr_level(char *leve_stri);

    //
    uint32 parse_disti_scope(OUT uint32 *lev_valu, char *dist_iden, const char *objide);
    uint32 parse_osev_privi(char *privi);

    // clent extend privile
#define BLVP_EXECU  0x00000001
#define BLVP_WRITE  0x00000002
#define BLVP_READ   0x00000004
    uint32 parse_base_privi(char *privi);
    uint32 parse_cont_privi(char *privi);
    int ochk_priv_valu(uint32 priv_valu);
    int bchk_priv_valu(uint32 priv_valu);
    int cchk_priv_valu(uint32 priv_valu);

#ifdef __cplusplus
}
#endif

#endif /* PRIVI_UTILI_H */

