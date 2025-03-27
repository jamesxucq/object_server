#include "common_header.h"

#include "stri_utili.h"
#include "query_bzl.h"
#include "comp_bzl.h"
#include "inte_invok.h"
#include "conoda.h"

//
// :create(xxx, xx);

static int parse_creat(struct cmdi_invok *cmd_invo, char *invok) {
    char obje_ide[OBJE_LENGTH];
    char meth_str[METH_LENGTH];
    char para_str[PARAM_LENGTH];
    if (!split_creat(obje_ide, meth_str, para_str, invok)) return -1;
    //
    cmd_invo->invo_type = INVO_CREAT;
    strcpy(cmd_invo->obje_ident, obje_ide);
    strcpy(cmd_invo->meth_str, meth_str);
    printf("obje_ident:%s meth_str:%s para_str:%s\n", cmd_invo->obje_ident, cmd_invo->meth_str, para_str);
    invok_paras(cmd_invo->invok_line, cmd_invo->paras, para_str);
    //
    return 0x00;
}

// :drop(obje_id);

static int parse_drop(struct cmdi_invok *cmd_invo, char *invok) {
    char obje_ide[OBJE_LENGTH];
    char meth_str[METH_LENGTH];
    char para_str[PARAM_LENGTH];
    if (!split_metho(obje_ide, meth_str, para_str, invok)) return -1;
    //
    cmd_invo->invo_type = INVO_DROP;
    strcpy(cmd_invo->obje_ident, obje_ide);
    strcpy(cmd_invo->meth_str, meth_str);
    invok_paras(cmd_invo->invok_line, cmd_invo->paras, para_str);
    //
    return 0x00;
}

// :replace("new obje", obje_id);

static int parse_repla(struct cmdi_invok *cmd_invo, char *invok) {
    char obje_ide[OBJE_LENGTH];
    char meth_str[METH_LENGTH];
    char para_str[PARAM_LENGTH];
    if (!split_metho(obje_ide, meth_str, para_str, invok)) return -1;
    //
    cmd_invo->invo_type = INVO_REPLA;
    strcpy(cmd_invo->obje_ident, obje_ide);
    strcpy(cmd_invo->meth_str, meth_str);
    invok_paras(cmd_invo->invok_line, cmd_invo->paras, para_str);
    //
    return 0x00;
}

// :insert("new obje");

static int parse_inser(struct cmdi_invok *cmd_invo, char *invok) {
    char obje_ide[OBJE_LENGTH];
    char meth_str[METH_LENGTH];
    char para_str[PARAM_LENGTH];
    if (!split_metho(obje_ide, meth_str, para_str, invok)) return -1;
// printf("obje_ide:|%s| meth_str:|%s| para_str:|%s|\n", obje_ide, meth_str, para_str);
    //
    cmd_invo->invo_type = INVO_INSER;
    strcpy(cmd_invo->obje_ident, obje_ide);
    strcpy(cmd_invo->meth_str, meth_str);
    invok_paras(cmd_invo->invok_line, cmd_invo->paras, para_str);
    //
    return 0x00;
}

// :find(obje_id);

static int parse_find(struct cmdi_invok *cmd_invo, char *invok) {
    char obje_ide[OBJE_LENGTH];
    char meth_str[METH_LENGTH];
    char para_str[PARAM_LENGTH];
    if (!split_metho(obje_ide, meth_str, para_str, invok)) return -1;
    //
    cmd_invo->invo_type = INVO_FIND;
    strcpy(cmd_invo->obje_ident, obje_ide);
    strcpy(cmd_invo->meth_str, meth_str);
    invok_paras(cmd_invo->invok_line, cmd_invo->paras, para_str);
    //
    return 0x00;
}

// :each("metho(122)", obje:is_class("test"));
// :each("metho(122)", "obje:numb() > 0x00");

static int parse_invok(struct cmdi_invok *cmd_invo, char *invok) {
    char obje_ide[OBJE_LENGTH];
    char meth_str[METH_LENGTH];
    char para_str[PARAM_LENGTH];
    if (!split_metho(obje_ide, meth_str, para_str, invok)) return -1;
printf("invok:|%s|\n", invok);
printf("obje_ide:|%s| meth_str:|%s| para_str:|%s|\n", obje_ide, meth_str, para_str);
    //
    cmd_invo->invo_type = INVO_INVOK;
    strcpy(cmd_invo->obje_ident, obje_ide);
    strcpy(cmd_invo->meth_str, meth_str);
    invok_paras(cmd_invo->invok_line, cmd_invo->paras, para_str);
    //
    return 0x00;
}

// -1:error 0x00:creat 0x01:drop 0x02:replace 0x03:inser 0x04:find 0x05:invok

static int chk_invok_type(char *invok) {
    if (!is_creat_obje(invok)) return 0x00;
    else if (!is_drop_obje(invok)) return 0x01;
    else if (!is_repla_obje(invok)) return 0x02;
    else if (!is_inser_obje(invok)) return 0x03;
    else if (!is_find_obje(invok)) return 0x04;
    else if (!is_obje_invok(invok)) return 0x05;
    return -1;
}

static int (*parse_invok_tab[])(struct cmdi_invok *, char *) = {
    parse_creat,
    parse_drop,
    parse_repla,
    parse_inser,
    parse_find,
    parse_invok
};

//

int parse_invoke(struct cmdi_invok *cmd_invo, char *invok) {
    printf("parse invok:|%s|\n", invok);
    int invok_type = chk_invok_type(invok);
    printf("invok_type:%d\n", invok_type);
    if (-1 == invok_type) return -1;
    return parse_invok_tab[invok_type](cmd_invo, invok);
}

int valid_invoke(char *osev_osdb, struct cmdi_invok *cmd_invo) {
    //
    return 0x00;
}

