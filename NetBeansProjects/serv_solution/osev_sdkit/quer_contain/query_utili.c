
#include "commo_header.h"
#include "kcomm_header.h"
#include "seion_struct.h"

#include "query_utili.h"
//

int inser_conta_list(cont_lsmp *conda_stm, cont_list *clist) {
    fprintf(stdout, "[FUNC]:inser_conta_list\n");
    cont_list *clsnd = clist;
    while (clsnd) {
        fprintf(stdout, "inser_conta:%s\n", clsnd->contp->cont_name);
        // PRIN_osv_oid_t_stri(&clsnd->contp->cont_obid);
        conta_cache_insert(conda_stm, clsnd->contp);
        // if (clsnd->contp->contype) PRIN_osv_oid_t_stri(&clsnd->contp->refe_cont[0x00]);
        clsnd = clsnd->next;
    }
    conda_stm->clist = clist;
    // fprintf(stdout, "[FUNC]:end inser_conta_list\n");
    return 0x00;
}

//

unsigned int parse_source_contn(contain **sconp, unsigned int *cont_type, cont_lsmp *conda_stm, char *src_name) {
    OSEVPF("[FUNC]:parse_source_contn, src_name:|%s|\n", src_name);
    cont_type[0x00] = INVAL_CONTA_TYPE;
    char qconta[SCONT_CONUT_ZTAI][CONTA_LENGTH];
    unsigned int cont_coun = query_source_conta(qconta, src_name);
    if (MAX_SCONT_COUNT < cont_coun) {
        sconp[0x00] = NULL;
        return 0x00;
    }
    //
    char (*qcont)[CONTA_LENGTH] = qconta;
    unsigned int inde = 0x00;
    for (; (cont_coun > inde) && (*qcont)[0x00]; ++inde, ++sconp, ++qcont) {
        sconp[0x00] = (contain *) cache_value(qcont[0x00], conda_stm->lev3n_hm);
        if (!sconp[0x00]) return 0x00;
        OSEVPF("(*sconp)->cont_name:|%s|\n", (*sconp)->cont_name);
        if (sconp[0x00]->contype) {
            cont_type[0x00] |= REFER_CONTA_TYPE;
        } else cont_type[0x00] |= ENTIT_CONTA_TYPE;
    }
    sconp[0x00] = NULL;
    OSEVPF("parse_source_contn end.....\n");
    return cont_coun;
}

unsigned int parse_source_conto(contain **sconp, unsigned int *cont_type, cont_lsmp *conda_stm, osv_oid_t *src_obid, unsigned long long src_len) {
    OSEVPF("[FUNC]:parse_source_conto\n");
    cont_type[0x00] = INVAL_CONTA_TYPE;
    unsigned int cont_coun = src_len / OBJE_IDENTI_BLEN;
    if (MAX_SCONT_COUNT < cont_coun) {
        sconp[0x00] = NULL;
        return 0x00;
    }
    //
    unsigned int inde = 0x00;
    for (; cont_coun > inde; ++inde, ++src_obid) {
        sconp[0x00] = (contain *) cache_value(src_obid, conda_stm->lev3o_hm);
        if (!sconp[0x00]) return 0x00;
        // OSEVPF("(*sconp)->cont_name:|%s|\n", (*sconp)->cont_name);
        if (sconp[0x00]->contype) {
            cont_type[0x00] |= REFER_CONTA_TYPE;
        } else cont_type[0x00] |= ENTIT_CONTA_TYPE;
    }
    sconp[0x00] = NULL;
    OSEVPF("parse_source_contn end.....\n");
    return cont_coun;
}

//

int parse_refere_conta(contain **rconp, cont_lsmp *conda_stm, cont_versi *rcove, int rcoun) {
    OSEVPF("[FUNC]:parse_refere_conta\n");
    unsigned int inde = 0x00;
    for (; rcoun > inde; ++inde, ++rconp, ++rcove) {
        PRIN_osv_oid_t_stri(&rcove->lv4p_obid);
        rconp[0x00] = (contain *) cache_value(&rcove->lv4p_obid, conda_stm->lev3o_hm);
        if (!rconp[0x00]) return -1;
    }
    rconp[0x00] = NULL;
    //
    return 0x00;
}

//

int check_refer_obid(unsigned char pamtyp, char *pamvu) {
    osv_oid_i *obje_obid = (osv_oid_i *) pamvu;
    if (DATY_OBID == pamtyp) {
        if (INSTAN_UNIQUE != obje_obid->osev_unique)
            return 0x00;
    }
    //
    return -1;
}

//




