function loadfmtfile: boolean;
label
  6666, 10;
var
  j, k: integer;
  p, q: halfword;
  x: integer;
  w: fourquarters;
begin
  {1308:}
x := fmtfile^.int;
  if x <> 117275187 then
    goto 6666;
  begin
    get(fmtfile);
    x := fmtfile^.int;
  end;
  if x <> 0 then
    goto 6666;
  begin
    get(fmtfile);
    x := fmtfile^.int;
  end;
  if x <> 30000 then
    goto 6666;
  begin
    get(fmtfile);
    x := fmtfile^.int;
  end;
  if x <> 6106 then
    goto 6666;
  begin
    get(fmtfile);
    x := fmtfile^.int;
  end;
  if x <> 1777 then
    goto 6666;
  begin
    get(fmtfile);
    x := fmtfile^.int;
  end;
  if x <> 307 then
    goto 6666{:1308}
;
  {1310:}
begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if x < 0 then
      goto 6666;
    if x > poolsize then
    begin
      ;
      writeln(termout, '---! Must increase the ', 'string pool size');
      goto 6666;
    end
    else
      poolptr := x;
  end;
  begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if x < 0 then
      goto 6666;
    if x > maxstrings then
    begin
      ;
      writeln(termout, '---! Must increase the ', 'max strings');
      goto 6666;
    end
    else
      strptr := x;
  end;
  for k := 0 to strptr do
  begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if (x < 0) or (x > poolptr) then
      goto 6666
    else
      strstart[k] := x;
  end;
  k := 0;
  while k + 4 < poolptr do
  begin
    begin
      get(fmtfile);
      w := fmtfile^.qqqq;
    end;
    strpool[k] := w.b0 - 0;
    strpool[k + 1] := w.b1 - 0;
    strpool[k + 2] := w.b2 - 0;
    strpool[k + 3] := w.b3 - 0;
    k := k + 4;
  end;
  k := poolptr - 4;
  begin
    get(fmtfile);
    w := fmtfile^.qqqq;
  end;
  strpool[k] := w.b0 - 0;
  strpool[k + 1] := w.b1 - 0;
  strpool[k + 2] := w.b2 - 0;
  strpool[k + 3] := w.b3 - 0;
  initstrptr := strptr;
  initpoolptr := poolptr{:1310}
;{1312:}

  begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if (x < 1019) or (x > 29986) then
      goto 6666
    else
      lomemmax := x;
  end;
  begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if (x < 20) or (x > lomemmax) then
      goto 6666
    else
      rover := x;
  end;
  p := 0;
  q := rover;
  repeat
    for k := p to q + 1 do
    begin
      get(fmtfile);
      mem[k] := fmtfile^;
    end;
    p := q + mem[q].hh.lh;
    if (p > lomemmax) or ((q >= mem[q + 1].hh.rh) and (mem[q + 1].hh.rh <> rover)) then
      goto6666;
    q := mem[q + 1].hh.rh;
  until q = rover;
  for k := p to lomemmax do
  begin
    get(fmtfile);
    mem[k] := fmtfile^;
  end;
  if memmin < -2 then
  begin
    p := mem[rover + 1].hh.lh;
    q := memmin + 1;
    mem[memmin].hh.rh := 0;
    mem[memmin].hh.lh := 0;
    mem[p + 1].hh.rh := q;
    mem[rover + 1].hh.lh := q;
    mem[q + 1].hh.rh := rover;
    mem[q + 1].hh.lh := p;
    mem[q].hh.rh := 65535;
    mem[q].hh.lh := -0 - q;
  end;
  begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if (x < lomemmax + 1) or (x > 29987) then
      goto 6666
    else
      himemmin := x;
  end;
  begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if (x < 0) or (x > 30000) then
      goto 6666
    else
      avail := x;
  end;
  memend := 30000;
  for k := himemmin to memend do
  begin
    get(fmtfile);
    mem[k] := fmtfile^;
  end;
  begin
    get(fmtfile);
    varused := fmtfile^.int;
  end;
  begin
    get(fmtfile);
    dynused := fmtfile^.int;
  end{:1312}
;
  {1314:}
{1317:}
k := 1;
  repeat
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if (x < 1) or (k + x > 6107) then
      goto 6666;
    for j := k to k + x - 1 do
    begin
      get(fmtfile);
      eqtb[j] := fmtfile^;
    end;
    k := k + x;
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if (x < 0) or (k + x > 6107) then
      goto 6666;
    for j := k to k + x - 1 do
      eqtb[j] := eqtb[k - 1];
    k := k + x;
  until k > 6106{:1317}
;
  begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if (x < 514) or (x > 2614) then
      goto 6666
    else
      parloc := x;
  end;
  partoken := 4095 + parloc;
  begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if (x < 514) or (x > 2614) then
      goto 6666
    else
      writeloc := x;
  end;
  {1319:}
begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if (x < 514) or (x > 2614) then
      goto 6666
    else
      hashused := x;
  end;
  p := 513;
  repeat
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < p + 1) or (x > hashused) then
        goto 6666
      else
        p := x;
    end;
    begin
      get(fmtfile);
      hash[p] := fmtfile^.hh;
    end;
  until p = hashused;
  for p := hashused + 1 to 2880 do
  begin
    get(fmtfile);
    hash[p] := fmtfile^.hh;
  end;
  begin
    get(fmtfile);
    cscount := fmtfile^.int;
  end{:1319}
{:1314}
;
  {1321:}
begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if x < 7 then
      goto 6666;
    if x > fontmemsize then
    begin
      ;
      writeln(termout, '---! Must increase the ', 'font mem size');
      goto 6666;
    end
    else
      fmemptr := x;
  end;
  for k := 0 to fmemptr - 1 do
  begin
    get(fmtfile);
    fontinfo[k] := fmtfile^;
  end;
  begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if x < 0 then
      goto 6666;
    if x > fontmax then
    begin
      ;
      writeln(termout, '---! Must increase the ', 'font max');
      goto 6666;
    end
    else
      fontptr := x;
  end;
  for k := 0 to fontptr do{1323:}

  begin
    begin
      get(fmtfile);
      fontcheck[k] := fmtfile^.qqqq;
    end;
    begin
      get(fmtfile);
      fontsize[k] := fmtfile^.int;
    end;
    begin
      get(fmtfile);
      fontdsize[k] := fmtfile^.int;
    end;
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 0) or (x > 65535) then
        goto 6666
      else
        fontparams[k] := x;
    end;
    begin
      get(fmtfile);
      hyphenchar[k] := fmtfile^.int;
    end;
    begin
      get(fmtfile);
      skewchar[k] := fmtfile^.int;
    end;
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 0) or (x > strptr) then
        goto 6666
      else
        fontname[k] := x;
    end;
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 0) or (x > strptr) then
        goto 6666
      else
        fontarea[k] := x;
    end;
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 0) or (x > 255) then
        goto 6666
      else
        fontbc[k] := x;
    end;
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 0) or (x > 255) then
        goto 6666
      else
        fontec[k] := x;
    end;
    begin
      get(fmtfile);
      charbase[k] := fmtfile^.int;
    end;
    begin
      get(fmtfile);
      widthbase[k] := fmtfile^.int;
    end;
    begin
      get(fmtfile);
      heightbase[k] := fmtfile^.int;
    end;
    begin
      get(fmtfile);
      depthbase[k] := fmtfile^.int;
    end;
    begin
      get(fmtfile);
      italicbase[k] := fmtfile^.int;
    end;
    begin
      get(fmtfile);
      ligkernbase[k] := fmtfile^.int;
    end;
    begin
      get(fmtfile);
      kernbase[k] := fmtfile^.int;
    end;
    begin
      get(fmtfile);
      extenbase[k] := fmtfile^.int;
    end;
    begin
      get(fmtfile);
      parambase[k] := fmtfile^.int;
    end;
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 0) or (x > lomemmax) then
        goto 6666
      else
        fontglue[k] := x;
    end;
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 0) or (x > fmemptr - 1) then
        goto 6666
      else
        bcharlabel[k] := x;
    end;
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 0) or (x > 256) then
        goto 6666
      else
        fontbchar[k] := x;
    end;
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 0) or (x > 256) then
        goto 6666
      else
        fontfalsebchar[k] := x;
    end;
  end{:1323}
{:1321}
;{1325:}

  begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if (x < 0) or (x > 307) then
      goto 6666
    else
      hyphcount := x;
  end;
  for k := 1 to hyphcount do
  begin
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 0) or (x > 307) then
        goto 6666
      else
        j := x;
    end;
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 0) or (x > strptr) then
        goto 6666
      else
        hyphword[j] := x;
    end;
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 0) or (x > 65535) then
        goto 6666
      else
        hyphlist[j] := x;
    end;
  end;
  begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if x < 0 then
      goto 6666;
    if x > triesize then
    begin
      ;
      writeln(termout, '---! Must increase the ', 'trie size');
      goto 6666;
    end
    else
      j := x;
  end;
  triemax := j;
  for k := 0 to j do
  begin
    get(fmtfile);
    trie[k] := fmtfile^.hh;
  end;
  begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if x < 0 then
      goto 6666;
    if x > trieopsize then
    begin
      ;
      writeln(termout, '---! Must increase the ', 'trie op size');
      goto 6666;
    end
    else
      j := x;
  end;
  trieopptr := j;
  for k := 1 to j do
  begin
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 0) or (x > 63) then
        goto 6666
      else
        hyfdistance[k] := x;
    end;
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 0) or (x > 63) then
        goto 6666
      else
        hyfnum[k] := x;
    end;
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 0) or (x > 255) then
        goto 6666
      else
        hyfnext[k] := x;
    end;
  end;
  for k := 0 to 255 do
    trieused[k] := 0;
  k := 256;
  while j > 0 do
  begin
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 0) or (x > k - 1) then
        goto 6666
      else
        k := x;
    end;
    begin
      begin
        get(fmtfile);
        x := fmtfile^.int;
      end;
      if (x < 1) or (x > j) then
        goto 6666
      else
        x := x;
    end;
    trieused[k] := x + 0;
    j := j - x;
    opstart[k] := j - 0;
  end;
  trienotready := false{:1325}
;
  {1327:}
begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if (x < 0) or (x > 3) then
      goto 6666
    else
      interaction := x;
  end;
  begin
    begin
      get(fmtfile);
      x := fmtfile^.int;
    end;
    if (x < 0) or (x > strptr) then
      goto 6666
    else
      formatident := x;
  end;
  begin
    get(fmtfile);
    x := fmtfile^.int;
  end;
  if (x <> 69069) or EOF(fmtfile) then
    goto 6666{:1327}
;
  loadfmtfile := true;
  goto 10;
  6666: ;
  writeln(termout, '(Fatal format file error; I''m stymied)');
  loadfmtfile := false;
  10: ;
end;
