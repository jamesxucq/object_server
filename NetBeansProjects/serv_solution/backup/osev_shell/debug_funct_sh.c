#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "osev_clie_clang.h"
#include "osvp_utili.h"

#include "debug_funct_sh.h"


//

void p_cli_instru(cli_inst *cinst) {
    printf("p_cli_instru --------------------\n");
    printf("coline:|%s|\n", cinst->coline);
    printf("inst_levtyp:|%d|\n", cinst->inst_levtyp);
    printf("obje_iden:|%s|\n", cinst->obje_iden);
    printf("inst_attrib:%u\n", cinst->inst_attrib);
    printf("cont_levivk:|%s|\n", cinst->cont_levivk);
    printf("inst_levivk:%u\n", cinst->inst_levivk);
    printf("cont_invok:|%s|\n", cinst->cont_invok);
    printf("inst_invok:%u\n", cinst->inst_invok);
    //
    unsigned int inde = 0x00;
    const char **pamvp = cinst->pamcon;
    for (; pamvp[0x00] && '\0' != (*pamvp)[0x00]; ++inde, ++pamvp)
        printf("cinst->pamcon[%d]:|%s|\n", inde, pamvp[0x00]);
    printf("--------------------\n");
}

//

/*
    struct _cli_inst_ {
        char coline[LARGE_TEXT_SIZE];
        unsigned int inst_attrib; //
        unsigned int inst_levtyp;
        const char obje_iden[OBJN_LENGTH];
        char comd_meth[LVON_LENGTH];
        unsigned int inst_levivk;
        //
        char pamtyp[PARAM_COUNT];
        const char *pamvu[PARAM_COUNT];
        char _pline_[LARGE_CONTE_SIZE];
        int reserved;
    };

    typedef struct _cli_inst_ cli_inst;
 */

void p_instru(cli_inst *cinst) {
    printf("cinst->coline:|%s|\n", cinst->coline);
    printf("cinst->inst_attrib:%08x\n", cinst->inst_attrib);
    printf("cinst->inst_levtyp:%u\n", cinst->inst_levtyp);
    printf("cinst->obje_iden:|%s|\n", cinst->obje_iden);
    printf("cinst->cont_levivk:|%s|\n", cinst->cont_levivk);
    printf("cinst->inst_levivk:%u\n", cinst->inst_levivk);
    printf("cinst->cont_invok:|%s|\n", cinst->cont_invok);
    printf("cinst->inst_invok:%u\n", cinst->inst_invok);
    //
    printf("cinst->pamtyp:%s\n", cinst->pamtyp);
    printf("cinst->pamcon[0x00]:%s\n", cinst->pamcon[0x00]);
    printf("cinst->reserved:%d\n", cinst->reserved);
}

void p_clie_auth(osvp_auth *clie_auth, const char *osvp_uri) {
    printf("osvp_uri:|%s|\n", osvp_uri);
    printf("sin_addr:|%s|\n", clie_auth->saddr.sin_addr);
    printf("sin_port:%d\n", clie_auth->saddr.sin_port);
    printf("_osev_base_:|%s|\n", clie_auth->osev_base);
    printf("user_name:|%s|\n", clie_auth->authe.user_name);
    printf("password:|%s|\n", clie_auth->authe.pass_word);
}

/*
void PRIN_md5sum_os(unsigned char *md5sum) {
    char sum_stri[33];
    char *chks_str = sum_stri;
    unsigned char *digest = md5sum;
    uint32 inde = 0x00;
    for (; inde < 16; ++inde, ++digest) {
        sprintf(chks_str, "%02x", *digest);
        ++chks_str;
        ++chks_str;
    }
    printf("md5sum:|%s|\n", sum_stri);
}
 */

//

static void p_lv2p_prop_qc(lv2p_prop *lv2nod) {
    printf("---------------\n");
    printf("attri:%08X\n", lv2nod->access);
    printf("name:|%s|\n", lv2nod->name);
    printf("potyp:|%d|\n", lv2nod->potyp);
    printf("decla:|%s|\n", lv2nod->decla);
}

/*
     typedef struct {
        int levtyp; // 0x01: normal method 0x02:inherit method 0x04: inherit class
        char lv2pn[LVTN_LENGTH];
        char *inhe_lv2n[INHE_COUNT];
        char _cline_[LINE_LENGTH];
        char ident[LVON_LENGTH]; // clasn / methn
        char inne_pams[PARAM_LENGTH];
        char inne_fmtsp[FMTST_COUNT_ZTAI]; //  meth binding pamvu type
    } lev1_inne_t;
 */

static void p_lev1_decl_qc(lev1_decl_t *lev1d) {
    printf("----- PRIN_lev1_decl\n");
    printf("levtyp:|%d|\n", lev1d->levtyp);
    printf("lv2pn:|%s|\n", lev1d->lv2pn);
    printf("inhe_lv2n:\n");
    char **ilv2np = lev1d->inhe_lv2n;
    for (; ilv2np[0x00]; ++ilv2np) printf("----- ilv2np:|%s|\n", ilv2np[0x00]);
    printf("ident:|%s|\n", lev1d->ident);
    printf("inne_pams:\n");
    char **innep = lev1d->innep.inne_pams;
    for (; innep[0x00]; ++innep) printf("----- innep:|%s|\n", innep[0x00]);
    printf("inne_fmtsp:|%s|\n", lev1d->innep.inne_fmtsp);
}

void p_sh_lv2p_expa_t(lv2p_expa_t *lv2expt) {
    printf("--------- p_io_lv2p_expa_t ---------\n");
    printf("lv2expt->lv2o_coun:|%d|\n", lv2expt->lv2o_coun);
    lv2p_prop *lv2nod = lv2expt->lv2nod;
    for (; ACCE_COTRL_INVAL != lv2nod->access; ++lv2nod) {
        p_lv2p_prop_qc(lv2nod);
    }
    //
    printf("lv2expt->lv1d_coun:|%d|\n", lv2expt->lv1d_coun);
    lev1_decl_t *lv1d = lv2expt->lv1dat;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        p_lev1_decl_qc(lv1d);
    }
    printf("--------- End p_io_lv2p_expa_t ---------\n");
}
