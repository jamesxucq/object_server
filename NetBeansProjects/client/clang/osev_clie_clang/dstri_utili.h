
#ifndef DSTR_UTILI_H
#define DSTR_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "clie_macro.h"
#include "reque_conne.h"
#include "osco_socks.h"
#include "pinvo.h"    

#include "debug_funct_clang.h"

    // trans-serve
    // SALT_LENGTH

    inline unsigned char *osev_authen_chks(unsigned char *chks_bin, char *uname, char *paswd, char *salt) {
        OSEVPF("[FUNC]:osev_authen_chks\n");
        char buffe[MID_TLENG];
        if (!paswd || !uname || !chks_bin)
            return NULL;
        sprintf(buffe, "%s:%s:%s:%s", salt, uname, paswd, salt);
        OSEVPF("authen buffe:|%s|\n", buffe);
        get_md5sum_memo(buffe, strlen(buffe), chks_bin);
        // OSEVPF("chks_bin:");
        PRIN_md5sum(chks_bin);
        return chks_bin;
    }

    // trans-serve

    inline void creat_authe_iacv(OUT unsigned char *req_valid, OUT unsigned char *salt, char *uname, char *paswd) {
        random_salt(salt);
        char salt_buff[SALT_LENGTH + 0x01];
        strzcpy(salt_buff, (char *) salt, SALT_LENGTH);
        osev_authen_chks(req_valid, uname, paswd, salt_buff);
    }

    // trans-serve

    inline unsigned long long pack_none_pamstyl(pamstyl_t *pscon) {
        OSEVPF("[FUNC]:pack_none_pamstyl\n");
        binary_entit *binen = (binary_entit *) pscon->pamstyl_memo;
        binen->notyp = DATY_BINARY;
        binen->colen = 0x00;
        pscon->colen = sizeof (binary_entit);
        //
        return pscon->colen;
    }

    // trans-serve
    // ("aa", "bb", "cc", "dd");

    inline unsigned long long pack_dstri_pamstyl(pamstyl_t *pscon, const char **pamvp) {
        unsigned long long colen = encod_stri_loop(pscon->pamstyl_memo + sizeof (binary_entit), pamvp);
        if (INVA_ULOLO_VALU == colen)
            return INVA_ULOLO_VALU;
        // OSEVPF("colen:%d pamvp[0x00]:|%s| pamvp[0x01]:|%s|\n", colen, pamvp[0x00], pamvp[0x01]);
        //
        binary_entit *binen = (binary_entit *) pscon->pamstyl_memo;
        binen->notyp = DATY_BINARY;
        binen->colen = colen;
        // OSEVPF("unpak_conte_leng, obsth->enlen:%d\n", obsth->enlen);
        pscon->colen = sizeof (binary_entit) + colen;
        return pscon->colen;
    }

    // trans-serve
    // ("aa", 11, "bb", "cc", 33, 55);

    inline unsigned long long pack_disti_pamstyl(pamstyl_t *pscon, const char **pamvp) {
        OSEVPF("[FUNC]:pack_disti_pamstyl\n");
        OSEVPF("pamvp[0x00]:|%s| pamvp[0x01]:|%s|\n", pamvp[0x00], pamvp[0x01]);
        unsigned long long colen = encod_list_loop(pscon->pamstyl_memo + sizeof (binary_entit), pamvp);
        if (INVA_ULOLO_VALU == colen)
            return INVA_ULOLO_VALU;
        //
        binary_entit *binen = (binary_entit *) pscon->pamstyl_memo;
        binen->notyp = DATY_BINARY;
        binen->colen = colen;
        pscon->colen = sizeof (binary_entit) + colen;
        OSEVPF("pscon->colen:%llu colen:%llu\n", pscon->colen, colen);
        return pscon->colen;
    }

    inline unsigned long long pack_disti_paki(pamstyl_t *pscon, const char **pamvp, char *fmtst) {
        OSEVPF("[FUNC]:pack_disti_paki\n");
        OSEVPF("pamvp[0x00]:|%s| pamvp[0x01]:|%s|\n", pamvp[0x00], pamvp[0x01]);
        unsigned long long colen = pack_list_loop(pscon->pamstyl_memo + sizeof (binary_entit), BINA_ARRAY_LEN - sizeof (binary_entit), pamvp, fmtst);
        // OSEVPF("[FUNC]:pack_disti_pamstyl encod_list_loop\n");
        if (INVA_ULOLO_VALU == colen)
            return INVA_ULOLO_VALU;
        //
        binary_entit *binen = (binary_entit *) pscon->pamstyl_memo;
        binen->notyp = DATY_BINARY;
        binen->colen = colen;
        pscon->colen = sizeof (binary_entit) + colen;
        OSEVPF("pscon->colen:%llu colen:%llu\n", pscon->colen, colen);
        return pscon->colen;
    }

    //

    inline unsigned long long pack_einvo_pamstyl(pamstyl_t *pscon, char **pamvp) {
        OSEVPF("[FUNC]:pack_einvo_pamstyl\n");
        pamstyl_t ivk_lvth;
        quote_decode(pamvp[0x00]);
        if (INVA_ULOLO_VALU == parse_invok_metho(&ivk_lvth, (char *) pamvp[0x00]))
            return INVA_ULOLO_VALU;
        char *last_str = binary_pamstyl_naked(pscon->pamstyl_memo + sizeof (binary_entit), ivk_lvth.pamstyl_memo, ivk_lvth.colen);
        //
        unsigned long long enlen = 0x00;
        if (pamvp[0x01]) {
            if (OBJE_IDENT_TYPE == pamvp[0x01][ESCA_NODTYP_PART]) {
                OSEVPF("pamvp[0x01][ESCA_NODTYP_PART]:%u\n", pamvp[0x01][ESCA_NODTYP_PART]);
                obid_pamstyl(last_str, (osv_oid_t *) (pamvp[0x01] + ESCA_OBIDCON_PART));
                enlen = sizeof (obid_entit);
            } else {
                OSEVPF("pamvp[0x01]:|%s|\n", pamvp[0x01]);
                enlen = strlen(pamvp[0x01]);
                stri_pamstyl_ext(last_str, pamvp[0x01], enlen);
                enlen += sizeof (stri_entit);
            }
        }
        //
        binary_entit *binen = (binary_entit *) pscon->pamstyl_memo;
        binen->notyp = DATY_BINARY;
        binen->colen = ivk_lvth.colen + enlen;
        pscon->colen = sizeof (binary_entit) + binen->colen;
        OSEVPF("end, pack_einvo_pamstyl\n");
        return pscon->colen;
    }

    //

    inline unsigned long long pack_qinvo_pamstyl(pamstyl_t *pscon, const char **pamvp) {
        OSEVPF("[FUNC]:pack_qinvo_pamstyl\n");
        unsigned long long enlen;
        char *last_str = pscon->pamstyl_memo + sizeof (binary_entit);
        if (OBJE_IDENT_TYPE == pamvp[0x00][ESCA_NODTYP_PART]) {
            last_str = obid_pamstyl(last_str, (osv_oid_t *) (pamvp[0x00] + ESCA_OBIDCON_PART));
            enlen = sizeof (obid_entit);
        } else {
            enlen = strlen(pamvp[0x00]);
            last_str = stri_pamstyl_ext(last_str, pamvp[0x00], enlen);
            enlen += sizeof (stri_entit);
        }
        //
        pamstyl_t ivk_lvfp;
        quote_decode((char *) pamvp[0x01]);
        if (INVA_ULOLO_VALU == parse_invok_metho(&ivk_lvfp, (char *) pamvp[0x01]))
            return INVA_ULOLO_VALU;
        last_str = binary_pamstyl_naked(last_str, ivk_lvfp.pamstyl_memo, ivk_lvfp.colen);
        //
        unsigned long long colen;
        if (pamvp[0x02]) {
            if (OBJE_IDENT_TYPE == pamvp[0x02][ESCA_NODTYP_PART]) {
                obid_pamstyl(last_str, (osv_oid_t *) (pamvp[0x02] + ESCA_OBIDCON_PART));
                enlen += sizeof (obid_entit);
            } else {
                colen = strlen(pamvp[0x02]);
                stri_pamstyl_ext(last_str, pamvp[0x02], colen);
                enlen += (sizeof (stri_entit) + colen);
            }
        }
        //
        binary_entit *binen = (binary_entit *) pscon->pamstyl_memo;
        binen->notyp = DATY_BINARY;
        binen->colen = ivk_lvfp.colen + enlen;
        pscon->colen = sizeof (binary_entit) + binen->colen;
        OSEVPF("end, pack_qinvo_pamstyl\n");
        return pscon->colen;
    }

    inline unsigned long long pack_qinup_paki(pamstyl_t *pscon, const char **pamvp, char *fmtst) {
        OSEVPF("[FUNC]:pack_disti_paki\n");
        OSEVPF("pamvp[0x00]:|%s| pamvp[0x01]:|%s|\n", pamvp[0x00], pamvp[0x01]);
        if (OBJE_IDENT_TYPE != ((char *) pamvp[0x00])[ESCA_NODTYP_PART])
            return INVA_ULOLO_VALU;
        char *last_str = obid_pamstyl(pscon->pamstyl_memo + sizeof (binary_entit), (osv_oid_t *) (pamvp[0x00] + ESCA_OBIDCON_PART));
        unsigned long long enlen = sizeof (obid_entit);
        //
        pamstyl_t ent_qinup;
        quote_decode((char *) pamvp[0x01]);
        if (INVA_ULOLO_VALU == parse_qinup_entit(&ent_qinup, (char *) pamvp[0x01], fmtst))
            return INVA_ULOLO_VALU;
        binary_pamstyl_naked(last_str, ent_qinup.pamstyl_memo, ent_qinup.colen);
        //
        binary_entit *binen = (binary_entit *) pscon->pamstyl_memo;
        binen->notyp = DATY_BINARY;
        binen->colen = ent_qinup.colen + enlen;
        pscon->colen = sizeof (binary_entit) + binen->colen;
        OSEVPF("pscon->colen:%llu enlen:%llu\n", pscon->colen, enlen);
        return pscon->colen;
    }

    // void build_local_fmtst(char *fmtst);

    inline void build_local_fmtst(char *fmtst) {
        char *tokep = strend(fmtst);
        (tokep + 0x01)[0x00] = '\0';
        char *tokop = tokep - 0x01;
        for (; fmtst <= tokop; --tokop, --tokep) {
            tokep[0x00] = tokop[0x00];
        }
        fmtst[0x00] = 'o';
    }

#ifdef __cplusplus
}
#endif

#endif /* DSTR_UTILI_H */

