
/* 
 * File:   close_rcont_utili.h
 * Author: James Xu
 *
 * Created on 2024.6.5, PM 2:54
 */

#ifndef CLOSE_RCONT_UTILI_H
#define CLOSE_RCONT_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    // rssi

    inline int open_stati_contai_rssi(riv_curso_t **scursp, cont_versi *rcove, rive_ha *stora_ha, stor_seio *sto_seio, lv2pme *lv2me, cont_lsmp *conda_stm) {
        OSEVPF("[FUNC]:open_stati_contai_rssi\n");
        char field_str[LVTNOD_LENGTH];
        if (field_lv2me_resi(field_str, lv2me))
            return -1;
        contain *rscop;
        unsigned int inde = 0x00;
        for (; (MAX_RSCON_COUNT > inde) && CHK_ZERO_COVE(rcove); ++inde, ++rcove, ++scursp) {
            rscop = (contain *) cache_value(&rcove->lv4p_obid, conda_stm->lev3o_hm);
            if (!rscop) return -1;
            if (stora_ha->open_curso_prop(scursp, sto_seio->seion, rscop->cont_name, field_str, "raw"))
                return -1;
        }
        scursp[0x00] = NULL;
        return 0x00;
    }

    inline int close_stati_contai_rssi(riv_curso_t **scursp, rive_ha *stora_ha) {
        unsigned int inde = 0x00;
        for (; (MAX_RSCON_COUNT > inde) && scursp[0x00]; ++inde, ++scursp) {
            stora_ha->close_curso(scursp[0x00]);
        }
        return 0x00;
    }

    // rsco

    inline int open_stati_contai_rsco(riv_curso_t **scursp, cont_versi *rcove, rive_ha *stora_ha, stor_seio *sto_seio, lv2pme *lv2me, cont_lsmp *conda_stm) {
        OSEVPF("[FUNC]:open_stati_contai_rsco\n");
        char field_str[LVTNOD_LENGTH];
        if (field_lv2me_reco(field_str, lv2me))
            return -1;
        contain *rscop;
        unsigned int inde = 0x00;
        for (; (MAX_RSCON_COUNT > inde) && CHK_ZERO_COVE(rcove); ++inde, ++rcove, ++scursp) {
            rscop = (contain *) cache_value(&rcove->lv4p_obid, conda_stm->lev3o_hm);
            if (!rscop) return -1;
            if (stora_ha->open_curso_prop(scursp, sto_seio->seion, rscop->cont_name, field_str, "raw"))
                return -1;
        }
        scursp[0x00] = NULL;
        return 0x00;
    }

    inline int close_stati_contai_rsco(riv_curso_t **scursp, rive_ha *stora_ha) {
        unsigned int inde = 0x00;
        for (; (MAX_RSCON_COUNT > inde) && scursp[0x00]; ++inde, ++scursp) {
            stora_ha->close_curso(scursp[0x00]);
        }
        return 0x00;
    }

    // rdsi

    inline int open_dynam_contai_rdsi(riv_curso_t **scursp, cont_versi *rcove, rive_ha *stora_ha, stor_seio *sto_seio, lv2pme *lv2me, cont_lsmp *conda_stm) {
        OSEVPF("[FUNC]:open_dynam_contai_rdsi\n");
        char field_str[LVTNOD_LENGTH];
        if (field_lv2me_resi(field_str, lv2me))
            return -1;
        OSEVPF("field_str:|%s|\n", field_str);
        contain *rscop;
        rscop = (contain *) cache_value(&rcove->lv4p_obid, conda_stm->lev3o_hm);
        if (!rscop) return -1;
        if (stora_ha->open_curso_prop(scursp, sto_seio->seion, rscop->cont_name, field_str, "raw"))
            return -1;
        return 0x00;
    }

    inline int close_dynam_contai_rdsi(riv_curso_t *scursp, rive_ha *stora_ha) {
        stora_ha->close_curso(scursp);
        return 0x00;
    }

    //

    inline int open_dynam_contai_rdco(riv_curso_t **scursp, cont_versi *rcove, rive_ha *stora_ha, stor_seio *sto_seio, lv2pme *lv2me, cont_lsmp *conda_stm) {
        OSEVPF("[FUNC]:open_dynam_contai_rdco\n");
        char field_str[LVTNOD_LENGTH];
        if (field_lv2me_reco(field_str, lv2me))
            return -1;
        contain *rscop;
        rscop = (contain *) cache_value(&rcove->lv4p_obid, conda_stm->lev3o_hm);
        if (!rscop) return -1;
        if (stora_ha->open_curso_prop(scursp, sto_seio->seion, rscop->cont_name, field_str, "raw"))
            return -1;
        return 0x00;
    }

    inline int close_dynam_contai_rdco(riv_curso_t *scursp, rive_ha *stora_ha) {
        stora_ha->close_curso(scursp);
        return 0x00;
    }

    //　refersh

    inline int open_refre_contai_rdsi(riv_curso_t **scursp, cont_versi *rcove, rive_ha *stora_ha, stor_seio *sto_seio, cont_lsmp *conda_stm) {
        OSEVPF("[FUNC]:open_refre_contai_rdsi\n");
        contain *rscop;
        rscop = (contain *) cache_value(&rcove->lv4p_obid, conda_stm->lev3o_hm);
        if (!rscop) return -1;
        if (stora_ha->open_curso_prop(scursp, sto_seio->seion, rscop->cont_name, "", "raw"))
            return -1;
        return 0x00;
    }

    inline int close_refre_contai_rdsi(riv_curso_t *scursp, rive_ha *stora_ha) {
        stora_ha->close_curso(scursp);
        return 0x00;
    }

    // rdco

    inline int open_refre_contai_rdco(riv_curso_t **scursp, cont_versi *rcove, rive_ha *stora_ha, stor_seio *sto_seio, cont_lsmp *conda_stm) {
        OSEVPF("[FUNC]:open_refre_contai_rdco\n");
        contain *rscop;
        unsigned int inde = 0x00;
        for (; (MAX_RSCON_COUNT > inde) && CHK_ZERO_COVE(rcove); ++inde, ++rcove, ++scursp) {
            rscop = (contain *) cache_value(&rcove->lv4p_obid, conda_stm->lev3o_hm);
            if (!rscop) return -1;
            if (stora_ha->open_curso_prop(scursp, sto_seio->seion, rscop->cont_name, "", "raw"))
                return -1;
        }
        scursp[0x00] = NULL;
        return 0x00;
    }

    inline int close_refre_contai_rdco(riv_curso_t **scursp, rive_ha *stora_ha) {
        unsigned int inde = 0x00;
        for (; (MAX_RSCON_COUNT > inde) && scursp[0x00]; ++inde, ++scursp) {
            stora_ha->close_curso(scursp[0x00]);
        }
        return 0x00;
    }


#ifdef __cplusplus
}
#endif

#endif /* CLOSE_RCONT_H */

