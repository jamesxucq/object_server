#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "lev1_oinvk.h"

//

int build_oinvk_parms(char *parm_oivk, char **pamvp) {
    unsigned long long colen;
    for (; NULL != pamvp[0x00]; ++pamvp) {
        switch (((unsigned char *) pamvp[0x00])[0x00]) {
            case DATY_BYTE:
            case DATY_UBYTE:
                *((unsigned char *) parm_oivk) = ((ubyte_entit *) pamvp[0x00])->data;
                parm_oivk += sizeof (unsigned char);
                break;
            case DATY_SHORT:
            case DATY_USHORT:
                *((unsigned short *) parm_oivk) = ((ushort_entit *) pamvp[0x00])->data;
                parm_oivk += sizeof (unsigned short);
                break;
            case DATY_INT:
            case DATY_UINT:
                *((unsigned int *) parm_oivk) = ((uint_entit *) pamvp[0x00])->data;
                // printf("---------------*((unsigned int *) parm_oivk):%d\n", *((unsigned int *) parm_oivk));
                parm_oivk += sizeof (unsigned int);
                break;
            case DATY_LLONG:
            case DATY_ULLONG:
                *((unsigned long long *) parm_oivk) = ((ullong_entit *) pamvp[0x00])->data;
                parm_oivk += sizeof (unsigned long long);
                break;
            case DATY_OBID:
                OBID_BINARY_COPY((osv_oid_t *) parm_oivk, &((obid_entit *) pamvp[0x00])->data)
                parm_oivk += sizeof (osv_oid_t);
                break;
            case DATY_FLOAT:
                *((float *) parm_oivk) = ((float_entit *) pamvp[0x00])->data;
                parm_oivk += sizeof (float);
                break;
            case DATY_DOUBLE:
                *((double *) parm_oivk) = ((double_entit *) pamvp[0x00])->data;
                parm_oivk += sizeof (double);
                break;
            case DATY_STRI:
                colen = ((stri_entit *) pamvp[0x00])->colen;
                memcpy(parm_oivk, ((stri_entit *) pamvp[0x00])->data, colen);
                parm_oivk += colen;
                break;
            case DATY_STRZ:
                ((strz_t *) parm_oivk)->type = 0x00; // 0x00:osev 0x0f:user 0xf0:stat
                ((strz_t *) parm_oivk)->data = ((strz_entit *) pamvp[0x00])->data;
                ((strz_t *) parm_oivk)->slen = ((strz_entit *) pamvp[0x00])->colen; // string leng
                ((strz_t *) parm_oivk)->asiz = ((strz_t *) parm_oivk)->slen; // alloc size
                parm_oivk += sizeof (strz_t);
                break;
            case DATY_BINARY:
                // enlen[0x00] = sizeof (binary_entit) + ((binary_entit *) pscon)->colen;
                colen = ((binary_entit *) pamvp[0x00])->colen;
                memcpy(parm_oivk, ((binary_entit *) pamvp[0x00])->data, colen);
                parm_oivk += colen;
                break;
            default:
                _LOG_WARN("default: decode_pamstyl");
                return -1;
                break;
        }
    }
    //
    return 0x00;
}

