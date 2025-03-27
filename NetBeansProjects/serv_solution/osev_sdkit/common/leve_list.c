
#include "commo_header.h"
#include "kcomm_header.h"

#include "invok_bzl.h"

#include "leve_list.h"
#include "debug_funct_co.h"

//
#define CLIST_APPEND(head, add) { \
    LDECLTYPE(head) _tmp; \
    if (head) { \
        _tmp = head; \
        while (_tmp->next) _tmp = _tmp->next; \
        _tmp->next = add; \
    } else head = add; \
}

lev1_list *appe_lev1_meta(lev1_list **lev1_lsth, lev1_meta *lev1m) {
    lev1_list *l1nod = (lev1_list *) malloc(sizeof (lev1_list));
    if (!l1nod) return NULL;
    memcpy(&l1nod->lev1m, lev1m, sizeof (lev1_list));
    l1nod->next = NULL;
    //
    CLIST_APPEND(*lev1_lsth, l1nod);
    return l1nod;
}

//

lev1_list *appe_lev1_list(lev1_list **lev1_lsth) {
    lev1_list *l1nod = (lev1_list *) malloc(sizeof (lev1_list));
    if (!l1nod) return NULL;
    l1nod->next = NULL;
    //
    CLIST_APPEND(*lev1_lsth, l1nod);
    return l1nod;
}

//

int lev1_list_meth(lev1_list **lev1_lsth, char *basen, char *lv2pn, char *lev1n) {
    OSEVPF("[FUNC]:destr_relom_bzl\n");
    lv1_cont *l1con_list = NULL;
    if (build_l2meth_ite(&l1con_list, basen, lv2pn))
        return -1;
    lv1_cont *l1lsnd = find_l1cnod_name(l1con_list, lev1n);
    lev1_list *l1nod;
    for (; l1lsnd; l1lsnd = find_l1cnod_name(l1lsnd->next, lev1n)) {
        l1nod = appe_lev1_list(lev1_lsth);
        if (!l1nod) {
            dele_lev1_list(lev1_lsth[0x00]);
            l1clst_dele(l1con_list);
            return -1;
        }
        if (parse_metho_conte(&l1nod->lev1m, l1lsnd->conte)) {
            dele_lev1_list(lev1_lsth[0x00]);
            l1clst_dele(l1con_list);
            return -1;
        }
        PRIN_lev1_list(l1nod);
    }
    //
    l1clst_dele(l1con_list);
    return 0x00;
}

//

int lev1_list_clas(lev1_list **lev1_lsth, char *basen, char *lv2pn) {
    lv1_cont *l1con_list = NULL;
    if (build_l2meth_ite(&l1con_list, basen, lv2pn))
        return -1;
    lv1_cont * l1lsnd = l1con_list;
    lev1_list *l1nod;
    for (; l1lsnd; l1lsnd = l1lsnd->next) {
        l1nod = appe_lev1_list(lev1_lsth);
        if (!l1nod) {
            dele_lev1_list(lev1_lsth[0x00]);
            l1clst_dele(l1con_list);
            return -1;
        }
        if (parse_metho_conte(&l1nod->lev1m, l1lsnd->conte)) {
            dele_lev1_list(lev1_lsth[0x00]);
            l1clst_dele(l1con_list);
            return -1;
        }
    }
    //
    l1clst_dele(l1con_list);
    return 0x00;
}

int lev1_list_lv2pn(lev1_list **lev1_lsth, char *basen, char *lv2pn) {
    lv1_cont *l1con_list = NULL;
    if (build_l2meth_ite(&l1con_list, basen, lv2pn))
        return -1;
    lv1_cont * l1lsnd = l1con_list;
    lev1_list *l1nod;
    for (; l1lsnd; l1lsnd = l1lsnd->next) {
        l1nod = appe_lev1_list(lev1_lsth);
        if (!l1nod) {
            dele_lev1_list(lev1_lsth[0x00]);
            l1clst_dele(l1con_list);
            return -1;
        }
        if (parse_metho_conte(&l1nod->lev1m, l1lsnd->conte)) {
            dele_lev1_list(lev1_lsth[0x00]);
            l1clst_dele(l1con_list);
            return -1;
        }
    }
    //
    l1clst_dele(l1con_list);
    return 0x00;
}

//

int lev1_list_whol(lev1_list **lev1_lsth, char *basen) {
    char *lv2p_arra[LVTP_COUNT];
    char _cline_[BUFF_32K_SIZE];
    //
    char lv2p_path[MAX_PATH * 3];
    CREAT_CLASS_DIRECTORY(lv2p_path, basen)
    if (LIST_LVTP_BZL(lv2p_arra, _cline_, lv2p_path))
        return -1;
    //
    char **lv2pnp = lv2p_arra;
    for (; lv2pnp[0x00]; ++lv2pnp) {
        OSEVPF("lv2pn:|%s|\n", lv2pnp[0x00]);
        if (lev1_list_clas(lev1_lsth, basen, lv2pnp[0x00])) {
            dele_lev1_list(lev1_lsth[0x00]);
            return -1;
        }
    }
    //
    return 0x00;
}

//

lv2p_list *appe_lv2p_list(lv2p_list **lv2p_lsth) {
    lv2p_list *l2nod = (lv2p_list *) malloc(sizeof (lv2p_list));
    if (!l2nod) return NULL;
    l2nod->next = NULL;
    //
    CLIST_APPEND(*lv2p_lsth, l2nod);
    return l2nod;
}

//

int lv2p_list_clas(lv2p_list **lv2p_lsth, char *basen, char *lv2pn) {
    lv2p_list *l2nod = appe_lv2p_list(lv2p_lsth);
    if (!l2nod) return -1;
    if (build_lv2pd_clasn(&l2nod->lv2dt, basen, lv2pn))
        return -1;
    return 0x00;
}

int lv2p_list_whol(lv2p_list **lv2p_lsth, char *basen) {
    char *lv2p_arra[LVTP_COUNT];
    char _cline_[BUFF_32K_SIZE];
    //
    char lv2p_path[MAX_PATH * 3];
    CREAT_CLASS_DIRECTORY(lv2p_path, basen)
    if (LIST_LVTP_BZL(lv2p_arra, _cline_, lv2p_path))
        return -1;
    //
    char **lv2pnp = lv2p_arra;
    for (; lv2pnp[0x00]; ++lv2pnp) {
        OSEVPF("lv2pn:|%s|\n", lv2pnp[0x00]);
        if (lv2p_list_clas(lv2p_lsth, basen, lv2pnp[0x00])) {
            dele_lv2p_list(lv2p_lsth[0x00]);
            return -1;
        }
    }
    //
    return 0x00;
}