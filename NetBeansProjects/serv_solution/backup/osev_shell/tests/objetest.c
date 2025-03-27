// test<[xx=8 int, ax int], [cx int] auto, tst(xx), tpp(ax)>;
//
// test:test<(aa int)int> {xx = aa; return 0x00;}
// test:test<(aa int, bb int)int> {xx = bb; ax = aa; return 0x00;}

// test:tst<(yy int)int, (ex int)> {ex = yy; return 0x00;}

// rive:rive("tvtv", "test")>odb;
// test:test(11, 11) > tvtv;

// tvtv:search() | kits:pretty("oiii");

// tvtv:invoke("test:tst(33,55)", "db5dab4a32542f5901000000");
// tvtv:invoke("test:tst(55)");

// :echo("test", "ATTRIB|CONTENT");
// exte:echo("test");
// kits:echo("test")|kits:conve(GCC);
// odb:echo("test")|kits:conve(GCC);

// kits:echo("test")|kits:conve(GCC)|kits:save("test.cpp");
// odb:echo("test")|kits:conve(GCC)|kits:save("test.h");
// kits:echo("test")|kits:conve(GCC);


/*
 <?xml version="1.0" encoding="UTF-8"?><lv2p_metada><stora_id>fe739b30f77c335900000000</stora_id><lv2p_name>test</lv2p_name><lv2p_atti><version>1</version><integrality>true</integrality></lv2p_atti></lv2p_metada>
test<[xx=8 int, ax int], [cx int] auto, tst(xx), tpp(ax)>
test:test<(aa int)int> {xx = aa; return 0x00;}
test:test<(aa int, bb int)int> {xx = bb; ax = aa; return 0x00;}
test:tst<(yy int)int, (ex int)> {ex = yy; return 0x00;}

 */

// level-4+> witi:witi("tsta_con", "taat") > odb;