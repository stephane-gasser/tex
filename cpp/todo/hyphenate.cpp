#include "hyphenate.h"
void hyphenate(void)
label
  50, 30, 40, 41, 42, 45, 10;
var
  {901:}
i, j, l: 0..65;
  q, r, s: halfword;
  bchar: halfword;
  {:901}
{912:}
majortail, minortail: halfword;
  c: ASCIIcode;
  cloc: 0..63;
  rcount: integer;
  hyfnode: halfword;
  {:912}
{922:}
z: triepointer;
  v: integer;
  {:922}
{929:}
h: hyphpointer;
  k: strnumber;
  u: poolpointer;
  {:929}
begin
  {923:}
for j := 0 to hn do
    hyf[j] := 0;
  {930:}
h := hc[1];
  hn := hn + 1;
  hc[hn] := curlang;
  for j := 2 to hn do
    h := (h + h + hc[j]) mod 307;
  while true do
  begin
    {931:}
k := hyphword[h];
    if k = 0 then
      goto 45;
    if (strstart[k + 1] - strstart[k]) < hn then
      goto 45;
    if (strstart[k + 1] - strstart[k]) = hn then
    begin
      j := 1;
      u := strstart[k];
      repeat
        if strpool[u] < hc[j] then
          goto 45;
        if strpool[u] > hc[j] then
          goto 30;
        j := j + 1;
        u := u + 1;
      until j > hn;
      {932:}
s := hyphlist[h];
      while s <> 0 do
      begin
        hyf[mem[s].hh.lh] := 1;
        s := mem[s].hh.rh;
      end{:932}
;
      hn := hn - 1;
      goto 40;
    end;
    30:
    {:931}
;
    if h > 0 then
      h := h - 1
    else
      h := 307;
  end;
  45:
    hn := hn - 1{:930}
;
  if trie[curlang + 1].b1 <> curlang + 0 then
    goto 10;
  hc[0] := 0;
  hc[hn + 1] := 0;
  hc[hn + 2] := 256;
  for j := 0 to hn - rhyf + 1 do
  begin
    z := trie[curlang + 1].rh + hc[j];
    l := j;
    while hc[l] = trie[z].b1 - 0 do
    begin
      if trie[z].b0 <> 0 then{924:}

      begin
        v :=
          trie[z].b0;
        repeat
          v := v + opstart[curlang];
          i := l - hyfdistance[v];
          if hyfnum[v] > hyf[i] then
            hyf[i] := hyfnum[v];
          v := hyfnext[v];
        until v = 0;
      end{:924}
;
      l := l + 1;
      z := trie[z].rh + hc[l];
    end;
  end;
  40:
    for j := 0 to lhyf - 1 do
      hyf[j] := 0;
  for j := 0 to rhyf - 1 do
    hyf[hn - j] := 0{:923}
;
  {902:}
for j := lhyf to hn - rhyf do
    if odd(hyf[j]) then
      goto 41;
  goto 10;
  41:
  {:902}
;
  {903:}
q := mem[hb].hh.rh;
  mem[hb].hh.rh := 0;
  r := mem[ha].hh.rh;
  mem[ha].hh.rh := 0;
  bchar := hyfbchar;
  if (ha >= himemmin) then
    if mem[ha].hh.b0 <> hf then
      goto 42
    else
    begin
      initlist := ha;
      initlig := false;
      hu[0] := mem[ha].hh.b1 - 0;
    end
  else if mem[ha].hh.b0 = 6 then
    if mem[ha + 1].hh.b0 <> hf then
      goto 42
    else
    begin
      initlist := mem[ha + 1].hh.rh;
      initlig := true;
      initlft := (mem[ha].hh.b1 > 1);
      hu[0] := mem[ha + 1].hh.b1 - 0;
      if initlist = 0 then
        if initlft then
        begin
          hu[0] := 256;
          initlig := false;
        end;
      freenode(ha, 2);
    end
  else
  begin
    if not (r >= himemmin) then
      if mem[r].hh.b0 = 6 then
        if mem[r].hh.b1 > 1 then
          goto 42;
    j := 1;
    s := ha;
    initlist := 0;
    goto 50;
  end;
  s := curp;
  while mem[s].hh.rh <> ha do
    s := mem[s].hh.rh;
  j := 0;
  goto 50;
  42:
    s := ha;
  j := 0;
  hu[0] := 256;
  initlig := false;
  initlist := 0;
  50:
    flushnodelist(r);
  {913:}
