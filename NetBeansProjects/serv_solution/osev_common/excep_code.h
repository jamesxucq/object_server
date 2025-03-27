
/* 
 * File:   excep_code.h
 * Author: James Xu
 *
 * Created on 2017.9.20
 */

#ifndef EXCEP_CODE_H
#define EXCEP_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

#define EXCEP_LENG sizeof(unsigned int)

    //
#define     SERV_BASE           0x10000000

    //
#define     HAND_BASE           0x40000000
#define     INVA_PARAM_EXPT         HAND_BASE|0x0001
#define     NOT_FOUND_CONTA         HAND_BASE|0x0003
#define     DROP_ENTIT_EXPT         HAND_BASE|0x0005
#define     FACTO_QUERY_EXPT        HAND_BASE|0x0007
#define     CREAT_ENTIT_EXPT        HAND_BASE|0x0009
#define     CREAT_QUERY_EXPT        HAND_BASE|0x000B
#define     INVOK_ENTIT_EXPT        HAND_BASE|0x000D
#define     SEARC_ENTIT_EXPT        HAND_BASE|0x0011
#define     INSER_ENTIT_EXPT        HAND_BASE|0x0013
#define     UPDAT_ENTIT_EXPT        HAND_BASE|0x0015
#define     ECHO_OBJID_EXPT         HAND_BASE|0x0017
#define     RELOA_LVTP_EXPT         HAND_BASE|0x0019
#define     LVTP_INTEG_EXPT         HAND_BASE|0x001B
#define     STATI_BASE_EXPT         HAND_BASE|0x001D
#define     LVTP_INFO_EXPT          HAND_BASE|0x0021
#define     CONTA_EXIST_EXPT        HAND_BASE|0x0023
#define     STATU_AUTH_EXPT         HAND_BASE|0x0027
#define     COMPI_COLLE_EXPT        HAND_BASE|0x0029  
#define     CREAT_COLLE_EXPT        HAND_BASE|0x002B    
#define     LVTP_NOT_FOUND          HAND_BASE|0x002D    
#define     RELOA_INVOK_CLANG       HAND_BASE|0x0031
#define     RELOA_INVOK_EXPT        HAND_BASE|0x0033  
#define     RELOA_INVOK_LIBRA       HAND_BASE|0x0035
#define     DROP_INVOK_EXPT         HAND_BASE|0x0037    
#define     DROP_INVOK_INHE         HAND_BASE|0x0039    
#define     PARMS_PARM_EXPT         HAND_BASE|0x003B   
#define     COMPI_INVOK_EXPT        HAND_BASE|0x003D    
#define     CREAT_INVOK_EXPT        HAND_BASE|0x0041    
#define     INVOK_NOT_FOUND         HAND_BASE|0x0043
#define     INVOK_INFO_EXPT         HAND_BASE|0x0045 
#define     INNER_DATA_EXPT         HAND_BASE|0x0047  
#define     CLOSE_BASE_EXPT         HAND_BASE|0x0049  
    // #define     OPEN_BASE_OK         HAND_BASE|0x004B  
#define     OPEN_BASE_EXPT          HAND_BASE|0x004D  
#define     ECHO_BASE_EXPT          HAND_BASE|0x0051  
#define     QUERY_ASTAT_EXPT        HAND_BASE|0x0053  
#define     ECHO_ABASE_EXPT         HAND_BASE|0x0055
#define     CREAT_INHER_EXPT        HAND_BASE|0x0057
#define     PARSE_METHO_EXPT        HAND_BASE|0x0059
#define     SAVE_CLASS_EXPT         HAND_BASE|0x005B
    // #define     SET_STATU_EXPT     HAND_BASE|0x0059 
