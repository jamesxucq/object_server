
#include "commo_header.h"
#include "kcomm_header.h"
#include "ostri_utili.h"
#include "lv2p_meta/lv2me_ite.h"
#include "lv2p_decla.h"

#include "inher_utili.h"
#include "filli_clang.h"
#include "lev1_utili.h"
#include "debug_funct_oi.h"

//

int merge_lv2p_prop(lv2p_prop *l2_nod, lv2p_prop *lv2nod) {
    OSEVPF("[FUNC]:merge_lv2p_prop\n");
    // PRIN_lv2p_prop_array(l2_nod);
    lv2p_prop *l2nod2;
    lv2p_prop *l2nod1 = lv2nod;
    for (; ACCE_COTRL_INVAL != l2nod1->access; ++l2nod1) {
        l2nod2 = find_lv2p_prop(l2_nod, l2nod1);
        if (l2nod2) {
            // OSEVPF("found name:|%s|\n", l2nod1->name);
            MK_ZERO(l2nod1->name);
        }
    }
    //
    unsigned int inde = 0x00;
    for (l2nod2 = l2_nod; ACCE_COTRL_INVAL != l2nod2->access; ++inde, ++l2nod2);
    for (l2nod1 = lv2nod; (ACCE_COTRL_INVAL != l2nod1->access) && (LVTNOD_COUNT > inde); ++inde, ++l2nod1) {
        // OSEVPF("name:|%s|\n", l2nod1->name);
        if (NOT_ZERO(l2nod1->name)) {
            l2nod2->access = l2nod1->access;
            strcpy(l2nod2->name, l2nod1->name);
            l2nod2->potyp = l2nod1->potyp;
            strcpy(l2nod2->decla, l2nod1->decla);
            ++l2nod2;
        }
    }
    l2nod2->access = ACCE_COTRL_INVAL;
    // PRIN_lv2p_prop_array(l2_nod);
    return 0x00;
}

//

int chk_inher_type(char *lv2_dec, char *lev1n) {
    lv2p_decl_t lv2dt;
    if (parse_lv2pd_decla(&lv2dt, lv2_dec))
        return -1;
    //
    lev1_decl_t *lv1d = lv2dt.meth;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        if (!strcmp(lev1n, lv1d->ident)) {
            if (IS_ZERO(lv1d->innep.inne_fmtsp))
                return INHER_TYPE_WHOLE;
            return INHER_TYPE_BINDI;
        }
    }
    //
    return -1;
}

//
#define FIND_LTNOD_NONE(NOVAL, ARRAY, NAME) { \
    lv2p_prop *l2_nod = ARRAY; \
    for(; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod) \
        if(!strcmp(NAME, l2_nod->name)) break; \
    memcpy(NOVAL, l2_nod, sizeof(lv2p_prop)); \
}

int parse_lev1d_bindi(lv2p_prop *clnod, char *lv2_dec, char *lev1n) {
    OSEVPF("[FUNC]:parse_lev1d_bindi\n");
    lv2p_decl_t lv2dt;
    if (parse_lv2pd_decla(&lv2dt, lv2_dec))
        return -1;
    lev1_decl_t *lv1d = lv2dt.meth;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        if (!strcmp(lev1n, lv1d->ident) && NOT_ZERO(lv1d->innep.inne_fmtsp))
            break;
    }
    if (LVTP_TYPE_NONE == lv1d->levtyp)
        return -1;
    //
    lv2p_prop *lv2nod = clnod;
    char **pamvp = lv1d->innep.inne_pams;
    for (; pamvp[0x00]; ++pamvp, ++lv2nod) {
        FIND_LTNOD_NONE(lv2nod, lv2dt.lv2nod, pamvp[0x00]);
        // PRIN_lv2p_prop(lv2nod);
    }
    lv2nod->access = ACCE_COTRL_INVAL;
    //
    return 0x00;
}

//

