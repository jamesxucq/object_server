#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"

#include "chk_utili.h"


// odb:echo("taat_con") | kits:format(BINARY_OBID); // default: objid
// odb:echo(taat_con", "ECHO|ATTRIB|STATIS"); // todo: 20230309
// 0x00:ok -1:error 

int qecho_contn_valid(valid_cobid *vaoid, cont_lsmp *conda_stm, char *echo_cont) {
    OSEVPF("[FUNC]:qecho_contn_valid\n");
    contain *dcont = (contain *) cache_value(echo_cont, conda_stm->lev3n_hm);
    if (!dcont) return -1;
    OBID_BINARY_COPY(&vaoid->chk_obid[0x00], &dcont->cont_obid);
    vaoid->vali_numb = 0xFF;
    //
    return 0x00;
}

//

int single_conta_valid(valid_cobid *vaoid, cont_lsmp *conda_stm, char *sing_cont) {
    OSEVPF("[FUNC]:single_conta_valid\n");
    contain *dcont = (contain *) cache_value(sing_cont, conda_stm->lev3n_hm);
    if (!dcont) return -1;
    OBID_BINARY_COPY(&vaoid->chk_obid[0x00], &dcont->cont_obid);
    vaoid->vali_numb = 0xFF;
    //
    return 0x00;
}

int creat_conta_valid(valid_cobid *vaoid, osv_oid_t *base_obid) {
    OSEVPF("[FUNC]:creat_conta_valid\n");
    OBID_BINARY_COPY(&vaoid->chk_obid[0x00], base_obid);
    vaoid->vali_numb = 0xFF;
    //
    return 0x00;
}


// odb:factory("lv2pn", "conobje", "obje:numb() > 0x00");
// :factory("lv2pn", conobje", "obje:numb() > 0x00");
// :factory("lv2pn", "conobje1, conobje2", "conobje1:obje:numb() > 0x00 AND conobje2:obje:numb() > 0x00");
// :factory("lv2pn", "conobje1, conobje2", "conobje1::numb() > 0x00 AND conobje2::numb() > 0x00");
// odb:factory("lv2pn", "conobje");

int multip_conta_valid(valid_cobid *vaoid, cont_lsmp *conda_stm, char *mult_cont) {
    OSEVPF("[FUNC]:multip_conta_valid\n");
    char qconta[SCONT_CONUT_ZTAI][CONTA_LENGTH];
    unsigned int cont_coun = query_source_conta(qconta, mult_cont);
    if (!cont_coun || (MAX_SCONT_COUNT < cont_coun))
        return -1;
    //
    vaoid->vali_numb = 0x00;
    unsigned char *cont_code = vaoid->vali_code;
    contain *contp;
    osv_oid_t *cont_obid = vaoid->chk_obid;
    char (*qcont)[CONTA_LENGTH] = qconta;
    unsigned int inde = 0x00;
    for (; (cont_coun > inde) && (*qcont)[0x00]; ++inde, ++cont_obid, ++cont_code, ++qcont) {
        contp = (contain *) cache_value(qcont[0x00], conda_stm->lev3n_hm);
        if (!contp) return -1;
        //
        OBID_BINARY_COPY(cont_obid, &contp->cont_obid)
        cont_code[0x00] = 0xFF;
    }
    //
    return 0x00;
}

// odb:search("lv2pn", "conobje", "obje:numb() > 0x00");
// :search("cobje", conobje", "obje:numb() > 0x00");
// :search("cobje", "conobje1, conobje2", "conobje1:obje:numb() > 0x00 AND conobje2:obje:numb() > 0x00");
// :search("cobje", "conobje1, conobje2", "conobje1::numb() > 0x00 AND conobje2::numb() > 0x00");
// odb:search("cobje", "conobje");

int searc_conta_valid(valid_cobid *vaoid, cont_lsmp *conda_stm, char *dest_cont, char *sour_cont) {
    OSEVPF("[FUNC]:searc_conta_valid\n");
    char qconta[SCONT_CONUT_ZTAI][CONTA_LENGTH];
    unsigned int cont_coun = query_source_conta(qconta, sour_cont);
    if (!cont_coun || (MAX_SCONT_COUNT < cont_coun))
        return -1;
    //source contain
    vaoid->vali_numb = 0x00;
    unsigned char *cont_code = vaoid->vali_code;
    contain *contp;
    osv_oid_t *cont_obid = vaoid->chk_obid;
    char (*qcont)[CONTA_LENGTH] = qconta;
    unsigned int inde = 0x00;
    for (; (cont_coun > inde) && (*qcont)[0x00]; ++inde, ++cont_obid, ++cont_code, ++qcont) {
        contp = (contain *) cache_value(qcont[0x00], conda_stm->lev3n_hm);
        if (!contp) return -1;
        //
        OBID_BINARY_COPY(cont_obid, &contp->cont_obid)
        cont_code[0x00] = 0xFF;
    }
    // desti contain
    contp = (contain *) cache_value(dest_cont, conda_stm->lev3n_hm);
    if (contp) {
        OBID_BINARY_COPY(cont_obid, &contp->cont_obid)
        cont_code[0x00] = 0xFF;
    }
    //
    return 0x00;
}

//

int facto_conta_valid(valid_cobid *vaoid, cont_lsmp *conda_stm, char *dest_cont, char *sour_cont) {
    OSEVPF("[FUNC]:facto_conta_valid\n");
    char qconta[SCONT_CONUT_ZTAI][CONTA_LENGTH];
    unsigned int cont_coun = query_source_conta(qconta, sour_cont);
    if (!cont_coun || (MAX_SCONT_COUNT < cont_coun))
        return -1;
    //source contain
    vaoid->vali_numb = 0x00;
    unsigned char *cont_code = vaoid->vali_code;
    contain *contp;
    osv_oid_t *cont_obid = vaoid->chk_obid;
    char (*qcont)[CONTA_LENGTH] = qconta;
    unsigned int inde = 0x00;
    for (; (cont_coun > inde) && (*qcont)[0x00]; ++inde, ++cont_obid, ++cont_code, ++qcont) {
        contp = (contain *) cache_value(qcont[0x00], conda_stm->lev3n_hm);
        if (!contp) return -1;
        //
        OBID_BINARY_COPY(cont_obid, &contp->cont_obid)
        cont_code[0x00] = 0xFF;
    }
    // desti contain
    contp = (contain *) cache_value(dest_cont, conda_stm->lev3n_hm);
    if (contp) {
        OBID_BINARY_COPY(cont_obid, &contp->cont_obid)
        cont_code[0x00] = 0xFF;
    }
    //
    return 0x00;
}

