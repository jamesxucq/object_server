
#ifndef CSTRI_UTILI_H
#define CSTRI_UTILI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int creat_runcomd_directory(char *comd_dire, char *leve_dire);
    char *runcomd_name(char *file_name);
    char *levecomd_name(char *leve_dire, char *file_name);

    // INVA_OLITYP:error  INVOK_INSTRU_OLITYP:only invok / command; OBJE_INVOK_OLITYP:object invok; 
    // LEVE_INVOK_OLITYP:object level invok; OBJE_LEVIVK_OLITYP:level invok
#define INVA_OLITYP             -1
#define INVOK_INSTRU_OLITYP     0x00
#define OBJE_INVOK_OLITYP       0x01
#define LEVE_INVOK_OLITYP       0x02   
#define OBJE_LEVIVK_OLITYP      0x03   
    int inst_lvikoi_type(char *space);
    char *split_levivk_space(char *levivk, char *space);
    char *split_levivk_invok(char *levivk, char *invok, char *space);
    char *split_objide_levivk(char *objide, char *levivk, char *space);
    char *decod_objide_levivk(char *objide, char *levivk, char *invok, char *coline);
    char *next_pamvu(char *pamcon, char *coline);

    // 0:yes -1:no
    int accep_clie_metho(char *line_str, const char* objide);
    int accep_osev_metho(char *line_str, const char *clie_obje, const char *osev_obje);
    int accep_base_metho(char *line_str, const char *clie_obje, const char *base_obje, const char *kits_obje);
    int accep_user_metho(char *line_str);
    // 0:yes -1:no
    int is_defin_class(char *line_str);
    int is_defin_metho(char *line_str);
    int is_opera_invok(char *line_str);
    int is_opera_colle(char *line_str);
    int is_opera_const(char *line_str);
    int is_opera_query(char *line_str);

    // 0x00:finish 0x01:continue -1:error 
    int invok_metho_finis(char *line_str);
    int class_defin_finis(char *line_str);
    int metho_defin_finis(char *line_str);
    int opera_invok_finis(char *line_str);
    int opera_colle_finis(char *line_str);
    int opera_const_finis(char *line_str);
    int opera_query_finis(char *line_str);

    // 
    char *have_nspace(char *pamcon);

    //
    int have_defa_obje(char *line_str);
    int is_creat_class(const char *objide, char *lev1n);
    int is_creat_metho(const char *objide, char *lev1n);
    int check_redirect_obje(char *line_str);
#define IS_CREAT_OBJE(OBJE, METHN) strcmp(OBJE, METHN)
    //
    int single_instru(char (*inst_stri)[LARGE_TEXT_SIZE], char *cline_stri);
    int multi_instru(char (*inst_stri)[LARGE_TEXT_SIZE], char *cline_stri);

    //
    char *analy_const_eobje_exte(char *parms_cont, char *line_str);
    char *analy_const_eobje_redi(char *redi_obje, char *parms_cont, char *line_str);
    // odb-lv4p> witi:witi("taat_con", "txxt") > odb;
#ifdef _CREAT_COBJE_REDIRECT
    char *analy_const_cobje(char *redi_obje, char *parms_cont, char *line_str, char *lv2pn);
#else
    char *analy_const_cobje(char *parms_cont, char *line_str, char *lv2pn);
#endif // _CREAT_COBJE_REDIRECT
    char *analy_statu_open(char *parms_cont, char *line_str, char *objide);
    char *analy_statu_statis(char *parms_cont, char *line_str, char *objide);

    //
    char *find_parms_conte(char *parms, char *coline);

    //
    void ClitPrintWarn(const char *fmt, ...);
#define CLIT_PROMPT "    CLIT: "

    //

#define ClitPrintErro(ERR_LABE, ERR_NUM) { \
        if (ERR_NUM) fprintf(stderr, CLIT_PROMPT"%s errno:%d\n", ERR_LABE, ERR_NUM); \
        else fprintf(stderr, CLIT_PROMPT"%s\n", ERR_LABE); \
    }

#define ClitPrintInfo(INFO) \
    fprintf(stderr, CLIT_PROMPT"%s\n", INFO)

#define OSEVE_PROMPT "    OSEV: "

    inline void OSEVPrintErro(char *err_labe, int err_num) {
        if (err_num) fprintf(stderr, OSEVE_PROMPT"%s errno:%08X\n", err_labe, err_num);
        else fprintf(stderr, OSEVE_PROMPT"%s\n", err_labe);
    }

    //
    char *inser_tail(char **strp, char *posi);

    //

    int valid_osev_objide(char *obje);
    int split_last_obje(char *last_obje, const char *objide);


#ifdef __cplusplus
}
#endif

#endif /* CSTRI_UTILI_H */

