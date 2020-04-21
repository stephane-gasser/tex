procedure dvifontdef(f: internalfontnumber);
var
  k: poolpointer;
begin
  begin
    dvibuf[dviptr] := 243;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  begin
    dvibuf[dviptr] := f - 1;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  begin
    dvibuf[dviptr] := fontcheck[f].b0 - 0;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  begin
    dvibuf[dviptr] := fontcheck[f].b1 - 0;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  begin
    dvibuf[dviptr] := fontcheck[f].b2 - 0;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  begin
    dvibuf[dviptr] := fontcheck[f].b3 - 0;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  dvifour(fontsize[f]);
  dvifour(fontdsize[f]);
  begin
    dvibuf[dviptr] := (strstart[fontarea[f] + 1] - strstart[fontarea[f]]);
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  begin
    dvibuf[dviptr] := (strstart[fontname[f] + 1] - strstart[fontname[f]]);
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  {603:}
for k := strstart[fontarea[f]] to strstart[fontarea[f] + 1] - 1 do
  begin
    dvibuf[dviptr] := strpool[k];
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  for k := strstart[fontname[f]] to strstart[fontname[f] + 1] - 1 do
  begin
    dvibuf
      [dviptr] := strpool[k];
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end{:603}
;
end;
