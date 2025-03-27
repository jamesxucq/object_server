
#include "commo_header.h"
#include "kcomm_header.h"
#include "filli_clang.h"
#include "debug_funct_oi.h"
#include "lev1_decla.h"

//

void p_parse_metho(conve_metho *metho) {
    printf("lv2pn:|%s|\n", metho->lv2pn);
    printf("lev1n:|%s|\n", metho->lev1n);
    printf("oivk_type:|%s|\n", metho->oivk_retyp);
    printf("line_oivk:|%s|\n", metho->line_oivk);
    printf("param_type:|%s|\n", metho->oivk_fmtsp);
    printf("ibind:|%s|\n", metho->ibind);
    printf("lev1_body:|%s|\n", metho->lev1_body);
}

// 

void p_lv2p_prop(lv2p_prop *lv2nod) {
    printf("---------------\n");
    printf("attri:%08X\n", lv2nod->access);
    printf("name:|%s|\n", lv2nod->name);
    printf("potyp:|%d|\n", lv2nod->potyp);
    printf("decla:|%s|\n", lv2nod->decla);
}

void p_lv2p_prop_array(lv2p_prop *lv2nod) {
    printf("A ******************\n");
    lv2p_prop *l2nod2 = lv2nod;
    for (; ACCE_COTRL_INVAL != l2nod2->access; ++l2nod2) {
        p_lv2p_prop(l2nod2);
    }
    printf("Z ******************\n");
}

void p_colum(colum *colu_data) {
    printf("p_colum A **********\n");
    for (; COLU_END != colu_data->type; ++colu_data) {
        printf("colu_data->name:|%s| size:|%s| type:%d\n", colu_data->name, colu_data->size, colu_data->type);
    }
    printf("Z ******************\n");
}

//

void p_inherit(inherit *ilsnd) {
    printf("----- p_inherit\n");
    printf("rang_type:|%d|\n", ilsnd->rang_type);
    printf("lv2pn:|%s|\n", ilsnd->lv2pn);
    printf("lev1n:|%s|\n", ilsnd->lev1n);
    printf("next:%p\n", ilsnd->next);
}

//

void p_parm_node(pamv_node *pamnod) {
    printf("name:|%s|", pamnod->name);
    printf(" type:|%s|", pamnod->type);
    if (PARM_ARRAY & pamnod->attri)printf(" array:|%s|", pamnod->array);
    if (PARM_DEFAU & pamnod->attri) printf(" defau:|%s|", pamnod->defau);
    printf(" attri:|%08x|\n", pamnod->attri);
}

// 

void p_lev1id(lev1id *lev1i) {
    printf("----- p_lev1id\n");
    printf("crea_lv2pn:|%s|\n", lev1i->crea_lv2pn);
    printf("crea_lev1n:|%s|\n", lev1i->crea_lev1n);
    printf("inhe_lev1n:|%s|\n", lev1i->inhe_lev1i);
    printf("fmtsp:|%s|\n", lev1i->oivk_fmtsp_oi);
    printf("supe_lv2pn:|%s|\n", lev1i->supe_lv2pn);
}

void p_lev1_decl(lev1_decl_t *lev1d) {
    printf("----- p_lev1_decl\n");
    printf("levtyp:|%d|\n", lev1d->levtyp);
    printf("clasn_inhe:|%s|\n", lev1d->lv2pn);
    printf("ident:|%s|\n", lev1d->ident);
    printf("inne_pams:\n");
    char **innep = lev1d->innep.inne_pams;
    for (; innep[0x00]; ++innep) printf("----- innep:|%s|\n", innep[0x00]);
    printf("inne_fmtsp:|%s|\n", lev1d->innep.inne_fmtsp);
}

//

void p_lev1_conte(lv1_cont *l1lsnd) {
    printf("lev1n:|%s|\n", l1lsnd->lev1n);
    printf("fmtsp:|%s|\n", l1lsnd->oivk_fmtsp_oc);
    printf("conte:|%s|\n", l1lsnd->conte);
}

//

static void p_lv2p_prop_oi(lv2p_prop *lv2nod) {
    printf("---------------\n");
    printf("attri:%08X\n", lv2nod->access);
    printf("name:|%s|\n", lv2nod->name);
    printf("type:|%d|\n", lv2nod->potyp);
    printf("decla:|%s|\n", lv2nod->decla);
}

static void p_lev1_decl_oi(lev1_decl_i *lev1d) {
    printf("----- p_lev1_decl\n");
    printf("levtyp:|%d|\n", lev1d->levtyp);
    printf("lv2pn:|%s|\n", lev1d->lv2pn);
    printf("inhe_lv2n:\n");
    char (*ilv2np)[LVTN_LENGTH] = lev1d->inhe_lv2n;
    unsigned int inde = 0x00;
    for (; (*ilv2np)[0x00]; ++inde, ++ilv2np) {
        printf("----- ilv2np:|%s|, inde:%d\n", ilv2np[0x00], inde);
        if (0x08 < inde) break;
    }
    printf("ident:|%s|\n", lev1d->ident);
    printf("inne_pams:\n");
    char (*innep)[PARAM_LENGTH] = lev1d->innep.inne_pams;
    inde = 0x00;
    for (; (*innep)[0x00]; ++inde, ++innep) {
        printf("----- innep:|%s|, inde:%d\n", innep[0x00], inde);
        if (0x08 < inde) break;
    }
    printf("inne_fmtsp:|%s|\n", lev1d->innep.inne_fmtsp);
}

void p_lv2p_expa_i(lv2p_expa_i *lv2expi) {
    printf("p_lv2p_expa_i\n");
    printf("lv2expi->lv2o_coun:|%d|\n", lv2expi->lv2o_coun);
    lv2p_prop *lv2nod = lv2expi->lv2nod;
    unsigned int inde = 0x00;
    for (; ACCE_COTRL_INVAL != lv2nod->access; ++inde, ++lv2nod) {
        printf("***** lv2nod, inde:%d\n", inde);
        p_lv2p_prop_oi(lv2nod);
        if (0x08 < inde) break;
    }
    //
    printf("lv2expi->lv1d_coun:|%d|\n", lv2expi->lv1d_coun);
    lev1_decl_i *lv1d = lv2expi->lv1dat;
    inde = 0x00;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++inde, ++lv1d) {
        printf("***** lv1d, inde:%d\n", inde);
        p_lev1_decl_oi(lv1d);
        if (0x08 < inde) break;
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
        char inne_fmtsp[PAMTYP_LENGTH]; //  meth binding param type
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

void p_io_lv2p_expa_t(lv2p_expa_t *lv2expt) {
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
