procedure setmathchar(c: integer);
var
  p: halfword;
begin
  if c >= 32768 then{1152:}

  begin
    curcs := curchr + 1;
    curcmd := eqtb[curcs].hh.b0;
    curchr := eqtb[curcs].hh.rh;
    xtoken;
    backinput;
  end{:1152}

  else
  begin
    p := newnoad;
    mem[p + 1].hh.rh := 1;
    mem[p + 1].hh.b1 := c mod 256 + 0;
    mem[p + 1].hh.b0 := (c div 256) mod 16;
    if c >= 28672 then
    begin
      if ((eqtb[5307].int >= 0) and (eqtb[5307].int < 16)) then
        mem[p + 1].hh.b0 := eqtb[5307].int;
      mem[p].hh.b0 := 16;
    end
    else
      mem[p].hh.b0 := 16 + (c div 4096);
    mem[curlist.tailfield].hh.rh := p;
    curlist.tailfield := p;
  end;
end;
