
/* 
 * File:   kcomm_header.h
 * Author: James Xu
 *
 * Created on 2022.11.23, AM 10:43
 */

#ifndef KCOMM_HEADER_H
#define KCOMM_HEADER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _OSEV_CLITE

#endif /* _OSEV_CLITE */

#ifdef _OSEV_SDKIT

#include "kcomm_macro.h"
#include "kcomm_struct.h"
#include "kcomm_types.h"
#include "fmtst_utili.h"
#include "compi_clang.h"
#include "hashdb_ex.h"
#include "hash_mapd_ex.h"
#include "daemonize.h"
#include "kcstr_utili.h"
#include "kcomm_directory.h"
#include "lev1_decla.h"
#include "lev1_oinvk.h"
#include "lv2p_decla.h"
#include "lv2p_expand.h"
#include "leve_list.h"
#include "lv2p_meta.h"
#include "lv2p_attri.h"
#include "instda.h"
#include "liv_list.h"
#include "privi_code.h"
#include "recurs_data.h"
#include "oattri.h"
#include "oreval.h"
#include "base_value.h"
#include "basev_list.h"
#include "field_utili.h"
#include "paki_memo.h"
#include "loop_memo.h"
#include "valu_memo.h"
#include "slov_memo.h"
#include "bound_utili.h"
#include "solve_bound.h"
#include "const_utili.h"
#include "cfile_utili.h"
#include "stati_scont.h"
    
#include "lvalid/vilid_lv2pd_ite.h"
#include "lvalid/valid_lev1d_ite.h"
#include "refere/refer_macro.h"
#include "refere/refer_struct.h"
#include "refere/refer_utili.h"
#include "proje_entit/build_proje_entit.h"
#include "proje_entit/build_proje_renti.h"

#endif /* _OSEV_SDKIT */

#ifdef _OSEV_CLIT

#endif /* _OSEV_CLIT */

#ifdef _OSEV_SERV

#include "kcomm_types.h"

#include "daemonize.h"
#include "lev1_decla.h"
#include "lv2p_decla.h"
#include "lv2p_expand.h"
#include "lv2p_attri.h"
#include "leve_list.h"
#include "liv_list.h"
#include "basev_list.h"
#include "instda.h"
#include "privi_code.h"
#include "loop_memo.h"
#include "valu_memo.h"
#include "slov_memo.h"

#endif /* _OSEV_SERV */


#ifdef __cplusplus
}
#endif

#endif /* KCOMM_HEADER_H */

