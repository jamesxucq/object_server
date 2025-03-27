
#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "execu_excep.h"


//

int hand_searo_excep_ensi(plan_node_ensi *quer_tok, plan_node_ensi *resupn, physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha) {
    OSEVPF("[FUNC]:hand_searo_excep_ensi\n");
    switch (ACTI_CODE(quer_tok->acti_oper)) {
        case INIT_QUERY_ACCO:
            break;
        case FINAL_QUDRY_ACCO:
            if (resupn->resul_set) {
                fclose(resupn->resul_set);
                resupn->resul_set = NULL;
            }
            break;
        case OPEN_CONTE_ACCO:
            hand_close_conte_ensi(phys_cont, rivcon, stora_ha);
            break;
        case CLOSE_CONTE_ACCO:
            break;
        case RESUL_SET_ACCO:
        case METHO_SET_ACCO:
        case OPERA_SET_ACCO:
            hand_close_conte_ensi(phys_cont, rivcon, stora_ha);
            if (resupn->resul_set) {
                fclose(resupn->resul_set);
                resupn->resul_set = NULL;
            }
            break;
    }
    //
    return 0x00;
}

int hand_searo_excep_enco(plan_node_enco *quer_tok, plan_node_enco *resupn, physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha) {
    OSEVPF("[FUNC]:hand_searo_excep_enco\n");
    switch (ACTI_CODE(quer_tok->acti_oper)) {
        case INIT_QUERY_ACCO:
            break;
        case FINAL_QUDRY_ACCO:
            if (resupn->resul_set) {
                fclose(resupn->resul_set);
                resupn->resul_set = NULL;
            }
            break;
        case OPEN_CONTE_ACCO:
            hand_close_conte_enco(phys_cont, rivcon, stora_ha);
            break;
        case CLOSE_CONTE_ACCO:
            break;
        case RESUL_SET_ACCO:
        case METHO_SET_ACCO:
        case OPERA_SET_ACCO:
            hand_close_conte_enco(phys_cont, rivcon, stora_ha);
            if (resupn->resul_set) {
                fclose(resupn->resul_set);
                resupn->resul_set = NULL;
            }
            break;
    }
    //
    return 0x00;
}

//

int hand_searq_excep_ensi(plan_node_ensi *quer_tok, plan_node_ensi *resupn, physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha) {
    OSEVPF("[FUNC]:hand_searq_excep_nosi\n");
    switch (ACTI_CODE(quer_tok->acti_oper)) {
        case INIT_QUERY_ACCO:
            break;
        case FINAL_QUDRY_ACCO:
            if (resupn->resul_set) {
                fclose(resupn->resul_set);
                resupn->resul_set = NULL;
            }
            break;
        case OPEN_CONTE_ACCO:
            hand_close_conte_ensi(phys_cont, rivcon, stora_ha);
            break;
        case CLOSE_CONTE_ACCO:
            break;
        case RESUL_SET_ACCO:
        case METHO_SET_ACCO:
        case OPERA_SET_ACCO:
            hand_close_conte_ensi(phys_cont, rivcon, stora_ha);
            if (resupn->resul_set) {
                fclose(resupn->resul_set);
                resupn->resul_set = NULL;
            }
            break;
    }
    //
    return 0x00;
}

//

int hand_searq_excep_enco(plan_node_enco *quer_tok, plan_node_enco *resupn, physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha) {
    OSEVPF("[FUNC]:hand_searq_excep_noco\n");
    switch (ACTI_CODE(quer_tok->acti_oper)) {
        case INIT_QUERY_ACCO:
            break;
        case FINAL_QUDRY_ACCO:
            if (resupn->resul_set) {
                fclose(resupn->resul_set);
                resupn->resul_set = NULL;
            }
            break;
        case OPEN_CONTE_ACCO:
            hand_close_conte_enco(phys_cont, rivcon, stora_ha);
            break;
        case CLOSE_CONTE_ACCO:
            break;
        case RESUL_SET_ACCO:
        case METHO_SET_ACCO:
        case OPERA_SET_ACCO:
            hand_close_conte_enco(phys_cont, rivcon, stora_ha);
            if (resupn->resul_set) {
                fclose(resupn->resul_set);
                resupn->resul_set = NULL;
            }
            break;
    }
    //
    return 0x00;
}

//

