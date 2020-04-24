#include "storefmtfile.h"
void storefmtfile(void)
label
  41, 42, 31, 32;
var
  j, k, l: integer;
  p, q: halfword;
  x: integer;
  w: fourquarters;
begin
  {1304:}
if saveptr <> 0 then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(1257);
    end;
    begin
      helpptr := 1;
      helpline[0] := 1258;
    end;
    begin
      if interaction = 3 then
        interaction := 2;
      if logopened then
        error;
      {if interaction>0 then debughelp;}
history := 3;
      jumpout;
    end;
  end{:1304}
;
  {1328:}
selector := 21;
  print(1271);
  print(jobname);
  printchar(32);
  printint(eqtb[5286].int);
  printchar(46);
  printint(eqtb[5285].int);
  printchar(46);
  printint(eqtb[5284].int);
  printchar(41);
  if interaction = 0 then
    selector := 18
  else
    selector := 19;
  begin
    if poolptr + 1 > poolsize then
      overflow(257, poolsize - initpoolptr);
  end;
  formatident := makestring;
  packjobname(785);
  while not wopenout(fmtfile) do
    promptfilename(1272, 785);
  printnl(1273);
  slowprint(wmakenamestring(fmtfile));
  begin
    strptr := strptr - 1;
    poolptr := strstart[strptr];
  end;
  printnl(338);
  slowprint(formatident){:1328}
;{1307:}

  begin
    fmtfile^.int := 117275187;
    put(fmtfile);
  end;
  begin
    fmtfile^.int := 0;
    put(fmtfile);
  end;
  begin
    fmtfile^.int := 30000;
    put(fmtfile);
  end;
  begin
    fmtfile^.int := 6106;
    put(fmtfile);
  end;
  begin
    fmtfile^.int := 1777;
    put(fmtfile);
  end;
  begin
    fmtfile^.int := 307;
    put(fmtfile);
  end{:1307}
;
  {1309:}
begin
    fmtfile^.int := poolptr;
    put(fmtfile);
  end;
  begin
    fmtfile^.int := strptr;
    put(fmtfile);
  end;
  for k := 0 to strptr do
  begin
    fmtfile^.int := strstart[k];
    put(fmtfile);
  end;
  k := 0;
  while k + 4 < poolptr do
  begin
    w.b0 := strpool[k] + 0;
    w.b1 := strpool[k + 1] + 0;
    w.b2 := strpool[k + 2] + 0;
    w.b3 := strpool[k + 3] + 0;
    begin
      fmtfile^.qqqq := w;
      put(fmtfile);
    end;
    k := k + 4;
  end;
  k := poolptr - 4;
  w.b0 := strpool[k] + 0;
  w.b1 := strpool[k + 1] + 0;
  w.b2 := strpool[k + 2] + 0;
  w.b3 := strpool[k + 3] + 0;
  begin
    fmtfile^.qqqq := w;
    put(fmtfile);
  end;
  println;
  printint(strptr);
  print(1259);
  printint(poolptr){:1309}
;
  {1311:}
sortavail;
  varused := 0;
  begin
    fmtfile^.int := lomemmax;
    put(fmtfile);
  end;
  begin
    fmtfile^.int := rover;
    put(fmtfile);
  end;
  p := 0;
  q := rover;
  x := 0;
  repeat
    for k := p to q + 1 do
    begin
      fmtfile^ := mem[k];
      put(fmtfile);
    end;
    x := x + q + 2 - p;
    varused := varused + q - p;
    p := q + mem[q].hh.lh;
    q := mem[q + 1].hh.rh;
  until q = rover;
  varused := varused + lomemmax - p;
  dynused := memend + 1 - himemmin;
  for k := p to lomemmax do
  begin
    fmtfile^ := mem[k];
    put(fmtfile);
  end;
  x := x + lomemmax + 1 - p;
  begin
    fmtfile^.int := himemmin;
    put(fmtfile);
  end;
  begin
    fmtfile^.int := avail;
    put(fmtfile);
  end;
  for k := himemmin to memend do
  begin
    fmtfile^ := mem[k];
    put(fmtfile);
  end;
  x := x + memend + 1 - himemmin;
  p := avail;
  while p <> 0 do
  begin
    dynused := dynused - 1;
    p := mem[p].hh.rh;
  end;
  begin
    fmtfile^.int := varused;
    put(fmtfile);
  end;
  begin
    fmtfile^.int := dynused;
    put(fmtfile);
  end;
  println;
  printint(x);
  print(1260);
  printint(varused);
  printchar(38);
  printint(dynused){:1311}
;
  {1313:}
{1315:}
k := 1;
  repeat
    j := k;
    while j < 5262 do
    begin
      if (eqtb[j].hh.rh = eqtb[j + 1].hh.rh) and (eqtb[j].hh.b0 = eqtb[j + 1].hh.b0) and (eqtb[j].hh.b1 = eqtb[j + 1].hh.b1) then
        goto 41;
      j := j + 1;
    end;
    l := 5263;
    goto 31;
    41:
      j := j + 1;
    l := j;
    while j < 5262 do
    begin
      if (eqtb[j].hh.rh <> eqtb[j + 1].hh.rh) or (eqtb[j].hh.b0 <> eqtb[j + 1].hh.b0) or (eqtb[j].hh.b1 <> eqtb[j + 1].hh.b1) then
        goto 31;
      j := j + 1;
    end;
    31:
    begin
      fmtfile^.int := l - k;
      put(fmtfile);
    end;
    while k < l do
    begin
      begin
        fmtfile^ := eqtb[k];
        put(fmtfile);
      end;
      k := k + 1;
    end;
    k := j + 1;
    begin
      fmtfile^.int := k - l;
      put(fmtfile);
    end;
  until k = 5263{:1315}
