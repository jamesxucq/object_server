#include "stdio.h"

#include "commo_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"

#include "prep_signed.h"
#include "prep_sequen.h"
#include "prep_conver.h"

#include "prepr_synta_conte.h"

//

int prepr_synta_tree(oper_node *synt_head) {
    OSEVPF("[FUNC]:reduce_uplus_uminus.\n");
    if (reduce_uplus_uminus(synt_head))
        return -1;
    OSEVPF("adjust_syntax_sequen.\n");
    if (adjust_syntax_sequen(synt_head))
        return -1;
    OSEVPF("metho_data_conve.\n");
    if (metho_data_conve(synt_head))
        return -1;
    //
    return 0x00;
}