#define     REPLA_INVOK_DECL        HAND_BASE|0x0061
#define     REPLA_INVOK_EXPT        HAND_BASE|0x0063
#define     SAVE_CLANG_EXPT         HAND_BASE|0x0065
#define     OPEN_IHAND_EXPT         HAND_BASE|0x0067            
#define     OPEN_OATTR_EXPT         HAND_BASE|0x0069   
#define     OPEN_BATTR_EXPT         HAND_BASE|0x0069   
#define     OBJEC_FILE_EXPT         HAND_BASE|0x006B
#define     LIST_LVTP_EXPT          HAND_BASE|0x006D
#define     RELOA_COLLE_DECL        HAND_BASE|0x006F
#define     REQUE_VALID_EXPT        HAND_BASE|0x0071
#define     DROP_COLLE_HAND         HAND_BASE|0x0073
#define     DROP_INVOK_INTE         HAND_BASE|0x0075   
#define     DROP_INVOK_HAND         HAND_BASE|0x0077
#define     DROP_INVOK_CONTE        HAND_BASE|0x0079
#define     LVTP_INHER_EXPT         HAND_BASE|0x007B
#define     DROP_COLLE_EXPT         HAND_BASE|0x007D
#define     DROP_COLLE_INHE         HAND_BASE|0x007F
#define     DROP_COLLE_OEXI         HAND_BASE|0x0081
#define     RELOA_INVOK_PROTE       HAND_BASE|0x0083
#define     RELOA_INVOK_INTEG       HAND_BASE|0x0085
#define     RELOA_INVOK_DECL        HAND_BASE|0x0087
#define     CREAT_REGIS_INHE        HAND_BASE|0x0089
#define     FIND_SUPER_EXPT         HAND_BASE|0x008B
#define     CONVE_INLVO_EXPT        HAND_BASE|0x008D
#define     CREAT_INLVO_EXPT        HAND_BASE|0x008F
#define     SEARC_QUERY_EXPT        HAND_BASE|0x0091
#define     DROP_QUERY_EXPT         HAND_BASE|0x0093
#define     UPDAT_QUERY_EXPT        HAND_BASE|0x0095
#define     INVOK_QUERY_EXPT        HAND_BASE|0x0097
#define     INSER_QUERY_EXPT        HAND_BASE|0x0099
#define     REPLA_COLLE_EXPT        HAND_BASE|0x009B    
#define     ECHO_QUERY_EXPT         HAND_BASE|0x009D    
#define     CREAT_LVTME_EXPT        HAND_BASE|0x009F
#define     CREAT_LVOME_EXPT        HAND_BASE|0x00A1
#define     LOAD_EXPAND_EXPT        HAND_BASE|0x00A3
#define     MALLO_LVTEXP_EXPT       HAND_BASE|0x00A5
#define     STATI_OSEV_EXPT         HAND_BASE|0x00A7
#define     INVA_PARAM_LENG         HAND_BASE|0x00A9
#define     STATI_CONTAIN_EXPT      HAND_BASE|0x00AB
    
    //
#define     FIND_ROLE_EXPT          HAND_BASE|0xA001
#define     ADDI_ROLE_EXPT          HAND_BASE|0xA003
#define     ROLE_USED_EXPT          HAND_BASE|0xA005
#define     DELE_ROLE_EXPT          HAND_BASE|0xA007
#define     DISTI_OBID_EXPT         HAND_BASE|0xA009
#define     LOAD_ROLE_EXPT          HAND_BASE|0xA00B
#define     REVK_PRIV_EXPT          HAND_BASE|0xA00D
#define     FIND_USER_EXPT          HAND_BASE|0xA00F
#define     GRAN_PRIV_EXPT          HAND_BASE|0xA011
#define     DELE_USER_EXPT          HAND_BASE|0xA013
#define     ADDI_USER_EXPT          HAND_BASE|0xA015
#define     REVK_ROLE_EXPT          HAND_BASE|0xA017
#define     GRAN_ROLE_EXPT          HAND_BASE|0xA019
#define     USER_ROLE_EXIS          HAND_BASE|0xA01B
#define     ROLE_PRIV_EXIS          HAND_BASE|0xA01D
#define     BASE_ADMIN_EXPT         HAND_BASE|0xA01F
#define     BASE_ECHO_EXPT          HAND_BASE|0xA021 
#define     BASE_SETLV_EXPT         HAND_BASE|0xA023 
#define     BASE_PRIVI_EXPT         HAND_BASE|0xA025 
#define     OSEV_ECHO_EXPT          HAND_BASE|0xA027 
#define     OSEV_SETLV_EXPT         HAND_BASE|0xA029 
#define     OSEV_PRIVI_EXPT         HAND_BASE|0xA02B
#define     USER_ROLE_NOTFOUND      HAND_BASE|0xA02D
#define     INVA_ATTRIB_EXPT        HAND_BASE|0xA02F
#define     LEVO_NOT_FOUND          HAND_BASE|0xA031
// #define     NO_PERMIS_EXPT          HAND_BASE|0xA033
// #define     LOST_TARGET_EXPT        HAND_BASE|0xA035
    
    //#define     _EXPT         HAND_BASE|0xA000 
    //#define     _EXPT         HAND_BASE|0xA000 


#define     OSEV_ATTACH_OKAY   (HAND_BASE|0xFFFFFF) 

    //
#define     RIVE_BASE      0x70000000


#ifdef __cplusplus
}
#endif

#endif /* EXCEP_CODE_H */