lev1_decl_t *parse_lev1d_lev1n(lev1_decl_t *lev1d, char *lv2_dec, char *lev1n) {
    OSEVPF("[FUNC]:parse_lev1d_bindi\n");
    lv2p_decl_t lv2dt;
    if (parse_lv2pd_decla(&lv2dt, lv2_dec))
        return NULL;
    lev1_decl_t *lv1d = lv2dt.meth;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        if (!strcmp(lev1n, lv1d->ident) && NOT_ZERO(lv1d->innep.inne_fmtsp))
            break;
    }
    if (LVTP_TYPE_NONE == lv1d->levtyp)
        return NULL;
    // memcpy(lev1d, lv1d, sizeof (lev1_decl_t));
    dupl_lev1_decl(lev1d, lv1d);
    (++lev1d)->levtyp = LVTP_TYPE_NONE;
    return lev1d;
}

//

int filli_ilev1_fmtsd(OUT char *fmtsd, char *basen, char *rlv2pn, char *lev1n) {
    OSEVPF("[FUNC]:filli_ilev1_fmtsd\n");
    OSEVPF("rlv2pn:|%s| lev1n:|%s|\n", rlv2pn, lev1n);
    //
    char lv2_dec[LARGE_TEXT_SIZE];
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, rlv2pn);
    if (!split_l2dec_ite(lv2_dec, lv2d_path))
        return -1;
    //
    lv2p_prop clnod[LVTNOD_COUNT];
    if (parse_lev1d_bindi(clnod, lv2_dec, lev1n))
        return -1;
    if (ilev1_pamvu_type(fmtsd, clnod))
        return -1;
    //
    OSEVPF("END fmtsd:|%s|\n", fmtsd);
    return 0x00;
}

//

int regis_inher_meth(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, char *regi_clas, char *lev1n) {
    OSEVPF("[FUNC]:regis_inher_meth\n");
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    if (find_inher_levo(lv2ai->inher_list, LVTP_INHE_METH, regi_clas, lev1n))
        return 0x00;
    if (!addi_inhe_meth(&lv2ai->inher_list, regi_clas, lev1n))
        return -1;
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2pn);
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

int regis_inher_lev1(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, char *regi_clas, char *lev1n) {
    OSEVPF("[FUNC]:regis_inher_lev1\n");
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    if (find_inher_levo(lv2ai->inher_list, LVTP_INHE_LEVO, regi_clas, lev1n))
        return 0x00;
    if (!addi_inhe_lev1(&lv2ai->inher_list, regi_clas, lev1n))
        return -1;
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2pn);
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

int regis_inher_lv2p(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, char *regi_clas) {
    OSEVPF("[FUNC]:regis_inher_lv2p\n");
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    if (find_inher_lvtp(lv2ai->inher_list, LVTP_INHE_LVTP, regi_clas))
        return 0x00;
    if (!addi_inhe_lv2p(&lv2ai->inher_list, regi_clas))
        return -1;
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2pn);
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

int regis_inher_clas(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, char *regi_clas) {
    OSEVPF("[FUNC]:regis_inher_clas\n");
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    if (find_inher_lvtp(lv2ai->inher_list, LVTP_INHE_CLAS, regi_clas))
        return 0x00;
    if (!addi_inhe_clas(&lv2ai->inher_list, regi_clas))
        return -1;
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2pn);
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

//

lev1_meta *parse_metho_decla(lev1_meta *lev1m, char *basen, inherit * innod) {
    lv1_cont *l1con_list = NULL;
    if (build_l2meth_ite(&l1con_list, basen, innod->lv2pn))
        return NULL;
    lv1_cont *l1c_nod = find_l1cnod_name(l1con_list, innod->lev1n);
    if (!l1c_nod) {
        l1clst_dele(l1con_list);
        return NULL;
    }
    if (parse_metho_conte(lev1m, l1c_nod->conte)) {
        l1clst_dele(l1con_list);
        return NULL;
    }
    //
    l1clst_dele(l1con_list);
    return lev1m;
}

//

int valid_imeth_legal(char *basen, lev1_decl_t *lev1d) {
    OSEVPF("[FUNC]:valid_imeth_legal\n");
    lev1_decl_t ilev1d[LEVO_COUNT];
    if (build_lev1d_clasn(ilev1d, basen, last_lv2pn(lev1d->inhe_lv2n)))
        return -1;
    //
    lev1_decl_t *lv1d = ilev1d;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        if (((LVTP_NORM_METH | LVTP_INHE_METH) & lv1d->levtyp)
                && !strcmp(lev1d->ident, lv1d->ident)
                && !strcmp(lev1d->innep.inne_fmtsp, lv1d->innep.inne_fmtsp))
            return 0x00;
        else if (((LVTP_INHE_LEVO | LVTP_INHE_LVTP) & lv1d->levtyp)
                && !strcmp(lev1d->ident, lv1d->ident))
            return 0x00;
    }
    //
    return -1;
}

