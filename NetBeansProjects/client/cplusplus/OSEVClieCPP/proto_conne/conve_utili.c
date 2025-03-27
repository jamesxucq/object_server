
#include <stddef.h>

#include "osev_common/commo_header.h"
#include "osev_common/reque_conne.h"

#include "conve_utili.h"

// const
//#define     ESTAT_ECHO    0x00
//#define     ESTAT_ATTRIB   0x01
//#define     ESTAT_STATIS   0x02

/*
const struct stui_node enti_echo_dict[] = {
    {"ECHO", ESTAT_ECHO}, // ECHO
    {"ATTRIB", ESTAT_ATTRIB}, // ATTRIB
    {"STATIS", ESTAT_STATIS}, // STATIS
    {NULL, INVA_UINT_VALU}
};
*/

// query

// Server
//#define     QSTAT_ECHO    0x00
//#define     QSTAT_ATTRIB   0x01
//#define     QSTAT_STATIS   0x02

/*
const struct stui_node quer_echo_dict[] = {
    {"ECHO", QSTAT_ECHO}, // ECHO
    {"ATTRIB", QSTAT_ATTRIB}, // ATTRIB
    {"STATIS", QSTAT_STATIS}, // STATIS
    {NULL, INVA_UINT_VALU}
};
*/

//

const struct stst_node stora_engine_dict[] = {
    {"sharp", "0I"}, // ENGINE_SHARP
    {"imemo", "1I"}, // ENGINE_IMEMO
    {"leap", "2I"}, // ENGINE_LEAP
    {"witi", "3I"}, // ENGINE_WTIGER
    {NULL, "INVA"}
};