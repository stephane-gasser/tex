procedure Initialize;
var
  {19:}
i: integer;
  {:19}
{163:}
k: integer;
  {:163}
{927:}
z: hyphpointer;{:927}

begin
  {8:}
{21:}
xchr[32] := ' ';
  xchr[33] := '!';
  xchr[34] := '"';
  xchr[35] := '#';
  xchr[36] := '$';
  xchr[37] := '%';
  xchr[38] := '&';
  xchr[39] := '''';
  xchr[40] := '(';
  xchr[41] := ')';
  xchr[42] := '*';
  xchr[43] := '+';
  xchr[44] := ',';
  xchr[45] := '-';
  xchr[46] := '.';
  xchr[47] := '/';
  xchr[48] := '0';
  xchr[49] := '1';
  xchr[50] := '2';
  xchr[51] := '3';
  xchr[52] := '4';
  xchr[53] := '5';
  xchr[54] := '6';
  xchr[55] := '7';
  xchr[56] := '8';
  xchr[57] := '9';
  xchr[58] := ':';
  xchr[59] := ';';
  xchr[60] := '<';
  xchr[61] := '=';
  xchr[62] := '>';
  xchr[63] := '?';
  xchr[64] := '@';
  xchr[65] := 'A';
  xchr[66] := 'B';
  xchr[67] := 'C';
  xchr[68] := 'D';
  xchr[69] := 'E';
  xchr[70] := 'F';
  xchr[71] := 'G';
  xchr[72] := 'H';
  xchr[73] := 'I';
  xchr[74] := 'J';
  xchr[75] := 'K';
  xchr[76] := 'L';
  xchr[77] := 'M';
  xchr[78] := 'N';
  xchr[79] := 'O';
  xchr[80] := 'P';
  xchr[81] := 'Q';
  xchr[82] := 'R';
  xchr[83] := 'S';
  xchr[84] := 'T';
  xchr[85] := 'U';
  xchr[86] := 'V';
  xchr[87] := 'W';
  xchr[88] := 'X';
  xchr[89] := 'Y';
  xchr[90] := 'Z';
  xchr[91] := '[';
  xchr[92] := '\';
  xchr[93] := ']';
  xchr[94] := '^';
  xchr[95] := '_';
  xchr[96] := '`';
  xchr[97] := 'a';
  xchr[98] := 'b';
  xchr[99] := 'c';
  xchr[100] := 'd';
  xchr[101] := 'e';
  xchr[102] := 'f';
  xchr[103] := 'g';
  xchr[104] := 'h';
  xchr[105] := 'i';
  xchr[106] := 'j';
  xchr[107] := 'k';
  xchr[108] := 'l';
  xchr[109] := 'm';
  xchr[110] := 'n';
  xchr[111] := 'o';
  xchr[112] := 'p';
  xchr[113] := 'q';
  xchr[114] := 'r';
  xchr[115] := 's';
  xchr[116] := 't';
  xchr[117] := 'u';
  xchr[118] := 'v';
  xchr[119] := 'w';
  xchr[120] := 'x';
  xchr[121] := 'y';
  xchr[122] := 'z';
  xchr[123] := '{';
  xchr[124] := '|';
  xchr[125] := '}
';
  xchr[126] := '~';
  {:21}
{23:}
for i := 0 to 31 do
    xchr[i] := ' ';
  for i := 127 to 255 do
    xchr[i] := ' ';
  {:23}
{24:}
for i := 0 to 255 do
    xord[chr(i)] := 127;
  for i := 128 to 255 do
    xord[xchr[i]] := i;
  for i := 0 to 126 do
    xord[xchr[i]] := i;
  {:24}
{74:}
interaction := 3;
  {:74}
{77:}
deletionsallowed := true;
  setboxallowed := true;
  errorcount := 0;
  {:77}
{80:}
helpptr := 0;
  useerrhelp := false;
  {:80}
{97:}
interrupt := 0;
  OKtointerrupt := true;
  {:97}
{166:}
{wasmemend:=memmin;waslomax:=memmin;
washimin:=memmax;panicking:=false;}
{:166}
{215:}
nestptr := 0;
  maxneststack := 0;
  curlist.modefield := 1;
  curlist.headfield := 29999;
  curlist.tailfield := 29999;
  curlist.auxfield.int := -65536000;
  curlist.mlfield := 0;
  curlist.pgfield := 0;
  shownmode := 0;
  {991:}
pagecontents := 0;
  pagetail := 29998;
  mem[29998].hh.rh := 0;
  lastglue := 65535;
  lastpenalty := 0;
  lastkern := 0;
  pagesofar[7] := 0;
  pagemaxdepth := 0{:991}
;
  {:215}
{254:}
for k := 5263 to 6106 do
    xeqlevel[k] := 1;
  {:254}
{257:}
nonewcontrolsequence := true;
  hash[514].lh := 0;
  hash[514].rh := 0;
  for k := 515 to 2880 do
    hash[k] := hash[514];
  {:257}
{272:}
saveptr := 0;
  curlevel := 1;
  curgroup := 0;
  curboundary := 0;
  maxsavestack := 0;
  {:272}
{287:}
magset := 0;
  {:287}
{383:}
curmark[0] := 0;
  curmark[1] := 0;
  curmark[2] := 0;
  curmark[3] := 0;
  curmark[4] := 0;
  {:383}
{439:}
curval := 0;
  curvallevel := 0;
  radix := 0;
  curorder := 0;
  {:439}
{481:}
for k := 0 to 16 do
    readopen[k] := 2;
  {:481}
{490:}
condptr := 0;
  iflimit := 0;
  curif := 0;
  ifline := 0;
  {:490}
{521:}
TEXformatdefault := 'TeXformats:plain.fmt';
  {:521}
{551:}
for k := 0 to fontmax do
    fontused[k] := false;
  {:551}
{556:}
nullcharacter.b0 := 0;
  nullcharacter.b1 := 0;
  nullcharacter.b2 := 0;
  nullcharacter.b3 := 0;
  {:556}
{593:}
totalpages := 0;
  maxv := 0;
  maxh := 0;
  maxpush := 0;
  lastbop := -1;
  doingleaders := false;
  deadcycles := 0;
  curs := -1;
  {:593}
{596:}
halfbuf := dvibufsize div 2;
  dvilimit := dvibufsize;
  dviptr := 0;
  dvioffset := 0;
  dvigone := 0;
  {:596}
{606:}
downptr := 0;
  rightptr := 0;
  {:606}
{648:}
adjusttail := 0;
  lastbadness := 0;
  {:648}
{662:}
packbeginline := 0;
  {:662}
{685:}
emptyfield.rh := 0;
  emptyfield.lh := 0;
  nulldelimiter.b0 := 0;
  nulldelimiter.b1 := 0;
  nulldelimiter.b2 := 0;
  nulldelimiter.b3 := 0;
  {:685}
{771:}
alignptr := 0;
  curalign := 0;
  curspan := 0;
  curloop := 0;
  curhead := 0;
  curtail := 0;
  {:771}
{928:}
for z := 0 to 307 do
  begin
    hyphword[z] := 0;
    hyphlist[z] := 0;
  end;
  hyphcount := 0;
  {:928}
{990:}
outputactive := false;
  insertpenalties := 0;
  {:990}
{1033:}
ligaturepresent := false;
  cancelboundary := false;
  lfthit := false;
  rthit := false;
  insdisc := false;
  {:1033}
{1267:}
aftertoken := 0;
  {:1267}
{1282:}
longhelpseen := false;
  {:1282}
{1300:}
formatident := 0;
  {:1300}
{1343:}
for k := 0 to 17 do
    writeopen[k] := false;
  {:1343}
{164:}
for k := 1 to 19 do
    mem[k].int := 0;
  k := 0;
  while k <= 19 do
  begin
    mem[k].hh.rh := 1;
    mem[k].hh.b0 := 0;
    mem[k].hh.b1 := 0;
    k := k + 4;
  end;
  mem[6].int := 65536;
  mem[4].hh.b0 := 1;
  mem[10].int := 65536;
  mem[8].hh.b0 := 2;
  mem[14].int := 65536;
  mem[12].hh.b0 := 1;
  mem[15].int := 65536;
  mem[12].hh.b1 := 1;
  mem[18].int := -65536;
  mem[16].hh.b0 := 1;
  rover := 20;
  mem[rover].hh.rh := 65535;
  mem[rover].hh.lh := 1000;
  mem[rover + 1].hh.lh := rover;
  mem[rover + 1].hh.rh := rover;
  lomemmax := rover + 1000;
  mem[lomemmax].hh.rh := 0;
  mem[lomemmax].hh.lh := 0;
  for k := 29987 to 30000 do
    mem[k] := mem[lomemmax];
  {790:}
mem[29990].hh.lh := 6714;
  {:790}
{797:}
mem[29991].hh.rh := 256;
  mem[29991].hh.lh := 0;
  {:797}
{820:}
mem[29993].hh.b0 := 1;
  mem[29994].hh.lh := 65535;
  mem[29993].hh.b1 := 0;
  {:820}
{981:}
mem[30000].hh.b1 := 255;
  mem[30000].hh.b0 := 1;
  mem[30000].hh.rh := 30000;
  {:981}
{988:}
mem[29998].hh.b0 := 10;
  mem[29998].hh.b1 := 0;
  {:988}
;
  avail := 0;
  memend := 30000;
  himemmin := 29987;
  varused := 20;
  dynused := 14;
  {:164}
{222:}
eqtb[2881].hh.b0 := 101;
  eqtb[2881].hh.rh := 0;
  eqtb[2881].hh.b1 := 0;
  for k := 1 to 2880 do
    eqtb[k] := eqtb[2881];
  {:222}
{228:}
eqtb[2882].hh.rh := 0;
  eqtb[2882].hh.b1 := 1;
  eqtb[2882].hh.b0 := 117;
  for k := 2883 to 3411 do
    eqtb[k] := eqtb[2882];
  mem[0].hh.rh := mem[0].hh.rh + 530;
  {:228}
{232:}
eqtb[3412].hh.rh := 0;
  eqtb[3412].hh.b0 := 118;
  eqtb[3412].hh.b1 := 1;
  for k := 3413 to 3677 do
    eqtb[k] := eqtb[2881];
  eqtb[3678].hh.rh := 0;
  eqtb[3678].hh.b0 := 119;
  eqtb[3678].hh.b1 := 1;
  for k := 3679 to 3933 do
    eqtb[k] := eqtb[3678];
  eqtb[3934].hh.rh := 0;
  eqtb[3934].hh.b0 := 120;
  eqtb[3934].hh.b1 := 1;
  for k := 3935 to 3982 do
    eqtb[k] := eqtb[3934];
  eqtb[3983].hh.rh := 0;
  eqtb[3983].hh.b0 := 120;
  eqtb[3983].hh.b1 := 1;
  for k := 3984 to 5262 do
    eqtb[k] := eqtb[3983];
  for k := 0 to 255 do
  begin
    eqtb[3983 + k].hh.rh := 12;
    eqtb[5007 + k].hh.rh := k + 0;
    eqtb[4751 + k].hh.rh := 1000;
  end;
  eqtb[3996].hh.rh := 5;
  eqtb[4015].hh.rh := 10;
  eqtb[4075].hh.rh := 0;
  eqtb[4020].hh.rh := 14;
  eqtb[4110].hh.rh := 15;
  eqtb[3983].hh.rh := 9;
  for k := 48 to 57 do
    eqtb[5007 + k].hh.rh := k + 28672;
  for k := 65 to 90 do
  begin
    eqtb[3983 + k].hh.rh := 11;
    eqtb[3983 + k + 32].hh.rh := 11;
    eqtb[5007 + k].hh.rh := k + 28928;
    eqtb[5007 + k + 32].hh.rh := k + 28960;
    eqtb[4239 + k].hh.rh := k + 32;
    eqtb[4239 + k + 32].hh.rh := k + 32;
    eqtb[4495 + k].hh.rh := k;
    eqtb[4495 + k + 32].hh.rh := k;
    eqtb[4751 + k].hh.rh := 999;
  end;
  {:232}
{240:}
for k := 5263 to 5573 do
    eqtb[k].int := 0;
  eqtb[5280].int := 1000;
  eqtb[5264].int := 10000;
  eqtb[5304].int := 1;
  eqtb[5303].int := 25;
  eqtb[5308].int := 92;
  eqtb[5311].int := 13;
  for k := 0 to 255 do
    eqtb[5574 + k].int := -1;
  eqtb[5620].int := 0;
  {:240}
{250:}
for k := 5830 to 6106 do
    eqtb[k].int := 0;
  {:250}
{258:}
hashused := 2614;
  cscount := 0;
  eqtb[2623].hh.b0 := 116;
  hash[2623].rh := 502;
  {:258}
{552:}
fontptr := 0;
  fmemptr := 7;
  fontname[0] := 800;
  fontarea[0] := 338;
  hyphenchar[0] := 45;
  skewchar[0] := -1;
  bcharlabel[0] := 0;
  fontbchar[0] := 256;
  fontfalsebchar[0] := 256;
  fontbc[0] := 1;
  fontec[0] := 0;
  fontsize[0] := 0;
  fontdsize[0] := 0;
  charbase[0] := 0;
  widthbase[0] := 0;
  heightbase[0] := 0;
  depthbase[0] := 0;
  italicbase[0] := 0;
  ligkernbase[0] := 0;
  kernbase[0] := 0;
  extenbase[0] := 0;
  fontglue[0] := 0;
  fontparams[0] := 7;
  parambase[0] := -1;
  for k := 0 to 6 do
    fontinfo[k].int := 0;
  {:552}
{946:}
for k := -trieopsize to trieopsize do
    trieophash[k] := 0;
  for k := 0 to 255 do
    trieused[k] := 0;
  trieopptr := 0;
  {:946}
{951:}
trienotready := true;
  triel[0] := 0;
  triec[0] := 0;
  trieptr := 0;
  {:951}
{1216:}
hash[2614].rh := 1189;
  {:1216}
{1301:}
formatident := 1256;
  {:1301}
{1369:}
hash[2622].rh := 1295;
  eqtb[2622].hh.b1 := 1;
  eqtb[2622].hh.b0 := 113;
  eqtb[2622].hh.rh := 0;{:1369}
{:8}

end;
