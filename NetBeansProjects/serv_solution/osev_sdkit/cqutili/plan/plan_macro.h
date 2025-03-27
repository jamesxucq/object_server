
/* 
 * File:   plan_macro.h
 * Author: James Xu
 *
 * Created on 2022.4.20, 2:20
 */

#ifndef PLAN_MACRO_H
#define PLAN_MACRO_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#define PLAN_ITEM_SZIE      256

    //
#define INVA_ACCO           0x00000000

    // position code
#define PLAN_HEAD_ACCO      0x10000000
#define POSI_CODE(POSCOD)   (POSCOD & 0xF0000000)

    // action code   
#define INIT_QUERY_ACCO     0x00010000
#define FINAL_QUDRY_ACCO    0x00030000
#define OPEN_CONTE_ACCO     0x00050000
#define CLOSE_CONTE_ACCO    0x00070000
#define RESUL_SET_ACCO      0x00090000
#define METHO_SET_ACCO      0x000B0000
#define OPERA_SET_ACCO      0x000D0000
#define ACTI_CODE(ACTCOD)   (ACTCOD & 0x0FFF0000)

    // value code
#define TEXT_VALU           0x00000100
#define LOLO_NUMB_VALU      0x00000300
#define ULLO_NUMB_VALU      0x00000500
#define DOUB_NUMB_VALU      0x00000700
#define ID_VALU             0x00000900
#define VALU_CODE(VALCOD)   (VALCOD & 0x0000FF00)

    // operation code
    // OR AND NOT IS MATCH LIKE_KW BETWEEN IN NOT_EQUAL EQUAL 
    // GREAT_THAN LESS_EQUAL LESS_THAN GREAT_EQUAL ESCAPE PLUS MINUS
#define OR_OPCO             0x00000001
#define AND_OPCO            0x00000003
#define NOT_OPCO            0x00000005
#define IS_OPCO             0x00000007
#define MATCH_OPCO          0x00000009
#define LIKE_KW_OPCO        0x0000000B
#define BETWEEN_OPCO        0x0000000D
#define IN_OPCO             0x0000000F
#define NOT_EQUAL_OPCO      0x00000011
#define EQUAL_OPCO          0x00000013
#define GREAT_THAN_OPCO     0x00000015
#define LESS_EQUAL_OPCO     0x00000017
#define LESS_THAN_OPCO      0x00000019
#define GREAT_EQUAL_OPCO    0x0000001B
#define ESCAPE_OPCO         0x0000001D
#define PLUS_OPCO           0x0000001F
#define MINUS_OPCO          0x00000021
#define OPER_CODE(OPECOD)   (OPECOD & 0x000000FF)

    //


#ifdef __cplusplus
}
#endif

#endif /* PLAN_MACRO_H */