;
  {1316:}
repeat
    j := k;
    while j < 6106 do
    begin
      if eqtb[j].int = eqtb[j + 1].int then
        goto 42;
      j := j + 1;
    end;
    l := 6107;
    goto 32;
    42:
      j := j + 1;
    l := j;
    while j < 6106 do
    begin
      if eqtb[j].int <> eqtb[j + 1].int then
        goto 32;
      j := j + 1;
    end;
    32:
    begin
      fmtfile^.int := l - k;
      put(fmtfile);
    end;
    while k < l do
    begin
      begin
        fmtfile^ := eqtb[k];
        put(fmtfile);
      end;
      k := k + 1;
    end;
    k := j + 1;
    begin
      fmtfile^.int := k - l;
      put(fmtfile);
    end;
  until k > 6106{:1316}
;
  begin
    fmtfile^.int := parloc;
    put(fmtfile);
  end;
  begin
    fmtfile^.int := writeloc;
    put(fmtfile);
  end;
  {1318:}
begin
    fmtfile^.int := hashused;
    put(fmtfile);
  end;
  cscount := 2613 - hashused;
  for p := 514 to hashused do
    if hash[p].rh <> 0 then
    begin
      begin
        fmtfile^.int := p;
        put(fmtfile);
      end;
      begin
        fmtfile^.hh := hash[p];
        put(fmtfile);
      end;
      cscount := cscount + 1;
    end;
  for p := hashused + 1 to 2880 do
  begin
    fmtfile^.hh := hash[p];
    put(fmtfile);
  end;
  begin
    fmtfile^.int := cscount;
    put(fmtfile);
  end;
  println;
  printint(cscount);
  print(1261){:1318}
{:1313}
;
  {1320:}
begin
    fmtfile^.int := fmemptr;
    put(fmtfile);
  end;
  for k := 0 to fmemptr - 1 do
  begin
    fmtfile^ := fontinfo[k];
    put(fmtfile);
  end;
  begin
    fmtfile^.int := fontptr;
    put(fmtfile);
  end;
  for k := 0 to fontptr do{1322:}

  begin
    begin
      fmtfile^.qqqq := fontcheck[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := fontsize[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := fontdsize[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := fontparams[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := hyphenchar[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := skewchar[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := fontname[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := fontarea[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := fontbc[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := fontec[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := charbase[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := widthbase[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := heightbase[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := depthbase[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := italicbase[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := ligkernbase[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := kernbase[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := extenbase[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := parambase[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := fontglue[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := bcharlabel[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := fontbchar[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := fontfalsebchar[k];
      put(fmtfile);
    end;
    printnl(1264);
    printesc(hash[2624 + k].rh);
    printchar(61);
    printfilename(fontname[k], fontarea[k], 338);
    if fontsize[k] <> fontdsize[k] then
    begin
      print(741);
      printscaled(fontsize[k]);
      print(397);
    end;
  end{:1322}
;
  println;
  printint(fmemptr - 7);
  print(1262);
  printint(fontptr - 0);
  print(1263);
  if fontptr <> 1 then
    printchar(115){:1320}
;
  {1324:}
begin
    fmtfile^.int := hyphcount;
    put(fmtfile);
  end;
  for k := 0 to 307 do
    if hyphword[k] <> 0 then
    begin
      begin
        fmtfile^.int := k;
        put(fmtfile);
      end;
      begin
        fmtfile^.int := hyphword[k];
        put(fmtfile);
      end;
      begin
        fmtfile^.int := hyphlist[k];
        put(fmtfile);
      end;
    end;
  println;
  printint(hyphcount);
  print(1265);
  if hyphcount <> 1 then
    printchar(115);
  if trienotready then
    inittrie;
  begin
    fmtfile^.int := triemax;
    put(fmtfile);
  end;
  for k := 0 to triemax do
  begin
    fmtfile^.hh := trie[k];
    put(fmtfile);
  end;
  begin
    fmtfile^.int := trieopptr;
    put(fmtfile);
  end;
  for k := 1 to trieopptr do
  begin
    begin
      fmtfile^.int := hyfdistance[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := hyfnum[k];
      put(fmtfile);
    end;
    begin
      fmtfile^.int := hyfnext[k];
      put(fmtfile);
    end;
  end;
  printnl(1266);
  printint(triemax);
  print(1267);
  printint(trieopptr);
  print(1268);
  if trieopptr <> 1 then
    printchar(115);
  print(1269);
  printint(trieopsize);
  for k := 255 downto 0 do
    if trieused[k] > 0 then
    begin
      printnl(799);
      printint(trieused[k] - 0);
      print(1270);
      printint(k);
      begin
        fmtfile^.int := k;
        put(fmtfile);
      end;
      begin
        fmtfile^.int := trieused[k] - 0;
        put(fmtfile);
      end;
    end{:1324}
;{1326:}

  begin
    fmtfile^.int := interaction;
    put(fmtfile);
  end;
  begin
    fmtfile^.int := formatident;
    put(fmtfile);
  end;
  begin
    fmtfile^.int := 69069;
    put(fmtfile);
  end;
  eqtb[5294].int := 0{:1326}
;
  {1329:}
wclose(fmtfile){:1329}
;
end;

