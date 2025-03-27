
#include "commo_header.h"
#include "kcomm_header.h"
#include "debug_funct_co.h"

//
/*
void p_lev1d_debug(lev1_decl_i *lev1d) {
    printf(" lev1d --------\n");
    printf(" lev1d->innep.inne_fmtsp:|%08X|\n", lev1d->levtyp);
    char cline[LINE_LENGTH];
    printf(" lev1d->clasn_inhe:|%s|\n", echo_inher_clasn(cline, lev1d->lv2pn, lev1d->clasn_inhe));
    printf(" lev1d->lev1n:|%s|\n", lev1d->lev1n);
    printf(" lev1d->inne_pams:|%s|\n", lev1d->inne_pams);
    printf(" lev1d->innep.inne_fmtsp:|%s|\n", lev1d->innep.inne_fmtsp);
}
 */

//

void p_lev1d_debug(lev1_decl_t *lev1d) {
    printf(" lev1d --------\n");
    printf(" lev1d->innep.inne_fmtsp:|%08X|\n", lev1d->levtyp);
    // char cline[LINE_LENGTH];
    // printf(" lev1d->clasn_inhe:|%s|\n", echo_inher_clasn(cline, lev1d->lv2pn, lev1d->clasn_inhe));
    // printf(" lev1d->lev1n:|%s|\n", lev1d->lev1n);
    printf(" lev1d->innep.inne_pams:\n");
    char **innep = lev1d->innep.inne_pams;
    for (; innep[0x00]; ++innep) printf("----- innep:|%s|\n", innep[0x00]);
    printf(" lev1d->innep.inne_fmtsp:|%s|\n", lev1d->innep.inne_fmtsp);
}

void p_lv2pd_debug(lv2p_decl_t *lv2dt) {
    printf(" lv2dt --------\n");
    printf(" lv2dt->lv2pn:|%s|\n", lv2dt->lv2pn);
    lv2p_prop *lv2nod = lv2dt->lv2nod;
    printf("----- lv2nod -----\n");
    for (; ACCE_COTRL_INVAL != lv2nod->access; ++lv2nod) {
        // printf("attri:|%08X| name:|%s| type:|%s| size:|%s| decla:|%s|\n", lv2nod->access, lv2nod->name, lv2nod->xxxxxtype, lv2nod->size, lv2nod->decla);
    }
    lev1_decl_t *lv1d = lv2dt->meth;
    printf("----- meth -----\n");
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        printf("levtyp:|%08X| lv2pn:|%s| inhe_lv2n:|%s| ident:|%s| fmtsp:|%s|\n", lv1d->levtyp, lv1d->lv2pn, lv1d->inhe_lv2n[0x00], lv1d->ident, lv1d->innep.inne_fmtsp);
    }
}

//

void p_lev1_list(lev1_list *l1lst) {
    lev1_meta *lev1m = &l1lst->lev1m;
    printf("----- p_lev1_list -----\n");
    printf("layout:%08X\n", lev1m->layout);
    if (HAVE_CLASN & lev1m->layout) printf("lv2pn:|%s|\n", lev1m->lv2pn);
    if (HAVE_METHN & lev1m->layout) printf("lev1n:|%s|\n", lev1m->lev1n);
    if (HAVE_DECLA & lev1m->layout) printf("decla:|%s|\n", lev1m->decla);
    if (HAVE_BODY & lev1m->layout) printf("body:|%s|\n", lev1m->body);
    printf("next:%p\n", l1lst->next);
    printf("---------------------\n");
}

//

void p_parms_label(char *label, char **pamvp) {
    char text_buff[PATH_MAX * 0x02];
    char *last_str = text_buff;
    //
    last_str = lscpy(last_str, label);
    last_str = lccpy(last_str, '\n');
    size_t wrilen = write(STDERR_FILENO, text_buff, strlen(text_buff));
    if (strlen(text_buff) != wrilen) {
        printf("write ERROR!\n");
    }
    //
    last_str = text_buff;
    for (; pamvp[0x00]; ++pamvp) {
        last_str = lscpy(last_str, pamvp[0x00]);
        last_str = lccpy(last_str, ' ');
    }
    last_str = lccpy(last_str, '\n');
    wrilen = write(STDERR_FILENO, text_buff, strlen(text_buff));
    if (strlen(text_buff) != wrilen) {
        printf("write ERROR!\n");
    }
}

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
        char inne_fmtsp[FMTST_COUNT_ZTAI]; //  meth binding param type
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

void p_lv2p_expa_tx(lv2p_expa_t *lv2expt) {
    printf("p_lv2p_expa_tx\n");
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
}

