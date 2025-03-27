
#include <string.h>

#include "commo_header.h"

#include "kcomm_types.h"

///////////////////////////////////////////
// trans-serve
const struct stst_node ostyp_clang_dict[] = {
    {OSV_DATYP_INT8, "signed char"},
    {OSV_DATYP_UINT8, "unsigned char"},
    {OSV_DATYP_INT16, "short int"},
    {OSV_DATYP_UINT16, "unsigned short int"},
    {OSV_DATYP_INT32, "int"},
    {OSV_DATYP_INT32, "unsigned int"},
    {OSV_DATYP_INT64, "long long int"},
    {OSV_DATYP_UINT64, "unsigned long long int"},
    {OSV_DATYP_OBID, "osv_oid_t"},
    {OSV_DATYP_FLOAT, "float"},
    {OSV_DATYP_DOUBLE, "double"},
    {OSV_DATYP_CHAR, "char"},
    {OSV_DATYP_STRING, "char *"}, // NUL-terminated
    {OSV_DATYP_BYTE, "unsigned char"},
    //
    {NULL, NULL}
};

/////////////////////////////////////////////
// trans-serve
const struct stch_node ostyp_fmtst_dict[] = {
    {OSV_DATYP_INT8, 'b'},
    {OSV_DATYP_UINT8, 'B'},
    {OSV_DATYP_INT16, 'h'},
    {OSV_DATYP_UINT16, 'H'},
    {OSV_DATYP_INT32, 'i'},
    {OSV_DATYP_INT32, 'I'},
    {OSV_DATYP_INT64, 'q'},
    {OSV_DATYP_UINT64, 'Q'},
    {OSV_DATYP_OBID, 'o'},
    {OSV_DATYP_FLOAT, 'f'},
    {OSV_DATYP_DOUBLE, 'd'},
    {OSV_DATYP_CHAR, 's'},
    {OSV_DATYP_STRING, 'S'}, // NUL-terminated
    {OSV_DATYP_BYTE, 's'},
    //
    {NULL, '\0'}
};

/////////////////////////////////////////////
// trans-serve
const struct stin_node retyp_calle_dict[] = {
    {OSV_DATYP_VOID, RTYP_VOID},
    {OSV_DATYP_INT8, RTYP_CHAR},
    {OSV_DATYP_UINT8, RTYP_UCHA},
    {OSV_DATYP_INT16, RTYP_SHOR},
    {OSV_DATYP_UINT16, RTYP_USHO},
    {OSV_DATYP_INT32, RTYP_INT},
    {OSV_DATYP_INT32, RTYP_UINT},
    {OSV_DATYP_INT64, RTYP_LLON},
    {OSV_DATYP_UINT64, RTYP_ULLO},
    {OSV_DATYP_OBID, RTYP_OBID},
    {OSV_DATYP_FLOAT, RTYP_FLOA},
    {OSV_DATYP_DOUBLE, RTYP_DOUB},
    {OSV_DATYP_CHAR, RTYP_CHAP},
    {OSV_DATYP_STRING, RTYP_STRZ}, // NUL-terminated
    {OSV_DATYP_BYTE, RTYP_CHAR},
    //
    {NULL, -1}
};

/////////////////////////////////////////////
// trans-serve
const struct stin_node ostyp_pamati_dict[] = {
    {OSV_DATYP_INT8, PARM_NUMB},
    {OSV_DATYP_UINT8, PARM_NUMB},
    {OSV_DATYP_INT16, PARM_NUMB},
    {OSV_DATYP_UINT16, PARM_NUMB},
    {OSV_DATYP_INT32, PARM_NUMB},
    {OSV_DATYP_INT32, PARM_NUMB},
    {OSV_DATYP_INT64, PARM_NUMB},
    {OSV_DATYP_UINT64, PARM_NUMB},
    {OSV_DATYP_OBID, PARM_OBID},
    {OSV_DATYP_FLOAT, PARM_NUMB},
    {OSV_DATYP_DOUBLE, PARM_NUMB},
    {OSV_DATYP_CHAR, PARM_STRI},
    {OSV_DATYP_STRING, PARM_STRZ}, // NUL-terminated
    {OSV_DATYP_BYTE, PARM_BYTE},
    //
    {NULL, PARM_INVAL}
};

/////////////////////////////////////////////
// trans-serve
const struct stin_node ostyp_potyp_dict[] = {
    {OSV_DATYP_INT8, DATY_BYTE},
    {OSV_DATYP_UINT8, DATY_UBYTE},
    {OSV_DATYP_INT16, DATY_SHORT},
    {OSV_DATYP_UINT16, DATY_USHORT},
    {OSV_DATYP_INT32, DATY_INT},
    {OSV_DATYP_INT32, DATY_UINT},
    {OSV_DATYP_INT64, DATY_LLONG},
    {OSV_DATYP_UINT64, DATY_ULLONG},
    {OSV_DATYP_OBID, DATY_OBID},
    {OSV_DATYP_FLOAT, DATY_FLOAT},
    {OSV_DATYP_DOUBLE, DATY_DOUBLE},
    {OSV_DATYP_CHAR, DATY_STRI},
    {OSV_DATYP_STRING, DATY_STRZ}, // NUL-terminated
    {OSV_DATYP_BYTE, DATY_BINARY},
    //
    {NULL, DATY_INVAL}
};

/////////////////////////////////////////////
// trans-serve
char potyp_fmtst_tab[] = {
    '\0', // DATY_INVAL
    //
    'b', // DATY_BYTE
    'B', // DATY_UBYTE
    'h', // DATY_SHORT
    'H', // DATY_USHORT
    'i', // DATY_INT
    'I', // DATY_UINT
    'q', // DATY_LLONG
    'Q', // DATY_ULLONG
    'o', // DATY_OBID
    'f', // DATY_FLOAT
    'd', // DATY_DOUBLE
    's', // DATY_STRI
    'S', // DATY_STRZ// NUL-terminated
    'e' // DATY_BINARY
};

// 

char *potyp_clang_tab[] = {
    NULL, // DATY_INVAL
    //
    "signed char", // DATY_BYTE
    "unsigned char", // DATY_UBYTE
    "short int", // DATY_SHORT
    "unsigned short int", // DATY_USHORT
    "int", // DATY_INT
    "unsigned int", // DATY_UINT
    "long long int", // DATY_LLONG
    "unsigned long long int", // DATY_ULLONG
    "osv_oid_t", // DATY_OBID
    "float", // DATY_FLOAT
    "double", // DATY_DOUBLE
    "char", // DATY_STRI
    "char *", // DATY_STRZ// NUL-terminated
    "char" // DATY_BINARY
};

//

char *potyp_ostyp_tab[] = {
    NULL, // DATY_INVAL
    //
    OSV_DATYP_INT8, // DATY_BYTE
    OSV_DATYP_UINT8, // DATY_UBYTE
    OSV_DATYP_INT16, // DATY_SHORT
    OSV_DATYP_UINT16, // DATY_USHORT
    OSV_DATYP_INT32, // DATY_INT
    OSV_DATYP_INT32, // DATY_UINT
    OSV_DATYP_INT64, // DATY_LLONG
    OSV_DATYP_UINT64, // DATY_ULLONG
    OSV_DATYP_OBID, // DATY_OBID
    OSV_DATYP_FLOAT, // DATY_FLOAT
    OSV_DATYP_DOUBLE, // DATY_DOUBLE
    OSV_DATYP_CHAR, // DATY_STRI
    OSV_DATYP_STRING, // DATY_STRZ// NUL-terminated
    OSV_DATYP_BYTE // DATY_BINARY
};