
#include <ctype.h>

#include "vilid_lv2pd_ite.h"

//
// <> angle brackets
// [] square brackets
// () parenthesis

int valid_lv2pd_conte(char *lv2_dec) {
    int angle_brake = 0x00;
    int squar_brake = 0x00;
    int parenth = 0x00;
    //
    if (!isalpha(lv2_dec[0x00]))
        return -1;
    char *detok = lv2_dec;
    //
    for (; detok[0x00]; ++detok) {
        // if( == detok[0x00])
        switch (detok[0x00]) {
            case '(':
                if (parenth || (0x01 != angle_brake))
                    return -1;
                ++parenth;
                break;
            case ')':
                --parenth;
                if (parenth || (0x01 != angle_brake))
                    return -1;
                break;
            case '[':
                if (squar_brake || (0x01 != angle_brake))
                    return -1;
                ++squar_brake;
                break;
            case ']':
                --squar_brake;
                if (squar_brake || (0x01 != angle_brake))
                    return -1;
                break;
            case '<':
                if (angle_brake) return -1;
                ++angle_brake;
                break;
            case '>':
                --angle_brake;
                if (angle_brake) return -1;
                break;
            default:
                break;
        }
    }
    //
    if (angle_brake || squar_brake || parenth)
        return -1;
    //
    return 0x00;
}

//

int valid_lv2pd_nonam(char *lv2_dec) {
    int angle_brake = 0x00;
    int squar_brake = 0x00;
    int parenth = 0x00;
    //
    if ('<' != lv2_dec[0x00])
        return -1;
    char *detok = lv2_dec;
    //
    for (; detok[0x00]; ++detok) {
        // if( == detok[0x00])
        switch (detok[0x00]) {
            case '(':
                if (parenth || (0x01 != angle_brake))
                    return -1;
                ++parenth;
                break;
            case ')':
                --parenth;
                if (parenth || (0x01 != angle_brake))
                    return -1;
                break;
            case '[':
                if (squar_brake || (0x01 != angle_brake))
                    return -1;
                ++squar_brake;
                break;
            case ']':
                --squar_brake;
                if (squar_brake || (0x01 != angle_brake))
                    return -1;
                break;
            case '<':
                if (angle_brake) return -1;
                ++angle_brake;
                break;
            case '>':
                --angle_brake;
                if (angle_brake) return -1;
                break;
            default:
                break;
        }
    }
    //
    if (angle_brake || squar_brake || parenth)
        return -1;
    //
    return 0x00;
}
