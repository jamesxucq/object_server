#include <stdlib.h>
#include <string.h>

#include "parms_style.h"

#include "cont_list.h"
#include "debug_funct_osv.h"

//

cont_list *appe_cont_list(cont_list **clsth) {
    // OSEVPF("[FUNC]:appe_cont_list\n");
    cont_list *clsnd = (cont_list *) malloc(sizeof (cont_list));
    if (!clsnd) return NULL;
    //
    clsnd->contp = (contain *) malloc(sizeof (contain));
    if (!clsnd->contp) {
        free(clsnd);
        return NULL;
    }
    //
    LL_APPEND((*clsth), clsnd)
    return clsnd;
}

//

contain *appe_clist_cont(cont_list **clsth) {
    // OSEVPF("[FUNC]:appe_clist_cont\n");
    cont_list *clsnd = (cont_list *) malloc(sizeof (cont_list));
    if (!clsnd) return NULL;
    //
    clsnd->contp = (contain *) malloc(sizeof (contain));
    if (!clsnd->contp) {
        free(clsnd);
        return NULL;
    }
    //
    LL_APPEND((*clsth), clsnd)
    return clsnd->contp;
}