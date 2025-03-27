#include "commo_header.h"

#include "statu_inner_valu.h"

//

#define LIST_LVTP_OBJID     0x0001
#define LIST_LVTP_ATTRIB    0x0002
#define LIST_LVTP_INHERI    0x0004
#define LIST_LVTP_EXPAND    0x0010
#define LIST_LVTP_CONTEN    0x0020

static osv_str_t INVO_LIST_OBJID = osv_stri("OBJID");
static osv_str_t INVO_LIST_ATTRIB = osv_stri("ATTRIB");
static osv_str_t INVO_LIST_INHERI = osv_stri("INHERIT");
static osv_str_t INVO_LIST_EXPAND = osv_stri("EXPAND");
static osv_str_t INVO_LIST_CONTEN = osv_stri("CONTENT");

static inline unsigned int build_list_type(char *invo_type) {
    if (!strncmp(INVO_LIST_OBJID.data, invo_type, INVO_LIST_OBJID.slen))
        return LIST_LVTP_OBJID;
    else if (!strncmp(INVO_LIST_ATTRIB.data, invo_type, INVO_LIST_ATTRIB.slen))
        return LIST_LVTP_ATTRIB;
    else if (!strncmp(INVO_LIST_INHERI.data, invo_type, INVO_LIST_INHERI.slen))
        return LIST_LVTP_INHERI;
    else if (!strncmp(INVO_LIST_EXPAND.data, invo_type, INVO_LIST_EXPAND.slen))
        return LIST_LVTP_EXPAND;
    else if (!strncmp(INVO_LIST_CONTEN.data, invo_type, INVO_LIST_CONTEN.slen))
        return LIST_LVTP_CONTEN;
    //
    return 0x00;
}

// "OBJID | ATTRIB | INHERI | EXPAND | CONTENT"

static unsigned int invo_list_type(char *invo_type) {
    // OSEVPF("[FUNC]:invo_list_type.\n");
    if (!invo_type)
        return LIST_LVTP_OBJID | LIST_LVTP_ATTRIB | LIST_LVTP_INHERI
            | LIST_LVTP_EXPAND | LIST_LVTP_CONTEN;
    quote_decode(invo_type);
    //
    int ivalu = 0x00;
    invo_type = pass_blank(invo_type);
    // OSEVPF("invo_type:|%s|\n", invo_type);
    ivalu |= build_list_type(invo_type);
    while ((invo_type = strchr(invo_type, '|'))) {
        invo_type = pass_blank(++invo_type);
        // OSEVPF("invo_type:|%s|\n", invo_type);
        ivalu |= build_list_type(invo_type);
    }
    //
    return ivalu;
}

//

int csta_inner_inst(char **pamvp) {
    unsigned int list_valu;
    if (pamvp[0x00] && pamvp[0x01] && !pamvp[0x01]) {
        list_valu = invo_list_type((char *) pamvp[0x01]);
        sprintf(pamvp[0x01], "%uI", list_valu);
    }
    //
    return 0x00;
}

