procedure indentinhmode;
var
  p, q: halfword;
begin
  if curchr > 0 then
  begin
    p := newnullbox;
    mem[p + 1].int := eqtb[5830].int;
    if abs(curlist.modefield) = 102 then
      curlist.auxfield.hh.lh := 1000
    else
    begin
      q := newnoad;
      mem[q + 1].hh.rh := 2;
      mem[q + 1].hh.lh := p;
      p := q;
    end;
    begin
      mem[curlist.tailfield].hh.rh := p;
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
  end;
end;
