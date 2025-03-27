
#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "../conte_resou.h"
#include "./opera_utili/opera_utili_resi.h"
#include "./opera_utili/opera_utili_rssi.h"
#include "./opera_utili/opera_utili_rdsi.h"

#include "opera_ehand_resi.h"

// OR AND

static int hand_or_resi(plan_node_ensi *querpn) {
    plan_node_ensi *left_chil, *righ_chil;
    OSEVPF("[FUNC]:hand_or_resi\n");
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
        if (cartesi_product_data_resi(querpn->resul_set, left_chil->resul_set, righ_chil->resul_set)) {
            fclose(left_chil->resul_set);
            fclose(righ_chil->resul_set);
            fclose(querpn->resul_set);
            return -1;
        }
    } else { // the same source
        if (merge_data_obid_resi(querpn->resul_set, left_chil->resul_set, righ_chil->resul_set)) {
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

static int hand_and_resi(plan_node_ensi *querpn) {
    plan_node_ensi *left_chil, *righ_chil;
    OSEVPF("[FUNC]:hand_and_resi\n");
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
    if (shared_data_obid_resi(querpn->resul_set, left_chil->resul_set, righ_chil->resul_set)) {
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

int hand_opera_set_resi(plan_node_ensi *querpn) { // OR AND
    OSEVPF("[FUNC]:hand_opera_set_resi\n");
    int hand_valu = 0x00;
    //
    switch (OPER_CODE(querpn->acti_oper)) {
        case OR_OPCO:
            hand_valu = hand_or_resi(querpn);
            break;
        case AND_OPCO:
            hand_valu = hand_and_resi(querpn);
            break;
    }

    //
    return hand_valu;
}

//

// OR AND

static int hand_or_rssi(plan_node_ensi *querpn) {
    plan_node_ensi *left_chil, *righ_chil;
    OSEVPF("[FUNC]:hand_or_rssi\n");
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
        if (cartesi_product_data_rssi(querpn->resul_set, left_chil->resul_set, righ_chil->resul_set)) {
            fclose(left_chil->resul_set);
            fclose(righ_chil->resul_set);
            fclose(querpn->resul_set);
            return -1;
        }
    } else { // the same source
        if (merge_data_obid_rssi(querpn->resul_set, left_chil->resul_set, righ_chil->resul_set)) {
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

static int hand_and_rssi(plan_node_ensi *querpn) {
    plan_node_ensi *left_chil, *righ_chil;
    OSEVPF("[FUNC]:hand_and_rssi\n");
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
    if (shared_data_obid_rssi(querpn->resul_set, left_chil->resul_set, righ_chil->resul_set)) {
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

int hand_opera_set_rssi(plan_node_ensi *querpn) { // OR AND
    OSEVPF("[FUNC]:hand_opera_set_rssi\n");
    int hand_valu = 0x00;
    //
    switch (OPER_CODE(querpn->acti_oper)) {
        case OR_OPCO:
            hand_valu = hand_or_rssi(querpn);
            break;
        case AND_OPCO:
            hand_valu = hand_and_rssi(querpn);
            break;
    }

    //
    return hand_valu;
}

//

// OR AND

static int hand_or_rdsi(plan_node_ensi *querpn) {
    plan_node_ensi *left_chil, *righ_chil;
    OSEVPF("[FUNC]:hand_or_rdsi\n");
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
        if (cartesi_product_data_rdsi(querpn->resul_set, left_chil->resul_set, righ_chil->resul_set)) {
            fclose(left_chil->resul_set);
            fclose(righ_chil->resul_set);
            fclose(querpn->resul_set);
            return -1;
        }
    } else { // the same source
        if (merge_data_obid_rdsi(querpn->resul_set, left_chil->resul_set, righ_chil->resul_set)) {
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

static int hand_and_rdsi(plan_node_ensi *querpn) {
    plan_node_ensi *left_chil, *righ_chil;
    OSEVPF("[FUNC]:hand_and_rdsi\n");
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
    if (shared_data_obid_rdsi(querpn->resul_set, left_chil->resul_set, righ_chil->resul_set)) {
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

int hand_opera_set_rdsi(plan_node_ensi *querpn) { // OR AND
    OSEVPF("[FUNC]:hand_opera_set_rdsi\n");
    int hand_valu = 0x00;
    //
    switch (OPER_CODE(querpn->acti_oper)) {
        case OR_OPCO:
            hand_valu = hand_or_rdsi(querpn);
            break;
        case AND_OPCO:
            hand_valu = hand_and_rdsi(querpn);
            break;
    }

    //
    return hand_valu;
}

