#include "common_header.h"

#include "stri_utili.h"
#include "comp_bzl.h"
#include "hand_bzl.h"
#include "inte_execu.h"

// odb:echo();
// odb:creat();
// odb:drop();
// odb:integri();
// odb:reload();

//
static osv_str_t LEVE_EODB_TOK = osv_string("odb");

//
static const struct value_node execu_value_table[] = {
    {"echo", EXEC_ECHO},
    {"creat", EXEC_CREAT},
    {"drop", EXEC_DROP},
    {"integri", EXEC_INTEGRI},
    {"reload", EXEC_RELOAD},
    {NULL, 0}
};

//

static int clas_querye(struct cmdi_execu *cmd_exec, char *execu) {
    char obje_ide[OBJE_LENGTH];
    char meth_str[METH_LENGTH];
    char para_str[PARAM_LENGTH];
    if (!split_metho(obje_ide, meth_str, para_str, execu)) return -1;
printf("parse class querye.\n");
    //);
    cmd_exec->clas_meth = 0x01;
    TEXT_VALUE(cmd_exec->exec_type, execu_value_table, meth_str)
    strcpy(cmd_exec->space_str, obje_ide);
    strcpy(cmd_exec->meth_str, meth_str);
    strcpy(cmd_exec->para_str, para_str);
    //
    return 0x00;
}

static int meth_querye(struct cmdi_execu *cmd_exec, char *execu) {
    char obje_ide[OBJE_LENGTH];
    char meth_str[METH_LENGTH];
    char para_str[PARAM_LENGTH];
    if (!split_metho(obje_ide, meth_str, para_str, execu)) return -1;
printf("parse method querye.\n");
    //
    cmd_exec->clas_meth = 0x00;
    TEXT_VALUE(cmd_exec->exec_type, execu_value_table, meth_str)
    strcpy(cmd_exec->space_str, obje_ide);
    strcpy(cmd_exec->meth_str, meth_str);
    strcpy(cmd_exec->para_str, para_str);
    //
    return 0x00;
}

static int defin_class(struct cmdi_execu *cmd_exec, char *execu) {
printf("parse class define.\n");
    cmd_exec->clas_meth = 0x01;
    cmd_exec->exec_type = EXEC_CREAT;
    strcpy(cmd_exec->execu_line, execu);
    return 0x00;
}

static int defin_method(struct cmdi_execu *cmd_exec, char *execu) {
printf("parse method define.\n");
    cmd_exec->clas_meth = 0x00;
    cmd_exec->exec_type = EXEC_CREAT;
    strcpy(cmd_exec->execu_line, execu);
    return 0x00;
}

// -1:error 0x00:method define 0x01/0x02:class define 0x03:meth querye

static int chk_execu_type(char *execu) {
    if (!is_class_querye(execu, &LEVE_EODB_TOK)) return 0x04;
    else if (!is_metho_querye(execu, &LEVE_EODB_TOK)) return 0x03;
    else if (!is_metho_comple(execu)) return 0x02;
    else if (!is_defin_class(execu)) return 0x01;
    else if (!is_metho_simple(execu)) return 0x00;
    return -1;
}

static int (*parse_execu_tab[])(struct cmdi_execu *, char *) = {
    defin_method,
    defin_class,
    defin_class,
    meth_querye,
    clas_querye
};

int parse_execute(struct cmdi_execu *cmd_exec, char *execu) {
printf("parse execute:|%s|\n", execu);
    int execu_type = chk_execu_type(execu);
printf("execu_type:%d\n", execu_type);
    if(-1 == execu_type) return -1;
    return parse_execu_tab[execu_type](cmd_exec, execu);
}

int valid_execute(char *osdb, struct cmdi_execu *cmd_exec) {
    // strcpy(cmd_exec->space_str, osdb);
    return 0x00;
}

// execute

static int metho_echo(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **param) {
printf("hand metho echo.\n");
    quote_decode(param[EPARA_PARA_STR]);
    if (echo_metho_bzl(sresp, osdb, param[EPARA_PARA_STR])) {
        strcpy((char *)sresp->sebuf, "Can not find method ! ");
        *(sresp->colen) = strlen((char *)sresp->sebuf);
        return -1;
    }
    return 0x00;
}

static int metho_creat(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **param) {
    char clang_txt[LARGE_TEXT_SIZE];
printf("hand metho creat.\n");
    MKZERO(clang_txt);
    if (comp_metho_bzl(clang_txt, osdb, param[EPARA_CLAS_METH])) {
        strcpy((char *)sresp->sebuf, "Create method error! ");
        *(sresp->colen) = strlen((char *)sresp->sebuf);
        return -1;
    }
//
    if (hcrea_metho_bzl(hando, handa, clang_txt, osdb, param[EPARA_CLAS_METH])) {
        strcpy((char *)sresp->sebuf, "Compile method error! ");
        *(sresp->colen) = strlen((char *)sresp->sebuf);
        return -1;
    }
    strcpy((char *)sresp->sebuf, "Create method OK! ");
    *(sresp->colen) = strlen((char *)sresp->sebuf);
    //
    return 0x00;
}