// invoke
// test:test(777, "first");
// test:test(333, "second") > mycon;

int creat_obje(prod_data *sresp, void *coval, char **paras) {
    struct contain *conta = (struct contain *) action_value(paras[IPARA_OBJE_IDEN], ((conoda *) coval)->conta_hm);
    if (!conta) {
printf("not find contain:%s!\n", paras[IPARA_OBJE_IDEN]);
        // strcpy(invok_str, "Can not find contain !");
        return -1;
    }
    //
    printf("invo_creat_bzl\n");
    int invo_value = invo_creat_bzl(conta, &((conoda *) coval)->hando, &((conoda *) coval)->rive, paras + IPARA_PARA_POS);
    if (invo_value) {
printf("create object error!\n");
        // char *last_str = lscpy(invok_str, "Create object error!");
        // lsprif(last_str, "invo_value:%d", invo_value);
        return -1;
    }
    //
    return 0x00;
}

// obje::drop(obje_id);
// obje::drop("xx()>0x00");

int drop_obje(prod_data *sresp, void *coval, char **paras) {
    struct contain *conta = (struct contain *) action_value(paras[IPARA_OBJE_IDEN], ((conoda *) coval)->conta_hm);
    if (!conta) {
printf("not found:%s\n", paras[IPARA_OBJE_IDEN]);
        // strcpy(invok_str, "Can not find contain ! ");
        return -1;
    }
    //
    printf("contain:%s\n", paras[IPARA_OBJE_IDEN]);
    int invo_value = invo_drop_bzl(conta, &((conoda *) coval)->hando, &((conoda *) coval)->rive, paras + IPARA_PARA_POS);
    if (invo_value) {
printf("drop object error!\n");
        // char *last_str = lscpy(invok_str, "Drop object error!");
        // lsprif(last_str, "invo_value:%d", invo_value);
        return -1;
    }
    //
    return 0x00;
}

// obje::replace("test:test(xx, dfa, adf)", obje_id);
// obje::replace("test:test(xx, dfa, adf)", "xx()>0x00");

int repla_obje(prod_data *sresp, void *coval, char **paras) {
    struct contain *conta = (struct contain *) action_value(paras[IPARA_OBJE_IDEN], ((conoda *) coval)->conta_hm);
    if (!conta) {
printf("not find contain !\n");
        // strcpy(invok_str, "Can not find contain ! ");
        return -1;
    }
    //
    int invo_value = invo_repla_bzl(conta, &((conoda *) coval)->handa, &((conoda *) coval)->rive, paras + IPARA_PARA_POS);
    if (invo_value) {
printf("replace object error!\n");
        // char *last_str = lscpy(invok_str, "Replace object error!");
        // lsprif(last_str, "invo_value:%d", invo_value);
        return -1;
    }
    //
    return 0x00;
}

// obje::insert("test:test(xx, dfa, adf)");

int inser_obje(prod_data *sresp, void *coval, char **paras) {
    struct contain *conta = (struct contain *) action_value(paras[IPARA_OBJE_IDEN], ((conoda *) coval)->conta_hm);
    if (!conta) {
printf("not find contain:%s!\n", paras[IPARA_OBJE_IDEN]);
        // strcpy(invok_str, "Can not find contain ! ");
        return -1;
    }
    //
    printf("invo_inser_bzl\n");
    int invo_value = invo_inser_bzl(conta, &((conoda *) coval)->handa, &((conoda *) coval)->rive, paras + IPARA_PARA_POS);
    if (invo_value) {
printf("insert object error!\n");
        // char *last_str = lscpy(invok_str, "Insert object error! ");
        // lsprif(last_str, "invo_value:%d", invo_value);
        return -1;
    }
    //
    return 0x00;
}

// obje:find();
// obje::find("xx()>0x00");

int find_obje(prod_data *sresp, void *coval, char **paras) {
    struct contain *conta = (struct contain *) action_value(paras[IPARA_OBJE_IDEN], ((conoda *) coval)->conta_hm);
    if (!conta) {
printf("not find contain:%s!\n", paras[IPARA_OBJE_IDEN]);
        // strcpy(invok_str, "Can not find contain ! ");
        return -1;
    }
    //
    int invo_value = invo_find_bzl(sresp, conta, &((conoda *) coval)->handa, &((conoda *) coval)->rive, paras + IPARA_PARA_POS);
    if (invo_value) {
printf("find object error!\n");
        // char *last_str = lscpy(invok_str, "Find object error!");
        // lsprif(last_str, "invo_value:%d", invo_value);
        return -1;
    }
    //
    return 0x00;
}

// obje::each("metho(122)", obje:is_class("test"));
// obje::each("metho(122)", "obje:numb() > 0x00");

int each_invok(prod_data *sresp, void *coval, char **paras) {
    struct contain *conta = (struct contain *) action_value(paras[IPARA_OBJE_IDEN], ((conoda *) coval)->conta_hm);
    if (!conta) {
printf("not find contain:%s!\n", paras[IPARA_OBJE_IDEN]);
        // strcpy(invok_str, "Can not find contain ! ");
        return -1;
    }
    //
    int invo_value = invo_each_bzl(sresp, conta, &((conoda *) coval)->hando, &((conoda *) coval)->rive, paras + IPARA_PARA_POS);
    if (invo_value) {
printf("each invoke object error!\n");
        // char *last_str = lscpy(invok_str, "Each invoke object error!");
        // lsprif(last_str, "invo_value:%d", invo_value);
        return -1;
    }
    //
    return 0x00;
}

int (*hand_invok_tab[])(prod_data *, void *, char **) = {
    creat_obje,
    drop_obje,
    repla_obje,
    inser_obje,
    find_obje,
    each_invok
};
//
