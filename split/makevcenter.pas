procedure makevcenter(q: halfword);
var
  v: halfword;
  delta: scaled;
begin
  v := mem[q + 1].hh.lh;
  if mem[v].hh.b0 <> 1 then
    confusion(539);
  delta := mem[v + 3].int + mem[v + 2].int;
  mem[v + 3].int := fontinfo[22 + parambase[eqtb[3937 + cursize].hh.rh]].int + half(delta);
  mem[v + 2].int := delta - mem[v + 3].int;
end;

