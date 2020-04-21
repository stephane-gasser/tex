procedure shiftcase;
var
  b: halfword;
  p: halfword;
  t: halfword;
  c: eightbits;
begin
  b := curchr;
  p := scantoks(false, false);
  p := mem[defref].hh.rh;
  while p <> 0 do
  begin
    {1289:}
t := mem[p].hh.lh;
    if t < 4352 then
    begin
      c := t mod 256;
      if eqtb[b + c].hh.rh <> 0 then
        mem[p].hh.lh := t - c + eqtb[b + c].hh.rh;
    end{:1289}
;
    p := mem[p].hh.rh;
  end;
  begintokenlist(mem[defref].hh.rh, 3);
  begin
    mem[defref].hh.rh := avail;
    avail := defref;{dynused:=dynused-1;}

  end;
end;
