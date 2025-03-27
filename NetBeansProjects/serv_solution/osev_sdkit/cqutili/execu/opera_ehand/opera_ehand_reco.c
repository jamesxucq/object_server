
#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "opera_ehand_enco.h"
#include "../conte_resou.h"
#include "./opera_utili/opera_utili.h"

#include "opera_ehand_resi.h"

// rsco
// OR AND

static int hand_or_rsco(plan_node_enco *querpn) {
    plan_node_enco *left_chil, *righ_chil;
    OSEVPF("[FUNC]:hand_or\n");
    //
    left_chil = querpn->left_chil;
    righ_chil = querpn->righ_chil;
    //
    OSEVPF("--- create tmpfile64.\n");
    querpn->resul_set = tmpfile64();
    if (!querpn->resul_set) {
        fclose(left_chil->resul_set);
        fclose(righ_chil->resul_set);
        return -1;
    }
    //
    if (strcmp(left_chil->cont_name, righ_chil->cont_name)) { // difference source
        if (cartesi_product_data(querpn->resul_set, left_chil->resul_set, righ_chil->resul_set)) {
            fclose(left_chil->resul_set);
            fclose(righ_chil->resul_set);
            fclose(querpn->resul_set);
            return -1;
        }
    } else { // the same source
        if (merge_data_obid(querpn->resul_set, left_chil->resul_set, righ_chil->resul_set)) {
            fclose(left_chil->resul_set);
            fclose(righ_chil->resul_set);
            fclose(querpn->resul_set);
            return -1;
        }
    }
    fclose(left_chil->resul_set);
    fclose(righ_chil->resul_set);
    //
    return 0x00;
}

static int hand_and_rsco(plan_node_enco *querpn) {
    plan_node_enco *left_chil, *righ_chil;
    OSEVPF("[FUNC]:hand_and\n");
    //
    left_chil = querpn->left_chil;
    righ_chil = querpn->righ_chil;
    //
    OSEVPF("--- create tmpfile64.\n");
    querpn->resul_set = tmpfile64();
    if (!querpn->resul_set) {
        fclose(left_chil->resul_set);
        fclose(righ_chil->resul_set);
        return -1;
    }
    // the same source
    if (shared_data_obid(querpn->resul_set, left_chil->resul_set, righ_chil->resul_set)) {
        fclose(left_chil->resul_set);
        fclose(righ_chil->resul_set);
        fclose(querpn->resul_set);
        return -1;
    }
    fclose(left_chil->resul_set);
    fclose(righ_chil->resul_set);
    //
    return 0x00;
}

//

int hand_opera_set_rsco(plan_node_enco *querpn) { // OR AND
    OSEVPF("[FUNC]:hand_opera_set_rsco\n");
    int hand_valu = 0x00;
    //
    switch (OPER_CODE(querpn->acti_oper)) {
        case OR_OPCO:
            hand_valu = hand_or_rsco(querpn);
            break;
        case AND_OPCO:
            hand_valu = hand_and_rsco(querpn);
            break;
    }
    //
    return hand_valu;
}


// rdco
// OR AND

static int hand_or_rdco(plan_node_enco *querpn) {
    plan_node_enco *left_chil, *righ_chil;
    OSEVPF("[FUNC]:hand_or\n");
    //
    left_chil = querpn->left_chil;
    righ_chil = querpn->righ_chil;
    //
    OSEVPF("--- create tmpfile64.\n");
    querpn->resul_set = tmpfile64();
    if (!querpn->resul_set) {
        fclose(left_chil->resul_set);
        fclose(righ_chil->resul_set);
        return -1;
    }
    //
    if (strcmp(left_chil->cont_name, righ_chil->cont_name)) { // difference source
        if (cartesi_product_data(querpn->resul_set, left_chil->resul_set, righ_chil->resul_set)) {
            fclose(left_chil->resul_set);
            fclose(righ_chil->resul_set);
            fclose(querpn->resul_set);
            return -1;
        }
    } else { // the same source
        if (merge_data_obid(querpn->resul_set, left_chil->resul_set, righ_chil->resul_set)) {
            fclose(left_chil->resul_set);
            fclose(righ_chil->resul_set);
            fclose(querpn->resul_set);
            return -1;
        }
    }
    fclose(left_chil->resul_set);
    fclose(righ_chil->resul_set);
    //
    return 0x00;
}

static int hand_and_rdco(plan_node_enco *querpn) {
    plan_node_enco *left_chil, *righ_chil;
    OSEVPF("[FUNC]:hand_and\n");
    //
    left_chil = querpn->left_chil;
    righ_chil = querpn->righ_chil;
    //
    OSEVPF("--- create tmpfile64.\n");
    querpn->resul_set = tmpfile64();
    if (!querpn->resul_set) {
        fclose(left_chil->resul_set);
        fclose(righ_chil->resul_set);
        return -1;
    }
    // the same source
    if (shared_data_obid(querpn->resul_set, left_chil->resul_set, righ_chil->resul_set)) {
        fclose(left_chil->resul_set);
        fclose(righ_chil->resul_set);
        fclose(querpn->resul_set);
        return -1;
    }
    fclose(left_chil->resul_set);
    fclose(righ_chil->resul_set);
    //
    return 0x00;
}

//

int hand_opera_set_rdco(plan_node_enco *querpn) { // OR AND
    OSEVPF("[FUNC]:hand_opera_set_rdco\n");
    int hand_valu = 0x00;
    //
    switch (OPER_CODE(querpn->acti_oper)) {
        case OR_OPCO:
            hand_valu = hand_or_rdco(querpn);
            break;
        case AND_OPCO:
            hand_valu = hand_and_rdco(querpn);
            break;
    }
    //
    return hand_valu;
}