static int metho_drop(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **param) {
printf("hand metho drop.\n");
    quote_decode(param[EPARA_PARA_STR]);
    if (dele_metho_bzl(osdb, param[EPARA_PARA_STR])) {
        strcpy((char *)sresp->sebuf, "Drop method error! ");
        *(sresp->colen) = strlen((char *)sresp->sebuf);
        return -1;
    }
    //
    strcpy((char *)sresp->sebuf, "Drop method OK! ");
    *(sresp->colen) = strlen((char *)sresp->sebuf);
    return 0x00;
}

static int metho_reload(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **param) {
    char clang_txt[LARGE_TEXT_SIZE];
printf("hand metho reload.\n");
    MKZERO(clang_txt);
    quote_decode(param[EPARA_PARA_STR]);
    if (load_metho_bzl(clang_txt, osdb, param[EPARA_PARA_STR])) {
        strcpy((char *)sresp->sebuf, "Load method error! ");
        *(sresp->colen) = strlen((char *)sresp->sebuf);
        return -1;
    }
/*
    if (hload_metho_bzl(dlsth, clang_txt, osdb, param[EPARA_PARA_STR])) {
        strcpy(execu_str, "Compile method error! ");
        return -1;
    }
*/
    strcpy((char *)sresp->sebuf, "Reload method OK! ");
    *(sresp->colen) = strlen((char *)sresp->sebuf);
    //
    return 0x00;
}

static int metho_null(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **param) {
printf("hand metho null.\n");
    return -1;
}

static int (*metho_execu_tab[])(prod_data *, hand_data *, hand_data *, char *, char **) = {
    metho_echo,
    metho_creat,
    metho_drop,
    metho_null,
    metho_reload
};

//

static int class_echo(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **param) {
printf("hand class echo.\n");
    quote_decode(param[EPARA_PARA_STR]);
    if (echo_class_bzl(sresp, osdb, param[EPARA_PARA_STR])) {
        strcpy((char *)sresp->sebuf, "Can not find class! ");
        *(sresp->colen) = strlen((char *)sresp->sebuf);
        return -1;
    }
printf("execu_str:%s\n", sresp->sebuf);
    return 0x00;
}

static int class_creat(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **param) {
    char clang_txt[LARGE_TEXT_SIZE];
printf("hand class creat.\n");
    MKZERO(clang_txt);
    if (comp_class_bzl(clang_txt, osdb, param[EPARA_CLAS_METH])) {
        strcpy((char *)sresp->sebuf, "Create class error! ");
        *(sresp->colen) = strlen((char *)sresp->sebuf);
        return -1;
    }
printf("hcrea_class_bzl.\n");
    if (hcrea_class_bzl(handa, clang_txt, osdb, param[EPARA_CLAS_METH])) {
        strcpy((char *)sresp->sebuf, "Compile class error!");
        *(sresp->colen) = strlen((char *)sresp->sebuf);
        return -1;
    }
//
    strcpy((char *)sresp->sebuf, "Create class OK! ");
    *(sresp->colen) = strlen((char *)sresp->sebuf);
    //
    return 0x00;
}

static int class_drop(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **param) {
printf("hand class drop.\n");
    quote_decode(param[EPARA_PARA_STR]);
    if (dele_class_bzl(osdb, param[EPARA_PARA_STR])) {
        strcpy((char *)sresp->sebuf, "Drop class error! ");
        *(sresp->colen) = strlen((char *)sresp->sebuf);
        return -1;
    }
    //
    strcpy((char *)sresp->sebuf, "Drop class OK! ");
    *(sresp->colen) = strlen((char *)sresp->sebuf);
    return 0x00;
}

static int class_integri(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **param) {
printf("hand class integri.\n");
    quote_decode(param[EPARA_PARA_STR]);
    int integri = class_integri_bzl(osdb, param[EPARA_PARA_STR]);
printf("integri:%d\n", integri);
    switch (integri) {
        case 0x00:
            strcpy((char *)sresp->sebuf, "Class integri error! ");
            break;
        case 0x01:
            strcpy((char *)sresp->sebuf, "Class integri pass! ");
            break;
        case -1:
            strcpy((char *)sresp->sebuf, "Get class info error! ");
            break;
    }
    *(sresp->colen) = strlen((char *)sresp->sebuf);
    //
    return 0x00;
}

static int class_reload(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **param) {
    char clang_txt[LARGE_TEXT_SIZE];
printf("hand metho reload.\n");
    MKZERO(clang_txt);
    quote_decode(param[EPARA_PARA_STR]);
    if (load_class_bzl(clang_txt, osdb, param[EPARA_PARA_STR])) {
        strcpy((char *)sresp->sebuf, "Load class error!");
        *(sresp->colen) = strlen((char *)sresp->sebuf);
        return -1;
    }
/*
    if (hload_class_bzl(dlsth, clang_txt, osdb, param[EPARA_PARA_STR])) {
        strcpy(execu_str, "Compile class error! ");
        return -1;
    }
*/
    strcpy((char *)sresp->sebuf, "Reload class OK! ");
    *(sresp->colen) = strlen((char *)sresp->sebuf);
    //
    return 0x00;
}

static int (*class_execu_tab[])(prod_data *, hand_data *, hand_data *, char *, char **) = {
    class_echo,
    class_creat,
    class_drop,
    class_integri,
    class_reload
};

int (**hand_execu_tab[])(prod_data *, hand_data *, hand_data *, char *, char **) = {
     metho_execu_tab,
     class_execu_tab
};