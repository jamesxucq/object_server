
#include "utlist.h"

#include "shap_entry.h"

//
#define APPE_NEW_RIVE(SHAP_DATA, ENTRY_LSTH, LINE_SIZE, ERRO_CODE) { \
    SHAP_DATA = (struct shap_list *) malloc(sizeof (struct shap_list)+LINE_SIZE); \
    if(!SHAP_DATA) return ERRO_CODE; \
    DL_APPEND((*ENTRY_LSTH), SHAP_DATA) \
}

//

/*
static int32 valid_data(FILE *fpiden, int32 isize) {
    if (fseek(fpiden, 0x00, SEEK_END)) return -1;
    off_t eose = ftell(fpiden);
    if (!eose) return -1;
    else if ((sizeof (struct entry_id)+isize) == eose) return 0x01;
    //
    return 0x00;
}
 */

uint32 load_entry(struct shap_list **entry_lsth, FILE *fpiden, int32 isize) {
    struct entry_id ident;
    //
    if (fseek(fpiden, 0x00, SEEK_SET)) return 0x01;
    if (0 >= fread(&ident, sizeof (struct entry_id), 0x01, fpiden))
        return 0x01;
    if(INVA_INDE_VALU == ident.next_sibli) return 0x00;
    //
    struct shap_list *shap_data;
    int line_size = sizeof (struct entry_id)+isize;
    for (; INVA_INDE_VALU != ident.next_sibli;) {
        APPE_NEW_RIVE(shap_data, entry_lsth, isize, 0x01)
        shap_data->einde = ident.next_sibli;
        //
        if (fseek(fpiden, line_size * ident.next_sibli, SEEK_SET))
            return 0x01;
        if (0 >= fread(&ident, sizeof (struct entry_id), 0x01, fpiden))
            return 0x01;
        if (0 >= fread(shap_data->idata, isize, 0x01, fpiden))
            return 0x01;
    }
    //
    return 0x00;
}

//

