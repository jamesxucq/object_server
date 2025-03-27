#include "commo_header.h"

#include "kcomm_header.h"
#include "authe_valid.h"


//

int filli_authe_valid(unsigned char *plai_valid, user_privi *uepriv) {
    OSEVPF("[FUNC]:filli_authe_valid\n");
    unsigned char ecb_key[KEY_LENGTH];
    produ_authen_key(ecb_key, uepriv->salt);
    //
    unsigned char password[PASWD_LENGTH];
    if (!crypto_decode_ecb(password, (unsigned char *) uepriv->password, ecb_key))
        return -1;
    sprintf((char *) plai_valid, "%s:%s", uepriv->user_name, password);
    OSEVPF("plai_valid:|%s|\n", plai_valid);
    //
    return 0x00;
}