int valid_ilev1_legal(char *basen, lev1_decl_t *lev1d) {
    OSEVPF("[FUNC]:valid_ilev1_legal\n");
    lev1_decl_t ilev1d[LEVO_COUNT];
    if (build_lev1d_clasn(ilev1d, basen, last_lv2pn(lev1d->inhe_lv2n)))
        return -1;
    //
    lev1_decl_t *lv1d = ilev1d;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        if (((LVTP_NORM_METH | LVTP_INHE_METH | LVTP_INHE_LEVO | LVTP_INHE_LVTP) & lv1d->levtyp)
                && !strcmp(lev1d->ident, lv1d->ident))
            return 0x00;
    }
    //
    return -1;
}

int valid_ilv2p_legal(char *basen, lev1_decl_t *lev1d) {
    OSEVPF("[FUNC]:valid_ilv2p_legal\n");
    lev1_decl_t ilev1d[LEVO_COUNT];
    if (build_lev1d_clasn(ilev1d, basen, lev1d->ident))
        return -1;
    //
    lev1_decl_t *lv1d = ilev1d;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        if ((LVTP_INHE_LVTP & lv1d->levtyp) && !strcmp(lev1d->ident, lv1d->ident))
            return 0x00;
    }
    //
    return -1;
}

int valid_iclas_legal(char *basen, lev1_decl_t *lev1d) {
    OSEVPF("[FUNC]:valid_iclas_legal\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, last_lv2pn(lev1d->inhe_lv2n));
    if (!CLASS_EXIST(lv2d_path))
        return 0x00;
    return -1;
}

//

int clear_inher_meth(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, char *clea_lv2p, char *lev1n) {
    OSEVPF("[FUNC]:clear_inher_meth\n");
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    inherit * innod = dele_inhe_meth(&lv2ai->inher_list, clea_lv2p, lev1n);
    if (!innod) return 0x00;
    IMETH_DELET(innod);
    //
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2pn);
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

int clear_inher_lev1(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, char *clea_lv2p, char *lev1n) {
    OSEVPF("[FUNC]:clear_inher_lev1\n");
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    inherit * innod = dele_inhe_lev1(&lv2ai->inher_list, clea_lv2p, lev1n);
    if (!innod) return 0x00;
    IMETH_DELET(innod);
    //
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2pn);
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

int clear_inher_lv2p(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, char *clea_lv2p) {
    OSEVPF("[FUNC]:clear_inher_lv2p\n");
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    inherit * innod = dele_inhe_lv2p(&lv2ai->inher_list, clea_lv2p);
    if (!innod) return 0x00;
    IMETH_DELET(innod);
    //
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2pn);
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

int clear_inher_clas(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, char *clea_lv2p) {
    OSEVPF("[FUNC]:clear_inher_clas\n");
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    inherit * innod = dele_inhe_clas(&lv2ai->inher_list, clea_lv2p);
    if (!innod) return 0x00;
    IMETH_DELET(innod);
    //
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2pn);
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

//

int find_super_lv2pn(OUT char *supe_lv2pn, char *basen, lev1_decl_t *lev1d) {
    OSEVPF("[FUNC]:find_super_lv2pn\n");
    lev1_decl_t *lv1d = lev1d;
    lev1_decl_t ilev1d[LEVO_COUNT];
    // unsigned int inde = 0x00;
    while (lv1d->inhe_lv2n[0x00]) {
        // OSEVPF("%d lv1d->inhe_lv2n[0x00]:|%s|\n", inde, lv1d->inhe_lv2n[0x00]);
        if (parse_lev1d_clasn(ilev1d, basen, lv1d->inhe_lv2n[0x00]))
            return -1;
        lv1d = find_lev1d_lv1n(ilev1d, lv1d->ident);
        if (!lv1d) return -1;
        // OSEVPF("%d lv1d->inhe_lv2n[0x00]:|%s|\n", inde, lv1d->inhe_lv2n[0x00]); ++inde;
    }
    //
    strcpy(supe_lv2pn, lv1d->lv2pn);
    return 0x00;
}
