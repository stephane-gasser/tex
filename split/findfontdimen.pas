procedure findfontdimen(writing: boolean);
var
  f: internalfontnumber;
  n: integer;
begin
  scanint;
  n := curval;
  scanfontident;
  f := curval;
  if n <= 0 then
    curval := fmemptr
  else
  begin
    if writing and (n <= 4) and (n >= 2) and (fontglue[f] <> 0) then
    begin
      deleteglueref(fontglue[f]);
      fontglue[f] := 0;
    end;
    if n > fontparams[f] then
      if f < fontptr then
        curval := fmemptr
      else{580:}

      begin
        repeat
          if fmemptr = fontmemsize then
            overflow(823, fontmemsize);
          fontinfo[fmemptr].int := 0;
          fmemptr := fmemptr + 1;
          fontparams[f] := fontparams[f] + 1;
        until n = fontparams[f];
        curval := fmemptr - 1;
      end{:580}

    else
      curval := n + parambase[f];
  end;
  {579:}
if curval = fmemptr then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(801);
    end;
    printesc(hash[2624 + f].rh);
    print(819);
    printint(fontparams[f]);
    print(820);
    begin
      helpptr := 2;
      helpline[1] := 821;
      helpline[0] := 822;
    end;
    error;
  end{:579}
;
end;