int hand_invoko_excep(plan_node_ensi *quer_tok, plan_node_ensi *resupn, physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha) {
    OSEVPF("[FUNC]:hand_invoko_excep\n");
    switch (ACTI_CODE(quer_tok->acti_oper)) {
        case INIT_QUERY_ACCO:
            break;
        case FINAL_QUDRY_ACCO:
            hand_close_conte_ensi(phys_cont, rivcon, stora_ha);
            if (resupn->resul_set) {
                fclose(resupn->resul_set);
                resupn->resul_set = NULL;
            }
            break;
        case OPEN_CONTE_ACCO:
            hand_close_conte_ensi(phys_cont, rivcon, stora_ha);
            break;
        case CLOSE_CONTE_ACCO:
            break;
        case RESUL_SET_ACCO:
        case METHO_SET_ACCO:
        case OPERA_SET_ACCO:
            hand_close_conte_ensi(phys_cont, rivcon, stora_ha);
            if (resupn->resul_set) {
                fclose(resupn->resul_set);
                resupn->resul_set = NULL;
            }
            break;
    }
    //
    return 0x00;
}

//

int hand_dropo_excep(plan_node_ensi *quer_tok, plan_node_ensi *resupn, physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha) {
    OSEVPF("[FUNC]:hand_dropo_excep\n");
    switch (ACTI_CODE(quer_tok->acti_oper)) {
        case INIT_QUERY_ACCO:
            break;
        case FINAL_QUDRY_ACCO:
            hand_close_conte_ensi(phys_cont, rivcon, stora_ha);
            if (resupn->resul_set) {
                fclose(resupn->resul_set);
                resupn->resul_set = NULL;
            }
            break;
        case OPEN_CONTE_ACCO:
            hand_close_conte_ensi(phys_cont, rivcon, stora_ha);
            break;
        case CLOSE_CONTE_ACCO:
            break;
        case RESUL_SET_ACCO:
        case METHO_SET_ACCO:
        case OPERA_SET_ACCO:
            hand_close_conte_ensi(phys_cont, rivcon, stora_ha);
            if (resupn->resul_set) {
                fclose(resupn->resul_set);
                resupn->resul_set = NULL;
            }
            break;
    }
    //
    return 0x00;
}

//

int hand_facto_excep_ensi(plan_node_ensi *quer_tok, plan_node_ensi *resupn, physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha) {
    OSEVPF("[FUNC]:hand_facto_excep_nosi\n");
    switch (ACTI_CODE(quer_tok->acti_oper)) {
        case INIT_QUERY_ACCO:
            break;
        case FINAL_QUDRY_ACCO:
            if (resupn->resul_set) {
                fclose(resupn->resul_set);
                resupn->resul_set = NULL;
            }
            break;
        case OPEN_CONTE_ACCO:
            hand_close_conte_ensi(phys_cont, rivcon, stora_ha);
            break;
        case CLOSE_CONTE_ACCO:
            break;
        case RESUL_SET_ACCO:
        case METHO_SET_ACCO:
        case OPERA_SET_ACCO:
            hand_close_conte_ensi(phys_cont, rivcon, stora_ha);
            if (resupn->resul_set) {
                fclose(resupn->resul_set);
                resupn->resul_set = NULL;
            }
            break;
    }
    //
    return 0x00;
}

//

int hand_facto_excep_enco(plan_node_enco *quer_tok, plan_node_enco *resupn, physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha) {
    OSEVPF("[FUNC]:hand_facto_excep_nosi\n");
    switch (ACTI_CODE(quer_tok->acti_oper)) {
        case INIT_QUERY_ACCO:
            break;
        case FINAL_QUDRY_ACCO:
            if (resupn->resul_set) {
                fclose(resupn->resul_set);
                resupn->resul_set = NULL;
            }
            break;
        case OPEN_CONTE_ACCO:
            hand_close_conte_enco(phys_cont, rivcon, stora_ha);
            break;
        case CLOSE_CONTE_ACCO:
            break;
        case RESUL_SET_ACCO:
        case METHO_SET_ACCO:
        case OPERA_SET_ACCO:
            hand_close_conte_enco(phys_cont, rivcon, stora_ha);
            if (resupn->resul_set) {
                fclose(resupn->resul_set);
                resupn->resul_set = NULL;
            }
            break;
    }
    //
    return 0x00;
}


