
#include "loop_memo.h"

void free_loop(loop_memo_t *loop_memp) {
    // OSEVPF("[FUNC]:free_loop\n");
    if (loop_memp->dest) free(loop_memp->dest);
    if (loop_memp->data) {
        if (loop_memp->strzp[0x00]) {
            strz_t **strzp = loop_memp->strzp;
            for (; strzp[0x00]; ++strzp) {
                if (STRZ_TYPE_USER & (strzp[0x00])->type) {
                    if ((strzp[0x00])->data)
                        free((strzp[0x00])->data);
                }
            }
        }
        free(loop_memp->data);
    }
}