repeat
    l := j;
    j := reconstitute(j, hn, bchar, hyfchar + 0) + 1;
    if hyphenpassed = 0 then
    begin
      mem[s].hh.rh := mem[29996].hh.rh;
      while mem[s].hh.rh > 0 do
        s := mem[s].hh.rh;
      if odd(hyf[j - 1]) then
      begin
        l := j;
        hyphenpassed := j - 1;
        mem[29996].hh.rh := 0;
      end;
    end;
    if hyphenpassed > 0 then
      {914:}
repeat
        r := getnode(2);
        mem[r].hh.rh := mem[29996].hh.rh;
        mem[r].hh.b0 := 7;
        majortail := r;
        rcount := 0;
        while mem[majortail].hh.rh > 0 do
        begin
          majortail := mem[majortail].hh.rh;
          rcount := rcount + 1;
        end;
        i := hyphenpassed;
        hyf[i] := 0;
        {915:}
minortail := 0;
        mem[r + 1].hh.lh := 0;
        hyfnode := newcharacter(hf, hyfchar);
        if hyfnode <> 0 then
        begin
          i := i + 1;
          c := hu[i];
          hu[i] := hyfchar;
          begin
            mem[hyfnode].hh.rh := avail;
            avail := hyfnode;{dynused:=dynused-1;}

          end;
        end;
        while l <= i do
        begin
          l := reconstitute(l, i, fontbchar[hf], 256) + 1;
          if mem[29996].hh.rh > 0 then
          begin
            if minortail = 0 then
              mem[r + 1].hh.lh := mem[29996].hh.rh
            else
              mem[minortail].hh.rh := mem[29996].hh.rh;
            minortail := mem[29996].hh.rh;
            while mem[minortail].hh.rh > 0 do
              minortail := mem[minortail].hh.rh;
          end;
        end;
        if hyfnode <> 0 then
        begin
          hu[i] := c;
          l := i;
          i := i - 1;
        end{:915}
;
        {916:}
minortail := 0;
        mem[r + 1].hh.rh := 0;
        cloc := 0;
        if bcharlabel[hf] <> 0 then
        begin
          l := l - 1;
          c := hu[l];
          cloc := l;
          hu[l] := 256;
        end;
        while l < j do
        begin
          repeat
            l := reconstitute(l, hn, bchar, 256) + 1;
            if cloc > 0 then
            begin
              hu[cloc] := c;
              cloc := 0;
            end;
            if mem[29996].hh.rh > 0 then
            begin
              if minortail = 0 then
                mem[r + 1].hh.rh := mem[29996].hh.rh
              else
                mem[minortail].hh.rh := mem[29996].hh.rh;
              minortail := mem[29996].hh.rh;
              while mem[minortail].hh.rh > 0 do
                minortail := mem[minortail].hh.rh;
            end;
          until l >= j;
          while l > j do{917:}

          begin
            j := reconstitute(j, hn, bchar, 256) + 1;
            mem[majortail].hh.rh := mem[29996].hh.rh;
            while mem[majortail].hh.rh > 0 do
            begin
              majortail := mem[majortail].hh.rh;
              rcount := rcount + 1;
            end;
          end{:917}
;
        end{:916}
;
        {918:}
if rcount > 127 then
        begin
          mem[s].hh.rh := mem[r].hh.rh;
          mem[r].hh.rh := 0;
          flushnodelist(r);
        end
        else
        begin
          mem[s].hh.rh := r;
          mem[r].hh.b1 := rcount;
        end;
        s := majortail{:918}
;
        hyphenpassed := j - 1;
        mem[29996].hh.rh := 0;
      until not odd(hyf[j - 1]){:914}
;
  until j > hn;
  mem[s].hh.rh := q{:913}
;
  flushlist(initlist){:903}
;
  10: ;
end;
