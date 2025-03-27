#include "commo_header.h"

#include "liv_list.h"

//

liv_list *appe_live_list(liv_list **llsth, void *liv_data, int liv_len) {
    // OSEVPF("[FUNC]:appe_live_list\n");
    liv_list *llsnd = (liv_list *) malloc(sizeof (liv_list));
    if (!llsnd) return NULL;
    //
    llsnd->liv_data = malloc(liv_len);
    if (!llsnd->liv_data) {
        free(llsnd);
        return NULL;
    }
    memcpy(llsnd->liv_data, liv_data, liv_len);
    //
    LL_APPEND(*llsth, llsnd);
    return llsnd;
}

liv_list *addi_live_list(liv_list **llsth, int liv_len) {
    liv_list *llsnd = (liv_list *) malloc(sizeof (liv_list));
    if (!llsnd) return NULL;
    //
    llsnd->liv_data = malloc(liv_len);
    if (!llsnd->liv_data) {
        free(llsnd);
        return NULL;
    }
    //
    LL_APPEND(*llsth, llsnd);
    return llsnd;
}


