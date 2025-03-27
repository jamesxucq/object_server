#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "commo_header.h"
#include "lexic/valtok.h"
#include "synta_tree.h"

#include "exptoke.h"
#include "gramm_analy.h"

#include "debug_funct_cq.h"

//

static void pastat_initi(pastat *state, char *erro_msg) {
    memset(state, '\0', sizeof (pastat));
    state->accept = PARSE_FAULT;
    state->erro_msg = erro_msg;
}


//
#include "expre_analy.h"
#include "expre_analy.c"

//

int gramm_analy_synta(char *erro_msg, oper_node **synt_head, valu_toke *vtsta) {
    pastat state;
    void *pParser;
    //
    pastat_initi(&state, erro_msg);
    pParser = ExpreParseAlloc(malloc);
    //
    OSEVPF("ExpreParse start.....\n");
    valu_toke *valtok = vtsta;
    unsigned int inde = 0x00;
    for (; STACK_SIZE > inde; ++inde, ++valtok) {
        OSEVPF("kind:|%u|", valtok->vtok_kind);
        if (INVA_TOKE == valtok->vtok_kind) break;
        OSEVPF("str:|%s|\n", valtok->stri_valu);
        ExpreParse(pParser, valtok->vtok_kind, valtok, &state);
    }
    ExpreParse(pParser, 0x00, 0x00, &state);
    OSEVPF("ExpreParse end.....\n");
    ExpreParseFree(pParser, free);
    //
    if (PARSE_FAULT == state.accept) {
        DESTROY_STREE(state.synt_head);
        return -1;
    }
    // 
    OSEVPF("exit gramm_analy_synta\n");
    *synt_head = state.synt_head;
    // PRIN_state(&state);
    return 0x00;
}