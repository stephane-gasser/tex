procedure dvifour(x: integer);
begin
  if x >= 0 then
  begin
    dvibuf[dviptr] := x div 16777216;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end
  else
  begin
    x := x + 1073741824;
    x := x + 1073741824;
    begin
      dvibuf[dviptr] := (x div 16777216) + 128;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
  end;
  x := x mod 16777216;
  begin
    dvibuf[dviptr] := x div 65536;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  x := x mod 65536;
  begin
    dvibuf[dviptr] := x div 256;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  begin
    dvibuf[dviptr] := x mod 256;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
end;
