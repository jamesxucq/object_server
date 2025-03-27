#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "third_party.h"

#include "utility/last_stri.h"
#include "osev_macro.h"
#include "stri_utili.h"
#include "commo_string.h"
#include "debug_funct_osv.h"


//
// -1:error 0x00:objeid 0x01:predicate / condition 0x02:"*"
#define WILDCARD_TOK '*'
#define PREDICA_TOK "!=<>&|"
#define PRED_AND_TOK "AND"
#define PRED_OR_TOK "OR"
#define PRED_NOT_TOK "NOT"

// 

int check_condi_type(char *pamcon) {
    // OSEVPF("[FUNC]:check_condi_type, pamcon:|%s|\n", pamcon);
    if (WILDCARD_TOK == pamcon[0x00] && '\0' == pamcon[0x01])
        return PREDI_TYPE_TRAVE;
    if (strpbrk(pamcon, PREDICA_TOK))
        return PREDI_TYPE_CONDI;
    //
    char *patok = pamcon;
    for (; '\0' != patok[0x00]; ++patok) {
        for (; ' ' == patok[0x00]; ++patok);
        if ('"' == patok[0x00]) {
            ++patok;
            for (; '\0' != patok[0x00] && '"' != patok[0x00]; ++patok);
            continue;
        }
        if (!strncmp(PRED_AND_TOK, patok, 0x03) || !strncmp(PRED_OR_TOK, patok, 0x02) || !strncmp(PRED_NOT_TOK, patok, 0x03))
            return PREDI_TYPE_CONDI;
        for (; '\0' != patok[0x00] && ' ' != patok[0x00]; ++patok);
    }
    //
    return PREDI_TYPE_EXCEP;
}

//
#define STROBID_TOK  "stroid"

int check_predi_type(char *pamcon) {
    OSEVPF("[FUNC]:check_predi_type, pamcon:|%s|\n", pamcon);
    if ('\0' == pamcon[0x00] || (WILDCARD_TOK == pamcon[0x00] && '\0' == pamcon[0x01]))
        return PREDI_TYPE_TRAVE;
    if (strpbrk(pamcon, PREDICA_TOK))
        return PREDI_TYPE_CONDI;
    //
    char *patok = pamcon;
    for (; '\0' != patok[0x00]; ++patok) {
        for (; ' ' == patok[0x00]; ++patok);
        if ('"' == patok[0x00]) {
            ++patok;
            for (; '\0' != patok[0x00] && '"' != patok[0x00]; ++patok);
            continue;
        }
        if (!strncmp(PRED_AND_TOK, patok, 0x03) || !strncmp(PRED_OR_TOK, patok, 0x02) || !strncmp(PRED_NOT_TOK, patok, 0x03))
            return PREDI_TYPE_CONDI;
        for (; '\0' != patok[0x00] && ' ' != patok[0x00]; ++patok);
    }
    //
    if (strstr(pamcon, STROBID_TOK))
        return PREDI_TYPE_OBJID;
    //
    OSEVPF("end check_predi_type\n");
    return PREDI_TYPE_EXCEP;
}

//

unsigned int query_source_count(char *source) {
    if ('\0' == source[0x00]) return 0x00;
    unsigned int scoun = 0x01;
    while ((source = strchr(++source, ','))) ++scoun;
    return scoun;
}

unsigned int query_source_conta(char (*qconta)[CONTA_LENGTH], char *source) {
    // OSEVPF("source:|%s|\n", source);
    char *toksp = source, *tokep;
    unsigned int inde = 0x00;
    for (; MAX_SCONT_COUNT > inde && '\0' != toksp[0x00]; ++inde, ++qconta) {
        for (; ' ' == toksp[0x00] || ',' == toksp[0x00]; ++toksp);
        if ('\0' == toksp[0x00]) break;
        tokep = toksp + 0x01;
        for (; ' ' != tokep[0x00] && ',' != tokep[0x00] && '\0' != tokep[0x00]; ++tokep);
        strzcpy(qconta[0x00], toksp, tokep - toksp);
        toksp = tokep;
    }
    MK_ZERO(qconta[0x00]);
    //
    return inde;
}

