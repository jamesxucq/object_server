

// test<[xx=8 int, ax int], [cx int] auto, tst(xx), tpp(ax)>;
//
// test:test<(aa int)int> {xx = aa; return 0x00;}
// test:test<(aa int, bb int)int> {xx = bb; ax = aa; return 0x00;}
// test:tst<(yy int)int, (ex int)> {ex = yy; return 0x00;}

//
// appe <[xx=8 int, ax int], faa(xx, ax)>;
// appe:appe<(aa int)int> {xx = aa; return 0x00;}
// appe:faa<(yy int)int, (ex int, fx int)> {ex = yy; fx = -1; return 0x00;}

// xxen <[xx=8 int, ax int], [cx int] auto, test:[tst(cx), tpp(ax)], appe:faa(xx, ax), tst(ax)>;
// xxen:xxen<(aa int)int> {xx = aa; return 0x00;}
// xxen:tst<(yy int)int, (ex int)> {ex = yy; return 0x00;}