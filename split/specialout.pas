procedure specialout(p: halfword);
var
  oldsetting: 0..21;
  k: poolpointer;
begin
  if curh <> dvih then
  begin
    movement(curh - dvih, 143);
    dvih := curh;
  end;
  if curv <> dviv then
  begin
    movement(curv - dviv, 157);
    dviv := curv;
  end;
  oldsetting := selector;
  selector := 21;
  showtokenlist(mem[mem[p + 1].hh.rh].hh.rh, 0, poolsize - poolptr);
  selector := oldsetting;
  begin
    if poolptr + 1 > poolsize then
      overflow(257, poolsize - initpoolptr);
  end;
  if (poolptr - strstart[strptr]) < 256 then
  begin
    begin
      dvibuf[dviptr] := 239;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    begin
      dvibuf[dviptr] := (poolptr - strstart[strptr]);
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
  end
  else
  begin
    begin
      dvibuf[dviptr] := 242;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    dvifour((poolptr - strstart[strptr]));
  end;
  for k := strstart[strptr] to poolptr - 1 do
  begin
    dvibuf[dviptr] := strpool[k];
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  poolptr := strstart[strptr];
end;

