
#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "debug_funct/debug_funct_qc.h"
#include "lv2p_expand.h"

void p_plan_node_ensi(plan_node_ensi *quer_tok) {
    for (; quer_tok->acti_oper; ++quer_tok) {
        printf("acti_oper:%08X cont_name:|%s|  source_str:|%s|\n", quer_tok->acti_oper, quer_tok->cont_name, quer_tok->source_str);
    }
}
//

void p_plan_node_enco(plan_node_enco *quer_tok) {
    for (; quer_tok->acti_oper; ++quer_tok) {
        printf("acti_oper:%08X cont_name:|%s|  source_str:|%s|\n", quer_tok->acti_oper, quer_tok->cont_name, quer_tok->source_str);
    }
}

//

void p_plan_node_resi(plan_node_ensi *quer_tok) {
    for (; quer_tok->acti_oper; ++quer_tok) {
        printf("acti_oper:%08X cont_name:|%s|  source_str:|%s|\n", quer_tok->acti_oper, quer_tok->cont_name, quer_tok->source_str);
    }
}

//

void p_plan_node_reco(plan_node_enco *quer_tok) {
    for (; quer_tok->acti_oper; ++quer_tok) {
        printf("acti_oper:%08X cont_name:|%s|  source_str:|%s|\n", quer_tok->acti_oper, quer_tok->cont_name, quer_tok->source_str);
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

void p_lv2p_expa_t(lv2p_expa_t *lv2expt) {
    printf("p_lv2p_expa_t\n");
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

/*
    struct _contain_ {
        osv_oid_t cont_obid;
        char cont_name[CONTA_LENGTH];
        int contype; // 0x00:normal conta, 0x01:static referen , 0x02:dynamic referen
        char base_name[BASE_LENGTH];
        osv_oid_t lv2p_type;
        //
        int refe_coun; // 0: is normal !=0: is referen contain, max is 4 referen
        unsigned long long versio; // 0x00:disable >0x00:is version // virtual
        cont_versi refe_cove[RCONT_CONUT_ZTAI];
        char condition[CONDIT_LENGTH];
        //
        rive_ha *stora_ha;
    };

    typedef struct _contain_ contain;
 */
void p_contain(contain *contp) {
    printf("p_contain\n");
    printf("contp->cont_name:|%s|\n", contp->cont_name);
    printf("contp->contype:|%d|\n", contp->contype);
    printf("contp->refe_coun:|%d|\n", contp->refe_coun);
}

