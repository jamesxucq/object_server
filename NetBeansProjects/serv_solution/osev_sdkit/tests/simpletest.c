
/*
 * File:   simpletest.c
 * Author: James Xu
 *
 * Created on 2022.10.8, AM 2:23
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Simple C Test Suite
 */
// user <[user_name char(32), password char(32), salt char(16), role_obid char(96)]>; // admin
// role <[role_type uint8, role_name char(32), priv_array char(1024)]>; // admin

// witi:witi("base_user_con", "user") > odb; // admin
// witi:witi("osev_user_con", "user") > odb; // admin
// witi:witi("roles_con", "role") > odb; // admin

// witi:witi("base_user_con", "user") > odb; // admin
// witi:witi("osev_user_con", "user") > odb; // admin
// witi:witi("roles_con", "role") > odb; // admin

// status(RELOAD_PRIVILE);

// privile:role(ADD, "admin");
// privile:role(GRANT, "admin", ALL_PRIVILE);
// privile:role(ADD, "rd3");
// privile:role(GRANT, "rd3", ALL_PRIVILE);
// privile:list(ROLE);
// privile:role(REVOKE, "rd3", OSEV, ALL_PRIVILE);
// privile:list(ROLE, "rd3");


// privile:user(ADD, "ssman", "123456");
// privile:list(USER);
// privile:user(DEL, "ssman");
// privile:list(USER, "xman");
// privile:user(ADD, "ssman", "123456");
// privile:user(GRANT, "xman", "admin");
// privile:user(REVOKE, "xman", "admin");

// odb:privile:role(ADD, "rdt");
// odb:privile:role(GRANT, "rd3", "todb", ALL_PRIVILE);
// odb:privile:role(GRANT, "rd3", "odb:containe", ALL_PRIVILE);
// odb:privile:role(GRANT, "rd3", "odb:2p", ALL_PRIVILE);
// odb:privile:role(GRANT, "develop", "todb", ALL_PRIVILE);

// conne osvp://xman:******@192.168.0.127:8848/
// conne osvp://192.168.0.127:8848/?uname=xman&paswd=123456
// conne osvp://192.168.0.127:8848/todb?uname=xman&paswd=123456
/*
    "osvp://10.0.0.103:8848/?uname=james&paswd=123456";
    "osvp://10.0.0.103:8848 ";
    "osvp://10.0.0.103:8848/ ";
    "osvp://10.0.0.103:8848/ osev ";
    "osvp://10.0.0.103:8848/ xxdb ";
    "osvp://10.0.0.103:8848/ xxdb ?uname=james&paswd=123456";
    "osvp://10.0.0.103:8848/ osev ? uname=james&paswd=123456";
    "osvp://10.0.0.103:8848?uname=james&paswd=123456";
 */
// conne osvp://192.168.0.127:8848/?uname=xman&paswd=123456
// conne osvp://192.168.0.127:8848/?uname=saman&paswd=123456

// status() | kits:format(XML);


// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
// 0 1 2 3 4 5 6 7 8 9 a  b  c  d  e  f  10           
//         8 4 2 1

// odb:privile:list(ROLE) | kits:format(XML);
// odb:privile:list(ROLE, dvxxx) | kits:format(XML);
// odb:privile:role(GRANT, "dvxxx", "todb", ALL_PRIVILE);
// odb:status(LIST) | kits:format(XML);
// odb:status(SET_RUN_LEVEL, "34p");

// odb:privile:user(GRANT, "dev3", "dvxxx");
// status(RELOAD_PRIVILE);
// odb:privile:role(GRANT, dvxxx, earth, ALL_PRIVILE);

// odb:privile:list(ROLE, dvxxx) | kits:format(XML);
// odb:privile:role(REVOKE, dvxxx, xodb, ALL_PRIVILE);

// odb:privile:list(ROLE, dvxxx) | kits:format(XML);
// odb:privile:role(REVOKE, dvxxx, todb, ALL_PRIVILE);
// odb:privile:role(GRANT, dvxxx, todb, ALL_PRIVILE);
// odb:status(SET_RUN_LEVEL, "12p");
// odb:status(SET_RUN_LEVEL, "34p");

// odb:privile:role(ADD, "dev12p");
// odb:privile:role(GRANT, "dev12p", "odb:12p", ALL_PRIVILE);