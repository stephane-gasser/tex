procedure movement(w: scaled; o: eightbits);
label
  10, 40, 45, 2, 1;
var
  mstate: smallnumber;
  p, q: halfword;
  k: integer;
begin
  q := getnode(3);
  mem[q + 1].int := w;
  mem[q + 2].int := dvioffset + dviptr;
  if o = 157 then
  begin
    mem[q].hh.rh := downptr;
    downptr := q;
  end
  else
  begin
    mem[q].hh.rh := rightptr;
    rightptr := q;
  end;
  {611:}
p := mem[q].hh.rh;
  mstate := 0;
  while p <> 0 do
  begin
    if mem[p + 1].int = w then
      {612:}
case mstate + mem[p].hh.lh
        of
        3, 4, 15, 16: if mem[p + 2].int < dvigone then
            goto 45
          else{613:}

          begin
            k := mem[p + 2].int - dvioffset;
            if k < 0 then
              k := k + dvibufsize;
            dvibuf[k] := dvibuf[k] + 5;
            mem[p].hh.lh := 1;
            goto 40;
          end{:613}
;
        5, 9, 11: if mem[p + 2].int < dvigone then
            goto 45
          else{614:}

          begin
            k := mem[p + 2].int - dvioffset;
            if k < 0 then
              k := k + dvibufsize;
            dvibuf[k] := dvibuf[k] + 10;
            mem[p].hh.lh := 2;
            goto 40;
          end{:614}
;
        1, 2, 8, 13: goto 40;
        others: end{:612}

    else
      case mstate + mem[p].hh.lh of
        1: mstate := 6;
        2: mstate := 12;
        8, 13: goto 45;
        others: end;
    p := mem[p].hh.rh;
  end;
  45:
  {:611}
;
  {610:}
mem[q].hh.lh := 3;
  if abs(w) >= 8388608 then
  begin
    begin
      dvibuf[dviptr] := o + 3;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    dvifour(w);
    goto 10;
  end;
  if abs(w) >= 32768 then
  begin
    begin
      dvibuf[dviptr] := o + 2;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    if w < 0 then
      w := w + 16777216;
    begin
      dvibuf[dviptr] := w div 65536;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    w := w mod 65536;
    goto 2;
  end;
  if abs(w) >= 128 then
  begin
    begin
      dvibuf[dviptr] := o + 1;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    if w < 0 then
      w := w + 65536;
    goto 2;
  end;
  begin
    dvibuf[dviptr] := o;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  if w < 0 then
    w := w + 256;
  goto 1;
  2:
  begin
    dvibuf[dviptr] := w div 256;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  1:
  begin
    dvibuf[dviptr] := w mod 256;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  goto 10{:610}
;
  40:
    {609:}
mem[q].hh.lh := mem[p].hh.lh;
  if mem[q].hh.lh = 1 then
  begin
    begin
      dvibuf[dviptr] := o + 4;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    while mem[q].hh.rh <> p do
    begin
      q := mem[q].hh.rh;
      case mem[q].hh.lh of
        3: mem[q].hh.lh := 5;
        4: mem[q].hh.lh := 6;
        others: end;
    end;
  end
  else
  begin
    begin
      dvibuf[dviptr] := o + 9;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    while mem[q].hh.rh <> p do
    begin
      q := mem[q].hh.rh;
      case mem[q].hh.lh of
        3: mem[q].hh.lh := 4;
        5: mem[q].hh.lh := 6;
        others: end;
    end;
  end{:609}
;
  10: ;
end;
