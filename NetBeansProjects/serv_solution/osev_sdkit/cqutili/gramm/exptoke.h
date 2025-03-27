
/* 
 * File:  exptoke.h
 * Author: James
 *
 * Created on 2018.12.10, AM 9:30
 */

#ifndef EXPTOKE_H
#define EXPTOKE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "commo_header.h"
// #include "gramm/expre_analy.h"

    /*
     * && AND || OR ! NOT ( ) < > == != <= >= BETWEEN IN
     */

    //
#define INVA_TOKE           0x00000000

    //
#define ALPHA_TOKE          0x00010000 // visual token
#define TERM_TOKE           0x00020000 // visual token
#define METH_TOKE           0x00040000 // visual token
    //
#define TEXT_TOKE           TK_STRING // general
#define LOLO_NUMB_TOKE      TK_INTEGER // general
#define ULLO_NUMB_TOKE      TK_UINTEGER // general
#define DOUB_NUMB_TOKE      TK_FLOAT // general
    //
#define OR_TOKE             TK_OR // || OR
#define AND_TOKE            TK_AND // && AND
#define NOT_TOKE            TK_NOT // ! NOT
#define IS_TOKE             TK_IS // IS
#define MATCH_TOKE          TK_MATCH // MATCH
#define LIKE_KW_TOKE        TK_LIKE_KW // LIKE
#define BETWEEN_TOKE        TK_BETWEEN // BETWEEN
#define IN_TOKE             TK_IN // IN
#define NOT_EQUAL_TOKE      TK_NE // !=
#define EQUAL_TOKE          TK_EQ // =
#define GREAT_THAN_TOKE     TK_GT // >
    // #define NOT_MORE_TOKE       0x00002000
#define LESS_EQUAL_TOKE     TK_LE // <=
#define LESS_THAN_TOKE      TK_LT // <
    // #define NOT_LESS_TOKE       0x00004000
#define GREAT_EQUAL_TOKE    TK_GE // >=
#define ESCAPE_TOKE         TK_ESCAPE // ESCAPE
#define LEFT_PARENT_TOKE    TK_LP // (
#define RIGHT_PARENT_TOKE   TK_RP // )
#define PLUS_TOKE           TK_PLUS // +
#define MINUS_TOKE          TK_MINUS // -
    //
#define ID_TOKE             TK_ID // general
#define CTIME_KW_TOKE       TK_CTIME_KW // CTIME
#define ISNULL_TOKE         TK_ISNULL // ISNULL
#define NOTNULL_TOKE        TK_NOTNULL // NOTNULL
#define BITAND_TOKE         TK_BITAND // BITAND
#define BITOR_TOKE          TK_BITOR // BITOR
#define LSHIFT_TOKE         TK_LSHIFT // LSHIFT
#define RSHIFT_TOKE         TK_RSHIFT // RSHIFT
#define STAR_TOKE           TK_STAR // *
#define SLASH_TOKE          TK_SLASH // /
#define REM_TOKE            TK_REM // #
#define CONCAT_TOKE         TK_CONCAT // CONCAT
#define COLLATE_TOKE        TK_COLLATE // COLLATE
#define BITNOT_TOKE         TK_BITNOT // BITNOT
#define ON_TOKE             TK_ON // ON
#define STRING_TOKE         TK_STRING
#define JOIN_KW_TOKE        TK_JOIN_KW // JOIN
    // #define COLON_TOKE          0x000000A1 // :
#define NULL_TOKE           TK_NULL // NULL
#define FLOAT_TOKE          TK_FLOAT
#define BLOB_TOKE           TK_BLOB // general
#define INTEGER_TOKE        TK_INTEGER
#define VARIABLE_TOKE       TK_VARIABLE // general
#define COMMA_TOKE          TK_COMMA // ,
    // user define
#define UPLUS_TOKE           TK_UPLUS // +
#define UMINUS_TOKE          TK_UMINUS // -
#define OPER_TYPE(OPETYP)   (OPETYP & 0x0000FFFF)

    //
    unsigned int get_alpha_toke(char *toke_stri);


    //



#ifdef __cplusplus
}
#endif

#endif /* EXPTOKE_H */

